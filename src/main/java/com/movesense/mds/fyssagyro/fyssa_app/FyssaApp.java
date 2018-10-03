package com.movesense.mds.fyssagyro.fyssa_app;

import android.app.Application;
import android.content.Context;

import com.movesense.mds.fyssagyro.MdsRx;
import com.movesense.mds.fyssagyro.R;
import com.movesense.mds.fyssagyro.RxBle;
import com.movesense.mds.fyssagyro.Util;
import com.movesense.mds.fyssagyro.app_using_mds_api.model.MagneticField;
import com.movesense.mds.fyssagyro.tool.MemoryTools;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Application for making all initializations
 */
public class FyssaApp extends Application {

    private MemoryTools memoryTools;
    public static String deviceVersion = "0.1.1.IMU";

    public LinkedList<Vector3d<Float>> trajectory;
    public ArrayList<Float> plottable;

    @Override
    public void onCreate() {
        super.onCreate();

        // Initialize RxBleWrapper
        RxBle.Instance.initialize(this);

        // Copy necessary configuration file to proper place
        copyRawResourceToFile(R.raw.kompostisettings, "KompostiSettings.xml");

        // Initialize MDS
        MdsRx.Instance.initialize(this);

        memoryTools = new MemoryTools(this);
        trajectory = new LinkedList<>();
        plottable = new ArrayList<>();
    }

    @Override
    public void onTerminate() {
        super.onTerminate();

    }

    public MemoryTools getMemoryTools() {
        return memoryTools;
    }

    /**
     * Copy raw resource file to file.
     *
     * @param resourceId Resource id.
     * @param fileName   Target file name.
     */
    private void copyRawResourceToFile(int resourceId, String fileName) {
        InputStream in = null;
        FileOutputStream out = null;
        try {
            in = getResources().openRawResource(resourceId);
            out = openFileOutput(fileName, Context.MODE_PRIVATE);
            byte[] buffer = new byte[1024];
            int len;
            while ((len = in.read(buffer)) != -1) {
                out.write(buffer, 0, len);
            }
        } catch (IOException e) {
            throw new IllegalArgumentException("Could not copy configuration file to: " + fileName);
        } finally {
            Util.safeClose(out);
            Util.safeClose(in);
        }
    }
}
