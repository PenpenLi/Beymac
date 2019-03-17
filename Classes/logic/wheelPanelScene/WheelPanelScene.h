//
//  WheelPanelScene.h
//  SuperPopPig
//
//  Created by wang on 15/1/19.
//
//

#ifndef __SuperPopPig__WheelPanelScene__
#define __SuperPopPig__WheelPanelScene__

#include "cocos2d.h"
#include "cocosGUI.h"

USING_NS_CC;

using namespace ui;

enum ButtonState
{
    nothingState,
    startWheelState,
    getPrizeState,

};

class WheelPanelScene :public Layer
{
public:
    WheelPanelScene();
    virtual ~WheelPanelScene();
    virtual bool init();
    CREATE_FUNC(WheelPanelScene);
    virtual void onEnter();
    virtual void onExit();
    
    static Scene* createWheelPanelScene(int level);

    void setLevel(int level);

private:
    
    Sprite*     wheel;
    int         rollRound;
    bool        isRolling;
    int         result;
    ButtonState buttonState;
    // 玩转盘的次数
    int         count;
    // 玩转盘的钱数
    int         money;
    Button*     startBtn;
    Button*     nextBtn;
    
    int         curLevel;
    
private:
    // 转盘开始转
    void  wheelStartRoll();
    // 转盘转完一圈
    void  wheelRollFinish();
    // 转盘完全转完
    void  wheelFinish();
    // 得到转盘结果
    int   getWheelResult();
    // 退出转盘
    void  finishScene();
    // 雪花
    void showSnow();
    // 获得金币提示消失
    void  hintFinish();
    
};

#endif /* defined(__SuperPopPig__WheelPanelScene__) */
