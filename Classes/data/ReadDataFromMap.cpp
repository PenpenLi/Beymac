//
//  ReadDataFromMap.cpp
//  beymac
//
//  Created by mumu on 15/6/26.
//
//

#include "ReadDataFromMap.h"

static ReadDataFromMap *sData = NULL;

//单例
ReadDataFromMap *ReadDataFromMap::getInstance()
{
    if(!sData){
        sData=new ReadDataFromMap();
        
    }
    return sData;
}

// 根据关卡数读取关卡数据
LevelData* ReadDataFromMap::readLevelDataByLevel(int level)
{
    
    map<int,Level*> map = LevelConfig::getList();
    Level* d = map[level];

    LevelData* data = new LevelData();
    if (!d) {
        return data;
    }
    data->setLevel(level);
    // boss血量
    data->setBossLife(d->bossLife);
    // 光盾血量
    data->setLightShieldLife(d->lightShieldLife);
    // 隐身现身时间:单位秒
    data->setShowUpTime(d->showUpTime);
    // boss移动速度,boss移速分1-5.每等级提速10%
    data->setBossSpeed(d->bossSpeed);
    //    log("读取lua：boss移动速度：%d",bossSpeed);
    
    // boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
    data->setBossAttackSpeed(d->bossAttackSpeed);
    //    log("读取lua：boss移动速度：%d",bossAttackSpeed);
    
    // boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
    data->setBossBulletSpeed(d->bossBulletSpeed);
    //    log("读取lua：boss移动速度：%d",bossBulletSpeed);

    // 关卡掉落能量
    data->setEnergy(d->energy);
    //    log("读取lua：关卡掉落能量：%d",energy);
    
    // 能量掉落次数
    data->setAmountOfEnergy(d->amountOfEnergy);
    //    log("读取lua：能量掉落次数：%d",amountOfEnergy);
    
    // 开启技能，0为没有
    data->setUnlockSkill(d->unlockSkill);
    //    log("读取lua：开启技能：%d",unlockSkill);
    
    // 初始能量
    data->setStartEnergy(d->startEnergy);
    
    // 开启技能几率
    data->setUnlockSkillChance(d->unlockSkillChance);
    //    log("读取lua：开启技能几率：%d",unlockSkillChance);
    
    // 关卡箱子掉落速度
    data->setBulletSpeed(d->bulletSpeed);
    //    log("读取lua：关卡箱子掉落速度：%d",bulletSpeed);
    
    // 物品掉落提示时间
    data->setPromptTime(d->promptTime);
    
    // 本关层数
    data->setFloor(d->floor);
    
    // boss能力列表
    data->bossAbilityList = d->bossAbility;
    
    // boss攻击方式列表
    data->bossAttackModeList = d->bossAttackMode;
    
    // 推荐技能列表
    data->recommendSkillList = d->recommendSkill;
    
    // 吐子弹数列表
    data->bulletTypeAndNumList = d->bulletTypeAndNum;
    
    data->buildShootBulletList();
    
    return data;
}