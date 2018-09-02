package com.movesense.mds.fyssagyro;

import android.app.Activity;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import com.movesense.mds.BLEDelegate;
import com.movesense.mds.BLEWrapper;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.polidea.rxandroidble.RxBleConnection;
import com.polidea.rxandroidble.RxBleDevice;
import com.polidea.rxandroidble.RxBleDeviceServices;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.UUID;

import rx.Observable;
import rx.Subscription;
import rx.functions.Action1;
import rx.functions.Func1;
import rx.subjects.PublishSubject;

/**
 * Manger responsible for handling the real BLE devices and passing
 * messages from WB to device and back.
 */
public enum BleManager implements BLEDelegate {
    INSTANCE;

    private static final String TAG = BleManager.class.getSimpleName();

    private static final int MAXIMUM_TRANSMISSION_UNIT = 20; // System MTU size
    private static final UUID NG_SERVICE_UUID = UUID.fromString("61353090-8231-49cc-b57a-886370740041"); //NON-NLS Data access service
    private static final UUID NG_WRITE_CHARACTERISTIC_UUID = UUID.fromString("17816557-5652-417f-909f-3aee61e5fa85"); //NON-NLS write / send
    //public static final UUID NG_READ_CHARACTERISTIC_UUID = UUID.fromString("34802252-7185-4d5d-b431-630e7050e8f0"); //NON-NLS read / receive
    private static final UUID NG_NOTIFY_CHARACTERISTIC_UUID = UUID.fromString("34802252-7185-4d5d-b431-630e7050e8f0"); //NON-NLS read / receive

    private final BLEWrapper bleWrapper;
    private final AddressMap addressMap;
    private final Map<String, Subscription> subscriptionMap;
    private final Map<String, RxBleConnection> connectionMap;
    private final Map<String, ConnectedDevice> devicesMap;
    private PublishSubject<Void> disconnectTriggerSubject = PublishSubject.create();
    private static int CONNECTION_TRY = 0;
    private final int CONNECTION_TIMEOUT_RETRY = 3000;
    private ArrayList<IBleConnectionMonitor> mIBleConnectionMonitorArrayList;

    public boolean isReconnectToLastConnectedDeviceEnable = true;

    BleManager() {
        bleWrapper = new BLEWrapper();
        bleWrapper.setDelegate(this);
        addressMap = new AddressMap();
        subscriptionMap = new HashMap<>();
        connectionMap = new HashMap<>();
        devicesMap = new HashMap<>();
        mIBleConnectionMonitorArrayList = new ArrayList<>();
    }

    public void connect(final RxBleDevice bleDevice, final Activity context) {
        Log.d(TAG, "connecting to " + bleDevice.getMacAddress());
        Log.d(TAG, "isConnected: " + bleDevice.getConnectionState());
        Log.d(TAG, "Connection try: " + CONNECTION_TRY);

        final String bleMac = bleDevice.getMacAddress();
        if (isConnected(bleDevice)) {
            triggerDisconnect(bleDevice, context);
        } else {
            final Subscription subscription = bleDevice.establishConnection(false)
                    .takeUntil(disconnectTriggerSubject)
                    .flatMap(new Func1<RxBleConnection, Observable<RxBleDeviceServices>>() {
                        @Override
                        public Observable<RxBleDeviceServices> call(RxBleConnection rxBleConnection) {
                            Log.d(TAG, "BLE connection to " + bleMac + " done!");

                            // Add this connection to a map for later use
                            connectionMap.put(bleMac, rxBleConnection);

                            return rxBleConnection.discoverServices();
                        }
                    })
                    .map(new Func1<RxBleDeviceServices, ConnectedDevice>() {
                        @Override
                        public ConnectedDevice call(RxBleDeviceServices rxBleDeviceServices) {
                            Log.d(TAG, "Got service BLE from " + bleMac);

                            BluetoothGattService ngService = null;
                            for (BluetoothGattService service : rxBleDeviceServices.getBluetoothGattServices()) {
                                Log.e(TAG, "ngServices UUID: " + service.getUuid());
                                Log.e(TAG, "ngServices Instance Id: " + service.getInstanceId());
                                if (NG_SERVICE_UUID.equals(service.getUuid())) {
                                    ngService = service;
                                    break;
                                }
                            }

                            // If there are no proper service, just throw an error
                            if (ngService == null) {
                                // try connect again in case of error
                                context.runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        Log.e(TAG, "Connected device not a proper ng device");

                                        new Handler().postDelayed(new Runnable() {
                                            @Override
                                            public void run() {
                                                MdsRx.Instance.connect(bleDevice, context);
                                            }
                                        }, CONNECTION_TIMEOUT_RETRY);

                                    }
                                });
                                return null;
                            }

                            BluetoothGattCharacteristic notifyCharacteristic = ngService.getCharacteristic(NG_NOTIFY_CHARACTERISTIC_UUID);
                            BluetoothGattCharacteristic writeCharacteristic = ngService.getCharacteristic(NG_WRITE_CHARACTERISTIC_UUID);

                            // Setup notifications for incoming data
                            RxBleConnection connection = connectionMap.get(bleMac);
                            Subscription notifySubscription = connection.setupNotification(notifyCharacteristic)
                                    .doOnNext(new Action1<Observable<byte[]>>() {
                                        @Override
                                        public void call(Observable<byte[]> observable) {
                                            Log.d(TAG, "Notifications set, calling bypassConnect()");

                                            // Bypass connect in WB to make it aware of this new device
                                            String wbAddress = addressMap.getOrCreateWbAddress(bleMac);
                                            bleWrapper.bypassConnect(wbAddress);
                                        }
                                    })
                                    .flatMap(new Func1<Observable<byte[]>, Observable<byte[]>>() {
                                        @Override
                                        public Observable<byte[]> call(Observable<byte[]> observable) {
                                            return observable;
                                        }
                                    })
                                    .subscribe(new Action1<byte[]>() {
                                        @Override
                                        public void call(byte[] bytes) {
                                            dataAvailable(bleMac, bytes);
                                        }
                                    }, new ThrowableLoggingAction(TAG, "Error while receiving data"));

                            ConnectedDevice device = new ConnectedDevice(bleDevice, notifySubscription, writeCharacteristic);
                            MovesenseConnectedDevices.addRxConnectedDevice(bleDevice);
                            devicesMap.put(bleMac, device);

                            notifyConnectBleConnectionMonitorListeners(bleDevice);

                            return device;
                        }
                    })
                    .subscribe(new Action1<ConnectedDevice>() {
                        @Override
                        public void call(ConnectedDevice connectedDevice) {
                            // ..
                        }
                    }, new Action1<Throwable>() {
                        @Override
                        public void call(Throwable throwable) {
                            // Unwind the connection (if it happened)
                            Subscription s = subscriptionMap.get(bleMac);
                            if (s != null) {
                                s.unsubscribe();
                            }

                            // Remove this from subscriptions and connections
                            subscriptionMap.remove(bleMac);
                            connectionMap.remove(bleMac);
                            addressMap.removeBleMac(bleMac);
                            devicesMap.remove(bleMac);

                            String wbAddress = addressMap.getOrCreateWbAddress(bleMac);
                            bleWrapper.bypassDisconnect(wbAddress);

                            notifyDisconnectBleConnectionMonitorListeners(bleDevice);

                            Log.e(TAG, "Could not connect to " + bleMac, throwable);

                            // try connect again in case of error but not if DFU mode is running
                            context.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    new Handler().postDelayed(new Runnable() {
                                        @Override
                                        public void run() {
                                            if (isReconnectToLastConnectedDeviceEnable) {
                                                MdsRx.Instance.connect(bleDevice, context);
                                            }
                                        }
                                    }, CONNECTION_TIMEOUT_RETRY);
                                }
                            });
                        }
                    });

            // Add this subscription to map so that we can disconnect later by unsubscribing
            subscriptionMap.put(bleMac, subscription);
        }
    }

    private void triggerDisconnect(final RxBleDevice rxBleDevice, final Activity activity) {
        Log.e(TAG, "triggerDisconnect()");
        disconnect(rxBleDevice);
        disconnectTriggerSubject.onNext(null);

        // Try connect again after disconnect but not if DFU mode is running
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                if (isReconnectToLastConnectedDeviceEnable) {
                    MdsRx.Instance.connect(rxBleDevice, activity);
                }
            }
        }, CONNECTION_TIMEOUT_RETRY);
    }

    public void disconnect(RxBleDevice rxBleDevice) {
        Log.d(TAG, "disconnect(): " + rxBleDevice.getMacAddress());

        String wbAddress = addressMap.getOrCreateWbAddress(rxBleDevice.getMacAddress());
        String bleMac = addressMap.getBleMac(wbAddress);
        if (bleMac != null) {
            Subscription subscription = subscriptionMap.get(bleMac);
            if (subscription != null) {
                subscription.unsubscribe();
            }

            subscriptionMap.remove(bleMac);
            connectionMap.remove(bleMac);
            addressMap.removeBleMac(bleMac);
            devicesMap.remove(bleMac);
        }

       // notifyDisconnectBleConnectionMonitorListeners(rxBleDevice);

        Log.d(TAG, "disconnect() wbAddress: " + wbAddress);
        bleWrapper.bypassDisconnect(wbAddress);
    }

    public void reconnect(final Activity activity) {
        disconnect(MovesenseConnectedDevices.getConnectedRxDevice(0));

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                connect(MovesenseConnectedDevices.getConnectedRxDevice(0), activity);
            }
        }, 2000);
    }

    private boolean isConnected(RxBleDevice rxBleDevice) {
        return rxBleDevice.getConnectionState() == RxBleConnection.RxBleConnectionState.CONNECTED;
    }

    @Override
    public boolean connectCb(final String wbAddress) {
        Log.d(TAG, "connectCb(" + wbAddress + ")");

        // Wait a bit before calling connectComplete (exit this thread)
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    // ..
                }

                Log.d(TAG, "calling connectCompleted(" + wbAddress + ")");
                bleWrapper.connectCompleted(wbAddress, true);
            }
        }).start();

        return true;
    }

    @Override
    public boolean cancelConnectCb(String wbAddress) {
        Log.d(TAG, "cancelConnectCb(" + wbAddress + ")");

        // TODO: There is currently no option to cancel, so best we can do is try to disconnect
        return disconnectCb(wbAddress);
    }

    @Override
    public boolean disconnectCb(String wbAddress) {
        Log.d(TAG, "disconnectCb(" + wbAddress + ")");

        String bleMac = addressMap.getBleMac(wbAddress);
        if (bleMac != null) {
            Subscription subscription = subscriptionMap.get(bleMac);
            if (subscription != null) {
                subscription.unsubscribe();
            }

            subscriptionMap.remove(bleMac);
            connectionMap.remove(bleMac);
            addressMap.removeBleMac(bleMac);
            devicesMap.remove(bleMac);
            return true;
        } else {
            Log.w(TAG, "No ble address found for cancel");
            return false;
        }
    }

    @Override
    public boolean sendCb(String wbAddress, byte[] wbData, int wbSize, final long wbLocalDataPointer) {
        Log.d(TAG, "sendCb(" + wbAddress + "), " + wbSize + " bytes");

        String bleMac = addressMap.getBleMac(wbAddress);
        if (bleMac == null) {
            Log.e(TAG, "No BleMac address found!");
            return false;
        }

        RxBleConnection connection = connectionMap.get(bleMac);
        if (connection == null) {
            Log.e(TAG, "No connection found!");
            return false;
        }

        ConnectedDevice device = devicesMap.get(bleMac);
        if (device == null) {
            Log.e(TAG, "No device found!");
            return false;
        }

        byte[] encoded = Util.sfEncode(wbData);

        // Reset connection tries
        CONNECTION_TRY = 0;

        // Do the writing
        connection.createNewLongWriteBuilder()
                .setCharacteristic(device.getWriteCharasteristic())
                .setBytes(encoded)
                .setMaxBatchSize(MAXIMUM_TRANSMISSION_UNIT)
                .build()
                .toSingle()
                .subscribe(new Action1<byte[]>() {
                    @Override
                    public void call(byte[] bytes) {
                        Log.d(TAG, "Send complete");
                    }
                }, new ThrowableLoggingAction(TAG, "Data write failed"));

        return true;
    }

    @Override
    public boolean cancelSendCb(long wbLocalDataPointer) {
        Log.d(TAG, "cancelSendCb(" + wbLocalDataPointer + ")");

        // Cancel is not really supported here, so just return true
        return true;
    }

    @Override
    public BLEWrapper.WbAddress deviceToWhiteboardCb(int wbDeviceId) {
        Log.d(TAG, "deviceToWhiteboardCb: wbDeviceId: " + wbDeviceId);
        return new BLEWrapper.WbAddress(Integer.toHexString(wbDeviceId));
    }

    @Override
    public int whiteboardToDevice(String wbAddress) {
        Log.d(TAG, "whiteboardToDevice: wbAddress: " + wbAddress);
        return Integer.valueOf(wbAddress, 16);
    }

    @Override
    public BLEWrapper.ConnectedDevices getConnectedBleDevicesCb() {
        Log.d(TAG, "getConnectedBleDevicesCb()");
        List<String> devicesList = new ArrayList<>();

        for (ConnectedDevice device : devicesMap.values()) {
            String name = device.getBleDevice().getName();
            String bleMac = device.getBleDevice().getMacAddress();
            String wbAddress = addressMap.getWbAddress(bleMac);
            String serial = Util.getVisibleSerial(name);

            if (serial != null && name != null && wbAddress != null && !serial.isEmpty()) {
                devicesList.add(wbAddress);
                devicesList.add(serial);
                devicesList.add(name);
            } else {
                Log.w(TAG, "Invalid device info: name: " + name + ", mac: " + bleMac + ", " +
                        "serial: " + serial + ", wbAddress: " + wbAddress);
            }
        }

        Log.d(TAG, "Found connected devices: " + devicesList.toString());
        return new BLEWrapper.ConnectedDevices(Util.toStringArray(devicesList));
    }

    /**
     * Called internally when there is data available from a device
     *
     * @param bleMac Mac address of the device that got data
     * @param data   Data
     */
    private void dataAvailable(@NonNull String bleMac, @NonNull byte[] data) {
        // Data available, add it to device and notify
        ConnectedDevice device = devicesMap.get(bleMac);
        if (device == null) {
            throw new IllegalStateException("Got data for non-existing device!");
        }

        device.addData(data);

        byte[] packet = device.getNextPacket();
        if (packet != null) {
            Log.d(TAG, "Received data: " + wbPacketDemystifier(packet));
            bleWrapper.dataReceived(addressMap.getWbAddress(bleMac), packet, packet.length);
        }
    }

    /**
     * Provide a more human readable interpretation of a WB packet.
     * Debug/logging only!
     *
     * @param wbData Data to demystify
     * @return Demystified String
     */
    private String wbPacketDemystifier(byte[] wbData) {
        if (wbData == null) {
            return "Null packet"; //NON-NLS
        }
        if (wbData[0] != (byte) 0xA5) { // 0xA5 is a magic number for WB packets
            return "Not a valid packet. Does not start with 0xA5"; //NON-NLS
        }
        if (wbData.length < 2) {
            return "Empty packet"; //NON-NLS
        }
        if (wbData.length < 4) {
            return "Packet too short to be meaningful"; //NON-NLS
        }
        boolean routed;
        routed = ((wbData[1] & 0x80) == 0x80);
        int type = wbData[1] & 0x7F;
        String result = String.format(Locale.getDefault(), "%s, type: %d, %s msg", WbMessageType.fromInt(type).toString(), type, (routed ? "routed" : "direct")); //NON-NLS

        int msgLen = (wbData[3] << 8) + wbData[2];
        int requestId = 0;
        if (wbData.length > 4) {
            requestId = ((wbData[4] << 8) + wbData[5]) & 0x0000ffff;
        }

        result = String.format(Locale.getDefault(), "%s, msgLen: %d, reqId: %d, size: %d", result, msgLen, requestId, wbData.length); //NON-NLS
        return result;
    }

    private enum WbMessageType {
        WB_MSG_INVALID(0),
        WB_DATAMSG_CLIENT_ON_NOTIFY(1),
        WB_DATAMSG_CLIENT_ON_GET_RESOURCE_RESULT(2),
        WB_DATAMSG_CLIENT_ON_RELEASE_RESOURCE_RESULT(3),
        DEPRECATED_WB_DATAMSG_CLIENT_ON_GET_RESOURCE_METADATA_RESULT(4),
        WB_DATAMSG_CLIENT_ON_GET_RESULT(5),
        WB_DATAMSG_CLIENT_ON_GET_STREAM(6),
        WB_DATAMSG_CLIENT_ON_PUT_RESULT(7),
        WB_DATAMSG_CLIENT_ON_SUBSCRIBE_RESULT(8),
        WB_DATAMSG_CLIENT_ON_UNSUBSCRIBE_RESULT(9),
        WB_DATAMSG_RESOURCE_GET_REQUEST(10),
        WB_DATAMSG_RESOURCE_RELEASE_REQUEST(11),
        DEPRECATED_WB_DATAMSG_RESOURCE_GET_METADATA_REQUEST(12),
        WB_DATAMSG_PROVIDER_GET_REQUEST(13),
        WB_DATAMSG_PROVIDER_PUT_REQUEST(14),
        DEPRECATED_WB_DATAMSG_PROVIDER_PUT_STREAM(15),
        WB_DATAMSG_PROVIDER_SUBSCRIBE_REQUEST(16),
        WB_DATAMSG_PROVIDER_UNSUBSCRIBE_REQUEST(17),
        WB_COMMMSG_HELLO(18),
        WB_COMMMSG_HELLO_ACK(19),
        WB_COMMMSG_KEEP_ALIVE(20),
        NOT_USED_2(21), // Thid was used by initial timer implementation, but was not ever transferred over the network
        WB_DATAMSG_PROVIDER_POST_REQUEST(22),
        WB_DATAMSG_PROVIDER_DELETE_REQUEST(23),
        WB_DATAMSG_CLIENT_ON_POST_RESULT(24),
        WB_DATAMSG_CLIENT_ON_DELETE_RESULT(25),
        WB_DATAMSG_DONT_UNDERSTAND(26),
        UNKNOWN(99);

        private final int value;

        WbMessageType(int v) {
            this.value = v;
        }

        public static WbMessageType fromInt(int v) {
            for (WbMessageType i : WbMessageType.values()) {
                if (i.value == v) {
                    return i;
                }
            }
            return WbMessageType.UNKNOWN;
        }
    }

    /**
     * Address translation map to get WB addresses out of ble mac address
     */
    private static class AddressMap {

        private final Map<String, String> wbAddressToBleMac;
        private final Map<String, String> bleMacToWbAddress;

        // Needs to be 8 _significant_ digits due to some SDS/WB implementation specifics
        private int nextDeviceHandle = 0x10000001;

        AddressMap() {
            wbAddressToBleMac = new HashMap<>();
            bleMacToWbAddress = new HashMap<>();
        }

        /**
         * Return wbAddress corresponding to given ble mac
         *
         * @param bleMac Address for which to look handle for
         * @return Valid handle, or null if not found
         */
        @Nullable
        String getWbAddress(@NonNull String bleMac) {
            return bleMacToWbAddress.get(bleMac);
        }

        /**
         * Returns wb handle corresponding to given ble mac, or creates new if
         * such handle is not present yet
         *
         * @param bleMac Address for which to look handle for
         * @return Valid handle
         */
        @NonNull
        synchronized String getOrCreateWbAddress(@NonNull String bleMac) {
            Log.e(TAG, "getOrCreateWbAddress: bleMac: " + bleMac);
            String wbAddress = getWbAddress(bleMac);
            Log.e(TAG, "getOrCreateWbAddress: wbAddress: " + wbAddress);
            if (wbAddress == null) {
                int handle = nextDeviceHandle++;
                Log.e(TAG, "getOrCreateWbAddress: handle: " + handle);
                wbAddress = Integer.toHexString(handle);
                Log.e(TAG, "getOrCreateWbAddress: wbAddress2: " + wbAddress);

                wbAddressToBleMac.put(wbAddress, bleMac);
                bleMacToWbAddress.put(bleMac, wbAddress);
            }

            return wbAddress;
        }

        /**
         * Translates wbAddress to ble mac address
         *
         * @param wbAddress WB Address to translate
         * @return Ble mac address or null if not found
         */
        @Nullable
        String getBleMac(@NonNull String wbAddress) {
            return wbAddressToBleMac.get(wbAddress);
        }

        /**
         * Removes given ble mac
         *
         * @param bleMac Address to remove
         */
        void removeBleMac(@NonNull String bleMac) {
            Log.e(TAG, "removeBleMac: bleMac: " + bleMac);
            String wbAddress = getWbAddress(bleMac);
            Log.e(TAG, "removeBleMac: wbAddress: " + wbAddress);
            if (wbAddress != null) {
                wbAddressToBleMac.remove(wbAddress);
                nextDeviceHandle--;
            }
            bleMacToWbAddress.remove(bleMac);
        }
    }

    public interface IBleConnectionMonitor {
        void onDisconnect(RxBleDevice rxBleDevice);

        void onConnect(RxBleDevice rxBleDevice);
    }

    public void addBleConnectionMonitorListener(IBleConnectionMonitor bleConnectionMonitor) {
        mIBleConnectionMonitorArrayList.add(bleConnectionMonitor);
    }

    public void notifyConnectBleConnectionMonitorListeners(RxBleDevice rxBleDevice) {
        for (IBleConnectionMonitor i : mIBleConnectionMonitorArrayList) {
            i.onConnect(rxBleDevice);
        }
    }

    public void notifyDisconnectBleConnectionMonitorListeners(RxBleDevice rxBleDevice) {
        for (IBleConnectionMonitor i : mIBleConnectionMonitorArrayList) {
            i.onDisconnect(rxBleDevice);
        }
    }

    public void removeBleConnectionMonitorListener(IBleConnectionMonitor bleConnectionMonitor) {
        if (mIBleConnectionMonitorArrayList.contains(bleConnectionMonitor)) {
            mIBleConnectionMonitorArrayList.remove(bleConnectionMonitor);
        } else {
            Log.e(TAG, "removeBleConnectionMonitorListener: NOT CONTAINS LISTENER" + bleConnectionMonitor);
        }
    }
}
