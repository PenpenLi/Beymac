//
//  LevelData.h
//  beymac
//
//  Created by mumu on 15/5/22.
//
//

#ifndef __beymac__LevelData__
#define __beymac__LevelData__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class BulletData{
public:
    BulletData();
    // 子弹类型
    int bulletType;
    // 最小子弹数
    int minNum;
    // 最大子弹数
    int maxNum;
};

class SpecialRequire{
public:
    SpecialRequire();
    // 子弹类型
    int bulletType;
    // 第几次发射
    int shootCount;
    // 子弹数
    int allNum;
};

class ShootBullet{
public:
    // 子弹类型
    int bulletType;
    // 发射个数
    int count;
};


class LevelData{
public:
    LevelData();
    ~LevelData();
    
    // 生成发射子弹的顺序队列
    void buildShootBulletList();
    // 随机生成范围内的随机数
    int getRandomNum(int min, int max);
    
public:
    // boss能力列表
    vector<int> bossAbilityList;
    // boss攻击方式列表
    vector<int> bossAttackModeList;
    // 推荐技能列表
    vector<int> recommendSkillList;
    // 吐子弹数列表
    vector<BulletData*> bulletTypeAndNumList;
    // 特殊要求列表
    vector<SpecialRequire*> bulletSpecialRequireList;
    // 子弹发射列表
    vector<ShootBullet*> shootBulletList;
    
private:
    // 关卡数
    CC_SYNTHESIZE(int, level, Level);
    // boss血量
    CC_SYNTHESIZE(float, bossLife, BossLife);
    // 光盾血量
    CC_SYNTHESIZE(int, lightShieldLife, LightShieldLife);
    // 隐身现身时间:单位秒
    CC_SYNTHESIZE(float, showUpTime, ShowUpTime);
    // boss移动速度,boss移速分1-5.每等级提速10%
    CC_SYNTHESIZE(int, bossSpeed, BossSpeed);
    // boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
    CC_SYNTHESIZE(int, bossAttackSpeed, BossAttackSpeed);
    // boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
    CC_SYNTHESIZE(int, bossBulletSpeed, BossBulletSpeed);
    // 关卡掉落能量
    CC_SYNTHESIZE(int, energy, Energy);
    // 能量掉落次数
    CC_SYNTHESIZE(int, amountOfEnergy, AmountOfEnergy);
    // 开启技能，0为没有
    CC_SYNTHESIZE(int, unlockSkill, UnlockSkill);
    // 开启技能几率
    CC_SYNTHESIZE(int, unlockSkillChance, UnlockSkillChance);
    // 掉水滴时间
    CC_SYNTHESIZE(int, fallDripTime, FallDripTime);
    // 关卡初始能量
    CC_SYNTHESIZE(int, startEnergy, StartEnergy);
    // 关卡箱子掉落速度
    CC_SYNTHESIZE(int, bulletSpeed, BulletSpeed);
    // 物品掉落提示时间:单位秒
    CC_SYNTHESIZE(float, promptTime, PromptTime);
    // 本关卡层数
    CC_SYNTHESIZE(int, floor, Floor);
};

#endif /* defined(__beymac__LevelData__) */
