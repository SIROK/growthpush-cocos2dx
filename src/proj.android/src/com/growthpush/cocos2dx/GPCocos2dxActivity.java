package com.growthpush.cocos2dx;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.growthpush.GrowthPush;
import com.growthpush.handler.DefaultReceiveHandler;

public class GPCocos2dxActivity extends Cocos2dxActivity {
	static final String LOG_TAG = "GPCocos2dxActivity";
	static GrowthPushJNI growthPushJNI = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		growthPushJNI = new GrowthPushJNI(this);

		// register receive handler method
		DefaultReceiveHandler receiveHandler = new DefaultReceiveHandler() {
			@Override
			public void onReceive(Context context, Intent intent) {
				Log.d(LOG_TAG, "onReceive");
				super.onReceive(context, intent);
			}
		};
		receiveHandler.setCallback(new DefaultReceiveHandler.Callback() {
			@Override
			public void onOpen(Context context, final Intent intent) {
				Log.d(LOG_TAG, "onOpen");
				super.onOpen(context, intent);
				String str = GrowthPushJNI.parseGrowthPushMessage(intent);
				if (str != null) {
					GrowthPushJNI.didReceiveRemoteNotificationOnGLSurfaceView(str);
				}
			}
		});
		GrowthPush.getInstance().setReceiveHandler(receiveHandler);
	}
	
	@Override
	protected void onResume() {
	    super.onResume();
	    GrowthPushJNI.sendLaunchEvent();
	}
}
