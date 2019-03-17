//
//  MysteryShopScene.h
//  beymac
//
//  Created by je on 6/11/15.
//
//

#ifndef __beymac__MysteryShopScene__
#define __beymac__MysteryShopScene__


#include "cocos2d.h"
#include <CocosGUI.h>
#include "Payment.h"

USING_NS_CC;
using namespace ui;

class MysteryShopScene:public Scene,public PaymentDelegate{
public:
    
    CREATE_FUNC(MysteryShopScene);
    
    virtual bool init();
    
    virtual void payResult(bool result);
    
private:
    
    //正在进行支付的计费编号
    int feedId;
};


#endif /* defined(__beymac__MysteryShopScene__) */




