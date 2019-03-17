//
//  Macro.h
//  PuzzleBobble_6
//
//  Created by lingzerg on 14/12/24.
//
//

#ifndef __WaterWars__Macro__
#define __WaterWars__Macro__

#include "cocos2d.h"

USING_NS_CC;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 1136

#define MYSIZE Director::getInstance()->getVisibleSize()
#define MYORIGIN Director::getInstance()->getVisibleOrigin()

#define SCREEN_CENTER getScreenCenter()
#define SCREEN_LEFT_DOWN getScreenLeftDown()
#define SCREEN_RIGHT_DOWN getScreenRightDown()
#define SCREEN_LEFT_UP getScreenLeftUp()
#define SCREEN_RIGHT_UP getScreenRightUp()

#define BUTTON_ISZOOMONTOUCHDOWN true
#define TOUCHPRIORITY_0 0

#define PAY_MODE 0

Point getScreenCenter();

Point getScreenLeftDown();

Point getScreenRightDown();

Point getScreenLeftUp();

Point getScreenRightUp();


namespace NUM2STR {
    
    template<typename T>
    std::string toString(T arg)
    {
        std::stringstream ss;
        ss << arg;
        return ss.str();
    }
}

#define NUM_TO_STR(value) (NUM2STR::toString(value))
#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")


#endif /* defined(__WaterWars__Macro__) */