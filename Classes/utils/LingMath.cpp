//
//  LingMath.cpp
//  PuzzleBobble_6
//
//  Created by lingzerg on 14/12/26.
//
//

#include "LingMath.h"
#include<math.h>


// 通过触摸点,计算角度
float LingMath::getAngle(float x, float y,float touchx, float touchy) {
    float angle = 0;
    float a = (touchx - x);
    float b = (touchy - y);//三角形 垂直边长
    double c = sqrt(((double)(a*a + b*b))); // 三角形 斜边长
    
    angle = (float)(acos(b/c)*180)/3.14;
    if (touchx < x) {
        angle *= -1;
    }
    return angle;
}

//两点之间距离
float LingMath::getTwoPointDistans(float x, float y, float _x, float _y) {
    return  fabs(sqrt((x-_x)*(x-_x) + (y-_y)*(y-_y)));
}

// 通过速度,角度, 计算移动点在那里
LingPoint LingMath::getMovePoint(float x, float y,float speed,float angle) {
    LingPoint lp;
    lp.x =x+speed*sin(angle * M_PI / 180);
    lp.y =y+speed*cos(angle * M_PI / 180);
    return lp;
}

//通过两点（一动点）、移动物体速度、计算移动点
LingPoint LingMath::getMovePoint(float x, float y, float _x, float _y,int speed){
	LingPoint lp;
	float delta_x = _x - x;
	float delta_y = _y - y;
	float t_Distance = getTwoPointDistans(x, y,_x, _y);
	lp.x = x + speed * delta_x / t_Distance;
	lp.y = y + speed * delta_y / t_Distance;
	return lp;

}