//
//  BasePlayer.h
//  WaterWars
//
//  Created by wang on 15/4/20.
//
//

#ifndef __WaterWars__BasePlayer__
#define __WaterWars__BasePlayer__

#include "cocos2d.h"
#include "cocosGUI.h"
#include <cocostudio/CocoStudio.h>

#define GRID_SIZE 80.0          //箱子如果是一个矩形的大小
#define GRID_RADIUS_SIZE 40.0   //箱子半径
#define DEAD_LINE 256
#define CELL_HORIZONTAL_SIZE 8  //水平多少行
#define SMOKE_TIME 0.1          //移动灰尘出现间隔
#define FALL_SPEED 15
#define FROZEN_CLICKNUMBER 5
#define MAXLIFE 3

USING_NS_CC;
using namespace std;
using namespace ui;

enum DripDirection
{
    dir_stop,
    dir_up,
    dir_down,
    dir_left,
    dir_right,
};

enum CollisionState
{
    noCollisionState,   // 没有碰撞状态
    boxState,           // 普通箱子，一砸就死
    hailState,          // 冰雹，碰到掉一滴血
    dustState,          // 灰尘，减速50%
    dripState,          // 水滴，一碰加一滴血
    sunState,           // 太阳，一碰掉两滴血
    bulletState,        // boss子弹
    waterBallState,      // 水炮
    goldBallState,           //金币
    helmetBallState,         //钢盔
    invincibleBallState,     //无敌
    TimeSlowsDownState,       //时间减慢
    VirusesBoxState,         // 沼泽箱子
    PowerBallState          // 能量箱子
};

enum ActionType
{
    walkLeftActionType,        // 左运动
    walkRightActionType,        // 右运动
    stopActionType,           // 停止
    boxDeadActionType,         // 死亡:箱子砸死
    otherDeadActionType,         // 死亡:其他死亡
    
};

enum CollisionType
{
    noCollisionType,           // 无碰撞
    UpCollisionType,           // 上碰撞
    DownCollisionType,         // 下碰撞
    LeftCollisionType,         // 左碰撞
    RightCollisionType,        // 右碰撞
};

enum RoleType
{
    BeymacType,             // 大白
    LaserType,              // 激光
    TomagoType,             // 神行姐
};

class Box;
class BaseRole;
class PlayScene;
class BaseRoleDelegate
{
public:
    
    // 0是死亡
    virtual void dripDelegateDead(BaseRole* node, int num) = 0;
    // 消除碰到的箱子
    virtual void dripDelegateRemoveHailBox(BaseRole* node, Box* box) = 0;
    // 碰到伞
    virtual void dripDelegateUmbrella(BaseRole* node) = 0;
    // 碰到水炮
    virtual void dripDelegateWaterBall(BaseRole* node,Box* box) = 0;
    // 碰到灰尘
    virtual void dripDelegatevirusesBox(BaseRole* node,int track) = 0;
    // 碰到能量
    virtual void dripDelegatePowerBox(BaseRole* node,Box* box) = 0;
    // 喷气背包动作完成回调
    virtual void dripDelegateBagEffectFinish()=0;
};


class BaseRole:public Node
{
public:
    BaseRole();
    virtual ~BaseRole();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    // 界面刷新
    virtual void onUpdate(float delta,std::list<Box*> *boxlist);
    // 向左移动
    void moveLeft();
    // 向右移动
    void moveRight();
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    bool onContactBegin(PhysicsContact& contact, Box* box);
    
    // 设置伞状态
    void setUmbrella(bool flag);
    bool getUmbrella();
    
    // 设置无敌状态
    void setInvincible(bool flag);
    bool getInvincible();
    // 设置金钟罩颜色
    void setSafeCoverColor(Node* image,int life);
    
    // 播动画
    virtual void startAction( ActionType type );
    virtual void playLeftAction() = 0;
    virtual void playRightAction() = 0;
    virtual void playStopAction() = 0;
    virtual void playBoxDieAction();
    virtual void playOtherDieAction();
    
    int getMyRow();
    // 设置减速效果
    void setReduceSpeedEffect( bool flag );
    
    // 获得水滴所在列
    int getRowOfDrip( float x );
    // 找出某列中最高box
    Box* getTopBoxByRow(int row);
    // 下落
    virtual void falling(float delta,std::list<Box*> *boxlist);
    // 设置相对位置
    void setDripPosition(float x, float y);
    // 碰撞检测
    bool collisionDetection();
    // 碰到箱子状态 type:箱子类型
    void collisionState(Box* box);
    // 水滴死亡
    void dripDead();
    // 粒子效果
    void showDripParticleEffect(Vec2 position,Node* node);
    // 显示加血减血图片
    void showScorePic(int score,Vec2 pos,Node* node);
    void removeScorePic(Node* node);
    
    // 移动时灰尘效果
    void showMoveSmoke(Vec2 pos,Node* node);
    void removeSmoke(Node* node);
    
    // 两个物理的碰撞状态(相对于第一个node)
    CollisionType getTwoNodeCollisionState(Node* node1, Node* node2);
    // 获取类型
    RoleType getRoleType();
    virtual void setRoleType(RoleType type);
    float getRoleAttack();
    
    virtual Size getContentSize();
    
    // 子类需要添加的update和touch
    virtual void childUpdate(float delta,std::list<Box*> *boxlist);
    virtual void childOnTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void childOnTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    
    // 设置冰冻状态
    void setFrozen(bool flag);
    void showFrozenBtn();
    void hideFrozenBtn();
    
    // 检测金钟罩
    void checkSafetyCover(int life);
    
    // 检测是否被炸弹炸到,type参数：0为炸弹 1为激光球 2为短激光,return:true为炸到主角，false为没有炸到
    bool checkIsHurtByBomb(Vec2 pos, int attack = 1, int type = 0);
    
    // 爆炸效果
    void boxBangAction(float x, float y);
    
public:
    float curSpeed;
    CC_SYNTHESIZE(float, maxAttack, MaxAttack);
    
protected:
    
    std::list<Box*> *boxlist;
    // 速度
    float rate;
    
    // 减速累计时间
    float decTime;
    bool isReduceSpeed;
    // 是否上移
    bool isUp;
    // 是否下降
    bool isDown;
    // 所在列数
    int myRow;
    
    // 血量
    CC_SYNTHESIZE(int, blood, Blood);
    // 是否死亡
    CC_SYNTHESIZE(bool, isDead, IsDead);
    
    Box* box;
    // 方向
    DripDirection direction;
    
    // 多点触屏id
    map<int , DripDirection> touchMap;
    
    CC_SYNTHESIZE(BaseRoleDelegate*, delegate, Delegate);
    
    // 状态
    CollisionState curState;
    CollisionState nextState;
    
    // 是否在地上
    CC_SYNTHESIZE(bool, isOnGround, IsOnGround);
    
    // 是否有伞
    bool isUmbrella;
    
    // 是否无敌
    bool isInvincible;
    
    CC_SYNTHESIZE(PlayScene*, playScene, PlayScene);
    
    bool isYaBian;
    
    bool isSmoke;
    float smokeTme;
    
    float maxSpeed;

    float allDecTime;
    RoleType roleType;
    
    // 是否可以被箱子砸到
    CC_SYNTHESIZE(bool, isEnabled, IsEnabled);

    // 是否被冰冻
    CC_SYNTHESIZE(bool, isFrozen, IsFrozen);
    // 冰冻按钮点击数
    int frozenClickCount;
    
    // 金钟罩生命数
    int safetyCoverLife ;
    
    CC_SYNTHESIZE(float, invincibleLastTime, InvincibleLastTime)
    float invincibleTotalTime;
    
    // 是否可以被炸到
    CC_SYNTHESIZE(bool, isCanBeContact, IsCanBeContact);
    float isCanBeContactLastTime;
    float isCanBeContactTotalTime;

};

#endif /* defined(__WaterWars__BasePlayer__) */
