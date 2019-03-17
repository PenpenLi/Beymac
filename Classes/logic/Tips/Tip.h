//
//  Tips.h
//  WaterWars
//
//  Created by lingzerg on 15/3/16.
//
//

#ifndef __WaterWars__Tips__
#define __WaterWars__Tips__

#include "cocos2d.h"
#include "Box.h"

USING_NS_CC;


class Tip : public Sprite {
public :
    Tip();
    ~Tip();
    static Tip* createMyTip();
    virtual bool init();
    
    void setTip(BoxType type);
    
private:
    Sprite *tipType;
    
    void initData();
};

#endif /* defined(__WaterWars__Tips__) */
