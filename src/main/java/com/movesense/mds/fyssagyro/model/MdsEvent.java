package com.movesense.mds.fyssagyro.model;

import com.google.gson.JsonElement;
import com.google.gson.annotations.SerializedName;

public class MdsEvent {

    public enum Method {
        GET,
        POST,
        PUT,
        DEL
    }

    @SerializedName("Body")
    private JsonElement body;

    @SerializedName("Uri")
    private String uri;

    @SerializedName("Method")
    private Method method;

    public JsonElement getBody() {
        return body;
    }

    public String getUri() {
        return uri;
    }

    public Method getMethod() {
        return method;
    }
}
