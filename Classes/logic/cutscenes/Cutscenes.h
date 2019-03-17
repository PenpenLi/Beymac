//
//  Cutscenes.h
//  WaterWars
//
//  过场动画 
//  Created by wang on 15/3/24.
//
//

#ifndef __WaterWars__Cutscenes__
#define __WaterWars__Cutscenes__

#include "cocos2d.h"
#include "cocosGUI.h"
#include "CommonHeader.h"

USING_NS_CC;
using namespace ui;

class CutscenesDelegate
{
public:
    virtual void CutscenesDelegateFinish() = 0;
};


class Cutscenes :public Node
{
public:
    Cutscenes(int type);
    virtual ~Cutscenes();
    virtual bool init();
    // type:0 开场动画  1 遇见boss动画
    static Cutscenes* createCutscenes(int type);
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
private:
    // 开场动画
    void playComic1();
    // boss动画
    void playComic2();
    
    ClippingNode* createClippingNode( Vec2 *verts );
    
    void showButton();
    void removeLayer();
    void layerDispear();
    
private:
    int  type;
    CC_SYNTHESIZE(CutscenesDelegate*, delegate, Delegate);
};

#endif /* defined(__WaterWars__Cutscenes__) */
