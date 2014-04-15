//
//  GPEnvironment.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef __GROWTHPUSHPLUGIN_GPENVIRONMENT_H__
#define __GROWTHPUSHPLUGIN_GPENVIRONMENT_H__

#include "GPMacros.h"

NS_GROWTHPUSH_BEGIN

typedef enum GPEnvironment {
    GPEnvironmentUnknown = 0,
    GPEnvironmentDevelopment,
    GPEnvironmentProduction,
} GPEnvironment;

NS_GROWTHPUSH_END

#endif // __GROWTHPUSHPLUGIN_GPENVIRONMENT_H__
