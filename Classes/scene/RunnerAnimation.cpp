//
//  RunnerAnimation.cpp
//  beymac
//
//  Created by je on 6/10/15.
//
//

#include "RunnerAnimation.h"
#include "CommonHeader.h"

#define FALL_HEIGHT 500
#define BOUND_LEFT 50
#define BOUND_RIGHT 590

#define AMT_SHOCK_1 "home_shock_1"
#define AMT_SHOCK_2 "home_shock_2"


RunnerAnimation *RunnerAnimation::create(RoleType type){
    auto ra=new RunnerAnimation();
    ra->roleType=type;
    if(ra&&ra->init()){
        ra->autorelease();
    }
    return ra;
}

bool RunnerAnimation::init(){
    ArmatureDataManager::getInstance()->addArmatureFileInfo("home_shock.ExportJson");
    
    amt=Armature::create("home_shock");
    
    
    
    amt->setPosition(0, -70);
    log("boss 高度：%f",amt->getContentSize().height);
    
    
    
    //monster动画回调
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
            if(strcmp(str.c_str(), AMT_SHOCK_2)==0){
                this->showRole();
            }
        }
    });
    
    
    amt->getAnimation()->playWithIndex(0);
    
    this->addChild(amt);
    
    
    runner= BeyMac::create();
    runner->setRoleType(roleType);
    runner->setScale(0.7);
    this->addChild(runner,5);
    
    
    return true;
}

//冲击波出现
void RunnerAnimation::fall()
{
    amt->setPosition(0, -70);
    
    auto func1=CallFunc::create([&](){
        this->amt->getAnimation()->playWithIndex(1);
    });
    
    auto mb=MoveBy::create(0.5, Vec2(0, -FALL_HEIGHT));
    
    auto seq=Sequence::create(mb,func1, NULL);
    
    amt->runAction(seq);
    
}

//人物出现
void RunnerAnimation::showRole()
{
    //将下落物体放回原位，否则会留在原地.
    amt->setPosition(0, -70);
    
    runner->setPosition(0, -FALL_HEIGHT-30);
    runner->setVisible(true);
    run();
}

//左右跑
void RunnerAnimation::run()
{
    runner->stopAllActions();
    
    
    const int speed=200;
    
    auto x=this->getPositionX();
    
    auto mb1=MoveBy::create(abs(BOUND_RIGHT-x)/speed, Vec2(BOUND_RIGHT-x, 0));
    
    auto mb2=MoveBy::create(abs(x-BOUND_RIGHT)/speed, Vec2(x-BOUND_RIGHT, 0));
    
    auto mb3=MoveBy::create(abs(BOUND_LEFT-x)/speed, Vec2(BOUND_LEFT-x, 0));
    
    auto mb4=MoveBy::create(abs(x-BOUND_LEFT)/speed, Vec2(x-BOUND_LEFT, 0));
    
    //左转
    auto turnLeft=CallFunc::create([&](){
        this->runner->playLeftAction();
    });
    //右转
    auto turnRight=CallFunc::create([&](){
        this->runner->playRightAction();
    });
    
    auto seq=Sequence::create(turnRight,mb1,turnLeft,mb2,mb3,turnRight,mb4, NULL);
    
    auto actRepeat=RepeatForever::create(seq);
    
    runner->runAction(actRepeat);
    
}

void RunnerAnimation::reset()
{
    amt->stopAllActions();
    runner->stopAllActions();
    runner->playStopAction();
    
    runner->setVisible(false);
}






