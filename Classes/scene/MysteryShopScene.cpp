//
//  MysteryShopScene.cpp
//  beymac
//
//  Created by je on 6/11/15.
//
//

#include "MysteryShopScene.h"
#include <cocos2d.h>
#include "Macro.h"
#include "HomeScene.h"
#include "ButtonFactory.h"
#include "Manager.h"


USING_NS_CC;
using namespace ui;


void MysteryShopScene::payResult(bool result)
{
    if(result){
        log("支付成功");
        if(feedId==MYSTERYSHOP1){
            CommonData::getInstance()->addEnergy(360);
        }else if(feedId==MYSTERYSHOP2){
            CommonData::getInstance()->addCrystal(110);
        }
    }else{
        log("支付失败");
    }
    
}

bool MysteryShopScene::init()
{
    //背景
    auto bg=Sprite::create("img_mystery_shop_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    
    
    //关闭
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_close.png");
    btnBack->cocos2d::Node::setPosition(SCREEN_WIDTH-55, SCREEN_HEIGHT-95);
    btnBack->setTitleFontSize(50);
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->popScene();
        }
    });
    
    //我的能量
    int iMyGold=CommonData::getInstance()->getEnergy();
    std::string strMyGold=StringUtils::format("我的能量    %d",iMyGold);
    //我的能量——文本
    auto txtMyGold=Text::create();
    txtMyGold->setString(strMyGold);
    txtMyGold->setFontSize(35);
    txtMyGold->cocos2d::Node::setPosition(150, 70);
    //我的能量——图片
    auto iconGold=Sprite::create("img_shop_icon_power.png");
    iconGold->setPosition(160, 20);
    txtMyGold->addChild(iconGold);
    
    
    //我的晶核
    int iMyCrystal=CommonData::getInstance()->getCrystal();
    std::string strMyCrystal=StringUtils::format("我的晶核    %d",iMyCrystal);
    //我的晶核文本
    auto txtMyCrystal=Text::create();
    txtMyCrystal->setString(strMyCrystal);
    txtMyCrystal->setFontSize(35);
    txtMyCrystal->cocos2d::Node::setPosition(450, 70);
    //我的晶核——图片
    auto iconCrystal=Sprite::create("img_shop_icon_crystal.png");
    iconCrystal->setPosition(160, 20);
    txtMyCrystal->addChild(iconCrystal);
    
    
    auto btnPrice1=ButtonFactory::createButtonPrice("img_price_12.png");
    btnPrice1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            feedId=MYSTERYSHOP1;
            Payment::pay(MYSTERYSHOP1, this);
        }
    });
    btnPrice1->cocos2d::Node::setPosition(490, 465);
    
    auto btnPrice2=ButtonFactory::createButtonPrice("img_price_18.png");
    btnPrice2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            feedId=MYSTERYSHOP2;
            Payment::pay(MYSTERYSHOP2, this);
        }
    });
    btnPrice2->cocos2d::Node::setPosition(490, 197);
    
    
    this->addChild(bg,-1);
    this->addChild(btnBack);
    this->addChild(txtMyGold);
    this->addChild(txtMyCrystal);
    this->addChild(btnPrice1);
    this->addChild(btnPrice2);
    return true;
}


