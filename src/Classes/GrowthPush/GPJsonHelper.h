//
//  GPJsonHelper.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/11.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef GROWTHPUSHPLUGIN_GPJSONHELPER_H_
#define GROWTHPUSHPLUGIN_GPJSONHELPER_H_

#include <string>

#include "cocos2d.h"
#include "picojson.h"

#if 0x00020100 <= COCOS2D_VERSION
#define GP_CAN_USE_NUMERIC_OBJECT 1
#endif

class GPJsonHelper
{
public:
    
    /**
     Parse JSON string to CCObject(CCDictionary, CCArray, CCString, CCBool, CCDouble).
     
     @param json  JSON string
     @return CCObject* object
     */
    static cocos2d::CCObject *parseJson2CCObject(const char *json)
    {
        picojson::value v;
        std::string error;
        
        /* parse json */
        picojson::parse(v, json, json + strlen(json), &error);
        if (!error.empty()) {
            CCLOGERROR("failed to parse json:%s", error.c_str());
            return NULL;
        }
        return convertJson2CCObject(v);
    }
    
    /**
     Parse JSON string to CCDictionary.
     
     @param json  JSON string
     @return CCDictionary* object
     */
    static cocos2d::CCDictionary *parseJson2CCDictionary(const char *json)
    {
        return dynamic_cast<cocos2d::CCDictionary *>(parseJson2CCObject(json));
    }
    
    /**
     Parse JSON string to CCArray.
     
     @param json  JSON string
     @return CCArray* object
     */
    static cocos2d::CCArray *parseJson2CCArray(const char *json)
    {
        return dynamic_cast<cocos2d::CCArray *>(parseJson2CCObject(json));
    }
    
    /**
     Parse JSON string to CCString.
     
     @param json  JSON string
     @return CCString* object
     */
    static cocos2d::CCString *parseJson2CCString(const char *json)
    {
        return dynamic_cast<cocos2d::CCString *>(parseJson2CCObject(json));
    }
    
#ifdef GP_CAN_USE_NUMERIC_OBJECT
    /**
     Parse JSON string to CCDouble.
     
     @param json  JSON string
     @return CCDouble* object
     */
    static cocos2d::CCDouble *parseJson2CCDouble(const char *json)
    {
        return dynamic_cast<cocos2d::CCDouble *>(parseJson2CCObject(json));
    }
    
    /**
     Parse JSON string to CCBool.
     
     @param json  JSON string
     @return CCBool* object
     */
    static cocos2d::CCBool *parseJson2CCBool(const char *json)
    {
        return dynamic_cast<cocos2d::CCBool *>(parseJson2CCObject(json));
    }
#endif
    
private:
    
    /*
     Convert type picojson::value to CCObject.
     
     @param v  value of picojson
     @return CCObject* object
     */
    static cocos2d::CCObject *convertJson2CCObject(picojson::value v)
    {
        if (v.is<bool>()) {
            return convertJson2CCBool(v);  // bool
        } else if (v.is<double>()) {
            return convertJson2CCDouble(v);  // number
        } else if (v.is<std::string>()) {
            return convertJson2CCString(v);  // string
        } else if (v.is<picojson::array>()) {
            return convertJson2CCArray(v);  // array
        } else if (v.is<picojson::object>()) {
            return convertJson2CCDictionary(v);  // object
        } else if (v.is<picojson::null>()) {
            return convertJson2Null(v);  // null
        }
        
        CCLOGERROR("failed to convert: Unknown object");
        return NULL;
    }
    
    /*
     Convert type picojson::value to CCDictionary.
     
     @param v  value of picojson
     @return CCDictionry* object
     */
    static cocos2d::CCObject *convertJson2CCDictionary(picojson::value v)
    {
        cocos2d::CCDictionary *pDictionary = new cocos2d::CCDictionary();
        if (!pDictionary) {
            return NULL;
        }
        picojson::object obj = v.get<picojson::object>();
        for (picojson::object::iterator it = obj.begin(); it != obj.end(); ++it) {
            cocos2d::CCObject *pObject = convertJson2CCObject(it->second);
            if (!pObject) {
                CC_SAFE_DELETE(pDictionary);
                return NULL;
            }
            pDictionary->setObject(pObject, it->first);
        }
        return pDictionary;
    }
    
    /*
     Convert type picojson::value to CCArray.
     
     @param v  value of picojson
     @return CCArray* object
     */
    static cocos2d::CCObject *convertJson2CCArray(picojson::value v)
    {
        cocos2d::CCArray *pArray = new cocos2d::CCArray();
        if (!pArray || !pArray->init()) {
            CC_SAFE_DELETE(pArray);
            return NULL;
        }
        picojson::array arr = v.get<picojson::array>();
        for (picojson::array::iterator it = arr.begin(); it != arr.end(); ++it) {
            cocos2d::CCObject *pObject = convertJson2CCObject(*it);
            if (!pObject) {
                CC_SAFE_DELETE(pArray);
                return NULL;
            }
            pArray->addObject(pObject);
        }
        return pArray;
    }
    
    /*
     Convert type picojson::value to CCString.
     
     @param v  value of picojson
     @return CCString* object
     */
    static cocos2d::CCObject *convertJson2CCString(picojson::value v)
    {
        std::string s = v.get<std::string>();
        return new cocos2d::CCString(s);
    }
    
    /*
     Convert type picojson::value to CCDouble or CCString.
     
     @param v  value of picojson
     @return CCDouble* or CCString* object
     */
    static cocos2d::CCObject *convertJson2CCDouble(picojson::value v)
    {
        double d = v.get<double>();
#ifdef GP_CAN_USE_NUMERIC_OBJECT
        return new cocos2d::CCDouble(d);
#else
        cocos2d::CCString *pString = new cocos2d::CCString();
        if (!pString || !pString->initWithFormat("%lf", d)) {
            CC_SAFE_DELETE(pString);
            return NULL;
        }
        return pString;
#endif
    }
    
    /*
     Convert type picojson::value to CCBool or CCString.
     
     @param v  value of picojson
     @return CCBool* or CCString* object
     */
    static cocos2d::CCObject *convertJson2CCBool(picojson::value v)
    {
        bool b = v.get<bool>();
#ifdef GP_CAN_USE_NUMERIC_OBJECT
        return new cocos2d::CCBool(b);
#else
        return new cocos2d::CCString(b ? "true" : "false");
#endif
    }
    
    /*
     Convert type picojson::value to CCObject. (Because cannot use CCNull Object.)
     
     @param v  value of picojson
     @return CCObject* object
     */
    static cocos2d::CCObject *convertJson2Null(picojson::value v)
    {
        CC_UNUSED_PARAM(v);  // ignore value
        return new cocos2d::CCObject();
    }
};

#endif  // GROWTHPUSHPLUGIN_GPJSONHELPER_H_
