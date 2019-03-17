//
//  LevelInfoTextLayer.cpp
//  beymac
//
//  Created by mumu on 15/6/2.
//
//

#include "LevelInfoTextLayer.h"

LevelInfoTextLayer::LevelInfoTextLayer(int l,LevelInfoTextLayerDelegate* d)
{
    level = l;
    delegate = d;
    const char* str = __String::createWithFormat("level%d",level)->getCString();
    const char* str2 = LSTRINGLEVELINFO(str);
    
    if (strcmp("", str2) == 0) {
        if (delegate) {
            delegate->LevelInfoTextLayerDelegateClose();
        }
    }
    
    init();
}

LevelInfoTextLayer::~LevelInfoTextLayer()
{

}

bool LevelInfoTextLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }

    Sprite* hua = Sprite::create("img_story_deco.png");
    hua->setPosition(SCREEN_CENTER+Vec2(0,350));
    addChild(hua);
    
    Sprite* hua2 = Sprite::create("img_story_deco.png");
    hua2->setPosition(SCREEN_CENTER-Vec2(0,350));
    addChild(hua2);
    
    const char* str = __String::createWithFormat("level%d",level)->getCString();
    const char* str2 = LSTRINGLEVELINFO(str);
    
//    log(LSTRINGLEVELINFO(str));
    
    Label* info = Label::create();
    info->setTextColor(Color4B::WHITE);
    info->setAnchorPoint(Vec2(0.5,0.5));
    info->setString(str2);
    info->setSystemFontSize(30);
    info->setDimensions(SCREEN_WIDTH-200, 500);
    info->setPosition(SCREEN_CENTER);
    info->setHorizontalAlignment(TextHAlignment::CENTER);
    info->setVerticalAlignment(TextVAlignment::CENTER);
    addChild(info);
    info->setOpacity(0);
    
    auto actFunc=CallFuncN::create([&](Ref *pSender){
        if (delegate) {
            delegate->LevelInfoTextLayerDelegateClose();
        }
    });
    info->runAction(Sequence::create(DelayTime::create(0.1),FadeIn::create(0.7),DelayTime::create(1),FadeOut::create(0.5),actFunc, NULL));
    
    return true;
}

void LevelInfoTextLayer::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    
}

void LevelInfoTextLayer::onExit()
{
    Node::onExit();
}

LevelInfoTextLayer* LevelInfoTextLayer::create(int level,LevelInfoTextLayerDelegate* delegate)
{
    LevelInfoTextLayer* layer = new LevelInfoTextLayer(level,delegate);
    if (layer) {
        layer->autorelease();
        
    }
    else
    {
        delete layer;
        layer = NULL;
    }
    
    return layer;
}
