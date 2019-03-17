//
//  Drip.h
//  TestA
//
//  Created by je on 3/5/15.
//
//

#ifndef __TestA__Drip__
#define __TestA__Drip__

#include "cocos2d.h"
#include "BaseRole.h"

#include "Follower.h"

USING_NS_CC;
using namespace cocostudio;

#define FOLLOWERDISTANCE_X 50
#define FOLLOWERDISTANCE_Y 30

class BeyMac:public BaseRole
{
public:
    BeyMac();
    virtual ~BeyMac();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static BeyMac *create();

    virtual void playLeftAction() ;
    virtual void playRightAction() ;
    virtual void playStopAction() ;
    virtual Size getContentSize();
    
    virtual void setRoleType(RoleType type);
    // 创建跟随者
    void createfollowers();
    // 测试用
    void createfollowers(int num);
    void removeFollowers();
    
    // 界面刷新
    virtual void childUpdate(float delta,std::list<Box*> *boxlist);
    virtual void childOnTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void childOnTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    
    //初始化属性：速度攻击力
    void initAttribute(RoleType type);
    // 更换角色
    void changeRole();
    // 穿上背包
    void takeBag(bool flag);
    bool getIsHaveBag() { return haveBag; }
    
private:
    
private:
    Node* root;
    
    list<Follower*> followerslist;
    // 在队列中的位置
    int listPosition;
    
    bool haveBag;
    
};

#endif /* defined(__TestA__Drip__) */