//
//  LingMath.h
//  PuzzleBobble_6
//
//  Created by lingzerg on 14/12/26.
//
//

#ifndef __PuzzleBobble_6__LingMath__
#define __PuzzleBobble_6__LingMath__


#include "cocos2d.h"

USING_NS_CC;

struct LingPoint
{
    float x;
    float y;
};

class LingMath {
    public :
        static float getAngle(float x, float y,float touchx, float touchy);             // 通过触摸点,计算角度
        static float getTwoPointDistans(float x, float y, float _x, float _y);          //两点之间距离
        static LingPoint getMovePoint(float x, float y,float speed,float angle);        // 通过速度,角度, 计算移动点在那里
		static LingPoint getMovePoint(float x, float y, float _x, float _y, int speed); //通过两点（一动点）、移动物体速度、计算移动点
};

#endif /* defined(__PuzzleBobble_6__LingMath__) */
