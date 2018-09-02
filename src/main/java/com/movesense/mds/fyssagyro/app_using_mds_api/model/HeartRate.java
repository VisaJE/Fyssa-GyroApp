package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class HeartRate {

    @SerializedName("Body")
    public final Body body;

    public HeartRate(Body body) {
        this.body = body;
    }

    public static class Body {
        @SerializedName("rrData")
        public final int rrData[];

        public Body(int[] rrData) {
            this.rrData = rrData;
        }
    }
}
