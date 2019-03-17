//
//  CheckpointScene.cpp
//  WaterWars
//
//  Created by je on 3/11/15.
//
//


#include "CheckpointScene.h"
#include <CocosGUI.h>
#include "Macro.h"
#include "HomeScene.h"
#include "Background.h"
#include "PlayScene.h"
#include "Manager.h"
#include "TutorialScene.h"
#include "ButtonFactory.h"
#include "ShopScene.h"
#include "Checkpoint.h"
#include "SkillSelectScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSHelper.h"
#endif


#define CP_LAYER_TOP 2550
#define CP_LAYER_BOTTOM SCREEN_HEIGHT-200


USING_NS_CC;
using namespace cocos2d::ui;

Layer *checkpointLayer;
float originY;
float offset;//关卡层向上偏移量


//关卡按钮回调
void CheckpointScene::onClick(Checkpoint *cp)
{
    int number=cp->number;
    int state=cp->state;
    log("关卡号：%d,状态:%d",number,state);

    if(number==1){
        Director::getInstance()->replaceScene(TutorialScene::createScene());
        return;
    }
    
//    selectedCp=cp;
//    skillSelectPop->show(number);
    
    Director::getInstance()->replaceScene(SkillSelectScene::createScene(number));
    
    
}

////点击开始游戏按钮
//void CheckpointScene::onClickStartGame()
//{
//    if(this->selectedCp->state==CHECKPOINT_LOCKED){
//        //锁定的关卡
//        unlockPop->show();
//    }else{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        IOSHelper::hidenAdBar();
//#endif
//        Director::getInstance()->replaceScene(PlayScene::createScene(this->selectedCp->number));
//    }
//    
//}


// on "init" you need to initialize your instance
bool CheckpointScene::init()
{
    //背景
    auto bg=Background::createBackground();
    
    //能量
    auto sprGold=Sprite::create("img_number_bg_gold.png");
    sprGold->setPosition(110, SCREEN_HEIGHT-50);
    //能量值
    auto txtGoldNo=Text::create();
    txtGoldNo->setFontSize(32);
    txtGoldNo->setString(StringUtils::format("%d",CommonData::getInstance()->getEnergy()));
    txtGoldNo->cocos2d::Node::setPosition(115, 45);
    sprGold->addChild(txtGoldNo);
    this->addChild(sprGold,1);
    
    //晶核
    auto sprCrystal=Sprite::create("img_number_bg_crystal.png");
    sprCrystal->setPosition(SCREEN_WIDTH-110, SCREEN_HEIGHT-50);
    //晶核数
    auto txtCrystalNo=Text::create();
    txtCrystalNo->setFontSize(32);
    txtCrystalNo->setString(StringUtils::format("%d",CommonData::getInstance()->getCrystal()));
    txtCrystalNo->cocos2d::Node::setPosition(115, 45);
    sprCrystal->addChild(txtCrystalNo);
    this->addChild(sprCrystal,1);
    
    
    //遮挡层(button实现)
    auto btnShade=Button::create("img_blue.png");
    btnShade->loadTexturePressed("img_blue.png");
    btnShade->cocos2d::Node::setPosition(SCREEN_WIDTH/2,btnShade->getContentSize().height/2);
    
    //返回
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_back.png");
    btnBack->setPosition(Point(70,60));
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(HomeScene::create());
        }
    });
    
    //商店按钮
    auto btnShop=Button::create(LSTRINGIMAGE("img_btn_shop_mainpage"));
    btnShop->setPosition(Vec2(SCREEN_WIDTH-120,60));
    btnShop->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->pushScene(ShopScene::create());
        }
    });
    
    //关卡层
    checkpointLayer= this->createCheckpointLayer(1,50);
    checkpointLayer->setPositionY(checkpointLayer->getPositionY()+offset);
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[](Touch *touch,Event *event){
        originY=checkpointLayer->getPositionY();//移动：起始位置
        return true;
    };
    listener->onTouchMoved=[](Touch *touch,Event *event){
        
        float distance=touch->getLocation().y-touch->getStartLocation().y;//移动的距离
        
        //判断超过顶部和底部的范围
        if(distance>0&&originY+distance>=CP_LAYER_TOP){
            checkpointLayer->setPositionY(CP_LAYER_TOP);
        }else if(distance<0&&originY+distance<=CP_LAYER_BOTTOM){
            checkpointLayer->setPositionY(CP_LAYER_BOTTOM);
        }else{
            checkpointLayer->setPositionY(originY+distance);//随着手移动
        }
        
    };
    listener->onTouchEnded=[&](Touch *touch,Event *event){
        originY=checkpointLayer->getPositionY();
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    //技能选择弹窗
//    skillSelectPop=SkillSelectPop::create(this);
    
    //解锁关卡弹窗
    unlockPop=PopupLayer::create("img_window_bg.png");
    unlockPop->setTitleImage("img_window_title3.png");
    unlockPop->setCloseButton("img_window_btn_close.png");
    unlockPop->setPosition(SCREEN_CENTER);
    auto lockSpr=Sprite::create("img_window_paper2.png");
    unlockPop->addChild(lockSpr);
    //解锁按钮
    auto btnUnlock=Button::create("img_window_green.png");
    btnUnlock->setTitleText("解锁");
    btnUnlock->setTitleFontSize(40);
    btnUnlock->cocos2d::Node::setPosition(0, -230);
    btnUnlock->setTitleColor(Color3B::BLACK);
    btnUnlock->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            selectedCp->unlock();
            this->unlockPop->hide();
        }
    });
    unlockPop->addChild(btnUnlock);
    
    
    
    
    this->addChild(bg);
    this->addChild(btnBack,1);
    this->addChild(btnShop,1);
    this->addChild(checkpointLayer);
    this->addChild(btnShade);
//    this->addChild(skillSelectPop,90);
    this->addChild(unlockPop,100);
    return true;
}


//创建关卡层
Layer *CheckpointScene::createCheckpointLayer(const int begin,const int count)
{
    //测试代码
//    CommonData::getInstance()->put(1, 1);
//    CommonData::getInstance()->put(2, 1);
//    CommonData::getInstance()->put(3, 1);
//    CommonData::getInstance()->put(4, 1);
    
    
    
    //更新第一个锁定的关卡号
    for(int i=0;i<50;i++){
        int state=CommonData::getInstance()->get(i+1);
        if(state==CHECKPOINT_LOCKED){
            Checkpoint::firstLockedCheckpoint=i+1;
            log("第一个锁定关卡号：%d",Checkpoint::firstLockedCheckpoint);
            break;
        }
    }
    
    
    
    
    //最大已通过关卡号
    int maxPlayedCP=0;
    for(int i=0;i<count;i++)
    {
        int level=CommonData::getInstance()->get(i+1);
        if(level==1){
            maxPlayedCP=i+1;
        }
    }
    log("最大已玩关卡号:%d",maxPlayedCP);
    
    
    //关卡层
    auto checkpointLayer=Layer::create();
    
    auto numberPanel=Sprite::create();
    float x=0,y=170;//y表示全部数字的初始位置
    for(int i=begin-1;i<count;i++)
    {
        if(i%5==0){
            x=0;
            y-=100;
        }
        if(i%10==0){
            //虚线
            if(i/10>=1){
                auto dottedLine=Sprite::create("img_choose_line.png");
                dottedLine->setPosition(SCREEN_WIDTH/2-100,y+30);
                checkpointLayer->addChild(dottedLine);
            }
            
            //章节图片--文件名
            std::string imgFilename="img_choose_pic";
            imgFilename.append(StringUtils::format("%d",i/10+1));
            imgFilename.append(".png");
            //章节图片--chapter
            auto chapter=this->createChapter(imgFilename.c_str());
            checkpointLayer->addChild(chapter);
            chapter->setPosition(SCREEN_WIDTH/2-100,-50-500*(i/10));//500表示每一章的图片间距
            y-=300;//数字的Y轴下移
            
            int currentChapter=maxPlayedCP/10+1;
            if(currentChapter>=2){
                if(currentChapter>4){
                    currentChapter=4;
                }
                offset=(currentChapter-1)*490;
            }
            
        }
        
        //关卡按钮
        auto cp=Checkpoint::create(i+1,this);
        
        cp->cocos2d::Node::setPosition(x,y);
        numberPanel->addChild(cp);
        x+=120;
        
    }
    
    numberPanel->setPositionX(-20);
    checkpointLayer->addChild(numberPanel);
    checkpointLayer->setPosition(100,CP_LAYER_BOTTOM);
    
    
    return checkpointLayer;
}

//创建章节
Sprite *CheckpointScene::createChapter(const char *image)
{
    Sprite *spr;
    if(image){
        spr=Sprite::create(image);
    }else{
        spr=Sprite::create();
        auto dr=DrawNode::create();
        dr->drawRect(Vec2(0,0), Vec2(450,150), Color4F::YELLOW);
        spr->addChild(dr);
    }
    return spr;
}


