//
//  SkillSelectScene.h
//  beymac
//
//  Created by je on 6/8/15.
//
//

#ifndef __beymac__SkillSelectScene__
#define __beymac__SkillSelectScene__


#include "cocos2d.h"
#include <CocosGUI.h>
#include "PopupLayer.h"
#include "SkillWithImgSprite.h"
#include "Payment.h"

USING_NS_CC;
using namespace ui;



class SkillSelectScene:public Scene,public PaymentDelegate{
public:
    
    SkillSelectScene(int number);
    
    static SkillSelectScene *createScene(int number);
    
    virtual bool init();
    
    void show();
    
//    //点击开始游戏按钮
    void onClickStartGame();
    
    virtual void onEnter();
    
    
    virtual void payResult(bool result);
    
public:
    //挑战模式所需参数
    int rank;
    int floor;
    std::string username;
    //是否离线模式
    bool isOffline;
    
    
private:
    int number;
    
    int state;
    
//    //是否在支付过程中
//    int paymentCount;
    
    PopupLayer *unlockPop;
    
    
    
    Sprite *bossSpr;
    
    Text *skillTitle;
    
    Sprite *skillImg;
    
    Button *btnArray[4];
    
    
    //三个技能。。
    SkillWithImgSprite *sws1;
    SkillWithImgSprite *sws2;
    SkillWithImgSprite *sws3;
    
    
    //教程-----------------------/
    
    //原本就需要的
    Button *btnStart;
    
    //专用
    Sprite *tt1Text;
    Sprite *tt2;
    Button *tt3;
    Sprite *tt5;
    
    //教程-----------------------//
    
    
};


#endif /* defined(__beymac__SkillSelectScene__) */
