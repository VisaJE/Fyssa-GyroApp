package com.movesense.mds.fyssagyro.fyssa_app;

public class ProjectionMatrix {

    private Float aa;
    private Float ab;
    private Float ac;
    private Float bb;
    private Float cc;
    private Float bc;

    public ProjectionMatrix(Vector3d<Float> n) {
        aa = n.x*n.x;
        ab = n.x*n.y;
        ac = n.x*n.z;
        bb = n.y*n.y;
        cc = n.z*n.z;
        bc = n.y*n.z;
    }

    public Vector3d<Float> project(Vector3d<Float> v) {
        return new Vector3d<>(aa*v.x + ab*v.y + ac*v.z,
                ab*v.x + bb*v.y + bc*v.z,
                ab*v.x + bc*v.y+ cc*v.z);
    }

}
