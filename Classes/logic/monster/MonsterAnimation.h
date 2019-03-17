//
//  MonsterAnimation.h
//  beymac
//
//  Created by je on 5/8/15.
//
//


#ifndef __beymac__MonsterAnimation__
#define __beymac__MonsterAnimation__

#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>

USING_NS_CC;
using namespace cocostudio;



class MonsterAnimationDelegate{
public:
    virtual void onMonsterAnimationAttackCompleted()=0;
    virtual void onMonsterAnimationShakeCompleted()=0;
    virtual void onMonsterAnimationHitCompleted()=0;
    virtual void onMonsterAnimationCheerCompleted()=0;
};


class MonsterAnimation:public Node{
public:
    static MonsterAnimation *createMonsterAnimation(int number);
    
    //初始化
    virtual bool init();
    
    void setOpacity(GLubyte opacity);

    
    void hit();
    void shake();
    void cheer();
    //type ,子弹类型
    void attack(const int type,const int count);
    
    
    //委托
    CC_SYNTHESIZE(MonsterAnimationDelegate*, monsterAnimationDelegate, callbackFunc);
    
    
    int monsterType;
    
private:
    
    
    Armature *armature;
    
    int atkType;   //弹类型
    int atkPower;  //攻击力（子弹数量)
    
};

#endif
