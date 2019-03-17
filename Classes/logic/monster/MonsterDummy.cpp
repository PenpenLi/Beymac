//
//  MonsterDummy.cpp
//  beymac
//
//  Created by je on 5/11/15.
//
//

#include "MonsterDummy.h"




MonsterDummy::MonsterDummy(const MonsterProperty *property,MonsterDummyDelegate *callback)
{
    this->property=property;
    
    this->mstAnimation=MonsterAnimation::createMonsterAnimation(property->type);
    
    this->addChild(this->mstAnimation);
    
    this->callback=callback;
    
    //开始摇摆
    this->mstAnimation->shake();
    
}

//状态重置
void MonsterDummy::reset()
{
    if(repeatAct){
        this->stopAction(repeatAct);
    }
}

//进入战斗
void MonsterDummy::enterBattle()
{
    this->moving();
}


//左右移动
void MonsterDummy::moving()
{
    
    //左右移动配置
    float speed=this->property->moveSpeed;
    auto x=this->getPositionX();
    
    //左右移动
    Sequence *seq;
    if(this->getPositionX()<=320){
        
        auto mb1=MoveBy::create((x-BOUND_LEFT)/speed, Vec2(BOUND_LEFT-x, 0));
        
        auto mb2=MoveBy::create((x-BOUND_LEFT)/speed, Vec2(x-BOUND_LEFT, 0));
        
        auto mb3=MoveBy::create((BOUND_RIGHT-x)/speed, Vec2(BOUND_RIGHT-x, 0));
        
        auto mb4=MoveBy::create((BOUND_RIGHT-x)/speed, Vec2(x-BOUND_RIGHT, 0));
        
        seq=Sequence::create(mb1,mb2,mb3,mb4,NULL);
        
    }else{
        
        auto mb1=MoveBy::create((BOUND_RIGHT-x)/speed, Vec2(BOUND_RIGHT-x, 0));
        
        auto mb2=MoveBy::create((BOUND_RIGHT-x)/speed, Vec2(x-BOUND_RIGHT, 0));
        
        auto mb3=MoveBy::create((x-BOUND_LEFT)/speed, Vec2(BOUND_LEFT-x, 0));
        
        auto mb4=MoveBy::create((x-BOUND_LEFT)/speed, Vec2(x-BOUND_LEFT, 0));
        
        seq=Sequence::create(mb1,mb2,mb3,mb4,NULL);
    }
    
    repeatAct=RepeatForever::create(seq);
    this->runAction(repeatAct);
    
}

//攻击,参数：子弹类型,威力
void MonsterDummy::attack(const int type,const int power)
{
    this->mstAnimation->attack(type, power);
    
    //继续摇晃
    mstAnimation->shake();
    
    
    //调用技能的attack.....
    for(std::map<int,MonsterAbility*>::iterator itr=mstAbiMap.begin();itr!=mstAbiMap.end();itr++){
        if(itr->second){
            itr->second->attack(type, power);
        }
    }
}


//被攻击时调用,damage表示所受到的伤害值.
void MonsterDummy::hit(float damage,bool trueDamage)
{
    mstAnimation->hit();    //被攻击动画
    
    if(callback){
        callback->onHit(damage,trueDamage);
    }
}

//范围攻击
void MonsterDummy::hit(Vec2 pos1,Vec2 pos2,float damage,bool trueDamage)
{
    
}

//获取位置
Point MonsterDummy::getPosition()
{
    if(this->getParent()){
        auto parentPos=this->getParent()->getPosition();
        return this->cocos2d::Node::getPosition()+parentPos;
    }else{
        return this->cocos2d::Node::getPosition();
    }
}

void MonsterDummy::setOpacity(GLubyte opacity)
{
    this->mstAnimation->setOpacity(opacity);
}


void MonsterDummy::onCast(MonsterAbility *abi)
{
    int abiType=abi->type;
    
    this->mstAbiMap[abiType]=abi;
    
    //通知已有技能，有新技能加入
    for(std::map<int,MonsterAbility *>::iterator itr=mstAbiMap.begin();itr!=mstAbiMap.end();itr++){
        if(itr->second){
            itr->second->onOtherAbilityCast(abiType);
        }
    }
    
}

void MonsterDummy::onCancel(const int abiType)
{
    this->mstAbiMap[abiType]=0;
    
}




