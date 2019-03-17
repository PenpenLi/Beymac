//
//  MonsterAbilityGhost.cpp
//  beymac
//
//  Created by je on 5/11/15.
//
//

#include "MonsterAbilityGhost.h"
#include "MonsterDummy.h"
#include "Monster.h"
#include "MonsterAbilityLightShield.h"

//隐身和假身透明度
#define STEALTH_OPACITY 200

void MonsterAbilityGhost::cast(CastableBody *target,const MonsterProperty *property)
{
    auto ghost=new MonsterAbilityGhost();
    log("技能：假身");
    ghost->type=3;
    
    //将假身加入 node对象。
    target->setPositionX(target->getPositionX() -100);
    
    //加入分身1
    auto dummy=new MonsterDummy(property,ghost);
    dummy->setPosition(target->getPositionX()+200,target->getPositionY()+0);
        
    dummy->setOpacity(STEALTH_OPACITY);
    
    
    
    target->getParent()->addChild(dummy);
    ghost->dummyVctor.push_back(dummy);
    
    
    //回调
    target->onCast(ghost);
    
    //配置
    ghost->target=target;
    dummy->enterBattle();
    ghost->isValid=true;
}


float MonsterAbilityGhost::hit(float damage)
{
    return damage;
}

void MonsterAbilityGhost::attack(const int type,const int power)
{
    dummyVctor.at(0)->attack(type, power);
}

void MonsterAbilityGhost::cancel()
{
    dummyVctor.at(0)->removeFromParentAndCleanup(true);
    
    //回调
    target->onCancel(this->type);
}

//被攻击时调用,damage表示所受到的伤害值.
void MonsterAbilityGhost::onHit(float damage,bool trueDamage)
{
    //不受伤害，所以不需要处理
    
    
}

void MonsterAbilityGhost::onOtherAbilityCast(const int type)
{
    if(type==MONSTER_ABILITY_LIGHT_SHIELD){
        MonsterAbilityLightShield::cast(dummyVctor.at(0), dummyVctor.at(0)->property);
    }
    
}




