//
//  WaitingAnimationSprite.cpp
//  WaterWars
//
//  Created by je on 4/3/15.
//
//

#include "WaitingAnimationSprite.h"
#include "Macro.h"




Sprite *WaitingAnimationSprite::createWaitingAnimation()
{
    auto panel=Sprite::create();
    
    for(int i=0;i<3;i++){
        auto dot=Sprite::create("img_snow.png");
        
        dot->setPosition((i-1)*30, 0);
        
        ActionInterval *out = FadeOut::create(0.5);
        ActionInterval *in = FadeIn::create(0.5);
        
        dot->runAction(RepeatForever::create(Sequence::create(out,in, NULL)));
        
        panel->addChild(dot);
    }
    panel->setPosition(SCREEN_CENTER);
    
    return panel;
}


Sprite *WaitingAnimationSprite::createWaitingAnimationZhu()
{
    auto panel=Sprite::create();
    
    Sprite* text = Sprite::create("loading_zi.png");
    text->setPosition(Vec2(0, -100));
    panel->addChild(text);
    
    Sprite* zhu = Sprite::create("loading_pic.png");
    zhu->setPosition(Vec2(0, 20));
    panel->addChild(zhu);
    
    RotateBy* rotateTo = RotateBy::create(0.5, 180);
    Sequence* action = Sequence::create(CCDelayTime::create(1.5f),rotateTo,NULL);
    RepeatForever* repeat = RepeatForever::create(action);
    zhu->runAction(repeat);
    
    panel->setPosition(SCREEN_CENTER);
    
    return panel;
}