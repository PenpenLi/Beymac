//
//  Tips.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/16.
//
//

#include "Tip.h"


Tip::Tip()
{
}

Tip::~Tip()
{
}

Tip* Tip::createMyTip() {
    auto node = new Tip();
    if(node && node->init()) {
        node->autorelease();
        return node;
    }
    return nullptr;
}

bool Tip::init()
{
    if (!Sprite::init() )
    {
        return false;
    }
    initData();
    return true;
}

void Tip::initData() {
    
    
    this->setTexture("img_warning.png");
    
    tipType = Sprite::create("img_box.png");
    tipType->setScale(0.7, 0.7);
    tipType->setPosition(Vec2(this->getContentSize().width/2,250));
    addChild(tipType);
    
    ActionInterval *out = FadeOut::create(0.5);
    ActionInterval *in = FadeIn::create(0.5);
    this->runAction(RepeatForever::create(Sequence::create(out,in, NULL)));
    tipType->runAction(RepeatForever::create(Sequence::create(out,in, NULL)));
}

void Tip::setTip(BoxType type) {
    if (type == BoxType::normalbox) {
        //添加箱子对象
        tipType->setTexture("img_box.png");
    }
    
    if (type == BoxType::normalbox2) {
        //添加箱子对象
        tipType->setTexture("img_box2.png");
    }
    
    if (type == BoxType::normalbox3) {
        //添加箱子对象
        tipType->setTexture("img_box3.png");
    }
    
    if (type == BoxType::normalbox4) {
        //添加箱子对象
        tipType->setTexture("img_box4.png");
    }
    
    if (type == BoxType::normalbox5) {
        //添加箱子对象
        tipType->setTexture("img_box5.png");
    }
    
    if (type == BoxType::dustbox) {
        tipType->setTexture("img_dust.png");
    }
    
    if (type == BoxType::hailbox) {
        tipType->setTexture("img_icestone.png");
    }
    
    if (type == BoxType::sinkbox) {
        tipType->setTexture("img_box.png");
    }
    
    if (type == BoxType::dripbox) {
        tipType->setTexture("img_water.png");
    }
    
    if (type == BoxType::sunbox) {
        tipType->setTexture("img_sun.png");
    }
    
    if (type == BoxType::bullet) {
        tipType->setTexture("img_boss1_stone.png");
    }
    
    if (type == BoxType::waterBall) {
        tipType->setTexture("img_water_ball.png");
    }
    
    if (type == BoxType::powerBall) {
        tipType->setTexture("img_power.png");
    }
    
}
