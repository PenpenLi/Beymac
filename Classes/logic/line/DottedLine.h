//
//  DottedLine.h
//  WaterWars
//
//  Created by lingzerg on 15/3/17.
//
//

#ifndef __WaterWars__DottedLine__
#define __WaterWars__DottedLine__

#include "cocos2d.h"
USING_NS_CC;

class DottedLine : public Sprite
{
public:
    DottedLine();
    ~DottedLine();
    static DottedLine* createNode();
    virtual bool init();
    CREATE_FUNC(DottedLine);
    
private:
    void initData();
};

#endif /* defined(__WaterWars__DottedLine__) */