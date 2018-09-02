package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class PeriodicityDetect {

    @SerializedName("Body")
    public final Body body;

    public PeriodicityDetect(Body body) {
        this.body = body;
    }

    public static class Body {
        @SerializedName("Timestamp")
        public final long timestamp;

        @SerializedName("Histogram")
        public final float[] histogram;

        @SerializedName("TriggerPeriodId")
        public final Byte triggerPeriodId;

        @SerializedName("NoiseLevel")
        public final float noiseLevel;

        @SerializedName("Amplitude")
        public final float amplitude;

        public Body(long timestamp, float[] array, Byte triggerPeriodId, float noiseLevel, float amplitude) {
            this.timestamp = timestamp;
            this.histogram = array;
            this.triggerPeriodId = triggerPeriodId;
            this.noiseLevel = noiseLevel;
            this.amplitude = amplitude;
        }
    }
}

