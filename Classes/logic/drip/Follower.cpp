//
//  Follower.cpp
//  beymac
//
//  Created by wang on 15/4/24.
//
//

#include "Follower.h"
#include "Box.h"
#include "BeyMac.h"

Follower::Follower(RoleType type)
:root()
,number(1)
,master()
{
    roleType = type;
    init();
}

Follower::~Follower()
{

}

bool Follower::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    setRoleType(roleType);
    
    isEnabled = false;
    setLocalZOrder(4);
    
    return true;
}

void Follower::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void Follower::onExit()
{
    Node::onExit();
}

Follower* Follower::create(RoleType type)
{
    Follower *beyMac=new Follower(type);
    if (beyMac) {
        beyMac->autorelease();
        
    }
    else
    {
        delete beyMac;
        beyMac = NULL;
    }
    
    return beyMac;
}

void Follower::playLeftAction()
{
    //    auto amt=(Armature *)(this->getChildByTag(100));
    auto node=this->getChildByTag(100);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    
    if (amt) {
        amt->getAnimation()->play("left");
    }
}
void Follower::playRightAction()
{
    auto node=this->getChildByTag(100);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    if (amt) {
        amt->getAnimation()->play("right");
    }
}
void Follower::playStopAction()
{
    auto node=this->getChildByTag(100);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    
    if (amt) {
        amt->getAnimation()->play("normal");
    }
    
}

Size Follower::getContentSize()
{
    float s = getScale();
    Size size = Size(64*s, 88*s);
    return size;
}

void Follower::setRoleType(RoleType type)
{
    roleType = type;
    if (getChildByTag(100)) {
        removeChildByTag(100);
        root = NULL;
    }
    if (type == BeymacType) {
        // 大白
        
        root = CSLoader::createNode("Beymac.csb");
        maxSpeed = 5;
        curSpeed = maxSpeed;
        log("创建追随者大白");
        
    }
    else if (type == LaserType)
    {
        // 激光
        root = CSLoader::createNode("Laser.csb");
        maxSpeed = 5;
        curSpeed = maxSpeed;
        log("创建追随者激光");
    }
    else if (type == TomagoType)
    {
        // 神行姐
        root = CSLoader::createNode("Tomago.csb");
        maxSpeed = 5;
        curSpeed = maxSpeed;
        log("创建追随者神行");
    }
    
    root->setTag(100);
    this->addChild(root, 5);
}

void Follower::childUpdate(float delta,std::list<Box*> *boxlist)
{

}

// 是否在主人身边
bool Follower::isNearMaster()
{
    if (!master) {
        return false;
    }
    Box* b1 = getTopBoxByRow(myRow);
    Box* b2 = getTopBoxByRow(master->getMyRow());
    
    if (b1&&b2) {
        if (b1->getPositionY() == b2->getPositionY()) {
            if (abs(master->getPositionX() - getPositionX()) < (FOLLOWERDISTANCE_X*number)) {
                return true;
            }
        }
    }
    else if ((!b1)&&(!b2))
    {
        if (abs(master->getPositionX() - getPositionX()) < (FOLLOWERDISTANCE_X*number)) {
            return true;
        }
    }
    
    return false;
}

void Follower::setMaster(BaseRole* m)
{
    if (m) {
        master = m;
        maxSpeed = master->maxSpeed;
        curSpeed = maxSpeed;
    }
    
}