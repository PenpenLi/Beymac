//
//  HeroUpgradeCell.h
//  beymac
//
//  Created by mumu on 15/6/9.
//
//

#ifndef __beymac__HeroUpgradeCell__
#define __beymac__HeroUpgradeCell__

#include "cocos2d.h"
#include "cocosGui.h"
#include "CommonHeader.h"
#include "BaseRole.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class HeroUpgradeCellDelegate
{
public:
    virtual void HeroUpgradeCellDelegateUnlockHero(RoleType type) = 0;
    virtual void HeroUpgradeCellDelegateOneKeyUp(RoleType type) = 0;
};

class HeroUpgradeCell :public Node
{
public:
    HeroUpgradeCell(RoleType type);
    virtual ~HeroUpgradeCell();
    virtual bool init();
    static HeroUpgradeCell* create(RoleType type);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    void initBG();
    void refreshBtn();
    void initAboutUpgrade();
    void refreshLevel();
    void oneKeyUpRoleSuccess();
    void unlockSuccess();
private:
    CC_SYNTHESIZE(RoleType, type, Type);
    int iType;
    int curlevel;
    // 升级按钮
    Button* btnUpgrade;
    // 一键升级
    Button* btnAllUpgrade;
    // 解锁
    Button* btnUnlock;
    
    Node* level1;
    Node* level2;
    Node* level3;
    Node* level4;

    
    CC_SYNTHESIZE(HeroUpgradeCellDelegate*, delegate, Delegate);
};

#endif /* defined(__beymac__HeroUpgradeCell__) */
