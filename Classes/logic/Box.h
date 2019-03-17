//
//  Box.h
//  WaterWars
//
//  Created by lingzerg on 15/3/4.
//
//

#ifndef __WaterWars__Box__
#define __WaterWars__Box__

#include "cocos2d.h"

USING_NS_CC;

#define GRID_RADIUS_SIZE 40.0   //箱子半径

enum BoxType
{
    normalbox,     //普通的箱子
    normalbox2,
    normalbox3,
    normalbox4,
    normalbox5,
    virusesBox,     //减速箱子,水滴走上去会减速
    sinkbox,       //已经越过死亡线的箱子
    hailbox,       //冰雹 减血,如果不减血,则没有碰主角, 增加一个箱子
    dustbox,       //灰尘 减血 落地消失
    dripbox,       //水滴 加血用
    sunbox,         //太阳
    bullet,         //boss战,子弹
    waterBall,       //boss战,水球
    goldBall,        //金币
    helmetBall,     //钢盔
    invincibleBall, //无敌
    powerBall,      //掉能量块
    TimeSlowsDown  //时间减慢
};

class Box : public Sprite
{
public:
    bool isSlow = false;
    bool isDestroy = false;
    BoxType type = normalbox;  // 什么类型的box
    bool isDead = false;        //是否还存在活动
    float targetPositionY = 0;  //垂直目标坐标
    int track = 0 ;             //所属轨道编号
    
public :
    Box(BoxType type);
    ~Box();
    static Box* createMyBox(BoxType type);
    virtual bool init();
    
    void slowbox();
    void removeSlowbox();
    
private:
    void initData();
};

#endif /* defined(__WaterWars__Box__) */
