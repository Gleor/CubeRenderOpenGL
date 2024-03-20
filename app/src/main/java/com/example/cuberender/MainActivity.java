package com.example.cuberender;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

class MyGLSurfaceView extends GLSurfaceView {

    public MyGLSurfaceView(Context context) {
        super(context);

        setEGLContextClientVersion(3);
        com.example.cuberender.MyGLRenderer renderer = new com.example.cuberender.MyGLRenderer();
        setRenderer(renderer);
    }
}

public class MainActivity extends AppCompatActivity {

    private MyGLSurfaceView glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        glView = new MyGLSurfaceView(getApplication());
        setContentView(glView);
    }
    @Override protected void onPause()
    {
        super.onPause();
        glView.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        glView.onResume();
    }
    @Override protected void onDestroy()
    {
        super.onDestroy();
    }
}