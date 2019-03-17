//
//  Jishiqi.h
//  WaterWars
//
//  Created by lingzerg on 15/3/23.
//
//

#ifndef __WaterWars__Jishiqi__
#define __WaterWars__Jishiqi__

#include "cocos2d.h"
#include "CommonHeader.h"
USING_NS_CC;

class Jishiqi : public Node
{
public:
    
    void setText(const std::string& text);
    void setBg(int type);
    Jishiqi();
    ~Jishiqi();
    static Jishiqi* createNode();
    virtual bool init();
    CREATE_FUNC(Jishiqi);
private :
    LabelAtlas *label;
    Sprite *bg;
private:
    void initData();
};

#endif /* defined(__WaterWars__Jishiqi__) */