package com.movesense.mds.fyssagyro.app_using_mds_api.adb;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsNotificationListener;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.MdsSubscription;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.app_using_mds_api.FormatHelper;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;

import java.util.HashMap;
import java.util.Map;

public class AdbBridge extends BroadcastReceiver {

    private final String LOG_TAG = AdbBridge.class.getSimpleName();
    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";

    private static Map<String, MdsSubscription> mSubscriptions = new HashMap<>();
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(LOG_TAG, "onReceive()");
        //No connected device
        if (MovesenseConnectedDevices.getConnectedDevices().size() == 0) {
            Log.i(LOG_TAG, "No devices connected");
            return;
        }

        //No paramaters
        if (intent.getExtras() == null) {
            Log.i(LOG_TAG, "No extras");
            return;
        }

        final Mds build = Mds.builder().build(context);

        //Get Extras
        final String type;
        final String path;
        final String value;
        final String id;
        try {
            type = intent.getStringExtra("type").toLowerCase();
            path = intent.getStringExtra("path");
            value = intent.getStringExtra("value");
            id = intent.getStringExtra("id");
        } catch (Exception e) {
            Log.i(LOG_TAG, "Extras error");
            return;
        }

        if (type.equals("subscribe")) {
            MdsSubscription mdsSubscription = build.subscribe(URI_EVENTLISTENER,
                    FormatHelper.formatContractToJson(
                            MovesenseConnectedDevices.getConnectedDevice(0).getSerial(),
                            path),
                    new MdsNotificationListener() {
                        @Override
                        public void onNotification(String data) {
                            Log.d(LOG_TAG, "ID:" + id + " " + path + " OUTPUT: " + data);

                        }
                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError(): ", error);
                        }
                    });

            mSubscriptions.put(path, mdsSubscription);
            MdsSubscription sub = mSubscriptions.get(path);
        } else if (type.equals("unsubscribe")) {
            try {
                MdsSubscription sub = mSubscriptions.get(path);
                if (sub != null)
                    sub.unsubscribe();
                mSubscriptions.remove(path);
            } catch (Exception e) {
                Log.e(LOG_TAG, "onError(): ", e);
            }
        }  else if (type.equals("get")) {
            build.get(MdsRx.SCHEME_PREFIX + MovesenseConnectedDevices.getConnectedDevice(0).getSerial()+ "/" + path,
                    value, new MdsResponseListener() {
                        @Override
                        public void onSuccess(String data) {
                            Log.d(LOG_TAG, "ID:" + id + " " + path + " OUTPUT: " + data);
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError()", error);
                        }
                    });
        }  else if (type.equals("put")) {
            build.put(MdsRx.SCHEME_PREFIX + MovesenseConnectedDevices.getConnectedDevice(0).getSerial()+ "/" + path,
                    value, new MdsResponseListener() {
                        @Override
                        public void onSuccess(String data) {
                            Log.d(LOG_TAG, "ID:" + id + " " + path + " OUTPUT: " + data);
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError()", error);
                        }
                    });
        } else if (type.equals("post")) {
            build.post(MdsRx.SCHEME_PREFIX + MovesenseConnectedDevices.getConnectedDevice(0).getSerial()+ "/" + path,
                    value, new MdsResponseListener() {
                        @Override
                        public void onSuccess(String data) {
                            Log.d(LOG_TAG, "ID:" + id + " " + path + " OUTPUT: " + data);
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError()", error);
                        }
                    });
        }
    }
}
