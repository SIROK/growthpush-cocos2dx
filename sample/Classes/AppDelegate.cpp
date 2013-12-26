#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "GrowthPush.h"

USING_NS_CC;
USING_NS_GROWTHPUSH;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    int appID = YOUR_APP_ID;
    const char *secrect = "YOUR_APP_SECRET";
    GPEnvironment environment = GPEnvironmentDevelopment;
    bool debug = true;
    EGPOption option = EGPOptionAll;
    const char *senderID = "YOUR_SENDER_ID";
    
    GrowthPush::initialize(appID, secrect, environment, debug, option);
    GrowthPush::registerDeviceToken(senderID);
    GrowthPush::setDeviceTags();
    GrowthPush::trackEvent("Event");
    GrowthPush::trackEvent("Event", "Value");
    GrowthPush::setTag("Tag");
    GrowthPush::setTag("Tag", "Value");
    GrowthPush::clearBadge();
    
    GrowthPush::launchWithNotification(this, gp_remote_notification_selector(AppDelegate::didReceiveRemoteNotification));
    
    return true;
}

void AppDelegate::didReceiveRemoteNotification(CCDictionary *json)
{
    CCDictionary *growthpush = (CCDictionary *)json->objectForKey("growthpush");
    if (growthpush) {
        CCObject *notificationIDObject = growthpush->objectForKey("notificationId");
        if (notificationIDObject) {
#if 0x00020100 <= COCOS2D_VERSION
            int notificationID = ((CCDouble *)notificationIDObject)->getValue();
#else
            int notificationID = ((CCString *)notificationIDObject)->intValue();
#endif
            GrowthPush::trackEvent(CCString::createWithFormat("Launch via push notification %d", notificationID));
        } else {
            GrowthPush::trackEvent("Launch");
        }
    } else {
        GrowthPush::trackEvent("Launch");
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
