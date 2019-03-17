//
//  ShortLaserBullet.h
//  beymac
//
//  Created by wang on 15/5/12.
//
//

#ifndef __beymac__ShortLaserBullet__
#define __beymac__ShortLaserBullet__

#include "cocos2d.h"
#include "BaseBullet.h"

USING_NS_CC;
using namespace std;

#define SLASER_HALFLENGTH 30


class Monster;
class Box;
class ShortLaserBullet :public BaseBullet
{
public:
    ShortLaserBullet(float speed, float attack,int whoShoot);
    virtual ~ShortLaserBullet();
    virtual bool init();
//    CREATE_FUNC(ShortLaserBullet);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    // 参数whoshoot: 0为大白发射，1为bossfashe
    static ShortLaserBullet* createSLBullet(float speed, float attack,int whoShoot = 0);
    
    void onUpdate(float delta,std::list<Box*> *boxlist,Node* player);
    
    void removeBullet();
    // 得到当前列最高的箱子
    Box* getTopBoxByRow(int row ,std::list<Box*> *boxlist);
    //
    void setIsUpdate(bool flag);
    bool getIsUpdate() { return isUpdate; }
    
    void playBombAction();
    void playFlyAction();
    
    // 时间减缓
    void setSlowDown(bool flag);
    
private:
    
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, maxSpeed, MaxSpeed);
    CC_SYNTHESIZE(DrawNode*, bullet, Bullet);
    bool isUpdate;
//    MotionStreak* streak;
//    Node* parent;
    // boss发射的子弹
    Sprite* bulletImage;
    // 英雄发射的子弹
    Node* bulletNode;
    CC_SYNTHESIZE(int, whoShoot, WhoShoot);
    
    CC_SYNTHESIZE(Monster*, boss, Boss);
    
    CC_SYNTHESIZE(float, laserHalfWidth, LaserHalfWidth);
};

#endif /* defined(__beymac__ShortLaserBullet__) */
