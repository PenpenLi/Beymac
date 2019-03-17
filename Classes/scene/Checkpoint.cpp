//
//  Checkpoint.cpp
//  beymac
//
//  Created by je on 5/27/15.
//
//

#include "Checkpoint.h"
#include "CommonData.h"
#include "CommonHeader.h"
#include "TutorialScene.h"
#include "PlayScene.h"

#define BEGIN 1
#define END 50


USING_NS_CC;
using namespace ui;



int Checkpoint::firstLockedCheckpoint;

Checkpoint *Checkpoint::create(const int number,CheckpointDelegate *callback)
{
    auto cp=new Checkpoint();
    
    cp->number=number;
    
    if(callback){
        cp->callback=callback;
    }
    
    cp->btn=Button::create();
    
    cp->addChild(cp->btn);
    
    if(cp&&cp->init()){
        cp->autorelease();
    }
    
    
    return cp;
}

bool Checkpoint::init()
{
    
    //状态
    this->state=CommonData::getInstance()->get(this->number);
    
    if(firstLockedCheckpoint==this->number){
        this->state=CHECKPOINT_PLAYABLE;
    }
    
    if(callback){
        this->btn->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                //设置关卡号和状态
                callback->onClick(this);
            }
        });
    }
    
    
    //设置贴图
    if(CHECKPOINT_PLAYED==state){
        btn->loadTextureNormal("img_choose_btn_complete.png");
    }else if(CHECKPOINT_PLAYABLE==state){
        btn->loadTextureNormal("img_choose_btn.png");
    }else{
        btn->loadTextureNormal("img_choose_btn_lock.png");
    }
    
    
    //加入特殊角色
    auto role=Sprite::create();
    role->setPosition(53, 43);
    if(number==7){
        role->setTexture("img_hero_man_light.png");
        btn->addChild(role);
    }else if(number==3){
        role->setTexture("img_hero_woman_light.png");
        btn->addChild(role);
    }else{
        //加上数字数字        
        if(state==CHECKPOINT_PLAYED||state==CHECKPOINT_PLAYABLE){
            std::string strNo=StringUtils::format("%d",number);
            auto imgNo=LabelAtlas::create(strNo, "img_choose_number.png", 22, 30, 48);
            imgNo->setPosition(48-imgNo->getContentSize().width/2,15);
            btn->addChild(imgNo,100);
        }
    }

    //bonus
    if(number%5==0&&number%10!=0){
        auto bonus=Sprite::create("img_choose_bonus.png");
        bonus->setPosition(btn->getContentSize().width/2, 75);
        btn->addChild(bonus);
    }
    
    
    return true;
}

void Checkpoint::unlock()
{
    CommonData::getInstance()->put(this->number, CHECKPOINT_PLAYABLE);
    
    state=CHECKPOINT_PLAYABLE;
    
    this->btn->loadTextureNormal("img_choose_btn.png");
    //加上数字数字
    std::string strNo=StringUtils::format("%d",number);
    auto imgNo=LabelAtlas::create(strNo, "img_choose_number.png", 22, 30, 48);
    imgNo->setPosition(48-imgNo->getContentSize().width/2,15);
    btn->addChild(imgNo,100);
}












