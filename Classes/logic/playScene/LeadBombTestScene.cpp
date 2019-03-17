//
//  LeadBombTestScene.cpp
//  beymac
//
//  Created by je on 6/16/15.
//
//

#include "LeadBombTestScene.h"

#include <CocosGUI.h>

using namespace ui;
using namespace cocostudio;

bool LeadBombTestScene::init()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lead_bomb.ExportJson");
    amt = Armature::create("lead_bomb");
    amt->setPosition(Vec2(320, 200));
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    this->addChild(amt,99);
    
    
    auto btn1=Button::create();
    btn1->cocos2d::Node::setPosition(100, 100);
    btn1->setTitleText("btn1");
    btn1->setTitleFontSize(30);
    btn1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            amt->getAnimation()->playWithIndex(0);
            
        }
    });
    this->addChild(btn1);
    
    
    auto btn2=Button::create();
    btn2->cocos2d::Node::setPosition(200, 100);
    btn2->setTitleText("btn1");
    btn2->setTitleFontSize(30);
    btn2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            amt->getAnimation()->playWithIndex(2);
            
        }
    });
    this->addChild(btn2);
    
    auto btn3=Button::create();
    btn3->cocos2d::Node::setPosition(300, 100);
    btn3->setTitleText("btn3");
    btn3->setTitleFontSize(30);
    btn3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            amt->getAnimation()->playWithIndex(4);
            
        }
    });
    this->addChild(btn3);
 
    
    
    
    return true;
}