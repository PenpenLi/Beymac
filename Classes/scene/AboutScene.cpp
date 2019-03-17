//
//  AboutScene.cpp
//  beymac
//
//  Created by je on 5/26/15.
//
//

#include "AboutScene.h"
#include "Background.h"
#include "ButtonFactory.h"
#include "CommonHeader.h"
#include "HomeScene.h"


USING_NS_CC;
using namespace ui;

bool AboutScene::init()
{
    //背景
    auto bg=Background::createBackground();
    
    auto txt=Sprite::create("img_aboutus.png");
    txt->setPosition(SCREEN_CENTER);
    bg->addChild(txt);
    
    
    //关闭
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_back.png");
    btnBack->cocos2d::Node::setPosition(70, 60);
    btnBack->setTitleFontSize(50);
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(HomeScene::create());
            
        }
    });
    
    this->addChild(bg,-10);
    this->addChild(btnBack);
    return true;
}