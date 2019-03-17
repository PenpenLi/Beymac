//
//  PlaySence.cpp
//  PuzzleBobble2
//
//  Created by lingzerg on 15/3/3.
//
//

#include "PlayScene.h"
#include "Manager.h"
#include "HomeScene.h"
#include "CheckpointScene.h"
#include "WheelPanelScene.h"
#include "GetPrizeHint.h"
#include "ShopScene.h"
#include "PlaySceneState.h"
#include "FinishGameScene.h"
#include "SkillSelectScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSHelper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "AndroidHelper.h"
#endif


PlayScene::PlayScene() {
    
}

PlayScene::~PlayScene() {
    
}


Scene* PlayScene::createScene(int level) {
    auto scene = Scene::create();
    auto layer = PlayScene::create(level,"",999);
    scene->addChild(layer);
    return scene;
}

string targetName = "PK对手:"; //目标姓名
int targetF = 999; //目标层数

Scene* PlayScene::createScene(int level, const char *name, int targetFloor) {
    auto scene = Scene::create();
    auto layer = PlayScene::create(level,name, targetFloor);
    
    scene->addChild(layer);
    return scene;
}

Scene* PlayScene::createScene() {
    auto scene = Scene::create();
    auto layer = PlayScene::create(0,"",999);
    scene->addChild(layer);
    return scene;
}

PlayScene* PlayScene::create(int level,const char *name, int targetFloor) {
    PlayScene *pRet = new PlayScene();
    if (pRet && pRet->init(level,name,targetFloor))
    {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayScene::init(int level, const char *name, int targetFloor) {
    if (!Layer::init())
    {
        return false;
    }
    targetName = name;
    targetF = targetFloor;
    this->level = level;
    initData();
    
    return true;
}

int goldEnergy;
Label *txtGoldPower;

void PlayScene::setBg() {
    
    
    
//    CommonData::getInstance()->addEnergy(100);
    
    auto bg = Sprite::create();
    auto *front = Sprite::create();
    bg->setTexture("img_scene1_bg.jpg");
    
    Manager::getInstance()->playBackgroundMusic("playBGM.mp3");
    if (level != 0) {
        //初始化进boss战线条
        line = DottedLine::createNode();
        line->setLocalZOrder(2);
        line->setPosition(0,256+data->getFloor()*GRID_SIZE);
        levelType = level%5;
        if (levelType == 1) {
            
            normaltype = BoxType::normalbox;
            bg->setTexture("img_scene1_bg.jpg");
        }
        
        if (levelType == 2) {
            normaltype = BoxType::normalbox2;
            
            bg->setTexture("img_scene2_bg.jpg");
        }
        
        if (levelType == 3) {
            normaltype = BoxType::normalbox3;
            
            bg->setTexture("img_scene3_bg.jpg");
        }
        
        if (levelType == 4) {
            normaltype = BoxType::normalbox4;
            
            bg->setTexture("img_scene4_bg.jpg");
        }
        
        if (levelType == 5) {
            normaltype = BoxType::normalbox5;
            bg->setTexture("img_scene5_bg.jpg");
        }
        addChild(line);
        
        if (level%5 == 0 && level != 50) {
            line->setVisible(false);
        
            
            auto imgcount = Sprite::create("img_count.png");
            
            imgcount->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT-100);
            this->addChild(imgcount);
            timer = LabelAtlas::create("40", "img_play_number_layer.png", 41, 58, '0');//21, 28
            timer->setPosition((SCREEN_WIDTH-timer->getContentSize().width)/2,SCREEN_HEIGHT-200);
            this->addChild(timer,99);
        }
    }
    
    bg->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
    front->setPosition(front->getContentSize().width/2,front->getContentSize().height/2);
    addChild(bg,-2);
    addChild(front,0);
    
    //添加提示条到舞台
    for (int i = 0; i< 8; i++) {
        tips[i] = Tip::createMyTip();
        tips[i]->cocos2d::Node::setPosition(i*GRID_SIZE+GRID_SIZE/2, SCREEN_HEIGHT-(tips[i]->getContentSize().height)+tips[i]->getContentSize().height/2);
        addChild(tips[i]);
        tips[i]->setVisible(false);
    }
    
    //添加水滴到舞台
    player = BeyMac::create();

    player->setPosition(SCREEN_CENTER);
    player->setPositionY(DEAD_LINE + player->getContentSize().height/2 );
    player->setTag(10000);
    
    if (CommonData::getInstance()->getHealth() <= 1 || level == 0) {
        player->setBlood(1);
        if(level%5 == 0 && level % 10 != 0  && level != 50) {
            player->setBlood(2);
        }
    } else {
        player->setBlood(CommonData::getInstance()->getHealth());
    }
    
    player->setPlayScene(this);
    addChild(player);
    player->createfollowers();
    
    auto bgbar = Sprite::create("img_play_blue.png");
    bgbar->setPosition(Vec2(bgbar->getContentSize().width/2, bgbar->getContentSize().height/2));
    addChild(bgbar,1);
    
    
    health = Health::createNode();
    health->setPosition(432,146);
    health->setLocalZOrder(101);
    addChild(health);
    
    auto *gold = Sprite::create("img_play_icon_power.png");
    gold->setPosition(260,146);
    gold->setLocalZOrder(101);
    addChild(gold);
    
    txtGold = Label::create();
    txtGold->setTextColor(Color4B::WHITE);
    txtGold->setString(NUM_TO_STR(myEnergy));
    txtGold->setSystemFontSize(30);
    txtGold->setPosition(314,146);
    txtGold->setLocalZOrder(101);
    addChild(txtGold);
    
    //金色能量图标
    auto goldPower = Sprite::create("img_play_icon_power_gold.png");
    goldPower->setPosition(140,146);
    addChild(goldPower,101);
    
    auto arrowLeft = Sprite::create("img_play_arrow_left.png");
    arrowLeft->setPosition(Vec2(86, 222));
    addChild(arrowLeft,100);
    
    auto arrowRight = Sprite::create("img_play_arrow_right.png");
    arrowRight->setPosition(Vec2(554, 222));
    addChild(arrowRight,100);
    
    txtGoldPower = Label::create();
    txtGoldPower->setTextColor(Color4B::WHITE);
    txtGoldPower->setString(NUM_TO_STR(goldEnergy));
    txtGoldPower->setSystemFontSize(30);
    txtGoldPower->setPosition(198,146);
    txtGoldPower->setLocalZOrder(101);
    addChild(txtGoldPower);
    
    //    health
    
    deadline = SCREEN_HEIGHT - (verticalCount+1) * GRID_SIZE;
    firstline = deadline + GRID_SIZE;
    log("deadline: %f",deadline);
    
    score = LabelAtlas::create(String::createWithFormat("%d",floor)->_string, "img_play_number_layer.png", 41, 58, '0');
    score->setPosition((SCREEN_WIDTH-score->getContentSize().width)/2,182);
    
    addChild(score,100);
}

LevelInfoTextLayer *levelInfo;


//初始化矩阵
void PlayScene::initData() {
    
    isGameOver = false;
    
    ws = new WebService(this);
    this->isSceneRunning = true;
    
    if (level == 0) {
        auto head = Sprite::create("img_play_pk_bg.png");
        head->setPosition(Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.8));
        
        auto txt = Text::create();
        
//        targetName = "..."; //目标姓名
//        targetFloor = 999;
        string txtContext;
        txtContext.append(targetName);
        txtContext.append(String::createWithFormat("\nPK层数:%d",targetF)->_string);
        
        txt->setString(txtContext);
        txt->setTextHorizontalAlignment(TextHAlignment::LEFT);
        txt->setColor(Color3B(255, 255, 255));
        txt->setFontSize(30);
        txt->setPosition(Vec2(head->getContentSize().width/2,head->getContentSize().height/2-45));
        head->addChild(txt,2);
        
        addChild(head,1);
    }
    
    data = ReadDataFromMap::getInstance()->readLevelDataByLevel(level);
    goldEnergy = CommonData::getInstance()->getEnergy();
//    bulletSpeed
    if(level != 0) {
        
        boxSpeed = itemDropTime(data->getBulletSpeed())*0.1;
        myEnergy = data->getStartEnergy();
        amountOfEnergy = data->getAmountOfEnergy();
        boxEnergy = data->getEnergy();
        
        //反弹球速度
        lb = LaserBullet::create(itemDropTime(data->getBulletSpeed()), itemDropTime(data->getBulletSpeed()), 1);
        lb->setPosition(Vec2(arc4random()%SCREEN_WIDTH, SCREEN_HEIGHT+GRID_SIZE));
        lb->setDelegate(this);
        if(level%5 != 0 || level == 50) {
            lb->setIsUpdate(false);
        }
        
        if(level%5 == 0 && level %10 != 0 && level != 50) {
            lb->setType(1);
        } else if(level %10 == 0  &&  level != 50){
            lb->setType(2);
        }
        addChild(lb,5);
    }else {
        myEnergy = 40;
    }
    
    
    playSceneState = PlaySceneState::createNode(this, data->getPromptTime());
    playSceneState->enCurState = EnumState::dropOver;
    
    
    
    auto listenerKeyCode = EventListenerKeyboard::create();
    listenerKeyCode->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyCode, this);
    
    time = 0.0;
    for (int j = 0; j <(SCREEN_HEIGHT-200) / GRID_SIZE -1 ; j++) {
        for (int i = 0 ; i< CELL_HORIZONTAL_SIZE ; i++) {
            verticalCount = j;
        }
    }
    
    this->setBg();
    
    
    jishi = Jishiqi::create();
    jishi->setText("0");
    jishi->setBg(1);
    jishi->setPosition(SCREEN_CENTER);
    jishi->setLocalZOrder(101);
    jishi->setVisible(false);
    addChild(jishi);
    
    
    
    
    
    //skill1 - 4
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(PlayScene::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(PlayScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    dripTip = Tip::createMyTip();
    dripTip->setTexture("img_warning_heart.png");
    dripTip->setPosition(0,0);
    
    addChild(dripTip);
    dripTip->setVisible(false);
    
    //设置水滴代理,用来反馈水滴的状态(生死)
    player->setDelegate(this);
    
//    if (level != 0) {
        //初始化boss动画组件
    if((level !=0 && level%5 !=0) || level == 50) {
        monster = Monster::createMonster(level);
        monster->setcallbackFunc(this);
        monster->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT*2);
        addChild(monster,-1);
    }
        laserBoss = SLaserBulletArray::createLBlistByPlayer(-10, 1, Vec2(-200, SCREEN_HEIGHT+500), this);
        addChild(laserBoss);
    
//    }
    
    
    
    
    
    this->initBtn();
    this->initPopup();
    isGamePause = true;
    if(level%2 != 0 && (CommonData::getInstance()->get(level) == CHECKPOINT_PLAYABLE || CommonData::getInstance()->get(level) == 0)) {
        levelInfo = LevelInfoTextLayer::create(level,this);
        addChild(levelInfo,13141516,999999);
    } else {
        
        if(level == 4) {
            
            isGamePause = true;
            auto textHintNode = Node::create();
            textHintNode->setPosition(SCREEN_CENTER+Vec2(0,300));
            addChild(textHintNode,100,2596);
            
            Sprite* textBG = Sprite::create("img_guide_blackboard.png");
            textBG->setPosition(Vec2::ZERO);
            textHintNode->addChild(textBG);
            
            auto textTitle = Sprite::create("img_guide4_word.png");
            textTitle->setPosition(80,22);
            textHintNode->addChild(textTitle,10);
            
            auto btnTips = Sprite::create("img_guide_arrow2.png");
            btnTips->setPosition(Vec2(40, 700));
            Blink* b1 = Blink::create(1.9, 5);
            RepeatForever* r1 = RepeatForever::create(b1);
            btnTips->runAction(r1);
            addChild(btnTips,100,2597);
            
            auto btnMask = Sprite::create();
            
            auto listener2=EventListenerTouchOneByOne::create();
            listener2->setSwallowTouches(true);
            listener2->onTouchBegan=[](Touch *touch,Event *event){
                return true;
            };
            listener2->onTouchMoved=[](Touch *touch,Event *event){
            };
            listener2->onTouchEnded=[=](Touch *touch,Event *event){
                //            btnMask->setVisible(false);
                //            this->removeChildByTag(2596);
                //            startGame();
                //            _eventDispatcher->removeEventListenersForTarget(btnMask);
            };
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, btnMask);
            btnMask->setTag(2598);
            addChild(btnMask,5);
            
            
        } else if(level == 5) {
            isGamePause = true;
            auto textHintNode = Node::create();
            textHintNode->setPosition(SCREEN_CENTER+Vec2(0,300));
            addChild(textHintNode,100,2596);
            
            Sprite* textBG = Sprite::create("img_guide_blackboard.png");
            textBG->setPosition(Vec2::ZERO);
            
            textHintNode->addChild(textBG);
            
            auto textTitle = Sprite::create("img_guide5_word.png");
            textTitle->setPosition(80,22);
            textHintNode->addChild(textTitle,10);
            
            auto btnMask = Sprite::create();
            
            auto listener2=EventListenerTouchOneByOne::create();
            listener2->setSwallowTouches(true);
            listener2->onTouchBegan=[](Touch *touch,Event *event){
                return true;
            };
            listener2->onTouchMoved=[](Touch *touch,Event *event){
            };
            listener2->onTouchEnded=[=](Touch *touch,Event *event){
                btnMask->setVisible(false);
                this->removeChildByTag(2596);
                startGame();
                _eventDispatcher->removeEventListenersForTarget(btnMask);
            };
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, btnMask);
            addChild(btnMask,300,2598);
        }else {
            startGame();
        }

    }
    
    schedule(schedule_selector(PlayScene::onUpdate));
}

Sprite *act1,*act2;

void PlayScene::startGame() {
    act1->setVisible(true);
    isDripDead = false;
    
    act1->runAction(Sequence::create(ScaleTo::create(0.5, 1, 1),MoveTo::create(0.2, Vec2((SCREEN_WIDTH-act1->getContentSize().width)/2,SCREEN_HEIGHT+act1->getContentSize().height)),CallFunc::create([&]{
        act2->setVisible(true);
        act2->runAction(Sequence::create(ScaleTo::create(0.5, 1, 1),MoveTo::create(0.2, Vec2((SCREEN_WIDTH-act2->getContentSize().width)/2,SCREEN_HEIGHT+act2->getContentSize().height)),CallFunc::create([&]{
            flag = false;
            isGamePause = false;
            act1->setPosition(SCREEN_CENTER);
            act1->setScale(4);
            act1->setVisible(false);
            
            act2->setPosition(SCREEN_CENTER);
            act2->setScale(4);
            act2->setVisible(false);
            
        }), NULL));
    }), NULL));
}

cocos2d::ui::Button *btnReturnOfTheKing;

void PlayScene::initPopup() {
    isTimeOver = false;
    rankPop = RankingPop::create();
    rankPop->setPosition(SCREEN_CENTER);
    this->addChild(rankPop,2999);
    
    //复活弹窗
    
    popupReturnOfTheKing = PopupLayer::create("img_window_bg.png", 640, 374);
    popupReturnOfTheKing->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    popupReturnOfTheKing->setDelegate(this);
    popupReturnOfTheKing->setCloseButton("img_window_btn_close.png");
    popupReturnOfTheKing->setTitleImage("img_window_title4.png");
    
    //img_window_paper3.png
    auto bgReturnOfTheKing = Sprite::create("img_window_paper3.png");
    
    btnReturnOfTheKing = cocos2d::ui::Button::create("img_window_green.png");
    btnReturnOfTheKing->setTitleText("复活");
    btnReturnOfTheKing->setTitleColor(Color3B(12,63,10));
    btnReturnOfTheKing->setTitleFontSize(40);
    btnReturnOfTheKing->setPosition(Point(0,-250));
    btnReturnOfTheKing->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            if (CommonData::getInstance()->getCrystal() >= 2) {
                CommonData::getInstance()->addCrystal(-2);
                isDripDead = false;
                
                
                if(player->getPositionY() > line->getPositionY()) {
                    monster->enterBattle();
                    monster->setVictory(false);
                }
                
                player->setBlood(1);
                removeChildByTag(1920);
                player->setVisible(true);
                player->setInvincible(false);
                player->setIsDead(false);
                jishi->setVisible(false);
                isTimeOver = false;
                boxSpeed = itemDropTime(data->getBulletSpeed())*0.1;
                if(boxSpeed == 0) {
                    boxSpeed = 1;
                }
                
                if(level == 0) {
                    if(floor < 3) {
                        boxSpeed = itemDropTime(5)*0.1;
                    }
                    if(floor > 3) {
                        boxSpeed = itemDropTime(6)*0.1;
                    }
                    
                    
                    if (floor > 9) {
                        boxSpeed = itemDropTime(7)*0.1;
                    }
                    
                    if (floor > 16) {
                        boxSpeed = itemDropTime(8)*0.1;
                    }
                    
                    
                    if(floor >25) {
                        boxSpeed = itemDropTime(8+(floor-16)/10)*0.1;
                    }
                }
                
                for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end(); ++iter) {
                    Box *box = (*iter);
                    removeChild(box);
                    boxlist.remove(box);
                }
                dropBoxList = {};
                startGame();
                popupReturnOfTheKing->hide();
            } else {
                this->showTxtTip("对不起,您没有足够的水晶");
            }
        }
    });
    
    auto txtReturnOfTheKing = Text::create();
    txtReturnOfTheKing->setColor(Color3B(12, 30, 66));
    txtReturnOfTheKing->setString("消耗晶核两枚");
    txtReturnOfTheKing->setFontSize(35);
    txtReturnOfTheKing->setPosition(Vec2(0, -107));

    
    popupReturnOfTheKing->addChild(bgReturnOfTheKing);
    popupReturnOfTheKing->addChild(txtReturnOfTheKing);
    popupReturnOfTheKing->addChild(btnReturnOfTheKing);
    addChild(popupReturnOfTheKing,990);
    
    //无尽模式
    popupEndless = PopupLayer::create("img_window_bg.png", 640, 374);
    popupEndless->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    popupEndless->setDelegate(this);
    popupEndless->setCloseButton("img_window_btn_close.png");
    popupEndless->setTitleImage("img_window_title1.png");
    
    auto txtEndlessDes = Text::create();
    txtEndlessDes->setColor(Color3B(203, 73, 24));
    txtEndlessDes->setString("挑战失败");
    txtEndlessDes->setFontSize(35);
    txtEndlessDes->setPosition(Vec2(0, 55));
    
    txtEndlessBestScore =Text::create();
    txtEndlessBestScore->setColor(Color3B(203, 73, 24));
    txtEndlessBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
    txtEndlessBestScore->setFontSize(35);
    txtEndlessBestScore->setPosition(Vec2(0, -30));
    
    //    auto txtLoseRankDes = Text::create();
    //    txtLoseRankDes->setColor(Color3B(203, 73, 24));
    //    txtLoseRankDes->setString(LSTRING("Ranking"));
    //    txtLoseRankDes->setFontSize(40);
    //    txtLoseRankDes->setPosition(Vec2(0, -55));
    
    txtEndlessRank =Text::create();
    txtEndlessRank->setColor(Color3B(203, 73, 24));
    txtEndlessRank->setString(String::createWithFormat("...")->_string);
    txtEndlessRank->setFontSize(35);
    txtEndlessRank->setPosition(Vec2(0, -85));
    
    
    auto btnEndlessContinue=cocos2d::ui::Button::create("img_window_green.png");
    
    btnEndlessContinue->setPosition(Point(140,-250));
    
    btnEndlessContinue->setTitleText("继续挑战");
    btnEndlessContinue->setTitleColor(Color3B(12, 63, 10));
    btnEndlessContinue->setTitleFontSize(40);
    btnEndlessContinue->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            this->restartGame();
            Manager::getInstance()->resumeBackgroundMusic();
            popupEndless->hide();
        } else {
            
        }
    });
    
    auto btnEndlessRank=cocos2d::ui::Button::create("img_window_btn_red.png");
    
    btnEndlessRank->setPosition(Point(-140,-250));
    
    btnEndlessRank->setTitleText("查看排名");
    btnEndlessRank->setTitleColor(Color3B(255, 255, 255));
    btnEndlessRank->setTitleFontSize(40);
    btnEndlessRank->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            //查看排名
            //排行榜弹窗
            RankingPop::refreshData();
            rankPop->show();
        }
    });
    auto endlessBg = Sprite::create("img_window_paper.png");
    
//    auto txtEndlessContinue = Text::create();
//    txtEndlessContinue->setPosition(Vec2(132,44));
//    txtEndlessContinue->setString("继续挑战");
//    txtEndlessContinue->setFontSize(40);
//    txtEndlessContinue->setColor(Color3B(12, 63, 10));

    popupEndless->addChild(endlessBg);
    popupEndless->addChild(btnEndlessRank);
    popupEndless->addChild(txtEndlessBestScore);
    popupEndless->addChild(txtEndlessRank);
    popupEndless->addChild(txtEndlessDes);
    popupEndless->addChild(btnEndlessContinue);
    addChild(popupEndless, 995);
    
    
    //失败弹窗
    popupLose = PopupLayer::create("img_window_bg.png", 640, 374);
    popupLose->setTitleImage("img_window_title1.png");
    
//
    
    popupLose->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    popupLose->setCloseButton("img_window_btn_close.png");
    popupLose->setDelegate(this);


    auto restart =cocos2d::ui::Button::create("img_window_green.png");
    restart->setTitleText("重新开始");
    restart->setTitleColor(Color3B(12,63,10));
    restart->setTitleFontSize(40);
    restart->setPosition(Point(0,-250));
    restart->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            
            this->restartGame();
            popupLose->hide();
        }
    });
    
    auto loseHome =cocos2d::ui::Button::create("img_window_btn_red.png");
    loseHome->cocos2d::Node::setPosition(-140, -344);
    
    loseHome->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            //失败后返回首页
            Director::getInstance()->replaceScene(HomeScene::create());
        }
    });

    
    auto txtlosehome = Text::create();
    txtlosehome->setPosition(Vec2(132,44));
    txtlosehome->setString("主页");
    txtlosehome->setFontSize(40);
    txtlosehome->setColor(Color3B(255, 255, 255));
    loseHome->addChild(txtlosehome);
    
    auto iconLoseHome = Sprite::create("img_window_icon_home.png");
    iconLoseHome->setPosition(Vec2(68,44));
    loseHome->addChild(iconLoseHome);
    

    
    auto loseShop =cocos2d::ui::Button::create("img_window_green.png");

    loseShop->cocos2d::Node::setPosition(140, -344);
    loseShop->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            //失败后打开商店页
            Director::getInstance()->pushScene(ShopScene::create());
        }
    });
    
    
    auto txtLoseShop = Text::create();
    txtLoseShop->setPosition(Vec2(132,44));
    txtLoseShop->setString("商店");
    txtLoseShop->setFontSize(40);
    txtLoseShop->setColor(Color3B(12, 63, 10));
    loseShop->addChild(txtLoseShop);
    
    auto iconLoseShop = Sprite::create("img_window_icon_shop.png");
    iconLoseShop->setPosition(Vec2(68,44));
    loseShop->addChild(iconLoseShop);
    
    
    auto txtLoseDes = Text::create();
    txtLoseDes->setColor(Color3B(203, 73, 24));
    txtLoseDes->setString("闯关失败喽");
    txtLoseDes->setFontSize(35);
    txtLoseDes->setPosition(Vec2(0, 55));
    
    txtLoseBestScore =Text::create();
    txtLoseBestScore->setColor(Color3B(203, 73, 24));
    txtLoseBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
    txtLoseBestScore->setFontSize(35);
    txtLoseBestScore->setPosition(Vec2(0, -30));
    
    txtLoseRank =Text::create();
    txtLoseRank->setColor(Color3B(203, 73, 24));
    txtLoseRank->setString(String::createWithFormat("...")->_string);
    txtLoseRank->setFontSize(35);
    txtLoseRank->setPosition(Vec2(0, -85));
    
    
    auto loseBg = Sprite::create("img_window_paper.png");
    
    popupLose->addChild(loseBg);
    popupLose->addChild(loseHome);
    popupLose->addChild(txtLoseDes);
    popupLose->addChild(loseShop);
//    popupLose->addChild(txtLoseRankDes);
    popupLose->addChild(txtLoseRank);
    popupLose->addChild(txtLoseBestScore);
    
    popupLose->addChild(restart);
    addChild(popupLose,9999);
    
    //暂停弹窗
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
            
            if((level != 0 && level%5 != 0) || level == 50) {
               
                if(!isTimeOver) {
                    monster->resumeMoving();
                }
                
            }
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            startGame();
            Manager::getInstance()->resumeBackgroundMusic();
            popupPause->hide();
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
            if (level == 0) {
                Director::getInstance()->replaceScene(HomeScene::create());
            } else {
                Director::getInstance()->replaceScene(CheckpointScene::create());
            }
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

    addChild(popupPause, 503);
    

    popupWin = PopupLayer::create("img_window_bg.png", 640, 424);
    popupWin->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    popupWin->setCloseButton("img_window_btn_close.png");
    popupWin->setTitleImage("img_window_title1.png");
    
    txtWinfloor =Text::create();
    txtWinfloor->setColor(Color3B(203, 73, 24));
    txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
    txtWinfloor->setFontSize(35);
    txtWinfloor->setPosition(Vec2(0, -30));
    
    //    auto txtLoseRankDes = Text::create();
    //    txtLoseRankDes->setColor(Color3B(203, 73, 24));
    //    txtLoseRankDes->setString(LSTRING("Ranking"));
    //    txtLoseRankDes->setFontSize(40);
    //    txtLoseRankDes->setPosition(Vec2(0, -55));
    
    txtWinRank =Text::create();
    txtWinRank->setColor(Color3B(203, 73, 24));
    txtWinRank->setString("当前排名:...");
    txtWinRank->setFontSize(35);
    txtWinRank->setPosition(Vec2(0, -85));
    
    
    auto txtWinDes = Text::create();
    txtWinDes->setColor(Color3B(203, 73, 24));
    txtWinDes->setString("闯关成功");
    txtWinDes->setFontSize(35);
    txtWinDes->setPosition(Vec2(0, 55));
    
    auto winBg = Sprite::create("img_window_paper.png");
    
    auto nextLevel = cocos2d::ui::Button::create("img_window_green.png");
    nextLevel->setPosition(Vec2(-156, -280));
    nextLevel->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            Director::getInstance()->replaceScene(SkillSelectScene::createScene(level+1));
        }
    });
    
    nextLevel->setTitleFontSize(40);
    nextLevel->setTitleText("下一关");
    nextLevel->setTitleColor(Color3B(12, 63, 10));
    
    popupWin->setDelegate(this);

    popupWin->addChild(winBg);
    popupWin->addChild(txtWinDes);
    
    if(Manager::getInstance()->isQQInstalled()) {
        auto share = cocos2d::ui::Button::create("img_window_btn_red.png");
        
        share->setPosition(Vec2(156, -280));
        
        share->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
                Manager::getInstance()->playSoundEffect("btnPress.mp3");
                Manager::getInstance()->shareQQ();
            }
        });
        
        auto txtShare = Text::create();
        txtShare->setPosition(Vec2(132,44));
        txtShare->setString("分享");
        txtShare->setFontSize(40);
        txtShare->setColor(Color3B(255, 255, 255));
        
        auto iconShare = Sprite::create("img_window_icon_qq.png");
        iconShare->setPosition(Vec2(68,44));
        share->addChild(txtShare);
        share->addChild(iconShare);
        popupWin->addChild(share);
    } else {
        nextLevel->setPosition(Vec2(0, -280));
    }
    
    popupWin->addChild(txtWinfloor);
    popupWin->addChild(nextLevel);
    popupWin->addChild(txtWinRank);
    addChild(popupWin, 1007);
    
    //无尽模式胜利弹窗
    popupEndlessWin = PopupLayer::create("img_window_bg.png", 640, 374);
    popupEndlessWin->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    popupEndlessWin->setDelegate(this);
    popupEndlessWin->setCloseButton("img_window_btn_close.png");
    popupEndlessWin->setTitleImage("img_window_title1.png");
    
    auto txtEndlessWinDes = Text::create();
    txtEndlessWinDes->setColor(Color3B(203, 73, 24));
    txtEndlessWinDes->setString("恭喜您挑战成功,奖励晶核x1");
    txtEndlessWinDes->setFontSize(35);
    txtEndlessWinDes->setPosition(Vec2(0, 55));
    
    txtEndlessWinBestScore =Text::create();
    txtEndlessWinBestScore->setColor(Color3B(203, 73, 24));
    txtEndlessWinBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
    txtEndlessWinBestScore->setFontSize(35);
    txtEndlessWinBestScore->setPosition(Vec2(0, -30));
    
    
    txtEndlessWinRank =Text::create();
    txtEndlessWinRank->setColor(Color3B(203, 73, 24));
    txtEndlessWinRank->setString(String::createWithFormat("...")->_string);
    txtEndlessWinRank->setFontSize(35);
    txtEndlessWinRank->setPosition(Vec2(0, -85));
    
    
    auto btnEndlessWinRank=cocos2d::ui::Button::create("img_window_green.png");
    
    btnEndlessWinRank->setPosition(Point(140,-250));
    
    btnEndlessWinRank->setTitleText("查看排名");
    btnEndlessWinRank->setTitleColor(Color3B(12, 63, 10));
    btnEndlessWinRank->setTitleFontSize(40);
    btnEndlessWinRank->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            //排行榜弹窗
            RankingPop::refreshData();
            rankPop->show();
        }
    });
    
    

    auto endlessWinBg = Sprite::create("img_window_paper.png");
    
    popupEndlessWin->addChild(endlessWinBg);
    popupEndlessWin->addChild(btnEndlessWinRank);
    popupEndlessWin->addChild(txtEndlessWinBestScore);
    popupEndlessWin->addChild(txtEndlessWinRank);
    popupEndlessWin->addChild(txtEndlessWinDes);
    
    if(Manager::getInstance()->isQQInstalled()) {
        auto btnEndlessWinShare=cocos2d::ui::Button::create("img_window_btn_red.png");
        
        btnEndlessWinShare->setPosition(Point(-140,-250));
        
        btnEndlessWinShare->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
                Manager::getInstance()->playSoundEffect("btnPress.mp3");
                Manager::getInstance()->shareQQ();
            }
        });
        
        auto txtEndnessShare = Text::create();
        txtEndnessShare->setPosition(Vec2(132,44));
        txtEndnessShare->setString("分享");
        txtEndnessShare->setFontSize(40);
        txtEndnessShare->setColor(Color3B(255, 255, 255));
        
        auto iconEndnessShare = Sprite::create("img_window_icon_qq.png");
        iconEndnessShare->setPosition(Vec2(68,44));
        
        btnEndlessWinShare->addChild(iconEndnessShare);
        btnEndlessWinShare->addChild(txtEndnessShare);
        popupEndlessWin->addChild(btnEndlessWinShare);
    } else {
        //-140,-250
        btnEndlessWinRank->setPosition(Vec2(0,-250));
    }
    
    addChild(popupEndlessWin, 1009);
}

bool isTekken;
bool isShowBomb;
float bombTimer;
bool isShowBag;
bool isLaser;
bool isDoor;

cocos2d::ui::Button *frist, *second, *third, *fourth;

void PlayScene::initBtn() {
    isShowBomb = false;
    isShowBag = false;
    isLaser = false;
    flag = false;
    isDoor = false;
    propcd = PropCd::createSprite();
    
    tekken = Sprite::create("fist_send_1.png");
    tekken->setPosition(Vec2(-100,-100));
    addChild(tekken);
    
    
    act1 = Sprite::create("img_countdown_ready.png");
    act1->setPosition(SCREEN_CENTER);
    act1->setScale(4);
    addChild(act1);
    act1->setVisible(false);
    
    act2 = Sprite::create("img_countdown_go.png");
    act2->setPosition(SCREEN_CENTER);
    act2->setScale(4);
    this->addChild(act2);
    act2->cocos2d::Node::setVisible(false);
    
    //添加角色切换按钮
    auto btnSwitch = cocos2d::ui::Button::create("img_btn_change.png");
    btnSwitch->setOpacity(150);
    btnSwitch->setPosition(Point(44,576));
    
    btnSwitch->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            if(level == 4) {
                if(isGamePause) {
                    startGame();
                }
                this->removeChildByTag(2596);
                this->removeChildByTag(2597);
                this->removeChildByTag(2598);
                _eventDispatcher->removeEventListenersForTarget(getChildByTag(2199));
            }
            
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
        }
    });
    addChild(btnSwitch,6);
    
    //添加暂停按钮
    btnPause = cocos2d::ui::Button::create("img_btn_pause.png");
    btnPause->setPosition(Point(596,576));
    btnPause->setOpacity(150);
    addChild(btnPause,6);
    
    btnPause->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            flag = true;
            popupPause->show();
            act1->stopAllActions();
            act2->stopAllActions();
            
            auto actFunc=CallFuncN::create([&](Ref *pSender){
                if(level != 0 && level%5 != 0) {
                    monster->pauseMoving();
                }
                
                if(level == 50) {
                    monster->pauseMoving();
                }
                Manager::getInstance()->pauseBackgroundMusic();
            });
            this->runAction(Sequence::create(DelayTime::create(0.5), actFunc, NULL));
        }
    });
    
    
        laser = SLaserBulletArray::createLBlistByPlayer(BOX_SPEED, 1, Vec2(0,-1000), this);
        laser->setBoss(monster);
        addChild(laser,4);
        
        if (CommonData::getInstance()->getCheckpointSkill(1) != 0) {
            frist = cocos2d::ui::Button::create(StringUtils::format("img_prop%d.png",CommonData::getInstance()->getCheckpointSkill(1)).c_str());
            frist->setPosition(Point(80,60));
            frist->setLocalZOrder(100);
            frist->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
                if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
                    Manager::getInstance()->playSoundEffect("btnPress.mp3");
                    if (propcd->getTimer1() == 0) {
                        propcd->showTimer1();
                        this->skillBtnClick(1);
                    }
                }
            });
            
            addChild(frist);
        } else {
            frist = cocos2d::ui::Button::create("img_prop_blank.png");
            frist->setPosition(Point(80,60));
            frist->setLocalZOrder(100);
            addChild(frist);
        }
        
        
        if (CommonData::getInstance()->getCheckpointSkill(2) != 0) {
            second = cocos2d::ui::Button::create(StringUtils::format("img_prop%d.png",CommonData::getInstance()->getCheckpointSkill(2)).c_str());
            second->setPosition(Point(240,60));
            second->setLocalZOrder(100);
            second->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
                if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
                    Manager::getInstance()->playSoundEffect("btnPress.mp3");
                    if (propcd->getTimer2() == 0) {
                        propcd->showTimer2();
                        this->skillBtnClick(2);
                    }
                    
                }
            });
            
            addChild(second);
        } else {
            second = cocos2d::ui::Button::create("img_prop_blank.png");
            second->setPosition(Point(240,60));
            second->setLocalZOrder(100);
            addChild(second);
        }
        
        
        if (CommonData::getInstance()->getCheckpointSkill(3) != 0) {
            third = cocos2d::ui::Button::create(StringUtils::format("img_prop%d.png",CommonData::getInstance()->getCheckpointSkill(3)).c_str());
            third->setLocalZOrder(100);
            third->setPosition(Point(400,60));
            third->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
                if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
                    Manager::getInstance()->playSoundEffect("btnPress.mp3");
                    
                    if (propcd->getTimer3() == 0) {
                        propcd->showTimer3();
                        this->skillBtnClick(3);
                    }
                }
            });
            addChild(third);
        } else {
            third = cocos2d::ui::Button::create("img_prop_blank.png");
            third->setPosition(Point(400,60));
            third->setLocalZOrder(100);
            addChild(third);
        }
        
        
        if (CommonData::getInstance()->getCheckpointSkill(4) != 0) {
            fourth = cocos2d::ui::Button::create(StringUtils::format("img_prop%d.png",CommonData::getInstance()->getCheckpointSkill(4)).c_str());
            
            fourth->setPosition(Point(560,60));
            fourth->setLocalZOrder(100);
            fourth->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type) {
                if(type==cocos2d::ui::Widget::TouchEventType::ENDED) {
                    Manager::getInstance()->playSoundEffect("btnPress.mp3");
                    if (propcd->getTimer4() == 0) {
                        propcd->showTimer4();
                        this->skillBtnClick(4);
                    }
                }
            });
            addChild(fourth);
        } else {
            fourth = cocos2d::ui::Button::create("img_prop_blank.png");
            fourth->setPosition(Point(560,60));
            fourth->setLocalZOrder(100);
            addChild(fourth);
        }
    
    addChild(propcd,100);
}


void PlayScene::skillBtnClick(int count) {
    if(isGamePause) {
        return;
    }
    
    int type = CommonData::getInstance()->getCheckpointSkill(count);
    if (type == 5) {
        type += 1;
    }
    
    Vec2 pos;
    
    switch (count) {
        case 1:
            pos = Vec2(168,60);
            break;
        case 2:
            pos = Vec2(270,60);
            break;
        case 3:
            pos = Vec2(371,60);
            break;
        case 4:
            pos = Vec2(473,60);
            break;
        default:
            break;
    }
    
    switch (type) {
        case 1://金钟罩
            if (!player->getInvincible()) {
                if (setEnergy(pos, 10)) {
                    txtGoldPower->setString(NUM_TO_STR(goldEnergy));
                    txtGold->setString(NUM_TO_STR(myEnergy));
                    this->prop1();
                } else {
                    //showTxtTip("能量不足");
                }
            } else {
//                showTxtTip("你已经有金钟罩了");
            }
            
            break;
        case 2://大白铁拳
           
            if (CommonData::getInstance()->getRoleSkillLevel(2) == 4) {
                txtGold->setString(NUM_TO_STR(myEnergy));
                this->showGoldNumber(pos,":10");
                txtGold->setString(NUM_TO_STR(myEnergy));
                this->prop2();
            }else if (setEnergy(pos, 10)) {
                this->prop2();
            } else {
//                showTxtTip("能量不足");
            }
            
            break;
        case 3://时间减缓
            
            if (isTimeOver) {
                break;
            }
            if (setEnergy(pos, 10)) {
                this->prop3();
            }
            break;
        case 4://喷气背包
            
            if(player->getPositionY() > line->getPositionY()) {
                break;
            }
            
            if(level%5 != 0) {
                if (!monster->inCombat()) {
                    if (setEnergy(pos, 25)) {
                        
                        this->prop4();
                    } else {
                        //                showTxtTip("能量不足");
                    }
                }
            }
            
            
            
            break;
        case 5://追踪导弹 放弃
            
            break;
        case 6://伽吗射线
            if (isLaser) {
                break;
            }
            if (setEnergy(pos, 20)) {
                this->prop6();
            } else {
//                showTxtTip("能量不足");
            }
           
            break;
        case 7://饱和轰炸
            if (setEnergy(pos, 30)) {
                this->prop7();
            } else {
//                showTxtTip("能量不足");
            }
            break;
        case 8://次元门
            if(level%5 != 0) {
                if(!(level == 0 || monster->inCombat())) {
                    this->prop8();
                }
            }
            
            break;
        default:
            break;
    }
}

//enum RoleType
//{
//    BeymacType,             // 大白
//    LaserType,              // 激光
//    TomagoType,             // 神行姐
//};

bool PlayScene::setEnergy(Vec2 pos,int energy) {
    if (player->getRoleType() == RoleType::BeymacType) {
        switch (CommonData::getInstance()->getRoleLevel(1)) {
            case 1:
                energy *= 0.85;
                break;
            case 2:
                energy *= 0.75;
                break;
            case 3:
                energy *= 0.65;
                break;
            case 4:
                energy *= 0.5;
                break;
            default:
                break;
        }
    }
    
    
    if(myEnergy >= energy || myEnergy + goldEnergy >= energy) {
        
        this->showGoldNumber(pos, NUM_TO_STR(energy).c_str());
        if(myEnergy >= energy) {
            myEnergy -= energy;
        } else {
            goldEnergy = goldEnergy-(energy - myEnergy);
            CommonData::getInstance()->addEnergy(-(energy - myEnergy));
            myEnergy = 0;
        }
        
        txtGoldPower->setString(NUM_TO_STR(goldEnergy));
        txtGold->setString(NUM_TO_STR(myEnergy));
        return true;
    } else {
        return false;
    }
}

void PlayScene::showTxtTip(const char *str) {
    Text *txt = Text::create();
    txt->setString(str);
    txt->setTextColor(Color4B(131, 89, 6,255));
    
    txt->setFontSize(40);
    txt->setPosition(SCREEN_CENTER);
    auto bg = Sprite::create("img_get_gold_bg.png");
    bg->setTag(233);
    bg->setPosition(SCREEN_CENTER);
    addChild(bg,2300);
    
    ActionInterval * ai = FadeOut::create(1);
    auto action = Sequence::create(ai,CallFunc::create([&]{
        this->removeChild(txt);
        this->removeChild(getChildByTag(233));
    }),nullptr);
    this->addChild(txt,2300);
    txt->runAction(action);
}

//金钟罩
void PlayScene::prop1() {
    player->setInvincible(true);
    Manager::getInstance()->playSoundEffect("skill1.mp3");
}

float tekkenX, tekkenY;

//大白铁拳
void PlayScene::prop2() {
    isGamePause = true;
    LayerColor* layer = LayerColor::create(Color4B::BLACK);
    addChild(layer,159,199);
    Manager::getInstance()->playSoundEffect("skill2.mp3");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lead_fist_light.ExportJson");
    auto amt = Armature::create("lead_fist_light");
    amt->setPosition(player->getPositionX()-10, player->getPositionY()-player->getContentSize().height/2-20);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    this->addChild(amt,199);
    amt->getAnimation()->playWithIndex(0);
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
            if(getChildByTag(199)) {
                removeChildByTag(199);
            }
            isTekken = true;
            isGamePause = false;
        }
    });
    
}

float timerOver;

//时间减缓
void PlayScene::prop3() {
    
    if(((level != 0 && level%5 != 0) || level == 50) && CommonData::getInstance()->getRoleSkillLevel(3) == 4) {
        monster->pauseMoving();
    }
    
    if(level != 0) {
        laserBoss->setSlowDown(true);
        lb->setSlowDown(true);
    }
    
    isGamePause = true;
    Manager::getInstance()->playSoundEffect("skill3.mp3");
    
    timerOver = CommonData::getInstance()->getRoleSkillLevel(3)*2 + 4;
    
    
    if (CommonData::getInstance()->getRoleSkillLevel(3) == 4) {
        timerOver = 6;
    }
    
    if (CommonData::getInstance()->getRoleSkillLevel(3) == 3) {
        timerOver = 12;
    }
    removeChildByTag(1029);
    isGamePause = false;
    auto frame = Sprite::create("lead_ice_frame.png");
    frame->setPosition(SCREEN_CENTER);
    addChild(frame,5,1920);
    isTimeOver = true;
    timerTimeOver = 0;
    jishi->setVisible(true);
    jishi->setText("2");
    
    
}

//喷气背包
void PlayScene::prop4() {
    
    isShowBag = true;
    Manager::getInstance()->playSoundEffect("skill4.mp3");
    
}

//追踪导弹 放弃
void PlayScene::prop5() {
    prop6();
}

//伽马射线
void PlayScene::prop6() {
    isLaser = true;
    txtGold->setString(NUM_TO_STR(myEnergy));
    Manager::getInstance()->playSoundEffect("skill6.mp3");
    laser->playBombAction();
    laser->setBulletsPos(player->getPosition());
}

Armature *amt;

//饱和轰炸
void PlayScene::prop7() {
    
    Manager::getInstance()->playSoundEffect("skill7.mp3");
    isGamePause = true;
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lead_bomb.ExportJson");
    amt = Armature::create("lead_bomb");
    amt->setScale(2);
    amt->setPosition(Vec2(320, -200));
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    this->addChild(amt,299,2196);
    amt->getAnimation()->playWithIndex(0);
    
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
            if(level%5 != 0 || level == 50) {
                if(monster->inCombat()) {
                    if(CommonData::getInstance()->getRoleSkillLevel(3) != 4) {
                        monster->resumeMoving();
                    }
                    for (int i=0; i < monster->getBodyList().size(); i++) {
                        log("%d",CommonData::getInstance()->getRoleSkillLevel(7));
                        log("%f",this->attackPlus());
                        monster->getBodyList().at(i)->hit(CommonData::getInstance()->getRoleSkillLevel(7)*this->attackPlus());
                    }
                }
            }
            
            
            
            amt->getAnimation()->playWithIndex(1);
            amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
                this->removeChildByTag(2196);
                if(MovementEventType::COMPLETE==type){
                    amt->getAnimation()->playWithIndex(2);
                    
                    for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
                        Box *box = (*iter);
                        boxBangAction(box->getPositionX(),box->getPositionY());
                        removeChild(box);
                        iter = dropBoxList.erase(iter);
                        boxlist.remove(box);
                        continue;
                    }
                    isGamePause = false;
                    
                }
            });
        }
    });
    
    
}

//次元门
void PlayScene::prop8() {
    Manager::getInstance()->playSoundEffect("skill8.mp3");
    struct  timeval tv;
    gettimeofday(&tv,NULL);
    
    if(CommonData::getInstance()->getDoorNumber() < CommonData::getInstance()->getRoleSkillLevel(8)) {
        log("door :%d",CommonData::getInstance()->getRoleSkillLevel(8));
        log("num: %d",CommonData::getInstance()->getDoorNumber());
        isDoor = true;
        CommonData::getInstance()->addDoorNumber(1);
        CommonData::getInstance()->put("doorTimer", (int) tv.tv_sec);
    } else if(CommonData::getInstance()->get("doorTimer") == 0 || (tv.tv_sec - CommonData::getInstance()->get("doorTimer")) > CommonData::getInstance()->getRoleSkillLevel(8)*24/4*60*60) {
        if (!monster->inCombat() && level != 0) {
            isDoor = true;
            CommonData::getInstance()->put("doorTimer", (int) tv.tv_sec);
            CommonData::getInstance()->setDoorNumber(1);
        }
    } else {
        this->showTxtTip("对不起,技能还在冷却中");
    }
    
    
}

void PlayScene::showGoldNumber(Vec2 pos,const char *str) {
    
    auto gold = LabelAtlas::create(str, "img_reduce_power_number.png", 21, 28, '0');
    gold->setPosition(pos.x-gold->getContentSize().width/2, pos.y);
    addChild(gold,999);
    
    
    CallFunc * funcall= CallFuncN::create(std::bind(&PlayScene::removeActionChild, this,gold));
    ActionInterval * moveBy = MoveTo::create(1.5,Vec2(gold->getPositionX(), gold->getPositionY()+130));
    ActionInterval * fadeout = FadeOut::create(1.5);
    FiniteTimeAction * spawn = Spawn::create(moveBy,fadeout,NULL);
    FiniteTimeAction * seq = Sequence::create(spawn,funcall,NULL);
    gold->runAction(seq);
    
}

void PlayScene::showBomb(float x, float y) {
    Sprite *bomb = Sprite::create("img_action_bomb.png");
    bomb->setPosition(x,y);
    
    addChild(bomb);
    bomb->setScale(0.2, 0.2);
    auto spawn1 = Spawn::create(ScaleBy::create(0.4, 5),RotateBy::create(0.5, 360),FadeOut::create(0.5),nullptr);
//    auto spawn2 = Spawn::create(RotateBy::create(1, 360),,nullptr);
    auto action = Sequence::create(spawn1,CallFunc::create([&]{
        removeChild(bomb);
    }),nullptr);
    bomb->runAction(action);
}

void PlayScene::restartGame() {
    floor = 0;
    isDripDead = false;
    myEnergy = data->getStartEnergy();
    
    if(level == 0) myEnergy = 40;
    txtGold->setString(NUM_TO_STR(myEnergy));
    
    if (level != 0) {
        lb->setPosition(Vec2(0,SCREEN_HEIGHT+GRID_SIZE));
        if(level == 50 || level%5 != 0) {
            lb->setIsUpdate(false);
            amountOfEnergy = data->getAmountOfEnergy();
        }
        
    }
    
    removeChildByTag(1920);
    
    jishi->setVisible(false);
    isTimeOver = false;
    boxSpeed = itemDropTime(data->getBulletSpeed())*0.1;
    
    if(level == 0) {
        if(floor < 3) {
            boxSpeed = itemDropTime(5)*0.1;
        }
        if(floor > 3) {
            boxSpeed = itemDropTime(6)*0.1;
        }
        
        
        if (floor > 9) {
            boxSpeed = itemDropTime(7)*0.1;
        }
        
        if (floor > 16) {
            boxSpeed = itemDropTime(8)*0.1;
        }
        
        
        if(floor >25) {
            boxSpeed = itemDropTime(8+(floor-16)/10)*0.1;
        }
    }
    
    
    
    if(boxSpeed == 0) boxSpeed = 1.0;
    hammerTimer = 0;
    score->setString("0");
    Manager::getInstance()->playBackgroundMusic("playBGM.mp3");
    player->removeFollowers();
    removeChild(player);
    boxtype = normaltype;
    this->hideTips();
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *box = (*iter);
        removeChild(box);
    }
    
    for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end(); ++iter) {
        Box *box = (*iter);
        removeChild(box);
    }
    
    
    //添加水滴到舞台
    player = BeyMac::create();
    player->setPosition(SCREEN_CENTER);
    player->setPositionY(DEAD_LINE + player->getContentSize().height/2 );
    player->setTag(10000);
    player->setPlayScene(this);
    player->setDelegate(this);
    player->setBlood(1);
    
    amountOfEnergy = data->getAmountOfEnergy();
    
    if(level%5 == 0 && level % 10 != 0  && level != 50) {
        player->setBlood(2);
    }
    addChild(player);
    player->createfollowers();
    if (level == 50 || (level != 0 && level%5 != 0)) {
        line->setPosition(0,256+data->getFloor()*GRID_SIZE);
    }
    
    startGame();
    
    
    isBossBattle = false;
    isShowBoss = false;
    if (level == 50 || (level != 0 && level%5 !=0)) {
        monster->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT*2);
    }
    
    boxlist = {};
    dropBoxList = {};
    if((level%5 != 0 || level == 0) || level == 50) {
        playSceneState->enCurState = EnumState::dropReady;
    }
}


float PlayScene::getLevelSpeed() {
    boxSpeed = 1.0;
    if (level > 4) {
        boxSpeed = 1.0;
    }
    
    if (level > 13) {
        boxSpeed = 1.2;
    }
    
    if (level > 19) {
        boxSpeed = 1.3;
    }
    
    if (level > 25) {
        boxSpeed = 1.4;
    }
    
    if (level > 49) {
        boxSpeed = 1.5;
    }
    
    return boxSpeed;
}


void PlayScene::readBossBattle() {
    if (level != 0) {
        if (isShowBag == false && player->getPositionY() > line->getPositionY() && player->getIsOnGround()) {
            
            Manager::getInstance()->playBackgroundMusic("bossBGM.mp3");
            this->overLine();
        }
    } else {

        if (floor > 5 && floor< 20) {
            this->boxSpeed = 1.1;
        }
        
        if (floor > 20&& floor < 40) {
            this->boxSpeed = 1.2;
        }
        
        if (floor < 60 &&floor > 40) {
            this->boxSpeed = 1.3;
        }
        
        if (floor < 80 &&floor > 60) {
            this->boxSpeed = 1.4;
        }
        
        if (floor < 100 &&floor > 80) {
            this->boxSpeed = 1.5;
        }
        
        if (floor < 120 &&floor > 100) {
            this->boxSpeed = 1.6;
        }
    }
}

int rankType;

//1 普通模式胜利
//2 普通模式胜利,但是用户玩过
//3 普通模式失败
//4 无尽模式结束

void PlayScene::onUnlimitedRankGot(int rank) {
    txtEndlessWinRank->setString(String::createWithFormat("当前排名:%d",rank)->_string);
    txtEndlessRank->setString(String::createWithFormat("当前排名:%d",rank)->_string);
}

void PlayScene::onNormalRankGot(int rank) {
    
    
    if (rankType == 1) {
        auto popupWinReward = (PopupWinReward*) getChildByTag(777);
        popupWinReward->setRank(rank);
    }
    
    switch (rankType) {
        
        case 2:
            txtWinRank->setString(String::createWithFormat("最高排名:%d",rank)->_string);
            break;
        case 3:
            txtLoseRank->setString(String::createWithFormat("最高排名:%d",rank)->_string);

            break;
        default:
            break;
    }
}

void PlayScene::hammerEnd() {
    CommonData::getInstance()->put(level, 1);
    // 1 - 8 道具奖励
    // 9 1钻石奖励
    // 10 无奖励
    // 11 12 奖励角色
    
    auto popupWinReward = PopupWinReward::createNode(9,hammerTimer/10);
    popupWinReward->setDelegate(this);
    popupWinReward->setPosition(0,0);
    popupWinReward->setFloor(floor);
    popupWinReward->setTag(777);
    ws->getNormalRank(floor);
    addChild(popupWinReward,998);
    
}

bool isMystery = true;

//刷新
void PlayScene::onUpdate(float delta) {
    
    if(flag) {
        return;
    }
    
    if (!isGamePause) {
        
        itemEnable(delta);

        if (level%10 == 0 && level != 0 && level != 50) {
            
            hammerTimer += delta;
            int show = hammerTimer;
            timer->setString(String::createWithFormat("%d",40-show)->_string);
            if (hammerTimer > 40) {
                isGamePause = true;
                
                if (CommonData::getInstance()->get(level) == CHECKPOINT_PLAYED) {
                    rankType = 2;
                    ws->getNormalRank(floor);
                    txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
                    popupWin->show();
                } else {
                    CommonData::getInstance()->put(level, 1);
                    // 1 - 8 道具奖励
                    // 9 1钻石奖励
                    // 10 无奖励
                    // 11 12 奖励角色
                    
                    auto popupWinReward = PopupWinReward::createNode(9,hammerTimer/10);
                    popupWinReward->setDelegate(this);
                    popupWinReward->setPosition(0,0);
                    popupWinReward->setFloor(floor);
                    popupWinReward->setTag(777);
                    ws->getNormalRank(floor);
                    addChild(popupWinReward,998);
                }
                
            }
        } else if(level%5 == 0 && level%10 != 0 && level != 0  && level != 50) {
            hammerTimer += delta;
            int show = hammerTimer;
            timer->setString(String::createWithFormat("%d",40-show)->_string);
            if (hammerTimer > 40) {
                isGamePause = true;
                if (CommonData::getInstance()->get(level) == CHECKPOINT_PLAYED) {
                    rankType = 2;
                    ws->getNormalRank(floor);
                    txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
                    popupWin->show();
                } else {
                    CommonData::getInstance()->put(level, 1);
                    // 1 - 8 道具奖励
                    // 9 1钻石奖励
                    // 10 无奖励
                    // 11 12 奖励角色
                    
                    auto popupWinReward = PopupWinReward::createNode(9,hammerTimer/10);
                    popupWinReward->setDelegate(this);
                    popupWinReward->setPosition(0,0);
                    popupWinReward->setFloor(floor);
                    popupWinReward->setTag(777);
                    ws->getNormalRank(floor);
                    addChild(popupWinReward,998);
                }
            }
            
        } else {
            //普通游戏逻辑
            destroyBox();
            playSceneState->execute(delta);
            
            if (level != 0) {
                if(!(isTimeOver && CommonData::getInstance()->getRoleSkillLevel(3) == 4)) {
                    laserBoss->onUpdate(delta, &boxlist, player);
                }
                
            }
        }
        
        if(level != 0) {
            if(!(isTimeOver && CommonData::getInstance()->getRoleSkillLevel(3) == 4)) {
                lb->onUpdate(delta, player);
            }
        }
        
        player->onUpdate(delta,&boxlist);
        health->setValue(player->getBlood()*33);
        
        propcd->onUpdate(delta);
        
        
        if(!isGamePause) {
            this->monitoringItem(delta);
        }

    }
}

int PlayScene::getItemPrice(int num) {
    
    int price = 0;
    
    if (num <= 3) {
        price =  10;
    }
    
    if (num == 4) {
        price = 25;
    }
    
    if (num == 7 || num == 6) {
        price = 20;
    }
    
    if (num == 8) {
        price = 0;
    }
    
    
    if (player->getRoleType() == RoleType::BeymacType) {
        switch (CommonData::getInstance()->getRoleLevel(1)) {
            case 1:
                price *= 0.85;
                break;
            case 2:
                price *= 0.75;
                break;
            case 3:
                price *= 0.65;
                break;
            case 4:
                price *= 0.5;
                break;
            default:
                break;
        }
    }
    
    return price;
}

void PlayScene::itemEnable(float delta) {
    if (!(level%5 == 0 && level%10 != 0)  && level != 50)  {
        
        if (this->getItemPrice(CommonData::getInstance()->getCheckpointSkill(1)) > myEnergy+goldEnergy) {
            frist->setEnabled(false);
            frist->setColor(Color3B::GRAY);
        } else {
            frist->setEnabled(true);
            frist->setColor(Color3B::WHITE);
        }
        
        if (this->getItemPrice(CommonData::getInstance()->getCheckpointSkill(2)) > myEnergy+goldEnergy) {
            second->setEnabled(false);
            second->setColor(Color3B::GRAY);
            
        } else {
            second->setEnabled(true);
            second->setColor(Color3B::WHITE);
        }
        
        if (this->getItemPrice(CommonData::getInstance()->getCheckpointSkill(3)) > myEnergy+goldEnergy) {
            third->setEnabled(false);
            third->setColor(Color3B::GRAY);
            
        } else {
            third->setEnabled(true);
            third->setColor(Color3B::WHITE);
        }
        
        if (this->getItemPrice(CommonData::getInstance()->getCheckpointSkill(4)) > myEnergy+goldEnergy) {
            fourth->setEnabled(false);
            fourth->setColor(Color3B::GRAY);
            
        } else {
            fourth->setEnabled(true);
            fourth->setColor(Color3B::WHITE);
        }
    }
}

float PlayScene::attackPlus() {
    float a = 1;
    if(player->getRoleType() == RoleType::LaserType) {
        switch (CommonData::getInstance()->getRoleLevel(2)) {
            case 1:
                a += 0.5;
                break;
            case 2:
                a += 0.8;
                break;
            case 3:
                a += 1.1;
                break;
            case 4:
                a += 1.5;
                break;
            default:
                break;
        }
    }
    return a;
}

void PlayScene::monitoringItem(float delta) {
    
    if(player->getInvincible()) {
        jishi->setVisible(true);
        jishi->setText(NUM_TO_STR((int) player->getInvincibleLastTime()));
        if (player->getInvincibleLastTime() < 1) {
            jishi->setVisible(false);
        }
    }
    
    if(level%5 != 0 || level == 50) {
        if(!isGamePause) {
            
            if (monster->inCombat()) {
                for (int i=0; i < monster->getBodyList().size(); i++) {
                    
                    if (fabs((tekken->getPositionY() - monster->getBodyList().at(i)->getPosition().y)) < GRID_SIZE && fabs((tekken->getPositionX() - monster->getBodyList().at(i)->getPosition().x)) < GRID_SIZE ) {
                        int tekenPower = CommonData::getInstance()->getRoleSkillLevel(2);
                        if(tekenPower > 3) {
                            tekenPower = 3;
                        }
                        monster->getBodyList().at(i)->hit(attackPlus()*tekenPower*player->getMaxAttack());
                        tekken->stopAllActions();
                        tekken->setPosition(Vec2(-500,-500));
                    }
                }
            }
        }
    }
    
    
    //雨伞道具管控
    if (isStartUmbrella) {
        timerUmbrella += delta;
    }
    
    if (timerUmbrella > 2) {
        player->setUmbrella(false);
        isStartUmbrella = false;
        timerUmbrella = 0;
    }
    
    //时间暂停道具管控
    if (isTimeOver) {

        timerTimeOver += delta;
        int num = timerTimeOver;
        jishi->setVisible(true);
        jishi->setText(NUM_TO_STR(timerOver-num));
        if(level != 0) {
            
            switch (CommonData::getInstance()->getRoleSkillLevel(3)) {
                case 1:
                    boxSpeed = itemDropTime(data->getBulletSpeed())*0.1 * 0.3;
                    break;
                case 2:
                    boxSpeed = itemDropTime(data->getBulletSpeed())*0.1 * 0.5;
                    break;
                case 3:
                    boxSpeed = itemDropTime(data->getBulletSpeed())*0.1 * 0.5;
                    break;
                case 4:
                    boxSpeed = 0;
                    break;
                default:
                    break;
            }
            
        } else {
            
                if(floor < 3) {
                    boxSpeed = itemDropTime(5)*0.1;
                }
                if(floor > 3) {
                    boxSpeed = itemDropTime(6)*0.1;
                }
                
                
                if (floor > 9) {
                    boxSpeed = itemDropTime(7)*0.1;
                }
                
                if (floor > 16) {
                    boxSpeed = itemDropTime(8)*0.1;
                }
                
                
                if(floor >25) {
                    boxSpeed = itemDropTime(8+(floor-16)/10)*0.1;
                }
            if(CommonData::getInstance()->getRoleSkillLevel(3) == 1) {
                boxSpeed *= 0.3;
            } else {
                boxSpeed *= 0.5;
            }
            
        }
        
        
        if(CommonData::getInstance()->getRoleSkillLevel(3) == 4) {
            boxSpeed = 0;
        }
        
        if (timerTimeOver > timerOver) {
            jishi->setVisible(false);
            isTimeOver = false;
            if(level != 0) {
                laserBoss->setSlowDown(false);
                lb->setSlowDown(false);
            }
            removeChildByTag(1920);
            if((level != 0 && level%5 != 0) || level == 50) {
                monster->resumeMoving();
            }
            
            
            if(level != 0) {
                boxSpeed = itemDropTime(data->getBulletSpeed())*0.1;
            } else {
                if(level == 0) {
                    if(floor < 3) {
                        boxSpeed = itemDropTime(5)*0.1;
                    }
                    if(floor > 3) {
                        boxSpeed = itemDropTime(6)*0.1;
                    }
                    
                    
                    if (floor > 9) {
                        boxSpeed = itemDropTime(7)*0.1;
                    }
                    
                    if (floor > 16) {
                        boxSpeed = itemDropTime(8)*0.1;
                    }
                    
                    
                    if(floor >25) {
                        boxSpeed = itemDropTime(8+(floor-16)/10)*0.1;
                    }
                }
            }
        }
    }
    
    if (isTekken) {
        isTekken = false;
        tekken->setPosition(player->getPosition());
        ActionInterval * moveTo = MoveTo::create(1.5,Vec2(player->getPositionX(), SCREEN_HEIGHT+tekken->getContentSize().width));
        auto action = Sequence::create(moveTo,CallFunc::create([&]{
            tekken->setPosition(Vec2(-500,-500));
        }),nullptr);
        tekken->runAction(action);
    }
    
    
    
    if (isShowBag) {
        isGamePause = true;
        hideTips();
        for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *box = (*iter);
            iter = dropBoxList.erase(iter);
            boxlist.remove(box);
            removeChild(box);
            continue;
        }
        dropBoxList = {};
        
        
        player->takeBag(true);
        
    }
    
    
    if (isDoor) {
        isDoor = false;
        
        isGamePause = true;
        
        //8  12  16
        LayerColor* layer = LayerColor::create(Color4B(8, 12, 16,255));
        addChild(layer,198,189);
        
        auto door = Sprite::create("lead_door_1.jpg");
        door->setPosition(SCREEN_CENTER);
        door->setScale(2, 2);
        addChild(door,199,1031);
        
        Animation* animation = Animation::create();
        for (int i=1; i<=14; i++)
        {
            __String* image = __String::createWithFormat("lead_door_%i.jpg", i);
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(image->getCString());
            Rect rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
            animation->addSpriteFrame(frame);
        }
        animation->setDelayPerUnit(0.15);
        Animate* animate = Animate::create(animation);
        Repeat* repeat = Repeat::create(animate,2);
        door->runAction(Sequence::create(repeat,CallFunc::create([&]{
            isGamePause = false;
            removeChildByTag(1031);
            removeChildByTag(189);
        }),NULL));
        
        
        
        auto move = MoveTo::create(2, Vec2(320, 568));

        player->runAction(Sequence::create(move,CallFunc::create([=](){
            //这里是事件
            door->setLocalZOrder(299);
        }), NULL));
        
        
        int up = (line->getPositionY()-player->getPositionY())/GRID_SIZE + 1;
        hideTips();
        for (int i = 0; i<8; i++) {
            Box *b = Box::createMyBox(normaltype);
            b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, deadline+up*GRID_SIZE-GRID_RADIUS_SIZE);
            b->track = i+1;
            b->isDead = true;
            b->targetPositionY = deadline+up*GRID_SIZE-GRID_RADIUS_SIZE;
            b->setOpacity(0);
            
            addChild(b);
            
            ActionInterval *in = FadeIn::create(0.5);
            b->runAction(in);
            boxlist.push_back(b);
        }
        
        
        for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end(); ++iter) {
            Box *box = (*iter);
            this->boxRemoveAction(box);
            boxlist.remove(box);
            removeChild(box);
        }
        dropBoxList = {};
        moveAllBox(up);
    }
}

void PlayScene::overLine() {
    
    log("过线");
    
    for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end(); ++iter) {
        Box *box = (*iter);
        this->boxRemoveAction(box);
        boxlist.remove(box);
        removeChild(box);
    }
    
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end();) {
        Box *box = (*iter);
        if (box->getPositionY() > line->getPositionY()) {
            boxRemoveAction(box);
            removeChild(box);
            iter = boxlist.erase(iter);
            continue;
        }
        ++iter;
    }
    
    for (int i = 0; i<8; i++) {
        Box *b = Box::createMyBox(normaltype);
        b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, line->getPositionY()-GRID_RADIUS_SIZE);
        b->track = i+1;
        b->isDead = true;
        b->targetPositionY = line->getPositionY()-GRID_RADIUS_SIZE;
        b->setOpacity(0);
        
        
        addChild(b);
        
        ActionInterval *in = FadeIn::create(0.5);
        b->runAction(in);
        boxlist.push_back(b);
        
    }
    
    hideTips();
    dropBoxList = {};
    isShowBoss = true;
    playSceneState->enCurState = EnumState::battleReady;
    moveAllBoxTo(line->getPositionY()-deadline);
}

void PlayScene::showBosss() {
    log("show boss");

    monster->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/1.5);
    
    playSceneState->enCurState = EnumState::battleStart;
}

void PlayScene::showBox(Box *box) {
    
}

void PlayScene::showTips() {
    log("show tips");
    
    ran = arc4random()%100;
    
    if (boxtype == BoxType::sunbox && ran >82 && ran <= 95) {
        ran = 15;
    }
    
    if (boxtype == BoxType::dustbox && ran >67 && ran <= 82) {
        ran = 15;
    }
    
    if (boxtype == BoxType::dripbox && ran >95 && ran <= 100) {
        ran = 15;
    }
    
    
    if(ran <= 45) { //普通箱子
        log("普通箱子");
        boxtype  = normaltype;
    } else if(ran > 45 && ran <= 67) { //冰雹
        log("冰雹");
        boxtype  = hailbox;
    } else if(ran > 67 && ran <= 82) { //沼泽
        log("阳光");
        boxtype  = dustbox;
    } else if(ran > 82 && ran <= 95) { //炸弹
        log("灰尘");
        boxtype  = sunbox;
    } else if(ran > 95 && ran < 100){               //水滴
        log("水滴");
        boxtype  = dripbox;
    }
    
    if (boxtype != BoxType::powerBall) {
        if(level != 0) {
            //1
            if(amountOfEnergy>0 && floor > (data->getFloor()/data->getAmountOfEnergy()) * (data->getAmountOfEnergy() - amountOfEnergy)) {
                log("1: %d",data->getFloor()/data->getAmountOfEnergy());
                log("getAe: %d",data->getAmountOfEnergy());
                log("all: %d",(data->getFloor()/data->getAmountOfEnergy()) * (data->getAmountOfEnergy() - amountOfEnergy));
                log("amountOfEnergy: %d",amountOfEnergy);
                boxtype = BoxType::powerBall;
                amountOfEnergy--;
                while(floor > (data->getFloor()/data->getAmountOfEnergy()) * (data->getAmountOfEnergy() - amountOfEnergy)) {
                    amountOfEnergy--;
                }
                log("amountOfEnergy: %d",amountOfEnergy);
            }
        }
    }
    
    
    
    
    if (level%5 ==0 && level != 0 && level %10 != 0  && level != 50) {
        boxtype = BoxType::normalbox;
    }
    
    

    for (int i = 0; i<5; i++) {
        track[i] = arc4random()%9;
        log("down track:-- %d",track[i]);
        isDrop = true;
        
        //设置轨道
        if(isForcedDown) {
            log("越界了");
            for (int s=1; s<9; s++) {
                
                if(emptyTrack[s] == 0) {
                    log("空轨道: %d",s);
                    track[i] = s;
                    emptyTrack[s] = 1;
                    break;
                }
            }
        }
    }
    
    int sum = 0;
    int temp[8] = {0,0,0,0,0,0,0,0};
    for (int i = 0; i<5; i++) {
        if (track[i] == 0) {
            sum++;
        } else {
            temp[track[i]-1] = 1;
        }
    }
    
    int put = abs(sum - 2);
    log("put: %d",put);
    if (sum > 3) {
        for (int i = 0; i<put; i++) {
            if (track[i] == 0) {
                for (int j=0; j<8; j++) {
                    if (temp[j] == 0) {
                        track[i] = j+1;
                        temp[j] = 0;
                        break;
                    }
                }
            }
        }
    }
    
    //去掉相同的轨道
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            if (track[i] == track[j] && i != j) {
                track[j] = 0;
            }
        }
    }
    
    
    for (int i= 0; i<5; i++) {
        log("第%d个 - %d",i,track[i]);
    }
    
    
    
    for (int i = 0; i<5; i++) {
        //如果轨道没有箱子, 则不进行提醒
        if(track[i] != 0) {
            if (boxtype == BoxType::dripbox) {
                log("dripbox!");
                dripTip->cocos2d::Node::setPosition((track[i]-1)*GRID_SIZE+GRID_SIZE/2, SCREEN_HEIGHT-(dripTip->getContentSize().height)+dripTip->getContentSize().height/2);
                dripTip->setVisible(true);
                dripTip->setTip(boxtype);
                break;
            } else {
                tips[(track[i]-1)]->setVisible(true);
                tips[(track[i]-1)]->setTip(boxtype);
            }
            
            if (boxtype == BoxType::sunbox && i>=1) {
                tips[(track[i]-1)]->setVisible(false);
            }
            
            if (boxtype == BoxType::powerBall) {
                dripTip->cocos2d::Node::setPosition((track[i]-1)*GRID_SIZE+GRID_SIZE/2, SCREEN_HEIGHT-(dripTip->getContentSize().height)+dripTip->getContentSize().height/2);
                dripTip->setVisible(true);
                dripTip->setTip(boxtype);
                break;
            }
        }
    }
    
//    //保证最低落下一个箱子
//    int sum;
//    for (int i = 0; i<5; i++) {
//        if (track[i]==0) {
//            sum ++;
//        }
//    }

//    if (sum == 5) {
//        log("随机空");
//        track[1] = 1;
//    }

    isShowTips = false;    //关闭轨道设置
    playSceneState->enCurState = EnumState::drop;
    isDrop = true;         //打开箱子下落业务
}

//隐藏提示
void PlayScene::hideTips() {
    for (int i = 0; i< 8; i++) {
        tips[i]->setVisible(false);
    }
    
    dripTip->setVisible(false);
}

//放下新的箱子列
void PlayScene::dropdownBox(float delta) {
    
    log("drop");
        hideTips();
        Manager::getInstance()->playSoundEffect("dorpbox.mp3");
        for (int i = 0; i < 5; i++) {
            
            if(track[i] != 0) {
                isDrop = false;
                if(level%5 ==0 && level != 0 && level%10 != 0  && level != 50) {
                    boxtype = BoxType::normalbox;
                }
                Box *box = Box::createMyBox(boxtype);
                
                int type = track[i]-1;
                box->setPosition(type*GRID_SIZE+GRID_SIZE/2, SCREEN_HEIGHT-GRID_SIZE+GRID_SIZE/2);
                box->track = track[i];
                box->targetPositionY = deadline+GRID_RADIUS_SIZE;
                
                //循环查找同轨道下最高的箱子
                for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
                    Box *b = (*iter);
                    
                    if(box->track == b->track && b->targetPositionY > deadline) { // 必须是同轨道才考虑计坐标
                        if (box->targetPositionY <= b->targetPositionY ) { //同轨道且大于需要下落箱子的目标坐标, 才会覆盖目标坐标
                            log("%f",deadline);
                            log("b ----- targetPositionY:%f, track : %d", b->targetPositionY,b->track);
                            if (b->type == BoxType::dripbox || b->type == BoxType::powerBall) {
                                box->targetPositionY = b->targetPositionY;
                            } else {
                                box->targetPositionY = b->targetPositionY+GRID_SIZE;
                            }
                        }
                    }
                }
//                log("----- targetPositionY:%f, track : %d", box->targetPositionY,box->track);
                dropBoxList.push_back(box);
                boxlist.push_back(box);
                addChild(box);
                
                if(box->type == BoxType::dripbox) {
                    break;
                }
                
                if (box->type == BoxType::sunbox && i >= 1) {
                    break;
                }
                
                if(box->type == BoxType::powerBall) {
                    break;
                }
            }
        }
//        hideTips();
        playSceneState->enCurState = EnumState::dropOver;
    
    isShowTips = true;
}

// 检查空轨道
void PlayScene::checkEmptyTrack() {
    log("checkEmptyTrack");
    if(isForcedDown) {
        for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
            Box *b = (*iter);
            if(b->type != BoxType::powerBall && b->type != BoxType::dripbox && b->getPositionY() > deadline && b->type != BoxType::sunbox && b->type != BoxType::dustbox) {
                emptyTrack[b->track] = 1;
            } else {
                log("有空轨道 - %d",b->track);
                emptyTrack[b->track] = 0;
            }
            
        }
    }
}

//检测是否要移动整个箱子阵列
void PlayScene::detectionOfFullLine() {
    log("检测是否要移动整个箱子阵列");
    int bottomNumber = 0;           //最下面一行的箱子数
    isDetectionBox = false;
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
        Box *b = (*iter);
        
        if(b->type != BoxType::powerBall && b->type != BoxType::dripbox && b->getPositionY() > deadline + GRID_SIZE*2) {
            log("超过3层啦, 快填充空轨道");
            isForcedDown = true; // 打开空列下落业务
        }
        
        if(b->type != BoxType::powerBall && b->type != BoxType::dripbox && b->getPositionY() < deadline+GRID_SIZE && b->getPositionY() > deadline) {
            bottomNumber++;
        }
        
        ++iter;
    }
    
    if(bottomNumber == 8) {  //如果有8个一排, 则下落整个矩阵
        this->moveAllBox();
        playSceneState->enCurState = EnumState::dropReady;
    } else {
        playSceneState->enCurState = EnumState::dropReady;        
    }
    

    bottomNumber = 0;
}

//移动全部的箱子
void PlayScene::moveAllBox() {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *b = (*iter);
        
//        if(b->getPositionY()<0) {
//            iter = boxlist.erase(iter);
//            removeChild(b);
//            continue;
//        }
        
        
        b->targetPositionY -=  GRID_SIZE; //重设箱子的目标矩阵
        
        //播下落一格的动画
        ActionInterval * moveTo = MoveTo::create(0.2,Vec2(b->getPositionX(),b->targetPositionY));
        b->runAction(moveTo);
        if(b->getPositionY() < deadline-GRID_SIZE) {
            b->type = sinkbox;
        }
    }
    
    if (level == 50 || (level != 0 && level%5 != 0)) {
        ActionInterval *lineMoveTo = MoveTo::create(0.2,Vec2(0,line->getPositionY()-GRID_SIZE));
        line->runAction(lineMoveTo);
    }
    
    floor++;
    score->setString(String::createWithFormat("%d",floor)->_string);
    if(floor >= finalFloor) {
        this->finash();
    }
}

void PlayScene::moveAllBox(int targetFloor) {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *b = (*iter);
        b->targetPositionY -=  GRID_SIZE*targetFloor; //重设箱子的目标矩阵
        
        //播下落一格的动画
        ActionInterval * moveTo = MoveTo::create(1,Vec2(b->getPositionX(),b->targetPositionY));
        b->runAction(moveTo);
        if(b->getPositionY() < deadline-GRID_SIZE) {
            b->type = sinkbox;
        }
    }
    
    if (level != 0) {
        ActionInterval *lineMoveTo = MoveTo::create(1,Vec2(0,line->getPositionY()-GRID_SIZE*targetFloor));
        line->runAction(lineMoveTo);
    }
    
    floor += targetFloor;
    score->setString(String::createWithFormat("%d",floor)->_string);
    if(floor >= finalFloor) {
        this->finash();
    }
}

//移动全部的箱子
void PlayScene::moveAllBoxTo(float _y) {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ++iter) {
        Box *b = (*iter);
        b->targetPositionY -=  _y; //重设箱子的目标矩阵
        
        //播下落一格的动画
        ActionInterval * moveTo = MoveTo::create(_y/GRID_SIZE,Vec2(b->getPositionX(),b->targetPositionY));
        b->runAction(moveTo);
    }
    
    if (level != 0) {
        ActionInterval *lineMoveTo = MoveTo::create(_y/GRID_SIZE,Vec2(0,line->getPositionY()-_y*GRID_SIZE));
        line->runAction(Sequence::create(lineMoveTo, CallFunc::create([&]{
            monster->enterBattle();
        }),NULL));
    }
}


//移除非法的箱子
void PlayScene::killBox() {
    boxlist.remove_if(
        [this](Box *b){
            if(b->getPositionY()<-1*GRID_SIZE) { // 如果箱子超过屏幕下边缘,则销毁箱子
                removeChild(b);return true;} return false;
        }
    );
}

void PlayScene::destroyBox() {
    for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
        Box *b = (*iter);
        if(b->isDestroy) {
            boxRemoveAction(b);
            iter = boxlist.erase(iter);
            removeChild(b);
            
            
            if (!b->isDead) {
                dropBoxList.remove(b);
            }
            
            continue;
        }
        ++iter;
    }
}

//移动箱子
void PlayScene::moveBox() {
    
    int removeDripTrack = 0; //移除这一列所有的水滴
        
        for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *b = (*iter);
            
            if (b->getPositionY() < tekken->getPositionY() + 100) {
                if (b->getPositionX()+GRID_SIZE > tekken->getPositionX() && b->getPositionX()-GRID_SIZE < tekken->getPositionX()) {
                    
                    boxBangAction(b->getPositionX(),b->getPositionY());
                    removeChild(b);
                    boxlist.remove(b);
                    iter = dropBoxList.erase(iter);
                    
                    ArmatureDataManager::getInstance()->addArmatureFileInfo("lead_fist_send.ExportJson");
                    auto amt = Armature::create("lead_fist_send");
                    amt->setPosition(tekken->getPositionX(),tekken->getPositionY()-243);
                    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
                    for(int i=0;i<animationCount;i++){
                        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
                        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
                    }
                    this->addChild(amt,99);
                    amt->getAnimation()->playWithIndex(0);
                    
                    tekken->stopAllActions();
                    tekken->setPosition(Vec2(-500,-500));
                    
                    continue;
                }
            }
            iter++;
        }
    
        if (isLaser) {
                isLaser = false;
            for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
                Box *box = (*iter);
                if(CommonData::getInstance()->getRoleSkillLevel(6)>1) {
                    if (box->track == player->getMyRow()+1 || box->track == player->getMyRow()-1 || box->track == player->getMyRow()) {
                        boxBangAction(box->getPositionX(),box->getPositionY());
                        removeChild(box);
                        iter = dropBoxList.erase(iter);
                        boxlist.remove(box);
                        continue;
                    } else {
                        iter++;
                    }
                } else {
                    if (box->track == player->getMyRow()) {
                        boxBangAction(box->getPositionX(),box->getPositionY());
                        removeChild(box);
                        iter = dropBoxList.erase(iter);
                        boxlist.remove(box);
                        continue;
                    } else {
                        iter++;
                    }
                }
            }
        }
    
        for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *box = (*iter);
            if (box) {
                if(!box->isDead) { // 箱子不能是静止状态
                    if((box->getPositionY() - box->targetPositionY ) <= BOX_SPEED * boxSpeed) {  // 如果下落的箱子,距离下落目标的距离低于移动速度, 就直接到下落目标的坐标
                        //log("最后一步小于速度,直接到目标坐标 %f, track :%d",box->targetPositionY,box->track);
                        box->setPositionY(box->targetPositionY);
                        if (topPos < box->getPositionY()) {
                            topPos = box->getPositionY();
                        }
                        
                        if (box->type != BoxType::dripbox || box->type != BoxType::powerBall) {
                            removeDripTrack = box->track;
                        }
                        
                        if (box->type == BoxType::dustbox) {
                            for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
                                Box *b = (*iter);
                                if (box->track == b->track) {
                                    if (b->type != BoxType::dustbox && b->type != BoxType::powerBall && b->type
                                        != BoxType::dripbox) {
                                        b->slowbox();
                                        b->isSlow = true;
                                    }
                                }
                                iter++;
                            }
                        }
                        
                        if(box->type == BoxType::dustbox || box->type == BoxType::sunbox || box->type == BoxType::bullet) {
                            
                            //如果是灰尘,或者阳光,落地后直接回收
                            
                            if(box->type == BoxType::sunbox) {
//                                int trac = box->track;
                                float _x = box->getPositionX();
                                float _y = box->getPositionY();
                                player->checkIsHurtByBomb(Vec2(_x,_y));
                                boxBangAction(_x-GRID_SIZE,_y);
                                boxBangAction(_x+GRID_SIZE,_y);
                                boxBangAction(_x,_y);
                                Manager::getInstance()->playSoundEffect("bombSound.mp3");
                                //this->removeTrackBox(box->track);
                            }
                            removeActionChild(box);
                            boxlist.remove(box);
                            iter = dropBoxList.erase(iter);
                            continue;
                        }
//                        
//                        if(level != 0) {
//                            if(monster->inCombat()) {
//                                if(box->type == BoxType::dustbox) {
//                                    
//                                }
//                            }
//                        }
                        
                        
                        
                        //
                        
                        if (box->type != BoxType::waterBall && box->type != BoxType::powerBall) {
                            for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
                                Box *b = (*iter);
                                if(b->track == removeDripTrack && (b->type == BoxType::waterBall || b->type == BoxType::powerBall)) {
                                    log("track:%d,y:%f",b->track,b->getPositionY());
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
                        iter = dropBoxList.erase(iter);
                        continue;
                    } else { //正常移动
                        box->setPosition(box->getPosition().x,box->getPosition().y - BOX_SPEED *boxSpeed);
                        
                    }
                    
                }
            }
            ++iter;
        }
        
        if (dropBoxList.size() == 0) {
            isMove = false;
            
            isDetectionBox = true;
            

            this->detectionOfFullLine();   //不改变状态
            if(level != 0) {
                this->isPlayAttackAnimotion = true;
            }
        }
}

void PlayScene::moveBullet() {
    int removeDripTrack = 0; //移除这一列所有的水滴
    
    for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *b = (*iter);
            if (b->getPositionY()< tekken->getPositionY()) {
                if (b->getPositionX()+GRID_SIZE > tekken->getPositionX() && b->getPositionX()-GRID_SIZE < tekken->getPositionX()) {
                    boxBangAction(b->getPositionX(),getPositionY());
                    removeChild(b);
                    boxlist.remove(b);
                    iter = dropBoxList.erase(iter);
                    tekken->stopAllActions();
                    tekken->setPosition(Vec2(-100,-100));
                    continue;
                }
            }
            iter++;
    }
    
    if (isLaser) {
        isLaser = false;
        for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *box = (*iter);
            if(CommonData::getInstance()->getRoleSkillLevel(6)>3) {
                if (box->track == player->getMyRow()+1 || box->track == player->getMyRow()-1 || box->track == player->getMyRow()) {
                    boxBangAction(box->getPositionX(),box->getPositionY());
                    removeChild(box);
                    iter = dropBoxList.erase(iter);
                    boxlist.remove(box);
                    continue;
                } else {
                    iter++;
                }
            } else {
                if (box->track == player->getMyRow()) {
                    boxBangAction(box->getPositionX(),box->getPositionY());
                    removeChild(box);
                    iter = dropBoxList.erase(iter);
                    boxlist.remove(box);
                    continue;
                } else {
                    iter++;
                }
            }
        }
    }
    
    for(std::list<Box*>::iterator iter = dropBoxList.begin(); iter != dropBoxList.end();) {
            Box *box = (*iter);
            if (box != NULL) {
//                if(!box->isDead) { // 箱子不能是静止状态
                    if((box->getPositionY() - box->targetPositionY ) <= BOX_SPEED*boxSpeed) {  // 如果下落的箱子,距离下落目标的距离低于移动速度, 就直接到下落目标的坐标
                        //log("最后一步小于速度,直接到目标坐标 %f, track :%d",box->targetPositionY,box->track);
                        box->setPositionY(box->targetPositionY);
                        
                        if (box->type != BoxType::dripbox || box->type != BoxType::powerBall) {
                            removeDripTrack = box->track;
                        }
                        
                        if (box->type == BoxType::dustbox) {
                            for(std::list<Box*>::iterator iter = boxlist.begin(); iter != boxlist.end(); ) {
                                
                                Box *b = (*iter);
                                
                                if(b->type != BoxType::waterBall) {
                                    if (box->track == b->track) {
                                        b->slowbox();
                                        b->isSlow = true;
                                    }
                                }
                                
                                
                                iter++;
                            }
                        }
                        
                        if(box->type == BoxType::dustbox || box->type == BoxType::sunbox || box->type == BoxType::bullet) {
                            
                            if(box->type == BoxType::sunbox) {
                                //呵呵 王梦雨这个催鬼
//                                int trac = box->track;
                                float _x = box->getPositionX();
                                float _y = box->getPositionY();
                                player->checkIsHurtByBomb(Vec2(_x, _y));
                                boxBangAction(_x-GRID_SIZE,_y);
                                boxBangAction(_x+GRID_SIZE,_y);
                                boxBangAction(_x,_y);
                                Manager::getInstance()->playSoundEffect("bombSound.mp3");
                                //this->removeTrackBox(box->track);
                            }
                            //由此开始
                            
                            removeActionChild(box);
                            boxlist.remove(box);
                            iter = dropBoxList.erase(iter);
                            box =  nullptr;
                            continue;

                        }
                        
                        if(box->type == BoxType::hailbox) {
                            removeActionChild(box);
                            boxlist.remove(box);
                            iter = dropBoxList.erase(iter);
                            box =  nullptr;
                            continue;
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
                        
                        box->isDead = true;
                        iter = dropBoxList.erase(iter);
                        continue;
                    } else { //正常移动
                        box->setPosition(box->getPosition().x,box->getPosition().y - BOX_SPEED *boxSpeed);
                    }
                    
                
            }
        ++iter;
    }
        
    if (dropBoxList.size() == 0) {
        this->playSceneState->enCurState = EnumState::battleWait;
    }
}


void PlayScene::boxRemoveAction(Box *box) {
    Box *b = Box::createMyBox(box->type);
    b->setPosition(box->getPosition());
    addChild(b);
//    CallFunc * funcall= CallFunc::create(this, callfunc_selector(PlayScene::removeActionChild));
    CallFunc * funcall= CallFuncN::create(std::bind(&PlayScene::removeActionChild, this,b));
    ActionInterval * moveBy = MoveTo::create(0.5,Vec2(b->getPositionX(), b->getPositionY()+30));
    ActionInterval * fadeout = FadeOut::create(0.5);
    FiniteTimeAction * spawn = Spawn::create(moveBy,fadeout,NULL);
    FiniteTimeAction * seq = Sequence::create(spawn,funcall,NULL);
    b->runAction(seq);
    
}

void PlayScene::boxBangAction(float x, float y) {
//    Box *b = Box::createMyBox(box->type);
//    b->setPosition(box->getPosition());
//    addChild(b);
    //CallFunc * funcall= CallFuncN::create(std::bind(&PlayScene::removeActionChild, this,b));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bomb_action.ExportJson");
    auto amt = Armature::create("bomb_action");
    amt->setPosition(x,y);
    amt->setScale(2);
    amt->setTag(141);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    this->addChild(amt,99);
    amt->getAnimation()->playWithIndex(0);
}

void PlayScene::removeActionChild(Node* node) {
    removeChild(node);
}


void PlayScene::onTouchesBegan(const std::vector<Touch*>& touches,Event* event) {
    log("onTouchesBegan");
    if (!isGamePause) {
        player->onTouchesBegan(touches, event);
    }    
}


void PlayScene::onTouchesEnded(const std::vector<Touch*>& touches,Event* event)
{
    if (!isGamePause) {
        player->onTouchesEnded(touches, event);
    }
}

void PlayScene::dripDelegateDead(BaseRole* node, int num) {
    log("dead");
    isDripDead = true;
    
    if(level == 50 || (level != 0 && level%5!=0)) {
        if(monster->inCombat()) {
            monster->reset();
            monster->setVictory(true);
        }
    }
    
    isGamePause = true;
    if(isGameOver) {
        return;
    }
    
    if (level != 0) {
        if(level%5 == 0 && level %10 != 0  && level != 50) {
            if (CommonData::getInstance()->get(level) == CHECKPOINT_PLAYED) {
                rankType = 2;
                ws->getNormalRank(floor);
                txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
                popupWin->show();
            } else {
                isGamePause = true;
                CommonData::getInstance()->put(level, 1);
                // 1 - 8 道具奖励
                // 9 1钻石奖励
                // 10 无奖励
                // 11 12 奖励角色
                
                auto popupWinReward = PopupWinReward::createNode(9,hammerTimer/10);
                popupWinReward->setDelegate(this);
                popupWinReward->setPosition(0,0);
                popupWinReward->setFloor(floor);
                popupWinReward->setTag(777);
                ws->getNormalRank(floor);
                addChild(popupWinReward,998);
            }
            
        } else {
            laserBoss->setBulletsPos(Vec2(-100, SCREEN_HEIGHT+500));
            laserBoss->setIsUpdate(false);
            btnReturnOfTheKing->setEnabled(true);
            popupReturnOfTheKing->show();
        }
    }
    
    if(level == 0) {
        if(floor < targetF) {
            popupEndless->show();
            ws->getUnlimitedRank(floor);
            if (floor > CommonData::getInstance()->getEndlessFloor()) {
                CommonData::getInstance()->setEndlessFloor(floor);
            }
            txtEndlessBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
        } else {
            popupEndlessWin->show();
            ws->getUnlimitedRank(floor);
            CommonData::getInstance()->addCrystal(1);
            if (floor > CommonData::getInstance()->getEndlessFloor()) {
                CommonData::getInstance()->setEndlessFloor(floor);
            }
            txtEndlessWinBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
        }
    }
}

void PlayScene::dripDelegateRemoveHailBox(BaseRole* node, Box* box) {
    log("移除箱子");
    box->isDestroy = true;
}

void PlayScene::dripDelegateUmbrella(BaseRole* node) {
    
}

int close = 0;

void PlayScene::dripDelegateWaterBall(BaseRole* node,Box* box){
    
    
//    monster->getBodyList()
//    float _x = box->getPositionX();
//    close = 0;
//    float a = fabs(monster->getBodyList().at(0)->getPosition().x - _x);
//    for (int i=1; i < monster->getBodyList().size(); i++) {
//        if(a  > fabs(monster->getBodyList().at(i)->getPosition().x - _x)) {
//            close = i;
//        }
//    }
    
    
    
    Sprite* sprite = Sprite::create("img_boss_attack6.png");
    
    
    sprite->setVisible(false);
    this->addChild(sprite);
    sprite->setPosition(box->getPosition());
    sprite->setTexture("img_boss_attack6.png");
    
    sprite->setVisible(true);
    MoveTo* m = MoveTo::create(0.3f, monster->getBodyList().at(0)->getPosition());
    sprite->runAction(Sequence::create(m, CallFunc::create(CC_CALLBACK_0(PlayScene::waterBall, this, sprite)),//调用runMyAction播放下一个动画
                                       NULL));
}

void PlayScene::dripDelegatevirusesBox(BaseRole* node,int track) {
    
}

void PlayScene::dripDelegatePowerBox(BaseRole* node,Box* box) {
    myEnergy += boxEnergy;
    txtGold->setString(NUM_TO_STR(myEnergy));
    
    this->showGoldNumber(box->getPosition(),String::createWithFormat(";%d",boxEnergy)->_string.c_str());
    box->isDestroy = true;
}

void PlayScene::dripDelegateBagEffectFinish() {
    
    
    LayerColor* layer = LayerColor::create(Color4B::BLACK);
    addChild(layer,199,199);
    
    auto move = MoveBy::create(0.5, Vec2(0, player->getPositionY()+150));
    //    auto move2 = MoveTo::create(0.5, Vec2(0, deadline+player->getContentSize().height/2));
    
    
    player->runAction(move);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("whiz_action.ExportJson");
    auto amt = Armature::create("whiz_action");
    amt->setScaleY(2);
    amt->setScaleX(3);
    amt->setPosition(SCREEN_CENTER);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    this->addChild(amt,250);
    amt->getAnimation()->playWithIndex(0);
    int baglevel = CommonData::getInstance()->getRoleSkillLevel(4);
    int flyfloor = baglevel*4+4;
    
    
    if (level != 0) {
        if (flyfloor > (line->getPositionY()-deadline)/GRID_SIZE) {
            flyfloor =  (line->getPositionY()-deadline)/GRID_SIZE;
        }
    }
    
    for (int i = 0; i<8; i++) {
        Box *b = Box::createMyBox(normaltype);
        b->setPosition(i*GRID_SIZE+GRID_RADIUS_SIZE, deadline+flyfloor*GRID_SIZE-GRID_RADIUS_SIZE);
        b->track = i+1;
        b->isDead = true;
        b->targetPositionY = deadline+flyfloor*GRID_SIZE-GRID_RADIUS_SIZE;
        b->setOpacity(0);
        
        addChild(b);
        
        ActionInterval *in = FadeIn::create(0.5);
        b->runAction(in);
        boxlist.push_back(b);
    }
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
            player->takeBag(false);
            if (getChildByTag(199)) {
                removeChildByTag(199);
            }
            isGamePause = false;
            isShowBag = false;
        }
    });
    
    playSceneState->enCurState = EnumState::gamePause;
    
    moveAllBox(flyfloor);
    
    
    
    playSceneState->enCurState = EnumState::dropReady;
}

    // 接触 flag为1时为碰到怪物或玩家，0为碰到砖块或下线
void PlayScene::baseBulletDelegateContact(BaseBullet* node, int flag, Box* box) {
    if (flag == 0) {
        log("hehe");
        this->boxBangAction(box->getPositionX(),box->getPositionY());
        boxlist.remove(box);
        dropBoxList.remove(box);
        removeChild(box);
    }
}

void PlayScene::baseBulletDelegateContactBall(BaseBullet* node, int flag) {
    if (level%5 != 0 && level != 0) {
        lb->setIsUpdate(false);
        lb->setPosition(-200, -200);
    }
}

void PlayScene::popupCloseCallBack(Ref *pSender) {
    log("弹窗关闭");
    
    Manager::getInstance()->playSoundEffect("btnPress.mp3");
    Manager::getInstance()->resumeBackgroundMusic();

    if (pSender == popupReturnOfTheKing) {
        if (level%5 ==0 && level != 0 && level %10 != 0 && CommonData::getInstance()->get(level) != CHECKPOINT_PLAYED  && level != 50) {
            this->hammerEnd();
            CommonData::getInstance()->put(level, 1);
        } else {
            if (level == 0) {
                popupEndless->show();
                ws->getUnlimitedRank(floor);
                if (floor > CommonData::getInstance()->getEndlessFloor()) {
                    CommonData::getInstance()->setEndlessFloor(floor);
                }
                txtEndlessBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
            } else {
                //txtLoseRank
                rankType = 3;
                ws->getNormalRank(level);
                popupLose->show();
                txtLoseBestScore->setString(String::createWithFormat("最高层数:%d",floor)->_string);
            }
        }
        if(level%5 !=0) {
            if (monster->inCombat()) {
                Manager::getInstance()->playSoundEffect("battleLose.mp3");
            }
        }
        
        CommonData::getInstance()->setHealth(1);
        
    } else if (level != 0 && pSender == popupLose) {
        Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
        Director::getInstance()->replaceScene(CheckpointScene::create());
    } else if(level != 0  && pSender == popupWin) {
        Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
        Director::getInstance()->replaceScene(CheckpointScene::create());
    } else if(level == 0 && pSender == popupEndless){
        Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
        Director::getInstance()->replaceScene(HomeScene::create());
    } else if (pSender == popupPause) {
        
        if(level == 50 || (level%5 !=0 && monster->inCombat())) {
            
            if(!isTimeOver) {
                monster->resumeMoving();
            }

        }
        startGame();
        
    }
    
    if(pSender == popupEndlessWin) {
        Director::getInstance()->replaceScene(HomeScene::create());
    }
    
    txtGold->setString(String::createWithFormat("%d",myEnergy)->_string);
}

void PlayScene::CutscenesDelegateFinish() {
    startGame();
    
    this->overLine();
}

void PlayScene::finash() {
    
}

void PlayScene::giveGift() {
    log("giveGift");
}

void PlayScene::waterBall(Sprite * sprite) {
    monster->getBodyList().at(0)->hit(1*player->getMaxAttack());
//    monster->hit();
    Manager::getInstance()->playSoundEffect("hit.mp3");
    log("attack : %f",player->getMaxAttack());
//    monster->addHealth(player->getMaxAttack()*-1);
    
    sprite->setTexture("img_boss_bomb6.png");
    sprite->runAction(ScaleBy::create(0.5, 5));
    sprite->runAction(Sequence::create(DelayTime::create(0.2), CallFunc::create(CC_CALLBACK_0(PlayScene::removeActionChild, this, sprite)),NULL));
}

void PlayScene::onMonsterAttack(int type, int count,int speed) {  //攻击.参数type：子弹类型
    log("攻击参数:%d",type);
    if(isTimeOver && CommonData::getInstance()->getRoleSkillLevel(3) == 4) {
        return;
    }
        ran = arc4random()%6;
        
        for (int i = 0; i<count; i++) {
            track[i] = ran+i+1; //随机出若干轨道
        }
        boxSpeed = itemDropTime(speed)*0.1;
        isMove = true;
        Manager::getInstance()->playSoundEffect("dorpbox.mp3");
        for (int i = 0; i < count; i++) {
            if(track[i] != 0) {
                isDrop = false;
                Box *box;
                //  弹药： 1.子弹 2.炸弹 3.冰块  4.粘液  5.反射激光  6.短激光 7.水球
                //            int type = track[i]-1;
                switch (type) {
                    case 1:
                        box = Box::createMyBox(BoxType::bullet);
                        break;
                    case 2:
                        box = Box::createMyBox(BoxType::sunbox);
                        break;
                    case 3:
                        box = Box::createMyBox(BoxType::hailbox);
                        break;
                    case 4:
                        box = Box::createMyBox(BoxType::dustbox);
                        break;
                    case 5:
                        
                        break;
                    case 6:
                        
                        break;
                    case 7:
                        box= Box::createMyBox(BoxType::waterBall);
                        break;
                    case 8:
                        break;
                    default:
                        break;
                }
                box->setPosition((track[i]-1)*GRID_SIZE+GRID_SIZE/2, SCREEN_HEIGHT-GRID_SIZE+GRID_SIZE/2);
                box->track = track[i];
                box->targetPositionY = deadline+GRID_SIZE/2;
                dropBoxList.push_back(box);
                boxlist.push_back(box);
                addChild(box);
                
                if(box->type == BoxType::waterBall) {
                    break;
                }
            }
        }
        
        this->playSceneState->enCurState = EnumState::battleStart;
    
    
    
    
    
}

void PlayScene::onBattleEnd(int result) {   //战斗结束，1.boss胜利，2.boss失败
    if(isDripDead) {
        return;
    }
    
    
    if (result == 1) {
        this->restartGame();
    }
    
    if (result == 2) {
        isGamePause = true;
        isGameOver = true;
        
        monster->reset();
        monster->leaveBattle();
        monster->setVisible(false);
        
        if (level == 50) {
            Director::getInstance()->replaceScene(FinishGameScene::createScene());
        } else {
            int ran = arc4random()%100;
            
            if(CommonData::getInstance()->get(level) == CHECKPOINT_PLAYED) { // 打过本关
                
                if(data->getUnlockSkill() == 0) { // 本关不需要解锁技能
                    rankType = 2;
                    ws->getNormalRank(floor);
                    txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
                    popupWin->show();
                } else {
                    if(CommonData::getInstance()->getRoleSkillLevel(data->getUnlockSkill()) == 0 && data->getUnlockSkillChance() > ran) { //解锁技能,未解锁技能
                        
                        showWinReward(data->getUnlockSkill());
                        
                    } else {
                        rankType = 2;
                        ws->getNormalRank(floor);
                        txtWinfloor->setString(String::createWithFormat("最高层数:%d",floor)->_string);
                        popupWin->show();
                    }
                }
                
            } else { // 没打过本关
                
                if(data->getUnlockSkill() == 0) { // 本关不需要解锁技能
                    if(level == 3 && CommonData::getInstance()->getRoleLevel(3) <=0){ //解锁千寻姐
                        showWinReward(11);
                        CommonData::getInstance()->setRoleLevel(3, 1);
                    }else if (level == 7 && CommonData::getInstance()->getRoleLevel(2) <=0 ) { //解锁激光
                        CommonData::getInstance()->setRoleLevel(2, 1);
                        showWinReward(12);
                    } else {
                        showWinReward(9);
                    }
                } else {
                    if(CommonData::getInstance()->getRoleSkillLevel(data->getUnlockSkill()) == 0 && data->getUnlockSkillChance() > ran) { //解锁技能,未解锁技能
                        showWinReward(data->getUnlockSkill());
                    } else {
                        showWinReward(9);
                    }
                }
            }
        }
        
        
    }
}

void PlayScene::showWinReward(int type) {
    CommonData::getInstance()->put(level, CHECKPOINT_PLAYED);
    auto popupWinReward = PopupWinReward::createNode(type,1);
    popupWinReward->setDelegate(this);
    popupWinReward->setPosition(0,0);
    popupWinReward->setFloor(floor);
    popupWinReward->setTag(777);
    rankType = 1;
    ws->getNormalRank(floor);

    addChild(popupWinReward,998);
}


//5.反射激光  6.短激光
void PlayScene::onMonsterCastSpell(int type,int speed) {
    if(isTimeOver && CommonData::getInstance()->getRoleSkillLevel(3) == 4) {
        return;
    }
    switch (type) {
        case 5:
            lb->setPosition(Vec2(arc4random()%SCREEN_WIDTH,SCREEN_HEIGHT+GRID_SIZE));
            lb->setSpeedX(itemDropTime(speed));
            lb->setSpeedY(itemDropTime(speed));
            lb->setIsUpdate(true);
            break;
        case 6:
            
            laserBoss->setBulletsPos(Vec2(arc4random()%SCREEN_WIDTH,SCREEN_HEIGHT+laserBoss->getContentSize().height));
            laserBoss->setIsUpdate(true);
            laserBoss->setSpeed(-1*itemDropTime(speed));
            break;
        default:
            break;
    }
}

void PlayScene::popupWinRewardDelegateCloseCallBack() {
    Director::getInstance()->replaceScene(CheckpointScene::create());
}

void PlayScene::popupWinRewardDelegateShareCallBack() {
    if (CommonData::getInstance()->IsShareSendGold()) {
        CommonData::getInstance()->addEnergy(5);
    }
    txtGold->setString(String::createWithFormat("%d",myEnergy)->_string);
    log("share");
    Manager::getInstance()->shareQQ();
    GetPrizeHint* hint = GetPrizeHint::createPrizeHint(5);
    hint->setPosition(Vec2(0, SCREEN_LEFT_UP.y+100));
    addChild(hint, 99999);
    hint->runAction(hint->createHintAction());
}

void PlayScene::popupWinRewardDelegateLuckCallBack() {
    Director::getInstance()->replaceScene(WheelPanelScene::createWheelPanelScene(level));
}

void PlayScene::LevelInfoTextLayerDelegateClose() {
    removeChild(levelInfo);
    
    
    
    if(level == 4) {
        
        isGamePause = true;
        auto textHintNode = Node::create();
        textHintNode->setPosition(SCREEN_CENTER+Vec2(0,300));
        addChild(textHintNode,100,2596);
        
        Sprite* textBG = Sprite::create("img_guide_blackboard.png");
        textBG->setPosition(Vec2::ZERO);
        textHintNode->addChild(textBG);
        
        auto textTitle = Sprite::create("img_guide4_word.png");
        textTitle->setPosition(80,22);
        textHintNode->addChild(textTitle,10);
        
        auto btnTips = Sprite::create("img_guide_arrow2.png");
        btnTips->setPosition(Vec2(40, 700));
        Blink* b1 = Blink::create(1.9, 5);
        RepeatForever* r1 = RepeatForever::create(b1);
        btnTips->runAction(r1);
        addChild(btnTips,100,2597);
        
        auto btnMask = Sprite::create();
        
        auto listener2=EventListenerTouchOneByOne::create();
        listener2->setSwallowTouches(true);
        listener2->onTouchBegan=[](Touch *touch,Event *event){
            return true;
        };
        listener2->onTouchMoved=[](Touch *touch,Event *event){
        };
        listener2->onTouchEnded=[=](Touch *touch,Event *event){
            //            btnMask->setVisible(false);
            //            this->removeChildByTag(2596);
            //            startGame();
            //            _eventDispatcher->removeEventListenersForTarget(btnMask);
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, btnMask);
        btnMask->setTag(2598);
        addChild(btnMask,5);
        
        
    } else if(level == 5) {
        isGamePause = true;
        auto textHintNode = Node::create();
        textHintNode->setPosition(SCREEN_CENTER+Vec2(0,300));
        addChild(textHintNode,100,2596);
        
        Sprite* textBG = Sprite::create("img_guide_blackboard.png");
        textBG->setPosition(Vec2::ZERO);
        
        textHintNode->addChild(textBG);
        
        auto textTitle = Sprite::create("img_guide5_word.png");
        textTitle->setPosition(80,22);
        textHintNode->addChild(textTitle,10);
        
        auto btnMask = Sprite::create();
        
        auto listener2=EventListenerTouchOneByOne::create();
        listener2->setSwallowTouches(true);
        listener2->onTouchBegan=[](Touch *touch,Event *event){
            return true;
        };
        listener2->onTouchMoved=[](Touch *touch,Event *event){
        };
        listener2->onTouchEnded=[=](Touch *touch,Event *event){
            btnMask->setVisible(false);
            this->removeChildByTag(2596);
            startGame();
            _eventDispatcher->removeEventListenersForTarget(btnMask);
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, btnMask);
        addChild(btnMask,300,2598);
    } else {
        startGame();
    }
}


void PlayScene::baseBulletDelegateSLaserActionFinish() {
    if(level%5 ==0 && level != 50) {
        return;
    }
    if (monster) {
        if (monster->inCombat()) {
            float _x = player->getPositionX();
            close = 0;
            float a = fabs(monster->getBodyList().at(0)->getPosition().x - _x);
            for (int i=0; i < monster->getBodyList().size(); i++) {
                if(a  > fabs(monster->getBodyList().at(i)->getPosition().x - _x)) {
                    close = i;
                }
            }
            
            if (fabs(_x-monster->getBodyList().at(close)->getPosition().x) < laser->halfWidth * GRID_SIZE) {
                
                
                
                monster->getBodyList().at(close)->hit(laser->attack*attackPlus(),true);
            }
        }
    }
    

}
//
void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event) {
    if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_BACK) {
        return;
    }
}


int PlayScene::itemDropTime(int level) {
    
    if(level > 15) {
        level = 15;
    }
    
    if(level <1 ) {
        level = 1;
    }
    
    switch (level) {
        case 1:
            return 4;
        case 2:
            return 5;
        case 3:
            return 6;
        case 4:
            return 7;
        case 5:
            return 8;
        case 6:
            return 9;
        case 7:
            return 10;
        case 8:
            return 11;
        case 9:
            return 12;
        case 10:
            return 13;
        case 11:
            return 14;
        case 12:
            return 15;
        case 13:
            return 16;
        case 14:
            return 17;
        case 15:
            return 18;
        case 16:
            return 19;
        case 17:
            return 20;
        case 18:
            return 21;
        case 19:
            return 22;
        case 20:
            return 23;
        default:
            break;
    }
    return 0;
}


void PlayScene::onEnter() {
    log("onEnter");
    Node::onEnter();
    Manager::getInstance()->playBackgroundMusic("playBGM.mp3");
}

void PlayScene::onExit()
{
    log("退出当前关卡:%d",level);
    Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
    this->isSceneRunning = false;
    Node::onExit();
}
