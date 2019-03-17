//
//  DottedLine.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/17.
//
//

#include "DottedLine.h"
#include "Macro.h"


DottedLine::DottedLine()
{
    
}

DottedLine::~DottedLine()
{
    
}

DottedLine* DottedLine::createNode()
{
    auto node = new DottedLine();
    if(node && node->init()) {
        node->autorelease();
        return node;
    }
    return nullptr;
}

bool DottedLine::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void DottedLine::initData()
{
    
//    SCREEN_WIDTH
    int num = SCREEN_WIDTH/(24+8);
    
    for (int i = 0; i<num; i++) {
        DrawNode *cell = DrawNode::create();
        Point rect[4]={*new Point(0,0),*new Point(0,6),*new Point(24,6),*new Point(24,0)};
        cell->setPosition(i*(24+8),0);
        Color4F color = {1, 1, 1, 0.4};
        cell->drawSolidPoly(rect, 4, color);
        
        addChild(cell);
    }
}