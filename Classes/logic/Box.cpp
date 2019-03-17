//
//  Box.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/4.
//
//

#include "Box.h"
#include "Macro.h"

Box::Box(BoxType t)
{
    this->type = t;
}

Box::~Box()
{
}

Box* Box::createMyBox(BoxType type) {
    auto sprite = new Box(type);
    if(sprite && sprite->init()) {
        sprite->autorelease();
        return sprite;
    }
    return nullptr;
}

bool Box::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void Box::initData()
{
    
//    DrawNode *cell = DrawNode::create();
//    Point rect[4]={*new Point(-GRID_RADIUS_SIZE,GRID_RADIUS_SIZE),*new Point(GRID_RADIUS_SIZE,GRID_RADIUS_SIZE),*new Point(GRID_RADIUS_SIZE,-GRID_RADIUS_SIZE),*new Point(-GRID_RADIUS_SIZE,-GRID_RADIUS_SIZE)};
//
//    Color4F color = {1, 0, 0, 1};
    
    //this->setTexture("img_box.png");
    if (type == BoxType::normalbox) {
        //添加箱子对象
        this->setTexture("img_box.png");
    }
    
    if (type == BoxType::normalbox2) {
        //添加箱子对象
        this->setTexture("img_box2.png");
    }
    
    if (type == BoxType::normalbox3) {
        //添加箱子对象
        this->setTexture("img_box3.png");
    }
    
    if (type == BoxType::normalbox4) {
        //添加箱子对象
        this->setTexture("img_box4.png");
    }
    
    if (type == BoxType::normalbox5) {
        //添加箱子对象
        this->setTexture("img_box5.png");
    }
    
    if (type == BoxType::dustbox) {
        this->setTexture("img_dust.png");
    }
    
    if (type == BoxType::hailbox) {
        this->setTexture("img_icestone.png");
    }
    
    if (type == BoxType::sinkbox) {
        this->setTexture("img_box.png");
    }
    
    if (type == BoxType::dripbox) {
        this->setTexture("img_water.png");
    }
    
    if (type == BoxType::sunbox) {
        this->setTexture("img_sun.png");
    }
    
    if (type == BoxType::bullet) {
        this->setTexture("img_boss1_stone.png");
    }
    
    if (type == BoxType::waterBall) {
        this->setTexture("img_water_ball.png");
    }
    
    if (type == BoxType::powerBall) {
        this->setTexture("img_power.png");
    }
    
//
//    cell->drawSolidPoly(rect, 4, color);
//    cell->drawPoly(rect, 4, true, color);
//    cell->setPosition(0,0);
//    addChild(cell);
}


void Box::slowbox() {
    auto sprite = Sprite::create("img_dust_dirty.png");
    sprite->setPosition(Vec2(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
    sprite->setTag(100);
    addChild(sprite);
}

void Box::removeSlowbox() {
    this->removeChildByTag(100);
}
