//
//  MonsterAbilityStealth.h
//  beymac
//
//  Created by je on 5/11/15.
//
//

#ifndef __beymac__MonsterAbilityStealth__
#define __beymac__MonsterAbilityStealth__


#include "MonsterAbility.h"
#include "Monster.h"
#include "CastableBody.h"

class MonsterAbilityStealth:public MonsterAbility{
public:
    static void cast(CastableBody *target,const MonsterProperty *property);
    
    virtual float hit(float damage);
    
    virtual void attack(const int type,const int power);
    
    virtual void cancel();
    
    //当target被附加其它技能效果的时候被调用
    virtual void onOtherAbilityCast(const int type);

    
private:
    
    //是否免疫攻击
    bool isImmune;
    
    //被施法体
    CastableBody *target;
    
    //当前攻击动作
    Sequence *seqAtk;
    
    //现身时间
    float showUpTime;
    
};


#endif