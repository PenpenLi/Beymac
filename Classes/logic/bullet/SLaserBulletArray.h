//
//  SLaserBulletArray.h
//  beymac
//
//  Created by mumu on 15/5/26.
//
//

#ifndef __beymac__SLaserBulletArray__
#define __beymac__SLaserBulletArray__

#include "cocos2d.h"
#include "ShortLaserBullet.h"

USING_NS_CC;
using namespace std;
class PlayScene;
class SLaserBulletArray :public Node
{
public:
    SLaserBulletArray(float halfWidth,float attack,float speed);
    virtual ~SLaserBulletArray();
//    CREATE_FUNC(SLaserBulletArray);
    static SLaserBulletArray* create(float halfWidth,float attack,float speed);
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static SLaserBulletArray* createLBlistByPlayer(float speed, float attack,Vec2 pos,PlayScene* parent );
    
    void onUpdate(float delta,std::list<Box*> *boxlist,Node* player);
    
    void removeBullets();
    
    void setIsUpdate(bool flag);
    
    void setBulletsPos(Vec2 pos);
    
    void setBoss(Monster* monster);
    
    void setSpeed(float speed);
    
    void playBombAction();
    void playFlyAction();
    
    void setSlowDown(bool flag);
    
public:
    list<ShortLaserBullet*> bulletList;
    
    float halfWidth;
    float attack;
    float speed;
};

#endif /* defined(__beymac__SLaserBulletArray__) */
