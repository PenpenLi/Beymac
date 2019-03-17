//
//  PopupWinReward.cpp
//  BeyMac
//
//  Created by lingzerg on 15/5/19.
//
//

#include "PopupWinReward.h"
#include "CommonHeader.h"

PopupWinReward::PopupWinReward()
{
    
}

PopupWinReward::~PopupWinReward()
{
    
}



// 1 - 8 道具奖励
// 9 1钻石奖励
// 10 无奖励
// 11 12 奖励角色
PopupWinReward* PopupWinReward::createNode(int type, int count)
{
    auto node = new PopupWinReward();
    if(node && node->init(type,count)) {
        node->autorelease();
        return node;
    }
    return node;
}

bool PopupWinReward::init(int type,int count)
{
    if ( !Node::init() )
    {
        
        return false;
    }
    this->type = type;
    this->count = count;
    initData();
    return true;
}
// 1 - 8 道具奖励
// 9 1钻石奖励
// 10 无奖励
// 11 12 奖励角色
#pragma mark - initData
void PopupWinReward::initData()
{
    auto bg = LayerColor::create(Color4B::BLACK);
    bg->setPosition(0,0);
    bg->setOpacity(150);
    
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[](Touch *touch,Event *event){
        return true;
    };
    listener->onTouchMoved=[](Touch *touch,Event *event){
    };
    listener->onTouchEnded=[&](Touch *touch,Event *event){
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener ,bg);
    
    addChild(bg);
    
    if (type != 10) {
        if (type != 9) {
            auto tip = Sprite::create("img_bg_get_crystal.png");
            tip->setPosition(Vec2(320,1030));
            addChild(tip);
        }
        
        CommonData::getInstance()->addCrystal(1);
        
        
        auto round = Sprite::create("img_win_round.png");
        round->setPosition(MYSIZE.width/2+MYORIGIN.x, MYSIZE.height/2+MYORIGIN.y+200);
        addChild(round);
        round->setScale(0.5, 0.5);
        auto rotate = RotateBy::create(120, 7200);
        auto scate = ScaleBy::create(1, 3);
        //    auto forever = RepeatForever::create(rotate);
        round->runAction(Spawn::create(scate, rotate,NULL));
        
        
        
        
    }
    
    
    if (type <= 8) {
        
        auto skill = Sprite::create("img_win_newskill.png");
        skill->setPosition(Vec2(320,472));
        addChild(skill);
        
        CommonData::getInstance()->setRoleSkillLevel(type, 1);
        
        auto txt1 = Text::create();
        txt1->setString("您可以在升级基地查看，在游戏中使用");
        txt1->setPosition(Vec2(MYSIZE.width/2,320+44*2));
        txt1->setColor(Color3B(255,255,255));
        txt1->setFontSize(30);
        addChild(txt1);
        
        
        auto icon = Sprite::create(String::createWithFormat("img_prop_big_pic%d.png",type)->getCString());
        icon->setPosition(MYSIZE.width/2+MYORIGIN.x, MYSIZE.height/2+MYORIGIN.y+200);
        icon->cocos2d::Node::setScale(0.5);
        auto *iconScate = ScaleBy::create(1, 2);
        addChild(icon);
        icon->runAction(iconScate);
    }
    
    if (type == 9) {
        
        auto txt1 = Text::create();
        txt1->setString(String::createWithFormat("恭喜您成功过关,得到%d个晶核",count)->_string);
        txt1->setPosition(Vec2(MYSIZE.width/2,320+44*3));
        txt1->setColor(Color3B(255,255,255));
        txt1->setFontSize(30);
        addChild(txt1);
        
        auto txt2 = Text::create();
        txt2->setString("并获得抽奖机会");
        txt2->setPosition(Vec2(MYSIZE.width/2,320+44*2));
        txt2->setColor(Color3B(255,255,255));
        txt2->setFontSize(30);
        addChild(txt2);
        
///        img_win_crystal.png
        auto icon = Sprite::create("img_win_crystal.png");
        icon->setPosition(MYSIZE.width/2+MYORIGIN.x, MYSIZE.height/2+MYORIGIN.y+200);
        icon->cocos2d::Node::setScale(0.5);
        auto *iconScate = ScaleBy::create(1, 2);
        addChild(icon);
        icon->runAction(iconScate);
    }
    
    
    
    if (type == 11 || type == 12) {
        
        auto hero = Sprite::create("img_win_newhero.png");
        hero->setPosition(Vec2(320,472));
        addChild(hero);
        
        auto txt1 = Text::create();
        txt1->setString("您可以在升级基地查看，在游戏中可以切换");
        txt1->setPosition(Vec2(MYSIZE.width/2,320+44*2));
        txt1->setColor(Color3B(255,255,255));
        txt1->setFontSize(30);
        addChild(txt1);
    }
    
    if (type == 11 ) {
        auto icon = Sprite::create("img_upgrade_sister.png");
        icon->setPosition(MYSIZE.width/2+MYORIGIN.x, MYSIZE.height/2+MYORIGIN.y+200);
        icon->cocos2d::Node::setScale(0.5);
        auto *iconScate = ScaleBy::create(1, 2);
        addChild(icon);
        icon->runAction(iconScate);
    }
    
    if (type == 12) {
        auto icon = Sprite::create("img_upgrade_brother.png");
        icon->setPosition(MYSIZE.width/2+MYORIGIN.x, MYSIZE.height/2+MYORIGIN.y+200);
        icon->cocos2d::Node::setScale(0.5);
        auto *iconScate = ScaleBy::create(1, 2);
        addChild(icon);
        icon->runAction(iconScate);
    }
    auto confirm = cocos2d::ui::Button::create("img_window_green.png");
    
    if (type == 10) {
        confirm->setPosition(Vec2(SCREEN_WIDTH/2 - confirm->getContentSize().width/2,216));
    } else {
        confirm->setPosition(Vec2(465,216));
    }
    
    confirm->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            this->callBack(1);
            
        }
    });
    
    
    
    
    confirm->setTitleText("抽奖/下一关");
    confirm->setTitleColor(Color3B(12, 63, 10));
    confirm->setTitleFontSize(30);
    addChild(confirm);
   
    
    if(Manager::getInstance()->isQQInstalled()) {
        auto share = cocos2d::ui::Button::create("img_window_btn_red.png");
        
        if (type != 10) {
            share->setPosition(Vec2(186,216));
        } else {
            share->setPosition(Vec2(320,216));
        }
        share->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
            if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
                this->callBack(2);
            }
        });
        
        auto txtShare = Text::create();
        txtShare->setPosition(Vec2(132,44));
        txtShare->setString("分享");
        txtShare->setFontSize(40);
        txtShare->setColor(Color3B(255, 255, 255));
        share->addChild(txtShare);
        
        auto iconShare = Sprite::create("img_window_icon_qq.png");
        iconShare->setPosition(Vec2(68,44));
        share->addChild(iconShare);
        addChild(share);
    } else {
        confirm->setPositionX(SCREEN_WIDTH/2);
    }
    
    
    auto close = cocos2d::ui::Button::create("img_window_btn_close.png");
    close->setPosition(Vec2(590,1080));
    close->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            this->callBack(3);
        }
    });
    
    addChild(close);
    
    txt3 = Text::create();
    txt3->setString("最高层数:...");
    txt3->setPosition(Vec2(MYSIZE.width/2,320+44));
    txt3->setColor(Color3B(255,255,255));
    txt3->setFontSize(30);
    addChild(txt3);
    
    txt4 = Text::create();
    txt4->setString("当前排名:...");
    txt4->setPosition(Vec2(MYSIZE.width/2,320));
    txt4->setColor(Color3B(255,255,255));
    txt4->setFontSize(30);
    addChild(txt4);
}

void PopupWinReward::setFloor(int floor) {
    txt3->setString(String::createWithFormat("最高层数:%d",floor)->_string);
}

void PopupWinReward::setRank(int rank) {
    txt4->setString(String::createWithFormat("当前排名:%d",rank)->_string);
}

void PopupWinReward::callBack(int type) {
    if (delegate) {
        switch (type) {
            case 1:
                delegate->popupWinRewardDelegateLuckCallBack();
                break;
            case 2:
                delegate->popupWinRewardDelegateShareCallBack();
                break;
            case 3:
                delegate->popupWinRewardDelegateCloseCallBack();
                break;
            default:
                break;
        }
    }
}