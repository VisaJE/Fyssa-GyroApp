package com.movesense.mds.fyssagyro.app_using_mds_api.model;

import com.google.gson.annotations.SerializedName;

public class InfoResponse {

    @SerializedName("Content")
    public final Content content;

    public InfoResponse(Content content) {
        this.content = content;
    }

    public static class Content {
        @SerializedName("SampleRates")
        public final int sampleRates[];

        @SerializedName("Ranges")
        public final int ranges[];

        public Content(int[] sampleRates, int[] ranges) {
            this.sampleRates = sampleRates;
            this.ranges = ranges;
        }
    }
}
