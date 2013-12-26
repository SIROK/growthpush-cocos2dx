//
//  GrowthPush.cpp
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/08.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#if defined(ANDROID)

#include "GrowthPush.h"

#include <string>
#include <jni.h>

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"

#include "GPJsonHelper.h"

USING_NS_CC;
USING_NS_GROWTHPUSH;

static const char *const JavaClassName = "com/growthpush/cocos2dx/GrowthPushJNI";

static cocos2d::CCApplication *s_target = NULL;
static GPRemoteNotificationCallFunc s_selector = NULL;

extern "C" {
    JNIEXPORT void JNICALL Java_com_growthpush_cocos2dx_GrowthPushJNI_didReceiveRemoteNotification(JNIEnv *env, jobject thiz, jstring jJson)
    {
        if (s_target != NULL && s_selector != NULL) {
            std::string json = JniHelper::jstring2string(jJson);
            CCDictionary *jsonDict = GPJsonHelper::parseJson2CCDictionary(json.c_str());
            (s_target->*s_selector)(jsonDict);
        }
    }
}

GrowthPush::GrowthPush(void)
{
}

GrowthPush::~GrowthPush(void)
{
    s_target = NULL;
    s_selector = NULL;
}

void GrowthPush::initialize(int applicationId, const char *secret, growthpush::GPEnvironment environment, bool debug)
{
    CCAssert(secret, "secret should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "initialize", "(ILjava/lang/String;IZ)V")) {
        jstring jSecret = t.env->NewStringUTF(secret);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, applicationId, jSecret, environment, debug);
        t.env->DeleteLocalRef(jSecret);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::initialize(int applicationId, const char *secret, GPEnvironment environment, bool debug, EGPOption option)
{
    CC_UNUSED_PARAM(option);
    initialize(applicationId, secret, environment, debug);  // ignore "option"
}

void GrowthPush::registerDeviceToken(void)
{
    // Do nothing on Android
}

void GrowthPush::registerDeviceToken(const char *senderId)
{
    CCAssert(senderId, "senderId should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "register", "(Ljava/lang/String;)V")) {
        jstring jSenderId = t.env->NewStringUTF(senderId);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jSenderId);
        t.env->DeleteLocalRef(jSenderId);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::trackEvent(const char *name)
{
    CCAssert(name, "name should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "trackEvent", "(Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::trackEvent(const char *name, const char *value)
{
    CCAssert(name, "name should not be NULL");
    CCAssert(value, "value should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name);
        jstring jValue = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName, jValue);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(jValue);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setTag(const char *name)
{
    CCAssert(name, "name should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "setTag", "(Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setTag(const char *name, const char *value)
{
    CCAssert(name, "name should not be NULL");
    CCAssert(value, "value should not be NULL");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, JavaClassName, "setTag", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jName = t.env->NewStringUTF(name);
        jstring jValue = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jName, jValue);
        t.env->DeleteLocalRef(jName);
        t.env->DeleteLocalRef(jValue);
        t.env->DeleteLocalRef(t.classID);
    }
}

void GrowthPush::setDeviceTags(void)
{
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


void GrowthPush::launchWithNotification(CCApplication *target, GPRemoteNotificationCallFunc selector)
{
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
