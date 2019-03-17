//
//  SkillWithImgSprite.cpp
//  beymac
//
//  Created by je on 5/29/15.
//
//

#include "SkillWithImgSprite.h"




SkillWithImgSprite *SkillWithImgSprite::create(){
    
    auto sws=new SkillWithImgSprite();
    
    if(sws&&sws->init()){
        sws->autorelease();
    }
    
    return sws;
}

bool SkillWithImgSprite::init()
{
    //几率掉落技能_内容
    auto unlockSpr=Sprite::create();
//    unlockSpr->setPosition(160,15);
    title=Text::create();
    title->setFontSize(22);
    title->setAnchorPoint(Vec2(0, 0.5));
    title->setString("无");
    unlockSpr->addChild(title);
    this->addChild(unlockSpr);
    //带上技能的小号图标
    img=Sprite::create();
    img->setScale(0.105);
    unlockSpr->addChild(img);
    
    
    return true;
}

void SkillWithImgSprite::show(string title,string img)
{
    this->setAnchorPoint(Vec2(0,0.5));
    
    if(!title.empty()){
        this->title->setString(title);
        if(!img.empty()){
            this->img->setTexture(img);
            this->img->setPositionX(this->title->getContentSize().width+15);
            this->img->setVisible(true);
        }else{
            this->img->setVisible(false);
        }
    }
    
    
}