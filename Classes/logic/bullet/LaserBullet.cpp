//
//  LaserBullet.cpp
//  beymac
//
//  Created by wang on 15/5/11.
//
//

#include "LaserBullet.h"
#include "math.h"
#include "Macro.h"
#include "Box.h"
#include "BeyMac.h"
#include "PlayScene.h"

LaserBullet::LaserBullet(float sx,float sy, float a)
:isShoot(true)
,image()
,isUpdate(true)
,isContact(true)
,ballType(2)
{
    maxSpeedX = sx;
    maxSpeedY = sy;
    speedX = maxSpeedX;
    speedY = maxSpeedY;
    attack = a;
    type = BulletType_ball;
    init();
}

LaserBullet::~LaserBullet()
{

}

bool LaserBullet::init()
{
    if (!Node::init())
    {
        return false;
    }

    image = Sprite::create("img_boss1_stone.png");
    image->setPosition(0, 0);
    addChild(image);
    
    setContentSize(image->getContentSize());
    
    return true;
}

void LaserBullet::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void LaserBullet::onExit()
{
    Node::onExit();
}

LaserBullet* LaserBullet::create(float speedX,float speedY, float attack)
{
    LaserBullet* bullet = new LaserBullet(speedX,speedY,attack);
    if (bullet) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}

void LaserBullet::onUpdate(float delta,Node* player)
{
    if (!isUpdate) {
        return;
    }
    
    if (!image) {
        return;
    }
    
    int absSpeedX = std::abs(speedX);
    
    int absSpeedY = std::abs(speedY);
    
    // 如果小球开始运动并且游戏还没有结束
    
    if(isShoot){
        
        // 如果碰到左边界
        
        if(getPositionX()-image->getContentSize().width/2-absSpeedX<0){

            setPositionX(image->getContentSize().width/2);
            speedX = -speedX;
//            Manager::getInstance()->playSoundEffect("ballContactSound.mp3");
            
        }
        
        // 如果碰到右边界
        
        if(getPositionX()+image->getContentSize().width/2 + absSpeedX > SCREEN_RIGHT_DOWN.x){

            setPositionX(SCREEN_RIGHT_DOWN.x-image->getContentSize().width/2);
            speedX = -speedX;
//            Manager::getInstance()->playSoundEffect("ballContactSound.mp3");
        }
        
        // 如果碰到下边界
        
        if(getPositionY()-image->getContentSize().height/2 - absSpeedY < DEAD_LINE){

            setPositionY(DEAD_LINE+image->getContentSize().height/2);
            speedY = -speedY;
            contactSomething(player);
            Manager::getInstance()->playSoundEffect("bombSound.mp3");
            if (delegate) {
                delegate->baseBulletDelegateContactBall(this, 0);
            }
            
        }
 
        // 如果碰到上边界
        
        if(getPositionY()+image->getContentSize().height/2 + absSpeedY > SCREEN_RIGHT_UP.y ){
            
            setPositionY(SCREEN_RIGHT_UP.y - image->getContentSize().height/2);
            speedY = -speedY;
//            Manager::getInstance()->playSoundEffect("ballContactSound.mp3");
        }

        // 是否碰到箱子
        
        // 是否碰到大白
        
        // 设置x坐标
        setPositionX(getPositionX() - speedX);
        
        // 设置y坐标
        setPositionY(getPositionY() - speedY);

    }
    
    if (player) {
        BeyMac* p = (BeyMac*)player;
        if (getBoundingBox().intersectsRect(p->getBoundingBox())) {
//            removeFromParent();
            if (isContact) {
                contactSomething(player,1);
                speedY = -speedY;
                Manager::getInstance()->playSoundEffect("bombSound.mp3");
//                speedX = -speedX;
                if (delegate) {
                    delegate->baseBulletDelegateContactBall(this, 1);
                }
            }
            
        }
        else
        {
            isContact = true;
        }
    }
    
//    std::list<Box*>::iterator i = boxlist->begin();
//    for( ;i != boxlist->end() ;i++)
//    {
//        Box* box = *i;
//        if (!box) {
//            continue;
//        }
//        if (!box->isDead) {
//            continue;
//        }
//        if (image->getBoundingBox().intersectsRect(box->getBoundingBox())) {
//            // 碰上了
////            removeFromParent();
////            break;
//            if (delegate) {
//                delegate->baseBulletDelegateContact(this, 0,box);
//            }
//        }
//    }
}



void LaserBullet::contactSomething(Node* player, int t)
{
    if (ballType == 2) {
        float _x = getPositionX();
        float _y = getPositionY();
        if (player) {
            BeyMac* p = (BeyMac*)player;
            if (p->checkIsHurtByBomb(getPosition(),attack,1)) {
                isContact = false;
            }
            else
            {
                isContact = true;
            }
            
        }
        boxBangAction(_x-GRID_SIZE,_y);
        boxBangAction(_x+GRID_SIZE,_y);
        boxBangAction(_x,_y);
    }
    else if (ballType == 1)
    {
        if (t == 1) {
            if (player) {
                BeyMac* p = (BeyMac*)player;
                if (p->checkIsHurtByBomb(getPosition(),attack,3)) {
                    isContact = false;
                }
                else
                {
                    isContact = true;
                }
                
            }
        }
        float _x = getPositionX();
        float _y = getPositionY();
        boxBangActionIce(_x-GRID_SIZE,_y);
        boxBangActionIce(_x+GRID_SIZE,_y);
        boxBangActionIce(_x,_y);
    }
    
}

void LaserBullet::setType(int t)
{
    if (t == 1) {
        if (image) {
            image->setTexture("img_boss_icestone.png");
        }
        else
        {
            image = Sprite::create("img_boss_icestone.png");
            image->setPosition(0, 0);
            addChild(image);
        }
    }
    else if (t == 2)
    {
        if (image) {
            image->setTexture("img_boss1_stone.png");
        }
        else
        {
            image = Sprite::create("img_boss1_stone.png");
            image->setPosition(0, 0);
            addChild(image);
        }
    }
    
    ballType = t;
}

// 时间减缓
void LaserBullet::setSlowDown(bool flag)
{
    if (flag) {
        switch (CommonData::getInstance()->getRoleSkillLevel(3)) {
            case 1:
                speedX = maxSpeedX * 0.7;
                speedY = maxSpeedY * 0.7;
                break;
            case 2:
                speedX = maxSpeedX * 0.5;
                speedY = maxSpeedY * 0.5;
                break;
            case 3:
                speedX = maxSpeedX * 0.5;
                speedY = maxSpeedY * 0.5;
                break;
            case 4:
                speedX = 0;
                speedY = 0;
                break;
            default:
                break;
        }
    }
    else
    {
        if (speedX >= 0 ) {
            speedX = std::abs(maxSpeedX);
        }
        else
        {
            speedX = -std::abs(maxSpeedX);
        }
        if (speedY >= 0 ) {
            speedY = std::abs(maxSpeedY);
        }
        else
        {
            speedY = -std::abs(maxSpeedY);
        }
    }
}