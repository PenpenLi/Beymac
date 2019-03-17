//
//  StartGameTextScene.h
//  beymac
//
//  Created by mumu on 15/6/4.
//
//

#ifndef __beymac__StartGameTextScene__
#define __beymac__StartGameTextScene__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class StartGameTextScene :public LayerColor
{
public:
    StartGameTextScene();
    virtual ~StartGameTextScene();
    virtual bool init();
    CREATE_FUNC(StartGameTextScene);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static Scene* createScene();
    void showSnow();
    
    virtual bool onTouchBegan(Touch* touch, Event *pEvent);
    virtual void onTouchMoved(Touch* touch, Event *pEvent);
    virtual void onTouchEnded(Touch* touch, Event *pEvent);
private:
    int totalLength;
    int curLength;
    string str;
    Label* info;
    bool isTouch;
};

#endif /* defined(__beymac__StartGameTextScene__) */
