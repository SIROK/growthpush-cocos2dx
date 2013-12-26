//
//  GPMacros.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/07.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef GROWTHPUSHPLUGIN_GPMACROS_H_
#define GROWTHPUSHPLUGIN_GPMACROS_H_

#ifdef __cplusplus
    #define NS_GROWTHPUSH_BEGIN    namespace growthpush {
    #define NS_GROWTHPUSH_END      }
    #define USING_NS_GROWTHPUSH    using namespace growthpush
#else
    #define NS_GROWTHPUSH_BEGIN
    #define NS_GROWTHPUSH_END
    #define USING_NS_GROWTHPUSH
#endif

#endif  // GROWTHPUSHPLUGIN_GPMACROS_H_
