//
//  SkillUpgradeCell.cpp
//  beymac
//
//  Created by mumu on 15/5/29.
//
//

#include "SkillUpgradeCell.h"
#include "Macro.h"
#include "MMLocalizedString.h"
#include "Manager.h"
#include "CommonData.h"
#include "ShopScene.h"
#include "UpgradeScene.h"

#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")

// 1 金钟罩
// 2 大白铁拳
// 3 时间减缓
// 4 喷气背包
// 5 追踪导弹（废弃）
// 6 伽马射线
// 7 饱和轰炸
// 8 次元门

SkillUpgradeCell::SkillUpgradeCell(int type)
:delegate()
{
    skillType = type;
}

SkillUpgradeCell::~SkillUpgradeCell()
{

}

bool SkillUpgradeCell::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initBG();
    
    return true;
}

void SkillUpgradeCell::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void SkillUpgradeCell::onExit()
{
    Node::onExit();
}

SkillUpgradeCell* SkillUpgradeCell::create(int type)
{
    SkillUpgradeCell* cell = new SkillUpgradeCell(type);
    if (cell && cell->init()) {
        cell->autorelease();
        
    }
    else
    {
        delete cell;
        cell = NULL;
    }
    
    return cell;
}

void SkillUpgradeCell::initBG()
{
    // 背景
    Sprite* bg = Sprite::create("img_upgrade_prop_bg_small.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    // 能力图标
    string iconstr = __String::createWithFormat("img_upgrade_pic%d.png",skillType)->getCString();
    skillIcon = Sprite::create(iconstr);
    skillIcon->setPosition(-210,55);
    addChild(skillIcon);
    
    // 能力名称
    Sprite* namebg = Sprite::create("img_upgrade_prop_bg_title.png");
    namebg->setPosition(skillIcon->getPosition()+Vec2(115,0));
    addChild(namebg);
    
    const char* namestr = __String::createWithFormat("SkilkName%d",skillType)->getCString();
    skillName = Label::create();
    skillName->setTextColor(Color4B::WHITE);
    skillName->setAnchorPoint(Vec2(0.5,0.5));
    skillName->setString(LSTRING(namestr));
    skillName->setSystemFontSize(28);
    if (skillType == 1 || skillType == 8) {
        skillName->setDimensions(90, 100);
    }
    else
    {
        skillName->setDimensions(80, 100);
    }
    skillName->setPosition(namebg->getPosition()+Vec2(-3,0));
    skillName->setHorizontalAlignment(TextHAlignment::CENTER);
    skillName->setVerticalAlignment(TextVAlignment::CENTER);
    addChild(skillName);
    // 能力介绍
    const char* infostr = __String::createWithFormat("SkilkInfo%d",skillType)->getCString();
    skillInfo = Label::create();
    skillInfo->setTextColor(Color4B::WHITE);
    skillInfo->setAnchorPoint(Vec2(0,0.5));
    skillInfo->setString(LSTRING(infostr));

    if (skillType == 8) {
        skillInfo->setSystemFontSize(19);
    }
    else
    {
        skillInfo->setSystemFontSize(21);
    }
    


    skillInfo->setDimensions(300, 130);
    skillInfo->setPosition(namebg->getPosition()+Vec2(70,0));
    addChild(skillInfo);

    
    // 等级按钮背景
    Sprite* level3_bg = Sprite::create("img_btn_upgrade_unuseful.png");
    level3_bg->setPosition(Vec2(-9,-63));
    addChild(level3_bg);
    
    Sprite* level2_bg = Sprite::create("img_btn_upgrade_unuseful.png");
    level2_bg->setPosition(level3_bg->getPosition() + Vec2(-105, 0));
    addChild(level2_bg);
    
    Sprite* level1_bg = Sprite::create("img_btn_upgrade_unuseful.png");
    level1_bg->setPosition(level2_bg->getPosition() + Vec2(-105, 0));
    addChild(level1_bg);

    Sprite* level4_bg = Sprite::create("img_btn_upgrade_unuseful.png");
    level4_bg->setPosition(level3_bg->getPosition() + Vec2(105, 0));
    addChild(level4_bg);
    
    allUpBtn = Button::create("img_btn_upgrade_one.png");
    allUpBtn->setPosition(level4_bg->getPosition() + Vec2(115, 0));
    allUpBtn->setTitleText(LSTRING("AllUpgrade"));
    allUpBtn->setTitleFontSize(27);
    allUpBtn->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
//            int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
//            if (l < 4) {
//                CommonData::getInstance()->setRoleSkillLevel(skillType, 4);
//            }
//            refreshBtn();
            if (delegate) {
                delegate->SkillUpgradeCellDelegateOneKeyUp(skillType);
            }
        }
    });
    addChild(allUpBtn);
    
    Label* txt1 = Label::create();
    txt1->setTextColor(Color4B::WHITE);
    txt1->setAnchorPoint(Vec2(0.5,0.5));
    txt1->setString("1级");
    txt1->setSystemFontSize(30);
    txt1->setPosition(level1_bg->getPosition());
    addChild(txt1);
    
    Label* txt2 = Label::create();
    txt2->setTextColor(Color4B::WHITE);
    txt2->setAnchorPoint(Vec2(0.5,0.5));
    txt2->setString("2级");
    txt2->setSystemFontSize(30);
    txt2->setPosition(level2_bg->getPosition());
    addChild(txt2);
    
    Label* txt3 = Label::create();
    txt3->setTextColor(Color4B::WHITE);
    txt3->setAnchorPoint(Vec2(0.5,0.5));
    txt3->setString("3级");
    txt3->setSystemFontSize(30);
    txt3->setPosition(level3_bg->getPosition());
    addChild(txt3);
    
    Label* txt4 = Label::create();
    txt4->setTextColor(Color4B::WHITE);
    txt4->setAnchorPoint(Vec2(0.5,0.5));
    txt4->setString("4级");
    txt4->setSystemFontSize(30);
    txt4->setPosition(level4_bg->getPosition());
    addChild(txt4);
    
    Label* txt2_pay = Label::create();
    txt2_pay->setTextColor(Color4B::WHITE);
    txt2_pay->setAnchorPoint(Vec2(0.5,0.5));
    txt2_pay->setString(LSTRING("SkillLevel2_pay"));
    txt2_pay->setSystemFontSize(17);
    txt2_pay->setPosition(level2_bg->getPosition()-Vec2(0, 47));
    addChild(txt2_pay);
    
    Label* txt3_pay = Label::create();
    txt3_pay->setTextColor(Color4B::WHITE);
    txt3_pay->setAnchorPoint(Vec2(0.5,0.5));
    txt3_pay->setString(LSTRING("SkillLevel3_pay"));
    txt3_pay->setSystemFontSize(17);
    txt3_pay->setPosition(level3_bg->getPosition()-Vec2(0, 47));
    addChild(txt3_pay);
    
    Label* txt4_pay = Label::create();
    txt4_pay->setTextColor(Color4B::WHITE);
    txt4_pay->setAnchorPoint(Vec2(0.5,0.5));
    txt4_pay->setString(LSTRING("SkillLevel4_pay"));
    txt4_pay->setSystemFontSize(17);
    txt4_pay->setPosition(level4_bg->getPosition()-Vec2(0, 47));
    addChild(txt4_pay);
    
    // 升级按钮
    level1 = Button::create("img_btn_upgrade_waiting.png","img_btn_upgrade_lock.png");
    level1->setPosition(level1_bg->getPosition());
    addChild(level1);
    level1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
//            int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
//            if (l == 0) {
//                CommonData::getInstance()->setRoleSkillLevel(skillType, 1);
//            }
//            
//            refreshBtn();
            if (delegate) {
                delegate->SkillUpgradeCellDelegateUnlockSkill(skillType);
            }
        }
    });
    
    
    
    level2 = Button::create("img_btn_upgrade_waiting.png","img_btn_upgrade_lock.png");
    level2->setPosition(level2_bg->getPosition());
    addChild(level2);
    level2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
            if (l == 1) {
                int c = 20;
                
                //                c = 0;
                
                if (CommonData::getInstance()->getCrystal() >= c) {
                    CommonData::getInstance()->addCrystal(-c);
                    CommonData::getInstance()->setRoleSkillLevel(skillType, 2);
                    if (Director::getInstance()->getRunningScene()->getChildByTag(100)) {
                        UpgradeScene* layer = (UpgradeScene*)Director::getInstance()->getRunningScene()->getChildByTag(100);
                        layer->refreshCrystal();
                    }
                }
                else
                {
                    Director::getInstance()->pushScene(ShopScene::create());
                }
                
                
                refreshBtn();
                
            }
            
            
        }
    });
    
    level3 = Button::create("img_btn_upgrade_waiting.png","img_btn_upgrade_lock.png");
    level3->setPosition(level3_bg->getPosition());
    addChild(level3);
    level3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
            if (l == 2) {
                int c = 30;
                
                //                c = 0;
                
                if (CommonData::getInstance()->getCrystal() >= c) {
                    CommonData::getInstance()->addCrystal(-c);
                    CommonData::getInstance()->setRoleSkillLevel(skillType, 3);
                    if (Director::getInstance()->getRunningScene()->getChildByTag(100)) {
                        UpgradeScene* layer = (UpgradeScene*)Director::getInstance()->getRunningScene()->getChildByTag(100);
                        layer->refreshCrystal();
                    }
                }
                else
                {
                    Director::getInstance()->pushScene(ShopScene::create());
                }
                
                
                refreshBtn();
            }
        }
    });
    
    level4 = Button::create("img_btn_upgrade_waiting.png","img_btn_upgrade_lock.png");
    level4->setPosition(level4_bg->getPosition());
    addChild(level4);
    level4->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType t){
        if(t==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
            if (l == 3) {
                int c = 40;
                
                //                c = 0;
                
                if (CommonData::getInstance()->getCrystal() >= c) {
                    CommonData::getInstance()->addCrystal(-c);
                    CommonData::getInstance()->setRoleSkillLevel(skillType, 4);
                    if (Director::getInstance()->getRunningScene()->getChildByTag(100)) {
                        UpgradeScene* layer = (UpgradeScene*)Director::getInstance()->getRunningScene()->getChildByTag(100);
                        layer->refreshCrystal();
                    }
                }
                else
                {
                    Director::getInstance()->pushScene(ShopScene::create());
                }
                
                
                refreshBtn();
            }
        }
    });
 
    refreshBtn();
    
    Sprite* suo1 = Sprite::create("img_icon_prop_lock.png");
    suo1->setPosition(Vec2(level1->getContentSize().width/2-25, level1->getContentSize().height/2));
    level1->addChild(suo1);
    Label* txtsuo1 = Label::create();
    txtsuo1->setTextColor(Color4B::WHITE);
    txtsuo1->setAnchorPoint(Vec2(0.5,0.5));
    txtsuo1->setString("1级");
    txtsuo1->setSystemFontSize(28);
    txtsuo1->setPosition(suo1->getPosition()+ Vec2(40, 0));
    level1->addChild(txtsuo1);
    
    Sprite* suo2 = Sprite::create("img_icon_prop_lock.png");
    suo2->setPosition(Vec2(level2->getContentSize().width/2-25, level2->getContentSize().height/2));
    level2->addChild(suo2);
    Label* txtsuo2 = Label::create();
    txtsuo2->setTextColor(Color4B::WHITE);
    txtsuo2->setAnchorPoint(Vec2(0.5,0.5));
    txtsuo2->setString("2级");
    txtsuo2->setSystemFontSize(28);
    txtsuo2->setPosition(suo2->getPosition()+Vec2(40, 0));
    level2->addChild(txtsuo2);
    
    Sprite* suo3 = Sprite::create("img_icon_prop_lock.png");
    suo3->setPosition(Vec2(level3->getContentSize().width/2-25, level3->getContentSize().height/2));
    level3->addChild(suo3);
    Label* txtsuo3 = Label::create();
    txtsuo3->setTextColor(Color4B::WHITE);
    txtsuo3->setAnchorPoint(Vec2(0.5,0.5));
    txtsuo3->setString("3级");
    txtsuo3->setSystemFontSize(28);
    txtsuo3->setPosition(suo3->getPosition()+Vec2(40, 0));
    level3->addChild(txtsuo3);
    
    Sprite* suo4 = Sprite::create("img_icon_prop_lock.png");
    suo4->setPosition(Vec2(level4->getContentSize().width/2-25, level4->getContentSize().height/2));
    level4->addChild(suo4);
    Label* txtsuo4 = Label::create();
    txtsuo4->setTextColor(Color4B::WHITE);
    txtsuo4->setAnchorPoint(Vec2(0.5,0.5));
    txtsuo4->setString("4级");
    txtsuo4->setSystemFontSize(28);
    txtsuo4->setPosition(suo4->getPosition()+Vec2(40, 0));
    level4->addChild(txtsuo4);
    
}

void SkillUpgradeCell::refreshBtn()
{
    int level = CommonData::getInstance()->getRoleSkillLevel(skillType);
    if (level <= 0) {
        level1->setVisible(true);
        level2->setVisible(true);
        level3->setVisible(true);
        level4->setVisible(true);
        level1->setEnabled(true);
        level1->setHighlighted(false);
        level2->setEnabled(false);
        level2->setHighlighted(true);
        level3->setEnabled(false);
        level3->setHighlighted(true);
        level4->setEnabled(false);
        level4->setHighlighted(true);
        allUpBtn->setEnabled(true);
        allUpBtn->setColor(Color3B::WHITE);
    }
    else if (level == 1)
    {
        level1->setVisible(false);
        level2->setEnabled(true);
        level2->setHighlighted(false);
        level3->setEnabled(false);
        level3->setHighlighted(true);
        level4->setEnabled(false);
        level4->setHighlighted(true);
        allUpBtn->setEnabled(true);
        allUpBtn->setColor(Color3B::WHITE);
    }
    else if (level == 2)
    {
        level1->setVisible(false);
        level2->setVisible(false);
        level3->setEnabled(true);
        level3->setHighlighted(false);
        level4->setEnabled(false);
        level4->setHighlighted(true);
        allUpBtn->setEnabled(true);
        allUpBtn->setColor(Color3B::WHITE);
    }
    else if (level == 3)
    {
        level1->setVisible(false);
        level2->setVisible(false);
        level3->setVisible(false);
        level4->setEnabled(true);
        level4->setHighlighted(false);
        allUpBtn->setEnabled(true);
        allUpBtn->setColor(Color3B::WHITE);
    }
    else if (level > 3)
    {
        level1->setVisible(false);
        level2->setVisible(false);
        level3->setVisible(false);
        level4->setVisible(false);
        allUpBtn->setEnabled(false);
        allUpBtn->setColor(Color3B::GRAY);
    }
    
}

void SkillUpgradeCell::oneKeyUpSkillSuccess()
{
    int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
    if (l < 4) {
        CommonData::getInstance()->setRoleSkillLevel(skillType, 4);
    }
    refreshBtn();
}
void SkillUpgradeCell::unlockNewSkillSuccess()
{
    int l = CommonData::getInstance()->getRoleSkillLevel(skillType);
    if (l < 1) {
        CommonData::getInstance()->setRoleSkillLevel(skillType, 1);
    }
    refreshBtn();
}