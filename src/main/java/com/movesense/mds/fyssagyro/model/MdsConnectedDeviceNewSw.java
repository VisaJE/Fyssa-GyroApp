package com.movesense.mds.fyssagyro.model;


import com.google.gson.annotations.SerializedName;

public class MdsConnectedDeviceNewSw extends MdsConnectedDevice {

      @SerializedName("DeviceInfo")
      private MdsDeviceInfoNewSw deviceInfo;

    public MdsDeviceInfoNewSw getDeviceInfo() {
        return deviceInfo;
    }

    public void setDeviceInfo(MdsDeviceInfoNewSw deviceInfo) {
        this.deviceInfo = deviceInfo;

    }

}

