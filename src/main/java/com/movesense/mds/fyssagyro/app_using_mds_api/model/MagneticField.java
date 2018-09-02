package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class MagneticField {

    @SerializedName("Body")
    public final MagneticField.Body body;

    public MagneticField(MagneticField.Body body) {
        this.body = body;
    }

    public static class Body {
        @SerializedName("Timestamp")
        public final long timestamp;

        @SerializedName("ArrayMagn")
        public final MagneticField.Array[] array;

        @SerializedName("Headers")
        public final MagneticField.Headers header;

        public Body(long timestamp, MagneticField.Array[] array, MagneticField.Headers header) {
            this.timestamp = timestamp;
            this.array = array;
            this.header = header;
        }
    }

    public static class Array {
        @SerializedName("x")
        public final double x;
        @SerializedName("y")

        public final double y;
        @SerializedName("z")
        public final double z;

        public Array(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    public static class Headers {
        @SerializedName("Param0")
        public final int param0;

        public Headers(int param0) {
            this.param0 = param0;
        }
    }
}

