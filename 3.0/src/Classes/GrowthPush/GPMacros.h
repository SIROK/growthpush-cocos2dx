//
//  GPMacros.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef __GROWTHPUSHPLUGIN_GPMACROS_H__
#define __GROWTHPUSHPLUGIN_GPMACROS_H__

#ifdef __cplusplus
    #define NS_GROWTHPUSH_BEGIN    namespace growthpush {
    #define NS_GROWTHPUSH_END      }
    #define USING_NS_GROWTHPUSH    using namespace growthpush
#else
    #define NS_GROWTHPUSH_BEGIN
    #define NS_GROWTHPUSH_END
    #define USING_NS_GROWTHPUSH
#endif

#endif  // __GROWTHPUSHPLUGIN_GPMACROS_H__
