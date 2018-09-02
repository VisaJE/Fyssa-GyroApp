package com.movesense.mds.fyssagyro.app_using_mds_api.tests;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.SwitchCompat;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.TextView;


import com.google.gson.Gson;
import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsNotificationListener;
import com.movesense.mds.MdsSubscription;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.ConnectionLostDialog;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.FormatHelper;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.AngularVelocity;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.LinearAcceleration;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MagneticField;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.polidea.rxandroidble.RxBleDevice;

import java.util.Locale;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;

public class MultiSubscribeActivity extends AppCompatActivity implements BleManager.IBleConnectionMonitor {

    @BindView(R.id.connected_device_textView) TextView connectedDeviceTextView;
    @BindView(R.id.switchSubscriptionLinearAcc) SwitchCompat switchSubscriptionLinearAcc;
    @BindView(R.id.x_axis_linearAcc_textView) TextView xAxisLinearAccTextView;
    @BindView(R.id.y_axis_linearAcc_textView) TextView yAxisLinearAccTextView;
    @BindView(R.id.z_axis_linearAcc_textView) TextView zAxisLinearAccTextView;
    @BindView(R.id.switchSubscriptionMagneticField) SwitchCompat switchSubscriptionMagneticField;
    @BindView(R.id.x_axis_magneticField_textView) TextView xAxisMagneticFieldTextView;
    @BindView(R.id.y_axis_magneticField_textView) TextView yAxisMagneticFieldTextView;
    @BindView(R.id.z_axis_magneticField_textView) TextView zAxisMagneticFieldTextView;
    @BindView(R.id.switchSubscriptionAngularVelocity) SwitchCompat switchSubscriptionAngularVelocity;
    @BindView(R.id.x_axis_angularVelocity_textView) TextView xAxisAngularVelocityTextView;
    @BindView(R.id.y_axis_angularVelocity_textView) TextView yAxisAngularVelocityTextView;
    @BindView(R.id.z_axis_angularVelocity_textView) TextView zAxisAngularVelocityTextView;

    private final String LOG_TAG = MultiSubscribeActivity.class.getSimpleName();
    private final String LINEAR_ACCELERATION_PATH = "Meas/Acc/";
    private final String MAGNETIC_FIELD_PATH = "Meas/Magn/";
    private final String ANGULAR_VELOCITY_PATH = "Meas/Gyro/";
    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";
    private MdsSubscription mdsSubscriptionLinearAcc;
    private MdsSubscription mdsSubscriptionMagneticField;
    private MdsSubscription mdsSubscriptionAngularVelocity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_multi_subscribe);
        ButterKnife.bind(this);

        connectedDeviceTextView.setText(MovesenseConnectedDevices.getConnectedDevice(0).getMacAddress());

        BleManager.INSTANCE.addBleConnectionMonitorListener(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        BleManager.INSTANCE.removeBleConnectionMonitorListener(this);
    }

    @OnCheckedChanged(R.id.switchSubscriptionLinearAcc)
    public void onCheckedChangedLinear(CompoundButton buttonView, boolean isChecked) {
        if (isChecked) {
            Log.d(LOG_TAG, "+++ Subscribe LinearAcc");
            mdsSubscriptionLinearAcc = Mds.builder().build(this).subscribe(URI_EVENTLISTENER,
                    FormatHelper.formatContractToJson(MovesenseConnectedDevices.getConnectedDevice(0)
                            .getSerial(), LINEAR_ACCELERATION_PATH + "13"), new MdsNotificationListener() {
                        @Override
                        public void onNotification(String data) {
                            Log.d(LOG_TAG, "onSuccess(): " + data);

                            LinearAcceleration linearAccelerationData = new Gson().fromJson(
                                    data, LinearAcceleration.class);

                            if (linearAccelerationData != null) {

                                LinearAcceleration.Array arrayData = linearAccelerationData.body.array[0];

                                xAxisLinearAccTextView.setText(String.format(Locale.getDefault(),
                                        "x: %.6f", arrayData.x));
                                yAxisLinearAccTextView.setText(String.format(Locale.getDefault(),
                                        "y: %.6f", arrayData.y));
                                zAxisLinearAccTextView.setText(String.format(Locale.getDefault(),
                                        "z: %.6f", arrayData.z));

                            }
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError(): ", error);
                        }
                    });
        } else {
            Log.d(LOG_TAG, "--- Unsubscribe LinearAcc");
            mdsSubscriptionLinearAcc.unsubscribe();
        }
    }


    @OnCheckedChanged(R.id.switchSubscriptionMagneticField)
    public void onCheckedChangedMagnetic(CompoundButton buttonView, boolean isChecked) {
        if (isChecked) {
            Log.d(LOG_TAG, "+++ Subscribe MagneticField");
            mdsSubscriptionMagneticField = Mds.builder().build(this).subscribe(URI_EVENTLISTENER,
                    FormatHelper.formatContractToJson(MovesenseConnectedDevices.getConnectedDevice(0)
                            .getSerial(), MAGNETIC_FIELD_PATH + "13"), new MdsNotificationListener() {
                        @Override
                        public void onNotification(String data) {
                            Log.d(LOG_TAG, "onSuccess(): " + data);

                            MagneticField magneticField = new Gson().fromJson(
                                    data, MagneticField.class);

                            if (magneticField != null) {

                                MagneticField.Array arrayData = magneticField.body.array[0];

                                xAxisMagneticFieldTextView.setText(String.format(Locale.getDefault(),
                                        "x: %.6f", arrayData.x));
                                yAxisMagneticFieldTextView.setText(String.format(Locale.getDefault(),
                                        "y: %.6f", arrayData.y));
                                zAxisMagneticFieldTextView.setText(String.format(Locale.getDefault(),
                                        "z: %.6f", arrayData.z));

                            }
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError(): ", error);
                        }
                    });
        } else {
            Log.d(LOG_TAG, "--- Unsubscribe MagneticField");
            mdsSubscriptionMagneticField.unsubscribe();
        }
    }

    @OnCheckedChanged(R.id.switchSubscriptionAngularVelocity)
    public void onCheckedChangedAngularVielocity(CompoundButton buttonView, boolean isChecked) {
        if (isChecked) {
            Log.d(LOG_TAG, "+++ Subscribe AngularVelocity");
            mdsSubscriptionAngularVelocity = Mds.builder().build(this).subscribe(URI_EVENTLISTENER,
                    FormatHelper.formatContractToJson(MovesenseConnectedDevices.getConnectedDevice(0)
                            .getSerial(), ANGULAR_VELOCITY_PATH + "13"), new MdsNotificationListener() {
                        @Override
                        public void onNotification(String data) {
                            Log.d(LOG_TAG, "onSuccess(): " + data);

                            AngularVelocity angularVelocity = new Gson().fromJson(
                                    data, AngularVelocity.class);

                            if (angularVelocity != null) {

                                AngularVelocity.Array arrayData = angularVelocity.body.array[0];

                                xAxisAngularVelocityTextView.setText(String.format(Locale.getDefault(),
                                        "x: %.6f", arrayData.x));
                                yAxisAngularVelocityTextView.setText(String.format(Locale.getDefault(),
                                        "y: %.6f", arrayData.y));
                                zAxisAngularVelocityTextView.setText(String.format(Locale.getDefault(),
                                        "z: %.6f", arrayData.z));

                            }
                        }

                        @Override
                        public void onError(MdsException error) {
                            Log.e(LOG_TAG, "onError(): ", error);
                        }
                    });
        } else {
            Log.d(LOG_TAG, "--- Unsubscribe AngularVelocity");
            mdsSubscriptionAngularVelocity.unsubscribe();
        }
    }

    @Override
    public void onDisconnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onDisconnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ConnectionLostDialog.INSTANCE.showDialog(MultiSubscribeActivity.this);
            }
        });
    }

    @Override
    public void onConnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onConnect: " + rxBleDevice.getName() + " " + rxBleDevice.getMacAddress());
        ConnectionLostDialog.INSTANCE.dismissDialog();
    }
}
