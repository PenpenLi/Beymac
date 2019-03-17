//
//  GetPrizeHint.h
//  SuperPopPig
//
//  Created by wang on 15/1/19.
//
//

#ifndef __SuperPopPig__GetPrizeHint__
#define __SuperPopPig__GetPrizeHint__

#include "cocos2d.h"
#include "CommonHeader.h"

USING_NS_CC;

class GetPrizeHint :public Node
{
public:
    GetPrizeHint(int type);
    virtual ~GetPrizeHint();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    static GetPrizeHint* createPrizeHint(int type);
    
    Sequence* createHintAction();
private:
    int type;
    
};

#endif /* defined(__SuperPopPig__GetPrizeHint__) */
