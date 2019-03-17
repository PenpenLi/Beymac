//
//  BasePlayer.cpp
//  WaterWars
//
//  Created by wang on 15/4/20.
//
//

#include "BaseRole.h"

#include "math.h"
#include "Macro.h"
#include "Box.h"
#include "PlayScene.h"

//int _boxes[100][2];



#define UMBRELLA_TAG 101
#define INVINCIBLE_TAG 102
#define SWEAT_TAG 103
#define REDUCESPEED 104
#define FROZEN_TAG 105
#define FROZEN_BTN_TAG 206

BaseRole::BaseRole()
:rate(0)
,isUp(false)
,isDown(false)
//,upRow(0)
,blood(1)
,isDead(false)
,myRow(0)
,direction(dir_stop)
,delegate()
,decTime(0)
,isReduceSpeed(false)
,isOnGround(true)
,isUmbrella(false)
,isInvincible(false)
,playScene()
,isYaBian(false)
,isSmoke(false)
,smokeTme(0)
,maxSpeed(5)
,allDecTime(8)
,isEnabled(true)
,frozenClickCount(0)
,safetyCoverLife(0)
,isFrozen(false)
,invincibleLastTime(0.0)
,invincibleTotalTime(0.0)
,isCanBeContact(true)
,isCanBeContactLastTime(0)
,isCanBeContactTotalTime(0.3)
{
    curSpeed = maxSpeed;
    init();
    
}
BaseRole::~BaseRole()
{
    
}
bool BaseRole::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    setLocalZOrder(5);
    
    return true;
}

void BaseRole::onEnter()
{
    Node::onEnter();
}
void BaseRole::onExit()
{
    Node::onExit();
}

void BaseRole::onUpdate(float delta,std::list<Box*> *boxlist)
{
    if (isDead) {
        return;
    }
    
    // 金钟罩
    if (isInvincible) {
        invincibleLastTime = invincibleLastTime - delta;
        if (invincibleLastTime <= 0) {
            setInvincible(false);
            invincibleLastTime = 0;
        }
    }
    
    // 安全期
    if (!isCanBeContact) {
        isCanBeContactLastTime = isCanBeContactLastTime - delta;
        if (isCanBeContactLastTime <= 0) {
            setIsCanBeContact(true);
            isCanBeContactLastTime = 0;
        }
    }
    
    
    // 水滴减速
    if (isReduceSpeed) {
//        decTime += delta;
//        if (decTime >= allDecTime) {
//            isReduceSpeed = false;
//            decTime = 0;
//            curSpeed = maxSpeed;
//            setReduceSpeedEffect(false);
//            //            log("====== 减速完成");
//        }
        
        curSpeed = maxSpeed*0.4;
    }
    else
    {
        curSpeed = maxSpeed;
        if (direction == dir_left) {
            rate = -curSpeed;
        }
        else if (direction == dir_right)
        {
            rate = curSpeed;
        }
        else
        {
            rate = 0;
        }
    }
    
    this->boxlist = boxlist;

    collisionDetection();
    
    if (!isFrozen) {
        if(rate!=0)
        {
            if((rate<0&&(getPosition().x>getContentSize().width/2))||(rate>0&&(getPosition().x<SCREEN_WIDTH-(getContentSize().width/2))))
            {
                
                if(rate<0)
                {
                    moveLeft();
                    
                }else if(rate>0)
                {
                    moveRight();
                    
                }
            }
        }
    }
    
    
    myRow = getRowOfDrip(getPositionX());

    // 下落
    falling(delta,boxlist);
    
    if (this->getPositionY() - getContentSize().height/2 < DEAD_LINE) {
        log("低于dead line啦！！！！");
        this->setPositionY(getContentSize().height/2+DEAD_LINE);
    }
    
    childUpdate(delta,boxlist);
    
//    if (isSmoke) {
//        smokeTme += delta;
//        if (smokeTme >= SMOKE_TIME) {
//            if (direction == dir_left) {
//                if (isUp) {
//                    showMoveSmoke(getPosition()+Vec2(-20, -30), playScene);
//                }
//                else
//                {
//                    showMoveSmoke(getPosition()+Vec2(20, -30), playScene);
//                }
//                
//            }
//            else if (direction == dir_right)
//            {
//                if (isUp) {
//                    showMoveSmoke(getPosition()+Vec2(20, -30), playScene);
//                }
//                else
//                {
//                    showMoveSmoke(getPosition()+Vec2(-20, -30), playScene);
//                }
//            }
//            smokeTme = 0;
//        }
//    }
//    else
//    {
//        smokeTme = 0;
//    }
}

//左移
void BaseRole::moveLeft()
{
    if (isUp) {
        //        log("up");
        // 上移
        if (direction == dir_stop) {
            isUp = false;
//            setRotation(0);
        }
        if (isDown) {
            //            log("down");
            return;
        }
        isOnGround = false;
//        setRotation(90);
        
        Box* b = getTopBoxByRow(myRow-1);
        
        if (!b) {
            return;
        }
        if ( b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2-10 > (int)getPositionY()) {
            if (b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2-10 + curSpeed < (int)getPositionY()) {
                this->setPosition(Vec2(getPosition().x,  b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2));
                setDripPosition(-GRID_RADIUS_SIZE-1, 0);
                isUp = false;
//                setRotation(0);
                rate = -curSpeed;
                myRow = getRowOfDrip(getPositionX());
                isOnGround = true;
            }
            else
            {
                setDripPosition(0, curSpeed);
                isOnGround = false;
                isReduceSpeed = false;
            }
            
        }
        else
        {
            setPosition(Vec2(getPosition().x,  b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2));
            setDripPosition(-GRID_RADIUS_SIZE-1, 0);
            isUp = false;
//            setRotation(0);
            rate = -curSpeed;
            myRow = getRowOfDrip(getPositionX());
            isOnGround = true;
        }
    }
    else
    {
        // 不靠墙
        if (myRow + 1 <= 8 && myRow > 0) {
            Box* b = getTopBoxByRow(myRow);
            
            if (b && b->getPositionY() + GRID_RADIUS_SIZE < DEAD_LINE) {
                if (b && b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2 > (int)getPositionY())
                {
                    setDripPosition(rate, 0);
                    setPositionY(b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2);
                    isOnGround = true;
//                    showMoveSmoke(getPosition()+Vec2(0,-20), playScene);
                }
                else
                {
                    setDripPosition(rate, 0);
                    isOnGround = true;
//                    showMoveSmoke(getPosition()+Vec2(0,-20), playScene);
                }
            }
            else
            {
                if ( b && b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2 < (int)getPositionY()) {
                    
                    //                isDown = true;
                }
                else if (b && b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2 > (int)getPositionY())
                {
                    setDripPosition(rate, 0);
//                    log("myrow = %d", myRow);
//                    setPositionY(b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2);
                    isOnGround = true;
                }
                else
                {
                    setDripPosition(rate, 0);
                    isOnGround = true;
                }
                
            }
            
        }
        else
        {
            setDripPosition(rate, 0);
            isOnGround = true;
        }
        
    }
    
}

//右移
void BaseRole::moveRight()
{
    if (isUp) {
        //        log("up");
        // 上移
        
        if (direction == dir_stop) {
            isUp = false;
//            setRotation(0);
        }
        if (isDown) {
            //            log("down");
            return;
        }
        isOnGround = false;
//        setRotation(270);
        
        Box* b = getTopBoxByRow(myRow+1);
        if (!b) {
            return;
        }
        
        if (b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2 > (int)getPositionY()) {
            if (b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2 + curSpeed <= (int)getPositionY()) {
                this->setPosition(Vec2(getPosition().x,  b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2));
                setDripPosition(GRID_RADIUS_SIZE+1, 0);
                isUp = false;
//                setRotation(0);
                rate = curSpeed;
                myRow = getRowOfDrip(getPositionX());
                isOnGround = true;
            }
            else
            {
                setDripPosition(0, curSpeed);
                isOnGround = false;
                isReduceSpeed = false;
                
                
            }
            
        }
        else
        {
            
            setPositionY(b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2);
            setDripPosition(GRID_RADIUS_SIZE+1, 0);
            isUp = false;
//            setRotation(0);
            rate = curSpeed;
            myRow = getRowOfDrip(getPositionX());
            isOnGround = true;
        }
    }
    else
    {
        // 不靠墙
        if (myRow + 1 <= 8 && myRow > 0) {
            
            Box* b = getTopBoxByRow(myRow);
            
            if (b && b->getPositionY() + GRID_SIZE/2 < DEAD_LINE) {
                if (b && b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2 > (int)getPositionY())
                {
                    setDripPosition(rate, 0);
                    setPositionY(b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2);
                    isOnGround = true;
                }
                else
                {
                    setDripPosition(rate, 0);
                    isOnGround = true;
                }
            }
            else
            {
                if ( b && b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2 < (int)getPositionY()) {
                    
                    //                isDown = true;
                    //                upRow =  b->track;
                }
                else if (b && b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2 > (int)getPositionY())
                {
                    setDripPosition(rate, 0);
//                    log("myrow = %d", myRow);
//                    setPositionY(b->getPositionY() + GRID_RADIUS_SIZE + getContentSize().height/2);
                    isOnGround = true;
                }
                else
                {
                    setDripPosition(rate, 0);
                    isOnGround = true;
                }
            }
            
            
        }
        else
        {
            setDripPosition(rate, 0);
            isOnGround = true;
        }
        
    }
    
}

void BaseRole::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event *event)
{
    
    //    auto target=static_cast<Sprite *>(event->getCurrentTarget());
    //    Point pos=target->convertToNodeSpace(touches[0]->getLocation());
    //    log("touch id: %d ", touches[0]->getID());
    
    if (isDead) {
        return;
    }
    if (isFrozen) {
        rate=0;//停止
        direction = dir_stop;
        startAction(stopActionType);
        return;
    }
    
    
    
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocation();
        
        if(location.x <= SCREEN_WIDTH/2 )
        {
            touchMap[item->getID()] = dir_left;
            
        }else{
            touchMap[item->getID()] = dir_right;
        }
    }
    
//    log("touches size: %d", (int)touchMap.size());
    
    if (touchMap.size() == 1) {
        // 触摸点只有一个
        map<int, DripDirection>::iterator it;
        it=touchMap.begin();
        direction =it->second;
        if (direction == dir_left) {
            rate = -curSpeed;
//            setFlippedX(false);
            startAction(walkLeftActionType);
        }
        else if (direction == dir_right) {
            rate = curSpeed;
//            setFlippedX(true);
            startAction(walkRightActionType);
        }
        isSmoke = true;
    }
    else
    {
        isUp = false;
//        setRotation(0);
        direction = dir_stop;
        startAction(stopActionType);
        rate = 0;
        
        isSmoke = false;
    }
    
    childOnTouchesBegan(touches, event);
    
}

void BaseRole::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event *event)
{
    //    log("touch id: %d ", touches[0]->getID());
    
    if (isDead) {
        return;
    }
    if (isFrozen) {
        rate=0;//停止
        direction = dir_stop;
        startAction(stopActionType);
        return;
    }
    
    for ( auto &item: touches )
    {
        auto touch = item;
        touchMap.erase(touch->getID());
    }
    if (touchMap.size() == 1) {
        map<int, DripDirection>::iterator it;
        it=touchMap.begin();
        direction =it->second;
        if (direction == dir_left) {
            rate = -curSpeed;
//            setFlippedX(false);
            startAction(walkLeftActionType);
        }
        else if (direction == dir_right) {
            rate = curSpeed;
//            setFlippedX(true);
            startAction(walkRightActionType);
        }
        isSmoke = true;
    }
    else
    {
        
        rate=0;//停止
        direction = dir_stop;
        startAction(stopActionType);
        if (isUp) {
            isUp = false;
//            setRotation(0);
            //isDown = true;
        }
        isSmoke = false;
    }
    
    childOnTouchesEnded(touches, event);
}

bool BaseRole::onContactBegin(PhysicsContact& contact, Box* box)
{
    
    return true;
}


// 获得水滴所在列
int BaseRole::getRowOfDrip( float x )
{
    if (x < 0 && x > SCREEN_WIDTH) {
        return 0;
    }
    for (int i = 1; i <= 8; i++) {
        if (x <= i * GRID_SIZE) {
            //            log("my row = %d",i);
            return i;
        }
    }
    return 0;
}

// 找出某列中最高box
Box* BaseRole::getTopBoxByRow(int row)
{
    list<Box*>::iterator i = boxlist->begin();
    Box* b = NULL;
    for( ;i != boxlist->end() ;i++)
    {
        Box* box = *i;
        if (!box) {
            continue;
        }
        if (box->isDead) {
            if (box->track == row) {
                if (!b) {
                    b = box;
                }
                else if (box->getPositionY() >= b->getPositionY()) {
                    b = box;
                }
            }
        }
        
    }
    if (b) {
        //        log("row %d", row);
        //        log("top b : x %f, y %f",b->getPositionX(),b->getPositionY());
        //        log("my : x %f, y %f",getPositionX(),getPositionY());
    }
    return b;
}

// 下落
void BaseRole::falling(float delta,std::list<Box*> *list)
{
    
    if (isUp) {
        return;
    }
    
    boxlist = list;
    
    if (direction == dir_left) {
        rate = -curSpeed;
    }
    else if (direction == dir_right)
    {
        rate = curSpeed;
        
    }
    
    Box* b = getTopBoxByRow(myRow);
    if (b) {
        
        if (b->getPositionY() + GRID_RADIUS_SIZE < DEAD_LINE) {
            return;
        }
        
        if ( b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2 < (int)getPositionY()) {
            if (b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2 + FALL_SPEED >= (int)getPositionY()) {
//                log("fall 1");
                
                isDown = false;
                this->setPosition(Vec2(b->getPositionX(),  b->getPositionY() + GRID_SIZE/2 + getContentSize().height/2));
                
                isOnGround = true;
            }
            else
            {
//                log("fall 2");
                isDown = true;
                setDripPosition(0,-FALL_SPEED);
                setPositionX(b->getPositionX());
                isOnGround = false;
            }
            
        }
        else
        {
            
            if (b->type == dripbox || b->type == powerBall) {
                collisionState(b);
            }
            
            isDown = false;
            isOnGround = true;
        }
    }
    else
    {
        
        if ( DEAD_LINE + getContentSize().height/2 < (int)getPositionY()) {
            if (DEAD_LINE + getContentSize().height/2 + FALL_SPEED >= (int)getPositionY()) {
                
                
                isDown = false;
                this->setPosition(myRow*GRID_SIZE-GRID_RADIUS_SIZE,  DEAD_LINE + getContentSize().height/2);
                isOnGround = true;
            }
            else
            {
                
                isDown = true;
                setDripPosition(0,-FALL_SPEED);
                setPositionX(myRow*GRID_SIZE-GRID_RADIUS_SIZE);
                isOnGround =false;
            }
            
        }
        else
        {
            isDown = false;
            isOnGround = true;
        }
        
        
    }
    
    
}

// 设置相对位置
void BaseRole::setDripPosition(float x, float y)
{
    if (getPositionX() - getContentSize().width/2 + x < 0) {
        setPositionX(getContentSize().width/2);
    }
    else if (getPositionX() + getContentSize().width/2 + x > SCREEN_WIDTH) {
        setPositionX(SCREEN_WIDTH - getContentSize().width/2);
    }
    else if ( getPositionY() - getContentSize().height/2 + y < DEAD_LINE )
    {
        setPositionY(getContentSize().height/2 + DEAD_LINE);
    }
    else
    {
        setPositionX(getPositionX() + x);
        setPositionY(getPositionY() + y);
        if (y >= 0) {
            //showMoveSmoke(getPosition()+Vec2(0,-30), playScene);
        }
        
    }
}

// 碰撞检测
bool BaseRole::collisionDetection()
{
    list<Box*>::iterator i = boxlist->begin();
    for( ;i != boxlist->end() ;i++)
    {
        Box* box = *i;
        if (!box) {
            continue;
        }
        
        getTwoNodeCollisionState(this, box);
        
        if (box->isDead) {
            // 固定箱子
            if (box->getPositionY()+GRID_RADIUS_SIZE >= getPositionY()) {
                if (direction == dir_left) {
                    
                    if (box->getPositionX() < getPositionX() ) {
                        if (box->getPositionX() + GRID_RADIUS_SIZE >= getPositionX() - getContentSize().width/2 ) {
                            
                            if (getPositionY() < box->getPositionY()+GRID_RADIUS_SIZE && getPositionY() > box->getPositionY()-GRID_RADIUS_SIZE) {
//                                  log("-----------  左碰撞");
                                if (box->type == dripbox || box->type == waterBall || box->type == powerBall)
                                {
                                    collisionState(box);
                                }
                                else
                                {
                                    
                                    isUp = true;
//                                      setRotation(90);
                                    isOnGround = false;
                                    
                                }
                            }

                            
                        }
                    }
                    
                }
                else if (direction == dir_right)
                {
                    if (box->getPositionX() > getPositionX()) {
                        if (box->getPositionX() - GRID_RADIUS_SIZE <= getPositionX() + getContentSize().width/2 ) {
                            
                            if (getPositionY() < box->getPositionY()+GRID_RADIUS_SIZE && getPositionY() > box->getPositionY()-GRID_RADIUS_SIZE) {
//                                  log("-----------  右碰撞");
                                if (box->type == dripbox || box->type == waterBall || box->type == powerBall)
                                {
                                    collisionState(box);
                                }
                                else
                                {
                                    isUp = true;
                                    //                                setRotation(270);
                                    isOnGround = false;
                                }
                            }

                            
                            
                        }
                    }
                    
                }
            }
            else if (box->getPositionY() < getPositionY()-getContentSize().height/2)
            {
                if (getMyRow() == box->track) {
                    // 判断脚下
                    if (getPositionY()-getContentSize().height/2 > box->getPositionY()+GRID_RADIUS_SIZE-5 && getPositionY()-getContentSize().height/2 < box->getPositionY()+GRID_RADIUS_SIZE+5) {
//                        log("踩到啦");
                        if (box->type == virusesBox) {
//                            log("沼泽箱子！");
                        }
                        collisionState(box);
                    }
                }
                
            }
            
        }
        else
        {
            // 头上的箱子
            if (box->track == myRow) {
                if (box->getPositionY() > getPositionY()) {
                    if (box->getPositionY() - box->getContentSize().height/2 <= getPositionY() + getContentSize().height/2) {
                        
                        if (box->isVisible()) {
                            collisionState(box);
                        }
                        
                    }
                }
            }
            else if (box->track == myRow+1) {
                if (direction == dir_stop) {
                    if (box->getPositionY()+GRID_RADIUS_SIZE > getPositionY()) {
                        if (box->getPositionY() - box->getContentSize().height/2 <= getPositionY() + getContentSize().height/2) {
                            if (box->getPositionX()- GRID_RADIUS_SIZE <= getPositionX() + getContentSize().width/2) {
                                // 掉落箱子在右边有接触
                                //log("右边");
                                
                                if (box->isVisible()) {
                                    if (box->type == normalbox || box->type == normalbox2 || box->type == normalbox3 || box->type == normalbox4 || box->type == normalbox5 || box->type == hailbox|| box->type == sunbox || box->type == dustbox) {
                                        
                                        setPositionX(box->getPositionX()- GRID_RADIUS_SIZE-getContentSize().width/2);
                                    }
                                    else if(box->getPositionX()- GRID_RADIUS_SIZE <= getPositionX() + getContentSize().width/2)
                                    {
                                        collisionState(box);
                                    }
                                }
                                
                            }
                        }
                    }
                }
                
            }
            else if (box->track == myRow-1) {
                if (direction == dir_stop) {
                    if (box->getPositionY()+GRID_RADIUS_SIZE > getPositionY()) {
                        if (box->getPositionY() - box->getContentSize().height/2 <= getPositionY() + getContentSize().height/2) {
                            if (box->getPositionX() + GRID_RADIUS_SIZE >= getPositionX() - getContentSize().width/2) {
                                // 掉落箱子在左边有接触
                                //log("左边");
                                
                                if (box->isVisible()) {
                                    if (box->type == normalbox || box->type == normalbox2 || box->type == normalbox3 || box->type == normalbox4 || box->type == normalbox5 || box->type == hailbox || box->type == sunbox || box->type == dustbox) {
                                        
                                        setPositionX(box->getPositionX()+ GRID_RADIUS_SIZE+getContentSize().width/2);
                                    }
                                    else if(box->getPositionX()+ GRID_RADIUS_SIZE <= getPositionX() - getContentSize().width/2)
                                    {
                                        collisionState(box);
                                    }
                                    
                                }
                                
                                
                            }
                        }
                    }
                }
            }
        }
        
    }
    
    
    return false;
}

// 碰到箱子状态
void BaseRole::collisionState(Box* box)
{
    if (!box) {
        return;
    }
    if (!isEnabled) {
        return;
    }
//    if (box->isDead && box->type != virusesBox && box->type != dripbox && box->type != waterBall
//        && box->type != powerBall) {
//        return;
//    }
//    if (isInvincible) {
//        // 无敌
//        //        log("无敌啦！！！！！");
//        if (box->type != dripbox && box->type != waterBall && box->type != virusesBox) {
//            if (delegate) {
//                delegate->dripDelegateRemoveHailBox(this, box);
//            }
//            return;
//        }
//    }
    
    switch (box->type) {
        case normalbox:
            nextState = boxState;
            break;
        case normalbox2:
            nextState = boxState;
            break;
        case normalbox3:
            nextState = boxState;
            break;
        case normalbox4:
            nextState = boxState;
            break;
        case normalbox5:
            nextState = boxState;
            break;
        case hailbox:
            nextState = hailState;
            break;
        case dustbox:
            nextState = dustState;
            break;
        case dripbox:
            nextState = dripState;
            break;
        case sunbox:
            nextState = sunState;
            break;
        case waterBall:
            nextState = waterBallState;
            break;
        case bullet:
            nextState = bulletState;
            break;
        case goldBall:
            nextState = goldBallState;
            break;
        case virusesBox:
            nextState = VirusesBoxState;
            break;
        case powerBall:
            nextState = PowerBallState;
            break;
        default:
            break;
    }
    
    
    curState = nextState;
    //log("判断中");
    if (box->isSlow) {
//        log("箱子变沼泽啦");
        isReduceSpeed = true;
    }
    else
    {
        isReduceSpeed = false;
    }
    
    switch (curState) {
        case boxState:
//////////////////////////////////////
//            // 普通箱子，一砸就死
//            isDown = true;
//            isUp = false;
//            direction = dir_stop;
//            rate = 0;
////            setRotation(0);
//            
//            if (isOnGround) {
//                blood = 0;
//                Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
//                startAction(boxDeadActionType);
//
//                
//                
//                nextState = noCollisionState;
//            }
//////////////////////////////////////
            if (box->isDead) {
                return;
            }
            // 普通箱子，砸中掉一滴血
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                if (delegate) {
                    delegate->dripDelegateRemoveHailBox(this, box);
                }
//                checkSafetyCover(1);
            }
            else
            {
//                Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
//                blood = blood - 1;
//                if (blood > 0) {
//                    showScorePic(-1, box->getPosition(), playScene);
//                }
//                startAction(otherDeadActionType);
                isDown = true;
                isUp = false;
                direction = dir_stop;
                rate = 0;
                if (isOnGround) {
                    blood = blood - 1;
                    if (blood > 0) {
                        showScorePic(-1, box->getPosition(), playScene);
                        if (delegate) {
                            delegate->dripDelegateRemoveHailBox(this, box);
                        }
                    }
                    Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
                    startAction(boxDeadActionType);

                    nextState = noCollisionState;
                }
                
            }
            nextState = noCollisionState;
            //           log(" =======  is 普通箱子 ");
            break;
        case hailState:
            // 冰雹，碰到被冰冻，弹出按钮点五下方可解冻
            if (box->isDead) {
                return;
            }
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                if (delegate) {
                    delegate->dripDelegateRemoveHailBox(this, box);
                }
//                checkSafetyCover(1);
            }
            else
            {
                isDown = true;
                isUp = false;
                direction = dir_stop;
                rate = 0;
                if (isOnGround) {
                    blood = blood - 1;
                    if (blood > 0) {
                        if (getParent()) {
                            showScorePic(-1, box->getPosition(), getParent());
                        }
                        
                        if (delegate) {
                            delegate->dripDelegateRemoveHailBox(this, box);
                        }
                        // 弹出按钮，点五下解冻
                        setFrozen(true);
                    }
                    Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
                    startAction(boxDeadActionType);
                    
                    nextState = noCollisionState;
                }
//                Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
//                blood = blood - 1;
//                if (blood > 0) {
//                    showScorePic(-1, box->getPosition(), playScene);
//                }
//                startAction(otherDeadActionType);
//                // 弹出按钮，点五下解冻
//                setFrozen(true);
                
                
            }
//            
//            if (delegate) {
//                delegate->dripDelegateRemoveHailBox(this, box);
//            }
            nextState = noCollisionState;
            //            log(" =======  is 冰雹雹 ");
            break;
        case dustState:
            // 灰尘，掉1血
            
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                if (delegate) {
                    delegate->dripDelegateRemoveHailBox(this, box);
                }
//                checkSafetyCover(1);
            }
            else
            {
                Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
//////////////////////
//                isReduceSpeed = true;
//                decTime = 0;
//                curSpeed = maxSpeed/2;
//                setReduceSpeedEffect(true);
//////////////////////
                blood = blood - 1;
                if (blood > 0) {
                    showScorePic(-1, box->getPosition(), playScene);
                }
                startAction(otherDeadActionType);
            }
            
            
            if (delegate) {
                delegate->dripDelegateRemoveHailBox(this, box);
                // 沼泽箱子委托
                delegate->dripDelegatevirusesBox(this, box->track);
            }
            nextState = noCollisionState;
            //            log(" =======  is 灰尘尘 ");
            break;
        case dripState:
            // 水滴，一碰加一滴血
            Manager::getInstance()->playSoundEffect("getWater.mp3");
            if (blood < MAXLIFE) {
                if (getParent()) {
                   showScorePic(1, box->getPosition(), getParent()); 
                }
                
                blood = blood + 1;
            }
            if (delegate) {
                delegate->dripDelegateRemoveHailBox(this, box);
            }
            nextState = noCollisionState;
                        log(" =======  is 水滴滴");
            break;
        case sunState:
            // 太阳，一碰掉1滴血
            
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                if (delegate) {
                    delegate->dripDelegateRemoveHailBox(this, box);
                }
//                checkSafetyCover(1);
            }
            else
            {
                Manager::getInstance()->playSoundEffect("bombSound.mp3");
                blood = blood - 1;
                if (blood > 0) {
                    showScorePic(-1, box->getPosition(), playScene);
                }
                startAction(otherDeadActionType);
            }
            
            if (delegate) {
                delegate->dripDelegateRemoveHailBox(this, box);
            }
            
            nextState = noCollisionState;
            //            log(" =======  is 太阳阳 ");
            break;
        case bulletState:
            // boss子弹，碰到掉一滴血
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                if (delegate) {
                    delegate->dripDelegateRemoveHailBox(this, box);
                }
//                checkSafetyCover(1);
            }
            else
            {
                Manager::getInstance()->playSoundEffect("dripBeaten.mp3");
                blood = blood - 1;
                if (blood > 0) {
                    showScorePic(-1, box->getPosition(), playScene);
                }
                startAction(otherDeadActionType);
                
            }
            
            if (delegate) {
                delegate->dripDelegateRemoveHailBox(this, box);
            }
            nextState = noCollisionState;
            //            log(" =======  is 子弹弹 ");
            break;
        case waterBallState:
            // 水炮
            Manager::getInstance()->playSoundEffect("getWater.mp3");
            if (delegate) {
                delegate->dripDelegateWaterBall(this, box );
            }
            if (delegate) {
                delegate->dripDelegateRemoveHailBox(this, box);
            }
            nextState = noCollisionState;
            //            log(" =======  is 水炮炮");
            break;
        case goldBallState:
            // 金币，一碰加一金币
            
            break;
        case VirusesBoxState:
            // 沼泽箱子
            
            break;
        case PowerBallState:
            // 能量箱子
            Manager::getInstance()->playSoundEffect("getWater.mp3");
            if (delegate) {
                delegate->dripDelegatePowerBox(this, box);
                delegate->dripDelegateRemoveHailBox(this, box);
            }
            nextState = noCollisionState;
            break;
        default:
            break;
    }
    
    //    log("======= blood : %d", blood);
}

// 水滴死亡
void BaseRole::dripDead()
{
    
    if (blood <= 0) {
        
        if (getChildByTag(SWEAT_TAG)) {
            removeChildByTag(SWEAT_TAG);
        }
        blood = 0;
        isDead = true;
        if (delegate) {
            delegate->dripDelegateDead(this, 0);
            
        }
        //        log(" =======  is dead ");
    }
}

// 播动画
void BaseRole::startAction( ActionType type )
{
    stopAllActions();
    
    //    log("========== runAction");
    
    if (type == walkLeftActionType ) {
        
        playLeftAction();
    }
    else if (type == walkRightActionType )
    {
        playRightAction();
    }
    else if (type == stopActionType )
    {
        playStopAction();
    }
    else if (type == boxDeadActionType)
    {
        if (blood <= 0) {
            blood = 0;
            isDead = true;
            rate = 0;
            direction = dir_stop;
            playBoxDieAction();
            
            isYaBian = true;
            
            touchMap.clear();
            hideFrozenBtn();
        }
        
    }
    else if (type == otherDeadActionType)
    {
        if (blood <= 0) {
            blood = 0;
            isDead = true;
            rate = 0;
            direction = dir_stop;
            
            playOtherDieAction();
            touchMap.clear();
            hideFrozenBtn();
        }
        
    }
}

void BaseRole::playBoxDieAction()
{
    if (playScene) {
        showDripParticleEffect(getPosition(), playScene);
    }
//    setScaleY(0.1);
    setVisible(false);
    dripDead();
}
void BaseRole::playOtherDieAction()
{
    if (playScene) {
        showDripParticleEffect(getPosition(), playScene);
    }
    
//    FadeOut* fadeout = FadeOut::create(0.3);
//    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(BaseRole::dripDead, this));
//    Sequence* action = Sequence::create(fadeout, callback, NULL);
//    runAction(action);
//    setScaleY(0.1);
    setVisible(false);
    dripDead();
}

// 设置伞状态
void BaseRole::setUmbrella(bool flag)
{
    if (flag) {
        if (!getChildByTag(UMBRELLA_TAG)) {
            Sprite* u = Sprite::create("img_props_umbrella_use.png");
            u->setPosition(Vec2(0,40));
            addChild(u,UMBRELLA_TAG,UMBRELLA_TAG);
        }
        
    }
    else
    {
        if(getChildByTag(UMBRELLA_TAG)) {
            removeChildByTag(UMBRELLA_TAG);
        }
    }
    
    isUmbrella = flag;
}
bool BaseRole::getUmbrella()
{
    return isUmbrella;
}

// 设置无敌状态
void BaseRole::setInvincible(bool flag)
{
    if (flag) {
        
        Node* texiao = CSLoader::createNode("wudi.csb");
        texiao->setScale(2.0);
        addChild(texiao,INVINCIBLE_TAG+1);
        
        if (playScene) {
            LayerColor* layer = LayerColor::create(Color4B::BLACK);
            playScene->addChild(layer,199,199);
            playScene->isGamePause = true;
        }
        
        auto amt = (Armature *)texiao->getChildByName("ArmatureNode_1");
        if (amt) {
            amt->getAnimation()->play("lead_protect1");
        }
        
        int l = CommonData::getInstance()->getRoleSkillLevel(1);
        if (l == 1) {
            invincibleTotalTime = 8.5;
            invincibleLastTime = invincibleTotalTime;
        }
        else if (l == 2)
        {
            invincibleTotalTime = 10.5;
            invincibleLastTime = invincibleTotalTime;
        }
        else if (l == 3)
        {
            invincibleTotalTime = 12.5;
            invincibleLastTime = invincibleTotalTime;
        }
        else if (l == 4)
        {
            invincibleTotalTime = 15.5;
            invincibleLastTime = invincibleTotalTime;
        }
        
        amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
            if(MovementEventType::COMPLETE==type){
                
                if(strcmp(str.c_str(), "lead_protect1")==0){
                    armture->getAnimation()->play("lead_protect2");
                    if (playScene) {
                        if (playScene->getChildByTag(199)) {
                            playScene->removeChildByTag(199);
                        }
                    }
                    isInvincible = true;
                }
                
                if(strcmp(str.c_str(), "lead_protect2")==0){
                    
//                    texiao->removeFromParent();
                    if (playScene) {
                        playScene->isGamePause = false;
                    }
                    
                    if (!getChildByTag(INVINCIBLE_TAG)) {
                        Sprite* i = Sprite::create("img_action_protect.png");
                        i->setPosition(Vec2(0,0));
                        addChild(i,INVINCIBLE_TAG,INVINCIBLE_TAG);
                        
                        i->setScale(0.1);
                        ScaleTo* s = ScaleTo::create(0.4, 1);
                        
                        ScaleTo* scaleTos = CCScaleTo::create(1.2f,0.95f);
                        ScaleTo* scaleTob = CCScaleTo::create(1.2f,1.05f);
                        Sequence* action = Sequence::create(scaleTos, scaleTob, NULL);
                        RepeatForever* repeat = RepeatForever::create(action);
                        
                        Sequence* seq = Sequence::create(s, repeat, NULL);
                        i->runAction(seq);
                        // 从commondata里读取life
                        log("开启无敌");
//                        isInvincible = true;
                        int life = 1;
//                        int l = CommonData::getInstance()->getRoleSkillLevel(1);
//                        life = l;
//                        //            setSafeCoverColor(i, life);
//                        safetyCoverLife = life;
//                        if (l == 1) {
//                            invincibleTotalTime = 8.5;
//                            invincibleLastTime = invincibleTotalTime;
//                        }
//                        else if (l == 2)
//                        {
//                            invincibleTotalTime = 10.5;
//                            invincibleLastTime = invincibleTotalTime;
//                        }
//                        else if (l == 3)
//                        {
//                            invincibleTotalTime = 12.5;
//                            invincibleLastTime = invincibleTotalTime;
//                        }
//                        else if (l == 4)
//                        {
//                            invincibleTotalTime = 15.5;
//                            invincibleLastTime = invincibleTotalTime;
//                        }
                    }
                }
            }
        });
        
        
    }
    else
    {
        if(getChildByTag(INVINCIBLE_TAG)) {
            removeChildByTag(INVINCIBLE_TAG);
            safetyCoverLife = 0;
            isInvincible = false;
        }
    }
    
    
}

// 设置金钟罩颜色
void BaseRole::setSafeCoverColor(Node* image,int life)
{
    if (!image) {
        return;
    }
    if (life == 1) {
        image->setColor(Color3B::WHITE);
    }
    else if(life == 2)
    {
        image->setColor(Color3B(254,248,182));
    }
    else if(life == 3)
    {
        image->setColor(Color3B(255,241,90));
    }
    else if(life == 4)
    {
        image->setColor(Color3B(255,234,3));
    }
}
bool BaseRole::getInvincible()
{
    return isInvincible;
}

void BaseRole::showDripParticleEffect(Vec2 position,Node* node){
    
    const char* str = "";
    if (roleType == BeymacType) {
        str = "img_icon_lead_bomb.png";
    }
    else if (roleType == LaserType)
    {
        str = "img_icon_lead_bomb2.png";
    }
    else if (roleType == TomagoType)
    {
        str = "img_icon_lead_bomb3.png";
    }
    
    ParticleExplosion* effect = ParticleExplosion::createWithTotalParticles(15);
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage(str));
    effect->setStartColor(Color4F(1,1,1,1));
    effect->setStartColorVar(Color4F(0,0,0,1));
    effect->setEndColor(Color4F(1,1,1,1));
    effect->setEndColorVar(Color4F(0,0,0,1));
    effect->setStartSize(20.0f);
    effect->setStartSizeVar(0.f);
    effect->setGravity(Vec2(0,-700));
    effect->setLife(0.3f);
    effect->setLifeVar(0.1f);
    effect->setSpeed(400);
    effect->setSpeedVar(20);
    effect->setPosition(position);
    effect->setAutoRemoveOnFinish(true);
    effect->setRadialAccelVar(60.f);
    node->addChild(effect,100000);
}

void BaseRole::showScorePic(int score,Vec2 pos,Node* node)
{
    //itoa(nValue, szBuf, 10);
    Sprite* sprite = NULL;
    if (score == -1) {
        // 减1血
        sprite = Sprite::create("img_reduce_life_1.png");
    }
    else if (score == -2)
    {
        // 减2血
        sprite = Sprite::create("img_reduce_life_2.png");
    }
    else if (score == 1)
    {
        // 加1血
        sprite = Sprite::create("img_increase_life_1.png");
    }
    if (!sprite) {
        return;
    }
    sprite->setAnchorPoint(Vec2(0.5,0.5));
    sprite->setPosition(pos);
    node->addChild(sprite);
    FadeIn* fadein = FadeIn::create(0.5);
    MoveBy* moveby = MoveBy::create(0.5, Vec2(0, 50));
    Spawn* spawn = Spawn::create(fadein, moveby, NULL);
    
    FadeOut* fadeout = FadeOut::create(0.5);
    MoveBy* moveby2 = MoveBy::create(0.5, Vec2(0, 50));
    Spawn* spawn2 = Spawn::create(fadeout, moveby2, NULL);
    
    CallFuncN* call = CallFuncN::create(CC_CALLBACK_1(BaseRole::removeScorePic,this));
    sprite->runAction(Sequence::create(spawn,spawn2,call,NULL));
}
void BaseRole::removeScorePic(Node* node)
{
    if (node) {
        node->removeFromParentAndCleanup(true);
    }
}

int BaseRole::getMyRow()
{
    return myRow;
}

// 设置减速效果
void BaseRole::setReduceSpeedEffect( bool flag )
{
    if (flag) {
        if (!getChildByTag(REDUCESPEED)) {
            Sprite* i = Sprite::create("img_play_evil1.png");
            i->setPosition(Vec2(0,30));
            addChild(i,REDUCESPEED,REDUCESPEED);
            
            Animation* animation = Animation::create();
            for (int i=1; i<=2; i++)
            {
                __String* image = __String::createWithFormat("img_play_evil%i.png", i);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(image->getCString());
                Rect rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
                animation->addSpriteFrame(frame);
            }
            animation->setDelayPerUnit(0.15);
            Animate* animate = Animate::create(animation);
            RepeatForever* repeat = RepeatForever::create(animate);
            i->runAction(repeat);
        }
        
    }
    else
    {
        if(getChildByTag(REDUCESPEED)) {
            removeChildByTag(REDUCESPEED);
        }
    }
}

// 移动时灰尘效果
void BaseRole::showMoveSmoke(Vec2 pos,Node* node)
{
    Sprite* sprite = Sprite::create("img_smoke.png");
    
    sprite->setAnchorPoint(Vec2(0.5,0.5));
    sprite->setPosition(pos);
    node->addChild(sprite,0);
    sprite->setScale(1.2);
    FadeOut* fadeout = FadeOut::create(0.5);
    ScaleTo* scaleto = ScaleTo::create(0.5, 0.3);
    Spawn* spawn = Spawn::create(fadeout, scaleto, NULL);
    
    CallFuncN* call = CallFuncN::create(CC_CALLBACK_1(BaseRole::removeSmoke,this));
    sprite->runAction(Sequence::create(spawn,call,NULL));
}

void BaseRole::removeSmoke(Node* node)
{
    if (node) {
        node->removeFromParentAndCleanup(true);
    }
}

// 两个物理的碰撞状态(相对于第一个node)
CollisionType BaseRole::getTwoNodeCollisionState(Node* n1, Node* n2)
{
    
    if (n1->getBoundingBox().intersectsRect(n2->getBoundingBox())) {
        // 已碰撞
        
        if (n2->getPositionY() > n1->getPositionY() + n1->getContentSize().height/2  ) {
            // 上
//            log("-------------------------------------------  上碰撞");
        }
        else if (n2->getPositionY() < n1->getPositionY() - n1->getContentSize().height/2)
        {
            // 下
            //log("-------------------------------------------  下碰撞");
        }
        else
        {
            if (n2->getPositionX() <= n1->getPositionX() - n1->getContentSize().width/2 ) {
                // 左
//                log("-------------------------------------------  左碰撞");
            }
            else
            {
                // 右
//                log("-------------------------------------------  右碰撞");
            }
        }
        
    }
    
    return noCollisionType;
}

// 获取类型
RoleType BaseRole::getRoleType()
{
    return roleType;
}

float BaseRole::getRoleAttack()
{
    return maxAttack;
}

Size BaseRole::getContentSize()
{
    float s = getScale();
    Size size = Size(64*s, 88*s);
    //    log("大白宽：%f,高：%f", size.width, size.height);
    
    return size;
}

void BaseRole::setRoleType(RoleType type)
{
    roleType = type;
}

void BaseRole::childUpdate(float delta,std::list<Box*> *boxlist)
{
    
}
void BaseRole::childOnTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent)
{
    
}
void BaseRole::childOnTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent)
{
    
}

// 设置冰冻状态
void BaseRole::setFrozen(bool flag)
{
    isFrozen = flag;
    if (isFrozen) {
        if (!getChildByTag(FROZEN_TAG)) {
            Sprite* ice = Sprite::create("img_icon_frozen.png");
            addChild(ice,FROZEN_TAG,FROZEN_TAG);
            ice->setPosition(Vec2(0,0));
            showFrozenBtn();
        }
    }
    else
    {
        if(getChildByTag(FROZEN_TAG)) {
            removeChildByTag(FROZEN_TAG);
        }
    }
    
    
}

void BaseRole::showFrozenBtn()
{
    if (isFrozen) {
        frozenClickCount = 0;
        
        Sprite* top = Sprite::create("img_btn_unfreeze_top.png");
        top->setPosition(SCREEN_CENTER);
        if (getParent()) {
            if (!getParent()->getChildByTag(FROZEN_BTN_TAG+1)) {
                getParent()->addChild(top, FROZEN_BTN_TAG+1, FROZEN_BTN_TAG+1);
            }
            
        }
        
        Button *btn = Button::create("img_btn_unfreeze.png");
        btn->setPosition(SCREEN_CENTER);
        btn->setZoomScale(0);
        btn->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::BEGAN){
                Manager::getInstance()->playSoundEffect("btnPress.mp3");
                frozenClickCount++;
                Button *btn = (Button*)pSender;
                btn->setPosition(btn->getPosition()-Vec2(0,20));
                if (frozenClickCount >= FROZEN_CLICKNUMBER) {
                    hideFrozenBtn();
                }
            }
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
                Button *btn = (Button*)pSender;
                btn->setPosition(btn->getPosition()+Vec2(0,20));
            }
        });

        if (getParent()) {
            if (!getParent()->getChildByTag(FROZEN_BTN_TAG)) {
                getParent()->addChild(btn, FROZEN_BTN_TAG, FROZEN_BTN_TAG);
            }
            
        }
    }
}

void BaseRole::hideFrozenBtn()
{
    if (getParent()) {
        if (getParent()->getChildByTag(FROZEN_BTN_TAG)) {
            getParent()->removeChildByTag(FROZEN_BTN_TAG);
            getParent()->removeChildByTag(FROZEN_BTN_TAG+1);
        }
        
    }
    touchMap.clear();
    setFrozen(false);
}

// 检测金钟罩
void BaseRole::checkSafetyCover(int life)
{
    if (isInvincible) {
        safetyCoverLife -= life;
        if (safetyCoverLife <= 0) {
            setInvincible(false);
        }
        else
        {
            if(getChildByTag(INVINCIBLE_TAG)) {
                setSafeCoverColor(getChildByTag(INVINCIBLE_TAG), safetyCoverLife);
            }
        }
    }
}

// 检测是否被炸弹炸到
bool BaseRole::checkIsHurtByBomb(Vec2 pos, int attack, int type)
{
    if (!isCanBeContact) {
        return true;
    }
    
    int row = getRowOfDrip(pos.x);
    if (type == 0 || type == 1) {
        if (row -1 <= myRow && myRow <= row + 1 ) {
            
            if (type == 0) {
                // 鲨鱼炸弹
                if (row == myRow) {
                    // 砸到头上
                    // 砸中掉血
                    if (isInvincible) {
                        //                log("我有金钟罩！！！！！");
                        //            if (delegate) {
                        //                delegate->dripDelegateRemoveHailBox(this, box);
                        //            }
//                        checkSafetyCover(attack);

                        return true;
                    }
                    else
                    {
                        blood = blood - attack;
                        if (blood > 0) {
                            showScorePic(-attack, getPosition()+Vec2(0,20), playScene);
                        }
                        startAction(otherDeadActionType);
                        
                        isCanBeContact = false;
                        isCanBeContactLastTime = isCanBeContactTotalTime;
                        
                        return true;
                    }
                }
                else
                {
                    // 判断是否在同一行
                    if (getPositionY() > pos.y - GRID_RADIUS_SIZE && getPositionY() < pos.y + GRID_RADIUS_SIZE) {
                        // 砸中掉血
                        if (isInvincible) {
                            //                log("我有金钟罩！！！！！");
                            //            if (delegate) {
                            //                delegate->dripDelegateRemoveHailBox(this, box);
                            //            }
//                            checkSafetyCover(attack);
                            return true;
                        }
                        else
                        {
                            blood = blood - attack;
                            if (blood > 0) {
                                showScorePic(-attack, getPosition()+Vec2(0,20), playScene);
                            }
                            startAction(otherDeadActionType);
                            
                            isCanBeContact = false;
                            isCanBeContactLastTime = isCanBeContactTotalTime;
                            
                            return true;
                        }
                    }
                }
            }
            else if (type == 1)
            {
                // 激光球
                if (isInvincible) {
//                    log("我有金钟罩！！！！！");
                    //            if (delegate) {
                    //                delegate->dripDelegateRemoveHailBox(this, box);
                    //            }
//                    checkSafetyCover(attack);
                    return true;
                }
                else
                {
//                    log("掉血掉血！！！");
                    blood = blood - attack;
                    if (blood > 0) {
                        showScorePic(-attack, getPosition()+Vec2(0,20), playScene);
                    }
                    startAction(otherDeadActionType);
                    
                    isCanBeContact = false;
                    isCanBeContactLastTime = isCanBeContactTotalTime;
                    
                    return true;
                }
            }
            
        }
    }
    else if (type == 2)
    {
        // 短激光
        if (row == myRow) {
            // 砸到头上
            // 砸中掉血
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                //            if (delegate) {
                //                delegate->dripDelegateRemoveHailBox(this, box);
                //            }
//                checkSafetyCover(attack);
                return true;
            }
            else
            {
                boxBangAction(getPositionX(),getPositionY());
                
                blood = blood - attack;
                if (blood > 0) {
                    showScorePic(-attack, getPosition()+Vec2(0,20), playScene);
                }
                startAction(otherDeadActionType);
                
                isCanBeContact = false;
                isCanBeContactLastTime = 1;
                
                return true;
            }
        }
    }
    else if (type == 3)
    {
        // 冰冻球
        // 砸到头上
        // 砸中掉血
        
        if (row -1 <= myRow && myRow <= row + 1 ) {
            if (isInvincible) {
                //                log("我有金钟罩！！！！！");
                //                checkSafetyCover(1);
                return true;
            }
            else
            {
                direction = dir_stop;
                rate = 0;
                if (isOnGround) {
                    blood = blood - attack;
                    if (blood > 0) {
                        if (getParent()) {
                            showScorePic(-attack, getPosition()+Vec2(0, GRID_HEIGHT), getParent());
                        }
                        // 弹出按钮，点五下解冻
                        setFrozen(true);
                    }
//                    Manager::getInstance()->playSoundEffect("bombSound.mp3");
                    startAction(boxDeadActionType);
                    
                    isCanBeContact = false;
                    isCanBeContactLastTime = isCanBeContactTotalTime;
                    
                    return true;
                }
                
            }
        }

    }
    
    
    return false;
}

void BaseRole::boxBangAction(float x, float y) {
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bomb_action.ExportJson");
    auto amt = Armature::create("bomb_action");
    amt->setPosition(x,y);
    amt->setScale(2);
    amt->setTag(141);
    long animationCount = amt->getAnimation()->getAnimationData()->getMovementCount();
    for(int i=0;i<animationCount;i++){
        std::string mn=amt->getAnimation()->getAnimationData()->movementNames.at(i);
        amt->getAnimation()->getAnimationData()->getMovement(mn)->loop=false;
    }
    if (getParent()) {
        getParent()->addChild(amt,201);
    }
    
    amt->getAnimation()->playWithIndex(0);
}