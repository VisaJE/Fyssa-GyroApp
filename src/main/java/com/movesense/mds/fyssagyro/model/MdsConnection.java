package com.movesense.mds.fyssagyro.model;

import com.google.gson.annotations.SerializedName;

public class MdsConnection {

    @SerializedName("UUID")
    private String uuid;

    @SerializedName("Type")
    private String type;

    public String getUuid() {
        return uuid;
    }

    public String getType() {
        return type;
    }
}
