//
//  TutorialScene.h
//  beymac
//
//  Created by lingzerg on 15/4/21.
//
//

#ifndef __beymac__TutorialScene__
#define __beymac__TutorialScene__

#include "cocos2d.h"
#include "cocosGUI.h"
#include <CocosGUI.h>
#include "CommonHeader.h"
#include "BeyMac.h"
#include "DottedLine.h"
#include "PlayScene.h"


using namespace cocos2d::ui;

USING_NS_CC;

#define GRID_SIZE 80.0          //箱子如果是一个矩形的大小

class TutorialScene : public PlayScene
{
public:
    TutorialScene();
    ~TutorialScene();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TutorialScene);
    //弹窗关闭按钮回调
    virtual void popupCloseCallBack(Ref *pSender);
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    
    // 0是死亡
    virtual void dripDelegateDead(BaseRole* node, int num);
    // 消除碰到的箱子
    virtual void dripDelegateRemoveHailBox(BaseRole* node, Box* box);
    // 碰到伞
    virtual void dripDelegateUmbrella(BaseRole* node);
    // 碰到水炮
    virtual void dripDelegateWaterBall(BaseRole* node,Box* box);
    // 碰到灰尘
    virtual void dripDelegatevirusesBox(BaseRole* node,int track);
    // 碰到能量
    virtual void dripDelegatePowerBox(BaseRole* node,Box* box);
    // 喷气背包动作完成回调
    virtual void dripDelegateBagEffectFinish();
    
    void destroyBox();
    void boxRemoveAction(Box *box);
    void removeActionChild(Node* node);
    
    void moveAllBox(float _y);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event);
    
    virtual void LevelInfoTextLayerDelegateClose();
    
private:
    void initData();
    void setBg();
    void onUpdate(float delta);
    void initBtn();
    void initPopup();
    // 显示提示
    void showTextHint(int step);
    void initHint();
    
    void moveBox();
    void removeTrackBox(int track);
    void showWaterBall();
    
    void attackBossCallback(Sprite * sprite);
    
    // 血条发光
    void lifeBarLight(int loop);
    // 能量发光
    void powerLight(int loop);
    // 技能发光
    void jinengLight(int loop);
    
private :
    bool isGamePause = false;
    // 角色是否可走
    bool isWalk = false;
    PopupLayer *popupPause;
    BeyMac *player;
    //参与游戏运算箱子的集合
    list<Box*> boxlist;
    DottedLine* line;
    
    Node* textHintNode;
    Label* text;
    Sprite* arrow1;
    Sprite* arrow2;
    Sprite* textTitle;
    
    int curStep = 1;
    
    bool showHint = true;
    
    int floor = 0;                      //当前层
    
    Health *health;                     //血条模块
    
    PopupLayer *popupStartTeach;
    PopupLayer *popupGetPrize;
    PopupLayer *popupWin;
    
    LayerColor* shadowlayer;
    // 能量数
    Label* txtGold;
    
    Sprite* arrowLeft;
    Sprite* arrowRight;
    Sprite* leftLight;
    Sprite* rightLight;
    
    LevelInfoTextLayer* infoLayer;
};

#endif /* defined(__beymac__TutorialScene__) */