//
//  LevelConfig.cpp
//  beymac
//
//  Created by je on 6/26/15.
//
//

#include "LevelConfig.h"

Level::Level()
{
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
    bulletSpeed = 1;
    promptTime = 1;
    floor = 5;
}


map<int,Level*> LevelConfig::levelList;


map<int,Level*> LevelConfig::getList()
{
    if (levelList.empty()) {
        //第2关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=3;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=1;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=1;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=1;
            //-- 关卡物品掉落速度
            l->bulletSpeed=1;
            //-- 物品掉落提示时间
            l->promptTime=1;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=3;
            //-- 开启技能，0为没有
            l->unlockSkill=2;
            //-- 开启技能几率
            l->unlockSkillChance=100;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=1;
            atk1->minNum=3;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=7;
            atk2->minNum=1;
            atk2->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            //-- 本关层数
            l->floor=3;
            
            levelList[2]=l;
        }
        
        //第3关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=3;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=2.2;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=1;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=1;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=3;
            //-- 关卡物品掉落速度
            l->bulletSpeed=2;
            //-- 物品掉落提示时间
            l->promptTime=1;
            //-- 关卡开始时携带的能量
            l->startEnergy=60;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=3;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=100;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=2;
            atk1->maxNum=2;
            auto atk2=new BulletData();
            atk2->bulletType=7;
            atk2->minNum=1;
            atk2->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            //-- 本关层数
            l->floor=5;
            
            levelList[3]=l;
        }
        
        //第4关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=5;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=1;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=4;
            //-- 关卡物品掉落速度
            l->bulletSpeed=4;
            //-- 物品掉落提示时间
            l->promptTime=1;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=4;
            //-- 开启技能，0为没有
            l->unlockSkill=3;
            //-- 开启技能几率
            l->unlockSkillChance=100;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=5;
            atk1->minNum=1;
            atk1->maxNum=1;
            auto atk2=new BulletData();
            atk2->bulletType=7;
            atk2->minNum=1;
            atk2->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            //-- 本关层数
            l->floor=7;
            
            levelList[4]=l;
        }
        
        //第5关
        {
            auto l=new Level;
            //-- 关卡物品掉落速度
            l->bulletSpeed=5;
            //-- 物品掉落提示时间
            l->promptTime=2;
            
            levelList[5]=l;
        }
        
        
        //第6关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=3;
            //-- 光盾血量
            l->lightShieldLife=3;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=1;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=2;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=4;
            //-- 关卡物品掉落速度
            l->bulletSpeed=5;
            //-- 物品掉落提示时间
            l->promptTime=2;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=4;
            //-- 开启技能，0为没有
            l->unlockSkill=4;
            //-- 开启技能几率
            l->unlockSkillChance=50;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=7;
            atk2->minNum=1;
            atk2->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            //-- 本关层数
            l->floor=11;
            
            levelList[6]=l;
        }
        
        //第7关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=6;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=2;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=6;
            //-- 关卡物品掉落速度
            l->bulletSpeed=5;
            //-- 物品掉落提示时间
            l->promptTime=2;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=4;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=100;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=6;
            atk1->minNum=2;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=2;
            atk2->maxNum=4;
            
            auto atk3=new BulletData();
            atk3->bulletType=7;
            atk3->minNum=1;
            atk3->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            //-- 本关层数
            l->floor=13;
            
            levelList[7]=l;
        }
        
        //第8关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=7;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=1.8;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=2;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=2;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=5;
            //-- 关卡物品掉落速度
            l->bulletSpeed=6;
            //-- 物品掉落提示时间
            l->promptTime=2;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=5;
            //-- 开启技能，0为没有
            l->unlockSkill=6;
            //-- 开启技能几率
            l->unlockSkillChance=40;
            //-- 推荐技能
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=2;
            atk1->maxNum=3;
            
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=2;
            atk2->maxNum=3;
            
            auto atk3=new BulletData();
            atk3->bulletType=7;
            atk3->minNum=1;
            atk3->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            //-- 本关层数
            l->floor=15;
            
            levelList[8]=l;
        }
        
        //第9关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=8;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=2;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=6;
            //-- 关卡物品掉落速度
            l->bulletSpeed=6;
            //-- 物品掉落提示时间
            l->promptTime=3;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=5;
            //-- 开启技能，0为没有
            l->unlockSkill=7;
            //-- 开启技能几率
            l->unlockSkillChance=40;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=3;
            atk1->minNum=3;
            atk1->maxNum=4;
            
            auto atk2=new BulletData();
            atk2->bulletType=5;
            atk2->minNum=1;
            atk2->maxNum=1;
            
            auto atk3=new BulletData();
            atk3->bulletType=7;
            atk3->minNum=1;
            atk3->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            //-- 本关层数
            l->floor=17;
            
            levelList[9]=l;
        }
        
        //第10关
        {
            auto l=new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed=6;
            //-- 物品掉落提示时间
            l->promptTime=4;
            //-- 关卡开始时携带的能量
            l->startEnergy=30;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            
            levelList[10]=l;
        }
        //第11关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 5;
            //-- 光盾血量
            l->lightShieldLife = 5;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 2;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 2;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 5;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 6;
            //-- 物品掉落提示时间
            l->promptTime = 4;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 6;
            //-- 开启技能，0为没有
            l->unlockSkill = 8;
            //-- 开启技能几率
            l->unlockSkillChance = 40;
            //-- 推荐技能
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 2;
            atk1->minNum = 2;
            atk1->maxNum = 3;
            auto atk2 = new BulletData();
            atk2->bulletType = 3;
            atk2->minNum = 4;
            atk2->maxNum = 5;
            auto atk3 = new BulletData();
            atk3->bulletType = 7;
            atk3->minNum = 1;
            atk3->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            //-- 本关层数
            l->floor = 19;
            
            levelList[11] = l;
        }
        //第12关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 11;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 1.1;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 7;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 6;
            //-- 物品掉落提示时间
            l->promptTime = 4;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 6;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 6;
            atk1->minNum = 2;
            atk1->maxNum = 4;
            auto atk2 = new BulletData();
            atk2->bulletType = 5;
            atk2->minNum = 1;
            atk2->maxNum = 1;
            auto atk3 = new BulletData();
            atk3->bulletType = 6;
            atk3->minNum = 2;
            atk3->maxNum = 4;
            auto atk4 = new BulletData();
            atk4->bulletType = 7;
            atk4->minNum = 1;
            atk4->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            //-- 本关层数
            l->floor = 21;
            
            levelList[12] = l;
        }
        //第13关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 11;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 6;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 6;
            //-- 物品掉落提示时间
            l->promptTime = 4;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 6;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(7);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 5;
            atk1->minNum = 1;
            atk1->maxNum = 1;
            auto atk2 = new BulletData();
            atk2->bulletType = 5;
            atk2->minNum = 1;
            atk2->maxNum = 1;
            auto atk3 = new BulletData();
            atk3->bulletType = 5;
            atk3->minNum = 1;
            atk3->maxNum = 1;
            auto atk4 = new BulletData();
            atk4->bulletType = 7;
            atk4->minNum = 1;
            atk4->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            //-- 本关层数
            l->floor = 22;
            
            levelList[13] = l;
        }
        //第14关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 12;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 6;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 6;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 6;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 6;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 1;
            atk1->minNum = 4;
            atk1->maxNum = 6;
            auto atk2 = new BulletData();
            atk2->bulletType = 4;
            atk2->minNum = 3;
            atk2->maxNum = 4;
            auto atk3 = new BulletData();
            atk3->bulletType = 1;
            atk3->minNum = 4;
            atk3->maxNum = 6;
            auto atk4 = new BulletData();
            atk4->bulletType = 7;
            atk4->minNum = 1;
            atk4->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            //-- 本关层数
            l->floor = 23;
            
            levelList[14] = l;
        }
        //第15关
        {
            auto l = new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            
            levelList[15] = l;
        }
        //第16关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 13;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 7;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 6;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 6;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 2;
            atk1->minNum = 3;
            atk1->maxNum = 3;
            auto atk2 = new BulletData();
            atk2->bulletType = 4;
            atk2->minNum = 3;
            atk2->maxNum = 3;
            auto atk3 = new BulletData();
            atk3->bulletType = 2;
            atk3->minNum = 3;
            atk3->maxNum = 3;
            auto atk4 = new BulletData();
            atk4->bulletType = 4;
            atk4->minNum = 3;
            atk4->maxNum = 3;
            auto atk5 = new BulletData();
            atk5->bulletType = 7;
            atk5->minNum = 1;
            atk5->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            //-- 本关层数
            l->floor = 24;
            
            levelList[16] = l;
        }
        //第17关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 7;
            //-- 光盾血量
            l->lightShieldLife = 11;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 7;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 7;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 7;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(5);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 6;
            atk1->minNum = 3;
            atk1->maxNum = 5;
            auto atk2 = new BulletData();
            atk2->bulletType = 3;
            atk2->minNum = 4;
            atk2->maxNum = 5;
            auto atk3 = new BulletData();
            atk3->bulletType = 6;
            atk3->minNum = 3;
            atk3->maxNum = 5;
            auto atk4 = new BulletData();
            atk4->bulletType = 3;
            atk4->minNum = 4;
            atk4->maxNum = 5;
            auto atk5 = new BulletData();
            atk5->bulletType = 7;
            atk5->minNum = 1;
            atk5->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            //-- 本关层数
            l->floor = 25;
            
            levelList[17] = l;
        }
        
        //第18关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 10;
            //-- 光盾血量
            l->lightShieldLife = 7;
            //    -- 隐身现身时间
            l->showUpTime = 1.1;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 7;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 7;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 7;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 3;
            atk1->minNum = 4;
            atk1->maxNum = 8;
            auto atk2 = new BulletData();
            atk2->bulletType = 4;
            atk2->minNum = 3;
            atk2->maxNum = 4;
            auto atk3 = new BulletData();
            atk3->bulletType = 3;
            atk3->minNum = 4;
            atk3->maxNum = 8;
            auto atk4 = new BulletData();
            atk4->bulletType = 4;
            atk4->minNum = 3;
            atk4->maxNum = 4;
            auto atk5 = new BulletData();
            atk5->bulletType = 7;
            atk5->minNum = 1;
            atk5->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            //-- 本关层数
            l->floor = 26;
            
            levelList[18] = l;
        }
        //第19关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 16;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 7;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 7;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 4;
            atk1->minNum = 2;
            atk1->maxNum = 3;
            auto atk2 = new BulletData();
            atk2->bulletType = 5;
            atk2->minNum = 1;
            atk2->maxNum = 1;
            auto atk3 = new BulletData();
            atk3->bulletType = 4;
            atk3->minNum = 2;
            atk3->maxNum = 3;
            auto atk4 = new BulletData();
            atk4->bulletType = 5;
            atk4->minNum = 1;
            atk4->maxNum = 1;
            auto atk5 = new BulletData();
            atk5->bulletType = 4;
            atk5->minNum = 2;
            atk5->maxNum = 2;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor = 27;
            
            levelList[19] = l;
        }
        
        //第20关
        {
            auto l = new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 20;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            
            levelList[20] = l;
            
        }
        
        //第21关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 17;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 8;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 8;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 3;
            atk1->minNum = 4;
            atk1->maxNum = 6;
            auto atk2 = new BulletData();
            atk2->bulletType = 2;
            atk2->minNum = 3;
            atk2->maxNum = 4;
            auto atk3 = new BulletData();
            atk3->bulletType = 3;
            atk3->minNum = 4;
            atk3->maxNum = 6;
            auto atk4 = new BulletData();
            atk4->bulletType = 2;
            atk4->minNum = 3;
            atk4->maxNum = 4;
            auto atk5 = new BulletData();
            atk5->bulletType = 3;
            atk5->minNum = 4;
            atk5->maxNum = 6;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            
            //-- 本关层数
            l->floor = 28;
            
            levelList[21] = l;
        }
        
        //第22关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 18;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 9;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 8;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 6;
            atk1->minNum = 3;
            atk1->maxNum = 6;
            auto atk2 = new BulletData();
            atk2->bulletType = 6;
            atk2->minNum = 3;
            atk2->maxNum = 6;
            auto atk3 = new BulletData();
            atk3->bulletType = 6;
            atk3->minNum = 3;
            atk3->maxNum = 6;
            auto atk4 = new BulletData();
            atk4->bulletType = 6;
            atk4->minNum = 3;
            atk4->maxNum = 6;
            auto atk5 = new BulletData();
            atk5->bulletType = 6;
            atk5->minNum = 3;
            atk5->maxNum = 6;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            
            //-- 本关层数
            l->floor = 29;
            
            levelList[22] = l;
        }
        
        
        //第23关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 9;
            //-- 光盾血量
            l->lightShieldLife = 15;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 8;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 9;
            //-- 物品掉落提示时间
            l->promptTime = 5;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 8;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 5;
            atk1->minNum = 1;
            atk1->maxNum = 1;
            auto atk2 = new BulletData();
            atk2->bulletType = 2;
            atk2->minNum = 3;
            atk2->maxNum = 4;
            auto atk3 = new BulletData();
            atk3->bulletType = 5;
            atk3->minNum = 1;
            atk3->maxNum = 1;
            auto atk4 = new BulletData();
            atk4->bulletType = 2;
            atk4->minNum = 3;
            atk4->maxNum = 4;
            auto atk5 = new BulletData();
            atk5->bulletType = 5;
            atk5->minNum = 1;
            atk5->maxNum = 1;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            
            //-- 本关层数
            l->floor = 30;
            
            levelList[23] = l;
        }
        
        
        //第24关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 20;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 8;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 6;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 8;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 1;
            atk1->minNum = 4;
            atk1->maxNum = 6;
            auto atk2 = new BulletData();
            atk2->bulletType = 4;
            atk2->minNum = 3;
            atk2->maxNum = 4;
            auto atk3 = new BulletData();
            atk3->bulletType = 1;
            atk3->minNum = 4;
            atk3->maxNum = 6;
            auto atk4 = new BulletData();
            atk4->bulletType = 4;
            atk4->minNum = 3;
            atk4->maxNum = 4;
            auto atk5 = new BulletData();
            atk5->bulletType = 1;
            atk5->minNum = 4;
            atk5->maxNum = 6;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            
            //-- 本关层数
            l->floor = 30;
            
            levelList[24] = l;
        }
        
        
        //第25关
        {
            auto l = new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed = 10;
            //-- 物品掉落提示时间
            l->promptTime = 6;
            
            
            levelList[25] = l;
        }
        
        
        
        
        //第26关
        {
            auto l = new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife = 21;
            //-- 光盾血量
            l->lightShieldLife = 0;
            //    -- 隐身现身时间
            l->showUpTime = 1.0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed = 3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed = 3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed = 8;
            //-- 关卡物品掉落速度
            l->bulletSpeed = 8;
            //-- 物品掉落提示时间
            l->promptTime = 6;
            //-- 关卡开始时携带的能量
            l->startEnergy = 40;
            //-- 关卡掉落能量
            l->energy = 20;
            //-- 能量掉落次数
            l->amountOfEnergy = 8;
            //-- 开启技能，0为没有
            l->unlockSkill = 0;
            //-- 开启技能几率
            l->unlockSkillChance = 0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1 = new BulletData();
            atk1->bulletType = 4;
            atk1->minNum = 2;
            atk1->maxNum = 4;
            auto atk2 = new BulletData();
            atk2->bulletType = 5;
            atk2->minNum = 1;
            atk2->maxNum = 1;
            auto atk3 = new BulletData();
            atk3->bulletType = 4;
            atk3->minNum = 2;
            atk3->maxNum = 4;
            auto atk4 = new BulletData();
            atk4->bulletType = 5;
            atk4->minNum = 1;
            atk4->maxNum = 1;
            auto atk5 = new BulletData();
            atk5->bulletType = 4;
            atk5->minNum = 2;
            atk5->maxNum = 4;
            auto atk6 = new BulletData();
            atk6->bulletType = 7;
            atk6->minNum = 1;
            atk6->maxNum = 1;
            
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            
            //-- 本关层数
            l->floor = 32;
            
            levelList[26] = l;
        }

        //第27关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=11;
            //-- 光盾血量
            l->lightShieldLife=15;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=8;
            //-- 关卡物品掉落速度
            l->bulletSpeed=8;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=8;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=2;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=3;
            atk2->minNum=5;
            atk2->maxNum=8;
            auto atk3=new BulletData();
            atk3->bulletType=2;
            atk3->minNum=2;
            atk3->maxNum=4;
            auto atk4=new BulletData();
            atk4->bulletType=3;
            atk4->minNum=5;
            atk4->maxNum=8;
            auto atk5=new BulletData();
            atk5->bulletType=2;
            atk5->minNum=2;
            atk5->maxNum=4;
            auto atk6=new BulletData();
            atk6->bulletType=7;
            atk6->minNum=1;
            atk6->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor=30;
            
            levelList[27]=l;
        }
        
        
        //第28关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=22;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=8;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=9;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=4;
            atk2->minNum=3;
            atk2->maxNum=6;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=3;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=4;
            atk4->minNum=3;
            atk4->maxNum=6;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=3;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=7;
            atk6->minNum=1;
            atk6->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor=30;
            
            levelList[28]=l;
        }
        
        //第29关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=23;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=9;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=9;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=2;
            atk2->maxNum=3;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=3;
            atk3->maxNum=4;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=2;
            atk4->maxNum=3;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=3;
            atk5->maxNum=4;
            auto atk6=new BulletData();
            atk6->bulletType=7;
            atk6->minNum=1;
            atk6->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor=30;
            
            levelList[29]=l;
        }
        
        //第30关
        {
            auto l=new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed=10;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=10;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            
            levelList[30]=l;
        }
        
        //第31关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=25;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=10;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=10;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=6;
            atk1->minNum=3;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=3;
            atk2->maxNum=6;
            auto atk3=new BulletData();
            atk3->bulletType=6;
            atk3->minNum=3;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=6;
            atk4->minNum=3;
            atk4->maxNum=6;
            auto atk5=new BulletData();
            atk5->bulletType=6;
            atk5->minNum=3;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=7;
            atk6->minNum=1;
            atk6->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor=30;
            
            levelList[31]=l;
        }
        
        //第32关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=27;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0.9;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=10;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=10;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=4;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=4;
            atk2->maxNum=4;
            auto atk3=new BulletData();
            atk3->bulletType=2;
            atk3->minNum=4;
            atk3->maxNum=4;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=4;
            atk4->maxNum=4;
            auto atk5=new BulletData();
            atk5->bulletType=2;
            atk5->minNum=4;
            atk5->maxNum=4;
            auto atk6=new BulletData();
            atk6->bulletType=7;
            atk6->minNum=1;
            atk6->maxNum=1;
            
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            //-- 本关层数
            l->floor=30;
            
            levelList[32]=l;
        }
        
        //第33关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=29;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=9;
            //-- 关卡物品掉落速度
            l->bulletSpeed=10;
            //-- 物品掉落提示时间
            l->promptTime=6;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=10;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=1;
            atk2->minNum=3;
            atk2->maxNum=6;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=3;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=1;
            atk4->minNum=3;
            atk4->maxNum=6;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=3;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=1;
            atk6->minNum=3;
            atk6->maxNum=6;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=30;
            
            levelList[33]=l;
        }
        
        //第34关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=30;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=8;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=10;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=2;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=5;
            atk2->minNum=1;
            atk2->maxNum=1;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=2;
            atk3->maxNum=4;
            auto atk4=new BulletData();
            atk4->bulletType=5;
            atk4->minNum=1;
            atk4->maxNum=1;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=2;
            atk5->maxNum=4;
            auto atk6=new BulletData();
            atk6->bulletType=5;
            atk6->minNum=1;
            atk6->maxNum=1;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=30;
            
            levelList[34]=l;
        }
        
        //第35关
        {
            auto l=new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed=12;
            //-- 物品掉落提示时间
            l->promptTime=6;
            
            
            levelList[35]=l;
        }
        
        //第36关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=30;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0.8;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=3;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=3;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=9;
            //-- 关卡物品掉落速度
            l->bulletSpeed=9;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=11;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(2);
            l->recommendSkill.push_back(3);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=5;
            atk1->minNum=1;
            atk1->maxNum=1;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=3;
            atk2->maxNum=4;
            auto atk3=new BulletData();
            atk3->bulletType=5;
            atk3->minNum=3;
            atk3->maxNum=3;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=3;
            atk4->maxNum=4;
            auto atk5=new BulletData();
            atk5->bulletType=5;
            atk5->minNum=3;
            atk5->maxNum=3;
            auto atk6=new BulletData();
            atk6->bulletType=2;
            atk6->minNum=3;
            atk6->maxNum=4;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=35;
            
            levelList[36]=l;
        }
        
        //第37关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(1);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=30;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=9;
            //-- 关卡物品掉落速度
            l->bulletSpeed=10;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=11;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=1;
            atk1->minNum=5;
            atk1->maxNum=7;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=3;
            atk2->maxNum=4;
            auto atk3=new BulletData();
            atk3->bulletType=1;
            atk3->minNum=5;
            atk3->maxNum=7;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=3;
            atk4->maxNum=4;
            auto atk5=new BulletData();
            atk5->bulletType=1;
            atk5->minNum=5;
            atk5->maxNum=7;
            auto atk6=new BulletData();
            atk6->bulletType=2;
            atk6->minNum=3;
            atk6->maxNum=4;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=35;
            
            levelList[37]=l;
        }
        
        //第38关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=30;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=10;
            //-- 关卡物品掉落速度
            l->bulletSpeed=10;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=10;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=3;
            atk2->maxNum=7;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=3;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=6;
            atk4->minNum=3;
            atk4->maxNum=7;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=3;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=6;
            atk6->minNum=3;
            atk6->maxNum=7;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=35;
            
            levelList[38]=l;
        }
        
        //第39关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=35;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=10;
            //-- 关卡物品掉落速度
            l->bulletSpeed=11;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=11;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=3;
            atk1->minNum=4;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=3;
            atk2->maxNum=3;
            auto atk3=new BulletData();
            atk3->bulletType=3;
            atk3->minNum=4;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=3;
            atk4->maxNum=3;
            auto atk5=new BulletData();
            atk5->bulletType=3;
            atk5->minNum=4;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=2;
            atk6->minNum=3;
            atk6->maxNum=3;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=35;
            
            levelList[39]=l;
        }
        
        //第40关
        {
            auto l=new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed=11;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=10;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            
            levelList[40]=l;
        }
        
        //第41关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=35;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=12;
            //-- 关卡物品掉落速度
            l->bulletSpeed=12;
            //-- 物品掉落提示时间
            l->promptTime=7;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=11;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(2);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=2;
            atk1->maxNum=4;
            auto atk2=new BulletData();
            atk2->bulletType=3;
            atk2->minNum=4;
            atk2->maxNum=7;
            auto atk3=new BulletData();
            atk3->bulletType=2;
            atk3->minNum=2;
            atk3->maxNum=4;
            auto atk4=new BulletData();
            atk4->bulletType=3;
            atk4->minNum=4;
            atk4->maxNum=7;
            auto atk5=new BulletData();
            atk5->bulletType=2;
            atk5->minNum=2;
            atk5->maxNum=4;
            auto atk6=new BulletData();
            atk6->bulletType=3;
            atk6->minNum=4;
            atk6->maxNum=7;
            auto atk7=new BulletData();
            atk7->bulletType=7;
            atk7->minNum=1;
            atk7->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            //-- 本关层数
            l->floor=40;
            
            levelList[41]=l;
        }
        
        //第42关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=35;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=13;
            //-- 关卡物品掉落速度
            l->bulletSpeed=13;
            //-- 物品掉落提示时间
            l->promptTime=8;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=12;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=5;
            atk1->minNum=1;
            atk1->maxNum=1;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=4;
            atk2->maxNum=6;
            auto atk3=new BulletData();
            atk3->bulletType=5;
            atk3->minNum=1;
            atk3->maxNum=1;
            auto atk4=new BulletData();
            atk4->bulletType=6;
            atk4->minNum=4;
            atk4->maxNum=6;
            auto atk5=new BulletData();
            atk5->bulletType=5;
            atk5->minNum=1;
            atk5->maxNum=1;
            auto atk6=new BulletData();
            atk6->bulletType=6;
            atk6->minNum=4;
            atk6->maxNum=6;
            auto atk7=new BulletData();
            atk7->bulletType=5;
            atk7->minNum=1;
            atk7->maxNum=1;
            auto atk8=new BulletData();
            atk8->bulletType=7;
            atk8->minNum=1;
            atk8->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            //-- 本关层数
            l->floor=40;
            
            levelList[42]=l;
        }
        
        //第43关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=35;
            //-- 光盾血量
            l->lightShieldLife=15;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=14;
            //-- 关卡物品掉落速度
            l->bulletSpeed=14;
            //-- 物品掉落提示时间
            l->promptTime=9;
            //-- 关卡开始时携带的能量
            l->startEnergy=30;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=12;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=1;
            atk1->minNum=5;
            atk1->maxNum=7;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=4;
            atk2->maxNum=4;
            auto atk3=new BulletData();
            atk3->bulletType=1;
            atk3->minNum=5;
            atk3->maxNum=7;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=4;
            atk4->maxNum=4;
            auto atk5=new BulletData();
            atk5->bulletType=1;
            atk5->minNum=5;
            atk5->maxNum=7;
            auto atk6=new BulletData();
            atk6->bulletType=2;
            atk6->minNum=4;
            atk6->maxNum=4;
            auto atk7=new BulletData();
            atk7->bulletType=1;
            atk7->minNum=5;
            atk7->maxNum=7;
            auto atk8=new BulletData();
            atk8->bulletType=7;
            atk8->minNum=1;
            atk8->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            //-- 本关层数
            l->floor=40;
            
            levelList[43]=l;
        }
        
        //第44关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=40;
            //-- 光盾血量
            l->lightShieldLife=0;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=13;
            //-- 关卡物品掉落速度
            l->bulletSpeed=15;
            //-- 物品掉落提示时间
            l->promptTime=10;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=12;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=4;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=5;
            atk2->minNum=1;
            atk2->maxNum=2;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=4;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=5;
            atk4->minNum=1;
            atk4->maxNum=2;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=4;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=5;
            atk6->minNum=1;
            atk6->maxNum=2;
            auto atk7=new BulletData();
            atk7->bulletType=4;
            atk7->minNum=4;
            atk7->maxNum=6;
            auto atk8=new BulletData();
            atk8->bulletType=7;
            atk8->minNum=1;
            atk8->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            //-- 本关层数
            l->floor=50;
            
            levelList[44]=l;
        }
        
        //第45关
        {
            auto l=new Level;
            
            //-- 关卡物品掉落速度
            l->bulletSpeed=16;
            //-- 物品掉落提示时间
            l->promptTime=8;
            
            
            levelList[45]=l;
        }
        
        //第46关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(4);
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=40;
            //-- 光盾血量
            l->lightShieldLife=25;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=5;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=16;
            //-- 关卡物品掉落速度
            l->bulletSpeed=16;
            //-- 物品掉落提示时间
            l->promptTime=10;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=15;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=1;
            atk1->minNum=5;
            atk1->maxNum=7;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=4;
            atk2->maxNum=7;
            auto atk3=new BulletData();
            atk3->bulletType=1;
            atk3->minNum=5;
            atk3->maxNum=7;
            auto atk4=new BulletData();
            atk4->bulletType=6;
            atk4->minNum=4;
            atk4->maxNum=7;
            auto atk5=new BulletData();
            atk5->bulletType=1;
            atk5->minNum=5;
            atk5->maxNum=7;
            auto atk6=new BulletData();
            atk6->bulletType=6;
            atk6->minNum=4;
            atk6->maxNum=7;
            auto atk7=new BulletData();
            atk7->bulletType=1;
            atk7->minNum=5;
            atk7->maxNum=7;
            auto atk8=new BulletData();
            atk8->bulletType=7;
            atk8->minNum=1;
            atk8->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            //-- 本关层数
            l->floor=60;
            
            levelList[46]=l;
        }
        
        //第47关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            //-- boss攻击方式
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(1);
            l->bossAttackMode.push_back(7);
            
            //-- boss血量
            l->bossLife=42;
            //-- 光盾血量
            l->lightShieldLife=20;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=17;
            //-- 关卡物品掉落速度
            l->bulletSpeed=17;
            //-- 物品掉落提示时间
            l->promptTime=11;
            //-- 关卡开始时携带的能量
            l->startEnergy=40;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=15;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=1;
            atk1->minNum=6;
            atk1->maxNum=7;
            auto atk2=new BulletData();
            atk2->bulletType=2;
            atk2->minNum=3;
            atk2->maxNum=5;
            auto atk3=new BulletData();
            atk3->bulletType=1;
            atk3->minNum=6;
            atk3->maxNum=7;
            auto atk4=new BulletData();
            atk4->bulletType=2;
            atk4->minNum=3;
            atk4->maxNum=5;
            auto atk5=new BulletData();
            atk5->bulletType=1;
            atk5->minNum=6;
            atk5->maxNum=7;
            auto atk6=new BulletData();
            atk6->bulletType=2;
            atk6->minNum=3;
            atk6->maxNum=5;
            auto atk7=new BulletData();
            atk7->bulletType=1;
            atk7->minNum=6;
            atk7->maxNum=7;
            auto atk8=new BulletData();
            atk8->bulletType=7;
            atk8->minNum=1;
            atk8->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            //-- 本关层数
            l->floor=60;
            
            levelList[47]=l;
        }
        
        //第48关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            l->bossAbility.push_back(5);
            //-- boss攻击方式
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(4);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=45;
            //-- 光盾血量
            l->lightShieldLife=20;
            //    -- 隐身现身时间
            l->showUpTime=0.5;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=16;
            //-- 关卡物品掉落速度
            l->bulletSpeed=18;
            //-- 物品掉落提示时间
            l->promptTime=11;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=20;
            //-- 能量掉落次数
            l->amountOfEnergy=12;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=4;
            atk1->minNum=3;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=5;
            atk2->minNum=2;
            atk2->maxNum=3;
            auto atk3=new BulletData();
            atk3->bulletType=4;
            atk3->minNum=3;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=5;
            atk4->minNum=2;
            atk4->maxNum=3;
            auto atk5=new BulletData();
            atk5->bulletType=4;
            atk5->minNum=3;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=5;
            atk6->minNum=2;
            atk6->maxNum=3;
            auto atk7=new BulletData();
            atk7->bulletType=4;
            atk7->minNum=3;
            atk7->maxNum=6;
            auto atk8=new BulletData();
            atk8->bulletType=5;
            atk8->minNum=2;
            atk8->maxNum=3;
            auto atk9=new BulletData();
            atk9->bulletType=7;
            atk9->minNum=1;
            atk9->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            l->bulletTypeAndNum.push_back(atk9);
            //-- 本关层数
            l->floor=74;
            
            levelList[48]=l;
        }
        
        //第49关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            l->bossAbility.push_back(3);
            //-- boss攻击方式
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(2);
            l->bossAttackMode.push_back(3);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=50;
            //-- 光盾血量
            l->lightShieldLife=30;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=19;
            //-- 关卡物品掉落速度
            l->bulletSpeed=19;
            //-- 物品掉落提示时间
            l->promptTime=12;
            //-- 关卡开始时携带的能量
            l->startEnergy=20;
            //-- 关卡掉落能量
            l->energy=30;
            //-- 能量掉落次数
            l->amountOfEnergy=12;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(3);
            l->recommendSkill.push_back(6);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=2;
            atk1->minNum=4;
            atk1->maxNum=6;
            auto atk2=new BulletData();
            atk2->bulletType=3;
            atk2->minNum=6;
            atk2->maxNum=8;
            auto atk3=new BulletData();
            atk3->bulletType=2;
            atk3->minNum=4;
            atk3->maxNum=6;
            auto atk4=new BulletData();
            atk4->bulletType=3;
            atk4->minNum=6;
            atk4->maxNum=8;
            auto atk5=new BulletData();
            atk5->bulletType=2;
            atk5->minNum=4;
            atk5->maxNum=6;
            auto atk6=new BulletData();
            atk6->bulletType=3;
            atk6->minNum=6;
            atk6->maxNum=8;
            auto atk7=new BulletData();
            atk7->bulletType=2;
            atk7->minNum=4;
            atk7->maxNum=6;
            auto atk8=new BulletData();
            atk8->bulletType=3;
            atk8->minNum=6;
            atk8->maxNum=8;
            auto atk9=new BulletData();
            atk9->bulletType=7;
            atk9->minNum=1;
            atk9->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            l->bulletTypeAndNum.push_back(atk9);
            //-- 本关层数
            l->floor=78;
            
            levelList[49]=l;
        }
        
        //第50关
        {
            auto l=new Level;
            
            //-- boss能力
            l->bossAbility.push_back(2);
            l->bossAbility.push_back(4);
            //-- boss攻击方式
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(5);
            l->bossAttackMode.push_back(6);
            l->bossAttackMode.push_back(7);
            //-- boss血量
            l->bossLife=60;
            //-- 光盾血量
            l->lightShieldLife=50;
            //    -- 隐身现身时间
            l->showUpTime=0;
            //-- boss移动速度,boss移速分1-5.每等级提速10%
            l->bossSpeed=4;
            //-- boss攻速，boss攻速分2个等级：1等级三秒攻击一次。2等级2秒攻击一次。
            l->bossAttackSpeed=4;
            //-- boss子弹攻速，boss子弹攻速分四个等级：1级为箱子原始掉落速度，下面每一级提速10%
            l->bossBulletSpeed=20;
            //-- 关卡物品掉落速度
            l->bulletSpeed=20;
            //-- 物品掉落提示时间
            l->promptTime=12;
            //-- 关卡开始时携带的能量
            l->startEnergy=0;
            //-- 关卡掉落能量
            l->energy=30;
            //-- 能量掉落次数
            l->amountOfEnergy=15;
            //-- 开启技能，0为没有
            l->unlockSkill=0;
            //-- 开启技能几率
            l->unlockSkillChance=0;
            //-- 推荐技能
            l->recommendSkill.push_back(1);
            l->recommendSkill.push_back(6);
            l->recommendSkill.push_back(7);
            //-- 所吐子弹的个数,"x,y,z" x=子弹类型，y=子弹最小格数，z=子弹最大格数
            auto atk1=new BulletData();
            atk1->bulletType=5;
            atk1->minNum=3;
            atk1->maxNum=3;
            auto atk2=new BulletData();
            atk2->bulletType=6;
            atk2->minNum=6;
            atk2->maxNum=6;
            auto atk3=new BulletData();
            atk3->bulletType=5;
            atk3->minNum=3;
            atk3->maxNum=3;
            auto atk4=new BulletData();
            atk4->bulletType=6;
            atk4->minNum=6;
            atk4->maxNum=6;
            auto atk5=new BulletData();
            atk5->bulletType=5;
            atk5->minNum=3;
            atk5->maxNum=3;
            auto atk6=new BulletData();
            atk6->bulletType=6;
            atk6->minNum=6;
            atk6->maxNum=6;
            auto atk7=new BulletData();
            atk7->bulletType=5;
            atk7->minNum=3;
            atk7->maxNum=3;
            auto atk8=new BulletData();
            atk8->bulletType=6;
            atk8->minNum=6;
            atk8->maxNum=6;
            auto atk9=new BulletData();
            atk9->bulletType=7;
            atk9->minNum=1;
            atk9->maxNum=1;
            l->bulletTypeAndNum.push_back(atk1);
            l->bulletTypeAndNum.push_back(atk2);
            l->bulletTypeAndNum.push_back(atk3);
            l->bulletTypeAndNum.push_back(atk4);
            l->bulletTypeAndNum.push_back(atk5);
            l->bulletTypeAndNum.push_back(atk6);
            l->bulletTypeAndNum.push_back(atk7);
            l->bulletTypeAndNum.push_back(atk8);
            l->bulletTypeAndNum.push_back(atk9);
            //-- 本关层数
            l->floor=100;
            
            levelList[50]=l;
        }
        
        
    }
    return levelList;
}

