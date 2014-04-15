package com.growthpush.cocos2dx;

public class OptionJNI {
    public static final int none = 0;
    public static final int trackLaunch = 1 << 0;
    public static final int tagDevie = 1 << 1;
    public static final int tagOS = 1 << 2;
    public static final int tagLanguage = 1 << 3;
    public static final int tagTimeZone = 1 << 4;
    public static final int tagVersion = 1 << 5;
    public static final int tagBuild = 1 << 6;
    public static final int trackAll = trackLaunch;
    public static final int tagAll = tagDevie | tagOS | tagLanguage | tagTimeZone | tagVersion | tagBuild;
    public static final int all = trackAll | tagAll;
}
