//
//  Health.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/18.
//
//

#include "Health.h"

Health::Health()
{
    
}

Health::~Health()
{
    
}

Health* Health::createNode()
{
    auto node = new Health();
    if(node && node->init()) {
        node->autorelease();
        return node;
    }
    return nullptr;
}

Health* Health::createNode(const char *imageName,const char *background)
{
    auto node = new Health();
    if(node && node->init(imageName,background)) {
        node->autorelease();
        return node;
    }
    return nullptr;
}

bool Health::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    initData();
    return true;
}

bool Health::init(const char *imageName,const char *background)
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    initData(imageName,background);
    return true;
}

void Health::initData(const char *imageName,const char *background) {
    Sprite *bg = Sprite::create(background);
    bg->setPosition(0,0);
    addChild(bg);
    
    Sprite *loading = Sprite::create(imageName);
    mypro = ProgressTimer::create(loading);
    mypro->setPosition(0, 0);
    mypro->setType(ProgressTimer::Type::BAR);
    mypro->setMidpoint(Vec2(0,0));
    mypro->setBarChangeRate(Vec2(1,0));
    
    mypro->setPercentage(33);
    addChild(mypro);
}


#pragma mark - initData
void Health::initData()
{
    initData("img_life.png","img_life_case.png");
}

void Health::hideHealth() {
    this->setVisible(false);
}

void Health::showHealth() {
    this->setVisible(true);
}

void Health::setValue(int value) {
    if (value > 90) {
        value = 100;
    }
    mypro->setPercentage(value);
}


void Health::setOriginHealth(float originHealth) {
    this->originHealth = originHealth;
}

void Health::addHealth(float health) {
    currentHealth += health;
    if (currentHealth < 0) {
        currentHealth =0;
    }
    mypro->setPercentage(currentHealth/originHealth*100);
}

void Health::setHealth(float currentHealth) {
    
    if (currentHealth > originHealth) {
        currentHealth = originHealth;
    }
    
    if (currentHealth < 0) {
        currentHealth =0;
    }
    this->currentHealth = currentHealth;
    log("%f",currentHealth/originHealth);
    mypro->setPercentage(currentHealth/originHealth*100);

    
}
float Health::getOriginHealth() {
    return originHealth;
}

float Health::getHealth() {
    return this->currentHealth;
}



//
//
//void Health::whitebar() {
//    DrawNode *leftCircle = DrawNode::create();
//    Color4F color = {1, 1, 1, 1};
//    
//    
//    
//    ////参数依次为：圆心、半径、角度、段数、X轴缩放系数、Y轴缩放系数
//    leftCircle->drawSolidCircle(*new Point(0,0), r, CC_DEGREES_TO_RADIANS(90), 1440, color);
//    leftCircle->setPosition(-(width-height)/2,0);
//    addChild(leftCircle);
//    
//    DrawNode *rightCircle = DrawNode::create();
//    ////参数依次为：圆心、半径、角度、段数、X轴缩放系数、Y轴缩放系数
//    rightCircle->drawSolidCircle(*new Point(0,0), r, CC_DEGREES_TO_RADIANS(90), 1440, color);
//    rightCircle->setPosition((width-height)/2,0);
//    addChild(rightCircle);
//    
//    
//    
//    DrawNode *cube = DrawNode::create();
//    Point rect[4]={*new Point(-(width-height)/2,-r),*new Point(-(width-height)/2,r),*new Point((width-height)/2,r),*new Point((width-height)/2,-r)};
//    cube->setPosition(0,0);
//    cube->drawSolidPoly(rect, 4, color);
//    addChild(cube);
//}
//
//void Health::shadow() {
//    DrawNode *leftCircle = DrawNode::create();
//    Color4F color = {0.2, 0.2, 0.2, 1};
//    
//    ////参数依次为：圆心、半径、角度、段数、X轴缩放系数、Y轴缩放系数
//    leftCircle->drawSolidCircle(*new Point(0,0), 21, CC_DEGREES_TO_RADIANS(90), 1440, color);
//    leftCircle->setPosition(-(width-height)/2,-4);
//    addChild(leftCircle);
//    
//    DrawNode *rightCircle = DrawNode::create();
//    ////参数依次为：圆心、半径、角度、段数、X轴缩放系数、Y轴缩放系数
//    rightCircle->drawSolidCircle(*new Point(0,0), 21, CC_DEGREES_TO_RADIANS(90), 1440, color);
//    rightCircle->setPosition((width-height)/2,-4);
//    addChild(rightCircle);
//    
//    DrawNode *cube = DrawNode::create();
//    Point rect[4]={*new Point(-(width-height)/2+4,-r),*new Point(-(width-height)/2+4,r),*new Point((width-height)/2-4,r),*new Point((width-height)/2-4,-r)};
////    Point rect[4]={*new Point(-70,-21),*new Point(-70,21),*new Point(70,21),*new Point(70,-21)};
//    cube->setPosition(4,-4);
//    cube->drawSolidPoly(rect, 4, color);
//    addChild(cube);
//}
