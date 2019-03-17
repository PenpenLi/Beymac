//
//  MonsterAbilityNormal.h
//  beymac
//
//  Created by je on 5/8/15.
//
//

#ifndef __beymac__MonsterAbilityNormal__
#define __beymac__MonsterAbilityNormal__

#include "MonsterAbility.h"
#include "Monster.h"


class MonsterAbilityNormal:public MonsterAbility{
    Monster *monster;
    virtual float hit(float damage);
    virtual void attack(const int type,const int power);
    virtual void cancel();
    virtual void onOtherAbilityCast(const int type);
};


#endif