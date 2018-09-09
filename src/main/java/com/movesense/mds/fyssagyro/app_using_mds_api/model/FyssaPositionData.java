package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class FyssaPositionData {

    @SerializedName("Body")
    private final Body body;

    public FyssaPositionData(Body body) {
        this.body = body;
    }

    public Body getContent() {
        return body;
    }

    public class Body {

        @SerializedName("X")
        private float x;

        @SerializedName("Y")
        private float y;

        @SerializedName("Z")
        private float z;


        public Body(float x, float y, float z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public float[] getArray() {
            return new float[]{x, y, z};
        }
        public float getX() {
            return x;
        }
        public float getY() {
            return y;
        }
        public float getZ() {
            return z;
        }


    }

}
