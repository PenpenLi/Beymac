//
//  StartGameTextScene.cpp
//  beymac
//
//  Created by mumu on 15/6/4.
//
//

#include "StartGameTextScene.h"
#include "CommonHeader.h"
#include "Cutscenes.h"
#include "HomeScene.h"

StartGameTextScene::StartGameTextScene()
:isTouch(false)
{

}

StartGameTextScene::~StartGameTextScene()
{

}

bool StartGameTextScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }
    
    showSnow();
    
    const char* s = __String::createWithFormat("level%d",0)->getCString();
    
    
    log("%s",LSTRINGLEVELINFO(s));
    str = LSTRINGLEVELINFO(s);

    
    totalLength = str.size();
    log("文本长度：%d",totalLength);
    curLength = 0;
    
    info = Label::create();
    info->setTextColor(Color4B::WHITE);
    info->setAnchorPoint(Vec2(0,1));
    info->setString("");
    info->setSystemFontSize(27);
    info->setDimensions(550, 800);
    info->setPosition(50,420);
//    info->setHorizontalAlignment(TextHAlignment::CENTER);
//    info->setVerticalAlignment(TextVAlignment::CENTER);
    addChild(info);
//
    
//    Sprite* bg = Sprite::create("img_story_bg_black.png");
//    bg->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
//    addChild(bg);
    
//    auto actFunc=CallFuncN::create([&](Ref *pSender){
//        Director::getInstance()->replaceScene(HomeScene::create());
//    });
//    info->runAction(Sequence::create(DelayTime::create(0.1),MoveBy::create(7, Vec2(0,600)),DelayTime::create(1.5),actFunc, NULL));
    
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        curLength = curLength+3;

        if (curLength > totalLength) {
//            Director::getInstance()->replaceScene(HomeScene::create());
            isTouch = true;
        }
        else
        {
            string s = str.substr(0,curLength);

//            log("显示文字：%s",s.c_str());
//            log("显示本文长度：%lu",s.size());
//            log("显示长度：%d",curLength);
            
            info->setString(s);
        }
        
    });
    RepeatForever* repeat = RepeatForever::create(Sequence::create(DelayTime::create(0.1),actFunc, NULL));
    info->runAction(repeat);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(StartGameTextScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(StartGameTextScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(StartGameTextScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void StartGameTextScene::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void StartGameTextScene::onExit()
{
    Node::onExit();
}

Scene* StartGameTextScene::createScene()
{
    Scene* scene = Scene::create();
    StartGameTextScene* layer = StartGameTextScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartGameTextScene::onTouchBegan(Touch* touch, Event *pEvent)
{
    if (isTouch) {
//        Scene* scene = Scene::create();
//        auto layer = Cutscenes::createCutscenes(0);
//        scene->addChild(layer);
        Director::getInstance()->replaceScene(HomeScene::create());
    }
    
    return true;
}
void StartGameTextScene::onTouchMoved(Touch* touch, Event *pEvent)
{
    
}
void StartGameTextScene::onTouchEnded(Touch* touch, Event *pEvent)
{
    
}

// 雪花
void StartGameTextScene::showSnow()
{
    auto snow = ParticleSnow::createWithTotalParticles(100);
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
    
    snow->setStartSize(15);
    snow->setStartSizeVar(12);
    snow->setEndSize(12);
    snow->setEndSizeVar(5);
    
    Color4F startColor = snow->getStartColor();
    startColor.r = 1.0f;
    startColor.g = 1.0f;
    startColor.b = 1.0f;
    snow->setStartColor(startColor);
    
    Color4F startColorVar = snow->getStartColorVar();
    startColorVar.b = 0.1f;
    snow->setStartColorVar(startColorVar);
    
    
    
    snow->setEmissionRate(snow->getTotalParticles()/snow->getLife());
    
    snow->setTexture( Director::getInstance()->getTextureCache()->addImage("img_snowball.png") );
    
    snow->setPosition(SCREEN_CENTER.x, SCREEN_LEFT_UP.y);
}
