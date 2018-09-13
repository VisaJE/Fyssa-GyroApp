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
import com.movesense.mds.fyssagyro.app_using_mds_api.FyssaSensorUpdateActivity;
import com.movesense.mds.fyssagyro.app_using_mds_api.SelectTestActivity;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.DebugResponse;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.FyssaGyroData;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.FyssaGyroGetData;

import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.InfoAppResponse;
import com.movesense.mds.fyssagyro.tool.MemoryTools;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;
import butterknife.OnClick;
import rx.subscriptions.CompositeSubscription;

public class FyssaGyroMainActivity extends AppCompatActivity {

    @BindView(R.id.fyssa_conn_infoTV) TextView connectionInfoTv;
    @BindView(R.id.get_heading_button) Button getButton;
    @BindView(R.id.subscription_switch) Switch subSwitch;

    @BindView(R.id.nimi_tv) TextView nimiTv;
    @BindView(R.id.top_pointer_tv) TextView topView;
    @BindView(R.id.front_pointer_tv) TextView frontView;
    @BindView(R.id.sample_rate_tv) EditText setSampleRate;
    @BindView(R.id.angle_treshold_tv) EditText setAngleTreshold;

    private final String TAG = FyssaGyroMainActivity.class.getSimpleName();

    private CompositeSubscription subscriptions;
    private FyssaApp app;

    private final String GYRO_PATH_GET = "/Fyssa/Gyro";
    private final String INFO_PATH_GET = "/Meas/Gyro/Info";
    private static final String GYRO_CONFIG = "/Fyssa/Gyro/FyssaGyroConfig";

    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";

    private MdsSubscription mdsSubscription;
    private MdsSubscription mGyroSubscription;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fyssa_gyro_main);
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
                            AlertDialog.Builder builder = new AlertDialog.Builder(FyssaGyroMainActivity.this);
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
        startActivity(new Intent(FyssaGyroMainActivity.this, FyssaSensorUpdateActivity.class)
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

    @OnClick({R.id.get_info_button, R.id.start_service_button, R.id.stop_service_button, R.id.subscription_switch, R.id.get_heading_button, R.id.apply_config_button})
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
                getHeading();
                break;
            case R.id.apply_config_button:
                try {
                    int sr = Integer.parseInt(setSampleRate.getText().toString());
                    float ma = Float.parseFloat(setAngleTreshold.getText().toString());
                    Log.d(TAG, "Setting configuration:" + sr + ", " + ma);
                    configureGyro(sr, ma);
                } catch (Exception e) {}

        }
    }
    @OnCheckedChanged({R.id.subscription_switch})
    public void onCheckedChanged(boolean isChecked) {
        if (isChecked) {
            subscribeRotation();
        }
        else unSubscribeRotation();
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
                        showCoordinates(data);

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

    private void configureGyro(int sampleRate, float minAngle) {
        // Access the config
        String configUri = MdsRx.SCHEME_PREFIX +
                MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + GYRO_CONFIG;

                // Create the config object
        String jsonConfig = "{\"fyssaGyroConfig\":{\"rate\":" + sampleRate + ",\"threshold\":" + minAngle + "}}";

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


    private void subscribeRotation() {
        Log.d(TAG, "Subscribing.");
        mGyroSubscription = Mds.builder().build(this).subscribe(URI_EVENTLISTENER, "{\"Uri\": \"" +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + GYRO_PATH_GET + "\"}",
                new MdsNotificationListener() {
                    @Override
                    public void onNotification(String s){
                        try {
                            FyssaGyroData data = new Gson().fromJson(s, FyssaGyroData.class);
                            showCoordinates(data);
                        } catch (Exception e){ Log.e(TAG, "Wrong value!", e);}

                    }

                    @Override
                    public void onError(MdsException e) {
                        Log.e(TAG, "Error on subscribing:", e);
                    }
                });
    }

    private void unSubscribeRotation() {
        if (mGyroSubscription != null) mGyroSubscription.unsubscribe();
    }

    void showCoordinates(FyssaGyroGetData data) {
        FyssaGyroGetData.Content dataC = data.getContent();
        String text1 = "Front vector\nx: " + dataC.getFrontX() + "\ny: " + dataC.getFrontY() + "\nz: " + dataC.getFrontZ();
        frontView.setText(text1);
        String text2 = "Side vector\nx: " + dataC.getTopX() + "\ny: " + dataC.getTopY() + "\nz: " + dataC.getTopZ();
        topView.setText(text2);
    }
    void showCoordinates(FyssaGyroData data) {
        FyssaGyroData.Body dataC = data.getContent();
        String text1 = "Front vector\nx: " + dataC.getFrontX() + "\ny: " + dataC.getFrontY() + "\nz: " + dataC.getFrontZ();
        frontView.setText(text1);
        String text2 = "Side vector\nx: " + dataC.getTopX() + "\ny: " + dataC.getTopY() + "\nz: " + dataC.getTopZ();
        topView.setText(text2);
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
        unSubscribeRotation();
        super.onDestroy();

        subscriptions.clear();
        subscriptions.unsubscribe();
    }

    @Override
    public void onBackPressed() {
        unsubscribeDebug();
        unSubscribeRotation();
        startActivity(new Intent(FyssaGyroMainActivity.this, SelectTestActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }

    private void startScanActivity() {
        startActivity(new Intent(FyssaGyroMainActivity.this, SelectTestActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }

    private void startInfoActivity() {
        startActivity(new Intent(FyssaGyroMainActivity.this, FyssaInfoActivity.class)
                .addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK));
    }
}
