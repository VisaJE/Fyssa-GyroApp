package com.movesense.mds.fyssagyro.app_using_mds_api.logs;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.util.Log;

import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MovesenseConnectedDevices;

import java.io.File;
import java.io.IOException;
import java.util.Calendar;
import java.util.TimeZone;

/**
 * Helper class for managing logs and saving to sdcard
 */
public class LogsManager {

    private final Context context;
    private Process process;

    public LogsManager(Context context) {
        this.context = context;
    }

    private final String LOG_TAG = LogsManager.class.getSimpleName();
    public static final int REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION = 99;
    public static final int READ_LOGS_PERMISSION = 100;

    public void saveLogsToSdCard(String logTag) {
        Log.d(LOG_TAG, "saveLogsToSdCard tag: " + logTag);
        if (isExternalStorageWritable()) {
            try {
                File externalDirectory = Environment.getExternalStorageDirectory();
                File appDirectory = new File(externalDirectory, "Movesense");
                File logFile = new File(appDirectory, createLogTitle(logTag) + ".txt");

                // create app folder
                if (!appDirectory.exists()) {
                    boolean status = appDirectory.mkdirs();
                    Log.e(LOG_TAG, "appDirectory created: " + status);
                }

                // create log file
                if (!logFile.exists()) {
                    boolean status = logFile.createNewFile();
                    Log.e(LOG_TAG, "logFile.createNewFile() created: " + status);
                }

                // Filter logs by logTag and save to file
                process = Runtime.getRuntime().exec("logcat -df " + logFile + " -s " + logTag);

            } catch (IOException e) {
                Log.e(LOG_TAG, "Couldn't create Process logcat -f ", e);
            }
        } else {
            Log.e(LOG_TAG, "No permission for writing logs");
        }
    }

    public void clearAdbLogcat() {
        // Clear Adb logcat
        try {
            Runtime.getRuntime().exec("logcat -c");
        } catch (IOException e) {
            Log.e(LOG_TAG, "Couldn't create Process logcat -c");
            e.printStackTrace();
        }
    }

    /* Checks if external storage is available for read and write */
    private boolean isExternalStorageWritable() {
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state)) {
            return true;
        }
        return false;
    }

    public boolean checkRuntimeWriteExternalStoragePermission(Context context, final Activity activity) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {

            if (ActivityCompat.shouldShowRequestPermissionRationale(activity,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE)) {

                new AlertDialog.Builder(activity)
                        .setTitle(R.string.write_external_storage_permission_title)
                        .setMessage(R.string.write_external_storage_permission_text)
                        .setPositiveButton(R.string.btn_ok, new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                //Prompt the user once explanation has been shown
                                requestForWriteExternalStoragePermission(activity);
                            }
                        })
                        .create()
                        .show();

            } else {
                requestForWriteExternalStoragePermission(activity);
            }
            Log.e(LOG_TAG, "checkRuntimeWriteExternalStoragePermission() FALSE");
            return false;
        } else {
            Log.e(LOG_TAG, "checkRuntimeWriteExternalStoragePermission() TRUE");
            return true;
        }
    }

    private void requestForWriteExternalStoragePermission(Activity activity) {
        ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION);
    }

    private String createLogTitle(String tag) {
        // timestamp (ISO 8601) + device serial + data type,
        StringBuilder sb = new StringBuilder();

        // Get Current Timestamp ISO 8601
        String currentISO8601Timestamp = String.format("%tFT%<tTZ.%<tL",
                Calendar.getInstance(TimeZone.getTimeZone("Z")));

        // Get connected device serial
        String deviceName = MovesenseConnectedDevices.getConnectedDevice(0).getSerial();

        sb.append(currentISO8601Timestamp).append("_").
                append(deviceName).append("_")
                .append(tag);

        Log.e(LOG_TAG, "File name: " + sb.toString());
        return sb.toString();
    }
}
