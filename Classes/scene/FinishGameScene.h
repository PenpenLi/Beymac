//
//  FinishGameScene.h
//  beymac
//
//  Created by mumu on 15/6/10.
//
//

#ifndef __beymac__FinishGameScene__
#define __beymac__FinishGameScene__

#include "cocos2d.h"

USING_NS_CC;

class FinishGameScene :public Layer
{
public:
    FinishGameScene();
    virtual ~FinishGameScene();
    virtual bool init();
    CREATE_FUNC(FinishGameScene);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static Scene* createScene();
    
    virtual bool onTouchBegan(Touch* touch, Event *pEvent);
    virtual void onTouchMoved(Touch* touch, Event *pEvent);
    virtual void onTouchEnded(Touch* touch, Event *pEvent);
private:
    bool isTouch;
};

#endif /* defined(__beymac__FinishGameScene__) */
