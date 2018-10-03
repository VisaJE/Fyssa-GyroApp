package com.movesense.mds.fyssagyro.fyssa_app;

import com.movesense.mds.fyssagyro.app_using_mds_api.model.MagneticField;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import static java.lang.Math.abs;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

public class Projector {
    private LinkedList<Vector3d<Float>> trajectory;
    private int points = 25;

    protected Projector(LinkedList<Vector3d<Float>> trajectory) {
        this.trajectory = trajectory;
    }

    private void collapse() {
        int dataPerPoint = trajectory.size()/points;
        for(int i = 0; i < points; i++) {
            Vector3d<Float> sum = new Vector3d<>(0.0F, 0.0F, 0.0F);
            for (int j = 0; j < dataPerPoint; j++) {
                Vector3d<Float> v= trajectory.pop();
                sum.x += v.x;
                sum.y += v.y;
                sum.z += v.z;
            }
            sum.x /= points;
            sum.y /= points;
            sum.z /= points;
            trajectory.addFirst(sum);
        }
        while (trajectory.size() > points) trajectory.pop();
    }
    
    private Vector3d<Float> findTangent() {
        Vector3d<Float> start = trajectory.getFirst();
        Vector3d<Float> total = new Vector3d<>(0F, 0F, 0F);
        for (int i = 1; i < trajectory.size(); i++) {
            Vector3d<Float> direction = trajectory.get(i);
            direction.x -= start.x;
            direction.y -= start.y;
            direction.z -= start.z;
            total.x += direction.x;
            total.y += direction.y;
            total.z += direction.z;
        }
        Double len = sqrt(total.x * total.x + total.y * total.y + total.z * total.z);
        // Really unlikely :P
        if (len.floatValue() < 0.0001) return new Vector3d<>(1F, 1F, 1F);

        total.x /= len.floatValue();
        total.y /= len.floatValue();
        total.z /= len.floatValue();
        return total;
    }

    private Vector3d<Float> findNormal(Vector3d<Float> a, Vector3d<Float> b) {
        Float alpha = a.x*a.x + a.y*a.y + a.z*a.z;
        Float dotProduct = a.x*b.x + a.y*b.y + a.z*b.z;
        Float scale = abs(dotProduct) < 0.0001 ? 0F : alpha/dotProduct;
        return new Vector3d<>(b.x - a.x*scale, b.y - a.y*scale, b.z-a.z*scale);
    }
    
    private Vector3d<Float> findNormalOfTan(Vector3d<Float> tan) {
        Vector3d<Float> start = trajectory.getFirst();
        Vector3d<Float> total = new Vector3d<>(0F, 0F, 0F);
        for (int i = 1; i < trajectory.size(); i++) {
            Vector3d<Float> direction = trajectory.get(i);
            direction.x -= start.x;
            direction.y -= start.y;
            direction.z -= start.z;
            Vector3d<Float> normal = findNormal(tan, direction);
            total.x += abs(normal.x);
            total.y += abs(normal.y);
            total.z += abs(normal.z);
        }
        total = normalize(total);
        return total;
    }

    private Vector3d<Float> crossP(Vector3d<Float> a, Vector3d<Float> b) {
        return new Vector3d<>(a.y*b.z - a.z*b.y, a.z*b.x - b.z*a.x, a.x*b.y - a.y*b.x);
    }
    private Vector3d<Float> normalize(Vector3d<Float> v) {
        Double size = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
        if (size < 0.00001) return v;
        return new Vector3d<>(v.x/size.floatValue(), v.y/size.floatValue(), v.z/size.floatValue());
    }

    // Tää kiertää z-akselin suhteen jotta syntyy mahdollisimman iso kuva.

    public ArrayList<Float> getProjection() {
        ArrayList<Float> result = new ArrayList<>(points*2);
        if (trajectory.size() == 0) return result;
        collapse();

        Vector3d<Float> x = findTangent();
        x.z = 0F;

        zRotationMatrix rM = new zRotationMatrix( x.x.doubleValue()/sqrt(x.x*x.x+x.y*x.y+x.z*x.z));
        for (int i = 0; i < trajectory.size(); i++) {
            Vector3d<Float> v = rM.rotateBack(trajectory.get(i));
            result.add(v.x);
            result.add(v.z);
        }
        return result;
    }

}
