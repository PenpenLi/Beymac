//
//  LaserBullet.h
//  beymac
//
//  Created by wang on 15/5/11.
//
//

#ifndef __beymac__LaserBullet__
#define __beymac__LaserBullet__

#include "cocos2d.h"
#include "BaseBullet.h"

USING_NS_CC;

class Box;
class LaserBullet :public BaseBullet
{
public:
    LaserBullet(float speedX,float speedY, float attack);
    virtual ~LaserBullet();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();

    static LaserBullet* create(float speedX,float speedY, float attack);
    
    void onUpdate(float delta,Node* player);
    
    // 碰到东西爆炸 type :0为地板  1为英雄
    void contactSomething(Node* player,int type = 0);
    
    void setType(int type);
    int getType() { return type; }
    
    // 时间减缓
    void setSlowDown(bool flag);
    
private:
    CC_SYNTHESIZE(float, speedX, SpeedX);
    CC_SYNTHESIZE(float, speedY, SpeedY);
    CC_SYNTHESIZE(float, maxSpeedX, MaxSpeedX);
    CC_SYNTHESIZE(float, maxSpeedY, MaxSpeedY);
    CC_SYNTHESIZE(bool, isShoot, IsShoot);
    CC_SYNTHESIZE(Sprite*, image, Image);
    CC_SYNTHESIZE(bool, isUpdate, IsUpdate);
    // 是否可以碰撞
    CC_SYNTHESIZE(bool, isContact, IsContact);
    
    // 反弹球材质：1 冰冻 2 爆炸
    int ballType;
};

#endif /* defined(__beymac__LaserBullet__) */
