//
//  BaseBullet.h
//  beymac
//
//  Created by wang on 15/5/13.
//
//

#ifndef __beymac__BaseBullet__
#define __beymac__BaseBullet__

#include "cocos2d.h"

USING_NS_CC;

// 得到列数
int getRow( float x );

enum BaseBulletType
{
    BulletType_NULL,
    BulletType_ball,
    BulletType_shortLaser,
};

class Box;
class BaseBullet;
class PlayScene;
class BaseBulletDelegate
{
public:
    
    // 激光条接触 flag为1时为碰到玩家，0为碰到砖块或下线,2为碰到boss
    virtual void baseBulletDelegateContact(BaseBullet* node, int flag, Box* box) = 0;
    // 激光球接触 flag为1时为碰到玩家，0为碰到下线
    virtual void baseBulletDelegateContactBall(BaseBullet* node, int flag) = 0;
    // 伽马射线动作播完
    virtual void baseBulletDelegateSLaserActionFinish()=0;
};

class BaseBullet :public Node
{
public:
    BaseBullet();
    virtual ~BaseBullet();
    virtual bool init();
    CREATE_FUNC(BaseBullet);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    // 爆炸效果
    void boxBangAction(float x, float y);
    void boxBangActionIce(float x, float y);
public:
    CC_SYNTHESIZE(PlayScene*, delegate, Delegate);
    CC_SYNTHESIZE(float, attack, Attack);
    CC_SYNTHESIZE(BaseBulletType, type, Type);
};

#endif /* defined(__beymac__BaseBullet__) */
