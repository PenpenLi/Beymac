//
//  ShopScene.cpp
//  beymac
//
//  Created by je on 4/22/15.
//
//

#include "ShopScene.h"
#include <cocos2d.h>
#include "Macro.h"
#include "HomeScene.h"
#include "ButtonFactory.h"
#include "Manager.h"


#define TAG_GIFT_PANEL 101
#define TAG_CRYSTAL_PANEL 102


USING_NS_CC;
using namespace ui;


//购买回调
void ShopScene::payResult(bool result)
{
    log("交易结果:%d,购买物品:%d",result,feedId);
    if(result){
        switch (feedId) {
            case POWER1:
                CommonData::getInstance()->addEnergy(100);
                break;
            case POWER2:
                CommonData::getInstance()->addEnergy(220);
                break;
            case POWER3:
                CommonData::getInstance()->addEnergy(360);
                break;
            case CRYSTAL1:
                CommonData::getInstance()->addCrystal(20);
                break;
            case CRYSTAL2:
                CommonData::getInstance()->addCrystal(44);
                break;
            case CRYSTAL3:
                CommonData::getInstance()->addCrystal(110);
                break;
                
            default:
                break;
        }
        
        if(this->isRunning()){
            refreshData();
        }
        
    }else{
        
    }
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




bool ShopScene::init()
{
    //背景
    auto bg=Sprite::create("img_shop_bg.jpg");
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
    
    
    
    //添加两种商品面板
    auto panelGoldItems=createGoldPanel();
    panelGoldItems->setTag(TAG_GIFT_PANEL);
    auto panelCrystalItems=createCrystalPanel();
    panelCrystalItems->setTag(TAG_CRYSTAL_PANEL);
    
    
    
    //添加两种按钮——礼包
    btnGiftTag=Button::create();
    btnGiftTag->loadTextures("img_shop_btn_gift_selected.png", "img_shop_btn_gift_unselected.png");
    btnGiftTag->cocos2d::Node::setPosition(210, SCREEN_HEIGHT-220);
    btnGiftTag->setEnabled(false);
    btnGiftTag->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            btnCrystalTag->loadTextureNormal("img_shop_btn_crystal_selected.png");
            btnCrystalTag->setEnabled(true);
            
            btnGiftTag->loadTextureNormal("img_shop_btn_gift_unselected.png");
            btnGiftTag->setEnabled(false);
            
            //切换面板
            this->getChildByTag(TAG_CRYSTAL_PANEL)->setVisible(false);
            this->getChildByTag(TAG_GIFT_PANEL)->setVisible(true);

        }
    });

    
    //添加两种按钮——晶核
    btnCrystalTag=Button::create();
    btnCrystalTag->loadTextures("img_shop_btn_crystal_selected.png", "img_shop_btn_crystal_unselected.png");
    btnCrystalTag->cocos2d::Node::setPosition(SCREEN_WIDTH- 210, SCREEN_HEIGHT-220);
    btnCrystalTag->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            //
            btnGiftTag->loadTextureNormal("img_shop_btn_gift_selected.png");
            btnGiftTag->setEnabled(true);
            
            btnCrystalTag->loadTextureNormal("img_shop_btn_crystal_unselected.png");
            btnCrystalTag->setEnabled(false);
            
            //切换面板
            this->getChildByTag(TAG_GIFT_PANEL)->setVisible(false);
            this->getChildByTag(TAG_CRYSTAL_PANEL)->setVisible(true);        }
    });
    
    //初始化一下按钮状态
    btnGiftTag->loadTextureNormal("img_shop_btn_gift_unselected.png");
    //初始化一下水晶面板状态
    panelCrystalItems->setVisible(false);
    
    
    refreshData();
    
    this->addChild(panelGoldItems);
    this->addChild(panelCrystalItems);
    
    this->addChild(btnGiftTag);
    this->addChild(btnCrystalTag);
    
    
    this->addChild(bg,-1);
    this->addChild(btnBack);
    return true;
}


void ShopScene::refreshData()
{
    if(!txtMyGold){
        //我的能量
        int iMyGold=CommonData::getInstance()->getEnergy();
        std::string strMyGold=StringUtils::format("我的能量     %d",iMyGold);
        //我的能量——文本
        txtMyGold=Text::create();
        txtMyGold->setString(strMyGold);
        txtMyGold->setFontSize(35);
        txtMyGold->cocos2d::Node::setPosition(150, 70);
        //我的能量——图片
        auto iconGold=Sprite::create("img_shop_icon_power.png");
        iconGold->setPosition(164, 20);
        txtMyGold->addChild(iconGold);
        
        this->addChild(txtMyGold);
    }else{
        int iMyGold=CommonData::getInstance()->getEnergy();
        std::string strMyGold=StringUtils::format("我的能量     %d",iMyGold);
        txtMyGold->setString(strMyGold);
    }
    
    if(!txtMyCrystal){
        //我的晶核
        int iMyCrystal=CommonData::getInstance()->getCrystal();
        std::string strMyCrystal=StringUtils::format("我的晶核     %d",iMyCrystal);
        //我的晶核文本
        txtMyCrystal=Text::create();
        txtMyCrystal->setString(strMyCrystal);
        txtMyCrystal->setFontSize(35);
        txtMyCrystal->cocos2d::Node::setPosition(450, 70);
        //我的晶核——图片
        auto iconCrystal=Sprite::create("img_shop_icon_crystal.png");
        iconCrystal->setPosition(164, 20);
        txtMyCrystal->addChild(iconCrystal);
        
        this->addChild(txtMyCrystal);
    }else{
        int iMyCrystal=CommonData::getInstance()->getCrystal();
        std::string strMyCrystal=StringUtils::format("我的晶核     %d",iMyCrystal);
        txtMyCrystal->setString(strMyCrystal);
    }
    
}


//显示能量面板
Sprite *ShopScene::createGoldPanel()
{
    auto root=Sprite::create();
    auto items=Sprite::create("img_shop_content_gift.png");
    items->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2-60);
    root->addChild(items);
    
    //价钱按钮
    auto btnPrice1=ButtonFactory::createButtonPrice("img_price_6.png");
    auto btnPrice2=ButtonFactory::createButtonPrice("img_price_12.png");
    auto btnPrice3=ButtonFactory::createButtonPrice("img_price_18.png");
    
    btnPrice1->cocos2d::Node::setPosition(490, 660);
    btnPrice2->cocos2d::Node::setPosition(490, 430);
    btnPrice3->cocos2d::Node::setPosition(490, 200);
    
    //购买
    btnPrice1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买8");
            this->retain();
            feedId=POWER1;
            Payment::pay(POWER1,this);
        }
    });
    btnPrice2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买15");
            this->retain();
            feedId=POWER2;
            Payment::pay(POWER2,this);
        }
    });
    btnPrice3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买20");
            this->retain();
            feedId=POWER3;
            Payment::pay(POWER3,this);
        }
    });
    
    
    root->addChild(btnPrice1);
    root->addChild(btnPrice2);
    root->addChild(btnPrice3);
    return root;
}

//显示晶核面板
Sprite *ShopScene::createCrystalPanel()
{
    auto root=Sprite::create();
    auto items=Sprite::create("img_shop_content_crystal.png");
    items->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2-60);
    root->addChild(items);
    
    //价钱按钮
    auto btnPrice1=ButtonFactory::createButtonPrice("img_price_6.png");
    auto btnPrice2=ButtonFactory::createButtonPrice("img_price_12.png");
    auto btnPrice3=ButtonFactory::createButtonPrice("img_price_25.png");
    
    btnPrice1->cocos2d::Node::setPosition(490, 660);
    btnPrice2->cocos2d::Node::setPosition(490, 430);
    btnPrice3->cocos2d::Node::setPosition(490, 200);
    
    //购买
    btnPrice1->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买6");
            this->retain();
            feedId=CRYSTAL1;
            Payment::pay(CRYSTAL1,this);
        }
    });
    btnPrice2->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买12");
            this->retain();
            feedId=CRYSTAL2;
            Payment::pay(CRYSTAL2,this);
        }
    });
    btnPrice3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("购买20");
            this->retain();
            feedId=CRYSTAL3;
            Payment::pay(CRYSTAL3,this);
        }
    });
    
    root->addChild(btnPrice1);
    root->addChild(btnPrice2);
    root->addChild(btnPrice3);
    return root;
}



