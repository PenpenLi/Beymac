//
//  ShortLaserBullet.cpp
//  beymac
//
//  Created by wang on 15/5/12.
//
//

#include "ShortLaserBullet.h"
#include "Macro.h"
#include "Box.h"
#include "PlayScene.h"
#include "BeyMac.h"
#include <cocostudio/CocoStudio.h>

ShortLaserBullet::ShortLaserBullet(float s, float a,int w)
:bullet()
,isUpdate(true)
,boss()
{
    maxSpeed = s;
    speed = maxSpeed;
    attack = a;
//    parent = p;
    whoShoot = w;
    type = BulletType_shortLaser;
    init();
}

ShortLaserBullet::~ShortLaserBullet()
{

}

ShortLaserBullet* ShortLaserBullet::createSLBullet(float speed, float attack,int whoShoot)
{
    ShortLaserBullet* bullet = new ShortLaserBullet(speed,attack,whoShoot);
    if (bullet) {
        bullet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(bullet);
    }
    return bullet;
}

bool ShortLaserBullet::init()
{
    if (!Node::init())
    {
        return false;
    }
    
//    bullet = DrawNode::create();
//    bullet->setPosition(Vec2::ZERO);
//    addChild(bullet);
//    bullet->drawSegment(Vec2(0, -SLASER_HALFLENGTH), Vec2(0, SLASER_HALFLENGTH), 5, Color4F(1,1,1,1));
    
    if (speed > 0 ) {
        // 大白发
        bulletNode = CSLoader::createNode("SLaserBullet.csb");
        bulletNode->setScale(2.0);
        bulletNode->setPosition(Vec2::ZERO);
        
        addChild(bulletNode);
        Size size = Size(80,550);
        setContentSize(size);
//
//        playFlyAction();
        
//        bulletImage = Sprite::create("img_action_line.png");
//        bulletImage->setPosition(Vec2::ZERO);
//        addChild(bulletImage);
//        setContentSize(bulletImage->getContentSize());
//        int num = CommonData::getInstance()->getRoleSkillLevel(6);
//        if (num == 1 || num == 2) {
//            attack = 1;
//        }
//        else if (num == 3)
//        {
//            attack = 2;
//        }
//        else if (num == 4)
//        {
//            attack = 3;
//        }
    }
    else 
    {
        // boss发
        bulletImage = Sprite::create("img_action_line_boss.png");
        bulletImage->setAnchorPoint(Vec2(0.5, 0.5));
        bulletImage->setPosition(Vec2::ZERO);
        addChild(bulletImage);
//        setContentSize(bulletImage->getContentSize());
        Size size = Size(bulletImage->getContentSize().width-20, bulletImage->getContentSize().height-120);
        setContentSize(size);
    }
    

    // 加入拖尾
//    if (parent) {
//        streak = MotionStreak::create(0.4, 3, 10, Color3B::WHITE, "streak.png" );
//        parent->addChild(streak,getLocalZOrder());
//    }
    
//    Size size = Size(10, SLASER_HALFLENGTH*2);
//    setContentSize(size);
    
    
    return true;
}

void ShortLaserBullet::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void ShortLaserBullet::onExit()
{
    Node::onExit();
}

void ShortLaserBullet::onUpdate(float delta,std::list<Box*> *boxlist,Node* player)
{
    if (!isUpdate) {
        return ;
    }
    
    setPositionY(getPositionY()+speed);
//    if (streak) {
//        streak->setPosition(getPosition());
//    }
    
    if (boxlist->size() > 0) {
//        Box* b = getTopBoxByRow(getRow(getPositionX()), boxlist);
        std::list<Box*>::iterator i = boxlist->begin();
        for( ;i != boxlist->end() ;i++)
        {
            Box* b = (*i);
            if (!b) {
                continue;
            }
            if (b->getPositionY() < DEAD_LINE) {
                continue;
            }
            if (getRow(getPositionX()) == b->track) {
                if (speed >0) {
                    if (b->getBoundingBox().intersectsRect(getBoundingBox())) {
                        // 碰到箱子
                        //                removeBullet();
                        if (delegate) {
                            delegate->baseBulletDelegateContact(this, 0,b);
                        }
                        break;
                    }
                }
                else
                {
                    if (b->getBoundingBox().intersectsRect(getBoundingBox())) {
                        // 碰到箱子
                        //                removeBullet();
                        if (delegate) {
                            delegate->baseBulletDelegateContact(this, 0,b);
                        }
                        break;
                    }
                }
                
            }

        }
    }

    if (player) {
        if (speed < 0) {
            BeyMac* p = (BeyMac*)player;
            Rect r = Rect(getPosition().x-getContentSize().width/2, getPosition().y-getContentSize().height/2, getContentSize().width, 240);
            if (p->getBoundingBox().intersectsRect(r)) {
                // 碰到大白
//                removeBullet();
//                isUpdate = false;
//                boxBangAction(p->getPositionX(), p->getPositionY());
                p->checkIsHurtByBomb(p->getPosition(),attack,2);
                if (delegate) {
//                    delegate->baseBulletDelegateContact(this, 1, NULL);
                }
                
            }
        }
    }
    
    if (boss) {
        if (speed > 0) {
//            vector<Body *>::iterator i;
//            for (i = boss->getBodyList().begin(); i != boss->getBodyList().end(); i++) {
//                Body* body = (*i);  
//                Rect r = Rect(body->getPosition().x-GRID_RADIUS_SIZE, body->getPosition().y-GRID_RADIUS_SIZE, GRID_SIZE, GRID_SIZE);
//                if (r.intersectsRect(getBoundingBox())) {
//                    boxBangAction(body->getPosition().x, body->getPosition().y);
//                    if (delegate) {
//                        delegate->baseBulletDelegateContact(this, 2, NULL);
//                    }
//                }
//            }
//            
        }
    }
    
//    if (getPositionY()>SCREEN_LEFT_UP.y + 100 || getPositionY()<SCREEN_LEFT_DOWN.y - 100) {
//        isUpdate = false;
//        setPosition(SCREEN_CENTER.x,- 100);
//        if (parent) {
//            parent->removeChild(streak);
//            streak = NULL;
//        }
//    }
    
    if (getPositionY()+getContentSize().height > SCREEN_HEIGHT) {
//        isUpdate = false;
    }
    
}



void ShortLaserBullet::removeBullet()
{
//    if (getParent()) {
//        getParent()->removeChild(streak);
//    }
    removeFromParent();
}

Box* ShortLaserBullet::getTopBoxByRow(int row,std::list<Box*> *boxlist)
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

    return b;
}

void ShortLaserBullet::setIsUpdate(bool flag)
{
    isUpdate = flag;
//    if (isUpdate) {
//        if (!streak) {
//            if (parent) {
//                streak = MotionStreak::create(0.4, 3, 10, Color3B::WHITE, "streak.png" );
//                parent->addChild(streak,getLocalZOrder());
//            }
//        }
//    }
}

void ShortLaserBullet::playBombAction()
{
    auto amt = (Armature *)bulletNode->getChildByName("ArmatureNode");
    isUpdate = false;
    
    if (amt) {
        amt->getAnimation()->play("lead_gamma1");
    }
    
    if (delegate) {
        LayerColor* layer = LayerColor::create(Color4B::BLACK);
        delegate->addChild(layer,199,199);
        delegate->isGamePause = true;
    }
    
    amt->getAnimation()->setMovementEventCallFunc([&](Armature *armture, MovementEventType type, const std::string &str){
        if(MovementEventType::COMPLETE==type){
             if(strcmp(str.c_str(), "lead_gamma1")==0){
                 armture->getAnimation()->play("lead_gamma2");
                 if (delegate) {
                     
                     if (delegate->getChildByTag(199)) {
                         delegate->removeChildByTag(199);
                         delegate->isGamePause = false;
                     }
                     delegate->baseBulletDelegateSLaserActionFinish();
                 }
//                 isUpdate = true;
             }
        }
    });
}

void ShortLaserBullet::playFlyAction()
{
    auto amt = (Armature *)bulletNode->getChildByName("ArmatureNode");
    
    if (amt) {
        amt->getAnimation()->play("lead_gamma2");
    }
}

// 时间减缓
void ShortLaserBullet::setSlowDown(bool flag)
{
    if (flag) {
        switch (CommonData::getInstance()->getRoleSkillLevel(3)) {
            case 1:
                speed = maxSpeed * 0.7;
                break;
            case 2:
                speed = maxSpeed * 0.5;
                break;
            case 3:
                speed = maxSpeed * 0.5;
                break;
            case 4:
                speed = 0;
                break;
            default:
                break;
        }
    }
    else
    {
        speed = maxSpeed;
    }
}
