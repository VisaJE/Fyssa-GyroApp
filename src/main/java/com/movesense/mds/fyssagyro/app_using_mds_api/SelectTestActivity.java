package com.movesense.mds.fyssagyro.app_using_mds_api;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;

import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.ConnectionLostDialog;
import com.movesense.mds.fyssagyro.MainActivity;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.ThrowableToastingAction;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.movesense.mds.fyssagyro.fyssa_app.FyssaMainActivity;
import com.movesense.mds.fyssagyro.model.MdsConnectedDevice;

import butterknife.ButterKnife;

import rx.android.schedulers.AndroidSchedulers;
import rx.functions.Action1;
import rx.subscriptions.CompositeSubscription;

public class SelectTestActivity extends AppCompatActivity {

    private AlertDialog alertDialog;
    private CompositeSubscription subscriptions;
    private boolean closeApp = false;
    private boolean disconnect = false;
    private ImageButton startButton;
    private ImageButton updateButton;

    private final String TAG = SelectTestActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_select_test);
        ButterKnife.bind(this);

        subscriptions = new CompositeSubscription();

        alertDialog = new AlertDialog.Builder(this)
                .setTitle(R.string.close_app)
                .setMessage(R.string.do_you_want_to_close_application)
                .setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        closeApp = true;
                        BleManager.INSTANCE.disconnect(MovesenseConnectedDevices.getConnectedRxDevice(0));
                    }
                })
                .setNegativeButton(R.string.no, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        alertDialog.dismiss();
                    }
                })
                .create();

        updateButton = (ImageButton) findViewById(R.id.update_button);
        startButton = (ImageButton) findViewById(R.id.start_button);

        updateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("ONCLICK", "Update activity");
                startActivity(new Intent(SelectTestActivity.this, FyssaSensorUpdateActivity.class)
                        .addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK));
            }
        });

        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("ONCLICK", "Start the app");
                startActivity(new Intent(SelectTestActivity.this, FyssaMainActivity.class)
                        .addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK));
            }
        });

        subscriptions.add(MdsRx.Instance.connectedDeviceObservable()
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Action1<MdsConnectedDevice>() {
                    @Override
                    public void call(MdsConnectedDevice mdsConnectedDevice) {
                        // Stop refreshing
                        if (mdsConnectedDevice.getConnection() == null) {
                            Log.e(TAG, "call: Rx Disconnect");
                            if (closeApp) {
                                if (Build.VERSION.SDK_INT >= 21) {
                                    finishAndRemoveTask();
                                } else {
                                    finish();
                                }
                            } else if (disconnect) {
                                startActivity(new Intent(SelectTestActivity.this, MainActivity.class)
                                        .addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK));
                            } else {
                                ConnectionLostDialog.INSTANCE.showDialog(SelectTestActivity.this);
                            }
                        } else {
                            ConnectionLostDialog.INSTANCE.dismissDialog();
                            Log.e(TAG, "call: Rx Connect");
                        }
                    }
                }, new ThrowableToastingAction(this)));


        //startActivity(new Intent(SelectTestActivity.this, ClassDataManagerActivity.class));
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(final MenuItem item) {
        switch (item.getItemId()) {
            case R.id.dfu_mode:
                startActivity(new Intent(SelectTestActivity.this, DfuActivity.class));
                return true;

            case R.id.update:
                startActivity(new Intent(SelectTestActivity.this, FyssaSensorUpdateActivity.class));
                return true;

            case R.id.disconnect:
                BleManager.INSTANCE.disconnect(MovesenseConnectedDevices.getConnectedRxDevice(0));
                disconnect = true;
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onBackPressed() {
        alertDialog.show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        subscriptions.unsubscribe();
    }
}

