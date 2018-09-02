package com.movesense.mds.fyssagyro.model;

import com.google.gson.annotations.SerializedName;

public  class MdsConnectedDevice<T> {

    @SerializedName("Connected")
    private boolean connected;

    @SerializedName("Serial")
    private String serial;

    @SerializedName("Connection")
    private MdsConnection connection;

    @SerializedName("DeviceInfo")
    private T deviceInfo;

    public boolean isConnected() {
        return connected;
    }

    public String getSerial() {
        return serial;
    }

    public MdsConnection getConnection() {
        return connection;
    }

//    public MdsDeviceInfo getDeviceInfo() {
//        return deviceInfo;
//    }

    public T getDeviceInfo() {
        return deviceInfo;
    }

    public void setDeviceInfo(T deviceInfo) {
        this.deviceInfo = deviceInfo;
    }

    public void setConnected(boolean connected) {
        this.connected = connected;
    }

    public void setSerial(String serial) {
        this.serial = serial;
    }

    public void setConnection(MdsConnection connection) {
        this.connection = connection;
    }

//    public void setDeviceInfo(MdsDeviceInfo deviceInfo) {
//        this.deviceInfo = deviceInfo;
//    }
}
