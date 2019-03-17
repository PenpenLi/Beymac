//
//  RoleWeaponUpgradeScene.cpp
//  beymac
//
//  Created by je on 5/21/15.
//
//

#include "RoleSkillUpgradeScene.h"
#include "CommonHeader.h"
#include "ButtonFactory.h"


#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")
#define SKILL_MAX_LEVEL 5


#define SKILL1 1
//#define SKILL2 2
//#define SKILL3 3
//#define SKILL4 4
//#define SKILL5 5
//#define SKILL6 6
//#define SKILL7 7
//#define SKILL8 8

#define SKILL_COUNT 8

//技能tag从101开始
#define TAG_SKILL_FIRST 1
//等级文本从201开始
#define TAG_SKILL_TEXT_FIRST 201


USING_NS_CC;

using namespace ui;

Scene *RoleSkillUpgradeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RoleSkillUpgradeScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

Sprite *RoleSkillUpgradeScene::test()
{
    auto sprTest=Sprite::create();
    sprTest->setTag(901);
    
    //升级按钮
    auto btnUpgrade=Button::create();
    btnUpgrade->cocos2d::Node::setPosition(200, 200);
    btnUpgrade->setTitleText("升级");
    btnUpgrade->setTitleFontSize(50);
    btnUpgrade->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            int level=CommonData::getInstance()->getRoleSkillLevel(selectSkill);
            if(level>=5){
            }else{
                upgrade(selectSkill);
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
            for(int i=0;i<SKILL_COUNT;i++){
                CommonData::getInstance()->setRoleSkillLevel(i+1, 0);
            }
//            CommonData::getInstance()->setRoleLevel(SKILL2, 0);
//            CommonData::getInstance()->setRoleLevel(SKILL3, 0);
            this->refreshRolesLevel();
        }
    });
    
    for(int i=0;i<SKILL_COUNT;i++){
        //角色1
        auto btnskill=Button::create();
        btnskill->setTag(i+TAG_SKILL_FIRST);
        btnskill->cocos2d::Node::setPosition(100, 800-i*50);
        btnskill->setTitleText(StringUtils::format("技能%d",i+1));
        btnskill->setTitleFontSize(50);
        btnskill->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                auto btnSkillNode=(Node *)pSender;
                
                selectSkill=btnSkillNode->getTag();
                log("当前角色设为:%d,等级:%d",selectSkill,CommonData::getInstance()->getRoleSkillLevel(selectSkill));
                
                //变色
                btnSkillNode->setColor(Color3B::WHITE);
                for(int j=0;j<SKILL_COUNT;j++){
                    if(j+TAG_SKILL_FIRST!=selectSkill){
                        this->getChildByTag(j+TAG_SKILL_FIRST)->setColor(Color3B::GRAY);
                    }
                }
                this->refreshRolesLevel();
                
            }
        });
        
        if(i==0){
            btnskill->setColor(Color3B::WHITE);
        }else{
            btnskill->setColor(Color3B::GRAY);
        }
        
        this->addChild(btnskill);
        
        //角色1等级
        auto txtRole1Level=Text::create();
        txtRole1Level->setTag(i+TAG_SKILL_TEXT_FIRST);
        txtRole1Level->setFontSize(50);
        txtRole1Level->cocos2d::Node::setPosition(400, 25);
        txtRole1Level->setColor(Color3B::GREEN);
        btnskill->addChild(txtRole1Level);
        
    }
    
    refreshRolesLevel();
    
    
    sprTest->addChild(btnUpgrade);
    sprTest->addChild(btnReset);
    return sprTest;
}

bool RoleSkillUpgradeScene::init()
{
    selectSkill=TAG_SKILL_FIRST;
    
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
            Director::getInstance()->popScene();
        }
    });
    
    
    
    
    this->addChild(bg,-10);
    this->addChild(head);
    this->addChild(test());
    this->addChild(btnBack);
    return true;
}


//角色升级
void RoleSkillUpgradeScene::upgrade(int role)
{
    int level=CommonData::getInstance()->getRoleSkillLevel(role);
    
    CommonData::getInstance()->setRoleSkillLevel(role, level+1);
    
    log("角色%d升级成功，当前等级:%d",role,CommonData::getInstance()->getRoleSkillLevel(role));
    
    
    refreshRolesLevel();
}

//刷新等级
void RoleSkillUpgradeScene::refreshRolesLevel()
{
    for(int i=0;i<SKILL_COUNT;i++){
        auto btnSkill=(Button *)(this->getChildByTag(i+TAG_SKILL_FIRST));
        auto txtLevel=(Text *)(btnSkill->getChildByTag(i+TAG_SKILL_TEXT_FIRST));
        txtLevel->setString(StringUtils::format("等级:%d",CommonData::getInstance()->getRoleSkillLevel(i+TAG_SKILL_FIRST)));
        
    }
}
