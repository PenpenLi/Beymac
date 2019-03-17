//
//  SkillUpgradeLayer.cpp
//  beymac
//
//  Created by mumu on 15/5/29.
//
//

#include "SkillUpgradeLayer.h"
#include "CommonHeader.h"
#include "SkillUpgradeCell.h"

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

#define SKILL_COUNT 7
#define CELL_HEIGHT 285

USING_NS_CC;

using namespace ui;

Scene *SkillUpgradeLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SkillUpgradeLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool SkillUpgradeLayer::init()
{
    
    if (!Node::init())
    {
        return false;
    }
    bgAllHeight = 0;
    
    popupType = popup_null;
    
    Sprite* bg = Sprite::create("img_upgrade_prop_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    addChild(bg);
    
    cellNode = Node::create();
    cellNode->setPosition(SCREEN_CENTER+Vec2(0,300));
    addChild(cellNode);
    
//    auto btnReset=Button::create();
//    btnReset->cocos2d::Node::setPosition(550, 200);
//    btnReset->setTitleText("重置");
//    btnReset->setTitleFontSize(50);
//    btnReset->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
//        if(type==Widget::TouchEventType::ENDED){
//            for(int i=1;i<9;i++){
//                CommonData::getInstance()->setRoleSkillLevel(i, 0);
//            }
//            vector<SkillUpgradeCell*>::iterator iter;
//            for (iter = cellList.begin(); iter != cellList.end(); iter++) {
//                SkillUpgradeCell* cell = (*iter);
//                cell->refreshBtn();
//            }
//        }
//    });
//    addChild(btnReset);
    
    initCells();
    initPopup();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SkillUpgradeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SkillUpgradeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SkillUpgradeLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool SkillUpgradeLayer::onTouchBegan(Touch* touch, Event *pEvent)
{
    touchCurPoint = touch->getLocation();
    
    return true;
}
void SkillUpgradeLayer::onTouchMoved(Touch* touch, Event *pEvent)
{
    
    if (!this->isVisible()) {
        return;
    }
    
    Point touchPoint = touch->getLocation();
    Point posPoint = Point(cellNode->getPositionX(), cellNode->getPositionY() + touchPoint.y - touchCurPoint.y);
    if (posPoint.y <= bgAllHeight && posPoint.y >= SCREEN_WIDTH/2+530 ) {
        cellNode->setPosition(posPoint);
        //CCLog("x = %f, y = %f", getPositionX(),getPositionY());
    }
    
    touchCurPoint = touchPoint;
}
void SkillUpgradeLayer::onTouchEnded(Touch* touch, Event *pEvent)
{
    
}

void SkillUpgradeLayer::initCells()
{
    for (int i = 1; i <= SKILL_COUNT; i++) {
        int t = i;
        if (i >= 5) {
            t = i+1;
        }
        SkillUpgradeCell* cell = SkillUpgradeCell::create(t);
        cell->setPosition(Vec2(0, -CELL_HEIGHT*(i-1)));
        cellNode->addChild(cell);
        cell->setDelegate(this);
        bgAllHeight += CELL_HEIGHT;
        
        cellList.push_back(cell);
    }
}

void SkillUpgradeLayer::SkillUpgradeCellDelegateUnlockSkill(int skillType)
{
    popupUnlockSkillNum= skillType;
    const char* str = __String::createWithFormat("img_upgrade_pic%d.png",skillType)->getCString();
    
    popupUKImage->setTexture(str);
    
    popupUnlockSkill->show();
}
void SkillUpgradeLayer::SkillUpgradeCellDelegateOneKeyUp(int skillType)
{
    popupOneKeyNum= skillType;
    const char* str = __String::createWithFormat("img_upgrade_pic%d.png",skillType)->getCString();
    
    popupOKImage->setTexture(str);
    
    popupOneKey->show();
}

void SkillUpgradeLayer::initPopup()
{
    // 解锁新技能
    popupUnlockSkill = PopupLayer::create("img_window_bg.png");
    popupUnlockSkill->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg = Sprite::create("img_window_title_bg.png");
    titlebg->setPosition(Vec2(0, 190));
    popupUnlockSkill->addChild(titlebg);
    
    Sprite* title = Sprite::create("img_window_title6.png");
    title->setPosition(Vec2(0, 190));
    popupUnlockSkill->addChild(title);
    
    Sprite* content = Sprite::create("img_window_paper.png");
    content->setPosition(Vec2::ZERO);
    popupUnlockSkill->addChild(content);
    
    Sprite* content2 = Sprite::create("img_window_paper6.png");
    content2->setPosition(Vec2::ZERO);
    popupUnlockSkill->addChild(content2);
    
    Label* context = Label::createWithSystemFont(LSTRING("UnlockNewSkill"), "arial", 30);
    context->setDimensions(260, 80);
    context->setPosition(Vec2(115,70));
    context->setColor(Color3B(203,  73,  24));
    context->setHorizontalAlignment(TextHAlignment::CENTER);
    context->setVerticalAlignment(TextVAlignment::CENTER);
    popupUnlockSkill->addChild(context);
    
    auto btnOK=cocos2d::ui::Button::create("img_window_green.png");
    btnOK->setPosition(Point(0,-240));
    btnOK->setTitleText(LSTRING("UNLOCK"));
    btnOK->setTitleFontName("Arial");
    btnOK->setTitleFontSize(40);
    btnOK->setTitleColor(Color3B(12, 63, 10));
    btnOK->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            unlockNewSkillSuccess();
            popupType = popup_unlock;
            Payment::pay(UNLOCKSKILL, this);
            
            this->retain();
            
            log("解锁新技能");
        }
    });
    popupUnlockSkill->addChild(btnOK);
    addChild(popupUnlockSkill, 9999);
    
    auto btnClose=Button::create("img_window_btn_close.png");
    btnClose->setPosition(Point(260,160));
    btnClose->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            popupUnlockSkill->hide();
        }
    });
    popupUnlockSkill->addChild(btnClose);
    
    popupUKImage = Sprite::create("img_upgrade_pic2.png");
    popupUKImage->setPosition(-100, 0);
    popupUnlockSkill->addChild(popupUKImage);
    
    // 一键升级
    popupOneKey = PopupLayer::create("img_window_bg.png");
    popupOneKey->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg2 = Sprite::create("img_window_title_bg.png");
    titlebg2->setPosition(Vec2(0, 190));
    popupOneKey->addChild(titlebg2);
    
    Sprite* title2 = Sprite::create("img_window_title5.png");
    title2->setPosition(Vec2(0, 190));
    popupOneKey->addChild(title2);
    
    Sprite* content3 = Sprite::create("img_window_paper.png");
    content3->setPosition(Vec2::ZERO);
    popupOneKey->addChild(content3);
    
    Sprite* content4 = Sprite::create("img_upgrade_round.png");
    content4->setPosition(0,30);
    popupOneKey->addChild(content4);
    
    Label* context2 = Label::createWithSystemFont(LSTRING("OneKeyUpSkill"), "arial", 33);
    context2->setDimensions(360, 140);
    context2->setPosition(Vec2(0,-90));
    context2->setColor(Color3B(203,  73,  24));
    context2->setHorizontalAlignment(TextHAlignment::CENTER);
    context2->setVerticalAlignment(TextVAlignment::CENTER);
    popupOneKey->addChild(context2);
    
    auto btnOK2=cocos2d::ui::Button::create("img_window_green.png");
    btnOK2->setPosition(Point(0,-240));
    btnOK2->setTitleText(LSTRING("Buy"));
    btnOK2->setTitleFontName("Arial");
    btnOK2->setTitleFontSize(40);
    btnOK2->setTitleColor(Color3B(12, 63, 10));
    btnOK2->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            oneKeyUpSkillSuccess();
            popupType = popup_onekey;
            Payment::pay(SKILLFULLEVEL, this);
            
            this->retain();
            
            log("购买一键升级");
        }
    });
    popupOneKey->addChild(btnOK2);
    addChild(popupOneKey, 9999);
    
    auto btnClose2=Button::create("img_window_btn_close.png");
    btnClose2->setPosition(Point(260,160));
    btnClose2->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            popupOneKey->hide();
        }
    });
    popupOneKey->addChild(btnClose2);
    
    popupOKImage = Sprite::create("img_upgrade_baymax.png");
    popupOKImage->setPosition(0, 40);
    popupOneKey->addChild(popupOKImage);
}

void SkillUpgradeLayer::oneKeyUpSkillSuccess()
{
    popupOneKey->hide();
    vector<SkillUpgradeCell*>::iterator iter;
    for (iter = cellList.begin(); iter != cellList.end(); iter++) {
        SkillUpgradeCell* cell = (*iter);
        if (cell->getSkillType() == popupOneKeyNum) {
            cell->oneKeyUpSkillSuccess();
        }
    }
}
void SkillUpgradeLayer::unlockNewSkillSuccess()
{
    popupUnlockSkill->hide();
    vector<SkillUpgradeCell*>::iterator iter;
    for (iter = cellList.begin(); iter != cellList.end(); iter++) {
        SkillUpgradeCell* cell = (*iter);
        if (cell->getSkillType() == popupUnlockSkillNum) {
            cell->unlockNewSkillSuccess();
        }
    }
}

void SkillUpgradeLayer::payResult(bool result)
{
    if (result) {
        log("支付成功");
        if ( popupType == popup_unlock) {
            unlockNewSkillSuccess();
        }
        else if (popupType == popup_onekey)
        {
            oneKeyUpSkillSuccess();
        }
    }
    else
    {
        log("支付失败");
    }
    
    if (this->isRunning()) {
        log("运行中");
    }
    else
    {
        log("不在运行");
    }
    popupType = popup_null;
    
    //判断释放条件。
    if(this->isRunning()){
        if(this->getReferenceCount()>1){
            this->release();
        }
    }else{
        if(this->getReferenceCount()>0){
            this->release();
        }
    }
    
}