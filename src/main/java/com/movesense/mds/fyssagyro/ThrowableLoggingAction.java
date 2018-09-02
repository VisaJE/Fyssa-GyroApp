package com.movesense.mds.fyssagyro;

import android.util.Log;

import rx.functions.Action1;

/**
 * Helper class to just log out Rx errors
 */
public class ThrowableLoggingAction implements Action1<Throwable>  {

    private final String tag;
    private final String msg;

    ThrowableLoggingAction(String tag, String msg) {
        this.tag = tag;
        this.msg = msg;
    }

    @Override
    public void call(Throwable throwable) {
        Log.e(tag, msg, throwable);
    }
}
