//
//  WheelPanelScene.cpp
//  SuperPopPig
//
//  Created by wang on 15/1/19.
//
//

#include "WheelPanelScene.h"
#include "Macro.h"
#include "CheckpointScene.h"
#include "GetPrizeHint.h"
#include "PlayScene.h"
#include "SkillSelectScene.h"
#include "SimpleAudioEngine.h"

static float m_needAngle[6] =
{
    30,
    330,
    270,
    210,
    150,
    90
};

int m_wheel_pArray[6] =
{
    800,
    950,
    990,
    997,
    999,
    1000
};

int m_wheel_reward[6] =
{
    1,
    2,
    3,
    5,
    10,
    20
};

WheelPanelScene::WheelPanelScene()
:isRolling(false)
,buttonState(startWheelState)
,count(0)
,money(0)
,curLevel(1)
{

}

WheelPanelScene::~WheelPanelScene()
{

}

bool WheelPanelScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Sprite* bg = Sprite::create("img_lucky_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    addChild(bg);
    
    showSnow();

    Sprite* title = Sprite::create(LSTRINGIMAGE("img_lucky_title"));
    title->setPosition(SCREEN_CENTER);
    title->setPositionY(SCREEN_LEFT_UP.y - title->getContentSize().height/2);
    addChild(title);
    
    Sprite* shadow = Sprite::create("img_lucky_round_bg.png");
    shadow->setPosition(SCREEN_CENTER+Vec2(0,20));
    addChild(shadow);
    
    wheel = Sprite::create("img_lucky_round.png");
    wheel->setPosition(SCREEN_CENTER+Vec2(0,20));
    addChild(wheel);
    
    Sprite* wheel_arrow = Sprite::create("img_luckty_pointer.png");
    wheel_arrow->setPosition(SCREEN_CENTER+Vec2(0,20));
    addChild(wheel_arrow);
    
    //商店弹窗
//    auto popShop=ShopLayer::createShopLayer();
//    popShop->setTag(10);
//    addChild(popShop,999);
    
    startBtn = Button::create("img_lucky_btn.png");
    startBtn->setPosition(SCREEN_CENTER+Vec2(0,-350));
    startBtn->setLocalZOrder(100);
    startBtn->setTitleText("免费抽奖");
    startBtn->setTitleFontName("Arial");
    startBtn->setTitleFontSize(40);
    startBtn->setTitleColor(Color3B(123, 78, 0));
    startBtn->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            if (buttonState == startWheelState) {
                // 开始转盘
                Manager::getInstance()->playSoundEffect("btnPress.mp3");
                // 扣钱
                if (CommonData::getInstance()->getCrystal() >= money) {
                    CommonData::getInstance()->addCrystal(-money);
                } else {

//                    auto shopLayer=(PopupLayer *)(this->getChildByTag(10));
//                    shopLayer->show();//显示商店弹窗
//                    return;
                }

                
                // 开始
                wheel->setRotation(0);
                wheelStartRoll();
                count++;
                
                startBtn->setEnabled(false);
                startBtn->setColor(Color3B::GRAY);
                
            }
            else if (buttonState == getPrizeState)
            {
                // 获取奖品
//                buttonState = startWheelState;
//                startBtn->setColor(Color3B(255, 255, 255));
//                
//                if (count == 1) {
//                    money = 5;
//                }
//                else if (count > 1)
//                {
//                    money = money * 2;
//                }
//                
//                startBtn->setTitleText("开始抽奖");
//                startBtn->setTitleColor(Color3B(136, 113, 255));
            }
            
        }
    });
    addChild(startBtn);
    
    Button *backBtn = Button::create("img_btn_round.png");
    backBtn->setPosition(SCREEN_LEFT_DOWN + Vec2(70,70));
    backBtn->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            finishScene();
        }
    });
    addChild(backBtn);
    
    Sprite* backImage = Sprite::create("img_btn_back.png");
    backImage->setPosition(SCREEN_LEFT_DOWN + Vec2(70,70));
    addChild(backImage);
    
    nextBtn = Button::create("img_window_green.png");
    nextBtn->setPosition(SCREEN_RIGHT_DOWN + Vec2(-120,70));
    nextBtn->setLocalZOrder(100);
    nextBtn->setTitleText(LSTRING("NextLevel"));
    nextBtn->setTitleFontName("Arial");
    nextBtn->setTitleFontSize(40);
    nextBtn->setTitleColor(Color3B(12, 63, 0));
    nextBtn->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            // 下一关
            log("curlevel : %d", curLevel);
            curLevel++;
            auto scene = SkillSelectScene::createScene(curLevel);
            Director::getInstance()->replaceScene(scene);
        }
    });
    addChild(nextBtn);
    
    return true;
}

void WheelPanelScene::onEnter()
{
    CCLayer::onEnter();
}

void WheelPanelScene::onExit()
{
    CCLayer::onExit();
}

Scene* WheelPanelScene::createWheelPanelScene(int level)
{
    Scene* scene = Scene::create();
    
    WheelPanelScene* layer = WheelPanelScene::create();
    scene->addChild(layer);
    layer->setLevel(level);
    return scene;
}


void  WheelPanelScene::wheelStartRoll()
{
    if (isRolling) {
        return;
    }
    
    Manager::getInstance()->playSoundEffect("wheel.mp3");
    
//    SceneManager::sharedSceneManager()->playWheel();
    isRolling = true;
    rollRound = 0;
    
    RotateBy* rotate = RotateBy::create(1.5f, 360);
    CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(WheelPanelScene::wheelRollFinish,this));
    Sequence* action = Sequence::create(rotate, callfun, NULL);
    wheel->runAction(action);
}
void  WheelPanelScene::wheelRollFinish()
{
    rollRound++;
    if (rollRound < 1) {
        RotateBy* rotate = RotateBy::create(1.5f, 360);
        CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(WheelPanelScene::wheelRollFinish,this));
        Sequence* action = Sequence::create(rotate, callfun, NULL);
        wheel->runAction(action);
    }
    else if (rollRound == 0)
    {
        RotateBy* rotate = RotateBy::create(1.8f, 360);
        CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(WheelPanelScene::wheelRollFinish,this));
        Sequence* action = Sequence::create(rotate, callfun, NULL);
        wheel->runAction(action);
    }
    else
    {
        float angle = 0;
        result = getWheelResult();
        
        log("getGold = %d",m_wheel_reward[result]);
//        GameDataManager::getInstance()->setGoldNum(GameDataManager::getInstance()->getGoldNum()+m_wheel_reward[m_result]);

        angle = m_needAngle[result];

        float sec = 2.3f;
        float duration = angle/360*sec;
        wheel->setRotation(0);
        RotateBy* rotate = RotateBy::create(duration, angle);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(WheelPanelScene::wheelFinish,this));
        Sequence* seq = Sequence::create(rotate, callback, NULL);
        wheel->runAction(seq);
    }
}
void  WheelPanelScene::wheelFinish()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    isRolling = false;
    
//    startBtn->setEnabled(true);
//    // 换字
//    if (count == 1) {
//        money = 5;
//    }
//    else if (count > 1)
//    {
//        money = money * 2;
//    }
//    char szBuf[32] = {0};
//    //itoa(nValue, szBuf, 10);
//    sprintf(szBuf, "%d %s", money,LSTRING("Crystal"));
//    startBtn->setTitleText(szBuf);
    
    // 得到晶核

    CommonData::getInstance()->addCrystal(m_wheel_reward[result]);
    
    
    Manager::getInstance()->playSoundEffect("getGift.mp3");
    
    GetPrizeHint* hint = GetPrizeHint::createPrizeHint(m_wheel_reward[result]);
    hint->setPosition(Vec2(0, SCREEN_LEFT_UP.y+100));
    addChild(hint, 100);
    CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(WheelPanelScene::hintFinish,this));
    Sequence* action = Sequence::create(hint->createHintAction(),callfun,NULL);
    hint->runAction(action);
//    startBtn->setEnabled(false);
}

int   WheelPanelScene::getWheelResult()
{
    srand((unsigned)time(NULL));
    int currP = rand()%1000+1;
    CCLOG("currP = %d" , currP);
    int level = 0;
    while (currP >= m_wheel_pArray[level]) {
        level++;
    }
    
    CCLOG("level = %d",level);
    return level;
}

void  WheelPanelScene::finishScene()
{
    Director::getInstance()->replaceScene(CheckpointScene::create());
    //removeFromParent();
}

// 雪花
void WheelPanelScene::showSnow()
{
    auto snow = ParticleSnow::createWithTotalParticles(130);
    this->addChild(snow,0);
    
    auto p = snow->getPosition();
    snow->setPosition(Vec2(p.x, p.y-110) );
    snow->setLife(10);
    snow->setLifeVar(1);
    
    // gravity
    snow->setGravity(Vec2(1,-10));
    
    // speed of particles
    snow->setSpeed(100);
    snow->setSpeedVar(30);
    
    snow->setStartSize(25);
    snow->setStartSizeVar(20);
    snow->setEndSize(20);
    snow->setEndSizeVar(10);
    
    Color4F startColor = snow->getStartColor();
    startColor.r = 1.0f;
    startColor.g = 1.0f;
    startColor.b = 1.0f;
    snow->setStartColor(startColor);
    
    Color4F startColorVar = snow->getStartColorVar();
    startColorVar.b = 0.1f;
    snow->setStartColorVar(startColorVar);
    
    
    
    snow->setEmissionRate(snow->getTotalParticles()/snow->getLife());
    
    snow->setTexture( Director::getInstance()->getTextureCache()->addImage("img_snow.png") );
    
    snow->setPosition(SCREEN_CENTER.x, SCREEN_LEFT_UP.y);
}

// 获得金币提示消失
void  WheelPanelScene::hintFinish()
{
    
}

void WheelPanelScene::setLevel(int level)
{
    curLevel = level;
}