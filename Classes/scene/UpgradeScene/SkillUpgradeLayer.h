//
//  SkillUpgradeLayer.h
//  beymac
//
//  Created by mumu on 15/5/29.
//
//

#ifndef __beymac__SkillUpgradeLayer__
#define __beymac__SkillUpgradeLayer__

#include "cocos2d.h"
#include "cocosGui.h"
#include "SkillUpgradeCell.h"
#include "PopupLayer.h"
#include "Payment.h"

USING_NS_CC;
using namespace ui;

enum PopupType_Skill
{
    popup_null,
    popup_onekey,
    popup_unlock,
};

class SkillUpgradeLayer :public Layer, public SkillUpgradeCellDelegate, public PaymentDelegate
{
public:
    static Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(SkillUpgradeLayer);
    
    virtual bool onTouchBegan(Touch* touch, Event *pEvent);
    virtual void onTouchMoved(Touch* touch, Event *pEvent);
    virtual void onTouchEnded(Touch* touch, Event *pEvent);
    
    virtual void SkillUpgradeCellDelegateUnlockSkill(int skillType) ;
    virtual void SkillUpgradeCellDelegateOneKeyUp(int skillType) ;
    
    void initCells();
    void initPopup();
    
    void oneKeyUpSkillSuccess();
    void unlockNewSkillSuccess();
    
    // 支付结果
    virtual void payResult(bool result);
    
private:

    
private:
    // 当前触摸点
    Point touchCurPoint;
    float bgAllHeight;
    Node* cellNode;
    vector<SkillUpgradeCell*> cellList;
    
    PopupLayer* popupUnlockSkill;
    PopupLayer* popupOneKey;
    
    int popupUnlockSkillNum;
    Sprite* popupUKImage;
    
    int popupOneKeyNum;
    Sprite* popupOKImage;
    
    PopupType_Skill popupType;
};

#endif /* defined(__beymac__SkillUpgradeLayer__) */
