//
//  GPJsonHelper.h
//  growthpush-cocos2dx
//
//  Created by TSURUDA Ryo on 2013/12/11.
//  Copyright (c) 2013年 TSURUDA Ryo. All rights reserved.
//

#ifndef __GROWTHPUSHPLUGIN_GPJSONHELPER_H__
#define __GROWTHPUSHPLUGIN_GPJSONHELPER_H__

#include "cocos2d.h"
#include "json/document.h"

#include "GPMacros.h"

NS_GROWTHPUSH_BEGIN

class GPJsonHelper
{
public:
    /**
     Parse JSON string to Value.
     
     @param json  JSON string.
     @return parsed Value value.
     */
    static cocos2d::Value parseJson2Value(const std::string &json)
    {
        rapidjson::Document d;
        if (d.Parse<0>(json.c_str()).HasParseError()) {
            CCLOGERROR("failed to parse json:%s", d.GetParseError());
            return cocos2d::Value::Null;
        }
        return convertJson2Value(d);
    }
    
    /**
     Parse JSON string to ValueMap.
     
     @param json  JSON string.
     @return parsed ValueMap value.
     */
    static cocos2d::ValueMap parseJson2Map(const std::string &json)
    {
        return parseJson2Value(json).asValueMap();
    }
    
    /**
     Parse JSON string to ValueVector.
     
     @param json  JSON string.
     @return parsed ValueVector value.
     */
    static cocos2d::ValueVector parseJson2Vector(const std::string &json)
    {
        return parseJson2Value(json).asValueVector();
    }
    
    /**
     Parse JSON string to string.
     
     @param json  JSON string.
     @return parsed string value.
     */
    static std::string parseJson2String(const std::string &json)
    {
        return parseJson2Value(json).asString();
    }
    
    /**
     Parse JSON string to double.
     
     @param json  JSON string.
     @return parsed double value.
     */
    static double parseJson2Double(const std::string &json)
    {
        return parseJson2Value(json).asDouble();
    }
    
    /**
     Parse JSON string to int.
     
     @param json  JSON string.
     @return parsed int value.
     */
    static int parseJson2Int(const std::string &json)
    {
        return parseJson2Value(json).asInt();
    }
    
    /**
     Parse JSON string to bool.
     
     @param json  JSON string.
     @return parsed bool value.
     */
    static bool parseJson2Bool(const std::string &json)
    {
        return parseJson2Value(json).asBool();
    }
    
private:
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson.
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Value(const rapidjson::Value &v)
    {
        if (v.IsObject()) {
            return convertJson2Map(v);  // object
        } else if (v.IsArray()) {
            return convertJson2Vector(v);  // array
        } else if (v.IsString()) {
            return convertJson2String(v);  // string
        } else if (v.IsNumber()) {
            return convertJson2Double(v);  // number
        } else if (v.IsBool()) {
            return convertJson2Bool(v);  // bool
        } else if (v.IsNull()) {
            return convertJson2Null(v);  // null
        }
        CCLOGERROR("failed to convert: Unknown value type");
        return cocos2d::Value::Null;
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Map(const rapidjson::Value &v)
    {
        cocos2d::ValueMap dictionary;
        for (rapidjson::Value::ConstMemberIterator it = v.MemberonBegin(); it != v.MemberonEnd(); ++it) {
            auto value = convertJson2Value(it->value);
            dictionary.insert(std::make_pair(it->name.GetString(), value));
        }
        return cocos2d::Value(dictionary);
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Vector(const rapidjson::Value &v)
    {
        cocos2d::ValueVector array;
        for (rapidjson::Value::ConstMemberIterator it = v.MemberonBegin(); it != v.MemberonEnd(); ++it) {
            auto value = convertJson2Value(it->value);
            array.push_back(value);
        }
        return cocos2d::Value(array);
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2String(const rapidjson::Value &v)
    {
        std::string s = v.GetString();
        return cocos2d::Value(s);
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Double(const rapidjson::Value &v)
    {
        double d = v.GetDouble();
        return cocos2d::Value(d);
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Bool(const rapidjson::Value &v)
    {
        bool b = v.GetBool();
        return cocos2d::Value(b);
    }
    
    /*
     Convert type rapidjson::Value to cocos2d::Value.
     
     @param v  value of rapidjson
     @return converted Value value.
     */
    static cocos2d::Value convertJson2Null(const rapidjson::Value &v)
    {
        CC_UNUSED_PARAM(v);  // ignore value
        return cocos2d::Value::Null;
    }
};

NS_GROWTHPUSH_END

#endif  // __GROWTHPUSHPLUGIN_GPJSONHELPER_H__
