package com.movesense.mds.fyssagyro;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import rx.functions.Action1;

/**
 * Helper class to allow showing Rx exceptions as Toasts
 */
public class ThrowableToastingAction implements Action1<Throwable> {

    private static final String TAG = ThrowableToastingAction.class.getSimpleName();

    private final Context context;

    public ThrowableToastingAction(Context context) {
        this.context = context;
    }

    @Override
    public void call(Throwable throwable) {
        Log.e(TAG, "RxError: ", throwable);
        Toast.makeText(context, throwable.getMessage(), Toast.LENGTH_LONG).show();
    }
}
