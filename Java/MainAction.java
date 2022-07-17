package com.example.test;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import android.app.Activity;
import android.os.Bundle;
import android.os.Bundle;
import android.util.Log;
import android.util.Log;
import android.widget.Toast;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;

import android.view.View;

import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.example.test.databinding.ActivityMainBinding;

import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity implements CvCameraViewListener2{

    public static final String TAG = "YOUR-TAG-NAME";
    public BaseLoaderCallback mLoaderCallback;
    public CameraBridgeViewBase mCVCamera;
    @Override
    protected void onCreate(Bundle saveInstanceState){
        super.onCreate(saveInstanceState);
        setContentView(R.layout.activity_main);
        mCVCamera = (CameraBridgeViewBase) findViewById(R.id.camera_view);
        mCVCamera.setCvCameraViewListener(this);
        mLoaderCallback = new BaseLoaderCallback(this) {
            @Override
            public void onManagerConnected(int status){
                switch (status) {
                    case LoaderCallbackInterface.SUCCESS:
                        Log.i(TAG,"OpenCV loaded successfully");
                        mCVCamera.enableView();
                        break;
                    default:
                        break;
                }
            }
        };
    }
    @Override
    public void onResume() {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG,"OpenCV library not found!");
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    };

    public void onCameraViewStarted(int width, int height){
        // TODO Auto-generated method stub

    }

    public void onCameraViewStopped(){
        // TODO Auto-generated method stub

    }

    //下面是具体的图像处理

    public Mat onCameraFrame(CvCameraViewFrame inputFrame){


        return inputFrame.rgba();

    }

}



