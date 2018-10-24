package com.movesense.mds.fyssagyro.fyssa_app;


import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsNotificationListener;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.MdsSubscription;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.FyssaSensorUpdateActivity;
import com.movesense.mds.fyssagyro.app_using_mds_api.SelectTestActivity;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.DebugResponse;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.FyssaGyroGetData;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.FyssaPositionData;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.InfoAppResponse;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.movesense.mds.fyssagyro.tool.MemoryTools;

import java.util.Queue;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;
import butterknife.OnClick;
import rx.subscriptions.CompositeSubscription;

import static java.lang.Thread.sleep;


public class FyssaImuMainActivity extends AppCompatActivity {

    @BindView(R.id.fyssa_conn_infoTV) TextView connectionInfoTv;
    @BindView(R.id.get_heading_button) Button getButton;
    @BindView(R.id.subscription_switch) Switch subSwitch;
    @BindView(R.id.plot_button) Button plotButton;


    @BindView(R.id.nimi_tv) TextView nimiTv;
    @BindView(R.id.position_tv) TextView posView;
    @BindView(R.id.sample_rate_tv) EditText setSampleRate;
    @BindView(R.id.acc_treshold_tv) EditText setAccTreshold;
    @BindView(R.id.filter_switch) Switch filterSwitch;


    private final String TAG = FyssaImuMainActivity.class.getSimpleName();

    private CompositeSubscription subscriptions;
    private FyssaApp app;

    private final String GYRO_PATH_GET = "/Fyssa/Gyro";
    private final String IMU_PATH_GET = "/Fyssa/Imu";
    private final String INFO_PATH_GET = "/Meas/Acc/Info";
    private static final String GYRO_CONFIG = "/Fyssa/Gyro/FyssaGyroConfig";
    private static final String IMU_CONFIG = "/Fyssa/Imu/FyssaAccConfig";

    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";

    private MdsSubscription mdsSubscription;
    private MdsSubscription mImuSubscription;




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fyssa_imu_main);
        ButterKnife.bind(this);


        app = (FyssaApp) getApplication();

        if (getSupportActionBar() != null) {
            getSupportActionBar().setTitle("Fyssasensori");
        }

        if (app.getMemoryTools().getName().equals(MemoryTools.DEFAULT_STRING)) {
            startInfoActivity();
            finish();
        } else {
            nimiTv.setText("Heiluttelija: " + app.getMemoryTools().getName());
        }
        filterSwitch.setChecked(true);
        subscriptions = new CompositeSubscription();
    }

    private void checkSensorSoftware() {
        Log.d(TAG, "Checking software");
        Mds.builder().build(this).get(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + "/Info/App",
                null, new MdsResponseListener() {

                    @Override
                    public void onSuccess(String s) {
                        Log.d(TAG, "/Info/App onSuccess: " + s);
                        InfoAppResponse infoAppResponse = new Gson().fromJson(s, InfoAppResponse.class);
                        Log.d(TAG, "Company: " + infoAppResponse.getContent().getCompany());
                        if (infoAppResponse.getContent() != null) {
                            Log.d(TAG, "Name: " + infoAppResponse.getContent().getName());
                            Log.d(TAG, "Version: " + infoAppResponse.getContent().getVersion());
                            Log.d(TAG, "Company: " + infoAppResponse.getContent().getCompany());
                        }
                        if (!infoAppResponse.getContent().getVersion().equals(FyssaApp.deviceVersion)) {
                            AlertDialog.Builder builder = new AlertDialog.Builder(FyssaImuMainActivity.this);
                            builder.setMessage("Update?").setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    switch (which) {
                                        case DialogInterface.BUTTON_POSITIVE:
                                            updateSensorSoftware();
                                            break;
                                    }
                                }
                            }).show();
                        }
                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Info onError: ", e);
                        if (e.toString().contains("404")) {
                            //updateSensorSoftware();
                        }
                    }
                });
    }

    private void removeAndDisconnectFromDevice(){
        if(MovesenseConnectedDevices.getConnectedDevices().size() > 0) {
            BleManager.INSTANCE.disconnect(MovesenseConnectedDevices.getConnectedRxDevice(0));
            BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable = false;
            MovesenseConnectedDevices.removeRxConnectedDevice(MovesenseConnectedDevices.getConnectedRxDevice(0));
        }
    }

    private void updateSensorSoftware() {
        //removeAndDisconnectFromDevice();
        startActivity(new Intent(FyssaImuMainActivity.this, FyssaSensorUpdateActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }

    @Override
    protected void onResume() {
        super.onResume();

        try {
            connectionInfoTv.setText("Serial: " + MovesenseConnectedDevices.getConnectedDevice(0).getSerial());
        } catch (Exception e) {
            startScanActivity();
            return;
        }

        checkSensorSoftware();
    }

    @OnClick({R.id.get_info_button, R.id.start_service_button, R.id.stop_service_button, R.id.subscription_switch, R.id.get_heading_button, R.id.apply_config_button, R.id.plot_button, R.id.path_button})
    public void onViewClicked(View view) {
        switch(view.getId()) {
            case R.id.get_info_button:
                getInfo();
                break;
            case R.id.start_service_button:
                subscribeDebug();
                break;
            case R.id.stop_service_button:
                unsubscribeDebug();
                break;
            case R.id.get_heading_button:
                resetImu();
                break;
            case R.id.apply_config_button:
                try {
                    int sr = Integer.parseInt(setSampleRate.getText().toString());
                    float ma = Float.parseFloat(setAccTreshold.getText().toString());
                    Log.d(TAG, "Setting configuration:" + sr + ", " + ma);
                    configureImu(sr, ma, filterSwitch.isChecked());
                } catch (Exception e) {}
                break;
            case R.id.plot_button:
                plotButton.setEnabled(false);
                unSubscribeImu();

                Projector p = new Projector(app.trajectory);
                app.plottable = p.getProjection();
                plotButton.setEnabled(true);
                if (app.plottable.size() > 0) startActivity(new Intent(FyssaImuMainActivity.this, SimpleXYPlotActivity.class)
                        .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK));
                else toast("No plottable data.");
                break;
            case  R.id.path_button:
                getPath();
                break;
        }
    }
    @OnCheckedChanged({R.id.subscription_switch})
    public void onCheckedChanged(boolean isChecked) {
        if (isChecked) {
            subscribePosition();
        }
        else unSubscribeImu();
    }

    private void getPath() {
        if (subSwitch.isChecked()) subSwitch.toggle();
        subSwitch.setEnabled(false);
        app.trajectory.clear();
        mImuSubscription = Mds.builder().build(this).subscribe(URI_EVENTLISTENER, "{\"Uri\": \"" +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + IMU_PATH_GET + "\"}",
                new MdsNotificationListener() {
                    @Override
                    public void onNotification(String s){
                        Log.d(TAG, "A datapoint" + app.trajectory.size());
                        try {
                            FyssaPositionData data = new Gson().fromJson(s, FyssaPositionData.class);
                            posView.setText("Getting path:\n" + app.trajectory.size() + " / 30.");
                            if (app.trajectory.size() < 30) app.trajectory.add(new Vector3d(data.getContent().getX(), data.getContent().getY(), data.getContent().getZ()) );
                            else {
                                mImuSubscription.unsubscribe();
                                plotButton.callOnClick();
                            }
                        } catch (Exception e){ Log.e(TAG, "Wrong value!", e);}

                    }
                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Error on subscribing:", e);
                    }
                });


    }

    private void getHeading() {
        if (!subSwitch.isChecked()) subSwitch.toggle();
        Mds.builder().build(this).get(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + GYRO_PATH_GET,
                null, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        Log.d(TAG, "Found a value from: " + MdsRx.SCHEME_PREFIX +
                                MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + GYRO_PATH_GET);
                        Log.d(TAG, s);
                        FyssaGyroGetData data = new Gson().fromJson(s, FyssaGyroGetData.class);

                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "onError: ", e);
                    }
                });
    }

    private void resetImu() {
        if (!subSwitch.isChecked()) subSwitch.toggle();
        Mds.builder().build(this).get(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + IMU_PATH_GET,
                null, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        Log.d(TAG, s);

                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "onError: ", e);
                    }
                });
    }

    private void getInfo() {
        Mds.builder().build(this).get(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + INFO_PATH_GET,
                null, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        Log.d(TAG, "Found a value from: " + MdsRx.SCHEME_PREFIX +
                                MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + INFO_PATH_GET);
                        toast(s);
                        Log.d(TAG, s);
                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "onError: ", e);
                    }
                });
    }

    public void toast(String text) {
        Toast.makeText(this, text, Toast.LENGTH_SHORT).show();
    }

    private void configureImu(int sampleRate, float minAngle, boolean filter) {
        // Access the config
        String configUri = MdsRx.SCHEME_PREFIX +
                MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + IMU_CONFIG;

                // Create the config object
        String jsonConfig = "{\"fyssaAccConfig\":{\"rate\":" + sampleRate + ",\"threshold\":" + minAngle + ",\"filter\":" + Boolean.toString(filter) + "}}";

        Log.d(TAG, "Config request: " + jsonConfig);
        Mds.builder().build(this).put(configUri, jsonConfig, new MdsResponseListener() {
            @Override
            public void onSuccess(String data) {
                Log.i(TAG, "POST config succesful: " + data);
            }

            @Override
            public void onError(MdsException e) {
                Log.e(TAG, "Put returned error: " + e);
            }
        });
    }


    private void subscribeDebug() {
        Mds.builder().build(this).get(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + "/System/Debug/Config",
                null, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        Log.d(TAG, "Sensor debug config: " + s);
                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Error on debug:", e);
                    }
                });
        mdsSubscription = Mds.builder().build(this).subscribe(URI_EVENTLISTENER, "{\"Uri\": \"" +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + "/System/Debug/4\"}",
                        new MdsNotificationListener() {
                    @Override
                    public void onNotification(String s) {
                        DebugResponse resp = new Gson().fromJson(s, DebugResponse.class);
                        Log.d(TAG, resp.getMessage());
                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Error on subscribing debug:", e);
                    }
                });
    }


    private void unsubscribeDebug() {
        if (mdsSubscription != null) mdsSubscription.unsubscribe();

        }


    private void subscribePosition() {
        Log.d(TAG, "Subscribing.");
        mImuSubscription = Mds.builder().build(this).subscribe(URI_EVENTLISTENER, "{\"Uri\": \"" +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + IMU_PATH_GET + "\"}",
                new MdsNotificationListener() {
                    @Override
                    public void onNotification(String s){
                        try {
                            FyssaPositionData data = new Gson().fromJson(s, FyssaPositionData.class);
                            showCoordinates(data);
                            while (app.trajectory.size() > 99) app.trajectory.pop();
                            app.trajectory.add(new Vector3d(data.getContent().getX(), data.getContent().getY(), data.getContent().getZ()) );
                        } catch (Exception e){ Log.e(TAG, "Wrong value!", e);}

                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Error on subscribing:", e);
                    }
                });
    }

    private void unSubscribeImu() {
        if (mImuSubscription != null) mImuSubscription.unsubscribe();
    }


    void showCoordinates(FyssaPositionData data) {
        FyssaPositionData.Body dataC = data.getContent();
        String text1 = "Coords:\nx: " + dataC.getX() + "\ny: " + dataC.getY() + "\nz: " + dataC.getZ();
        posView.setText(text1);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.fyssa_main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.remove_device) {
            subscriptions.clear();
            app.getMemoryTools().saveSerial(app.getMemoryTools().DEFAULT_STRING);
            startScanActivity();
            return true;
        }
        return false;
    }

    @Override
    protected void onDestroy() {
        unsubscribeDebug();
        unSubscribeImu();
        super.onDestroy();

        subscriptions.clear();
        subscriptions.unsubscribe();
    }

    @Override
    public void onBackPressed() {
        unsubscribeDebug();
        unSubscribeImu();
        startActivity(new Intent(FyssaImuMainActivity.this, SelectTestActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }

    private void startScanActivity() {
        startActivity(new Intent(FyssaImuMainActivity.this, SelectTestActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }

    private void startInfoActivity() {
        startActivity(new Intent(FyssaImuMainActivity.this, FyssaInfoActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }
}
