package com.movesense.mds.fyssagyro.app_using_mds_api;

import com.polidea.rxandroidble.RxBleDevice;

/**
 * Created by kosarzem on 2017-07-26.
 */

public class BleConnectionMonitor {

    public static IBleConnectionMonitor iBleConnectionMonitor;

    public interface IBleConnectionMonitor {
        void onDisconnect(RxBleDevice rxBleDevice);
        void onConnect(RxBleDevice rxBleDevice);
    }

    public static void setBleConnectionMonitorListener(IBleConnectionMonitor bleConnectionMonitorListener) {
        iBleConnectionMonitor = bleConnectionMonitorListener;
    }
}
