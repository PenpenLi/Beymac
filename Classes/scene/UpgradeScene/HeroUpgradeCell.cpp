//
//  HeroUpgradeCell.cpp
//  beymac
//
//  Created by mumu on 15/6/9.
//
//

#include "HeroUpgradeCell.h"
#include "UpgradeScene.h"
#include "ShopScene.h"

#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")

HeroUpgradeCell::HeroUpgradeCell(RoleType t)
:delegate()
{
    type = t;
    if (type == BeymacType) {
        iType = 1;
    }
    else if (type == LaserType)
    {
        iType = 2;
    }
    else if (type == TomagoType)
    {
        iType = 3;
    }
}

HeroUpgradeCell::~HeroUpgradeCell()
{

}

bool HeroUpgradeCell::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initBG();
    initAboutUpgrade();
//    initPopup();
    
    return true;
}

void HeroUpgradeCell::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void HeroUpgradeCell::onExit()
{
    Node::onExit();
}

HeroUpgradeCell* HeroUpgradeCell::create(RoleType type)
{
    HeroUpgradeCell* node = new HeroUpgradeCell(type);
    if (node && node->init()) {
        node->autorelease();
        
    }
    else
    {
        delete node;
        node = NULL;
    }
    
    return node;
}

void HeroUpgradeCell::initBG()
{
    Sprite* background = Sprite::create("img_upgrade_lead_bg_small.png");
    background->setPosition(0,0);
    addChild(background);
    
    btnUpgrade=Button::create("img_window_green.png");
    btnUpgrade->setPosition(Vec2(-150,-230));
    btnUpgrade->setTitleText(LSTRING("Upgrade"));
    btnUpgrade->setTitleColor(Color3B(12, 63, 10));
    btnUpgrade->setTitleFontSize(35);
    btnUpgrade->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            int level=CommonData::getInstance()->getRoleLevel(iType);
            if(level>=4){
                
            }else{
                // 扣钱
                int c = 0;
                if (level == 1) {
                    c = 30;
                }
                else if (level == 2)
                {
                    c = 50;
                }
                else if (level == 3)
                {
                    c = 70;
                }
                
                //                c = 0;
                
                if (CommonData::getInstance()->getCrystal() >= c) {
                    CommonData::getInstance()->addCrystal(-c);
                    CommonData::getInstance()->setRoleLevel(iType, level+1);
                    if (Director::getInstance()->getRunningScene()->getChildByTag(100)) {
                        UpgradeScene* layer = (UpgradeScene*)Director::getInstance()->getRunningScene()->getChildByTag(100);
                        layer->refreshCrystal();
                    }
                    
                }
                else
                {
                    Director::getInstance()->pushScene(ShopScene::create());
                }
                
                
            }
            
            refreshLevel();
            refreshBtn();
        }
    });
    addChild(btnUpgrade);
    
    btnAllUpgrade=Button::create("img_window_btn_red.png");
    btnAllUpgrade->setPosition(Vec2(150, btnUpgrade->getPositionY()));
    btnAllUpgrade->setTitleText(LSTRING("AllUpgrade"));
    btnAllUpgrade->setTitleFontSize(35);
    btnAllUpgrade->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
//            if (CommonData::getInstance()->getRoleLevel(iType) < 4) {
//                
//                if (iType == 1) {
////                    popupImage->setTexture("img_upgrade_baymax.png");
//                }
//                else if (iType == 2)
//                {
//                    popupImage->setTexture("img_upgrade_brother.png");
//                }
//                else if (iType == 3)
//                {
//                    popupImage->setTexture("img_upgrade_sister.png");
//                }
//                
//                
//                popupOneKeyUpRole->show();
//            }
            
            if (delegate) {
                delegate->HeroUpgradeCellDelegateOneKeyUp(type);
            }
            
        }
    });
    addChild(btnAllUpgrade);
    
    btnUnlock=Button::create("img_window_btn_red.png");
    btnUnlock->setPosition(Vec2(0, btnUpgrade->getPositionY()));
    btnUnlock->setTitleText(LSTRING("UNLOCK"));
    btnUnlock->setTitleFontSize(35);
    btnUnlock->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            if (delegate) {
                delegate->HeroUpgradeCellDelegateUnlockHero(type);
            }
        }
    });
    addChild(btnUnlock);
    
    refreshBtn();
    
    const char* iconName = "img_icon_power2.png";
    const char* roleName = "img_upgrade_baymax.png";
    const char* roleInfo = "Baymac_info";
    const char* name = "Baymac";
    
    if (type == BeymacType) {
        
    }
    else if (type == LaserType)
    {
        iconName = "img_icon_power.png";
        roleName = "img_upgrade_brother.png";
        roleInfo = "Laser_info";
        name = "Laser";
    }
    else if (type == TomagoType)
    {
        iconName = "img_icon_faster.png";
        roleName = "img_upgrade_sister.png";
        roleInfo = "Tomago_info";
        name = "Tomago";
    }
    
    Sprite* role = Sprite::create(roleName);
    role->setPosition(-160, 40 );
    addChild(role);
    
    Sprite* icon = Sprite::create(iconName);
    icon->setPosition(-160, 200 );
    addChild(icon);
    
    Label* info = Label::create();
    info->setTextColor(Color4B::WHITE);
    info->setAnchorPoint(Vec2(0.5,0.5));
    info->setString(LSTRING(roleInfo));
    info->setSystemFontSize(18);
    info->setDimensions(200, 120);
    info->setPosition(-160,-150);
    info->setHorizontalAlignment(TextHAlignment::CENTER);
    info->setVerticalAlignment(TextVAlignment::CENTER);
    addChild(info);
    
    Label* title = Label::create();
    title->setTextColor(Color4B::WHITE);
    title->setAnchorPoint(Vec2(0.5,0.5));
    title->setString(LSTRING(name));
    title->setSystemFontSize(35);
    title->setPosition(0,250);

    addChild(title);
}
void HeroUpgradeCell::refreshBtn()
{
    curlevel = CommonData::getInstance()->getRoleLevel(iType);
    
    if (curlevel >= 4) {
        btnUnlock->setVisible(false);
        btnAllUpgrade->setVisible(true);
        btnUpgrade->setVisible(true);
        btnAllUpgrade->setEnabled(false);
        btnAllUpgrade->setColor(Color3B::GRAY);
        btnUpgrade->setEnabled(false);
        btnUpgrade->setColor(Color3B::GRAY);
    }
    else if ( curlevel > 0 )
    {
        btnUnlock->setVisible(false);
        btnAllUpgrade->setVisible(true);
        btnUpgrade->setVisible(true);
        btnAllUpgrade->setEnabled(true);
        btnAllUpgrade->setColor(Color3B::WHITE);
        btnUpgrade->setEnabled(true);
        btnUpgrade->setColor(Color3B::WHITE);
    }
    else
    {
        btnUnlock->setVisible(true);
        btnAllUpgrade->setVisible(false);
        btnUpgrade->setVisible(false);
    }
}
void HeroUpgradeCell::initAboutUpgrade()
{
    
    const char* iconName = "img_icon_power2_small.png";
    const char* l1 = "85%";
    const char* l2 = "75%";
    const char* l3 = "65%";
    const char* l4 = "50%";
    const char* up_info = "BaymacUp_info";
    curlevel = 1;
    
    curlevel = CommonData::getInstance()->getRoleLevel(iType);
    if (type == BeymacType) {
        
    }
    else if (type == LaserType)
    {
        iconName = "img_icon_power_small.png";
        l1 = "150%";
        l2 = "180%";
        l3 = "210%";
        l4 = "250%";
        up_info = "LaserUp_info";
    }
    else if (type == TomagoType)
    {
        iconName = "img_icon_faster_small.png";
        l1 = "130%";
        l2 = "160%";
        l3 = "190%";
        l4 = "220%";
        up_info = "TomagoUp_info";
    }

    // 等级背景
    Sprite* level1_bg = Sprite::create("img_upgrade_icon_lock.png");
    level1_bg->setPosition(7, 180);
    addChild(level1_bg);
    
    Sprite* level2_bg = Sprite::create("img_upgrade_icon_lock.png");
    level2_bg->setPosition(level1_bg->getPosition() + Vec2(0, -105));
    addChild(level2_bg);
    
    Sprite* level3_bg = Sprite::create("img_upgrade_icon_lock.png");
    level3_bg->setPosition(level2_bg->getPosition() + Vec2(0,-105));
    addChild(level3_bg);
    
    Sprite* level4_bg = Sprite::create("img_upgrade_icon_lock.png");
    level4_bg->setPosition(level3_bg->getPosition() + Vec2(0, -105));
    addChild(level4_bg);
    
    // 箭头
    Sprite* arrow1= Sprite::create("img_icon_arrow.png");
    arrow1->setPosition(level1_bg->getPosition() + Vec2(0, -55));
    addChild(arrow1);
    
    Sprite* arrow2 = Sprite::create("img_icon_arrow.png");
    arrow2->setPosition(level2_bg->getPosition() + Vec2(0, -55));
    addChild(arrow2);
    
    Sprite* arrow3 = Sprite::create("img_icon_arrow.png");
    arrow3->setPosition(level3_bg->getPosition() + Vec2(0, -55));
    addChild(arrow3);
    
    level1 = Node::create();
    level1->setPosition(level1_bg->getPosition());
    addChild(level1);
    
    Sprite* level1_ = Sprite::create("img_upgrade_icon_unlock.png");
    level1_->setPosition(0,0);
    level1->addChild(level1_);
    
    Label* level1_txt = Label::create();
    level1_txt->setTextColor(Color4B::BLACK);
    level1_txt->setAnchorPoint(Vec2(0.5,0.5));
    level1_txt->setString(l1);
    level1_txt->setSystemFontSize(20);
    level1_txt->setPosition(Vec2(0,0));
    level1->addChild(level1_txt);
    
    level2 = Node::create();
    level2->setPosition(level2_bg->getPosition());
    addChild(level2);
    
    Sprite* level2_ = Sprite::create("img_upgrade_icon_unlock.png");
    level2_->setPosition(0,0);
    level2->addChild(level2_);
    
    Label* level2_txt = Label::create();
    level2_txt->setTextColor(Color4B::BLACK);
    level2_txt->setAnchorPoint(Vec2(0.5,0.5));
    level2_txt->setString(l2);
    level2_txt->setSystemFontSize(20);
    level2_txt->setPosition(Vec2(0,0));
    level2->addChild(level2_txt);
    
    level3 = Node::create();
    level3->setPosition(level3_bg->getPosition());
    addChild(level3);
    
    Sprite* level3_ = Sprite::create("img_upgrade_icon_unlock.png");
    level3_->setPosition(0,0);
    level3->addChild(level3_);
    
    Label* level3_txt = Label::create();
    level3_txt->setTextColor(Color4B::BLACK);
    level3_txt->setAnchorPoint(Vec2(0.5,0.5));
    level3_txt->setString(l3);
    level3_txt->setSystemFontSize(20);
    level3_txt->setPosition(Vec2(0,0));
    level3->addChild(level3_txt);
    
    level4 = Node::create();
    level4->setPosition(level4_bg->getPosition());
    addChild(level4);
    
    Sprite* level4_ = Sprite::create("img_upgrade_icon_unlock.png");
    level4_->setPosition(0,0);
    level4->addChild(level4_);
    
    Label* level4_txt = Label::create();
    level4_txt->setTextColor(Color4B::BLACK);
    level4_txt->setAnchorPoint(Vec2(0.5,0.5));
    level4_txt->setString(l4);
    level4_txt->setSystemFontSize(20);
    level4_txt->setPosition(Vec2(0,0));
    level4->addChild(level4_txt);
    
    const char* ll1 = "15%";
    const char* ll2 = "25%";
    const char* ll3 = "35%";
    const char* ll4 = "50%";
    
    curlevel = CommonData::getInstance()->getRoleLevel(iType);
    
    if (type == BeymacType) {
        
        
    }
    else if (type == LaserType)
    {
        ll1 = "50%";
        ll2 = "80%";
        ll3 = "110%";
        ll4 = "150%";
    }
    else if (type == TomagoType)
    {
        ll1 = "30%";
        ll2 = "60%";
        ll3 = "90%";
        ll4 = "120%";
    }
    
    string str = __String::createWithFormat(LSTRING(up_info),LSTRING("level1_txt"),ll1,"")->getCString();
    
    Label* info1 = Label::create();
    info1->setTextColor(Color4B::WHITE);
    info1->setAnchorPoint(Vec2(0,0.5));
    info1->setString(str);
    info1->setSystemFontSize(20);
    info1->setDimensions(230, 100);
    info1->setPosition(level1_bg->getPosition()+Vec2(40,0));
    addChild(info1);
    
    str = __String::createWithFormat(LSTRING(up_info),LSTRING("level2_txt"),ll2,LSTRING("level2_pay"))->getCString();
    Label* info2 = Label::create();
    info2->setTextColor(Color4B::WHITE);
    info2->setAnchorPoint(Vec2(0,0.5));
    info2->setString(str);
    info2->setSystemFontSize(20);
    info2->setDimensions(230, 100);
    info2->setPosition(level2_bg->getPosition()+Vec2(40,0));

    addChild(info2);
    
    str = __String::createWithFormat(LSTRING(up_info),LSTRING("level3_txt"),ll3,LSTRING("level3_pay"))->getCString();
    Label* info3 = Label::create();
    info3->setTextColor(Color4B::WHITE);
    info3->setAnchorPoint(Vec2(0,0.5));
    info3->setString(str);
    info3->setSystemFontSize(20);
    info3->setDimensions(230, 100);
    info3->setPosition(level3_bg->getPosition()+Vec2(40,0));

    addChild(info3);
    
    str = __String::createWithFormat(LSTRING(up_info),LSTRING("level4_txt"),ll4,LSTRING("level4_pay"))->getCString();
    Label* info4 = Label::create();
    info4->setTextColor(Color4B::WHITE);
    info4->setAnchorPoint(Vec2(0,0.5));
    info4->setString(str);
    info4->setSystemFontSize(20);
    info4->setDimensions(230, 100);
    info4->setPosition(level4_bg->getPosition()+Vec2(40,0));
    addChild(info4);
    
    refreshBtn();
    refreshLevel();
}
void HeroUpgradeCell::refreshLevel()
{
    curlevel = CommonData::getInstance()->getRoleLevel(iType);
    
    if (curlevel == 0) {
        level1->setVisible(false);
        level2->setVisible(false);
        level3->setVisible(false);
        level4->setVisible(false);
        
    }
    else if (curlevel == 1) {
        level1->setVisible(true);
        level2->setVisible(false);
        level3->setVisible(false);
        level4->setVisible(false);

    }
    else if (curlevel == 2)
    {
        level1->setVisible(true);
        level2->setVisible(true);
        level3->setVisible(false);
        level4->setVisible(false);

    }
    else if (curlevel == 3)
    {
        level1->setVisible(true);
        level2->setVisible(true);
        level3->setVisible(true);
        level4->setVisible(false);

    }
    else if (curlevel == 4)
    {
        level1->setVisible(true);
        level2->setVisible(true);
        level3->setVisible(true);
        level4->setVisible(true);

    }
}

void HeroUpgradeCell::oneKeyUpRoleSuccess()
{
    
    int level=CommonData::getInstance()->getRoleLevel(iType);
    if (level < 4) {
        CommonData::getInstance()->setRoleLevel(iType, 4);
    }
    refreshLevel();
    refreshBtn();
}

void HeroUpgradeCell::unlockSuccess()
{
    int level=CommonData::getInstance()->getRoleLevel(iType);
    if (level == 0) {
        CommonData::getInstance()->setRoleLevel(iType, 1);
    }
    refreshLevel();
    refreshBtn();
}

