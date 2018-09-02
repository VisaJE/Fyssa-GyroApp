package com.movesense.mds.fyssagyro.app_using_mds_api.tests;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.SwitchCompat;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsNotificationListener;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.MdsSubscription;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.ConnectionLostDialog;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.FormatHelper;
import com.movesense.mds.fyssagyro.app_using_mds_api.logs.LogsManager;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.Temperature;
import com.polidea.rxandroidble.RxBleDevice;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;
import butterknife.OnClick;

public class TemperatureTestActivity extends AppCompatActivity implements BleManager.IBleConnectionMonitor {

    private final String LOG_TAG = TemperatureTestActivity.class.getSimpleName();
    private final String TEMPERATURE_PATH = "/Meas/Temp";
    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";
    public static final String URI_SCHEME_PREFIX = "suunto://";
    private final double KELVIN_ABSOLUTE_ZERO = 274.15;
    private MdsSubscription mdsSubscription;
    @BindView(R.id.temperature_connected_device_textView) TextView temperatureConnectedDeviceTextView;
    @BindView(R.id.temperature_switch) SwitchCompat temperatureSwitch;
    @BindView(R.id.temperature_switch_layout) LinearLayout temperatureSwitchLayout;
    @BindView(R.id.temperature_get_button) Button temperatureGetButton;
    @BindView(R.id.temperature_kelvin_textView) TextView temperatureKelvinTextView;
    @BindView(R.id.temperature_celsius_textView) TextView temperatureCelsiusTextView;
    private AlertDialog alertDialog;
    private LogsManager logsManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_temperature_test);
        ButterKnife.bind(this);

        logsManager = new LogsManager(this);

        alertDialog = new AlertDialog.Builder(this)
                .setTitle(R.string.please_wait)
                .setMessage(R.string.loading_information)
                .create();


        // TODO: temporary disable subscribe ( bug)
        temperatureSwitch.setEnabled(false);
        temperatureSwitchLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(TemperatureTestActivity.this, R.string.temporary_disabled, Toast.LENGTH_LONG).show();
            }
        });

        BleManager.INSTANCE.addBleConnectionMonitorListener(this);
    }


    @OnCheckedChanged(R.id.temperature_switch)
    public void onCheckedChange(CompoundButton compoundButton, boolean isChecked) {
        if (isChecked) {

            // Clear Logcat
            logsManager.clearAdbLogcat();

            mdsSubscription = com.movesense.mds.Mds.builder().build(this).subscribe(URI_EVENTLISTENER,
                    FormatHelper.formatContractToJson(MovesenseConnectedDevices.getConnectedDevice(0).getSerial(),
                            TEMPERATURE_PATH), new MdsNotificationListener() {
                        @Override
                        public void onNotification(String data) {
                            Log.d(LOG_TAG, "Temperature onNotification() : " + data);

                            Temperature temperature = new Gson().fromJson(data, Temperature.class);

                            if (temperature != null) {
                                temperatureKelvinTextView.setText(String.format(getString(R.string.kelvin) + " %.6f", temperature.content.measurement));
                                temperatureCelsiusTextView.setText(String.format(getString(R.string.celsius) + " %.6f", (temperature.content.measurement - KELVIN_ABSOLUTE_ZERO)));
                            }
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "Temperature onError(", error);
                        }
                    });
        } else {
            unSubscribe();

            // Save logs
            saveAdbLogsToFile(LOG_TAG);
        }
    }

    @OnClick(R.id.temperature_get_button)
    public void onClick() {

        alertDialog.show();

        Mds.builder().build(this).get(URI_SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + TEMPERATURE_PATH,
                null, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String data) {
                        alertDialog.dismiss();
                        Log.d(LOG_TAG, "Temperature onSuccess(): " + data);

                        Temperature temperature = new Gson().fromJson(data, Temperature.class);

                        if (temperature != null) {
                            temperatureKelvinTextView.setText(String.format(getString(R.string.kelvin) + " %.6f", temperature.content.measurement));
                            temperatureCelsiusTextView.setText(String.format(getString(R.string.celsius) + " %.6f", (temperature.content.measurement - KELVIN_ABSOLUTE_ZERO)));
                        }
                    }

                    @Override
                    public void onError(MdsException error) {
                        alertDialog.dismiss();
                        Log.e(LOG_TAG, "Temperature onError(", error);
                    }
                });
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        unSubscribe();

        BleManager.INSTANCE.removeBleConnectionMonitorListener(this);
    }

    private void unSubscribe() {
        if (mdsSubscription != null) {
            mdsSubscription.unsubscribe();
            mdsSubscription = null;
        }
    }

    private void saveAdbLogsToFile(String logTag) {
        if (!logsManager.checkRuntimeWriteExternalStoragePermission(this, this)) {
            return;
        }

        logsManager.saveLogsToSdCard(logTag);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {

        if (requestCode == LogsManager.REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION) {
            // if request is cancelled grantResults array is empty
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

                if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                        == PackageManager.PERMISSION_GRANTED) {

                    // Save logs
                    saveAdbLogsToFile(LOG_TAG);
                }
            }
        }
    }

    @Override
    public void onDisconnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onDisconnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ConnectionLostDialog.INSTANCE.showDialog(TemperatureTestActivity.this);
            }
        });
    }

    @Override
    public void onConnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onConnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        ConnectionLostDialog.INSTANCE.dismissDialog();
    }
}
