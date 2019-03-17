//
//  MonsterAbilityCopy.cpp
//  beymac
//
//  Created by je on 5/11/15.
//
//

#include "MonsterAbilityCopy.h"
#include "Monster.h"
#include "MonsterAbilityLightShield.h"
#include "MonsterAbilityStealth.h"


void MonsterAbilityCopy::cast(CastableBody *target,const MonsterProperty *property)
{
    auto copy=new MonsterAbilityCopy();
    log("技能：分身");
    copy->type=4;
        
    //加入分身1
    auto dummy=new MonsterDummy(property,copy);
    dummy->setPosition(target->getPositionX()-200,target->getPositionY()+0);
    target->getParent()->addChild(dummy);
    copy->dummyVctor.push_back(dummy);
    
    //加入分身2
    auto dummy2=new MonsterDummy(property,copy);
    dummy2->setPosition(target->getPositionX()+200,target->getPositionY()+0);
    target->getParent()->addChild(dummy2);
    copy->dummyVctor.push_back(dummy2);
    
    
    //回调
    target->onCast(copy);
    
    //配置
    copy->target=target;
    dummy->enterBattle();
    dummy2->enterBattle();
    copy->isValid=true;
}


float MonsterAbilityCopy::hit(float damage)
{
    return damage;
}

void MonsterAbilityCopy::attack(const int type,const int power)
{
    dummyVctor.at(0)->attack(type, power);
    dummyVctor.at(1)->attack(type, power);
}

void MonsterAbilityCopy::cancel()
{
    dummyVctor.at(0)->removeFromParentAndCleanup(true);
    dummyVctor.at(1)->removeFromParentAndCleanup(true);
    
    //回调
    target->onCancel(this->type);
}

//分身被直接攻击
void MonsterAbilityCopy::onHit(float damage,bool trueDamage)
{
    
}

void MonsterAbilityCopy::onOtherAbilityCast(const int type)
{
    if(type==MONSTER_ABILITY_LIGHT_SHIELD){
        MonsterAbilityLightShield::cast(dummyVctor.at(0), dummyVctor.at(0)->property);
        MonsterAbilityLightShield::cast(dummyVctor.at(1), dummyVctor.at(1)->property);
    }
    
    if(type==MONSTER_ABILITY_STEALTH){
        MonsterAbilityStealth::cast(dummyVctor.at(0),dummyVctor.at(0)->property);
        MonsterAbilityStealth::cast(dummyVctor.at(1),dummyVctor.at(1)->property);
    }
    
}



