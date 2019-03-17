//
//  Tamago.cpp
//  beymac
//
//  Created by wang on 15/4/21.
//
//

#include "Tomago.h"

Tomago::Tomago()
{
    
    init();
}

Tomago::~Tomago()
{

}

bool Tomago::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    maxSpeed = 8;
    curSpeed = maxSpeed;
    roleType = TomagoType;
    startAction(stopActionType);
    setLocalZOrder(5);
    return true;
}

void Tomago::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void Tomago::onExit()
{
    Node::onExit();
}

Tomago* Tomago::create()
{
    Tomago *role=new Tomago();
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

void Tomago::playLeftAction()
{
    
}
void Tomago::playRightAction()
{
    
}
void Tomago::playStopAction()
{
    
}