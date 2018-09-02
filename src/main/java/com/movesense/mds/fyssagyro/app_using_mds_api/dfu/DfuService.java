package com.movesense.mds.fyssagyro.app_using_mds_api.dfu;

import android.app.Activity;
import android.util.Log;

import no.nordicsemi.android.dfu.DfuBaseService;

/**
 *
 */

public class DfuService extends DfuBaseService {

    private final String LOG_TAG = DfuService.class.getSimpleName();

    @Override
    protected Class<? extends Activity> getNotificationTarget() {
        Log.d(LOG_TAG, "getNotificationTarget() ");
        return NotificationActivity.class;
    }

    @Override
    protected boolean isDebug() {
        Log.d(LOG_TAG, "isDebug() ");
        return true;
    }
}
