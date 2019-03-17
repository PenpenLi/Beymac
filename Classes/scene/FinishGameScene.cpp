//
//  FinishGameScene.cpp
//  beymac
//
//  Created by mumu on 15/6/10.
//
//

#include "FinishGameScene.h"
#include "CommonHeader.h"
#include "HomeScene.h"

FinishGameScene::FinishGameScene()
:isTouch(false)
{

}

FinishGameScene::~FinishGameScene()
{

}

bool FinishGameScene::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    const char* s = __String::createWithFormat("level%d",100)->getCString();
    
    
    log("%s",LSTRINGLEVELINFO(s));
    
    Label* info = Label::create();
    info->setTextColor(Color4B::WHITE);
    info->setAnchorPoint(Vec2(0,1));
    info->setString(LSTRINGLEVELINFO(s));
    info->setSystemFontSize(28);
    info->setDimensions(550, 900);
    info->setPosition(50,0);
    //    info->setHorizontalAlignment(TextHAlignment::CENTER);
    //    info->setVerticalAlignment(TextVAlignment::CENTER);
    addChild(info);

    Sprite* bg = Sprite::create("img_story_bg_black.png");
    bg->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
    addChild(bg);

    auto actFunc=CallFuncN::create([&](Ref *pSender){
        isTouch = true;
//        Director::getInstance()->replaceScene(HomeScene::create());
    });
    info->runAction(Sequence::create(DelayTime::create(0.1),MoveBy::create(8, Vec2(0,800)),DelayTime::create(1.5),actFunc, NULL));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FinishGameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FinishGameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FinishGameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void FinishGameScene::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void FinishGameScene::onExit()
{
    Node::onExit();
}

Scene* FinishGameScene::createScene()
{
    Scene* scene = Scene::create();
    FinishGameScene* layer = FinishGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool FinishGameScene::onTouchBegan(Touch* touch, Event *pEvent)
{
    if (isTouch) {
        Director::getInstance()->replaceScene(HomeScene::create());
    }
    
    return true;
}
void FinishGameScene::onTouchMoved(Touch* touch, Event *pEvent)
{
    
}
void FinishGameScene::onTouchEnded(Touch* touch, Event *pEvent)
{
    
}
