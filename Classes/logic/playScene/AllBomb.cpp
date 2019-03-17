//
//  AllBomb.cpp
//  BeyMac
//
//  Created by lingzerg on 15/5/13.
//
//

#include "AllBomb.h"
AllBomb::AllBomb()
{
    
}

AllBomb::~AllBomb()
{
    
}

AllBomb* AllBomb::createNode()
{
    auto node = AllBomb::create();
    return node;
}

bool AllBomb::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void AllBomb::initData()
{
    
}