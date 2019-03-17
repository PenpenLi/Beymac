//
//  MonsterAbilityLightShield.h
//  beymac
//
//  Created by je on 5/11/15.
//
//

#ifndef __beymac__MonsterAbilityLightShield__
#define __beymac__MonsterAbilityLightShield__

#include "MonsterAbility.h"
#include "Health.h"
#include "CastableBody.h"

USING_NS_CC;

class MonsterAbilityLightShield:public MonsterAbility{
public:
    //参数：node父节点，power护盾强度，showValue表示显示能量条，主体需要，分身不需要
    static void cast(CastableBody *target,const MonsterProperty *property,bool showValue=false);
    
    virtual float hit(float damage);
    
    virtual void attack(const int type,const int power);
    
    virtual void cancel();
    
    virtual void onOtherAbilityCast(const int type);
    
public:
    float powerOrigin;    //初始强度
    
    float power;  //现在强度
    
    
    
private:
    
    //能量条
    Health *shieldPower;    
    
    Sprite *lightShield;
    
    CastableBody *target;
};


#endif








