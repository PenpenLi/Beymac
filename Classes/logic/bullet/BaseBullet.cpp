//
//  BaseBullet.cpp
//  beymac
//
//  Created by wang on 15/5/13.
//
//

#include "BaseBullet.h"
#include "Macro.h"
#include "BaseRole.h"
#include "BeyMac.h"
#include "PlayScene.h"

BaseBullet::BaseBullet()
:delegate()
,attack(0)
{
    type = BulletType_NULL;
}

BaseBullet::~BaseBullet()
{

}

bool BaseBullet::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void BaseBullet::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void BaseBullet::onExit()
{
    Node::onExit();
}

int getRow( float x )
{
    if (x < 0 && x > SCREEN_WIDTH) {
        return 0;
    }
    for (int i = 1; i <= 8; i++) {
        if (x <= i * GRID_SIZE) {
            //            log("my row = %d",i);
            return i;
        }
    }
    return 0;
}

void BaseBullet::boxBangAction(float x, float y) {
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bomb_action.ExportJson");
    auto amt = Armature::create("bomb_action");
    amt->setPosition(x,y);
    amt->setScale(2);
    amt->setTag(141);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    if (getParent()) {
        getParent()->addChild(amt,201);
    }
    
    amt->getAnimation()->playWithIndex(0);
}

void BaseBullet::boxBangActionIce(float x, float y)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bomb_action2.ExportJson");
    auto amt = Armature::create("bomb_action2");
    amt->setPosition(x,y);
    amt->setScale(2);
    amt->setTag(141);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }

    if (getParent()) {
        getParent()->addChild(amt,201);
    }
    
    amt->getAnimation()->playWithIndex(0);
}