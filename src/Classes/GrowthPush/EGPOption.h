//
//  EGPOption.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef GROWTHPUSHPLUGIN_EGPOPTION_H_
#define GROWTHPUSHPLUGIN_EGPOPTION_H_

#include "GPMacros.h"

NS_GROWTHPUSH_BEGIN

typedef enum EGPOption {
    EGPOptionNone = 0,
    EGPOptionTrackLaunch = 1 << 0,
    EGPOptionTagDevie = 1 << 1,
    EGPOptionTagOS = 1 << 2,
    EGPOptionTagLanguage = 1 << 3,
    EGPOptionTagTimeZone = 1 << 4,
    EGPOptionTagVersion = 1 << 5,
    EGPOptionTagBuild = 1 << 6,
    EGPOptionTrackAll = EGPOptionTrackLaunch,
    EGPOptionTagAll = EGPOptionTagDevie | EGPOptionTagOS | EGPOptionTagLanguage | EGPOptionTagTimeZone | EGPOptionTagVersion | EGPOptionTagBuild,
    EGPOptionAll = EGPOptionTrackAll | EGPOptionTagAll,
} EGPOption;

NS_GROWTHPUSH_END

#endif  // GROWTHPUSHPLUGIN_EGPOPTION_H_
