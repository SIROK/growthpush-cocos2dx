//
//  GrowthPush.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef GROWTHPUSHPLUGIN_GROWTHPUSH_H_
#define GROWTHPUSHPLUGIN_GROWTHPUSH_H_

#include "cocos2d.h"

#include "GPEnvironment.h"
#include "EGPOption.h"

NS_GROWTHPUSH_BEGIN

/* APNS/GCM did receive callback function */
#define gp_remote_notification_selector(_SELECTOR) (GPRemoteNotificationCallFunc)(&_SELECTOR)
typedef void (cocos2d::CCApplication::*GPRemoteNotificationCallFunc)(cocos2d::CCDictionary *);

class CC_DLL GrowthPush
{
public:
    
    /**
     * Initialize GrowthPush instance and register the client device if not yet been registered
     *
     * @param applicationId Application ID
     * @param secret Secret key for application
     * @param environment Build configuration (debug or release)
     * @param debug Debug mode
     */
    static void initialize(int applicationId, const char *secret, GPEnvironment environment, bool debug);
    
    /**
     * Initialize GrowthPush instance and register the client device if not yet been registered
     *
     * @param applicationId Application ID
     * @param secret Secret key for application
     * @param environment Build configuration (debug or release)
     * @param debug Debug mode
     * @param option option flags
     */
    static void initialize(int applicationId, const char *secret, GPEnvironment environment, bool debug, EGPOption option);

    /**
     * Set device token
     */
    static void registerDeviceToken(void);
    
    /**
     * Set device token
     *
     * @param senderID Google Project Number
     */
    static void registerDeviceToken(const char *senderId);
    
    /**
     * Track event
     *
     * @param name Event name such as "Launch" (max 64 characters)
     */
    static void trackEvent(const char *name);
    static void trackEvent(cocos2d::CCString *name)
    {
        CCAssert(name, "name should not be NULL");
        trackEvent(name->getCString());
    }
    
    /**
     * Track event with additional information
     *
     * @param name Event name (max 64 characters)
     * @param value Additional information
     */
    static void trackEvent(const char *name, const char *value);
    static void trackEvent(cocos2d::CCString *name, cocos2d::CCString *value)
    {
        CCAssert(name, "name should not be NULL");
        CCAssert(value, "value should not be NULL");
        trackEvent(name->getCString(), value->getCString());
    }
    
    
    /**
     * Create a tag for the device
     *
     * @param name Tag name such as "Finished Tutorial" (max 64 characters)
     */
    static void setTag(const char *name);
    static void setTag(cocos2d::CCString *name)
    {
        CCAssert(name, "name should not be NULL");
        setTag(name->getCString());
    }

    
    /**
     * Create a tag with value for the device
     *
     * @param name Tag name such as "Gender" (max 64 characters)
     * @param value Tag value such as "male"
     */
    static void setTag(const char *name, const char *value);
    static void setTag(cocos2d::CCString *name, cocos2d::CCString *value)
    {
        CCAssert(name, "name should not be NULL");
        CCAssert(value, "value should not be NULL");
        setTag(name->getCString());
    }
    
    /**
     * Create tags including device model, OS version, language, time zone and app version
     */
    static void setDeviceTags(void);
    
    /**
     * Clear badge of app icon
     */
    static void clearBadge(void);
    
    /**
     * Adds an callback for the specified target.
     *
     * @param target The target which wants to observe notification events.
     * @param selector The callback function which will be invoked when the specified notification event was posted.
     */
    static void launchWithNotification(cocos2d::CCApplication *target, GPRemoteNotificationCallFunc selector);
    
private:
    GrowthPush(void);
    ~GrowthPush(void);
};

NS_GROWTHPUSH_END

#endif  // GROWTHPUSHPLUGIN_GROWTHPUSH_H_
