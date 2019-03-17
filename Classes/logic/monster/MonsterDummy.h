//
//  MonsterDummy.h
//  beymac
//
//  Created by je on 5/11/15.
//
//  分身和假身都是Dummy的子类


#ifndef __beymac__MonsterDummy__
#define __beymac__MonsterDummy__

#include <cocos2d.h>
#include "MonsterAnimation.h"
#include "Body.h"
#include "CastableBody.h"
#include "LevelData.h"

#define BOUND_LEFT 100
#define BOUND_RIGHT 540


USING_NS_CC;
using namespace ui;

class MonsterDummyDelegate{
public:
    virtual void onHit(float damage,bool trueDamage=false)=0;
};


class MonsterDummy:public Body,public CastableBody{
public:
    
    MonsterDummy(const MonsterProperty *property,MonsterDummyDelegate *callback);
    
    //状态重置
    void reset();
    
    //进入战斗
    void enterBattle();
    
    //左右移动
    void moving();
    
    //攻击,参数：子弹类型
    void attack(const int type,const int count);
    
    //被攻击时调用,damage表示所受到的伤害值.
    virtual void hit(float damage,bool trueDamage=false);
    
    //范围攻击
    virtual void hit(Vec2 pos1,Vec2 pos2,float damage,bool trueDamage=false);
    
    //获取位置
    virtual Point getPosition();
    //重写
    virtual void setOpacity(GLubyte opacity);
    
    
    virtual void onCast(MonsterAbility *abi);
    
    virtual void onCancel(const int abiType);
    
public:
    
    const MonsterProperty *property;
    
private:
    
    MonsterAnimation *mstAnimation;
    
    RepeatForever *repeatAct;
    
    MonsterDummyDelegate *callback;
    
    std::map<int,MonsterAbility *> mstAbiMap;
        
    //暂停移动
    bool isPauseMoving;
};

#endif