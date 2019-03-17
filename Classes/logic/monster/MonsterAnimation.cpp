//
//  MonsterAnimation.cpp
//  beymac
//
//  Created by je on 5/8/15.
//
//


#include "MonsterAnimation.h"
#include "Monster.h"
#include "Manager.h"


#define MOVEMENT_NAME_ATTACK "attack"
#define MOVEMENT_NAME_SHAKE "shake"
#define MOVEMENT_NAME_HIT "hit"
#define MOVEMENT_NAME_CHEER "win"

#define TAG_AMT 1


MonsterAnimation *MonsterAnimation::createMonsterAnimation(int number)
{
    std::string strBase="boss",str;
    strBase.append(StringUtils::format("%d_action",number));
    
    str=strBase;
    str.append(".ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo(str);
    auto ma=new MonsterAnimation();
    
    //boss编号
    ma->monsterType=number;
    
    auto amt=Armature::create(strBase);
    
    amt->setPosition(0, -120);
    
    ma->addChild(amt);
    amt->setTag(TAG_AMT);
    long animationCount=amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        if(strcmp(mn.c_str(), "shake")==0){
            amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=true;
        }else{
            amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
        }
    }
    
    if(ma&&ma->init()){
        ma->autorelease();
    }
    
    //尺寸
//    amt->setScale(0.3);
    
    
    ma->shake();
    return ma;
    
}


//初始化
bool MonsterAnimation::init()
{
    //获取骨骼动画对象
    auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
    
    //加入attack动画
    auto mHit=amt->getAnimation()->getAnimationData()->getMovement(MOVEMENT_NAME_HIT);
    auto md=MovementData::create();
    md->movBoneDataDic=mHit->movBoneDataDic;
    md->name=MOVEMENT_NAME_ATTACK;
//    md->loop=false;
    amt->getAnimation()->getAnimationData()->addMovement(md);
    
    //monster动画回调
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
            if(!monsterAnimationDelegate){
                log("Animation callback is null.");
                return;
            }
            if(strcmp(str.c_str(), MOVEMENT_NAME_SHAKE)==0){
                monsterAnimationDelegate->onMonsterAnimationShakeCompleted();
            }else if(strcmp(str.c_str(), MOVEMENT_NAME_HIT)==0){
                monsterAnimationDelegate->onMonsterAnimationHitCompleted();
            }else if(strcmp(str.c_str(), MOVEMENT_NAME_CHEER)==0){
                monsterAnimationDelegate->onMonsterAnimationCheerCompleted();
            }else if(strcmp(str.c_str(), MOVEMENT_NAME_ATTACK)==0){
                //                log("on attack.....");
            }
        }
    });
    
    return true;
}


void MonsterAnimation::setOpacity(GLubyte opacity)
{
    auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
    amt->setOpacity(opacity);
}


void MonsterAnimation::hit()
{
//    log("hit in ma");
    
    auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
    
    amt->getAnimation()->playWithIndex(0);
    
}

void MonsterAnimation::shake()
{
//    log("shake in ma");
    
    auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
    
    amt->getAnimation()->playWithIndex(1);
}


void MonsterAnimation::cheer()
{
//    log("cheer in ma");
    
    auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
    
    amt->getAnimation()->playWithIndex(2);
}

void MonsterAnimation::attack(const int atkType,const int atkPower)
{
    //攻击动画结束时调用
    auto onAttackCallfunc=CallFunc::create([&](){
        if(monsterAnimationDelegate){
            monsterAnimationDelegate->onMonsterAnimationAttackCompleted();
        }
    });
    
    //攻击音效
    if(this->monsterType>=1&&this->monsterType<=5&&atkType!=7){
        auto atkSound=StringUtils::format("bossAtk%d.mp3",this->monsterType);
        
        log("攻击音效:%s",atkSound.c_str());
        
        Manager::getInstance()->playSoundEffect(atkSound.c_str());
    }
    
    
    
    if(atkType>=1&&atkType<=5){
        this->atkType=atkType;
        this->atkPower=atkPower;
        //攻击动画
        auto bulletCallFunc=CallFunc::create([&](){
            std::string str="img_boss";
            
            str.append(StringUtils::format("%d",this->atkType));
            
            str.append("_stone.png");
            
            auto bullet=Sprite::create(str);
            if(bullet){
                //尺寸
                bullet->setScale(0.7);
                
                bullet->setPosition(0,30);
                
                auto mb=MoveBy::create(1, Vec2(0,1000));
                
                bullet->runAction(mb);
                
                this->addChild(bullet);
            }
        });
        //攻击动画
        Sequence *seqOnlyAnimation;
        //攻击回调
        Sequence *atkCallbackSeq;
        
        float atkIntervalTime=0.1;
        switch (atkPower) {
            case 1:
                //1个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc, NULL);
                break;
            case 2:
                //2个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 3:
                //3个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 4:
                //4个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 5:
                //5个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 6:
                //6个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 7:
                //7个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
            case 8:
                //8个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc,DelayTime::create(atkIntervalTime),bulletCallFunc, NULL);
                break;
                
            default:
                //默认——1个子弹
                seqOnlyAnimation=Sequence::create(bulletCallFunc, NULL);
                break;
        }
        
        auto amt=(Armature *)(this->getChildByTag(TAG_AMT));
        
        amt->getAnimation()->playWithIndex(3);
        
        this->runAction(seqOnlyAnimation);
        
        //开始回调,不等动画播完，1秒后回调
        atkCallbackSeq=Sequence::create(DelayTime::create(0.8),onAttackCallfunc, NULL);
        
        this->runAction(atkCallbackSeq);
        
    }else{
        //开始回调,不播动画，直接回调
        auto seq=Sequence::create(onAttackCallfunc, NULL);
        this->runAction(seq);
    }
    
}

