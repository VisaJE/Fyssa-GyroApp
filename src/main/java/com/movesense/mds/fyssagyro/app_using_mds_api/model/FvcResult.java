package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class FvcResult {

    @SerializedName("Body")
    public final Body body;

    public FvcResult(Body body) {
        this.body = body;
    }

    public static class Body {
        @SerializedName("Timestamp")
        public final long timestamp;

        @SerializedName("Value")
        public final float[] value;

        @SerializedName("Goodness")
        public final float goodness;

        public Body(long timestamp, float[] array, float goodness) {
            this.timestamp = timestamp;
            this.value = array;
            this.goodness = goodness;
        }
    }
}

