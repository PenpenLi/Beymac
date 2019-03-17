//
//  TutorialScene.cpp
//  beymac
//
//  Created by lingzerg on 15/4/21.
//
//

#include "TutorialScene.h"
#include "CheckpointScene.h"
#include "Box.h"
#include "MMLocalizedString.h"
#include "Monster.h"
#include "ShopScene.h"


float deadLine = SCREEN_HEIGHT - 12 * GRID_SIZE;

TutorialScene::TutorialScene()
:textHintNode()
,arrow1()
,arrow2()
,shadowlayer()
{
    
}

TutorialScene::~TutorialScene()
{
    
}

Scene* TutorialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TutorialScene::create();
    scene->addChild(layer);
    return scene;
}

bool TutorialScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    if (CommonData::getInstance()->get(1) == 0) {
        isGamePause = true;
        //popupStartTeach->show();
        infoLayer = LevelInfoTextLayer::create(1,this);
        addChild(infoLayer,9999);
    }
    initData();
    
    return true;
}

#pragma mark - initData
void TutorialScene::initData()
{
    
    this->setBg();
    this->initBtn();
    this->initPopup();
    this->initHint();
    
    
    for (int i = 0; i<8; i++) {
        Box *b = Box::createMyBox(BoxType::normalbox);
        b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+GRID_RADIUS_SIZE);
        b->track = i+1;
        b->isDead = true;
        b->targetPositionY = deadLine+GRID_RADIUS_SIZE;
        b->setOpacity(0);
        
        
        addChild(b);
        boxlist.push_back(b);
        ActionInterval *in = FadeIn::create(0.5);
        b->runAction(in);
    }
    
    for (int i = 0; i<8; i++) {
        Box *b = Box::createMyBox(BoxType::normalbox);
        b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, deadLine-GRID_RADIUS_SIZE);
        b->track = i+1;
        b->isDead = true;
        b->targetPositionY = deadLine-GRID_RADIUS_SIZE;
        b->setOpacity(0);
        
        addChild(b);
        boxlist.push_back(b);
        ActionInterval *in = FadeIn::create(0.5);
        b->runAction(in);
    }

    
    Box *b = Box::createMyBox(BoxType::normalbox);
    b->setPosition(GRID_RADIUS_SIZE, deadLine+GRID_SIZE+GRID_RADIUS_SIZE);
    b->track = 1;
    b->isDead = true;
    b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
    b->setOpacity(0);
    addChild(b);
    boxlist.push_back(b);
    ActionInterval *in = FadeIn::create(0.5);
    b->runAction(in);
    
    Box *b2 = Box::createMyBox(BoxType::normalbox);
    b2->setPosition(GRID_RADIUS_SIZE, deadLine+2*GRID_SIZE+GRID_RADIUS_SIZE);
    b2->track = 1;
    b2->isDead = true;
    b2->targetPositionY = deadLine+2*GRID_SIZE+GRID_RADIUS_SIZE;
    b2->setOpacity(0);
    addChild(b2);
    boxlist.push_back(b2);
    ActionInterval *in2 = FadeIn::create(0.5);
    b2->runAction(in2);
    
    Box *b3 = Box::createMyBox(BoxType::normalbox);
    b3->setPosition(GRID_RADIUS_SIZE, deadLine+3*GRID_SIZE+GRID_RADIUS_SIZE);
    b3->track = 1;
    b3->isDead = true;
    b3->targetPositionY = deadLine+3*GRID_SIZE+GRID_RADIUS_SIZE;
    b3->setOpacity(0);
    addChild(b3);
    boxlist.push_back(b3);
    ActionInterval *in3 = FadeIn::create(0.5);
    b3->runAction(in3);
    
    player = BeyMac::create();
    player->setPosition(SCREEN_CENTER+Vec2(40,0));
    player->setPositionY(DEAD_LINE + player->getContentSize().height/2 );
    player->setTag(10000);
    player->setBlood(1);
    player->setDelegate(this);
    player->setPlayScene(this);
    addChild(player);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TutorialScene::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TutorialScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    showTextHint(9);
    
    
    
    schedule(schedule_selector(TutorialScene::onUpdate));
}

void TutorialScene::onTouchesBegan(const std::vector<Touch*>& touches,Event* event) {
    
    if (curStep == 9) {
        for ( auto &item: touches )
        {
            auto touch = item;
            auto location = touch->getLocation();
            
            if(location.x <= SCREEN_WIDTH/2 )
            {
                
                player->onTouchesBegan(touches, event);
            }
        }
    }
    else if (curStep == 10)
    {
        for ( auto &item: touches )
        {
            auto touch = item;
            auto location = touch->getLocation();
            
            if(location.x > SCREEN_WIDTH/2 )
            {
                player->onTouchesBegan(touches, event);
            }
        }
    }
    else if (curStep == 4) {
        isGamePause = false;
        arrow1->setPositionX(-200);
        player->onTouchesBegan(touches, event);
    }
    else if (curStep == 11)
    {
        isGamePause = false;
        arrow1->setPositionX(-200);
    }
    else
    {
        player->onTouchesBegan(touches, event);
    }
    
    
    
}


void TutorialScene::onTouchesEnded(const std::vector<Touch*>& touches,Event* event)
{
        player->onTouchesEnded(touches, event);
    
}

void TutorialScene::setBg() {
    auto bg = Sprite::create("img_scene1_bg.jpg");
    bg->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
    addChild(bg, -2);
    
    
    line = DottedLine::createNode();
    line->setLocalZOrder(100);
    line->setPosition(0,256+GRID_SIZE*3);
    addChild(line);
    
    auto bgbar2 = Sprite::create("img_play_blue.png");
    bgbar2->setPosition(Vec2(bgbar2->getContentSize().width/2, bgbar2->getContentSize().height/2));
    addChild(bgbar2,1);
    
    
    health = Health::createNode();
    health->setPosition(432,146);
    health->setLocalZOrder(101);
    addChild(health);
    
    auto *gold = Sprite::create("img_play_icon_power.png");
    gold->setPosition(260,146);
    gold->setLocalZOrder(99);
    addChild(gold);
    
    txtGold = Label::create();
    txtGold->setTextColor(Color4B::WHITE);
    txtGold->setString(NUM_TO_STR(CommonData::getInstance()->getEnergy()));
    txtGold->setSystemFontSize(30);
    txtGold->setPosition(314,146);
    txtGold->setLocalZOrder(101);
    txtGold->setString("0");
    addChild(txtGold);
    
    //金色能量图标
    auto goldPower = Sprite::create("img_play_icon_power_gold.png");
    goldPower->setPosition(140,146);
    addChild(goldPower,99);
    
    auto txtGoldPower = Label::create();
    txtGoldPower->setTextColor(Color4B::WHITE);
    txtGoldPower->setString("0");
    txtGoldPower->setSystemFontSize(30);
    txtGoldPower->setPosition(198,146);
    txtGoldPower->setLocalZOrder(101);
    addChild(txtGoldPower);
//    
    arrowLeft = Sprite::create("img_play_arrow_left.png");
    arrowLeft->setPosition(86,222);
    arrowLeft->setLocalZOrder(100);
    addChild(arrowLeft);
    
    arrowRight = Sprite::create("img_play_arrow_right.png");
    arrowRight->setPosition(554,222);
    arrowRight->setLocalZOrder(100);
    addChild(arrowRight);
    
    LabelAtlas* score = LabelAtlas::create(String::createWithFormat("%d",floor)->_string, "img_play_number_layer.png", 41, 58, '0');
    score->setPosition((SCREEN_WIDTH-score->getContentSize().width)/2,180);
    
    addChild(score,100);
    
}

void TutorialScene::onUpdate(float delta) {
    
    destroyBox();
    if(!isGamePause) {
        
        if (curStep == 12) {
            if (player->isInvincible) {
                moveBox();
                if (getChildByTag(999)) {
                    removeChildByTag(999);
                }
            }
        }
        else
        {
            moveBox();
        }
        
        
    }
    if (isWalk) {
        player->onUpdate(delta, &boxlist);
        health->setValue(player->getBlood()*33);
        
        if (curStep == 1) {
            if (player->getMyRow() == 4) {
                //                isWalk = false;
                player->setPositionX(player->getPositionX()-GRID_RADIUS_SIZE);
                showHint = true;
                showTextHint(2);
            }
        }
        else if (curStep == 2)
        {
            if (player->getMyRow() == 5) {
                player->setPositionX(player->getPositionX()+GRID_RADIUS_SIZE);
                isGamePause = false;
                isWalk = false;
                arrow1->setPositionX(-200);
                arrow2->setPositionX(-200);
                leftLight->setPosition(-200,-200);
                rightLight->setPosition(-200,-200);
            }
        }
        else if (curStep == 3)
        {
            if (player->getMyRow() == 7) {
                player->setPositionX(player->getPositionX()+GRID_RADIUS_SIZE);
                isGamePause = false;
                isWalk = false;
                arrow1->setPositionX(-200);
                arrow2->setPositionX(-200);
                leftLight->setPosition(-200,-200);
                rightLight->setPosition(-200,-200);
            }
        }
        else if (curStep == 5)
        {
            if (!player->getIsFrozen()) {
                showHint = true;
                showTextHint(11);
                
            }
        }
        else if (curStep == 6)
        {
            if (player->getMyRow() == 1) {
                showHint = true;
                showTextHint(7);
                arrow2->setPositionX(-200);
            }
        }
        else if (curStep == 9)
        {
            if (player->getMyRow() == 2) {
                showHint = true;
                isWalk = false;
                showTextHint(10);
//                arrow2->setPositionX(-200);
                arrow1->setPositionX(-200);
            }
        }
        else if (curStep == 10)
        {
            if (player->getMyRow() == 7) {
                showHint = true;
                isWalk = false;
                showTextHint(1);
            }
        }
    }
    
}

void TutorialScene::initBtn() {
    
    auto btnSwitch = cocos2d::ui::Button::create("img_btn_change.png");
    btnSwitch->setOpacity(153);
    btnSwitch->setLocalZOrder(100);
    btnSwitch->setPosition(Point(42,166+420));
    btnSwitch->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            player->changeRole();
            string str = "hehe";
            switch (player->getRoleType()) {
                case RoleType::BeymacType:
                    str = "大白";
                    break;
                case RoleType::LaserType:
                    str = "激光";
                    break;
                case RoleType::TomagoType:
                    str = "神行姐";
                    break;
                default:
                    break;
            }
            
//            Text *txt = Text::create();
//            txt->setString(str);
//            txt->setTextColor(Color4B::BLACK);
//            txt->setFontSize(50);
//            txt->setPosition(SCREEN_CENTER);
//            ActionInterval * ai = FadeOut::create(1);
//            auto action = Sequence::create(ai,CallFunc::create([&]{
//                this->removeChild(txt);
//            }),nullptr);
//            
//            this->addChild(txt,100);
//            txt->runAction(action);
        }
    });
    addChild(btnSwitch);
    
    //添加暂停按钮
    auto btnPause = cocos2d::ui::Button::create("img_btn_pause.png");
    btnPause->setLocalZOrder(100);
    btnPause->setOpacity(153);
    btnPause->setPosition(Point(600,166+420));
    
    addChild(btnPause);
    
    btnPause->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            Manager::getInstance()->pauseBackgroundMusic();
            popupPause->show();
//            isGamePause = true;
        }
    });
    
    // 金钟罩
    auto frist = cocos2d::ui::Button::create(MMImageNameLink("img_prop1"));
    frist->setPosition(Point(80,60));
    frist->setLocalZOrder(100);
    frist->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
            Manager::getInstance()->playSoundEffect("btnPress.mp3");

            if (curStep == 12) {
                txtGold->setString("0");
                isGamePause = false;
                player->setInvincible(true);
                arrow1->setPositionY(-200);
                arrow2->setPositionY(-200);
                
                if (getChildByTag(1000)) {
                    removeChildByTag(1000);
                }
                
            }
            
        }
    });
    
    addChild(frist);
    
    Sprite* bg2 = Sprite::create("img_prop_blank.png");
    bg2->setPosition(Point(240,60));
    addChild(bg2,100);
    
//    //添加大白铁拳道具按钮
//    auto second = cocos2d::ui::Button::create(MMImageNameLink("img_window_props_frame_add"));
//    second->setPosition(Point(240,60));
//    second->setLocalZOrder(100);
//    second->setColor(Color3B::GRAY);
//    second->setEnabled(false);
//    second->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
//        if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
//            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            if (CommonData::getInstance()->getEnergy() >= 10) {
////                if (propcd->getTimer2() == 0) {
////                    propcd->showTimer2();
////                    this->skillBtnClick(2);
////                }
//            }
//        }
//    });
    
//    addChild(second);
    
    Sprite* bg3 = Sprite::create("img_prop_blank.png");
    bg3->setPosition(Point(400,60));
    addChild(bg3,100);
//    //添加时间停止按钮
//    auto third = cocos2d::ui::Button::create(MMImageNameLink("img_window_props_frame_add"));
//    third->setLocalZOrder(100);
//    third->setPosition(Point(400,60));
//    third->setColor(Color3B::GRAY);
//    third->setEnabled(false);
//    third->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
//        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
//            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            if (CommonData::getInstance()->getEnergy() >= 10) {
////                if (propcd->getTimer3() == 0) {
////                    propcd->showTimer3();
////                    this->skillBtnClick(3);
////                }
//            }
//        }
//    });
//    addChild(third);
    
    Sprite* bg4 = Sprite::create("img_prop_blank.png");
    bg4->setPosition(Point(560,60));
    addChild(bg4,100);
//    
//    //添加喷气背包按钮
//    auto fourth = cocos2d::ui::Button::create(MMImageNameLink("img_window_props_frame_add"));
//    fourth->setPosition(Point(560,60));
//    fourth->setLocalZOrder(100);
//    fourth->setColor(Color3B::GRAY);
//    fourth->setEnabled(false);
//    fourth->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
//        if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
//            Manager::getInstance()->playSoundEffect("btnPress.mp3");
//            if (CommonData::getInstance()->getEnergy() >= 10) {
////                if (propcd->getTimer4() == 0) {
////                    propcd->showTimer4();
//////                    this->skillBtnClick(4);
////                }
//            }
//            
//        }
//    });
//    addChild(fourth);
//    addChild(propcd,100);
    
}

void TutorialScene::initPopup() {
    // 暂停菜单
    popupPause = PopupLayer::create("img_window_bg.png", 640, 330);
    popupPause->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    popupPause->setCloseButton("img_window_btn_close.png");
    popupPause->setDelegate(this);
    popupPause->setTitleImage("img_window_title1.png");
    
    auto pauseBg = Sprite::create("img_window_paper.png");
    
    auto btnContinue=cocos2d::ui::Button::create("img_btn_continue.png");
    btnContinue->setPosition(Point(-160,0));
    btnContinue->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            Manager::getInstance()->resumeBackgroundMusic();
            popupPause->hide();
//            isGamePause = false;
        }
    });
    
    
    auto btnMainpage=cocos2d::ui::Button::create("img_btn_level.png");
    btnMainpage->setPosition(Point(0,0));
    btnMainpage->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            popupPause->hide();
            //返回菜单
            Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
            Director::getInstance()->replaceScene(CheckpointScene::create());
        }
    });
    
    auto btnShop=cocos2d::ui::Button::create("img_btn_shop.png");
    btnShop->setPosition(Point(160,0));
    btnShop->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            Director::getInstance()->pushScene(ShopScene::create());
        }
    });
    
    popupPause->addChild(pauseBg);
    popupPause->addChild(btnShop);
    popupPause->addChild(btnContinue);
    popupPause->addChild(btnMainpage);
    
    addChild(popupPause, 9999);
    
    // 开始教程弹窗
    popupStartTeach = PopupLayer::create("img_window_bg.png");
    popupStartTeach->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    Sprite* titlebg = Sprite::create("img_window_title_bg.png");
    titlebg->setPosition(Vec2(0, 190));
    popupStartTeach->addChild(titlebg);
    
    Sprite* title = Sprite::create("img_window_title8.png");
    title->setPosition(Vec2(0, 190));
    popupStartTeach->addChild(title);
    
    Sprite* content = Sprite::create("img_window_paper4.png");
    content->setPosition(Vec2::ZERO);
    popupStartTeach->addChild(content);
    
//    log(LSTRING("GuideText9"));
    
    Label* context = Label::createWithSystemFont(LSTRING("GuideText9"), "arial", 35);
    context->setDimensions(400, 120);
    context->setPosition(Vec2(0,50));
    context->setColor(Color3B(203,  73,  24));
    context->setHorizontalAlignment(TextHAlignment::CENTER);
    context->setVerticalAlignment(TextVAlignment::CENTER);
    popupStartTeach->addChild(context);
    
    auto btnSkip=cocos2d::ui::Button::create("img_window_btn_red.png");
    btnSkip->setPosition(Point(-150,-240));
    btnSkip->setTitleText(LSTRING("SKIP"));
    btnSkip->setTitleFontName("Arial");
    btnSkip->setTitleFontSize(40);
    btnSkip->setTitleColor(Color3B(255, 255, 255));
    btnSkip->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            CommonData::getInstance()->put(1, 1);
            
            
            //返回菜单
            Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
            Director::getInstance()->replaceScene(CheckpointScene::create());
        }
    });
    
    auto btnStart=cocos2d::ui::Button::create("img_window_green.png");
    btnStart->setPosition(Point(150,-240));
    btnStart->setTitleText(LSTRING("DoTask"));
    btnStart->setTitleFontName("Arial");
    btnStart->setTitleFontSize(40);
    btnStart->setTitleColor(Color3B(12, 63, 10));
    btnStart->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            isGamePause = false;
            popupStartTeach->hide();
        }
    });
    popupStartTeach->addChild(btnSkip);
    popupStartTeach->addChild(btnStart);
    
    addChild(popupStartTeach, 9999);
    
    // 教程完毕弹窗
    popupGetPrize = PopupLayer::create("img_window_bg.png");
    popupGetPrize->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    Sprite* titlebg2 = Sprite::create("img_window_title_bg.png");
    titlebg2->setPosition(Vec2(0, 190));
    popupGetPrize->addChild(titlebg2);
    
    Sprite* title2 = Sprite::create("img_window_title8.png");
    title2->setPosition(Vec2(0, 190));
    popupGetPrize->addChild(title2);
    
    Sprite* content2 = Sprite::create("img_window_paper4.png");
    content2->setPosition(Vec2::ZERO);
    popupGetPrize->addChild(content2);
    
    Label* context2 = Label::createWithSystemFont(LSTRING("GuideText10"), "arial", 35);
    context2->setDimensions(400, 120);
    context2->setPosition(Vec2(0,50));
    context2->setColor(Color3B(203,  73,  24));
    context2->setHorizontalAlignment(TextHAlignment::CENTER);
    context2->setVerticalAlignment(TextVAlignment::CENTER);
    popupGetPrize->addChild(context2);
    
    auto btnOK=cocos2d::ui::Button::create("img_window_green.png");
    btnOK->setPosition(Point(0,-240));
    btnOK->setTitleText(LSTRING("OK"));
    btnOK->setTitleFontName("Arial");
    btnOK->setTitleFontSize(40);
    btnOK->setTitleColor(Color3B(12, 63, 10));
    btnOK->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            popupGetPrize->hide();
            // 得晶核
            CommonData::getInstance()->addCrystal(3);
            
            CommonData::getInstance()->put(1, 1);

            
            //返回菜单
            Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
            Director::getInstance()->replaceScene(CheckpointScene::create());
        }
    });
    popupGetPrize->addChild(btnOK);
    addChild(popupGetPrize, 9999);
    
    // 非首次过关后弹窗
    popupWin = PopupLayer::create("img_window_bg.png");
    popupWin->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg3 = Sprite::create("img_window_title_bg.png");
    titlebg3->setPosition(Vec2(0, 190));
    popupWin->addChild(titlebg3);
    
    Sprite* title3 = Sprite::create("img_window_title8.png");
    title3->setPosition(Vec2(0, 190));
    popupWin->addChild(title3);
    
    Sprite* content3 = Sprite::create("img_window_paper.png");
    content3->setPosition(Vec2::ZERO);
    popupWin->addChild(content3);
    
    Label* context3 = Label::createWithSystemFont(LSTRING("GuideText11"), "arial", 35);
    context3->setDimensions(400, 120);
    context3->setPosition(Vec2(0,0));
    context3->setColor(Color3B(203,  73,  24));
    context3->setHorizontalAlignment(TextHAlignment::CENTER);
    context3->setVerticalAlignment(TextVAlignment::CENTER);
    popupWin->addChild(context3);
    
    auto btnOK2=cocos2d::ui::Button::create("img_window_green.png");
    btnOK2->setPosition(Point(0,-240));
    btnOK2->setTitleText(LSTRING("OK"));
    btnOK2->setTitleFontName("Arial");
    btnOK2->setTitleFontSize(40);
    btnOK2->setTitleColor(Color3B(12, 63, 10));
    btnOK2->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            CommonData::getInstance()->put(1, 1);
            popupWin->hide();
            //返回菜单
            Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
            Director::getInstance()->replaceScene(CheckpointScene::create());
        }
    });
    popupWin->addChild(btnOK2);
    addChild(popupWin, 9999);
    
    
}

void TutorialScene::popupCloseCallBack(Ref *pSender) {
//    isGamePause = false;
    Manager::getInstance()->playSoundEffect("btnPress.mp3");
    Manager::getInstance()->resumeBackgroundMusic();
}

// 显示提示
void TutorialScene::showTextHint(int step)
{
    if (!showHint) {
        return;
    }
    curStep = step;
    switch (step) {
        case 1:
            // 出现电池吃掉
        {
//            text->setString(LSTRING("GuideText1"));
            textTitle->setTexture("img_guide_word3.png");
//            shadowlayer->removeFromParent();
//            shadowlayer = NULL;
            isWalk = true;
            Box *b = Box::createMyBox(BoxType::dripbox);
            b->setPosition(3*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 4;
            b->isDead = true;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
            lifeBarLight(-1);
            
            
            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            arrow2->setPosition(Vec2(-200,-200));
            
            leftLight->setPosition(arrowLeft->getPosition());
            rightLight->setPosition(-200,-200);
        }
            break;
        case 2:
            // 躲避粘液
        {
//            text->setString(LSTRING("GuideText2"));
            textTitle->setTexture("img_guide_word4.png");
            Box *b = Box::createMyBox(BoxType::dustbox);
            b->setPosition(3*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+5*GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 4;
            b->isDead = false;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            arrow2->setPosition(4*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+GRID_SIZE+60);
            
            if (getChildByTag(999)) {
                removeChildByTag(999);
            }
            
            leftLight->setPosition(-200,-200);
            rightLight->setPosition(arrowRight->getPosition());
        }

            break;
        case 3:
            // 躲避炸弹
        {
//            text->setString(LSTRING("GuideText3"));
            textTitle->setTexture("img_guide_word5.png");
            Box *b = Box::createMyBox(BoxType::sunbox);
            b->setPosition(4*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+5*GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 5;
            b->isDead = false;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            arrow2->setPosition(6*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+GRID_SIZE+60);
            
            leftLight->setPosition(-200,-200);
            rightLight->setPosition(arrowRight->getPosition());
        }
            
            break;
        case 4:
            // 提示冰块
        {
//            text->setString(LSTRING("GuideText4"));
//            textTitle->setTexture("img_guide_word6.png");
            textTitle->setVisible(false);
            Box *b = Box::createMyBox(BoxType::hailbox);
            b->setPosition(6*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+7*GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 7;
            b->isDead = false;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
//            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            
            isWalk = true;
            player->setIsFrozen(true);
        }
            
            break;
        case 5:
            // 提示点击五次冰块解冻
        {
//            text->setString(LSTRING("GuideText5"));
            textTitle->setVisible(true);
            textTitle->setTexture("img_guide_word7.png");
        }
            
            break;
        case 6:
            // 提示提示左移到顶
        {
//            text->setString(LSTRING("GuideText6"));
            textTitle->setTexture("img_guide_word10.png");
            
            arrow2->setPosition(GRID_RADIUS_SIZE, deadLine+4*GRID_SIZE+60);
            
            leftLight->setPosition(arrowLeft->getPosition());
            rightLight->setPosition(-200,-200);
        }
            
            break;
        case 7:
            // 提示打BOSS
        {
//            text->setString(LSTRING("GuideText7"));
            textTitle->setTexture("img_guide_word11.png");
            // 添加一排箱子
            for (int i = 1; i<8; i++) {
                Box *b = Box::createMyBox(BoxType::normalbox);
                b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+3*GRID_SIZE+GRID_RADIUS_SIZE);
                b->track = i+1;
                b->isDead = true;
                b->targetPositionY = deadLine+3*GRID_SIZE+GRID_RADIUS_SIZE;
                b->setOpacity(0);
                
                addChild(b);
                boxlist.push_back(b);
                ActionInterval *in = FadeIn::create(0.5);
                b->runAction(in);
            }
            // 箱子整体下移
            moveAllBox(line->getPositionY()-deadLine-GRID_SIZE);
            
            // boss出现
            Monster* monster = Monster::createMonster(1);
            monster->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT - 150 );
            addChild(monster,1,99);
            
            leftLight->setPosition(-200,-200);
            rightLight->setPosition(-200,-200);
        }
            
            break;
        case 8:
        {
            // 完成新手教程
//            text->setString(LSTRING("GuideText8"));
            if (CommonData::getInstance()->get(1) == 1) {
                isGamePause = true;
                popupWin->show();
            }
            else
            {
                isGamePause= true;
                popupGetPrize->show();
            }
        }
            
            break;
        case 9:
        {
            // 开始教程，点击左边屏幕
//            text->setString(LSTRING("GuideText12"));
            textTitle->setTexture("img_guide_word1.png");
            isWalk = true;
//            shadowlayer = LayerColor::create(Color4B::BLACK, SCREEN_WIDTH/2, SCREEN_HEIGHT);
//            shadowlayer->setPosition(0,0);
//            shadowlayer->setOpacity(100);
//            FadeTo* a = FadeTo::create(0.5,100);
//            FadeOut* a2 = FadeOut::create(0.5);
//            Sequence* action = Sequence::create(a, a2, NULL);
//            RepeatForever* repeat = RepeatForever::create(action);
//            shadowlayer->runAction(repeat);
//            addChild(shadowlayer);
            
//            arrow2->setPosition(86, 340);
            
            leftLight->setPosition(arrowLeft->getPosition());
            rightLight->setPosition(-200,-200);
        }
            break;
        case 10:
        {
            // 点击右边屏幕
//            text->setString(LSTRING("GuideText13"));
            textTitle->setTexture("img_guide_word2.png");
            isWalk = true;
//            if (shadowlayer) {
//                shadowlayer->setPosition(SCREEN_CENTER.x,0);
//            }
//            else
//            {
//                shadowlayer = LayerColor::create(Color4B::BLACK, SCREEN_WIDTH/2, SCREEN_HEIGHT);
//                shadowlayer->setPosition(0,0);
//                shadowlayer->setOpacity(100);
//                addChild(shadowlayer);
//            }
//            arrow2->setPosition(554, 340);
            
            leftLight->setPosition(-200,-200);
            rightLight->setPosition(arrowRight->getPosition());

        }
            break;
        case 11:
        {
            // 掉能量
//            text->setString(LSTRING("GuideText14"));
            textTitle->setTexture("img_guide_word8.png");
            isWalk = true;
            player->setIsFrozen(true);
            isGamePause = true;
            
            Box *b = Box::createMyBox(BoxType::powerBall);
            b->setPosition(6*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+5*GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 7;
            b->isDead = false;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            
            powerLight(-1);
            
        }
            break;
        case 12:
        {
            // 用金钟罩
//            text->setString(LSTRING("GuideText15"));
            textTitle->setTexture("img_guide_word9.png");
            isWalk = true;
            player->setIsFrozen(true);
            isGamePause = true;
            Box *b = Box::createMyBox(BoxType::normalbox);
            b->setPosition(6*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+5*GRID_SIZE+GRID_RADIUS_SIZE);
            b->track = 7;
            b->isDead = false;
            b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
            b->setOpacity(0);
            addChild(b);
            boxlist.push_back(b);
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            
            jinengLight(-1);
            
            arrow1->setPosition(b->getPosition()+Vec2(-30,90));
            arrow2->setPosition(Vec2(80,170));
        }
            break;
        default:
            break;
    }
    showHint = false;
}

void TutorialScene::initHint()
{
    arrow1 = Sprite::create("img_guide_arrow.png");
    arrow1->setPosition(Vec2(-100,-200));
    addChild(arrow1,100);
//    arrow1->setVisible(false);
    arrow2 = Sprite::create("img_guide_arrow2.png");
    arrow2->setPosition(Vec2(-100,-200));
    addChild(arrow2,100);
//    arrow2->setVisible(false);
    
//    Blink* b1 = Blink::create(1.9, 5);
//    RepeatForever* r1 = RepeatForever::create(b1);
//    arrow1->runAction(r1);
//    arrow2->runAction(r1->clone());
    
    textHintNode = Node::create();
    textHintNode->setPosition(SCREEN_CENTER+Vec2(0,300));
    addChild(textHintNode, 100);
    Sprite* textBG = Sprite::create("img_guide_blackboard.png");
    textBG->setPosition(Vec2::ZERO);
    textHintNode->addChild(textBG);
    
    textTitle = Sprite::create("img_guide_word1.png");
    textTitle->setPosition(80,22);
    textHintNode->addChild(textTitle,10);
    
//    text = Label::createWithSystemFont(LSTRING("GuideText1"), "arial", 32);
//    text->setDimensions(430, 140);
//    text->setPosition(Vec2(80,22));
//    textHintNode->addChild(text,10);
//    text->setHorizontalAlignment(TextHAlignment::CENTER);
//    text->setVerticalAlignment(TextVAlignment::CENTER);
    
    
    ActionInterval *in = FadeIn::create(0.5);
    textHintNode->runAction(in);
    
    leftLight = Sprite::create("img_play_arrow_left_light.png");
    leftLight->setPosition(Vec2(-200,-222));
    addChild(leftLight,101);
    rightLight = Sprite::create("img_play_arrow_right_light.png");
    rightLight->setPosition(Vec2(-200,-222));
    addChild(rightLight,101);
    
    Blink* b1 = Blink::create(1.9, 5);
    RepeatForever* r1 = RepeatForever::create(b1);
    leftLight->runAction(r1);
    rightLight->runAction(r1->clone());
}

void TutorialScene::destroyBox() {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
        Box *b = (*iter);
        if(b->isDestroy) {
            
            if (b->type == dustbox) {
                // 灰尘
                isGamePause = true;
                isWalk = true;
                showHint = true;
                showTextHint(3);
            }
            else if (b->type == sunbox){
//                isGamePause = true;
//                isWalk = true;
                showHint = true;
                showTextHint(4);
                Manager::getInstance()->playSoundEffect("bombSound.mp3");
                // 播爆炸动画
                Sprite* bomb = Sprite::create("img_boss_bomb6.png");
                Sprite* bomb2 = Sprite::create("img_boss_bomb6.png");
                Sprite* bomb3 = Sprite::create("img_boss_bomb6.png");
                bomb->setPosition(b->getPosition()-Vec2(GRID_SIZE,0));
                bomb2->setPosition(b->getPosition());
                bomb3->setPosition(b->getPosition()+Vec2(GRID_SIZE,0));
                addChild(bomb);
                addChild(bomb2);
                addChild(bomb3);
                
                bomb->setScale(0.1);
                bomb2->setScale(0.1);
                bomb3->setScale(0.1);
                ScaleTo* s = ScaleTo::create(0.3, 0.4);
                FadeOut* f = FadeOut::create(0.2);
                Sequence* action = Sequence::create(s,f, NULL);
                bomb->runAction(action);
                bomb2->runAction(action->clone());
                bomb3->runAction(action->clone());
            }
            
            boxRemoveAction(b);
            removeChild(b);
            iter = boxlist.erase(iter);
            
            continue;
        }
        ++iter;
    }
}

void TutorialScene::moveBox()
{
    int removeDripTrack = 0; //移除这一列所有的水滴
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end();) {
        Box *box = (*iter);
        if (box) {
            if(!box->isDead) { // 箱子不能是静止状态
                if((box->getPositionY() - box->targetPositionY ) <= 5) {  // 如果下落的箱子,距离下落目标的距离低于移动速度, 就直接到下落目标的坐标
                    log("最后一步小于速度,直接到目标坐标 %f, track :%d",box->targetPositionY,box->track);
                    box->setPositionY(box->targetPositionY);
                    
                    if (box->type != BoxType::dripbox || box->type != BoxType::powerBall) {
                        removeDripTrack = box->track;
                    }
                    
                    if(box->type == BoxType::dustbox || box->type == BoxType::sunbox || box->type == BoxType::bullet) {
                        
                        //如果是灰尘,或者阳光,落地后直接回收
                        //                        removeActionChild(box);
                        //                        boxlist.remove(box);
                        box->isDestroy = true;
                        if(box->type == BoxType::sunbox) {
//                            this->removeTrackBox(box->track);
                        }
                    }

                    if (box->type == BoxType::dustbox) {
                        for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
                            
                            Box *b = (*iter);
                            if (box->track == b->track ) {
                                b->slowbox();
                                b->isSlow = true;
                            }
                            iter++;
                        }
                    }

                    //
                    
                    if (box->type != BoxType::waterBall && box->type != BoxType::powerBall) {
                        for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
                            Box *b = (*iter);
                            if(b->track == removeDripTrack && (b->type == BoxType::waterBall || b->type == BoxType::powerBall)) {
                                boxRemoveAction(b);
                                removeChild(b);
                                removeDripTrack = 0;
                                iter = boxlist.erase(iter);
                                continue;
                            }
                            iter++;
                        }
                    }
                    
                    //冰雹落地变身
                    //                            if (box->type == BoxType::hailbox) {
                    //                                box->setTexture("img_icestone_change.png");
                    //                            }
                    box->isDead = true;
//                    iter = dropBoxList.erase(iter);
                    continue;
                } else { //正常移动
                    int level = 0;
                    if (level == 0) {
                        if (level/15 < 4) {
                            box->setPosition(box->getPosition().x,box->getPosition().y - 5 + level/15);
                        } else {
                            box->setPosition(box->getPosition().x,box->getPosition().y - 5 + 4);
                        }
                    } else {
//                        if ((level%10)/2 < 2) {
//                            box->setPosition(box->getPosition().x,box->getPosition().y - BOX_SPEED*boxSpeed+(level%10)/2);
//                        } else {
//                            box->setPosition(box->getPosition().x,box->getPosition().y - BOX_SPEED*boxSpeed + 2);
//                        }
                    }
                }
                
            }
        }
        ++iter;
    }
}

void TutorialScene::removeTrackBox(int track) {
    Box *removeBox = NULL;
    float y = 0;
    
    //循环查找同轨道下最高的箱子
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *b = (*iter);
        
        if(track == b->track) { // 必须是同轨道才考虑计坐标
            if (y <= b->targetPositionY && b->targetPositionY > deadLine) { //同轨道且大于需要下落箱子的目标坐标, 才会覆盖目标坐标
                y = b->targetPositionY;
                removeBox = b;
            }
        }
    }
    
    if(removeBox) {
        boxlist.remove(removeBox);
        removeChild(removeBox);
    }
}

void TutorialScene::boxRemoveAction(Box *box) {
    Box *b = Box::createMyBox(box->type);
    b->setPosition(box->getPosition());
    addChild(b);
    //    CallFunc * funcall= CallFunc::create(this, callfunc_selector(PlayScene::removeActionChild));
    CallFunc * funcall= CallFuncN::create(std::bind(&TutorialScene::removeActionChild, this,b));
    ActionInterval * moveBy = MoveTo::create(0.5,Vec2(b->getPositionX(), b->getPositionY()+30));
    ActionInterval * fadeout = FadeOut::create(0.5);
    FiniteTimeAction * spawn = Spawn::create(moveBy,fadeout,NULL);
    FiniteTimeAction * seq = Sequence::create(spawn,funcall,NULL);
    b->runAction(seq);
    
}

void TutorialScene::removeActionChild(Node* node)
{
    removeChild(node);
    if (curStep == 7) {
        if (getChildByTag(99)) {
            removeChildByTag(99);
            //        FadeOut* f = FadeOut::create(0.5);
            //        getChildByTag(99)->runAction(f);
            showHint = true;
            showTextHint(8);
        }
    }
}

void TutorialScene::moveAllBox(float _y) {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *b = (*iter);
        b->targetPositionY -=  _y; //重设箱子的目标矩阵
        
        //播下落一格的动画
        ActionInterval * moveTo = MoveTo::create(_y/GRID_SIZE,Vec2(b->getPositionX(),b->targetPositionY));
        b->runAction(moveTo);
    }
    
    int level = 1;
    if (level != 0) {
        ActionInterval *lineMoveTo = MoveTo::create(_y/GRID_SIZE,Vec2(0,line->getPositionY()-_y*GRID_SIZE));
        line->runAction(Sequence::create(lineMoveTo, CallFunc::create(CC_CALLBACK_0(TutorialScene::showWaterBall, this)), NULL));
    }

}

void TutorialScene::showWaterBall()
{
    Box *b = Box::createMyBox(BoxType::waterBall);
    b->setPosition(3*GRID_SIZE+GRID_RADIUS_SIZE, deadLine+GRID_SIZE+GRID_RADIUS_SIZE);
    b->track = 4;
    b->isDead = false;
    b->targetPositionY = deadLine+GRID_SIZE+GRID_RADIUS_SIZE;
    b->setOpacity(0);
    addChild(b);
    boxlist.push_back(b);
    ActionInterval *in = FadeIn::create(0.5);
    b->runAction(in);
    
    arrow1->setPosition(b->getPosition()+Vec2(-30,90));
    
    leftLight->setPosition(-200,-200);
    rightLight->setPosition(arrowRight->getPosition());
}

// 0是死亡
void TutorialScene::dripDelegateDead(BaseRole* node, int num)
{
    
}
// 消除碰到的箱子
void TutorialScene::dripDelegateRemoveHailBox(BaseRole* node, Box* box)
{
    box->isDestroy = true;
    if (box->type == dripbox) {
        // 电池
//        showTextHint(2);
        isGamePause = true;
//        lifeBarLight();
        
    }
    else if (box->type == hailbox)
    {
        // 冰块
        showHint = true;
        showTextHint(5);
        lifeBarLight(1);
    }
    else if (box->type == normalbox)
    {
        // 普通
        showHint = true;
        player->setIsFrozen(false);
        showTextHint(6);
    }
}
// 碰到伞
void TutorialScene::dripDelegateUmbrella(BaseRole* node)
{
    
}
// 碰到水炮
void TutorialScene::dripDelegateWaterBall(BaseRole* node,Box* box)
{
    arrow1->setPositionX(-200);
    
    Sprite* sprite = Sprite::create("img_boss_attack6.png");
    sprite->setPosition(Vec2(SCREEN_WIDTH / 2, 200));
    sprite->setVisible(false);
    this->addChild(sprite);
    log("WaterBall");
    sprite->setPosition(box->getPosition());
    sprite->setTexture("img_boss_attack6.png");
    sprite->setVisible(true);
    MoveTo* m = MoveTo::create(0.5f, Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT -180));
    sprite->runAction(Sequence::create(m, CallFunc::create(CC_CALLBACK_0(TutorialScene::attackBossCallback, this, sprite)),//调用runMyAction播放下一个动画
                                       NULL));
    sprite->runAction(m);
}

void TutorialScene::attackBossCallback(Sprite * sprite)
{
    sprite->setTexture("img_boss_bomb6.png");
    sprite->runAction(ScaleBy::create(0.5, 2));
    sprite->runAction(Sequence::create(DelayTime::create(0.2), CallFunc::create(CC_CALLBACK_0(TutorialScene::removeActionChild, this, sprite)),NULL));
    

}

// 碰到灰尘
void TutorialScene::dripDelegatevirusesBox(BaseRole* node,int track)
{
    
}
// 碰到能量
void TutorialScene::dripDelegatePowerBox(BaseRole* node,Box* box)
{
    if (txtGold) {
        txtGold->setString("10");
    }
    showHint = true;
    showTextHint(12);
}

// 血条发光
void TutorialScene::lifeBarLight(int loop)
{
    Sprite* light = Sprite::create("img_blood_light.png");
    if (health) {
        light->setPosition(health->getPosition());
    }
    addChild(light,999,999);
    
    auto fi = FadeIn::create(0.5);
    auto fo = FadeOut::create(0.5);
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        ((Sprite *)pSender)->removeFromParent();
    });
    
    if (loop == 1) {
        light->runAction(Sequence::create(fi, fo, actFunc, NULL));
    }
    else
    {
        RepeatForever* repeat = RepeatForever::create(Sequence::create(fi, fo, NULL));
        light->runAction(repeat);
    }
    
}

// 能量发光
void TutorialScene::powerLight(int loop)
{
    Sprite* light = Sprite::create("img_power_light.png");
    if (txtGold) {
        light->setPosition(txtGold->getPosition()-Vec2(30,0));
    }
    addChild(light,150,999);
    
    auto fi = FadeIn::create(0.5);
    auto fo = FadeOut::create(0.5);
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        ((Sprite *)pSender)->removeFromParent();
    });
    
    if (loop == 1) {
        light->runAction(Sequence::create(fi, fo, actFunc, NULL));
    }
    else
    {
        RepeatForever* repeat = RepeatForever::create(Sequence::create(fi, fo, NULL));
        light->runAction(repeat);
    }
}

// 技能发光
void TutorialScene::jinengLight(int loop)
{
    Sprite* light = Sprite::create("img_prop_light.png");
    light->setPosition(80,60);
    addChild(light,999,1000);
    
    auto fi = FadeIn::create(0.2);
    auto fo = FadeOut::create(0.2);
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        ((Sprite *)pSender)->removeFromParent();
    });
    
    if (loop == 1) {
        light->runAction(Sequence::create(fi, fo, actFunc, NULL));
    }
    else
    {
        RepeatForever* repeat = RepeatForever::create(Sequence::create(fi, fo, NULL));
        light->runAction(repeat);
    }
}

// 喷气背包动作完成回调
void TutorialScene::dripDelegateBagEffectFinish()
{
    
}


void TutorialScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event)
{
    
}

void TutorialScene::LevelInfoTextLayerDelegateClose()
{
    if (infoLayer) {
        removeChild(infoLayer);
        isGamePause = false;
    }
}