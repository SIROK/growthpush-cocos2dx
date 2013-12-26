//
//  UIApplication+GrowthPushCCInternal.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/08.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#if defined(CC_TARGET_OS_IPHONE)

#import <UIKit/UIKit.h>

@interface UIApplication (GrowthPushCCInternalInterface)

- (BOOL)application:(UIApplication *)application gp_didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void)application:(UIApplication *)application gp_didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)devToken;
- (void)application:(UIApplication *)application gp_didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
- (void)application:(UIApplication *)application gp_didReceiveRemoteNotification:(NSDictionary *)userInfo;

@end

#endif
