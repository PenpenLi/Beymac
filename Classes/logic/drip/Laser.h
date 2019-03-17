//
//  Laser.h
//  beymac
//
//  Created by wang on 15/4/21.
//
//

#ifndef __beymac__Laser__
#define __beymac__Laser__

#include "cocos2d.h"
#include "BaseRole.h"

USING_NS_CC;

class Laser :public BaseRole
{
public:
    Laser();
    virtual ~Laser();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    static Laser* create();
    
    virtual void playLeftAction() ;
    virtual void playRightAction() ;
    virtual void playStopAction() ;

private:
    
};

#endif /* defined(__beymac__Laser__) */
