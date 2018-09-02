package com.movesense.mds.fyssagyro.app_using_mds_api.tests;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.SwitchCompat;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.TextView;

import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.ConnectionLostDialog;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.polidea.rxandroidble.RxBleDevice;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;

public class LedTestActivity extends AppCompatActivity implements BleManager.IBleConnectionMonitor {

    @BindView(R.id.led_on_off_switch) SwitchCompat ledOnOffSwitch;
    @BindView(R.id.response_textView) TextView responseTextView;

    private final String LOG_TAG = LedTestActivity.class.getSimpleName();
    private final String LED_PATH = "/Component/Led";
    private final String LED_PARAMETER = "{\"isOn\":";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led_test);
        ButterKnife.bind(this);

        BleManager.INSTANCE.addBleConnectionMonitorListener(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        BleManager.INSTANCE.removeBleConnectionMonitorListener(this);
    }

    @OnCheckedChanged(R.id.led_on_off_switch)
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

        // Block switch until response will come
        ledOnOffSwitch.setEnabled(false);

        // Set waiting status
        responseTextView.setText(R.string.waiting_for_response);
        responseTextView.setTextColor(getResources().getColor(android.R.color.darker_gray));

        Mds.builder().build(this).put(MdsRx.SCHEME_PREFIX
                        + MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + LED_PATH
                , LED_PARAMETER + isChecked + "}", new MdsResponseListener() {
                    @Override
                    public void onSuccess(String data) {
                        Log.d(LOG_TAG, "onSuccess: " + data);
                        ledOnOffSwitch.setEnabled(true);

                        // Set success result
                        responseTextView.setText(R.string.success);
                        responseTextView.setTextColor(getResources().getColor(android.R.color.holo_green_dark));
                    }

                    @Override
                    public void onError(MdsException error) {
                        Log.e(LOG_TAG, "onError()", error);
                        ledOnOffSwitch.setEnabled(true);

                        // Set error result
                        responseTextView.setText(R.string.error);
                        responseTextView.setTextColor(getResources().getColor(android.R.color.holo_red_dark));

                    }
                });
    }

    @Override
    public void onDisconnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onDisconnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ConnectionLostDialog.INSTANCE.showDialog(LedTestActivity.this);
            }
        });
    }

    @Override
    public void onConnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onConnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        ConnectionLostDialog.INSTANCE.dismissDialog();
    }
}
