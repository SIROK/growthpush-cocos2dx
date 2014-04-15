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
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);

    int appID = YOUR_APP_ID;
    const char *secrect = "YOUR_APP_SECRET";
    GPEnvironment environment = GPEnvironmentDevelopment;
    bool debug = true;
    const char *senderID = "YOUR_SENDER_ID";
    
    GrowthPush::initialize(appID, secrect, environment, debug);
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

void AppDelegate::didReceiveRemoteNotification(Value json)
{
    // ex.) {"aps":{"badge":1,"sound":"default","alert":"Message"},"growthpush":{"notificationId":1234}}
    CCLOG("%s", json.getDescription().c_str());
    auto growthpush = json.asValueMap()["growthpush"].asValueMap();
    int notificationId = growthpush["notificationId"].asInt();
    GrowthPush::trackEvent(StringUtils::format("Launch via push notification %d", notificationId));
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
