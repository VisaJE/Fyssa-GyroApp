package com.movesense.mds.fyssagyro.app_using_mds_api.model;

import com.google.gson.annotations.SerializedName;

public class DebugResponse {
    @SerializedName("Body")
    private final Body body;


    public DebugResponse(Body body){
        this.body = body;
    }
    public static class Body {
        @SerializedName("Timestamp")
        private final int timestamp;
        @SerializedName("Level")
        private final int level;
        @SerializedName("Tag")
        private final String tag;
        @SerializedName("Message")
        private final String message;

        public Body(int timestamp, int level, String tag, String message) {
            this.timestamp = timestamp;
            this.level = level;
            this.tag = tag;
            this.message = message;
        }
        String getMessage() {return message;}
    }
    public String getMessage() {return body.getMessage();}
}
