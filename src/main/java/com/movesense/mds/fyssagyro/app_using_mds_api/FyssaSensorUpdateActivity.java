package com.movesense.mds.fyssagyro.app_using_mds_api;

import android.app.ActivityManager;

import android.app.NotificationManager;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.content.Context;

import android.content.DialogInterface;
import android.content.Intent;

import android.content.pm.PackageManager;

import android.os.Build;
import android.os.Bundle;
import android.os.Handler;

import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;

import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;


import com.movesense.mds.fyssagyro.RxBle;
import com.movesense.mds.fyssagyro.ScannerFragment;
import com.movesense.mds.fyssagyro.ThrowableToastingAction;
import com.movesense.mds.fyssagyro.app_using_mds_api.dfu.DfuService;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.polidea.rxandroidble.RxBleClient;
import com.polidea.rxandroidble.RxBleDevice;
import com.polidea.rxandroidble.RxBleScanResult;


import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import no.nordicsemi.android.dfu.DfuProgressListener;
import no.nordicsemi.android.dfu.DfuServiceInitiator;
import no.nordicsemi.android.dfu.DfuServiceListenerHelper;

import rx.Subscription;
import rx.functions.Action1;
import rx.subscriptions.CompositeSubscription;

/**
 * Created by Eemil on 20.8.2018.
 */

public class FyssaSensorUpdateActivity extends AppCompatActivity implements ScannerFragment.DeviceSelectionListener, BleManager.IBleConnectionMonitor {


    @BindView(R.id.start_update) Button startUpdate;
    @BindView(R.id.dfu_select_device_btn2) Button dfuSelectDeviceBtn;

    private final String fileName = "movesense_dfu";

    private static final int PERMISSION_REQ = 25;
    private static final int ENABLE_BT_REQ = 0;

    private final String LOG_TAG = FyssaSensorUpdateActivity.class.getSimpleName();
    @BindView(R.id.dfu_uploading_tv2) TextView dfuUploadingTv;
    @BindView(R.id.dfu_uploading_percent_tv2) TextView dfuUploadingPercentTv;

    private static final String DATA_DEVICE = "device";
    private static final String DATA_STATUS = "status";
    private static final String DATA_DFU_COMPLETED = "dfu_completed";
    private static final String DATA_DFU_ERROR = "dfu_error";

    private ScannerFragment scannerFragment;
    private boolean mStatusOk;
    private RxBleDevice selectedDevice = null;
    private boolean mDfuCompleted;
    private boolean mResumed;
    private String mDfuError;
    private boolean mIsDeviceReconnected = false;
    private boolean isDfuEnable = false;

    private BluetoothAdapter bluetoothAdapter;

    CompositeSubscription cSubscriptions;
    Boolean subscribed = false;
    ArrayList<RxBleDevice> devices;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensor_update);
        ButterKnife.bind(this);
        Log.e(LOG_TAG, "onCreate");
        isBLESupported();
        if (!isBLEEnabled()) {
            showBLEDialog();
        }

        if (savedInstanceState != null) {
            selectedDevice = savedInstanceState.getParcelable(DATA_DEVICE);
            mStatusOk = mStatusOk || savedInstanceState.getBoolean(DATA_STATUS);
            startUpdate.setEnabled(selectedDevice != null && mStatusOk);
            mDfuCompleted = savedInstanceState.getBoolean(DATA_DFU_COMPLETED);
            mDfuError = savedInstanceState.getString(DATA_DFU_ERROR);
        }

        enableDfu();
        // Ask For Bluetooth
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!bluetoothAdapter.isEnabled()) {
            // Bluetooth is not enable so run
            bluetoothAdapter.enable();
        }

        DfuServiceListenerHelper.registerProgressListener(this, dfuProgressListener);

        BleManager.INSTANCE.addBleConnectionMonitorListener(this);

        startUpdate.setEnabled(false);

        skipDeviceScanningDialog();

    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.e(LOG_TAG, "onResume");
        mResumed = true;

        if (mDfuCompleted)
            onTransferCompleted();
        if (mDfuError != null)
            showErrorMessage(mDfuError);
        if (mDfuCompleted || mDfuError != null) {
            // if this activity is still open and upload process was completed, cancel the notification
            final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            manager.cancel(DfuService.NOTIFICATION_ID);
            mDfuCompleted = false;
            mDfuError = null;
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        mResumed = false;

        // save the data
        Log.e(LOG_TAG, "onPause");
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        Log.e(LOG_TAG, "onSaveInstanceState");

        outState.putParcelable(DATA_DEVICE, selectedDevice != null ? selectedDevice.getBluetoothDevice() : null);
        outState.putBoolean(DATA_STATUS, mStatusOk);
        outState.putBoolean(DATA_DFU_COMPLETED, mDfuCompleted);
        outState.putString(DATA_DFU_ERROR, mDfuError);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        DfuServiceListenerHelper.unregisterProgressListener(this, dfuProgressListener);
        Log.e(LOG_TAG, "onDestroy");
    }

    @OnClick({R.id.dfu_select_device_btn2, R.id.start_update})
    public void onViewClicked(View view) {
        switch (view.getId()) {
            case R.id.start_update:
                if (!isBLEEnabled()) {
                    showBLEDialog();
                }
                if (selectedDevice == null) {
                    if (devices.size() == 1) {
                        selectedDevice = devices.get(0);
                        Log.d(LOG_TAG, "Starting update on found device");
                    } else {
                        startUpdate.setEnabled(false);
                        return;
                    }
                }
                Log.d(LOG_TAG, "Found devices: " +devices.size());
                if (subscribed) {
                    subscribed = false;
                    cSubscriptions.unsubscribe();
                }
                devices.clear();
                dfuUploadingPercentTv.setVisibility(View.VISIBLE);
                dfuUploadingTv.setVisibility(View.VISIBLE);
                startUpdate.setEnabled(false);
                dfuSelectDeviceBtn.setEnabled(false);
                Log.d(LOG_TAG, "Beginning update!");
                Log.d(LOG_TAG, "Name: " + selectedDevice.getBluetoothDevice().getName());
                Log.d(LOG_TAG, "Address: " + selectedDevice.getBluetoothDevice().getAddress());

                DfuServiceInitiator serviceInitiator = new DfuServiceInitiator(selectedDevice.getBluetoothDevice().getAddress())
                        .setDeviceName(selectedDevice.getBluetoothDevice().getName())
                        .setKeepBond(false)
                        .setForceDfu(false)
                        .setPacketsReceiptNotificationsEnabled(Build.VERSION.SDK_INT < Build.VERSION_CODES.M)
                        .setPacketsReceiptNotificationsValue(DfuServiceInitiator.DEFAULT_PRN_VALUE)
                        .setUnsafeExperimentalButtonlessServiceInSecureDfuEnabled(true);

                Log.d(LOG_TAG, "File id:" + this.getResources().getIdentifier(fileName, "raw", this.getPackageName()));
                serviceInitiator.setZip(this.getResources().getIdentifier(fileName, "raw", this.getPackageName()));

                serviceInitiator.start(this, DfuService.class);
                break;
            case R.id.dfu_select_device_btn2:
                if (!isBLEEnabled()) {
                    showBLEDialog();
                }

                showDeviceScanningDialog();
                break;

        }
    }

    private void enableDfu() {
        Log.d(LOG_TAG, "enableDfu()");
        if (BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable && isDfuEnable) {
            Log.d(LOG_TAG, "enableDfu() BleManager.isReconnectToLastConnectedDeviceEnable");
            Toast.makeText(this, "Dfu Already Enabled", Toast.LENGTH_SHORT).show();
            return;
        }

        Mds.builder().build(this).put(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + "/System/Mode",
                "{\"NewState\":12}", new MdsResponseListener() {
                    @Override
                    public void onSuccess(String data) {
                        Log.e(LOG_TAG, "onSuccess(): " + data);
                        isDfuEnable = true;
                        BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable = false;
                    }

                    @Override
                    public void onError(MdsException error) {
                        Log.e(LOG_TAG, "onError(): ", error);
                        isDfuEnable = false;
                        Toast.makeText(FyssaSensorUpdateActivity.this, "Failed to enable DFU.", Toast.LENGTH_SHORT).show();
                    }
                });
    }



    private void showErrorMessage(final String message) {
        clearUI();
        Toast.makeText(this, "Upload failed: " + message, Toast.LENGTH_SHORT).show();
    }


    private boolean isBLEEnabled() {
        BluetoothManager manager = (BluetoothManager) getSystemService(BLUETOOTH_SERVICE);
        BluetoothAdapter adapter = manager.getAdapter();
        return adapter != null && adapter.isEnabled();
    }


    private void showDeviceScanningDialog() {
        scannerFragment = new ScannerFragment();
        scannerFragment.show(getSupportFragmentManager(), ScannerFragment.class.getName());
    }


    // Capture instance of RxBleClient to make code look cleaner
    RxBleClient rxBleClient = RxBle.Instance.getClient();

    private void skipDeviceScanningDialog() {
        Log.d(LOG_TAG, "Subscribing to rxBle devices.");
        cSubscriptions = new CompositeSubscription();
        subscribed = true;
        devices = new ArrayList<>();
        cSubscriptions.add(rxBleClient.scanBleDevices()
                .subscribe(new Action1<RxBleScanResult>() {
                    @Override
                    public void call(RxBleScanResult rxBleScanResult) {
                        //Log.d(LOG_TAG, "Found device name " + rxBleScanResult.getBleDevice().getName() + " mac: " + rxBleScanResult.getBleDevice().getMacAddress());
                        String dName = rxBleScanResult.getBleDevice().getName();
                        if (dName != null && dName.equals("DfuTarg")) {
                            if (!exists(devices, rxBleScanResult.getBleDevice())) {
                                Log.d(LOG_TAG, "New device!");

                                if (devices.size() >= 1) {
                                    Log.d(LOG_TAG, "Too many devices, forcing selection.");
                                    devices.add(rxBleScanResult.getBleDevice());
                                    startUpdate.setEnabled(false);
                                } else {
                                    devices.add(rxBleScanResult.getBleDevice());
                                    startUpdate.setEnabled(true);
                                }
                            }
                        }
                    }
                },  new ThrowableToastingAction(null)));

    }

    @Override
    public void onDeviceSelected(RxBleDevice device) {
        Log.d(LOG_TAG, "onDeviceSelected()");
        selectedDevice = device;
        scannerFragment.dismiss();
        if (subscribed) {
            subscribed = false;
            cSubscriptions.unsubscribe();
        }
        startUpdate.setEnabled(true);
    }

    DfuProgressListener dfuProgressListener = new DfuProgressListener() {
        @Override
        public void onDeviceConnecting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceConnecting");
        }

        @Override
        public void onDeviceConnected(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceConnected");
        }

        @Override
        public void onDfuProcessStarting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuProcessStarting");
        }

        @Override
        public void onDfuProcessStarted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuProcessStarted");
        }

        @Override
        public void onEnablingDfuMode(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onEnablingDfuMode");
        }

        @Override
        public void onProgressChanged(String deviceAddress, int percent, float speed, float avgSpeed, int currentPart, int partsTotal) {
            Log.d(LOG_TAG, "DfuProgress onProgressChanged percent: " + percent);
            dfuUploadingPercentTv.setText(percent + "%");
        }

        @Override
        public void onFirmwareValidating(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onFirmwareValidating");
        }

        @Override
        public void onDeviceDisconnecting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceDisconnecting");
        }

        @Override
        public void onDeviceDisconnected(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceDisconnected");
        }

        @Override
        public void onDfuCompleted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuCompleted");
            dfuUploadingPercentTv.setText(R.string.dfu_status_completed);
            if (mResumed) {
                // let's wait a bit until we cancel the notification. When canceled immediately it will be recreated by service again.
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        onTransferCompleted();

                        // if this activity is still open and upload process was completed, cancel the notification
                        final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                        manager.cancel(DfuService.NOTIFICATION_ID);
                    }
                }, 200);
            } else {
                //  Save that the DFU process has finished
                mDfuCompleted = true;
            }
        }

        @Override
        public void onDfuAborted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuAborted");
            dfuUploadingPercentTv.setText(R.string.dfu_status_aborted);
            // let's wait a bit until we cancel the notification. When canceled immediately it will be recreated by service again.
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    onUploadCanceled();

                    // if this activity is still open and upload process was completed, cancel the notification
                    final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                    manager.cancel(DfuService.NOTIFICATION_ID);
                }
            }, 200);
        }

        @Override
        public void onError(String deviceAddress, int error, int errorType, String message) {
            Log.d(LOG_TAG, "DfuProgress onError");
            if (mResumed) {
                showErrorMessage(message);

                // We have to wait a bit before canceling notification. This is called before DfuService creates the last notification.
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        // if this activity is still open and upload process was completed, cancel the notification
                        final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                        manager.cancel(DfuService.NOTIFICATION_ID);
                    }
                }, 200);
            } else {
                mDfuError = message;
            }
        }
    };

    private void showBLEDialog() {
        final Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(enableIntent, ENABLE_BT_REQ);
    }

    private void isBLESupported() {
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, "no Ble", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    private void onTransferCompleted() {
        clearUI();
        dfuUploadingTv.setVisibility(View.VISIBLE);
        dfuUploadingTv.setText("Reconnecting to the device...");

        BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable = true;

        isDfuEnable = false;

        // Reconnect to last connected device
        MdsRx.Instance.reconnect(this);
    }

    public void onUploadCanceled() {
        clearUI();
        Toast.makeText(this, "Dfu Aborted", Toast.LENGTH_SHORT).show();
    }

    private void clearUI() {
        dfuUploadingPercentTv.setVisibility(View.INVISIBLE);
        dfuUploadingTv.setVisibility(View.INVISIBLE);
        dfuSelectDeviceBtn.setEnabled(true);
        startUpdate.setEnabled(false);
        mStatusOk = false;
    }





    @Override
    public void onBackPressed() {
        if (BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable || !mIsDeviceReconnected) {
            new AlertDialog.Builder(this)
                    .setTitle("Dfu Mode")
                    .setMessage("DFU operations are running. Please wait until process will be finished.")
                    .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    }).show();
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public void onDisconnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onDisconnect: " + rxBleDevice.getMacAddress());

        mIsDeviceReconnected = false;
    }

    @Override
    public void onConnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onConnect: " + rxBleDevice.getMacAddress());

        mIsDeviceReconnected = true;

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(FyssaSensorUpdateActivity.this, "Connected", Toast.LENGTH_SHORT).show();
                if (mDfuCompleted) {
                    startActivity(new Intent(FyssaSensorUpdateActivity.this, SelectTestActivity.class)
                            .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
                }
            }
        });
    }
    private boolean exists(ArrayList<RxBleDevice> listed, RxBleDevice device) {
        boolean res = false;
        for (int i = 0; i < listed.size(); i++) {
            if (listed.get(i).getMacAddress().equals(device.getMacAddress()) ) res = true;
        }
        return res;
    }
}

