//
//  Monster.cpp
//  beymac
//
//  Created by je on 5/8/15.
//
//

#include "Monster.h"
#include <cocos2d.h>
#include "CommonHeader.h"
#include "MonsterAbilityGhost.h"
#include "MonsterAbilityCopy.h"
#include "MonsterAbilityLightShield.h"
#include "MonsterAbilityStealth.h"
#include "ReadDataFromMap.h"


Monster::Monster(const int level){
    this->level=level;
    this->monsterDelegate=nullptr;
}

Monster *Monster::createMonster(const int level)
{
    auto m=new Monster(level);
    if(m&&m->init()){
        m->autorelease();
    }
    return m;
}

bool Monster::init()
{
    this->_inCombat=false;
    this->isMoving=false;
    
    type=level%5;
    if(type==0){
        type=5;
    }
    
    
    
    auto ma=MonsterAnimation::createMonsterAnimation(type);
    
    ma->setcallbackFunc(this);
    
    this->monsterAnimation=ma;
    
    this->addChild(ma);
    
    //开始摇摆
    this->monsterAnimation->shake();
    
    
    auto levelData=ReadDataFromMap::getInstance()->readLevelDataByLevel(level);
    
    //攻速
    int atkSpeedLevel=levelData->getBossAttackSpeed();
    switch (atkSpeedLevel) {
        case 1:
            atkSpeed=3;
            break;
        case 2:
            atkSpeed=2.5;
            break;
        case 3:
            atkSpeed=2;
            break;
        case 4:
            atkSpeed=1.5;
            break;
        case 5:
            atkSpeed=1;
            break;
        default:
            atkSpeed=3;
            break;
    }
    
    //移速
    int moveSpeedLevel=levelData->getBossSpeed();
    switch (moveSpeedLevel) {
        case 1:
            moveSpeed=90;
            break;
        case 2:
            moveSpeed=120;
            break;
        case 3:
            moveSpeed=140;
            break;
        case 4:
            moveSpeed=160;
            break;
        case 5:
            moveSpeed=180;
            break;
        default:
            moveSpeed=100;
            break;
    }
    
    //读现身时间
    this->showUpTime=levelData->getShowUpTime();
    
    //读取血量
    this->healthValue=levelData->getBossLife();
    if(this->healthValue<=0){
        this->healthValue=5;
    }
    //护盾能量值
    this->shieldValue=levelData->getLightShieldLife();
    
    
    //加入子弹
    auto seqData=levelData->shootBulletList;
    
    log("源攻击序列长度:%lu",seqData.size());
    
    //攻击序列
    this->mstAttackSeq = new MonsterAttackSequence();
    
    for(vector<ShootBullet*>::iterator itr=seqData.begin();itr!=seqData.end();itr++){
        
        //        log("攻击子弹类型:%d",(*itr)->bulletType);
        auto atk=new MonsterAttack();
        atk->attackModeNumber=(*itr)->bulletType;
        atk->power=(*itr)->count;
        atk->speed=levelData->getBossBulletSpeed();
        this->mstAttackSeq->addMonsterAttack(atk);
    }
    
    //加载boss能力
    auto mstAbiVct=levelData->bossAbilityList;
    
    
    mstUsableAbiMap[MONSTER_ABILITY_NORMAL]=0;
    mstUsableAbiMap[MONSTER_ABILITY_LIGHT_SHIELD]=0;
    mstUsableAbiMap[MONSTER_ABILITY_GHOST]=0;
    mstUsableAbiMap[MONSTER_ABILITY_COPY]=0;
    mstUsableAbiMap[MONSTER_ABILITY_STEALTH]=0;
    
    
    log("boss能力编号：");
    for(vector<int>::iterator itr=mstAbiVct.begin();itr!=mstAbiVct.end();itr++){
        const int key=*itr;
        log("%d",key);
        mstUsableAbiMap[key]=1;
    }

    
    property=new MonsterProperty();
    property->level=this->level;
    property->type=this->type;
    property->atkSpeed=this->atkSpeed;
    property->moveSpeed=this->moveSpeed;
    property->showUpTime=this->showUpTime;
    property->healthValue=this->healthValue;
    property->shieldValue=this->shieldValue;
    
    
    return true;
}


//显示血量
void Monster::showHealth(float value)
{
    //monster血条
    auto health=Health::createNode("img_boss_life.png","img_boss_life_case.png");
    health->setOriginHealth(value);
    health->setHealth(value);
    health->setPosition(SCREEN_WIDTH/2+40,SCREEN_HEIGHT-120);
    this->getParent()->addChild(health);
    
    //文字"BOSS"
    auto bossSpr=Sprite::create("img_boss_zi.png");
    bossSpr->setPosition(-160,0);
    health->addChild(bossSpr);
    
    
    this->health=health;
}

void Monster::onUpdate(float dt)
{
    if(_inCombat){
        //防止dtAttack溢出变为负数
        if(this->dtAttack<0){
            log("dtAttack变为负数:%f",this->dtAttack);
            this->dtAttack=0;
        }
        this->dtAttack+=dt;
        
        //判断boss有没有被暂停
        if(this->isMoving&&this->dtAttack>=atkSpeed){
            attack();
            this->dtAttack=0;
        }
    }
    
}


//攻击
void Monster::attack()
{
    //身体总数量
    long bodyCount=getBodyList().size();
    //此次攻击
    atkCur=mstAttackSeq->next();
    //主体攻击动画
    this->monsterAnimation->attack(atkCur->attackModeNumber,atkCur->power/bodyCount);
    
    //继续摇晃
    monsterAnimation->shake();
    
    //调用技能的attack.....
    for(std::map<int,MonsterAbility*>::iterator itr=mstAbiMap.begin();itr!=mstAbiMap.end();itr++){
        if(itr->second){
            itr->second->attack(atkCur->attackModeNumber, atkCur->power/bodyCount);
        }
    }
    
    
}

//获取boss主体及其它身体
std::vector<Body *> Monster::getBodyList()
{
    std::vector<Body *> bodyList;
    
    bodyList.push_back(this);
    
    //分身坐标
    auto ghost=mstAbiMap[MONSTER_ABILITY_GHOST];
    
    if(ghost){
        auto ghostDummy=((MonsterAbilityGhost *)ghost)->dummyVctor;
        
//        log("分身数量：%lu",ghostDummy.size());
        
        for(std::vector<MonsterDummy *>::iterator dmIter=ghostDummy.begin();dmIter!=ghostDummy.end();dmIter++){
            bodyList.push_back((*dmIter));
        }
        
    }
    
    
    //假身坐标
    auto copy=mstAbiMap[MONSTER_ABILITY_COPY];
    
    if(copy){
        auto copyDummy=((MonsterAbilityCopy *)copy)->dummyVctor;
        
//        log("分身数量：%lu",copyDummy.size());
        
        for(std::vector<MonsterDummy *>::iterator dmIter=copyDummy.begin();dmIter!=copyDummy.end();dmIter++){
            
            bodyList.push_back((*dmIter));
            
        }
    }
    
    return bodyList;
}


//获取位置
Point Monster::getPosition()
{
    return this->cocos2d::Node::getPosition();
}

void Monster::setOpacity(GLubyte opacity)
{
    this->monsterAnimation->setOpacity(opacity);
}

//进入战斗
void Monster::enterBattle()
{
    if(_inCombat){
        log("已经在战斗中。");
        return;
    }
    
    //技能施放
    if(mstUsableAbiMap[MONSTER_ABILITY_GHOST]==1){
        //假身(1个)
        MonsterAbilityGhost::cast(this,this->property);
    }
    if(mstUsableAbiMap[MONSTER_ABILITY_COPY]==1){
        //分身(2个)
        MonsterAbilityCopy::cast(this,this->property);
        
        
        
        
        //光盾.2
//        MonsterAbilityLightShield::cast(this, this->property,true);
        
        
        
//        property->showUpTime=0.7;
////        //隐身
//        MonsterAbilityStealth::cast(this,this->property);
        
    }
    if(mstUsableAbiMap[MONSTER_ABILITY_LIGHT_SHIELD]==1){
        //光盾.2
        MonsterAbilityLightShield::cast(this, this->property,true);
    }
    if(mstUsableAbiMap[MONSTER_ABILITY_STEALTH]==1){
        //隐身
        MonsterAbilityStealth::cast(this,this->property);
    }
    
    
    //左右移动
    this->startMoving();
    
    showHealth(healthValue);
    
    this->_inCombat=true;
    this->isVictory=false;
}

//离开战斗
void Monster::leaveBattle()
{
    _inCombat=false;
}


//设置boss为已胜出
void Monster::setVictory(bool isVictory)
{
    this->isVictory=isVictory;
    if(isVictory){
        _inCombat=false;
        this->pause();
    }else{
        _inCombat=true;
        this->resume();
    }
}


//状态重置，包括血量
void Monster::reset()
{
    //停止动画
    if(repeatAct&&_inCombat==true){
        this->stopAction(repeatAct);
    }
    
    //停止战斗
    this->_inCombat=false;
    
    //重置攻击计时
    dtAttack=0;
    
    
    //重置位置
    this->setPositionX(SCREEN_WIDTH/2);
    
    //取消所有技能效果
    for(map<int,MonsterAbility *>::iterator itr=mstAbiMap.begin();itr!=mstAbiMap.end();itr++){
        if(itr->second){
            if(itr->second->isValid){
                itr->second->cancel();
            }
        }
    }
    
    //隐藏并重置血条
    if(this->health){
        this->health->hideHealth();
        health->setHealth(health->getOriginHealth());
    }
}

//左右移动
void Monster::startMoving()
{
//    if(this->isMoving){
//        log("boss已经在移动");
//        return;
//    }
    this->isMoving=true;
    
    //左右移动配置
    float speed=moveSpeed;
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

//是否在战斗中
bool Monster::inCombat()
{
    return _inCombat;
}

void Monster::pauseMoving()
{
    if(this->inCombat()&&this->isMoving){
        log("暂停移动");
        this->pause();
        isMoving=false;
        
        //分身坐标
        auto ghost=mstAbiMap[MONSTER_ABILITY_GHOST];
        if(ghost){
            auto ghostDummy=((MonsterAbilityGhost *)ghost)->dummyVctor;
            for(std::vector<MonsterDummy *>::iterator dmIter=ghostDummy.begin();dmIter!=ghostDummy.end();dmIter++){
                (*dmIter)->pause();
            }
            
        }
        //假身坐标
        auto copy=mstAbiMap[MONSTER_ABILITY_COPY];
        if(copy){
            auto copyDummy=((MonsterAbilityCopy *)copy)->dummyVctor;
            for(std::vector<MonsterDummy *>::iterator dmIter=copyDummy.begin();dmIter!=copyDummy.end();dmIter++){
                (*dmIter)->pause();
            }
        }
        
        
    }
    
}

void Monster::resumeMoving()
{
    if(this->inCombat()&&this->isMoving==false){
        log("继续移动");
        this->resume();
        isMoving=true;
        
        //分身坐标
        auto ghost=mstAbiMap[MONSTER_ABILITY_GHOST];
        if(ghost){
            auto ghostDummy=((MonsterAbilityGhost *)ghost)->dummyVctor;
            for(std::vector<MonsterDummy *>::iterator dmIter=ghostDummy.begin();dmIter!=ghostDummy.end();dmIter++){
                (*dmIter)->resume();
            }
            
        }
        //假身坐标
        auto copy=mstAbiMap[MONSTER_ABILITY_COPY];
        if(copy){
            auto copyDummy=((MonsterAbilityCopy *)copy)->dummyVctor;
            for(std::vector<MonsterDummy *>::iterator dmIter=copyDummy.begin();dmIter!=copyDummy.end();dmIter++){
                (*dmIter)->resume();
                
            }
        }
        
    }
    
}


//被攻击时调用,damage表示所受到的伤害值.
void Monster::hit(float damage,bool trueDamage)
{
    if(this->isVictory){
        log("boss已胜出，不再掉血");
        return;
    }
    
    log("受到伤害:%f",damage);
    
    //判断是否真实伤害
    if(!trueDamage){
        for(std::map<int,MonsterAbility *>::iterator itr=mstAbiMap.begin();itr!=mstAbiMap.end();itr++){
            if(itr->second){
                log("判断是否有效:%d",itr->second->isValid);
                
                if(itr->second->isValid){
                    damage=itr->second->hit(damage);
                }
            }else{
                
            }
        }
    }
    
    log("实际伤害:%f",damage);
    
    //判断血量是否大于0，大于0则扣血。
    if(health->getHealth()>0){
        health->addHealth(-damage);
        monsterAnimation->hit();
        //判断boss是否被此次攻击杀死
        if(health->getHealth()<=0){
            log("boss被击败");
            this->reset();
            //在此通知PlayScene玩家胜利。在角色死亡的一瞬间设置boss状态为胜出。
            if(monsterDelegate){
                monsterDelegate->onBattleEnd(2);
            }
        }
    }else{
        log("boss已死。。。。。。。。");
    }
    
    
}

//范围攻击
void Monster::hit(Vec2 pos1,Vec2 pos2,float damage,bool trueDamage)
{
    auto bdList=getBodyList();
    
    for(std::vector<Body *>::iterator itr=bdList.begin();itr!=bdList.end();itr++){
        auto bd=(*itr);
        
        if(bd->getPosition().x>=pos1.x&&bd->getPosition().x<=pos2.x){
            bd->hit(damage,trueDamage);
        }
        
    }
    
}



//攻击回调。
void Monster::onMonsterAnimationAttackCompleted()
{
    int type=atkCur->attackModeNumber;
    int power=atkCur->power;
    int speed=atkCur->speed;
    
    log("Monster attack callback.type:%d,power:%d,speed:%d",type,power,speed);
    if(monsterDelegate){
        //1-4是箱子。后边特殊。
        if((type>=1&&type<=4)||type==7){
            monsterDelegate->onMonsterAttack(type,power,speed);
        }else if(type==5||type==6){
            monsterDelegate->onMonsterCastSpell(type,speed);
        }
    }
}
void Monster::onMonsterAnimationShakeCompleted()
{
    log("ShakeCompleted in monster.");
}
void Monster::onMonsterAnimationHitCompleted()
{
    log("HitCompleted in monster.");
    //继续摇晃
    monsterAnimation->shake();
}
void Monster::onMonsterAnimationCheerCompleted()
{
    log("CheerCompleted in monster.");
    //继续摇晃
    monsterAnimation->shake();
}


//施法技能时
void Monster::onCast(MonsterAbility *abi)
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

//取消技能时
void Monster::onCancel(const int abiType)
{
    this->mstAbiMap[abiType]=0;
}









