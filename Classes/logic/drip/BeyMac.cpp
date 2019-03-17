//
//  Drip.cpp
//  TestA
//
//  Created by je on 3/5/15.
//
//

#include "BeyMac.h"
#include "math.h"
#include "Macro.h"
#include "Box.h"
#include "PlayScene.h"
#include "RoleAttributeList.h"

#define BAG_TAG 50
#define ROOT_TAG 100

BeyMac::BeyMac()
:root()
,listPosition(1)
,haveBag(false)
{
    init();
    
}
BeyMac::~BeyMac()
{
    removeFollowers();
}
bool BeyMac::init()
{
    if (!Node::init())
    {
        return false;
    }

    int n = CommonData::getInstance()->getRoleByPosition(1);
    if (n == 1) {
        roleType = BeymacType;
        
    }
    else if (n == 2)
    {
        roleType = LaserType;
    }
    else if (n == 3)
    {
        roleType = TomagoType;
    }
    setRoleType(roleType);
    setLocalZOrder(200);

    
//    isEnabled =false;
    
    return true;
}

void BeyMac::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
}
void BeyMac::onExit()
{

    Node::onExit();
    
}

BeyMac* BeyMac::create()
{
    BeyMac *beyMac=new BeyMac();
    if (beyMac) {
        beyMac->autorelease();
        
    }
    else
    {
        delete beyMac;
        beyMac = NULL;
    }
    
    return beyMac;
}

void BeyMac::playLeftAction()
{
//    auto amt=(Armature *)(this->getChildByTag(100));
    auto node=this->getChildByTag(ROOT_TAG);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    
    if (amt) {
        amt->getAnimation()->play("left");
    }
}
void BeyMac::playRightAction()
{
    auto node=this->getChildByTag(ROOT_TAG);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    if (amt) {
        amt->getAnimation()->play("right");
    }
}
void BeyMac::playStopAction()
{
    auto node=this->getChildByTag(ROOT_TAG);
    auto amt = (Armature *)node->getChildByName("armatureNode");
    
    if (amt) {
        amt->getAnimation()->play("normal");
    }
    
}

Size BeyMac::getContentSize()
{
    float s = getScaleX();
    Size size = Size(64*s, 88*s);
    Node::setContentSize(size);
//    log("大白宽：%f,高：%f", size.width, size.height);
    return size;
}

void BeyMac::setRoleType(RoleType type)
{
    roleType = type;
    if (getChildByTag(ROOT_TAG)) {
        removeChildByTag(ROOT_TAG);
        root = NULL;
    }
    if (type == BeymacType) {
        // 大白
        
        root = CSLoader::createNode("Beymac.csb");
//        log(" 创建：大白");
        
    }
    else if (type == LaserType)
    {
        // 激光
        root = CSLoader::createNode("Laser.csb");
//        log(" 创建：激光");
    }
    else if (type == TomagoType)
    {
        // 神行姐
        root = CSLoader::createNode("Tomago.csb");
//        log(" 创建：神行");
    }
    
    initAttribute(type);
    
    root->setTag(ROOT_TAG);
    this->addChild(root, 5);
}

// 创建跟随者
void BeyMac::createfollowers()
{
    removeFollowers();
    if (CommonData::getInstance()->getRoleLevel(2) > 0 && CommonData::getInstance()->getRoleLevel(3) > 0) {
       
//            int index = 0;
//            for (int i = 0; i < 3; i++) {
//                if (roleType == i) {
//                    continue;
//                }
//                index++;
//                Follower* f = NULL;
//                if (i == 0) {
//                    f = Follower::create(BeymacType);
//                    log(" 跟随：大白");
//                }
//                else if (i == 1)
//                {
//                    f = Follower::create(LaserType);
//                    log(" 跟随：激光");
//                }
//                else if (i == 2)
//                {
//                    f = Follower::create(TomagoType);
//                    log(" 跟随：神行");
//                }
//                if (!f) {
//                    return;
//                }
//                f->setNumber(index);
//                f->setScale(0.5);
//                f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X*index, -getContentSize().height/2+f->getContentSize().height/2));
//                f->setMaster(this);
//                if (getParent()) {
//                    getParent()->addChild(f);
//                    followerslist.push_back(f);
//                }
//            }
            RoleType type = BeymacType;
            int i = CommonData::getInstance()->getRoleByPosition(2);
            if (i == 1) {
                
                type = BeymacType;
            }
            else if (i == 2)
            {
                type = LaserType;
            }
            else if (i == 3)
            {
                type = TomagoType;
            }
            
            Follower* f = Follower::create(type);
            f->setScale(0.5);
            f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X, -getContentSize().height/2+f->getContentSize().height/2));
            f->setNumber(1);
            followerslist.push_back(f);
            if (getParent()) {
                getParent()->addChild(f);
            }
            f->setMaster(this);
            
            i = CommonData::getInstance()->getRoleByPosition(3);
            if (i == 1) {
                
                type = BeymacType;
            }
            else if (i == 2)
            {
                type = LaserType;
            }
            else if (i == 3)
            {
                type = TomagoType;
            }
            Follower* f2 = Follower::create(type);
            f2->setScale(0.5);
            f2->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X, -getContentSize().height/2+f2->getContentSize().height/2));
            f2->setNumber(2);
            followerslist.push_back(f2);
            if (getParent()) {
                getParent()->addChild(f2);
            }
            f2->setMaster(this);
        
    
    }
    else if (CommonData::getInstance()->getRoleLevel(2) > 0 || CommonData::getInstance()->getRoleLevel(3) > 0)
    {
        RoleType type = BeymacType;
        int i = CommonData::getInstance()->getRoleByPosition(2);
        if (CommonData::getInstance()->getRoleLevel(i) < 1) {
            i = CommonData::getInstance()->getRoleByPosition(3);
        }
        if (i == 1) {
            
            type = BeymacType;
        }
        else if (i == 2)
        {
            type = LaserType;
        }
        else if (i == 3)
        {
            type = TomagoType;
        }
        
        Follower* f = Follower::create(type);
        f->setScale(0.5);
        f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X, -getContentSize().height/2+f->getContentSize().height/2));
        f->setNumber(1);
        followerslist.push_back(f);
        if (getParent()) {
            getParent()->addChild(f);
        }
        f->setMaster(this);
        
    }
    


}

void BeyMac::createfollowers(int num)
{
    removeFollowers();
        if (num == 1) {
            if (roleType == BeymacType) {
                Follower* f = Follower::create(LaserType);
                f->setScale(0.5);
                f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X, -getContentSize().height/2+f->getContentSize().height/2));
                f->setNumber(1);
                followerslist.push_back(f);
                if (getParent()) {
                    getParent()->addChild(f);
                }
                f->setMaster(this);
            }
            else if (roleType == LaserType)
            {
                Follower* f = Follower::create(BeymacType);
                f->setScale(0.5);
                f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X, -getContentSize().height/2+f->getContentSize().height/2));
                f->setNumber(1);
                followerslist.push_back(f);
                if (getParent()) {
                    getParent()->addChild(f);
                }
                f->setMaster(this);
            }
        }
        else if (num == 2)
        {
            int index = 0;
            for (int i = 0; i < 3; i++) {
                if (roleType == i) {
                    continue;
                }
                index++;
                Follower* f = NULL;
                if (i == 0) {
                    f = Follower::create(BeymacType);
                }
                else if (i == 1)
                {
                    f = Follower::create(LaserType);
                }
                else if (i == 2)
                {
                    f = Follower::create(TomagoType);
                }
                if (!f) {
                    return;
                }
                f->setNumber(index);
                f->setScale(0.5);
                f->setPosition(getPosition()+Vec2(FOLLOWERDISTANCE_X*index, -getContentSize().height/2+f->getContentSize().height/2));
                f->setMaster(this);
                if (getParent()) {
                    getParent()->addChild(f);
                    followerslist.push_back(f);
                }
            }
        }
}

void BeyMac::removeFollowers()
{
    list<Follower*>::iterator i;
    for (i = followerslist.begin(); i != followerslist.end(); i++) {
        if (getParent()) {
            getParent()->removeChild((*i));
//            followerslist.erase(i);
        }
        
    }
    followerslist.clear();
}

// 界面刷新
void BeyMac::childUpdate(float delta,std::list<Box*> *boxlist)
{
    list<Follower*>::iterator i;
    for (i = followerslist.begin(); i != followerslist.end(); i++) {
        Follower* f = (*i);
        if (!f) {
            continue;
        }
        
        if (direction == dir_stop) {
            f->setPosition(this->getPosition());
            f->setPositionY( getPositionY()-getContentSize().height/2+f->getContentSize().height/2);
        }

//        f->onUpdate(delta, boxlist);
        
        if (abs(getPositionX() - f->getPositionX()) > (FOLLOWERDISTANCE_X*f->getNumber())) {
            if (direction == dir_left) {
                if (f->getPositionX() > getPositionX()) {
                    f->onUpdate(delta, boxlist);
                }
            }
            else if ( direction == dir_right )
            {
                if (f->getPositionX() < getPositionX()) {
                    f->onUpdate(delta, boxlist);
                }
            }
            else
            {
                f->onUpdate(delta, boxlist);
            }
            
        }
        else
        {
            if (abs(getPositionY() - f->getPositionY()) > (FOLLOWERDISTANCE_Y*f->getNumber()))
            {
                    
                f->onUpdate(delta, boxlist);
            }
            
        }

//        f->falling(delta, boxlist);
        
        
    }
}

void BeyMac::childOnTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent)
{
    list<Follower*>::iterator i;
    for (i = followerslist.begin(); i != followerslist.end(); i++) {
        
        
//        if (direction == dir_stop) {
//            (*i)->setPosition(this->getPositionX(), getPositionY()-getContentSize().height/2+(*i)->getContentSize().height/2);
//        }

        (*i)->onTouchesBegan(touches, pEvent);
    }
}
void BeyMac::childOnTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent)
{
    list<Follower*>::iterator i;
    for (i = followerslist.begin(); i != followerslist.end(); i++) {
        
        
        
//        if (direction == dir_stop) {
//
//            (*i)->setPosition(this->getPositionX(), getPositionY()-getContentSize().height/2+(*i)->getContentSize().height/2);
//        }
        
        (*i)->onTouchesEnded(touches, pEvent);
        
    }
}

//初始化属性：速度攻击力
void BeyMac::initAttribute(RoleType type)
{
    maxSpeed = 5;
    
    maxAttack = 1;

    if (type == BeymacType) {
        maxSpeed = RoleAttributeList::getCurAttributes()[0].speed;
        maxAttack = RoleAttributeList::getCurAttributes()[0].attack;
    }
    else if (type == LaserType)
    {
        maxSpeed = RoleAttributeList::getCurAttributes()[1].speed;
        maxAttack = RoleAttributeList::getCurAttributes()[1].attack;
    }
    else if (type == TomagoType)
    {
        maxSpeed = RoleAttributeList::getCurAttributes()[2].speed;
        maxAttack = RoleAttributeList::getCurAttributes()[2].attack;
    }
    
//    log(" 主角速度：%f, 攻击力：%f ", maxSpeed,maxAttack);
    
    curSpeed = maxSpeed;
}

// 更换角色
void BeyMac::changeRole()
{
    
    // 烟雾效果
    Sprite* smoke = Sprite::create("img_smog.png");
    smoke->setPosition(0, 0);
    addChild(smoke,10);
    
    smoke->setScale(0.1);
    ScaleTo* st = ScaleTo::create(0.2, 1.1);
    FadeOut* f = FadeOut::create(0.1);
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        ((Sprite *)pSender)->removeFromParent();
    });
    auto actFunc2=CallFuncN::create([&](Ref *pSender){
        // 换跟随者
        if (followerslist.size()>0) {
            Follower* f = Follower::create(roleType);
            f->setScale(0.5);
            f->setPosition(followerslist.back()->getPosition()+Vec2(FOLLOWERDISTANCE_X, 0));
            f->setPosition(Vec2(100,100));
            int n = followerslist.back()->getNumber();
            f->setNumber(n+1);
            
            if (getParent()) {
                getParent()->removeChild(followerslist.front());
                getParent()->addChild(f);
            }
            followerslist.push_back(f);
            f->setMaster(this);
            followerslist.pop_front();
            
            list<Follower*>::iterator i;
            for (i = followerslist.begin(); i != followerslist.end(); i++) {
                Follower* ff = (*i);
                if (ff) {
                    ff->setNumber(ff->getNumber()-1);
                    ff->setPosition(ff->getPosition()-Vec2(FOLLOWERDISTANCE_X,0));
                }
                
                
            }
        }
        
        // 正式
        if (CommonData::getInstance()->getRoleLevel(2) > 0 && CommonData::getInstance()->getRoleLevel(3) > 0) {
            
            if (listPosition < 3 ) {
                listPosition++;
                
            }else
            {
                listPosition = 1;
            }
            
        }
        else if (CommonData::getInstance()->getRoleLevel(2) > 0 || CommonData::getInstance()->getRoleLevel(3) > 0)
        {

            if (listPosition < 2 ) {
                listPosition++;
                
            }else
            {
                listPosition = 1;

            }
        }
        // 测试
        //    if (listPosition < 2 ) {
        //        listPosition++;
        //
        //    }else
        //    {
        //        listPosition = 1;
        //    }
        
        
        int n = CommonData::getInstance()->getRoleByPosition(listPosition);
        if (n == 1) {
            setRoleType(BeymacType);
//            log(" 切换大白");
        }
        else if (n == 2)
        {
            setRoleType(LaserType);
//            log(" 切换激光");
        }
        else if (n == 3)
        {
            setRoleType(TomagoType);
//            log(" 切换神行");
        }
        
        if (followerslist.size() > 0) {
            // 测试
            //        createfollowers(2);
        }
        list<Follower*>::iterator i;
        for (i = followerslist.begin(); i != followerslist.end(); i++) {
            Follower* ff = (*i);
            if (ff) {
                ff->setMaster(this);
            }
            
        }
    });
    smoke->runAction(Sequence::create(st, actFunc2,f, actFunc, NULL));
    
 
}

// 穿上背包
void BeyMac::takeBag(bool flag)
{
    Node* bag;
    if (flag) {
        if (!getChildByTag(BAG_TAG)) {
            
            setPositionX(myRow*GRID_SIZE-GRID_RADIUS_SIZE);
            
            if (playScene) {
                playScene->isGamePause = true;
            }
            
            isOnGround = false;
            
            bag = CSLoader::createNode("Bag.csb");
            addChild(bag, 0, BAG_TAG);
            
            Sprite* i = Sprite::create("lead_bag1.png");
            i->setScale(1.2);
            i->setPosition(Vec2(0,0));
            addChild(i,BAG_TAG+1,BAG_TAG+1);
            
            Animation* animation = Animation::create();
            for (int i=1; i<=11; i++)
            {
                __String* image = __String::createWithFormat("lead_bag%i.png", i);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(image->getCString());
                Rect rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
                animation->addSpriteFrame(frame);
            }
            animation->setDelayPerUnit(0.15);
            Animate* animate = Animate::create(animation);
            auto actFunc=CallFuncN::create([&](Ref *pSender){
                ((Sprite *)pSender)->removeFromParent();
                if (playScene) {
                    //playScene->isGamePause = false; 王总,您真是坑我不辍
                }
                if (delegate) {
                    delegate->dripDelegateBagEffectFinish();
                }
                
                haveBag = true;
            });
            i->runAction(Sequence::create(animate,actFunc, NULL));
  
        }
    }
    else
    {
        if (getChildByTag(BAG_TAG)) {
            removeChildByTag(BAG_TAG);
            haveBag = false;
        }
    }
    
    
}