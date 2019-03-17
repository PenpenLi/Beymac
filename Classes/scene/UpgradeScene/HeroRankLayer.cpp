//
//  HeroRankLayer.cpp
//  beymac
//
//  Created by mumu on 15/5/28.
//
//

#include "HeroRankLayer.h"
#include "Macro.h"
#include "MMLocalizedString.h"
#include "Manager.h"
#include "CommonData.h"

#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")

HeroRankLayer::HeroRankLayer()
{

}

HeroRankLayer::~HeroRankLayer()
{

}

bool HeroRankLayer::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initBG();
    return true;
}

void HeroRankLayer::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void HeroRankLayer::onExit()
{
    Node::onExit();
}

void HeroRankLayer::initBG()
{
    Sprite* background = Sprite::create("img_upgrade_sort_bg.jpg");
    background->setPosition(SCREEN_CENTER);
    addChild(background);
    
    bg1 = Sprite::create("img_upgrade_sort_whitebg.png");
    bg1->setPosition(SCREEN_CENTER+Vec2(-10, 270));
    addChild(bg1);
    
    bg2 = Sprite::create("img_upgrade_sort_whitebg.png");
    bg2->setPosition(SCREEN_CENTER+Vec2(-10,-20));
    addChild(bg2);
    
    bg3 = Sprite::create("img_upgrade_sort_whitebg.png");
    bg3->setPosition(SCREEN_CENTER-Vec2(10, 320));
    addChild(bg3);
    
    nodeBeymac = Node::create();
    nodeBeymac->setPosition(bg1->getPosition());
    addChild(nodeBeymac,50);
    
    nodeLaser = Node::create();
    nodeLaser->setPosition(bg3->getPosition());
    addChild(nodeLaser,50);
    
    nodeTomago = Node::create();
    nodeTomago->setPosition(bg2->getPosition());
    addChild(nodeTomago,50);
    
    
    Label* info = Label::create();
    info->setAnchorPoint(Vec2(0.5,0.5));
    info->setString(LSTRING("HeroRank_info"));
    info->setSystemFontSize(21);
    info->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT-150);
    addChild(info,999);
    
    btn1_down=Button::create("img_upgrade_arrow_bottom_white.png","img_upgrade_arrow_bottom_gray.png");
    btn1_down->setPosition(Vec2( SCREEN_WIDTH-75,SCREEN_HEIGHT-290 ));
    btn1_down->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            int t = ranklist[0];
            ranklist[0] = ranklist[1];
            ranklist[1] = t;
            
            refreshHero();
        }
    });
    addChild(btn1_down);
    
    btn2_up=Button::create("img_upgrade_arrow_top_white.png","img_upgrade_arrow_top_gray.png");
    btn2_up->setPosition(btn1_down->getPosition()-Vec2(0,250));
    btn2_up->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            int t = ranklist[0];
            ranklist[0] = ranklist[1];
            ranklist[1] = t;
            
            refreshHero();
        }
    });
    addChild(btn2_up);
    
    btn2_down=Button::create("img_upgrade_arrow_bottom_white.png","img_upgrade_arrow_bottom_gray.png");
    btn2_down->setPosition(btn2_up->getPosition()-Vec2(0,100));
    btn2_down->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            int t = ranklist[1];
            ranklist[1] = ranklist[2];
            ranklist[2] = t;
            
            refreshHero();
        }
    });
    addChild(btn2_down);
    
    btn3_up=Button::create("img_upgrade_arrow_top_white.png","img_upgrade_arrow_top_gray.png");
    btn3_up->setPosition(btn2_down->getPosition()-Vec2(0,250));
    btn3_up->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            int t = ranklist[1];
            ranklist[1] = ranklist[2];
            ranklist[2] = t;
            
            refreshHero();
        }
    });
    addChild(btn3_up);
    
    btn1_down->setHighlighted(true);
    btn1_down->setEnabled(false);
    btn2_up->setHighlighted(true);
    btn2_up->setEnabled(false);
    btn2_down->setHighlighted(true);
    btn2_down->setEnabled(false);
    btn3_up->setHighlighted(true);
    btn3_up->setEnabled(false);
    
    initRoleInfo();
    refreshBtn();
}

void HeroRankLayer::initRoleInfo()
{
    Sprite* baymacImage = Sprite::create("img_upgrade_baymax.png");
    baymacImage->setScale(0.7);
    baymacImage->setPosition(-120,0);
    nodeBeymac->addChild(baymacImage);
    
    Label* baymacName = Label::create();
    baymacName->setAnchorPoint(Vec2(0,0.5));
    baymacName->setString(LSTRING("Baymac"));
    baymacName->setSystemFontSize(40);
    baymacName->setPosition(-25,55);
    nodeBeymac->addChild(baymacName);
    
    Label* baymacInfo = Label::create();
    baymacInfo->setAnchorPoint(Vec2(0,0.5));
    baymacInfo->setString(LSTRING("Baymac_info2"));
    baymacInfo->setColor(Color3B(255,120,119));
    baymacInfo->setSystemFontSize(21);
    baymacInfo->setPosition(-25,-35);
    baymacInfo->setDimensions(215, 100);
    nodeBeymac->addChild(baymacInfo);
    
    Label* baymacInfo2 = Label::create();
    baymacInfo2->setAnchorPoint(Vec2(0,0.5));
    baymacInfo2->setString(LSTRING("Baymac_info3"));
    baymacInfo2->setSystemFontSize(21);
    baymacInfo2->setPosition(-25,-105);
    baymacInfo2->setDimensions(215, 100);
    nodeBeymac->addChild(baymacInfo2);
    
    Sprite* laserImage = Sprite::create("img_upgrade_brother.png");
    laserImage->setScale(0.7);
    laserImage->setPosition(-120,0);
    nodeLaser->addChild(laserImage);
    
    Label* laserName = Label::create();
    laserName->setAnchorPoint(Vec2(0,0.5));
    laserName->setString(LSTRING("Laser"));
    laserName->setSystemFontSize(40);
    laserName->setPosition(-25,55);
    nodeLaser->addChild(laserName);
    
    Label* laserInfo = Label::create();
    laserInfo->setAnchorPoint(Vec2(0,0.5));
    laserInfo->setString(LSTRING("Laser_info2"));
    laserInfo->setColor(Color3B(255,120,119));
    laserInfo->setSystemFontSize(21);
    laserInfo->setPosition(-25,-35);
    laserInfo->setDimensions(215, 100);
    nodeLaser->addChild(laserInfo);
    
    Label* laserInfo2 = Label::create();
    laserInfo2->setAnchorPoint(Vec2(0,0.5));
    laserInfo2->setString(LSTRING("Laser_info3"));
    laserInfo2->setSystemFontSize(21);
    laserInfo2->setPosition(-25,-85);
    laserInfo2->setDimensions(215, 100);
    nodeLaser->addChild(laserInfo2);
    
    Sprite* tomagoImage = Sprite::create("img_upgrade_sister.png");
    tomagoImage->setScale(0.7);
    tomagoImage->setPosition(-120,0);
    nodeTomago->addChild(tomagoImage);
    
    Label* tomagoName = Label::create();
    tomagoName->setAnchorPoint(Vec2(0,0.5));
    tomagoName->setString(LSTRING("Tomago"));
    tomagoName->setSystemFontSize(40);
    tomagoName->setPosition(-25,55);
    nodeTomago->addChild(tomagoName);
    
    Label* tomagoInfo = Label::create();
    tomagoInfo->setAnchorPoint(Vec2(0,0.5));
    tomagoInfo->setString(LSTRING("Tomago_info2"));
    tomagoInfo->setColor(Color3B(255,120,119));
    tomagoInfo->setSystemFontSize(21);
    tomagoInfo->setPosition(-25,-35);
    tomagoInfo->setDimensions(215, 100);
    nodeTomago->addChild(tomagoInfo);
    
    Label* tomagoInfo2 = Label::create();
    tomagoInfo2->setAnchorPoint(Vec2(0,0.5));
    tomagoInfo2->setString(LSTRING("Tomago_info3"));
    tomagoInfo2->setSystemFontSize(21);
    tomagoInfo2->setPosition(-25,-85);
    tomagoInfo2->setDimensions(215, 100);
    nodeTomago->addChild(tomagoInfo2);
    
    ranklist.push_back(CommonData::getInstance()->getRoleByPosition(1));
    ranklist.push_back(CommonData::getInstance()->getRoleByPosition(2));
    ranklist.push_back(CommonData::getInstance()->getRoleByPosition(3));
    
    refreshHero();
}

// 更新英雄排序
void HeroRankLayer::refreshHero()
{
    for (int i = 0; i < ranklist.size(); i++) {
        Vec2 p;
        if (i == 0) {
            p = bg1->getPosition();
        }
        else if (i == 1)
        {
            p = bg2->getPosition();
        }
        else if (i == 2)
        {
            p = bg3->getPosition();
        }
        
        if (ranklist[i] == 1) {
            nodeBeymac->setPosition(p);
        }
        else if (ranklist[i] == 2)
        {
            nodeLaser->setPosition(p);
        }
        else if (ranklist[i] == 3)
        {
            nodeTomago->setPosition(p);
        }
        
        CommonData::getInstance()->setRoleToPosition(i+1, ranklist[i]);
    }
}

void HeroRankLayer::refreshBtn()
{
    if (CommonData::getInstance()->getRoleLevel(3)>0 && CommonData::getInstance()->getRoleLevel(2)>0) {
        btn1_down->setHighlighted(false);
        btn1_down->setEnabled(true);
        btn2_up->setHighlighted(false);
        btn2_up->setEnabled(true);
        btn2_down->setHighlighted(false);
        btn2_down->setEnabled(true);
        btn3_up->setHighlighted(false);
        btn3_up->setEnabled(true);
    }
    else if (CommonData::getInstance()->getRoleLevel(2)>0 || CommonData::getInstance()->getRoleLevel(3)>0)
    {
        if (CommonData::getInstance()->getRoleLevel(2)>0) {
            if (CommonData::getInstance()->getRoleByPosition(2) == 3) {
                
                ranklist[1] = 2;
                ranklist[2] = 3;
            }
        }
        else if (CommonData::getInstance()->getRoleLevel(3)>0)
        {
            
            if (CommonData::getInstance()->getRoleByPosition(2) == 2) {
                
                ranklist[1] = 3;
                ranklist[2] = 2;
            }
        }
        btn1_down->setHighlighted(false);
        btn1_down->setEnabled(true);
        btn2_up->setHighlighted(false);
        btn2_up->setEnabled(true);
        btn2_down->setHighlighted(true);
        btn2_down->setEnabled(false);
        btn3_up->setHighlighted(true);
        btn3_up->setEnabled(false);
    }
    else
    {
        ranklist[0] = 1;
        ranklist[1] = 3;
        ranklist[2] = 2;
        btn1_down->setHighlighted(true);
        btn1_down->setEnabled(false);
        btn2_up->setHighlighted(true);
        btn2_up->setEnabled(false);
        btn2_down->setHighlighted(true);
        btn2_down->setEnabled(false);
        btn3_up->setHighlighted(true);
        btn3_up->setEnabled(false);
    }
}