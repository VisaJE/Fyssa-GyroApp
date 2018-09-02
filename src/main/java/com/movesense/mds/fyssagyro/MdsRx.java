package com.movesense.mds.fyssagyro;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.movesense.mds.Logger;
import com.movesense.mds.Mds;
import com.movesense.mds.MdsException;
import com.movesense.mds.MdsNotificationListener;
import com.movesense.mds.MdsResponseListener;
import com.movesense.mds.MdsSubscription;
import com.movesense.mds.fyssagyro.model.MdsConnectedDevice;
import com.movesense.mds.fyssagyro.model.MdsDeviceInfoNewSw;
import com.movesense.mds.fyssagyro.model.MdsDeviceInfoOldSw;
import com.movesense.mds.fyssagyro.model.MdsResponse;
import com.movesense.mds.fyssagyro.model.MdsUri;
import com.polidea.rxandroidble.RxBleDevice;

import java.lang.reflect.Type;
import java.nio.charset.Charset;

import rx.Emitter;
import rx.Observable;
import rx.Single;
import rx.SingleEmitter;
import rx.functions.Action1;
import rx.functions.Cancellable;
import rx.functions.Func1;

/**
 * Singleton to hold MDS
 */
public enum MdsRx {
    Instance;

    // Set of MDS constants
    public static final String EMPTY_CONTRACT = "";
    public static final String SCHEME_PREFIX = "suunto://";
    public static final String URI_WHITEBOARD_INFO = "suunto://MDS/whiteboard/info";
    public static final String URI_EVENTLISTENER = "suunto://MDS/EventListener";
    public static final String URI_CONNECTEDDEVICES = "suunto://MDS/ConnectedDevices";

    private static final String TAG = "MDS";

    private final Charset utf8Charset;
    private final Gson gson;


    private BleManager bleManager;

    private RxBleDevice rxBleDevice;
    private Activity activity;
    private Mds mMds;

    MdsRx() {
        utf8Charset = Charset.forName("UTF-8"); // NON-NLS
        gson = new GsonBuilder().create();
    }

    public void initialize(Context context) {
        mMds = Mds.builder().build(context);

        // Create BleManager
        bleManager = BleManager.INSTANCE;

        // Allow logging
        Logger.setPipeToOSLoggingEnabled(true);
    }

    public void connect(RxBleDevice bleDevice, Activity activity) {
        this.rxBleDevice = bleDevice;
        this.activity = activity;
        bleManager.connect(bleDevice, activity);
    }

    public void reconnect(Activity activity) {
        Log.e(TAG, "reconnect() : " + rxBleDevice.getMacAddress());
        bleManager.reconnect(activity);
    }

    public Single<String> get(String uri) {
        return get(uri, EMPTY_CONTRACT);
    }

    public Single<String> delete(String uri) {
        return delete(uri, EMPTY_CONTRACT);
    }

    public Single<String> get(final String uri, final String contract) {
       return Single.fromEmitter(new Action1<SingleEmitter<String>>() {
           @Override
           public void call(final SingleEmitter<String> mdsCallbackSingleEmitter) {
               mMds.get(uri, contract, new MdsResponseListener() {
                   @Override
                   public void onSuccess(String s) {
                       mdsCallbackSingleEmitter.onSuccess(s);
                   }

                   @Override
                   public void onError(MdsException e) {
                        mdsCallbackSingleEmitter.onError(e);
                   }
               });
           }
       });
    }

    public Single<String> post(final String uri, final String contract) {
        return Single.fromEmitter(new Action1<SingleEmitter<String>>() {
            @Override
            public void call(final SingleEmitter<String> mdsCallbackSingleEmitter) {
                mMds.post(uri, contract, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        mdsCallbackSingleEmitter.onSuccess(s);
                    }

                    @Override
                    public void onError(MdsException e) {
                        mdsCallbackSingleEmitter.onError(e);
                    }
                });
            }
        });
    }

    public Single<String> delete(final String uri, final String contract) {
       return Single.fromEmitter(new Action1<SingleEmitter<String>>() {
           @Override
           public void call(final SingleEmitter<String> mdsCallbackSingleEmitter) {
                mMds.delete(uri, contract, new MdsResponseListener() {
                    @Override
                    public void onSuccess(String s) {
                        mdsCallbackSingleEmitter.onSuccess(s);
                    }

                    @Override
                    public void onError(MdsException e) {
                        mdsCallbackSingleEmitter.onError(e);
                    }
                });
           }
       });
    }

    public Observable<MdsConnectedDevice> connectedDeviceObservable() {
        return subscribe(URI_CONNECTEDDEVICES)
                .map(new Func1<String, MdsConnectedDevice>() {
                    @Override
                    public MdsConnectedDevice call(String s) {
                        try {
                            Type type = new TypeToken<MdsResponse<MdsConnectedDevice<MdsDeviceInfoNewSw>>>() {}.getType();
                            MdsResponse<MdsConnectedDevice<MdsDeviceInfoNewSw>> response = gson.fromJson(s, type);
                            return response.getBody();
                        } catch (Exception e) {
                            Type type = new TypeToken<MdsResponse<MdsConnectedDevice<MdsDeviceInfoOldSw>>>() {}.getType();
                            MdsResponse<MdsConnectedDevice<MdsDeviceInfoOldSw>> response = gson.fromJson(s, type);
                            return response.getBody();
                        }
                    }
                })
                .filter(new Func1<MdsConnectedDevice, Boolean>() {
                    @Override
                    public Boolean call(MdsConnectedDevice mdsConnectedDevice) {
                        return mdsConnectedDevice != null;
                    }
                });
    }

    public Observable<String> subscribe(final String uri) {
        return Observable.create(new Action1<Emitter<String>>() {
            @Override
            public void call(final Emitter<String> stringEmitter) {
                final MdsSubscription subscription = mMds.subscribe(URI_EVENTLISTENER, gson.toJson(new MdsUri(uri)),
                        new MdsNotificationListener() {
                            @Override
                            public void onNotification(String s) {
                                stringEmitter.onNext(s);
                            }

                            @Override
                            public void onError(MdsException e) {
                                stringEmitter.onError(e);
                            }
                        });

                stringEmitter.setCancellation(new Cancellable() {
                    @Override
                    public void cancel() throws Exception {
                        subscription.unsubscribe();
                    }
                });
            }
        }, Emitter.BackpressureMode.BUFFER);
    }
}
