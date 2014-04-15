package com.growthpush.cocos2dx;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;

import com.growthpush.GrowthPush;

public class GrowthPushJNI {
    static final String LOG_TAG = "growthpush-cocos2dx";
    static Context mContext = null;
    static String mGrowthPushMessage = null;
    static int mOption = OptionJNI.all;

    public GrowthPushJNI(Context context) {
        mContext = context;
    }

    public static void saveGrowthPushMessage(Intent intent) {
        String msg = parseGrowthPushMessage(intent);
        mGrowthPushMessage = msg;
    }
    
    public static void callTrackGrowthPushMessage() {
        if (mGrowthPushMessage != null) {
            didReceiveRemoteNotificationOnGLSurfaceView(mGrowthPushMessage);
            mGrowthPushMessage = null;
        }
    }
    
    /*
     * Send "Launch" event.
     */
    public static void sendLaunchEvent() {
        if ((mOption & OptionJNI.trackLaunch) == OptionJNI.trackLaunch) {
            trackEvent("Launch");
        }
    }

    /*
     * Parse intent to json.
     * 
     * @param intent
     * @return json string
     */
    public static String parseGrowthPushMessage(final Intent intent) {
        if (intent == null) {
            return null;
        }
        Bundle bundle = intent.getExtras();
        if (bundle == null || bundle.isEmpty()) {
            return null;
        }

        try {
            JSONObject jsonObject = new JSONObject();
            for (String key : bundle.keySet()) {
                Object value = bundle.get(key);
                if (key.equals("showDialog") || key.equals("collapse_key") || key.equals("from")) {
                    continue;
                }
                JSONObject json = new JSONObject("{\"" + key + "\":" + value + "}");
                jsonObject.put(key, json.get(key));
            }
            return jsonObject.toString();
        } catch (JSONException e) {
            Log.e(LOG_TAG, "Unknown JSON format", e);
        }
        return null;
    }
    
    static void didReceiveRemoteNotificationOnGLSurfaceView(final String json) {
        Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
            @Override
            public void run() {
                didReceiveRemoteNotification(json);
            }
        });
    }
    
    /*
     * Remote notification callback method (JNI interface)
     *
     * @param json  json string
     */
    static native void didReceiveRemoteNotification(String json);

    public static void initialize(int applicationId, final String secret, int environment, boolean debug) {
        GrowthPush.getInstance().initialize(mContext, applicationId, secret, EnvironmentJNI.environmentFromCocos(environment), debug);
    }

    public static void initialize(int applicationId, final String secret, int environment, boolean debug, int option) {
        mOption = option;
        initialize(applicationId, secret, environment, debug);
    }
    
    public static void register(final String senderId) {
        GrowthPush.getInstance().register(senderId);
    }

    public static void trackEvent(final String name) {
        GrowthPush.getInstance().trackEvent(name);
    }

    public static void trackEvent(final String name, final String value) {
        GrowthPush.getInstance().trackEvent(name, value);
    }

    public static void setTag(final String name) {
        GrowthPush.getInstance().setTag(name);
    }

    public static void setTag(final String name, final String value) {
        GrowthPush.getInstance().setTag(name, value);
    }

    public static void setDeviceTags() {
        GrowthPush.getInstance().setDeviceTags();
    }
}
