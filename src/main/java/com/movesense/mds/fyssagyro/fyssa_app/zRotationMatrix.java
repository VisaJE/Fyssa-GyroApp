package com.movesense.mds.fyssagyro.fyssa_app;

import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static java.lang.Math.sqrt;

public class zRotationMatrix {
    private Double aa;
    private Double ab;
    private Double cc;


    public zRotationMatrix(Float angle) {
        aa = cos(angle);
        ab = sin(angle);
    }
    public zRotationMatrix(Double cosA) {
        aa = cosA;
        ab = sqrt(1-cosA*cosA);
    }

    public Vector3d<Float> rotateBack(Vector3d<Float> v) {
        return new Vector3d<>(aa.floatValue()*v.x - ab.floatValue()*v.y,
                ab.floatValue()*v.x + aa.floatValue()*v.y,
                v.z);
    }
}
