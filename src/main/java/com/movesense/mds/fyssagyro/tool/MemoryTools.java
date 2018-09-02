package com.movesense.mds.fyssagyro.tool;


import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.os.Environment;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class MemoryTools {
    public static final String DEFAULT_STRING = "AKSDJISAJDIOAS !UIOPHISFHIAOSIO_!@#232j";

    private static final String SHARED_PREF_NAME = "SHARED_PREFS";
    private static final String NAME_SHARED_PREF = "NAME_PREFS";
    private static final String SERIAL_SHARED_PREF = "SERIAL_PREFS";

    private final static int BUFFER_SIZE = 1024;


    private Application app;
    private SharedPreferences sharedPref;

    public MemoryTools(Application app) {
        this.app = app;
        sharedPref = app.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
    }

    public void saveName(String name) {
        SharedPreferences.Editor edit = sharedPref.edit();
        edit.putString(NAME_SHARED_PREF, name);
        edit.commit();
    }

    public String getName() {
        return sharedPref.getString(NAME_SHARED_PREF, DEFAULT_STRING);
    }

    public void saveSerial(String name) {
        SharedPreferences.Editor edit = sharedPref.edit();
        edit.putString(SERIAL_SHARED_PREF, name);
        edit.commit();
    }

    public String getSerial() {
        return sharedPref.getString(SERIAL_SHARED_PREF, DEFAULT_STRING);
    }

    public File getAssetsFile(AssetManager assetManager, String assetsFile) {
        InputStream in = null;
        OutputStream out = null;
        try {
            in = assetManager.open(assetsFile);
            File outFile = new File(Environment.getExternalStorageDirectory(), assetsFile);
            out = new FileOutputStream(outFile);
            copyFile(in, out);
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
        } catch(IOException e) {
                Log.e("tag", "Failed to copy asset file: " + assetsFile, e);
                return null;
        }
        return new File(Environment.getExternalStorageDirectory() + "/" + assetsFile);
    }

    private void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while((read = in.read(buffer)) != -1){
            out.write(buffer, 0, read);
        }
    }
}
