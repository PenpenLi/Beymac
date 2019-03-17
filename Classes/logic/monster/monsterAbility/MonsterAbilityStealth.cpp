//
//  MonsterAbilityStealth.cpp
//  beymac
//
//  Created by je on 5/11/15.
//
//

#include "MonsterAbilityStealth.h"
#include "MonsterAbilityCopy.h"


void MonsterAbilityStealth::cast(CastableBody *target,const MonsterProperty *property)
{
    
    //主体隐身，假身不管。
    
    auto stealth=new MonsterAbilityStealth();
    log("技能：隐身,现身时间:%f/%f",property->showUpTime,property->atkSpeed);
    stealth->type=5;
    
    stealth->showUpTime=property->showUpTime;
    
    //主体隐身
    
    log("本体隐身");
    target->setVisible(false);
    
    
    //回调
    target->onCast(stealth);
    
    //配置
    stealth->target=target;
    stealth->isValid=true;
}

float MonsterAbilityStealth::hit(float damage)
{
    if(isImmune){
        log("Immune");
        return 0;
    }else{
        return damage;
    }
}

void MonsterAbilityStealth::attack(const int type,const int power)
{
    //boss现身攻击
    log("boss现身攻击");
    this->target->setVisible(true);
    
    this->isImmune=false;
    
    auto func1=CallFunc::create([&](){
        log("重新隐身");
        this->isImmune=true;
        this->target->setVisible(false);
    });
    
    seqAtk=Sequence::create(DelayTime::create(this->showUpTime),func1, NULL);
    
    this->target->runAction(seqAtk);
    
    
}

void MonsterAbilityStealth::cancel()
{
    //回调
    target->onCancel(this->type);
    
    if(seqAtk){
        this->target->stopAction(seqAtk);
    }
    //取消隐身效果
    target->setVisible(true);
    
}

void MonsterAbilityStealth::onOtherAbilityCast(const int type)
{
    
}