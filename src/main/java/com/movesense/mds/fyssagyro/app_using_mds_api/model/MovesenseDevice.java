package com.movesense.mds.fyssagyro.app_using_mds_api.model;


public class MovesenseDevice {

    private final String macAddress;
    private final String name;
    private final String serial;
    private final String swVersion;

    public MovesenseDevice(String macAddress, String name, String serial, String swVersion) {
        this.macAddress = macAddress;
        this.name = name;
        this.serial = serial;
        this.swVersion = swVersion;
    }

    public String getName() {
        return name;
    }

    public String getSerial() {
        return serial;
    }

    public String getMacAddress() {
        return macAddress;
    }

    public String getSwVersion() {
        return swVersion;
    }
}
