//
//  CheckpointScene.h
//  WaterWars
//
//  Created by je on 3/11/15.
//
//


#ifndef __beymac__CheckpointScene__
#define __beymac__CheckpointScene__


#include "cocos2d.h"
#include <CocosGUI.h>
#include "Checkpoint.h"
#include "CommonHeader.h"

USING_NS_CC;
using namespace ui;


class CheckpointScene:public Scene,public CheckpointDelegate{
public:
    
    CREATE_FUNC(CheckpointScene);
    
    virtual bool init();
    
    //关卡回调
    virtual void onClick(Checkpoint *cp);
    
    //点击开始游戏按钮
//    virtual void onClickStartGame();
private:
    
    //创建关卡层
    Layer *createCheckpointLayer(const int begin,const int count);
    
    Sprite *createChapter(const char *image);
    
//    SkillSelectPop *skillSelectPop;
    
    PopupLayer *unlockPop;
    
    Checkpoint *selectedCp;
};

#endif