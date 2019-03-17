//
//  Monster.h
//  beymac
//
//  Created by je on 5/8/15.
//
//


#ifndef __beymac__Monster__
#define __beymac__Monster__

#include "MonsterAnimation.h"
#include "MonsterAttackSequence.h"
#include "Health.h"
#include "Body.h"
#include "MonsterDummy.h"
#include "CastableBody.h"
#include "MonsterProperty.h"


#define MONSTER_ABILITY_NORMAL 1
#define MONSTER_ABILITY_LIGHT_SHIELD 2
#define MONSTER_ABILITY_GHOST 3
#define MONSTER_ABILITY_COPY 4
#define MONSTER_ABILITY_STEALTH 5


class MonsterDelegate{
public:
    //  弹药： 1.子弹 2.炸弹 3.冰块  4.粘液  5.反射激光  6.短激光  7.水泡
    virtual void onMonsterAttack(int type,int power,int speed)=0;  //攻击.type子弹类型,power威力(子弹数量)
    virtual void onMonsterCastSpell(int type,int speed)=0;
    //boss胜利触发不了
    virtual void onBattleEnd(int result)=0;   //战斗结束，1.boss胜利，2.boss失败

};


class Monster:public MonsterAnimationDelegate,public CastableBody,public Body{
    
public:
    
    Monster(const int level);
    
    //参数是关卡号
    static Monster *createMonster(const int level);
    
    bool init();
    
    void onUpdate(float dt);
    
    //进入战斗
    void enterBattle();
    
    //离开战斗
    void leaveBattle();
    
    //状态重置，包括血量
    void reset();
    
    //显示血量
    void showHealth(float value);
    
    //攻击
    void attack();
    
    //左右移动
    void startMoving();
    
    //是否在战斗中
    bool inCombat();
    
//    //暂停移动
    void pauseMoving();
//
//    //继续移动
    void resumeMoving();
    
    //重写
    virtual Point getPosition();
    //重写
    virtual void setOpacity(GLubyte opacity);
    
    
    //被攻击时调用,damage表示所受到的伤害值.
    virtual void hit(float damage,bool trueDamage=false);
    
    //范围攻击
    virtual void hit(Vec2 pos1,Vec2 pos2,float damage,bool trueDamage=false);
    
    //施法技能时
    virtual void onCast(MonsterAbility *abi);
    
    //取消技能时
    virtual void onCancel(const int abiType);
    
    //获取boss主体及其它身体
    std::vector<Body *> getBodyList();
    
    //设置boss为已胜出
    void setVictory(bool isVictory);
        
    //动画回调
    virtual void onMonsterAnimationAttackCompleted();
    virtual void onMonsterAnimationShakeCompleted();
    virtual void onMonsterAnimationHitCompleted();
    virtual void onMonsterAnimationCheerCompleted();
    
    
private:
    //委托
    CC_SYNTHESIZE(MonsterDelegate*, monsterDelegate, callbackFunc);
    
    MonsterProperty *property;
    
    //所属关卡
    int level;
    
    //boss类型
    int type;
    
    //攻击速度（即攻击频率）
    float atkSpeed;
    
    //移动速度
    float moveSpeed;
    
    //现身时间
    float showUpTime;
    
    //boss动画对象，包含组合动画
    MonsterAnimation *monsterAnimation;
    
    //可使用的技能编号列表
    std::map<int,int> mstUsableAbiMap;
    
    //技能列表
    std::map<int,MonsterAbility *> mstAbiMap;
    
    //攻击序列
    MonsterAttackSequence *mstAttackSeq;
    
    //本次攻击
    MonsterAttack *atkCur;
    
    //初始血量
    int healthValue;
    
    //护盾强度
    float shieldValue;
    
    //血条
    Health *health;
    
    //战斗中
    bool _inCombat;
    
    //update计时
    float dtAttack;
    
    //左右移动
    RepeatForever *repeatAct;
    
    //是否运动中
    bool isMoving;
    
    
    //是否已胜出
    bool isVictory;
    
    
};



#endif
