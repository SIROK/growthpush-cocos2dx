package com.growthpush.cocos2dx;

import com.growthpush.BroadcastReceiver;
import com.growthpush.GrowthPush;

import android.content.Context;
import android.content.Intent;

public class GPCocos2dxBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        super.onReceive(context, intent);
        
        if (GrowthPush.getInstance().getClient() == null) {
            GrowthPushJNI.saveGrowthPushMessage(intent);
        }
    }
}
