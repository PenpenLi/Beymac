//
//  RunnerAnimation.h
//  beymac
//
//  Created by je on 6/10/15.
//
//

#ifndef __beymac__RunnerAnimation__
#define __beymac__RunnerAnimation__

#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>
#include "BeyMac.h"

USING_NS_CC;
using namespace cocostudio;


class RunnerAnimation:public Node{
public:
    
    static RunnerAnimation *create(RoleType type);
    
    virtual bool init();
    
    //冲击波出现
    void fall();
    
    //人物出现
    void showRole();
    
    //左右跑
    void run();
    
    void reset();
    
private:
    
    Armature *amt;
    
    Vec2 pos;
    
    RoleType roleType;
    
    BeyMac *runner;
};



#endif /* defined(__beymac__RunnerAnimation__) */
