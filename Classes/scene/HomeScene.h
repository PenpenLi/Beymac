//
//  Home.h
//  WaterWars
//
//  Created by je on 3/10/15.
//
//


#ifndef __beymac__HomeScene__
#define __beymac__HomeScene__

#include "cocos2d.h"
#include "CommonHeader.h"
#include "Rankws.h"
#include "RunnerAnimation.h"
#include "Payment.h"


USING_NS_CC;
using namespace ui;


class HomeScene:public Scene,public RankwsDelegate,public PaymentDelegate,public EditBoxDelegate {
public:
    CREATE_FUNC(HomeScene);
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event);
    
    
    //---------------rankws请求回调.........\
    //名称是否存在
    virtual void isUsernameExist(bool exist);
    //获取名称
    virtual void onGetUsername(bool succeed,std::string username);
    //注册名称
    virtual void onRegistered(bool succeed);
    //匹配到对手
    virtual void onMatchedWithOther(const int floor,const int rank,const int score,std::string username,const int myFloor,std::string myUsername);
    //离线模式
    virtual void onOffline();
    //---------------rankws请求回调........./
    
    //输入框
    virtual void editBoxEditingDidBegin( EditBox *editBox ); //开始时的函数
    
    virtual void editBoxEditingDidEnd( EditBox *editBox ); //结束时的函数
    
    virtual void editBoxReturn( EditBox *editBox ); //输入完后点击回车时的处理
    
    virtual void editBoxTextChanged( EditBox *editBox, const std::string &text ); //文字更改函数
    
    //输入框
    
    virtual void payResult(bool result);
    
private:
    
    void refreshData();
    
    void mute();    //静音
    
    void cancelMute();  //取消静音
    
    void switchLanguage();  //语言切换
    
private:
    PopupLayer *giftPop;
    
    PopupLayer *popupLeaveGame; // 退出游戏弹窗
    
    //神级挑战未过第三关提示弹窗
    PopupLayer *popCantEnterShenjitiaozhan;
    
    //大侠名称
    PopupLayer *namePop;
    
    //神级挑战_
    PopupLayer *rankPop;
    
    //匹配结果弹窗
    PopupLayer *matchPop;
    
    //ws回调
    Rankws *rankws;
    
    //设置层
    Sprite *shadowOfSetting;
    //能量数
    Text *txtGold;
    //晶核数
    Text *txtCrystal;
    //昵称输入框
    EditBox *m_editbox;
    //重复提示
    Text *noticeRepeat;
    
    //对手名字
    Text *opponentName;
    
    //对手层数
    Text *opponentFloor;
    
    //自己的名字
    Text *myName;
    
    //自己的层数
    Text *myFloor;
    
    
    //做特效动画用
    Sprite *txtTitle;
    Sprite *headSpr;
    Sprite *bodySpr;
    Sprite *footSpr;
    
    
    //闯关模式按钮
    Button *btnMission;
    
    //神级挑战按钮
    Button *btnWuJin;
    
    //排行榜按钮
    Button *btnRank;
    
    //基地升级按钮
    Button *btnCamp;
    
    //静音
    Button *btnMute;
    Button *btnCancelMute;
    
    //奔跑的小人
    RunnerAnimation *runner1;
    RunnerAnimation *runner2;
    RunnerAnimation *runner3;
    
    
};







#endif