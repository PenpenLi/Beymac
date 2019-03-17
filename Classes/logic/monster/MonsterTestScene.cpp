//
//  MonsterTestScene.cpp
//  beymac
//
//  Created by je on 4/24/15.
//
//

#include "MonsterTestScene.h"
#include "Monster.h"
#include "MonsterAbilityLightShield.h"
#include "MonsterAbilityGhost.h"
#include "MonsterAbilityCopy.h"
#include "MonsterAbilityStealth.h"

USING_NS_CC;
using namespace ui;


bool MonsterTestScene::init()
{
    auto m=Monster::createMonster(16);
    m->setPosition(320, 600);
    m->setTag(1);
    this->addChild(m);
    
    
    auto btnAttack=Button::create();
    btnAttack->cocos2d::Node::setPosition(100, 400);
    btnAttack->setTitleText("attack");
    btnAttack->setTitleFontSize(40);
    btnAttack->setTitleColor(Color3B::WHITE);
    btnAttack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            ((Monster *)this->getChildByTag(1))->attack();
        }
    });
    this->addChild(btnAttack);
    
    
    
    
    //被攻击
    {
        auto btnTest4=Button::create();
        btnTest4->cocos2d::Node::setPosition(250, 100);
        btnTest4->setTitleText("hit1");
        btnTest4->setTitleFontSize(40);
        btnTest4->setTitleColor(Color3B::WHITE);
        btnTest4->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                ((Monster *)this->getChildByTag(1))->getBodyList()[0]->hit(1);
            }
        });
        this->addChild(btnTest4);
    }
    {
        auto btnTest4=Button::create();
        btnTest4->cocos2d::Node::setPosition(350, 100);
        btnTest4->setTitleText("hit2");
        btnTest4->setTitleFontSize(40);
        btnTest4->setTitleColor(Color3B::WHITE);
        btnTest4->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                auto m=((Monster *)this->getChildByTag(1));
                if(m->getBodyList().size()>=2){
                    ((Monster *)this->getChildByTag(1))->getBodyList()[1]->hit(1);
                }
            }
        });
        this->addChild(btnTest4);
    }
    {
        auto btnTest4=Button::create();
        btnTest4->cocos2d::Node::setPosition(450, 100);
        btnTest4->setTitleText("hit3");
        btnTest4->setTitleFontSize(40);
        btnTest4->setTitleColor(Color3B::WHITE);
        btnTest4->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                auto m=((Monster *)this->getChildByTag(1));
                if(m->getBodyList().size()>=3){
                    ((Monster *)this->getChildByTag(1))->getBodyList()[2]->hit(1);
                }
            }
        });
        this->addChild(btnTest4);
    }
    
    auto btnTest5=Button::create();
    btnTest5->cocos2d::Node::setPosition(400, 200);
    btnTest5->setTitleText("reset");
    btnTest5->setTitleFontSize(40);
    btnTest5->setTitleColor(Color3B::WHITE);
    btnTest5->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            ((Monster *)this->getChildByTag(1))->reset();
        }
    });
    this->addChild(btnTest5);
    
    auto btnTest6=Button::create();
    btnTest6->cocos2d::Node::setPosition(400, 300);
    btnTest6->setTitleText("enterBattle");
    btnTest6->setTitleFontSize(40);
    btnTest6->setTitleColor(Color3B::WHITE);
    btnTest6->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            ((Monster *)this->getChildByTag(1))->enterBattle();
        }
    });
    this->addChild(btnTest6);
    
    {
        auto btnTest6=Button::create();
        btnTest6->cocos2d::Node::setPosition(100, 100);
        btnTest6->setTitleText("pause");
        btnTest6->setTitleFontSize(40);
        btnTest6->setTitleColor(Color3B::WHITE);
        btnTest6->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                ((Monster *)this->getChildByTag(1))->pauseMoving();
            }
        });
        this->addChild(btnTest6);
    }
    
    {
        auto btnTest6=Button::create();
        btnTest6->cocos2d::Node::setPosition(100, 200);
        btnTest6->setTitleText("resume");
        btnTest6->setTitleFontSize(40);
        btnTest6->setTitleColor(Color3B::WHITE);
        btnTest6->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                ((Monster *)this->getChildByTag(1))->resumeMoving();
            }
        });
        this->addChild(btnTest6);
    }
    
    
    
    
    auto s=DrawNode::create();
    s->drawPoint(Point(320,600), 5, Color4F::RED);
    this->addChild(s,300);
    
    
    scheduleUpdate();
    
//    schedule(schedule_selector(Monster::update),3);
    
    //进入战斗
//    ((Monster *)this->getChildByTag(1))->enterBattle();
    
    return true;
}

void MonsterTestScene::update(float dt)
{
    ((Monster *)this->getChildByTag(1))->onUpdate(dt);
    
}







