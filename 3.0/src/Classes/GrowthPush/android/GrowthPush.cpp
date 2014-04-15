//
//  GrowthPush.cpp
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/08.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "GrowthPush.h"

#include <string>
#include <jni.h>

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"

#include "GPJsonHelper.h"

USING_NS_CC;
USING_NS_GROWTHPUSH;

static const char *const JavaClassName = "com/growthpush/cocos2dx/GrowthPushJNI";

// FIXME: for C++11
//static gpDidReceiveRemoteNotificationCallback s_callback = nullptr;
static cocos2d::Application *s_target = nullptr;
static GPRemoteNotificationCallFunc s_selector = nullptr;

extern "C" {
    JNIEXPORT void JNICALL Java_com_growthpush_cocos2dx_GrowthPushJNI_didReceiveRemoteNotification(JNIEnv *env, jobject thiz, jstring jJson)
    {
        // FIXME: for C++11
        /*
        if (s_callback != nullptr) {
            std::string json = JniHelper::jstring2string(jJson);
            auto jsonMap = GPJsonHelper::parseJson2Map(json.c_str());
            s_callback(jsonMap);
        }
         */
        if (s_target != nullptr && s_selector != nullptr) {
            std::string json = JniHelper::jstring2string(jJson);
            auto jsonValue = GPJsonHelper::parseJson2Value(json.c_str());
            (s_target->*s_selector)(jsonValue);
        }
    }
}

GrowthPush::GrowthPush(void)
{
}

GrowthPush::~GrowthPush(void)
{
    // FIXME: for C++11
    //s_callback = nullptr;
    s_target = nullptr;
    s_selector = nullptr;
}

void GrowthPush::initialize(int applicationId, const std::string &secret, GPEnvironment environment, bool debug)
{
    CCLOG("GrowthPush::initialize:applicationId=%d, secret=%s, environment=%d, debug=%d", applicationId, secret.c_str(), environment, debug);
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "initialize", "(ILjava/lang/String;IZ)V")) {
        jstring jSecret = t.env->NewStringUTF(secret.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, applicationId, jSecret, environment, debug);
        t.env->DeleteLocalRef(jSecret);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::registerDeviceToken(void)
{
    // Do nothing on Android
}

void GrowthPush::registerDeviceToken(const std::string &senderId)
{
    CCLOG("GrowthPush::registerDeviceToken=%s", senderId.c_str());
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "register", "(Ljava/lang/String;)V")) {
        jstring jSenderId = t.env->NewStringUTF(senderId.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jSenderId);
        t.env->DeleteLocalRef(jSenderId);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::trackEvent(const std::string &name)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "trackEvent", "(Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::trackEvent(const std::string &name, const std::string &value)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name.c_str());
        jstring jValue = t.env->NewStringUTF(value.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName, jValue);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(jValue);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setTag(const std::string &name)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "setTag", "(Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setTag(const std::string &name, const std::string &value)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "setTag", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name.c_str());
        jstring jValue = t.env->NewStringUTF(value.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName, jValue);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(jValue);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setDeviceTags(void)
{
    CCLOG("GrowthPush::setDeviceTags");
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "setDeviceTags", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::clearBadge(void)
{
    // Do nothing on Android
}

// FIXME: for C++11
//void GrowthPush::launchWithNotification(const gpDidReceiveRemoteNotificationCallback &callback)
void GrowthPush::launchWithNotification(Application *target, GPRemoteNotificationCallFunc selector)
{
    //s_callback = callback;
    CCAssert(target, "target should not be NULL");
    CCAssert(selector, "selector should not be NULL");
    
    s_target = target;
    s_selector = selector;
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "callTrackGrowthPushMessage", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif
