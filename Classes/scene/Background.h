//
//  HomeBackground.h
//  WaterWars
//
//  Created by je on 3/23/15.
//
//

#include "cocos2d.h"

USING_NS_CC;

class Background:public Layer{
public:
    //创建蓝色背景
    static Background *createBackground();
    
    virtual bool init();
    
    //使用云朵
    void addCloud();
    
    //使用波浪
    void addWave();
    
};
