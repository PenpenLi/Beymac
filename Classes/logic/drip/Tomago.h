//
//  Tamago.h
//  beymac
//
//  Created by wang on 15/4/21.
//
//

#ifndef __beymac__Tamago__
#define __beymac__Tamago__

#include "cocos2d.h"
#include "BaseRole.h"

USING_NS_CC;

class Tomago :public BaseRole
{
public:
    Tomago();
    virtual ~Tomago();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    static Tomago* create();
    
    virtual void playLeftAction() ;
    virtual void playRightAction() ;
    virtual void playStopAction() ;
private:
    
};

#endif /* defined(__beymac__Tamago__) */
