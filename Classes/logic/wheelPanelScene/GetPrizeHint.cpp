//
//  GetPrizeHint.cpp
//  SuperPopPig
//
//  Created by wang on 15/1/19.
//
//

#include "GetPrizeHint.h"
#include "Macro.h"
#include "MMLocalizedString.h"

GetPrizeHint::GetPrizeHint(int type)
{
    this->type = type;
    init();
}

GetPrizeHint::~GetPrizeHint()
{

}

GetPrizeHint* GetPrizeHint::createPrizeHint(int type)
{
    GetPrizeHint* node = new GetPrizeHint(type);
    if (node) {
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }
    return node;
}

bool GetPrizeHint::init()
{
    if (!Node::init())
    {
        return false;
    }

    Sprite* bg = Sprite::create("img_get_gold_bg.png");
    Size size = bg->getContentSize();
    bg->setPosition(Vec2(SCREEN_CENTER.x, size.height/2));
    addChild(bg);
    
//    LabelAtlas* content = LabelAtlas::create(NUM_TO_STR(type), "img_get_gold_number.png", 28, 38, '0');
    Label* content;
    __String* str = __String::createWithFormat(LSTRING("GetPrizeGold"),type);
    content = Label::createWithSystemFont(str->getCString(), "arial", 45);
//    if (type == 0) {
//        // 获得一个金币
//        content = Label::createWithSystemFont(LSTRING("GetPrizeGold1"), "arial", 45);
//    }
//    else if (type == 1)
//    {
//        // 获得3个金币
//        content = Label::createWithSystemFont(LSTRING("GetPrizeGold3"), "arial", 45);
//    }
//    else if (type == 2)
//    {
//        // 获得一个钢盔
//        content = Label::createWithSystemFont(LSTRING("GetPrizeHelmet"), "arial", 45);
//    }
//    else if (type == 3)
//    {
//        // 获得一个时间减缓
//        content = Label::createWithSystemFont(LSTRING("GetPrizeInvincible"), "arial", 45);
//    }
//    else if (type == 4)
//    {
//        // 获得一个无敌
//        content = Label::createWithSystemFont(LSTRING("GetPrizeTime"), "arial", 45);
//    }
//    else if (type == 5)
//    {
//        // 获得一个晶核
//        content = Label::createWithSystemFont(LSTRING("GetPrizeCrystal"), "arial", 45);
//    }

    if (content) {
        content->setAnchorPoint(Vec2(0.5, 0.5));
        content->setPosition(bg->getPosition());
        content->setColor(Color3B::BLACK);
        addChild(content);
    }
    
    return true;
}

void GetPrizeHint::onEnter()
{
    CCNode::onEnter();
}

void GetPrizeHint::onExit()
{
    CCNode::onExit();
}

Sequence* GetPrizeHint::createHintAction()
{
    MoveTo* moveto = MoveTo::create(0.5, Vec2(0, SCREEN_CENTER.y-50));
    EaseBackOut* easeOut = EaseBackOut::create(moveto);
    
    MoveTo* moveto2 = MoveTo::create(0.5, Vec2(0, SCREEN_LEFT_UP.y+100));
    EaseBackIn* easeIn = CCEaseBackIn::create(moveto2);
    Sequence* action = Sequence::create(easeOut,CCDelayTime::create(1.0),easeIn,CCDelayTime::create(0.5),NULL);
    
    return action;
}
