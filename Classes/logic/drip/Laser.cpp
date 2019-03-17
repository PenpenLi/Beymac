//
//  Laser.cpp
//  beymac
//
//  Created by wang on 15/4/21.
//
//

#include "Laser.h"

Laser::Laser()
{
    
    init();
}

Laser::~Laser()
{

}

bool Laser::init()
{
    if (!Node::init())
    {
        return false;
    }
    maxSpeed = 5;
    curSpeed = maxSpeed;
    roleType = LaserType;
    startAction(stopActionType);
    setLocalZOrder(5);
    return true;
}

void Laser::onEnter()
{
    Node::onEnter();
}

void Laser::onExit()
{
    Node::onExit();
}

Laser* Laser::create()
{
    Laser *role=new Laser();
    if (role) {
        role->autorelease();
    }
    else
    {
        delete role;
        role = NULL;
    }
    
    return role;
}

void Laser::playLeftAction()
{
    
}
void Laser::playRightAction()
{
    
}
void Laser::playStopAction()
{
    
}
