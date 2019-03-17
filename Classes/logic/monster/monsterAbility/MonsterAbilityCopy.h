//
//  MonsterAbilityCopy.h
//  beymac
//
//  Created by je on 5/11/15.
//
//

#ifndef __beymac__MonsterAbilityCopy__
#define __beymac__MonsterAbilityCopy__

#include "MonsterAbility.h"
#include "MonsterDummy.h"
#include "CastableBody.h"


class MonsterAbilityCopy:public MonsterAbility,public MonsterDummyDelegate{
public:
    static void cast(CastableBody *target,const MonsterProperty *property);
    
    virtual float hit(float damage);
    
    virtual void attack(const int type,const int power);
    
    virtual void cancel();
    
    //分身承受攻击
    virtual void onHit(float damage,bool trueDamage=false);
    
    virtual void onOtherAbilityCast(const int type);
public:
    
    std::vector<MonsterDummy *> dummyVctor;
    
private:
    
    CastableBody *target;
};


#endif