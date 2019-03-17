//
//  PropCd.cpp
//  BeyMac
//
//  Created by lingzerg on 15/5/12.
//
//

#include "PropCd.h"
PropCd::PropCd()
{
    
}

PropCd::~PropCd()
{
    
}

PropCd* PropCd::createSprite()
{
    auto node = PropCd::create();
    return node;
}

bool PropCd::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void PropCd::initData()
{
    Sprite *loading = Sprite::create("img_prop_cd.png");
    
    mypro1 = ProgressTimer::create(loading);
    mypro1->setPosition(80, 60);
    mypro1->setType(ProgressTimer::Type::BAR);
    mypro1->setMidpoint(Vec2(0,0));
    mypro1->setBarChangeRate(Vec2(0,1));
    mypro1->setPercentage(0);
    addChild(mypro1);
    
    mypro2 = ProgressTimer::create(loading);
    mypro2->setPosition(240,60);
    mypro2->setType(ProgressTimer::Type::BAR);
    mypro2->setMidpoint(Vec2(0,0));
    mypro2->setBarChangeRate(Vec2(0,1));
    mypro2->setPercentage(0);
    addChild(mypro2);
    
    mypro3 = ProgressTimer::create(loading);
    mypro3->setPosition(400,60);
    mypro3->setType(ProgressTimer::Type::BAR);
    mypro3->setMidpoint(Vec2(0,0));
    mypro3->setBarChangeRate(Vec2(0,1));
    mypro3->setPercentage(0);
    addChild(mypro3);
    
    mypro4 = ProgressTimer::create(loading);
    mypro4->setPosition(560,60);
    mypro4->setType(ProgressTimer::Type::BAR);
    mypro4->setMidpoint(Vec2(0,0));
    mypro4->setBarChangeRate(Vec2(0,1));
    mypro4->setPercentage(0);
    addChild(mypro4);
    
    
    myproHammer = ProgressTimer::create(loading);
    myproHammer->setPosition(400,60);
    myproHammer->setType(ProgressTimer::Type::BAR);
    myproHammer->setMidpoint(Vec2(0,0));
    myproHammer->setBarChangeRate(Vec2(0,1));
    myproHammer->setPercentage(0);
    addChild(myproHammer);
    
    isTimer1 = false;
    isTimer2 = false;
    isTimer3 = false;
    isTimer4 = false;
    isTimerHammer = false;
    
}


void PropCd::showHammer() {
    
    timerHammer = 0;
    myproHammer->setPercentage(100);
    isTimerHammer = true;
}

float PropCd::getTimerHammer() {
    return myproHammer->getPercentage();
}

void PropCd::showTimer1() {
    
    timer1 = 0;
    mypro1->setPercentage(100);
    isTimer1 = true;
}

float PropCd::getTimer1() {
    return mypro1->getPercentage();
}

void PropCd::showTimer2() {
    
    timer2 = 0;
    mypro2->setPercentage(100);
    isTimer2 = true;
}


float PropCd::getTimer2() {
    return mypro2->getPercentage();
}

void PropCd::showTimer3() {
    
    timer3 = 0;
    mypro3->setPercentage(100);
    isTimer3 = true;
}

float PropCd::getTimer3() {
    return mypro3->getPercentage();
}

void PropCd::showTimer4() {
    
    timer4 = 0;
    mypro4->setPercentage(100);
    isTimer4 = true;
}

float PropCd::getTimer4() {
    return mypro4->getPercentage();
}




void PropCd::onUpdate(float delta) {
    
    if (isTimer1) {
        timer1 += delta;
        if (mypro1->getPercentage() > 0 && timer1 < 5000) {
            mypro1->setPercentage(100 - timer1/3 * 100);
        } else {
            mypro1->setPercentage(0);
            timer1 = 0;
            isTimer1 = false;
        }
    }
    
    if (isTimer2) {
        timer2 += delta;

        if (mypro2->getPercentage() > 0 && timer2 < 5000) {
            mypro2->setPercentage(100 - timer2/3 * 100);
        } else {
            mypro2->setPercentage(0);
            timer2 = 0;
            isTimer2 = false;
        }
    }
    
    if (isTimer3) {
        timer3 += delta;
        
        if (mypro3->getPercentage() > 0 && timer3 < 5000) {
            mypro3->setPercentage(100 - timer3/3 * 100);
        } else {
            mypro3->setPercentage(0);
            timer3 = 0;
            isTimer3 = false;
        }
    }
    
    if (isTimer4) {
        timer4 += delta;
        
        if (mypro4->getPercentage() > 0 && timer4 < 5000) {
            mypro4->setPercentage(100 - timer4/3 * 100);
        } else {
            mypro4->setPercentage(0);
            timer4 = 0;
            isTimer4 = false;
        }
    }
    
    if (isTimerHammer) {
        timerHammer += delta;
        
        if (myproHammer->getPercentage() > 0 && timerHammer < 1000) {
            myproHammer->setPercentage(100 - timerHammer * 100);
        } else {
            myproHammer->setPercentage(0);
            timerHammer = 0;
            isTimerHammer = false;
        }
    }
}

