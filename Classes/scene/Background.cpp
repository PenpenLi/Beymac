//
//  HomeBackground.cpp
//  WaterWars
//
//  Created by je on 3/23/15.
//
//

#include "Background.h"
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

Background* Background::createBackground()
{
    auto bg=new Background();
    if(bg&&bg->init())
    {
        bg->autorelease();
        return bg;
    }
    return nullptr;
}

bool Background::init(){
    auto bgImg=Sprite::create("img_bg.jpg");
    this->addChild(bgImg);
    bgImg->setPosition(SCREEN_CENTER);
    return true;
}

void Background::addCloud()
{
    //云朵1
    auto imgCloud1=Sprite::create("img_cloud1.png");
    imgCloud1->setPosition(-100,SCREEN_HEIGHT-220);
    imgCloud1->setTag(33);
    //云朵1的动作
    {
        auto actMoveto=MoveTo::create(90, Vec2(SCREEN_WIDTH+100,imgCloud1->getPosition().y));
        auto actFunc=CallFuncN::create([&](Ref *pSender){
            ((Sprite *)pSender)->setPosition(-100,SCREEN_HEIGHT-200);
        });
        auto actSequence=Sequence::create(actMoveto,actFunc, NULL);
        auto actRepeat=RepeatForever::create(actSequence);
        imgCloud1->runAction(actRepeat);
    }
    //云朵2
    auto imgCloud2=Sprite::create("img_cloud2.png");
    imgCloud2->setPosition(SCREEN_WIDTH*0.8,SCREEN_HEIGHT-90);
    //云朵2的动作
    {
        auto actMoveto=MoveTo::create(50, Vec2(SCREEN_WIDTH+100,imgCloud2->getPosition().y));
        auto actFunc=CallFuncN::create([&](Ref *pSender){
            ((Sprite *)pSender)->setPosition(-100,SCREEN_HEIGHT-90);
        });
        auto actSequence=Sequence::create(actMoveto,actFunc, NULL);
        auto actRepeat=RepeatForever::create(actSequence);
        imgCloud2->runAction(actRepeat);
    }
    
    //云朵3
    auto imgCloud3=Sprite::create("img_cloud3.png");
    imgCloud3->setPosition(SCREEN_WIDTH*0.1,SCREEN_HEIGHT-40);
    //云朵2的动作
    {
        auto actMoveto=MoveTo::create(40, Vec2(SCREEN_WIDTH+100,imgCloud3->getPosition().y));
        auto actFunc=CallFuncN::create([&](Ref *pSender){
            ((Sprite *)pSender)->setPosition(-100,SCREEN_HEIGHT-40);
        });
        auto actSequence=Sequence::create(actMoveto,actFunc, NULL);
        auto actRepeat=RepeatForever::create(actSequence);
        imgCloud3->runAction(actRepeat);
    }
    
    this->addChild(imgCloud1);
    this->addChild(imgCloud2);
    this->addChild(imgCloud3);
}



void Background::addWave()

{
    
    int waveWidth=7;
    
    //波浪1
    
    auto imgWave1=Sprite::create("img_sea1.png");
    
    imgWave1->setPosition(SCREEN_WIDTH/2,95);
    
    //波浪1动作
    
    {
        
        auto actMoveByUp=MoveTo::create(1.2, Vec2(SCREEN_WIDTH/2,imgWave1->getPositionY()+waveWidth*2));
        
        auto actMoveByMid=MoveTo::create(1.2, Vec2(SCREEN_WIDTH/2,imgWave1->getPositionY()));
        
        auto actMoveByDown=MoveTo::create(1.2, Vec2(SCREEN_WIDTH/2,imgWave1->getPositionY()-waveWidth*2));
        
        auto actSequence=Sequence::create(actMoveByUp,actMoveByMid,actMoveByDown,actMoveByMid, NULL);
        
        auto actRepeat=RepeatForever::create(actSequence);
        
        imgWave1->runAction(actRepeat);
        
    }
    
    
    
    //波浪2
    
    auto imgWave2=Sprite::create("img_sea2.png");
    
    imgWave2->setPosition(SCREEN_WIDTH/2,270);
    
    //波浪2动作
    
    {
        
        auto actMoveByUp=MoveTo::create(1.4, Vec2(SCREEN_WIDTH/2,imgWave2->getPositionY()+waveWidth*2));
        
        auto actMoveByMid=MoveTo::create(1.4, Vec2(SCREEN_WIDTH/2,imgWave2->getPositionY()));
        
        auto actMoveByDown=MoveTo::create(1.4, Vec2(SCREEN_WIDTH/2,imgWave2->getPositionY()-waveWidth*2));
        
        auto actSequence=Sequence::create(actMoveByMid,actMoveByUp,actMoveByMid,actMoveByDown, NULL);
        
        auto actRepeat=RepeatForever::create(actSequence);
        
        imgWave2->runAction(actRepeat);
        
    }
    
    
    
    //波浪3
    
    auto imgWave3=Sprite::create("img_sea3.png");
    
    imgWave3->setPosition(SCREEN_WIDTH/2,290);
    
    //波浪3动作
    
    {
        
        auto actMoveByUp=MoveTo::create(1.6, Vec2(SCREEN_WIDTH/2,imgWave3->getPositionY()+waveWidth*2));
        
        auto actMoveByMid=MoveTo::create(1.6, Vec2(SCREEN_WIDTH/2,imgWave3->getPositionY()));
        
        auto actMoveByDown=MoveTo::create(1.6, Vec2(SCREEN_WIDTH/2,imgWave3->getPositionY()-waveWidth*2));
        
        auto actSequence=Sequence::create(actMoveByDown,actMoveByMid,actMoveByUp,actMoveByMid,NULL);
        
        auto actRepeat=RepeatForever::create(actSequence);
        
        imgWave3->runAction(actRepeat);
        
    }
    
    
    
    this->addChild(imgWave3);
    
    this->addChild(imgWave2);
    
    this->addChild(imgWave1);
    
}

