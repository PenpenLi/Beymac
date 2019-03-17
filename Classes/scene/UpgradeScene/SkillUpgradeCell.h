//
//  SkillUpgradeCell.h
//  beymac
//
//  Created by mumu on 15/5/29.
//
//

#ifndef __beymac__SkillUpgradeCell__
#define __beymac__SkillUpgradeCell__

#include "cocos2d.h"
#include "cocosGui.h"

USING_NS_CC;
using namespace ui;
using namespace std;

// 1 金钟罩
// 2 大白铁拳
// 3 时间减缓
// 4 喷气背包
// 5 追踪导弹（废弃）
// 6 伽马射线
// 7 饱和轰炸
// 8 次元门

class SkillUpgradeCellDelegate
{
public:
    virtual void SkillUpgradeCellDelegateUnlockSkill(int skillType) = 0;
    virtual void SkillUpgradeCellDelegateOneKeyUp(int skillType) = 0;
};


class SkillUpgradeCell :public Node
{
public:
    SkillUpgradeCell(int type);
    virtual ~SkillUpgradeCell();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    static SkillUpgradeCell* create(int type);
    
    void initBG();
    void refreshBtn();
    
    void oneKeyUpSkillSuccess();
    void unlockNewSkillSuccess();
    
private:

    CC_SYNTHESIZE(int, skillType, SkillType);
    
    Label* skillName;
    Label* skillInfo;
    Sprite* skillIcon;
    
    Button* level1;
    Button* level2;
    Button* level3;
    Button* level4;
    
    Button* allUpBtn;
    
    CC_SYNTHESIZE(SkillUpgradeCellDelegate*, delegate, Delegate);
};

#endif /* defined(__beymac__SkillUpgradeCell__) */
