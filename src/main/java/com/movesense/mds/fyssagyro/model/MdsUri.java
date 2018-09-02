package com.movesense.mds.fyssagyro.model;

import com.google.gson.annotations.SerializedName;

public class MdsUri {

    @SerializedName("Uri")
    private String uri;

    public MdsUri() {
    }

    public MdsUri(String uri) {
        this.uri = uri;
    }

    public String getUri() {
        return uri;
    }

    public void setUri(String uri) {
        this.uri = uri;
    }
}
