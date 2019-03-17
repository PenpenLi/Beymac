//
//  SLaserBulletArray.cpp
//  beymac
//
//  Created by mumu on 15/5/26.
//
//

#include "SLaserBulletArray.h"
#include "PlayScene.h"

#define ROLESKILL_SLASER 6


SLaserBulletArray::SLaserBulletArray(float h,float a,float s)
{
    halfWidth = h;
    attack = a;
    speed = s;
    log("伽马射线：半径宽: %f, 攻击力：%f",halfWidth,attack);
}

SLaserBulletArray::~SLaserBulletArray()
{

}

SLaserBulletArray* SLaserBulletArray::create(float halfWidth,float attack,float speed)
{
    SLaserBulletArray* bullet = new SLaserBulletArray(halfWidth,attack,speed);
    if (bullet&&bullet->init()) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}

bool SLaserBulletArray::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void SLaserBulletArray::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void SLaserBulletArray::onExit()
{
    Node::onExit();
}

SLaserBulletArray* SLaserBulletArray::createLBlistByPlayer(float speed, float attack,Vec2 pos,PlayScene* parent )
{
    
    
    int num = 3;
    int a = 1;
    
    if (speed > 0) {
        num = CommonData::getInstance()->getRoleSkillLevel(ROLESKILL_SLASER);
        if (num == 1) {
            num = 1;
            a = 1;
        }
        else if (num == 2 )
        {
            num = 1;
            a = 2;
        }
        else if (num == 3 )
        {
            num = 1;
            a = 3;
        }
        else if (num == 4 )
        {
            num = 3;
            a = 1;
        }
        else if (num == 0 )
        {
            num = 0;
            a = 0;
        }
    }else
    {
        num = 3;
        a = attack;
    }
    
    SLaserBulletArray* array = SLaserBulletArray::create((float)((float)num/2),a,speed);
    
    for (int i = 0; i < num; i++) {
        ShortLaserBullet* bullet = ShortLaserBullet::createSLBullet(speed, a);
        
        bullet->setIsUpdate(false);
        int track = getRow(pos.x);
        if (num == 1) {
            bullet->setPosition((track)*GRID_SIZE-GRID_RADIUS_SIZE, pos.y);
        }
        else{
            bullet->setPosition((track-1+i)*GRID_SIZE-GRID_RADIUS_SIZE, pos.y);
        }
        
        if (parent) {
            parent->addChild(bullet,250);
            bullet->setDelegate(parent);
            array->bulletList.push_back(bullet);
        }
    }
    
    return array;
}

void SLaserBulletArray::onUpdate(float delta,std::list<Box*> *boxlist,Node* player)
{
    if (bulletList.size() > 0) {
        list<ShortLaserBullet*>::iterator iter;
        for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
            
            if ((*iter)->getIsUpdate()) {
                (*iter)->onUpdate(delta, boxlist, player);
            }
            else
            {
                if ((*iter)->getSpeed() > 0) {
                    setIsUpdate(false);
                }
                else
                {
                    setIsUpdate(false);
                    setBulletsPos(Vec2(-200,SCREEN_HEIGHT+500));
                    
                }
                break;
            }
        }
    }
    
}

void SLaserBulletArray::removeBullets()
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->removeBullet();
        (*iter) = NULL;
    }
    bulletList.clear();
}

void SLaserBulletArray::setIsUpdate(bool flag)
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->setIsUpdate(flag);
    }
}

void SLaserBulletArray::setBulletsPos(Vec2 pos)
{
    int track = getRow(pos.x);
    if (bulletList.size() == 3) {
        int num = 0;
        list<ShortLaserBullet*>::iterator iter;
        for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {

            (*iter)->setPosition(pos);
            (*iter)->setPositionX((track-1+num)*GRID_SIZE-GRID_RADIUS_SIZE);
            num++;
        }
    }
    else if (bulletList.size() == 1)
    {
        list<ShortLaserBullet*>::iterator iter;
        for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
            
            (*iter)->setPosition(pos);
            (*iter)->setPositionX((track)*GRID_SIZE-GRID_RADIUS_SIZE);
        }
    }
    
}

void SLaserBulletArray::setBoss(Monster* monster)
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->setBoss(monster);
    }
}

void SLaserBulletArray::setSpeed(float speed)
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->setSpeed(speed);
    }
}

void SLaserBulletArray::playBombAction()
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->playBombAction();
    }
}
void SLaserBulletArray::playFlyAction()
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->playFlyAction();
    }
}

void SLaserBulletArray::setSlowDown(bool flag)
{
    list<ShortLaserBullet*>::iterator iter;
    for (iter = bulletList.begin(); iter != bulletList.end(); iter++) {
        (*iter)->setSlowDown(flag);
    }
}