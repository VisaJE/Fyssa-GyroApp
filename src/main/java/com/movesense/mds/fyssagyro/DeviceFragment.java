package com.movesense.mds.fyssagyro;

import android.os.Bundle;
import android.support.annotation.IdRes;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.movesense.mds.fyssagyro.model.MdsConnectedDevice;

import rx.Observable;
import rx.android.schedulers.AndroidSchedulers;
import rx.functions.Action1;
import rx.functions.Func1;
import rx.subjects.PublishSubject;
import rx.subscriptions.CompositeSubscription;

/**
 * Fragment for showing info about current connection
 */
public class DeviceFragment extends Fragment {

    private CompositeSubscription subscriptions;

    private String serial;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        subscriptions = new CompositeSubscription();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_device, container, false);

        // Set the view as being refreshing
        final SwipeRefreshLayout swipeRefreshLayout = (SwipeRefreshLayout) view;
        swipeRefreshLayout.setRefreshing(true);

        final TextView serialTextView = (TextView) view.findViewById(R.id.serialTextView);

        // Monitor for connected devices
        subscriptions.add(MdsRx.Instance.connectedDeviceObservable()
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Action1<MdsConnectedDevice>() {
                    @Override
                    public void call(MdsConnectedDevice mdsConnectedDevice) {
                        // We have a new SdsDevice
                        serial = mdsConnectedDevice.getSerial();
                        serialTextView.setText(serial);

                        // Stop refreshing
                        swipeRefreshLayout.setRefreshing(false);
                        swipeRefreshLayout.setEnabled(false);
                    }
                }, new ThrowableToastingAction(getContext())));

        final EditText pathEditText = (EditText) view.findViewById(R.id.pathEditText);
        final EditText contractEditText = (EditText) view.findViewById(R.id.contractEditText);
        final TextView resultTextView = (TextView) view.findViewById(R.id.resultTextView);

        Action1<String> toResultAction = new Action1<String>() {
            @Override
            public void call(String s) {
                resultTextView.setText(s);
            }
        };

        Action1<Throwable> errorToResultAction = new Action1<Throwable>() {
            @Override
            public void call(Throwable throwable) {
                resultTextView.setText(throwable.getMessage());
            }
        };

        // Handle Get button clicks
        subscriptions.add(getViewClicks(R.id.btn_get, view)
                .flatMap(new Func1<View, Observable<String>>() {
                    @Override
                    public Observable<String> call(View view) {
                        String path = MdsRx.SCHEME_PREFIX + serial + "/" + pathEditText.getText().toString();
                        String contract = contractEditText.getText().toString();

                        return MdsRx.Instance.get(path, contract).toObservable();
                    }
                })
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(toResultAction, errorToResultAction));

        // Handle Post button clicks
        subscriptions.add(getViewClicks(R.id.btn_post, view)
                .flatMap(new Func1<View, Observable<String>>() {
                    @Override
                    public Observable<String> call(View view) {
                        String path = MdsRx.SCHEME_PREFIX + serial + "/" + pathEditText.getText().toString();
                        String contract = contractEditText.getText().toString();

                        return MdsRx.Instance.post(path, contract).toObservable();
                    }
                })
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(toResultAction, errorToResultAction));

        // Handle Del button clicks
        subscriptions.add(getViewClicks(R.id.btn_del, view)
                .flatMap(new Func1<View, Observable<String>>() {
                    @Override
                    public Observable<String> call(View view) {
                        String path = MdsRx.SCHEME_PREFIX + serial + "/" + pathEditText.getText().toString();
                        String contract = contractEditText.getText().toString();

                        return MdsRx.Instance.delete(path, contract).toObservable();
                    }
                })
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(toResultAction, errorToResultAction));

        return view;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();

        subscriptions.unsubscribe();
    }

    private Observable<View> getViewClicks(@IdRes int viewId, View root) {
        final View view = root.findViewById(viewId);
        final PublishSubject<View> subject = PublishSubject.create();
        view.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                subject.onNext(view);
            }
        });

        return subject
                .asObservable()
                .observeOn(AndroidSchedulers.mainThread());
    }
}
