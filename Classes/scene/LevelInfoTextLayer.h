//
//  LevelInfoTextLayer.h
//  beymac
//
//  Created by mumu on 15/6/2.
//
//

#ifndef __beymac__LevelInfoTextLayer__
#define __beymac__LevelInfoTextLayer__

#include "cocos2d.h"
#include "CommonHeader.h"

USING_NS_CC;
class LevelInfoTextLayerDelegate
{
public:
    virtual void LevelInfoTextLayerDelegateClose() = 0;
};

class LevelInfoTextLayer :public LayerColor
{
public:
    LevelInfoTextLayer(int level,LevelInfoTextLayerDelegate* delegate);
    virtual ~LevelInfoTextLayer();
    virtual bool init();
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static LevelInfoTextLayer* create(int level,LevelInfoTextLayerDelegate* delegate);
private:
    int level;
    CC_SYNTHESIZE(LevelInfoTextLayerDelegate*, delegate, Delegate);
};

#endif /* defined(__beymac__LevelInfoTextLayer__) */
