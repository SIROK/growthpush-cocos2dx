//
//  UIApplication+GrowthPushCCInternal.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/08.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

@interface UIApplication (GrowthPushCCInternalInterface)

- (BOOL)application:(UIApplication *)application gp_didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void)application:(UIApplication *)application gp_didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)devToken;
- (void)application:(UIApplication *)application gp_didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
- (void)application:(UIApplication *)application gp_didReceiveRemoteNotification:(NSDictionary *)userInfo;

@end

#endif
