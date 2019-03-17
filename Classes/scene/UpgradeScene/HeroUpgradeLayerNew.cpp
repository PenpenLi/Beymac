//
//  HeroUpgradeLayerNew.cpp
//  beymac
//
//  Created by mumu on 15/6/9.
//
//

#include "HeroUpgradeLayerNew.h"

#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")

#define CELL_HEIGHT 585

HeroUpgradeLayerNew::HeroUpgradeLayerNew()
{

}

HeroUpgradeLayerNew::~HeroUpgradeLayerNew()
{

}

bool HeroUpgradeLayerNew::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    popupType = popupHero_null;
    
    bgAllHeight = 0;
    
    Sprite* bg = Sprite::create("img_upgrade_prop_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    addChild(bg);
    
    cellNode = Node::create();
    cellNode->setPosition(SCREEN_CENTER+Vec2(0,130));
    addChild(cellNode);
    
//    auto btnReset=Button::create();
//    btnReset->cocos2d::Node::setPosition(550, 200);
//    btnReset->setTitleText("重置");
//    btnReset->setTitleFontSize(50);
//    btnReset->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
//        if(type==Widget::TouchEventType::ENDED){
//            for(int i=1;i<4;i++){
//                CommonData::getInstance()->setRoleLevel(i, 0);
//                if (i == 1) {
//                    CommonData::getInstance()->setRoleLevel(i, 1);
//                }
//            }
//            vector<HeroUpgradeCell*>::iterator iter;
//            for (iter = cellList.begin(); iter != cellList.end(); iter++) {
//                HeroUpgradeCell* cell = (*iter);
//                cell->refreshBtn();
//                cell->refreshLevel();
//            }
//        }
//    });
//    addChild(btnReset);
    
    initCells();
    initPopup();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HeroUpgradeLayerNew::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HeroUpgradeLayerNew::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HeroUpgradeLayerNew::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HeroUpgradeLayerNew::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void HeroUpgradeLayerNew::onExit()
{
    Node::onExit();
}

bool HeroUpgradeLayerNew::onTouchBegan(Touch* touch, Event *pEvent)
{
    touchCurPoint = touch->getLocation();
    
    return true;
}
void HeroUpgradeLayerNew::onTouchMoved(Touch* touch, Event *pEvent)
{
    if (!this->isVisible()) {
        return;
    }
    
    Point touchPoint = touch->getLocation();
    Point posPoint = Point(cellNode->getPositionX(), cellNode->getPositionY() + touchPoint.y - touchCurPoint.y);
    if (posPoint.y <= bgAllHeight-170 && posPoint.y >= SCREEN_WIDTH/2+380 ) {
        cellNode->setPosition(posPoint);
        //CCLog("x = %f, y = %f", getPositionX(),getPositionY());
    }
    
    touchCurPoint = touchPoint;
}
void HeroUpgradeLayerNew::onTouchEnded(Touch* touch, Event *pEvent)
{
    
}

void HeroUpgradeLayerNew::HeroUpgradeCellDelegateUnlockHero(RoleType type)
{
    if (type == BeymacType) {
        
    }
    else if (type == LaserType)
    {
        popupUnlockType = LaserType;
        popupUKImage->setTexture("img_upgrade_brother.png");
    }
    else if (type == TomagoType)
    {
        popupUnlockType = TomagoType;
        popupUKImage->setTexture("img_upgrade_sister.png");
    }
    popupUnlockRole->show();
    
}
void HeroUpgradeLayerNew::HeroUpgradeCellDelegateOneKeyUp(RoleType type)
{
    if (type == BeymacType) {
        popupOneKeyType = BeymacType;
        popupOKImage->setTexture("img_upgrade_baymax.png");
    }
    else if (type == LaserType)
    {
        popupOneKeyType = LaserType;
        popupOKImage->setTexture("img_upgrade_brother.png");
    }
    else if (type == TomagoType)
    {
        popupOneKeyType = TomagoType;
        popupOKImage->setTexture("img_upgrade_sister.png");
        
    }
    popupOneKeyUpRole->show();
}

void HeroUpgradeLayerNew::initCells()
{
    HeroUpgradeCell* cell1 = HeroUpgradeCell::create(BeymacType);
    cell1->setPosition(Vec2(0, 0));
    cellNode->addChild(cell1);
    cell1->setDelegate(this);
    bgAllHeight += CELL_HEIGHT;
    cellList.push_back(cell1);
    
    HeroUpgradeCell* cell2 = HeroUpgradeCell::create(TomagoType);
    cell2->setPosition(Vec2(0, -CELL_HEIGHT));
    cellNode->addChild(cell2);
    cell2->setDelegate(this);
    bgAllHeight += CELL_HEIGHT;
    cellList.push_back(cell2);
    
    HeroUpgradeCell* cell3 = HeroUpgradeCell::create(LaserType);
    cell3->setPosition(Vec2(0, -CELL_HEIGHT*2));
    cellNode->addChild(cell3);
    cell3->setDelegate(this);
    bgAllHeight += CELL_HEIGHT;
    cellList.push_back(cell3);
}
void HeroUpgradeLayerNew::initPopup()
{
    popupOneKeyUpRole = PopupLayer::create("img_window_bg.png");
    popupOneKeyUpRole->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg = Sprite::create("img_window_title_bg.png");
    titlebg->setPosition(Vec2(0, 190));
    popupOneKeyUpRole->addChild(titlebg);
    
    Sprite* title = Sprite::create("img_window_title5.png");
    title->setPosition(Vec2(0, 190));
    popupOneKeyUpRole->addChild(title);
    
    Sprite* content = Sprite::create("img_window_paper.png");
    content->setPosition(Vec2::ZERO);
    popupOneKeyUpRole->addChild(content);
    
    Sprite* content2 = Sprite::create("img_upgrade_round.png");
    content2->setPosition(0,30);
    popupOneKeyUpRole->addChild(content2);
    
    Label* context = Label::createWithSystemFont(LSTRING("OneKeyUpRole"), "arial", 33);
    context->setDimensions(360, 140);
    context->setPosition(Vec2(0,-90));
    context->setColor(Color3B(203,  73,  24));
    context->setHorizontalAlignment(TextHAlignment::CENTER);
    context->setVerticalAlignment(TextVAlignment::CENTER);
    popupOneKeyUpRole->addChild(context);
    
    auto btnOK=cocos2d::ui::Button::create("img_window_green.png");
    btnOK->setPosition(Point(0,-240));
    btnOK->setTitleText(LSTRING("Buy"));
    btnOK->setTitleFontName("Arial");
    btnOK->setTitleFontSize(40);
    btnOK->setTitleColor(Color3B(12, 63, 10));
    btnOK->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            oneKeyUpRoleSuccess();
            popupType = popupHero_onekey;
            Payment::pay(ROLEFULLLEVEL, this);
            
            this->retain();
            
            log("购买一键升级");
        }
    });
    popupOneKeyUpRole->addChild(btnOK);
    addChild(popupOneKeyUpRole, 9999);
    
    auto btnClose=Button::create("img_window_btn_close.png");
    btnClose->setPosition(Point(260,160));
    btnClose->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            popupOneKeyUpRole->hide();
        }
    });
    popupOneKeyUpRole->addChild(btnClose);
    
    popupOKImage = Sprite::create("img_upgrade_baymax.png");
    popupOKImage->setScale(0.45);
    popupOKImage->setPosition(0, 40);
    popupOneKeyUpRole->addChild(popupOKImage);
    
    popupUnlockRole = PopupLayer::create("img_window_bg.png");
    popupUnlockRole->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg2 = Sprite::create("img_window_title_bg.png");
    titlebg2->setPosition(Vec2(0, 190));
    popupUnlockRole->addChild(titlebg2);
    
    Sprite* title2 = Sprite::create("img_window_title7.png");
    title2->setPosition(Vec2(0, 190));
    popupUnlockRole->addChild(title2);
    
    Sprite* content3 = Sprite::create("img_window_paper.png");
    content3->setPosition(Vec2::ZERO);
    popupUnlockRole->addChild(content3);
    
    Sprite* content3_ = Sprite::create("img_window_paper6.png");
    content3_->setPosition(Vec2::ZERO);
    popupUnlockRole->addChild(content3_);
    
    Label* context2 = Label::createWithSystemFont(LSTRING("UnlockNewRole"), "arial", 30);
    context2->setDimensions(260, 80);
    context2->setPosition(Vec2(115,70));
    context2->setColor(Color3B(203,  73,  24));
    context2->setHorizontalAlignment(TextHAlignment::CENTER);
    context2->setVerticalAlignment(TextVAlignment::CENTER);
    popupUnlockRole->addChild(context2);
    
    auto btnOK2=cocos2d::ui::Button::create("img_window_green.png");
    btnOK2->setPosition(Point(0,-240));
    btnOK2->setTitleText(LSTRING("UNLOCK"));
    btnOK2->setTitleFontName("Arial");
    btnOK2->setTitleFontSize(40);
    btnOK2->setTitleColor(Color3B(12, 63, 10));
    btnOK2->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            unlockNewRoleSuccess();
            popupType = popupHero_unlock;
            Payment::pay(UNLOCKROLE, this);
            
            this->retain();
            
            log("解锁新人物");
        }
    });
    popupUnlockRole->addChild(btnOK2);
    addChild(popupUnlockRole, 9999);
    
    auto btnClose2=Button::create("img_window_btn_close.png");
    btnClose2->setPosition(Point(260,160));
    btnClose2->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            popupUnlockRole->hide();
        }
    });
    popupUnlockRole->addChild(btnClose2);
    
    popupUnlockType = TomagoType;
    
    popupUKImage = Sprite::create("img_upgrade_brother.png");
    popupUKImage->setScale(0.4);
    popupUKImage->setPosition(-100, 0);
    popupUnlockRole->addChild(popupUKImage);
}

void HeroUpgradeLayerNew::oneKeyUpRoleSuccess()
{
    vector<HeroUpgradeCell*>::iterator iter;
    for (iter = cellList.begin(); iter != cellList.end(); iter++) {
        HeroUpgradeCell* cell = (*iter);
        if (cell->getType() == popupOneKeyType) {
            cell->oneKeyUpRoleSuccess();
            popupOneKeyUpRole->hide();
        }
//        cell->refreshBtn();
//        cell->refreshLevel();
    }
}
void HeroUpgradeLayerNew::unlockNewRoleSuccess()
{
    vector<HeroUpgradeCell*>::iterator iter;
    for (iter = cellList.begin(); iter != cellList.end(); iter++) {
        HeroUpgradeCell* cell = (*iter);
        if (cell->getType() == popupUnlockType) {
            cell->unlockSuccess();
            popupUnlockRole->hide();
        }
//        cell->refreshBtn();
//        cell->refreshLevel();
    }
}

void HeroUpgradeLayerNew::payResult(bool result)
{
    if (result) {
        log("支付成功");
        if ( popupType == popupHero_unlock) {
            log("解锁支付成功");
            unlockNewRoleSuccess();
        }
        else if (popupType == popupHero_onekey)
        {
            log("一键满级支付成功");
            oneKeyUpRoleSuccess();
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
    
    popupType = popupHero_null;
    
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