//
//  Helper.cpp
//  PopStar
//
//  Created by wang on 14/12/26.
//
//

#include "Macro.h"

Point getScreenCenter()
{
    Size size = MYSIZE;
    Point origin = MYORIGIN;
    return Vec2(size.width/2+origin.x, size.height/2+origin.y);
    
}
Point getScreenLeftDown()
{
    return MYORIGIN;
}
Point getScreenRightDown()
{
    Size size = MYSIZE;
    Point origin = MYORIGIN;
    return Vec2(size.width+origin.x, origin.y);
}
Point getScreenLeftUp()
{
    Size size = MYSIZE;
    Point origin = MYORIGIN;
    return Vec2(origin.x, size.height+origin.y);
}
Point getScreenRightUp()
{
    Size size = MYSIZE;
    Point origin = MYORIGIN;
    return Vec2(size.width+origin.x, size.height+origin.y);
}