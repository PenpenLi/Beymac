//
//  HeroUpgradeLayerNew.h
//  beymac
//
//  Created by mumu on 15/6/9.
//
//

#ifndef __beymac__HeroUpgradeLayerNew__
#define __beymac__HeroUpgradeLayerNew__

#include "cocos2d.h"
#include "cocosGui.h"
#include "HeroUpgradeCell.h"
#include "PopupLayer.h"
#include "Payment.h"

USING_NS_CC;
using namespace ui;

enum PopupType_Hero
{
    popupHero_null,
    popupHero_onekey,
    popupHero_unlock,
};

class HeroUpgradeLayerNew :public Layer, public HeroUpgradeCellDelegate, public PaymentDelegate
{
public:
    HeroUpgradeLayerNew();
    virtual ~HeroUpgradeLayerNew();
    virtual bool init();
    CREATE_FUNC(HeroUpgradeLayerNew);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch* touch, Event *pEvent);
    virtual void onTouchMoved(Touch* touch, Event *pEvent);
    virtual void onTouchEnded(Touch* touch, Event *pEvent);
    
    virtual void HeroUpgradeCellDelegateUnlockHero(RoleType type) ;
    virtual void HeroUpgradeCellDelegateOneKeyUp(RoleType type) ;
    
    void initCells();
    void initPopup();
    
    void oneKeyUpRoleSuccess();
    void unlockNewRoleSuccess();
    
    // 支付结果
    virtual void payResult(bool result);
    
private:
    
    // 当前触摸点
    Point touchCurPoint;
    float bgAllHeight;
    Node* cellNode;
    vector<HeroUpgradeCell*> cellList;
    
    PopupLayer* popupOneKeyUpRole;
    PopupLayer* popupUnlockRole;
    
    RoleType popupUnlockType;
    Sprite* popupUKImage;
    
    RoleType popupOneKeyType;
    Sprite* popupOKImage;
    
    PopupType_Hero popupType;
};

#endif /* defined(__beymac__HeroUpgradeLayerNew__) */
