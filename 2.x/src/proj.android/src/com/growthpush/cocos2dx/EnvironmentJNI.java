package com.growthpush.cocos2dx;

import com.growthpush.model.Environment;

public class EnvironmentJNI {
    /*
     * Convert GPEnvironment to Environment
     * 
     * @param environment GPEnvironment value of Cocos2d-x
     * @return Environment value of Java
     */
    public static Environment environmentFromCocos(int environment) {
        if (environment == Environment.development.ordinal()) {
            return Environment.development;
        } else if (environment == Environment.production.ordinal()) {
            return Environment.production;
        }
        throw new IllegalArgumentException("Unknown environment");
    }
}
