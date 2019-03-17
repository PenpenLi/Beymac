//
//  Follower.h
//  beymac
//
//  Created by wang on 15/4/24.
//
//

#ifndef __beymac__Follower__
#define __beymac__Follower__

#include "cocos2d.h"
#include "BaseRole.h"
#include <cocostudio/CocoStudio.h>

USING_NS_CC;
using namespace cocostudio;

class Follower :public BaseRole
{
public:
    Follower(RoleType type);
    virtual ~Follower();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static Follower *create(RoleType type);
    
    virtual void playLeftAction() ;
    virtual void playRightAction() ;
    virtual void playStopAction() ;
    virtual Size getContentSize();
    
    virtual void setRoleType(RoleType type);
    virtual void childUpdate(float delta,std::list<Box*> *boxlist);
    
    // 是否在主人身边
    bool isNearMaster();
    
    void setMaster(BaseRole* master);
    
private:
    Node* root;
    
    CC_SYNTHESIZE(int, number, Number);
    
    BaseRole* master;
};

#endif /* defined(__beymac__Follower__) */
