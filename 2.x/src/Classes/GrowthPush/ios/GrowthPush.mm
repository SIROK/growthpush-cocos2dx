//
//  GrowthPush.mm
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#if defined(CC_TARGET_OS_IPHONE)

#include "GrowthPush.h"

#include "GPJsonHelper.h"
#include "GrowthPushCCInternal.h"

USING_NS_CC;
USING_NS_GROWTHPUSH;

GrowthPush::GrowthPush(void)
{
}

GrowthPush::~GrowthPush(void)
{
}

void GrowthPush::initialize(int applicationId, const char *secret, growthpush::GPEnvironment environment, bool debug)
{
    CCAssert(secret, "secret should not be NULL");
    
    [GrowthPushCCInternal setApplicationId:applicationId
                                    secret:[NSString stringWithUTF8String:secret]
                               environment:environment
                                     debug:debug];
}

void GrowthPush::initialize(int applicationId, const char *secret, growthpush::GPEnvironment environment, bool debug, growthpush::EGPOption option)
{
    CCAssert(secret, "secret should not be NULL");
    
    [GrowthPushCCInternal setApplicationId:applicationId
                                    secret:[NSString stringWithUTF8String:secret]
                               environment:environment
                                     debug:debug
                                    option:option];
}

void GrowthPush::registerDeviceToken(void)
{
    [GrowthPushCCInternal requestDeviceToken];
}

void GrowthPush::registerDeviceToken(const char *senderId)
{
    CC_UNUSED_PARAM(senderId);  // ignore senderID
    registerDeviceToken();
}

void GrowthPush::trackEvent(const char *name)
{
    CCAssert(name, "name should not be NULL");
    
    [GrowthPushCCInternal trackEvent:[NSString stringWithUTF8String:name]];
}

void GrowthPush::trackEvent(const char *name, const char *value)
{
    CCAssert(name, "name should not be NULL");
    CCAssert(value, "value should not be NULL");
    
    [GrowthPushCCInternal trackEvent:[NSString stringWithUTF8String:name]
                               value:[NSString stringWithUTF8String:value]];
}

void GrowthPush::setTag(const char *name)
{
    CCAssert(name, "name should not be NULL");
    
    [GrowthPushCCInternal setTag:[NSString stringWithUTF8String:name]];
}

void GrowthPush::setTag(const char *name, const char *value)
{
    CCAssert(name, "name should not be NULL");
    CCAssert(value, "value should not be NULL");
    
    [GrowthPushCCInternal setTag:[NSString stringWithUTF8String:name]
                           value:[NSString stringWithUTF8String:value]];
}

void GrowthPush::setDeviceTags(void)
{
    [GrowthPushCCInternal setDeviceTags];
}

void GrowthPush::clearBadge(void)
{
    [GrowthPushCCInternal clearBadge];
}

void GrowthPush::launchWithNotification(CCApplication *target, GPRemoteNotificationCallFunc selector)
{
    CCAssert(target, "target should not be NULL");
    CCAssert(selector, "selector should not be NULL");
    
    [GrowthPushCCInternal setDidReceiveNotificationBlock:^(NSString *json) {
        CCDictionary *jsonDict = GPJsonHelper::parseJson2CCDictionary([json UTF8String]);
        (target->*selector)(jsonDict);
    }];
}

#endif
