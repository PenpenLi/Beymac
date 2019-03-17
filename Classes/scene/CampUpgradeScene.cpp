//
//  CampUpgradeScene.cpp
//  beymac
//
//  Created by je on 4/21/15.
//
//

#include "CampUpgradeScene.h"
#include "Macro.h"
#include "HomeScene.h"
#include "ButtonFactory.h"
#include "RoleSkillUpgradeScene.h"


#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")
#define ROLE_MAX_LEVEL 5

USING_NS_CC;

using namespace ui;

Sprite *CampUpgradeScene::test()
{
    auto sprTest=Sprite::create();
    
    //升级按钮
    auto btnUpgrade=Button::create();
    btnUpgrade->cocos2d::Node::setPosition(200, 200);
    btnUpgrade->setTitleText("升级");
    btnUpgrade->setTitleFontSize(50);
    btnUpgrade->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            int level=CommonData::getInstance()->getRoleLevel(selectRole);
            if(level>=5){
            }else{
                upgrade(selectRole);
            }
        }
    });
    
    //reset
    
    auto btnReset=Button::create();
    btnReset->cocos2d::Node::setPosition(400, 200);
    btnReset->setTitleText("重置");
    btnReset->setTitleFontSize(50);
    btnReset->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            CommonData::getInstance()->setRoleLevel(ROLE1, 0);
            CommonData::getInstance()->setRoleLevel(ROLE2, 0);
            CommonData::getInstance()->setRoleLevel(ROLE3, 0);
            this->refreshRolesLevel();
        }
    });
    
    
    //角色1
    btnRole1=Button::create();
    btnRole1->cocos2d::Node::setPosition(100, 800);
    btnRole1->setTitleText("角色1");
    btnRole1->setTitleFontSize(50);
    btnRole1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            selectRole=ROLE1;
            log("当前角色设为:%d,等级:%d",selectRole,CommonData::getInstance()->getRoleLevel(selectRole));
            
            btnRole1->setColor(Color3B::WHITE);
            btnRole2->setColor(Color3B::GRAY);
            btnRole3->setColor(Color3B::GRAY);
        }
    });
    
    //角色2
    btnRole2=Button::create();
    btnRole2->cocos2d::Node::setPosition(100, 600);
    btnRole2->setTitleText("角色2");
    btnRole2->setTitleFontSize(50);
    btnRole2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            selectRole=ROLE2;
            log("当前角色设为:%d,等级:%d",selectRole,CommonData::getInstance()->getRoleLevel(selectRole));
            
            btnRole1->setColor(Color3B::GRAY);
            btnRole2->setColor(Color3B::WHITE);
            btnRole3->setColor(Color3B::GRAY);
        }
    });
    
    //角色3
    btnRole3=Button::create();
    btnRole3->cocos2d::Node::setPosition(100, 400);
    btnRole3->setTitleText("角色3");
    btnRole3->setTitleFontSize(50);
    btnRole3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            selectRole=ROLE3;
            log("当前角色设为:%d,等级:%d",selectRole,CommonData::getInstance()->getRoleLevel(selectRole));
            
            btnRole1->setColor(Color3B::GRAY);
            btnRole2->setColor(Color3B::GRAY);
            btnRole3->setColor(Color3B::WHITE);
        }
    });
    
    
    //角色1等级
    txtRole1Level=Text::create();
    txtRole1Level->setFontSize(50);
    txtRole1Level->cocos2d::Node::setPosition(400, 25);
    txtRole1Level->setColor(Color3B::GREEN);
    btnRole1->addChild(txtRole1Level);
    
    //角色1等级
    txtRole2Level=Text::create();
    txtRole2Level->setFontSize(50);
    txtRole2Level->cocos2d::Node::setPosition(400, 25);
    txtRole2Level->setColor(Color3B::GREEN);
    btnRole2->addChild(txtRole2Level);
    
    //角色1等级
    txtRole3Level=Text::create();
    txtRole3Level->setFontSize(50);
    txtRole3Level->cocos2d::Node::setPosition(400, 25);
    txtRole3Level->setColor(Color3B::GREEN);
    btnRole3->addChild(txtRole3Level);
    
    
    refreshRolesLevel();
    
    
    
    //初始角色为role1
    selectRole=ROLE1;
    //btn
    btnRole1->setColor(Color3B::WHITE);
    btnRole2->setColor(Color3B::GRAY);
    btnRole3->setColor(Color3B::GRAY);
    
    
    sprTest->addChild(btnRole1);
    sprTest->addChild(btnRole2);
    sprTest->addChild(btnRole3);
    sprTest->addChild(btnUpgrade);
    sprTest->addChild(btnReset);
    return sprTest;
}

bool CampUpgradeScene::init()
{
    //背景
    auto bg=Sprite::create("img_lucky_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    
    //头部
    auto head=Sprite::create("img_upgrade_title_bg.png");
    head->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-head->getContentSize().height/2);
    
    //返回
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_back.png");
    btnBack->setPosition(Point(70,SCREEN_HEIGHT-head->getContentSize().height/2));
    //    btnBack->setTitleText("返回");
    btnBack->setTitleFontSize(50);
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(HomeScene::create());
        }
    });
    

    //技能升级
    auto btnSkillUpgrade=Button::create();
    btnSkillUpgrade->cocos2d::Node::setPosition(100, 70);
    btnSkillUpgrade->setTitleFontSize(40);
    btnSkillUpgrade->setTitleText("技能升级");
    btnSkillUpgrade->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->pushScene(RoleSkillUpgradeScene::createScene());
        }
    });
    this->addChild(btnSkillUpgrade);
    
    
    this->addChild(bg,-10);
    this->addChild(head);
    this->addChild(test());
    this->addChild(btnBack);
    return true;
}


//角色升级
void CampUpgradeScene::upgrade(int role)
{
    int level=CommonData::getInstance()->getRoleLevel(role);
    
    CommonData::getInstance()->setRoleLevel(role, level+1);
    
    log("角色%d升级成功，当前等级:%d",role,CommonData::getInstance()->getRoleLevel(role));
    
    
    refreshRolesLevel();
}

//刷新等级
void CampUpgradeScene::refreshRolesLevel()
{
    txtRole1Level->setString(StringUtils::format("等级:%d",CommonData::getInstance()->getRoleLevel(ROLE1)));
    txtRole2Level->setString(StringUtils::format("等级:%d",CommonData::getInstance()->getRoleLevel(ROLE2)));
    txtRole3Level->setString(StringUtils::format("等级:%d",CommonData::getInstance()->getRoleLevel(ROLE3)));
}
