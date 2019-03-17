//
//  MonsterAbilityGhost.h
//  beymac
//
//  Created by je on 5/11/15.
//
//


#ifndef __beymac__MonsterAbilityGhost__
#define __beymac__MonsterAbilityGhost__

#include "MonsterAbility.h"
#include "MonsterDummy.h"
#include "CastableBody.h"

class MonsterAbilityGhost:public MonsterAbility,public MonsterDummyDelegate{
public:
    static void cast(CastableBody *target,const MonsterProperty *property);
    
    virtual float hit(float damage);
    
    virtual void attack(const int type,const int power);
    
    virtual void cancel();
    
    //被攻击时调用,damage表示所受到的伤害值.
    virtual void onHit(float damage,bool trueDamage=false);
    
    virtual void onOtherAbilityCast(const int type);
    
public:
        
    std::vector<MonsterDummy *> dummyVctor;
    
private:
    
    CastableBody *target;
};

#endif