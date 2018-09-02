package com.movesense.mds.fyssagyro;

import android.bluetooth.BluetoothGattCharacteristic;

import com.polidea.rxandroidble.RxBleDevice;

import java.util.ArrayList;
import java.util.List;

import rx.Subscription;

/**
 * Class to wrap a connected device
 */
public class ConnectedDevice {
    private static final byte START_END_MARK = 0x7e;
    // Escape mark before START_END_MARK means that START_END_MARK is packet content. Not start or end mark.
    private static final byte ESCAPE_MARK = 0x7d;

    private final RxBleDevice bleDevice;
    private final Subscription notifySubscription;
    private final BluetoothGattCharacteristic writeCharasteristic;
    private List<Byte> receivedData;

    ConnectedDevice(RxBleDevice bleDevice,
                           Subscription notifySubscription,
                           BluetoothGattCharacteristic writeCharasteristic) {
        this.bleDevice = bleDevice;
        this.notifySubscription = notifySubscription;
        this.writeCharasteristic = writeCharasteristic;
        this.receivedData = new ArrayList<>();
    }

    RxBleDevice getBleDevice() {
        return bleDevice;
    }

    BluetoothGattCharacteristic getWriteCharasteristic() {
        return writeCharasteristic;
    }

    void addData(byte[] data) {
        for (byte b : data) {
            receivedData.add(b);
        }
    }


    public byte[] getNextPacket() {
        if (receivedData.size() < 2)
            return null;

        int endPos = receivedData.lastIndexOf(START_END_MARK);

        // If START_END_MARK is only the first
        if (endPos < 1) {
            return null;
        }

        // If there is empty packet
        if (endPos == 1) {
            receivedData.remove(0);
            return getNextPacket();
        }

        // If START_END_MARK was escaped
        if (receivedData.get(endPos - 1).equals(ESCAPE_MARK)) {
            return null;
        }

        // End position is valid
        List<Byte> packet = receivedData.subList(0, endPos + 1);
        // Decode and validate
        List<Byte> decoded = Util.sfDecode(packet);

        for(int i = 0; i < endPos + 1; i++) {
            receivedData.remove(0);
        }

        // Decode and validate
        if (decoded.size() < 2) {
            // Decode not successful. Try next packet
            return getNextPacket();
        }

        return Util.toByteArray(decoded);
    }

}
