package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class FyssaGyroGetData {

    @SerializedName("Content")
    private final Content body;

    public FyssaGyroGetData(Content body) {
        this.body = body;
    }

    public Content getContent() {
        return body;
    }

    public class Content {

        @SerializedName("Frontx")
        private float frontx;

        @SerializedName("Fronty")
        private float fronty;

        @SerializedName("Frontz")
        private float frontz;

        @SerializedName("Topx")
        private float topx;

        @SerializedName("Topy")
        private float topy;

        @SerializedName("Topz")
        private float topz;



        public Content(float frontx, float fronty, float frontz, float topx, float topy, float topz) {
            this.frontx = frontx;
            this.fronty = fronty;
            this.frontz = frontz;
            this.topx = topx;
            this.topy = topy;
            this.topz = topz;
        }

        public float[] getFrontArray() {
            return new float[]{frontx, fronty, frontz};
        }
        public float getFrontX() {
            return frontx;
        }
        public float getFrontY() {
            return fronty;
        }
        public float getFrontZ() {
            return frontz;
        }
        public float getTopX() {
            return topx;
        }
        public float getTopY() {
            return topy;
        }
        public float getTopZ() {
            return topz;
        }

        public float[] getTopArray() {
            return new float[]{topx, topy, topz};
        }

    }

}
