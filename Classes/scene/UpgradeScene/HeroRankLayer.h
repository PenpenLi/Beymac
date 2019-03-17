//
//  HeroRankLayer.h
//  beymac
//
//  Created by mumu on 15/5/28.
//
//

#ifndef __beymac__HeroRankLayer__
#define __beymac__HeroRankLayer__

#include "cocos2d.h"
#include "cocosGui.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class HeroRankLayer :public Layer
{
public:
    HeroRankLayer();
    virtual ~HeroRankLayer();
    virtual bool init();
    CREATE_FUNC(HeroRankLayer);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    void initBG();
    void initRoleInfo();
    
    void refreshBtn();
    
    // 更新英雄排序
    void refreshHero();
    
private:
    Sprite* bg1;
    Sprite* bg2;
    Sprite* bg3;
    
    Node* nodeBeymac;
    Node* nodeLaser;
    Node* nodeTomago;
    
    vector<int> ranklist;
    
    Button* btn1_down;
    Button* btn2_up;
    Button* btn2_down;
    Button* btn3_up;
};

#endif /* defined(__beymac__HeroRankLayer__) */
