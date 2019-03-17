//
//  MonsterAbility.h
//  beymac
//
//  Created by je on 5/8/15.
//
//


#ifndef __beymac__MonsterAbility__
#define __beymac__MonsterAbility__

#include <cocos2d.h>
#include "MonsterProperty.h"

USING_NS_CC;

class MonsterAbility{
public:
    
    
    //技能抵消伤害
    virtual float hit(float damage)=0;
    
    virtual void attack(const int type,const int power)=0;
    
    virtual void cancel()=0;
    
    virtual void onOtherAbilityCast(const int type)=0;
    
    //    virtual void onOtherAbilityCancel()=0;
    
public:
    
    //技能编号
    int type;
    
    bool isValid;
    
    
};


#endif