//
//  MonsterAbilityLightShield.cpp
//  beymac
//
//  Created by je on 5/11/15.
//
//


#include "MonsterAbilityLightShield.h"
#include "MonsterAbilityCopy.h"
#include "CommonHeader.h"
#include "Monster.h"

//隐身和假身透明度
#define STEALTH_OPACITY 120

USING_NS_CC;

void MonsterAbilityLightShield::cast(CastableBody *target,const MonsterProperty *property,bool showValue)
{
    auto shield=new MonsterAbilityLightShield();
    log("技能：光盾,强度:%f",property->shieldValue);
    shield->type=2;
    
    //护盾强度
    shield->powerOrigin=property->shieldValue;
    shield->power=shield->powerOrigin;
    
    //加入光盾
    shield->lightShield=Sprite::create("img_boss_shield.png");
    shield->lightShield->setOpacity(STEALTH_OPACITY);
    target->addChild(shield->lightShield);
    
    if(showValue){
        //加护盾能量条
        shield->shieldPower=Health::createNode("img_shield_life.png","img_shield_life_case.png");
        shield->shieldPower->setOriginHealth(shield->powerOrigin);
        shield->shieldPower->setHealth(shield->powerOrigin);
        shield->shieldPower->setPosition(SCREEN_WIDTH/2+40, SCREEN_HEIGHT-170);
        target->getParent()->addChild(shield->shieldPower);
        
        
        //文字"BOSS"
        auto bossSpr=Sprite::create("img_shield_zi.png");
        bossSpr->setPosition(-160,0);
        shield->shieldPower->addChild(bossSpr);
    }
    
    //回调
    target->onCast(shield);
    
    //配置
    shield->target=target;
    shield->isValid=true;
}


float MonsterAbilityLightShield::hit(float damage)
{
    if(this->isValid==false){
        log("无效护盾");
        return damage;
    }
    log("------------------------------------");
    log("伤害%f，光盾能量%f",damage,power);
    if(damage>=power){
        damage-=power;
        power=0;
        this->cancel();
    }else{
        power-=damage;
        damage=0;
        shieldPower->setHealth(power);
    }
    log("剩余：伤害 %f , 光盾能量 %f",damage,power);
    log("------------------------------------");
    return damage;
}

void MonsterAbilityLightShield::attack(const int type,const int power)
{
    
    
}

void MonsterAbilityLightShield::cancel()
{
    //去掉盾
    lightShield->removeFromParentAndCleanup(true);
    
    //去掉能量条
    if(shieldPower){
        shieldPower->removeFromParentAndCleanup(true);
    }
    
    this->isValid=false;
    
    //回调
    target->onCancel(this->type);
}


void MonsterAbilityLightShield::onOtherAbilityCast(const int type)
{
    
}
