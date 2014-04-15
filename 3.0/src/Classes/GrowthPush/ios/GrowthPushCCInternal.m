//
//  GrowthPushCCInternal.m
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/09.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "GrowthPushCCInternal.h"

#import <GrowthPush/GrowthPush.h>

#import "UIApplication+GrowthPushCCInternal.h"

static void (^s_didReceiveRemoteNotificationBlock)(NSString *json) = NULL;
                                                      
@implementation GrowthPushCCInternal

- (void)dealloc
{
    if (s_didReceiveRemoteNotificationBlock) {
        Block_release(s_didReceiveRemoteNotificationBlock);
        s_didReceiveRemoteNotificationBlock = NULL;
    }
    [super dealloc];
}

+ (void)setApplicationId:(NSInteger)applicationId secret:(NSString *)secret environment:(GPEnvironment)environment debug:(BOOL)debug
{
    [GrowthPush setApplicationId:applicationId
                          secret:secret
                     environment:environment
                           debug:debug];
}

+ (void)setApplicationId:(NSInteger)applicationId secret:(NSString *)secret environment:(GPEnvironment)environment debug:(BOOL)debug option:(EGPOption)option
{
    [EasyGrowthPush setApplicationId:applicationId
                              secret:secret
                         environment:environment
                               debug:debug
                              option:option];
}

+ (void)requestDeviceToken
{
    [GrowthPush requestDeviceToken];
}

+ (void)trackEvent:(NSString *)name
{
    [GrowthPush trackEvent:name];
}

+ (void)trackEvent:(NSString *)name value:(NSString *)value
{
    [GrowthPush trackEvent:name value:value];
}

+ (void)setTag:(NSString *)name
{
    [GrowthPush setTag:name];
}

+ (void)setTag:(NSString *)name value:(NSString *)value
{
    [GrowthPush setTag:name value:value];
}

+ (void)setDeviceTags
{
    [GrowthPush setDeviceTags];
}

+ (void)clearBadge
{
    [GrowthPush clearBadge];
}

+ (void)setDidReceiveNotificationBlock:(void (^)(NSString *json))block
{
    if (s_didReceiveRemoteNotificationBlock) {
        Block_release(s_didReceiveRemoteNotificationBlock);
    }
    s_didReceiveRemoteNotificationBlock = Block_copy(block);
}

#pragma mark -
#pragma UIApplicationDelegate hook methods

+ (BOOL)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSDictionary *userInfo = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
    if (userInfo) {
        [self didReceiveRemoteNotification:userInfo];
    }
    return YES;
}

+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    [GrowthPush setDeviceToken:deviceToken];
}

+ (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    [GrowthPush setDeviceToken:nil];
}

+ (void)didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    if (s_didReceiveRemoteNotificationBlock) {
        NSError *error = nil;
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:userInfo options:0 error:&error];
        if (error) {
            NSLog(@"failed to parse json: error=%@", [error description]);
            return;
        }
        
        NSString *json = [[[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding] autorelease];
        if (json) {
            s_didReceiveRemoteNotificationBlock(json);
        }
    }
}

@end

#endif
