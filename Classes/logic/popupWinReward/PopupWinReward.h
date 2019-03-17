//
//  PopupWinReward.h
//  BeyMac
//
//  Created by lingzerg on 15/5/19.
//
//

#ifndef __BeyMac__PopupWinReward__
#define __BeyMac__PopupWinReward__

#include "cocos2d.h"
#include <CocosGUI.h>

USING_NS_CC;

using namespace cocos2d::ui;
using namespace ui;

class PopupWinReward;
class PopupWinRewardDelegate //代理,返回游戏结果
{
public:
    virtual void popupWinRewardDelegateCloseCallBack() = 0;
    virtual void popupWinRewardDelegateShareCallBack() = 0;
    virtual void popupWinRewardDelegateLuckCallBack() = 0;
};


class PopupWinReward : public Node
{
public:
    PopupWinReward();
    ~PopupWinReward();
    static PopupWinReward* createNode(int type,int count);
    bool init(int type,int count);
    CC_SYNTHESIZE(PopupWinRewardDelegate*, delegate, Delegate);
    void setFloor(int floor);
    void setRank(int rank);
private:
    int type;
    Text *txt3,*txt4;
    int count;
    void initData();
    void callBack(int type);
};

#endif /* defined(__BeyMac__PopupWinReward__) */
