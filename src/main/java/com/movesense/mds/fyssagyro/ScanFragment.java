package com.movesense.mds.fyssagyro;

import android.Manifest;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.polidea.rxandroidble.RxBleClient;
import com.polidea.rxandroidble.RxBleDevice;
import com.polidea.rxandroidble.RxBleScanResult;

import rx.Subscription;
import rx.functions.Action1;
import rx.subscriptions.CompositeSubscription;

/**
 * Fragment for scanning a ble device
 */
public class ScanFragment extends Fragment {

    private BluetoothAdapter bluetoothAdapter;

    public interface DeviceSelectionListener {
        void onDeviceSelected(RxBleDevice device);
    }

    private static final int MY_PERMISSIONS_REQUEST_LOCATION = 99;

    private DeviceSelectionListener deviceSelectionListener;
    private RxBleClient rxBleClient;
    private ScannedDevicesAdapter scannedDevicesAdapter;
    private CompositeSubscription subscriptions;

    private final String LOG_TAG = ScanFragment.class.getSimpleName();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Activity activity = getActivity();
        if (activity instanceof DeviceSelectionListener) {
            deviceSelectionListener = (DeviceSelectionListener) activity;
        } else {
            throw new IllegalArgumentException("Containing Activity does not implement DeviceSelectionListener");
        }

        getActivity().registerReceiver(btReceiver, new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED));

        // Ask For Bluetooth
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!bluetoothAdapter.isEnabled()) {
            // Bluetooth is not enable so run
            bluetoothAdapter.enable();
        }

        // Capture instance of RxBleClient to make code look cleaner
        rxBleClient = RxBle.Instance.getClient();

        // Create one composite subscription to hold everything
        subscriptions = new CompositeSubscription();


    }

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_scan, container, false);

        // Set up list and adapter for scanned devices
        scannedDevicesAdapter = new ScannedDevicesAdapter(true);
        RecyclerView deviceList = (RecyclerView) view.findViewById(R.id.device_list);
        deviceList.setLayoutManager(new LinearLayoutManager(getContext()));
        deviceList.setAdapter(scannedDevicesAdapter);
        deviceList.setItemAnimator(null);

        // Listen for device selection
        Subscription selectionSubscription = scannedDevicesAdapter.deviceSelectionObservable()
                .subscribe(new Action1<RxBleDevice>() {
                    @Override
                    public void call(RxBleDevice rxBleDevice) {
                        deviceSelectionListener.onDeviceSelected(rxBleDevice);
                    }
                }, new ThrowableToastingAction(getContext()));
        subscriptions.add(selectionSubscription);

        // Start scanning immediately
        startScanning();

        return view;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();

        // Clear all subscriptions
        subscriptions.unsubscribe();

        // Unregister BtReceiver
        getActivity().unregisterReceiver(btReceiver);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           @NonNull String permissions[],
                                           @NonNull int[] grantResults) {
        if (requestCode == MY_PERMISSIONS_REQUEST_LOCATION) {
            // If request is cancelled, the result arrays are empty.
            if (grantResults.length > 0
                    && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

                // permission was granted, yay! Do the
                // location-related task you need to do.
                if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.ACCESS_COARSE_LOCATION)
                        == PackageManager.PERMISSION_GRANTED) {

                    // Try starting scan again
                    startScanning();
                }
            }
        }
    }

    private void startScanning() {
        // Make sure we have location permission
        if (!checkLocationPermission()) {
            return;
        }

        Log.d(LOG_TAG, "START SCANNING !!!");
        // Start scanning
        subscriptions.add(rxBleClient.scanBleDevices()
                .subscribe(new Action1<RxBleScanResult>() {
                    @Override
                    public void call(RxBleScanResult rxBleScanResult) {
                        scannedDevicesAdapter.handleScanResult(rxBleScanResult);
                    }
                }, new ThrowableToastingAction(getContext())));
    }


    private boolean checkLocationPermission() {
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.ACCESS_COARSE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {

            // Should we show an explanation?
            if (shouldShowRequestPermissionRationale(Manifest.permission.ACCESS_COARSE_LOCATION)) {
                new AlertDialog.Builder(getActivity())
                        .setTitle(R.string.title_location_permission)
                        .setMessage(R.string.text_location_permission)
                        .setPositiveButton(R.string.btn_ok, new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                //Prompt the user once explanation has been shown
                                requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                                        MY_PERMISSIONS_REQUEST_LOCATION);
                            }
                        })
                        .create()
                        .show();

            } else {
                // No explanation needed, we can request the permission.
                requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                        MY_PERMISSIONS_REQUEST_LOCATION);
            }
            return false;
        } else {
            return true;
        }
    }

    private final BroadcastReceiver btReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {

            String action = intent.getAction();

            // It means the user has changed his bluetooth state.
            if (action.equals(BluetoothAdapter.ACTION_STATE_CHANGED)) {

                if (bluetoothAdapter.getState() == BluetoothAdapter.STATE_ON) {
                    // The user bluetooth is ready to use.

                    // start scanning again in case of ready Bluetooth
                    startScanning();
                    return;
                }

                if (bluetoothAdapter.getState() == BluetoothAdapter.STATE_TURNING_OFF) {
                    // The user bluetooth is turning off yet, but it is not disabled yet.
                    return;
                }

                if (bluetoothAdapter.getState() == BluetoothAdapter.STATE_OFF) {
                    // The user bluetooth is already disabled.
                    return;
                }

            }
        }
    };

}
