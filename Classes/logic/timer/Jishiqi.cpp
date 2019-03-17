//
//  Jishiqi.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/23.
//
//

#include "Jishiqi.h"


Jishiqi::Jishiqi()
{
    
}

Jishiqi::~Jishiqi()
{
    
}

Jishiqi* Jishiqi::createNode()
{
    auto node = new Jishiqi();
    if(node && node->init()) {
        node->autorelease();
        return node;
    }
    return nullptr;
}

bool Jishiqi::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void Jishiqi::initData()
{
    
    bg = Sprite::create("img_countdown_number_icon.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    label= LabelAtlas::create(String::createWithFormat("%d",0)->_string, "img_countdown_number.png", 27, 36, '0');
    label->setAnchorPoint(Vec2(0.5,0.5));
    label->setPosition(0,-13);
    addChild(label);
    
}




void Jishiqi::setBg(int type) {
   
    
    if (type == 1) {
        bg->setTexture("img_countdown_number_icon.png");
    }
    
    if (type == 2) {
        bg->setTexture("img_countdown_number_icon.png");
    }

}

void Jishiqi::setText(const std::string& text) {
    
    label->setString(text);
    
}

