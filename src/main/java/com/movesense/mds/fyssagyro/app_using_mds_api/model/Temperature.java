package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class Temperature {

    @SerializedName("Content")
    public final Content content;

    public Temperature(Content content) {
        this.content = content;
    }

    public static final class Content {
        @SerializedName("RelativeTime")
        public final long relativeTime;

        @SerializedName("Measurement")
        public final double measurement;

        public Content(long relativeTime, double measurement) {
            this.relativeTime = relativeTime;
            this.measurement = measurement;
        }
    }
}
