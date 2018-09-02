package com.movesense.mds.fyssagyro.app_using_mds_api.dfu;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.movesense.mds.fyssagyro.app_using_mds_api.DfuActivity;
import com.movesense.mds.fyssagyro.app_using_mds_api.SelectTestActivity;

/**
 *
 */

public class NotificationActivity extends Activity {

    private final String TAG = NotificationActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.e(TAG, "onCreate()");

        // If this activity is the root activity of the task, the app is not running
        if (isTaskRoot()) {
            Log.e(TAG, "isTaskRoot()");
            // Start the app before finishing
            // Start the app before finishing
            final Intent parentIntent = new Intent(this, SelectTestActivity.class);
            parentIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            final Intent startAppIntent = new Intent(this, DfuActivity.class);
            startAppIntent.putExtras(getIntent().getExtras());
            startActivities(new Intent[] { parentIntent, startAppIntent });
        } else {
            Log.e(TAG, "NOT isTaskRoot()");
        }

        // Now finish, which will drop the user in to the activity that was at the top
        //  of the task stack
        finish();
    }
}
