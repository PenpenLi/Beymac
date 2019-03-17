//
//  ShopScene.h
//  beymac
//
//  Created by je on 4/22/15.
//
//

#ifndef __beymac__ShopScene__
#define __beymac__ShopScene__

#include "cocos2d.h"
#include <CocosGUI.h>
#include "Payment.h"

USING_NS_CC;
using namespace ui;

class ShopScene:public Scene,public PaymentDelegate{
public:
    
    CREATE_FUNC(ShopScene);
    
    virtual bool init();
    
    //显示金币面板
    Sprite *createGoldPanel();
    
    //显示晶核面板
    Sprite *createCrystalPanel();
    
    //购买回调
    virtual void payResult(bool result);
    
private:
    
    void refreshData();
    
private:
    Button *btnGiftTag;
    Button *btnCrystalTag;
    
    Text *txtMyGold;
    Text *txtMyCrystal;
    
    int feedId;
};



#endif