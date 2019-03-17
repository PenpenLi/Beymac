//
//  UpgradeScene.h
//  beymac
//
//  Created by mumu on 15/5/27.
//
//

#ifndef __beymac__UpgradeScene__
#define __beymac__UpgradeScene__

#include "cocos2d.h"
#include "cocosGui.h"
#include "HeroRankLayer.h"
//#include "HeroUpgradeLayer.h"
#include "SkillUpgradeLayer.h"
#include "HeroUpgradeLayerNew.h"
#include "CommonHeader.h"

USING_NS_CC;
using namespace ui;

class UpgradeScene :public Layer,public PopupDelegate
{
public:
    UpgradeScene();
    virtual ~UpgradeScene();
    virtual bool init();
    CREATE_FUNC(UpgradeScene);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    //弹窗关闭按钮回调
    virtual void popupCloseCallBack(Ref *pSender);
    
    void initBG();
    void initBtn();
    void initLayer();
    void initPopup();
    
    static Scene* createScene();
    
    void setAllBtnUnSelect();
    void setAllLayerDispear();
    
    void unlockNewRoleSuccess();
    
    void refreshCrystal();
    
private:
    Label* txtPower;
    Label* txtCrystal;
    
    Button* btnRank;
//    Button* btnBayMac;
//    Button* btnLaser;
//    Button* btnTomago;
    Button* btnHero;
    Button* btnSkill;
    
    HeroRankLayer* layer1;
    HeroUpgradeLayerNew* layer2;
//    HeroUpgradeLayer* layer3;
//    HeroUpgradeLayer* layer4;
    SkillUpgradeLayer* layer5;
    
    PopupLayer *popupUnlockRole;
    Sprite* popupImage;
    int popupUnlockRoleNum;
};

#endif /* defined(__beymac__UpgradeScene__) */
