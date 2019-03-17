//
//  ButtonFactory.cpp
//  beymac
//
//  Created by je on 4/27/15.
//
//

#include "ButtonFactory.h"

USING_NS_CC;
using namespace ui;

//圆形按钮
Button *ButtonFactory::createButtonCircle(const char *image)
{
    auto btnReturn=Button::create("img_btn_round.png");
    
    auto texture=Sprite::create(image);
    
    texture->setPosition(btnReturn->getContentSize().width/2, btnReturn->getContentSize().height/2);
    
    btnReturn->addChild(texture);
    
    return btnReturn;
}

//圆形绿色按钮
Button *ButtonFactory::createButtonCircleGreen(const char *image)
{
    auto btnReturn=Button::create("img_btn_round_green.png");
    
    auto texture=Sprite::create(image);
    
    texture->setPosition(btnReturn->getContentSize().width/2, btnReturn->getContentSize().height/2);
    
    btnReturn->addChild(texture);
    
    return btnReturn;
}

//价钱（购买按钮)
Button *ButtonFactory::createButtonPrice(const char *image)
{
    auto btnPrice=Button::create("img_shop_btn.png");
    
    auto sprNumber=Sprite::create(image);
    
    sprNumber->setPosition(btnPrice->getContentSize().width/2, btnPrice->getContentSize().height/2);
    
    btnPrice->addChild(sprNumber);
    
    return btnPrice;
}