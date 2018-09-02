package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.polidea.rxandroidble.RxBleDevice;

import java.util.ArrayList;
import java.util.List;

public final class MovesenseConnectedDevices {

    private static final String LOG_TAG = MovesenseConnectedDevices.class.getSimpleName();
    private static final List<MovesenseDevice> movesenseDevices = new ArrayList<>();
    private static final List<RxBleDevice> rxMovesenseConnectedDevices = new ArrayList<>();

    public static void addConnectedDevice(MovesenseDevice movesenseDevice) {
        if (!movesenseDevices.contains(movesenseDevice))
            movesenseDevices.add(movesenseDevice);
    }

    public static void removeConnectedDevice(MovesenseDevice movesenseDevice) {
        if (movesenseDevices.contains(movesenseDevice))
            movesenseDevices.remove(movesenseDevice);
    }

    public static List<MovesenseDevice> getConnectedDevices() {
        return movesenseDevices;
    }

    public static MovesenseDevice getConnectedDevice(int index) {
        return movesenseDevices.get(index);
    }

    public static void addRxConnectedDevice(RxBleDevice rxBleDevice) {
        if (!rxMovesenseConnectedDevices.contains(rxBleDevice)) {
            rxMovesenseConnectedDevices.add(rxBleDevice);
        }
    }

    public static void removeRxConnectedDevice(RxBleDevice rxBleDevice) {
        if (rxMovesenseConnectedDevices.contains(rxBleDevice)) {
            rxMovesenseConnectedDevices.remove(rxBleDevice);
        }
    }

    public static List<RxBleDevice> getRxMovesenseConnectedDevices() {
        return rxMovesenseConnectedDevices;
    }

    public static RxBleDevice getConnectedRxDevice(int index) {
        return rxMovesenseConnectedDevices.get(index);
    }

}
