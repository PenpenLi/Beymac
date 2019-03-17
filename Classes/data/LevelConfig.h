//
//  LevelConfig.h
//  beymac
//
//  Created by je on 6/26/15.
//
//

#ifndef __beymac__LevelConfig__
#define __beymac__LevelConfig__

#include <cocos2d.h>

#include "LevelData.h"


using namespace std;

class Attack{
public:
    int type;
    int min;
    int max;
};


class Level{
public:
    
    Level();
    
    //-- boss能力
    vector<int> bossAbility;
    
    //-- boss攻击方式
    vector<int> bossAttackMode;
    
    //-- boss血量
    float bossLife;
    
    //-- 光盾血量
    float lightShieldLife;
    
    //    -- 隐身现身时间
    float showUpTime;
    
    //-- boss移动速度,boss移速分1-5.每等级提速10%
    int bossSpeed;
    
    //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
    int bossAttackSpeed;
    
    //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
    int bossBulletSpeed;
    
    //-- 关卡物品掉落速度
    int bulletSpeed;
    
    //-- 物品掉落提示时间
    int promptTime;
    
    //-- 关卡开始时携带的能量
    float startEnergy;
    
    //-- 关卡掉落能量
    float energy;
    
    //-- 能量掉落次数
    int amountOfEnergy;
    
    //-- 开启技能，0为没有
    int unlockSkill;
    
    //-- 开启技能几率
    int unlockSkillChance;
    
    //-- 推荐技能
    vector<int> recommendSkill;
    
    //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
    vector<BulletData*> bulletTypeAndNum;
    
    //-- 本关层数
    int floor;
    
};





class LevelConfig{
public:
    static map<int,Level*> getList();
    
    
private:
    
    static map<int,Level*> levelList;
    
    
};







#endif /* defined(__beymac__LevelConfig__) */
