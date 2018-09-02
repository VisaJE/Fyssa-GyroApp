package com.movesense.mds.fyssagyro;

import java.util.Arrays;

/**
 * Created by martikkm on 13.10.2016.
 */

public class FeatureVector {
    float[] data;
    public FeatureVector(float[] dataIn) {
        data = dataIn;
    }

    public String toString() {
        String s = "[";
        int c = 0;
        for(float f: data) {
            if(c > 0) {
                s += ", ";
            }
            c++;
            s += f;
        }
        s += "]";
        return s;
    }

    public float norm() {
        float diff = 0.0f;
        for(float v: data) {
            diff += v * v;
        }
        return (float)Math.sqrt(diff);
    }

    public void add(FeatureVector f) {
        if(f.data.length == data.length) {
            for(int i = 0; i< data.length; i++) {
                data[i] += f.data[i];
            }
        }
    }

    public void subtract(FeatureVector f) {
        if(f.data.length == data.length) {
            for(int i = 0; i< data.length; i++) {
                data[i] -= f.data[i];
            }
        }
    }

    public FeatureVector scale(float scaler) {
        FeatureVector fHere = new FeatureVector(Arrays.copyOfRange(data, 0, data.length));
        for (int i = 0; i < data.length; i++) {
            fHere.data[i] *= scaler;
        }
        return fHere;
    }

    public float[] getData() {
        return Arrays.copyOf(data, data.length);
    }
}
