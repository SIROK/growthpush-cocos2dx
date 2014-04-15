package jp.example.sample;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import com.growthpush.cocos2dx.GPCocos2dxActivity;

import android.os.Bundle;

public class SampleActivity extends GPCocos2dxActivity {
    
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
    }

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// GrowthPushCocos2dxPlugin should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
