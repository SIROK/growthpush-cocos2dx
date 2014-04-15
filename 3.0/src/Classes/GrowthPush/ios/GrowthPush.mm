//
//  GrowthPush.mm
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "GrowthPush.h"

#include "GPJsonHelper.h"
#import "GrowthPushCCInternal.h"

USING_NS_CC;
// Don't use USING_NS_GROWTHPUSH. Because, it's conflict between GPEnvironment(C++) and GPEnvironment(Objective-C).

// C++ and Objective-C wrapper functions.
static inline void _initialize(int applicationId, const std::string &secret, growthpush::GPEnvironment environment, bool debug) {
    [GrowthPushCCInternal setApplicationId:applicationId
                                    secret:[NSString stringWithUTF8String:secret.c_str()]
                               environment:(GPEnvironment)environment
                                     debug:debug];
}

growthpush::GrowthPush::GrowthPush(void)
{
}

growthpush::GrowthPush::~GrowthPush(void)
{
}

void growthpush::GrowthPush::initialize(int applicationId, const std::string &secret, growthpush::GPEnvironment environment, bool debug)
{
    _initialize(applicationId, secret, environment, debug);
}

void growthpush::GrowthPush::registerDeviceToken(void)
{
    [GrowthPushCCInternal requestDeviceToken];
}

void growthpush::GrowthPush::registerDeviceToken(const std::string &senderId)
{
    CC_UNUSED_PARAM(senderId);  // ignore senderID
    registerDeviceToken();
}

void growthpush::GrowthPush::trackEvent(const std::string &name)
{
    [GrowthPushCCInternal trackEvent:[NSString stringWithUTF8String:name.c_str()]];
}

void growthpush::GrowthPush::trackEvent(const std::string &name, const std::string &value)
{
    [GrowthPushCCInternal trackEvent:[NSString stringWithUTF8String:name.c_str()]
                               value:[NSString stringWithUTF8String:value.c_str()]];
}

void growthpush::GrowthPush::setTag(const std::string &name)
{
    [GrowthPushCCInternal setTag:[NSString stringWithUTF8String:name.c_str()]];
}

void growthpush::GrowthPush::setTag(const std::string &name, const std::string &value)
{
    [GrowthPushCCInternal setTag:[NSString stringWithUTF8String:name.c_str()]
                           value:[NSString stringWithUTF8String:value.c_str()]];
}

void growthpush::GrowthPush::setDeviceTags(void)
{
    [GrowthPushCCInternal setDeviceTags];
}

void growthpush::GrowthPush::clearBadge(void)
{
    [GrowthPushCCInternal clearBadge];
}

// FIXME: for C++11
//void growthpush::GrowthPush::launchWithNotification(const growthpush::gpDidReceiveRemoteNotificationCallback &callback)
void growthpush::GrowthPush::launchWithNotification(Application *target, growthpush::GPRemoteNotificationCallFunc selector)
{
    CCAssert(target, "target should not be NULL");
    CCAssert(selector, "selector should not be NULL");
    
    [GrowthPushCCInternal setDidReceiveNotificationBlock:^(NSString *json) {
        auto jsonValue = GPJsonHelper::parseJson2Value([json UTF8String]);
        (target->*selector)(jsonValue);
    }];
}

#endif
