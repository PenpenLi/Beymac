//
//  LevelData.cpp
//  beymac
//
//  Created by mumu on 15/5/22.
//
//

#include "LevelData.h"

#define LOOPCOUNT 3

BulletData::BulletData()
{
    bulletType = 1;
    minNum = 0;
    maxNum = 0;
}

SpecialRequire::SpecialRequire()
{
    bulletType = 1;
    shootCount = 0;
    allNum = 0;
}

LevelData::LevelData()
{
    level = 1;
    bossLife = 1;
    lightShieldLife = 0;
    showUpTime = 0;
    bossSpeed = 1;
    bossAttackSpeed = 1;
    bossBulletSpeed = 1;
    energy = 0;
    amountOfEnergy = 0;
    startEnergy = 0;
    unlockSkill = 0;
    unlockSkillChance = 0;
    fallDripTime = 5;
    bulletSpeed = 1;
    promptTime = 1;
    floor = 5;
}

LevelData::~LevelData()
{
    bossAbilityList.clear();
    bossAttackModeList.clear();
    recommendSkillList.clear();
    bulletSpecialRequireList.clear();
    bulletTypeAndNumList.clear();
}

// 生成发射子弹的顺序队列
void LevelData::buildShootBulletList()
{
    
    // 获取特殊需求中最高层数
    vector<SpecialRequire*>::iterator iter;
    int floor = 0;
    for (iter = bulletSpecialRequireList.begin(); iter != bulletSpecialRequireList.end(); iter++) {
        if ((*iter)->shootCount > floor) {
            floor = (*iter)->shootCount;
        }
    }
    
    int count = 0;
    if (floor == 0) {
        count = LOOPCOUNT;
        
    }
    else
    {
        count = floor;
    }
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < bossAttackModeList.size(); j++) {
            if (bossAttackModeList.size() > bulletTypeAndNumList.size()) {
                j = 0;
            }
            ShootBullet* data = new ShootBullet();
            data->count = getRandomNum(bulletTypeAndNumList[j]->minNum, bulletTypeAndNumList[j]->maxNum);
            data->bulletType = bulletTypeAndNumList[j]->bulletType;
            shootBulletList.push_back(data);
        }
    }
    
    if (bulletSpecialRequireList.size()>0) {
        // 有特殊要求
        vector<ShootBullet*>::iterator i;
        for (iter = bulletSpecialRequireList.begin(); iter != bulletSpecialRequireList.end(); iter++) {
         
            SpecialRequire* s = (*iter);
            int num = 0;
            for (i = shootBulletList.begin(); i != shootBulletList.end(); i++) {
                if ((*i)->bulletType == s->bulletType) {
                    num++;
                    if (num == s->shootCount) {
                        num = 0;
                        (*i)->count = s->allNum;
//                        log("输出有特殊需求的子弹列表：类型：%d，总数：%d",(*i)->bulletType,s->allNum);
                    }
                    
                    
                }
            }
        }
    }
    
    
    vector<ShootBullet*>::iterator j;
    for (j = shootBulletList.begin(); j != shootBulletList.end(); j++) {
        log("输出生成的子弹列表：类型：%d，个数：%d",(*j)->bulletType,(*j)->count);
    }

}

// 随机生成范围内的随机数
int LevelData::getRandomNum(int min, int max)
{
//    srand((int)time(0));
    int i = rand()%(max-min+1)+min;
//    log("输出随机数：%d",i);
    return i;
}