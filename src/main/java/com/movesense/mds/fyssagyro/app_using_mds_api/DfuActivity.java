package com.movesense.mds.fyssagyro.app_using_mds_api;

import android.app.ActivityManager;
import android.app.LoaderManager;
import android.app.NotificationManager;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.content.Context;
import android.content.CursorLoader;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.Loader;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.fyssagyro.BleManager;
import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.ScannerFragment;
import com.movesense.mds.fyssagyro.app_using_mds_api.dfu.DfuService;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;
import com.polidea.rxandroidble.RxBleDevice;

import java.io.File;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import no.nordicsemi.android.dfu.DfuProgressListener;
import no.nordicsemi.android.dfu.DfuServiceInitiator;
import no.nordicsemi.android.dfu.DfuServiceListenerHelper;

public class DfuActivity extends AppCompatActivity implements ScannerFragment.DeviceSelectionListener, LoaderManager.LoaderCallbacks<Cursor>, BleManager.IBleConnectionMonitor {

    public static final int SELECT_FILE_REQUEST_CODE = 1000;

    @BindView(R.id.dfu_application_title_tv) TextView dfuApplicationTitleTv;
    @BindView(R.id.dfu_file_name_tv) TextView dfuFileNameTv;
    @BindView(R.id.dfu_file_type_tv) TextView dfuFileTypeTv;
    @BindView(R.id.dfu_file_size_tv) TextView dfuFileSizeTv;
    @BindView(R.id.dfu_file_status_tv) TextView dfuFileStatusTv;
    @BindView(R.id.dfu_file_name_value_tv) TextView dfuFileNameValueTv;
    @BindView(R.id.dfu_file_type_value_tv) TextView dfuFileTypeValueTv;
    @BindView(R.id.dfu_file_size_value_tv) TextView dfuFileSizeValueTv;
    @BindView(R.id.dfu_file_status_value_tv) TextView dfuFileStatusValueTv;
    @BindView(R.id.sw_version) TextView swVersion;
    @BindView(R.id.dfu_select_file_btn) Button dfuSelectFileBtn;
    @BindView(R.id.dfu_device_firmware_update_tv) TextView dfuDeviceFirmwareUpdateTv;
    @BindView(R.id.dfu_upload_btn) Button dfuUploadBtn;
    @BindView(R.id.dfu_select_device_btn) Button dfuSelectDeviceBtn;
    @BindView(R.id.parentLayout) ConstraintLayout parentLayout;

    private static final String EXTRA_URI = "uri";

    private static final int PERMISSION_REQ = 25;
    private static final int ENABLE_BT_REQ = 0;
    private static final int SELECT_FILE_REQ = 1;
    private static final int SELECT_INIT_FILE_REQ = 2;

    private final String LOG_TAG = DfuActivity.class.getSimpleName();
    @BindView(R.id.dfu_uploading_tv) TextView dfuUploadingTv;
    @BindView(R.id.dfu_uploading_percent_tv) TextView dfuUploadingPercentTv;
    @BindView(R.id.dfu_status_section_tv) TextView dfuStatusSectionTv;
    @BindView(R.id.dfu_status_tv) TextView dfuStatusTv;
    @BindView(R.id.dfu_enable_dfu_btn) Button dfuEnableDfuBtn;

    private static final String DATA_DEVICE = "device";
    private static final String DATA_FILE_TYPE = "file_type";
    private static final String DATA_FILE_TYPE_TMP = "file_type_tmp";
    private static final String DATA_FILE_PATH = "file_path";
    private static final String DATA_FILE_STREAM = "file_stream";
    private static final String DATA_INIT_FILE_PATH = "init_file_path";
    private static final String DATA_INIT_FILE_STREAM = "init_file_stream";
    private static final String DATA_STATUS = "status";
    private static final String DATA_DFU_COMPLETED = "dfu_completed";
    private static final String DATA_DFU_ERROR = "dfu_error";

    private ScannerFragment scannerFragment;
    private int mFileType;
    private int mFileTypeTmp; // This value is being used when user is selecting a file not to overwrite the old value (in case he/she will cancel selecting file)
    private String mFilePath;
    private Uri mFileStreamUri;
    private boolean mStatusOk;
    private RxBleDevice selectedDevice;
    private boolean mDfuCompleted;
    private boolean mResumed;
    private String mDfuError;
    private boolean mPaused;
    private String mFilename;
    private long mFileSize;
    private boolean mIsDeviceReconnected = false;
    private boolean isDfuEnable = false;

    private BluetoothAdapter bluetoothAdapter;
    private File mFile;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dfu);
        ButterKnife.bind(this);
        Log.e(LOG_TAG, "onCreate");

        isBLESupported();
        if (!isBLEEnabled()) {
            showBLEDialog();
        }

        if (savedInstanceState != null) {
            mFileType = savedInstanceState.getInt(DATA_FILE_TYPE);
            mFileTypeTmp = savedInstanceState.getInt(DATA_FILE_TYPE_TMP);
            mFilePath = savedInstanceState.getString(DATA_FILE_PATH);
            mFileStreamUri = savedInstanceState.getParcelable(DATA_FILE_STREAM);
            selectedDevice = savedInstanceState.getParcelable(DATA_DEVICE);
            mStatusOk = mStatusOk || savedInstanceState.getBoolean(DATA_STATUS);
            dfuUploadBtn.setEnabled(selectedDevice != null && mStatusOk);
            mDfuCompleted = savedInstanceState.getBoolean(DATA_DFU_COMPLETED);
            mDfuError = savedInstanceState.getString(DATA_DFU_ERROR);
        }
        // Run Dfu Mode on the device
        enableDfu();

        // Ask For Bluetooth
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!bluetoothAdapter.isEnabled()) {
            // Bluetooth is not enable so run
            bluetoothAdapter.enable();
        }

        DfuServiceListenerHelper.registerProgressListener(this, dfuProgressListener);

        BleManager.INSTANCE.addBleConnectionMonitorListener(this);

    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.e(LOG_TAG, "onResume");
        mResumed = true;

        if (mDfuCompleted)
            onTransferCompleted();
        if (mDfuError != null)
            showErrorMessage(mDfuError);
        if (mDfuCompleted || mDfuError != null) {
            // if this activity is still open and upload process was completed, cancel the notification
            final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            manager.cancel(DfuService.NOTIFICATION_ID);
            mDfuCompleted = false;
            mDfuError = null;
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        mResumed = false;
        mPaused = true;

        // save the data
        Log.e(LOG_TAG, "onPause");
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        Log.e(LOG_TAG, "onSaveInstanceState");
        outState.putInt(DATA_FILE_TYPE, mFileType);
        outState.putInt(DATA_FILE_TYPE_TMP, mFileTypeTmp);
        outState.putString(DATA_FILE_PATH, mFilePath);
        outState.putParcelable(DATA_FILE_STREAM, mFileStreamUri);
        outState.putParcelable(DATA_DEVICE, selectedDevice != null ? selectedDevice.getBluetoothDevice() : null);
        outState.putBoolean(DATA_STATUS, mStatusOk);
        outState.putBoolean(DATA_DFU_COMPLETED, mDfuCompleted);
        outState.putString(DATA_DFU_ERROR, mDfuError);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        DfuServiceListenerHelper.unregisterProgressListener(this, dfuProgressListener);
        Log.e(LOG_TAG, "onDestroy");
    }

    @OnClick({R.id.dfu_select_file_btn, R.id.dfu_upload_btn, R.id.dfu_select_device_btn, R.id.dfu_enable_dfu_btn})
    public void onViewClicked(View view) {
        switch (view.getId()) {
            case R.id.dfu_select_file_btn:
                // Open file chooser
                openFileChooser();
                break;
            case R.id.dfu_upload_btn:

                if (mFileSize <= 0) {
                    Toast.makeText(DfuActivity.this, "File corrupted", Toast.LENGTH_SHORT).show();
                    return;
                }

                dfuUploadingPercentTv.setVisibility(View.VISIBLE);
                dfuUploadingTv.setVisibility(View.VISIBLE);
                dfuEnableDfuBtn.setEnabled(false);
                dfuSelectFileBtn.setEnabled(false);
                dfuUploadBtn.setEnabled(false);
                dfuSelectDeviceBtn.setEnabled(false);

                Log.d(LOG_TAG, "Name: " + selectedDevice.getBluetoothDevice().getName());
                Log.d(LOG_TAG, "Address: " + selectedDevice.getBluetoothDevice().getAddress());

                DfuServiceInitiator serviceInitiator = new DfuServiceInitiator(selectedDevice.getBluetoothDevice().getAddress())
                        .setDeviceName(selectedDevice.getBluetoothDevice().getName())
                        .setKeepBond(false)
                        .setForceDfu(false)
                        .setPacketsReceiptNotificationsEnabled(Build.VERSION.SDK_INT < Build.VERSION_CODES.M)
                        .setPacketsReceiptNotificationsValue(DfuServiceInitiator.DEFAULT_PRN_VALUE)
                        .setUnsafeExperimentalButtonlessServiceInSecureDfuEnabled(true);

                serviceInitiator.setZip(mFileStreamUri, mFilePath);

                serviceInitiator.start(this, DfuService.class);
                break;
            case R.id.dfu_select_device_btn:
                if (!isBLEEnabled()) {
                    showBLEDialog();
                }

                showDeviceScanningDialog();
                break;

            case R.id.dfu_enable_dfu_btn:
                enableDfu();
                break;
        }
    }

    private void enableDfu() {
        Log.d(LOG_TAG, "enableDfu()");
        if (BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable && isDfuEnable) {
            Log.d(LOG_TAG, "enableDfu() BleManager.isReconnectToLastConnectedDeviceEnable");
            Toast.makeText(this, "Dfu Already Enabled", Toast.LENGTH_SHORT).show();
            return;
        }

        Mds.builder().build(this).put(MdsRx.SCHEME_PREFIX +
                        MovesenseConnectedDevices.getConnectedDevice(0).getSerial() + "/System/Mode",
                "{\"NewState\":12}", new MdsResponseListener() {
                    @Override
                    public void onSuccess(String data) {
                        Log.e(LOG_TAG, "onSuccess(): " + data);
                        isDfuEnable = true;
                        BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable = false;
                        dfuStatusTv.setText(getString(R.string.dfu_status) + " Enabled");
                    }

                    @Override
                    public void onError(MdsException error) {
                        Log.e(LOG_TAG, "onError(): ", error);
                        isDfuEnable = false;
                        dfuStatusTv.setText(getString(R.string.dfu_status) + " Error");
                    }
                });
    }

    private void openFileChooser() {
        final Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("application/zip");
        intent.addCategory(Intent.CATEGORY_OPENABLE);

        if (intent.resolveActivity(getPackageManager()) != null) {
            // file browser has been found on the device
            startActivityForResult(Intent.createChooser(intent, "Select File Browser"), SELECT_FILE_REQUEST_CODE);
        } else {
            // there is no any file browser app, let's try to download one
            new AlertDialog.Builder(this).setTitle("File Browser not found")
                    .setItems(new CharSequence[]{"Find File Browser in Google Play", "Cancel"},
                            new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    switch (which) {
                                        case 0:
                                            startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://search?q=file manager")));
                                            break;
                                        case 1:
                                            dialog.dismiss();
                                            break;
                                    }
                                }
                            }).show();
        }
    }

    private void showErrorMessage(final String message) {
        clearUI();
        Toast.makeText(this, "Upload failed: " + message, Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK) {
            if (requestCode == SELECT_FILE_REQUEST_CODE) {
                // clear previous data
                mFileType = mFileTypeTmp;
                mFilePath = null;
                mFileStreamUri = null;

                mPaused = false;

                // and read new one
                final Uri uri = data.getData();
            /*
             * The URI returned from application may be in 'file' or 'content' schema. 'File' schema allows us to create a File object and read details from if
			 * directly. Data from 'Content' schema must be read by Content Provider. To do that we are using a Loader.
			 */
                if (uri.getScheme().equals("file")) {
                    // the direct path to the file has been returned
                    final String path = uri.getPath();
                    mFile = new File(path);
                    mFilePath = path;

                    updateFileInfo(mFile.getName(), mFile.length(), mFileType);
                } else if (uri.getScheme().equals("content")) {
                    // an Uri has been returned
                    mFileStreamUri = uri;
                    // if application returned Uri for streaming, let's us it. Does it works?
                    // FIXME both Uris works with Google Drive app. Why both? What's the difference? How about other apps like DropBox?
                    final Bundle extras = data.getExtras();
                    if (extras != null && extras.containsKey(Intent.EXTRA_STREAM))
                        mFileStreamUri = extras.getParcelable(Intent.EXTRA_STREAM);

                    // file name and size must be obtained from Content Provider
                    final Bundle bundle = new Bundle();
                    bundle.putParcelable(EXTRA_URI, uri);
                    getLoaderManager().restartLoader(SELECT_FILE_REQ, bundle, this);
                }
            }
        }
    }

    private void updateFileInfo(String fileName, long fileSize, int fileType) {
        mFilename = fileName;
        mFileSize = fileSize;
        dfuFileNameValueTv.setText(fileName);
        dfuFileTypeValueTv.setText("Distribution packet (ZIP)");
        dfuFileSizeValueTv.setText(String.valueOf(fileSize) + " bytes");
        dfuFileStatusValueTv.setText("OK");
    }

    private boolean isDfuServiceRunning() {
        ActivityManager manager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
            if (DfuService.class.getName().equals(service.service.getClassName())) {
                Log.d(LOG_TAG, "isDfuServiceRunning() TRUE");
                return true;
            }
        }
        Log.d(LOG_TAG, "isDfuServiceRunning() FALSE");
        return false;
    }

    private boolean isBLEEnabled() {
        BluetoothManager manager = (BluetoothManager) getSystemService(BLUETOOTH_SERVICE);
        BluetoothAdapter adapter = manager.getAdapter();
        return adapter != null && adapter.isEnabled();
    }

    private void showDeviceScanningDialog() {
        scannerFragment = new ScannerFragment();
        scannerFragment.show(getSupportFragmentManager(), ScannerFragment.class.getName());
    }

    @Override
    public void onDeviceSelected(RxBleDevice device) {
        Log.d(LOG_TAG, "onDeviceSelected()");
        selectedDevice = device;
        swVersion.setText(selectedDevice.getName());
        scannerFragment.dismiss();
        dfuUploadBtn.setEnabled(true);
    }

    DfuProgressListener dfuProgressListener = new DfuProgressListener() {
        @Override
        public void onDeviceConnecting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceConnecting");
        }

        @Override
        public void onDeviceConnected(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceConnected");
        }

        @Override
        public void onDfuProcessStarting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuProcessStarting");
        }

        @Override
        public void onDfuProcessStarted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuProcessStarted");
        }

        @Override
        public void onEnablingDfuMode(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onEnablingDfuMode");
        }

        @Override
        public void onProgressChanged(String deviceAddress, int percent, float speed, float avgSpeed, int currentPart, int partsTotal) {
            Log.d(LOG_TAG, "DfuProgress onProgressChanged percent: " + percent);
            dfuUploadingPercentTv.setText(percent + "%");
        }

        @Override
        public void onFirmwareValidating(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onFirmwareValidating");
        }

        @Override
        public void onDeviceDisconnecting(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceDisconnecting");
        }

        @Override
        public void onDeviceDisconnected(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDeviceDisconnected");
        }

        @Override
        public void onDfuCompleted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuCompleted");
            dfuUploadingPercentTv.setText(R.string.dfu_status_completed);
            if (mResumed) {
                // let's wait a bit until we cancel the notification. When canceled immediately it will be recreated by service again.
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        onTransferCompleted();

                        // if this activity is still open and upload process was completed, cancel the notification
                        final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                        manager.cancel(DfuService.NOTIFICATION_ID);
                    }
                }, 200);
            } else {
                //  Save that the DFU process has finished
                mDfuCompleted = true;
            }
        }

        @Override
        public void onDfuAborted(String deviceAddress) {
            Log.d(LOG_TAG, "DfuProgress onDfuAborted");
            dfuUploadingPercentTv.setText(R.string.dfu_status_aborted);
            // let's wait a bit until we cancel the notification. When canceled immediately it will be recreated by service again.
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    onUploadCanceled();

                    // if this activity is still open and upload process was completed, cancel the notification
                    final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                    manager.cancel(DfuService.NOTIFICATION_ID);
                }
            }, 200);
        }

        @Override
        public void onError(String deviceAddress, int error, int errorType, String message) {
            Log.d(LOG_TAG, "DfuProgress onError");
            if (mResumed) {
                showErrorMessage(message);

                // We have to wait a bit before canceling notification. This is called before DfuService creates the last notification.
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        // if this activity is still open and upload process was completed, cancel the notification
                        final NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
                        manager.cancel(DfuService.NOTIFICATION_ID);
                    }
                }, 200);
            } else {
                mDfuError = message;
            }
        }
    };

    private void showBLEDialog() {
        final Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(enableIntent, ENABLE_BT_REQ);
    }

    private void isBLESupported() {
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, "no Ble", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    private void onTransferCompleted() {
        clearUI();
        dfuUploadingTv.setVisibility(View.VISIBLE);
        dfuUploadingTv.setText("Reconnecting to the device...");

        BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable = true;

        isDfuEnable = false;

        // Reconnect to last connected device
        MdsRx.Instance.reconnect(this);
    }

    public void onUploadCanceled() {
        clearUI();
        Toast.makeText(this, "Dfu Aborted", Toast.LENGTH_SHORT).show();
    }

    private void clearUI() {
        dfuUploadingPercentTv.setVisibility(View.INVISIBLE);
        dfuUploadingTv.setVisibility(View.INVISIBLE);
        dfuSelectDeviceBtn.setEnabled(true);
        dfuSelectFileBtn.setEnabled(true);
        dfuUploadBtn.setEnabled(false);
        dfuUploadBtn.setText("Upload");
        dfuFileNameValueTv.setText(null);
        dfuFileTypeValueTv.setText(null);
        dfuFileSizeValueTv.setText(null);
        dfuFileStatusValueTv.setText("No selected file");
        mFilePath = null;
        mFileStreamUri = null;
        mStatusOk = false;
    }

    @Override
    public Loader<Cursor> onCreateLoader(int id, Bundle args) {
        final Uri uri = args.getParcelable(EXTRA_URI);

        return new CursorLoader(this, uri, null, null, null, null);
    }

    @Override
    public void onLoadFinished(Loader<Cursor> loader, Cursor data) {
        if (data != null && data.moveToNext()) {
            /*
             * Here we have to check the column indexes by name as we have requested for all. The order may be different.
			 */
            final String fileName = data.getString(data.getColumnIndex(MediaStore.MediaColumns.DISPLAY_NAME)/* 0 DISPLAY_NAME */);
            final int fileSize = data.getInt(data.getColumnIndex(MediaStore.MediaColumns.SIZE) /* 1 SIZE */);
            String filePath = null;
            final int dataIndex = data.getColumnIndex(MediaStore.MediaColumns.DATA);
            if (dataIndex != -1)
                filePath = data.getString(dataIndex /* 2 DATA */);
            if (!TextUtils.isEmpty(filePath))
                mFilePath = filePath;

            updateFileInfo(fileName, fileSize, mFileType);
        } else {
            dfuFileNameValueTv.setText(null);
            dfuFileTypeValueTv.setText(null);
            dfuFileSizeValueTv.setText(null);
            mFilePath = null;
            mFileStreamUri = null;
            dfuFileStatusValueTv.setText("Error");
            mStatusOk = false;
        }
    }

    @Override
    public void onLoaderReset(Loader<Cursor> loader) {
        dfuFileNameValueTv.setText(null);
        dfuFileTypeValueTv.setText(null);
        dfuFileSizeValueTv.setText(null);
        dfuFileStatusValueTv.setText(null);
    }

    @Override
    public void onBackPressed() {
        if (BleManager.INSTANCE.isReconnectToLastConnectedDeviceEnable || !mIsDeviceReconnected) {
            new AlertDialog.Builder(this)
                    .setTitle("Dfu Mode")
                    .setMessage("DFU operations are running. Please wait until process will be finished.")
                    .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    }).show();
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public void onDisconnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onDisconnect: " + rxBleDevice.getMacAddress());

        mIsDeviceReconnected = false;
    }

    @Override
    public void onConnect(RxBleDevice rxBleDevice) {
        Log.e(LOG_TAG, "onConnect: " + rxBleDevice.getMacAddress());

        mIsDeviceReconnected = true;

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(DfuActivity.this, "Connected", Toast.LENGTH_SHORT).show();

                dfuUploadingTv.setText("Connected");

                dfuStatusTv.setText(getString(R.string.dfu_status) + " Disabled");
                dfuEnableDfuBtn.setEnabled(true);
            }
        });
    }
}
