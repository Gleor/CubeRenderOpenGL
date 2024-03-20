package com.example.cuberender;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.os.SystemClock;
import java.util.concurrent.TimeUnit;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    private float mCubeRotation;
    private long UpdateMs;
    private static final float ROTATION_INCREMENT = 0.01f;
    private static final float FRAME_TIME = TimeUnit.SECONDS.toMillis(1) / 60.0f;
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    }
    @Override
    public void onDrawFrame(GL10 unused) {
        CubeDraw(mCubeRotation);
        updateCubeRotation();
    }
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        CubeInit(width, height);
    }
    private void updateCubeRotation() {
        if (UpdateMs != 0) {
            float varCoef = (SystemClock.elapsedRealtime() - UpdateMs) / FRAME_TIME;
            mCubeRotation += ROTATION_INCREMENT * varCoef;
        }
        UpdateMs = SystemClock.elapsedRealtime();
    }
    public native void CubeInit(int width, int height);
    public native void CubeDraw(float rotation);

    static {
        System.loadLibrary("native-lib");
    }
}
