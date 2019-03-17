//
//  PropCd.h
//  BeyMac
//
//  Created by lingzerg on 15/5/12.
//
//

#ifndef __BeyMac__PropCd__
#define __BeyMac__PropCd__

#include "cocos2d.h"

USING_NS_CC;

class PropCd : public Sprite
{
public:
    PropCd();
    ~PropCd();
    static PropCd* createSprite();
    virtual bool init();
    CREATE_FUNC(PropCd);
    void onUpdate(float delta);
    
    void showTimer1();
    float getTimer1();
    
    void showTimer2();
    float getTimer2();
    
    void showTimer3();
    float getTimer3();
    
    void showTimer4();
    float getTimer4();
    
    void showHammer();
    float getTimerHammer();
    
private:
    float timer1;
    ProgressTimer *mypro1;
    
    float timer2;
    ProgressTimer *mypro2;
    
    float timer3;
    ProgressTimer *mypro3;
    
    float timer4;
    ProgressTimer *mypro4;
    
    float timerHammer;
    ProgressTimer *myproHammer;
    
    bool isTimer1;
    bool isTimer2;
    bool isTimer3;
    bool isTimer4;
    bool isTimerHammer;
    
    void initData();
};

#endif /* defined(__BeyMac__PropCd__) */
