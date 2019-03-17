//
//  PlaySence.h
//  PuzzleBobble2
//
//  Created by lingzerg on 15/3/3.
//
//

#ifndef __PuzzleBobble2__PlayScene__
#define __PuzzleBobble2__PlayScene__

#define CELL_HORIZONTAL_SIZE 8  //水平多少行
#define FALL_SIZE 5             //最大下落数量

#define GRID_RADIUS_SIZE 40.0   //箱子半径
#define GRID_SIZE 80.0          //箱子如果是一个矩形的大小
#define GRID_WIDTH 80           //箱子宽
#define GRID_HEIGHT 80          //箱子高
#define BOX_SPEED 10            //箱子下落速度

#define COLOR_BAR 120   

#define TIME_WUDI 6                  //无敌时间

#include "cocos2d.h"
#include "cocosGUI.h"

#include "Box.h"
#include "Manager.h"
#include "Tip.h"
#include "BeyMac.h"
#include "DottedLine.h"
#include "Health.h"
#include "CommonHeader.h"
#include "WebService.h"
#include "Jishiqi.h"
#include "Cutscenes.h"
#include "Monster.h"
#include "PopupWinReward.h"
#include "PropCd.h"
#include "LaserBullet.h"
#include "SLaserBulletArray.h"
#include <CocosGUI.h>
#include "ReadDataFromMap.h"
#include "LevelInfoTextLayer.h"
#include "Payment.h"


class PlaySceneState;

using namespace cocos2d::ui;
using namespace ui;
#define GOLD75 1
#define GOLD105 5

USING_NS_CC;



class PlayScene;
class PlaySceneDelegate //代理,返回游戏结果
{
public:
    virtual bool PlaySceneDelegateCallback(int result) = 0;
};

class PlayScene :public Layer,public LevelInfoTextLayerDelegate, public BaseRoleDelegate,public WebServiceDelegate, public PopupDelegate ,public BaseBulletDelegate ,public CutscenesDelegate, public MonsterDelegate,PopupWinRewardDelegate {
    
public:
    bool isGamePause = false;
    
public:
    
    PlayScene();
    virtual ~PlayScene();
    
    static Scene* createScene();
    static Scene* createScene(int level);
    static Scene* createScene(int level, const char *name, int targetFloor);
    bool init(int level, const char *name, int targetFloor);
    void onUpdate(float delta);
    float attackPlus();
    void onEnter();
    void onExit();
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);

    // 0是死亡
    virtual void dripDelegateDead(BaseRole* node, int num);
    // 消除碰到的箱子
    virtual void dripDelegateRemoveHailBox(BaseRole* node, Box* box);
    // 碰到伞
    virtual void dripDelegateUmbrella(BaseRole* node);
    // 碰到水炮
    virtual void dripDelegateWaterBall(BaseRole* node,Box* box);
    virtual void dripDelegatevirusesBox(BaseRole* node,int track);
    virtual void dripDelegatePowerBox(BaseRole* node,Box* box);
    
    
    //激光碰见箱子回调
    virtual void baseBulletDelegateContact(BaseBullet* node, int flag, Box* box);
    virtual void baseBulletDelegateContactBall(BaseBullet* node, int flag);
    virtual void CutscenesDelegateFinish();
    
    //弹窗关闭按钮回调
    virtual void popupCloseCallBack(Ref *pSender);
    
    //boss回调
    
    virtual void onMonsterAttack(int type,int power,int speed);  //攻击.type子弹类型,power威力(子弹数量)
    virtual void onBattleEnd(int result);   //战斗结束，1.boss胜利，2.boss失败
    virtual void onMonsterCastSpell(int type,int speed);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event);

    virtual void onNormalRankGot(int rank);
    virtual void onUnlimitedRankGot(int rank);
    
    //胜利弹窗回调
    virtual void popupWinRewardDelegateCloseCallBack();
    virtual void popupWinRewardDelegateShareCallBack();
    virtual void popupWinRewardDelegateLuckCallBack();
    
    virtual void LevelInfoTextLayerDelegateClose();
    
    // 伽马射线动作播完
    virtual void baseBulletDelegateSLaserActionFinish();
    // 喷气背包动作完成回调
    virtual void dripDelegateBagEffectFinish();
public :
    
//    int energy;
    void moveBullet();
    
    Monster *monster;
    
    void moveBox();                         //移动下落的箱子
    void detectionOfFullLine();
    void showTips();                        //显示下落箱子提示标记
    void dropdownBox(float delta);          //放下箱子
    void checkEmptyTrack();                 //检查空的轨道
    void readBossBattle();
    void bossDead();
    void killBox();                         //去掉超出屏幕显示范围的箱子
//    void showBulletTips();                        //显示下落箱子提示标记
    void showBosss();
    
    
private :
    WebService *ws;
    bool setEnergy(Vec2 pos,int energy);
    
    bool isGameOver;
    bool isDripDead;
    bool flag;
    
    int myEnergy = 0;
    int boxEnergy;
    int amountOfEnergy; //掉多少次能量块
    float topPos = 0;
    LevelData* data;
    
    LaserBullet *lb;
    SLaserBulletArray *laser;
    SLaserBulletArray *laserBoss;
    
    float hammerTimer = 0;
    int hammerDestroyBoxNumber = 0;
    
//    list<ShortLaserBullet*> laserlist;
    LabelAtlas *timer;
    void showTxtTip(const char *str);
    void showGoldNumber(Vec2 pos,const char *str);
    void destroyBox();
    void skillBtnClick(int count);
    void showBomb(float x, float y);
    PlaySceneState *playSceneState;
    float getLevelSpeed();
    float boxSpeed = 1;
    BoxType normaltype = BoxType::normalbox;
    Sprite *tekken;
    
    LabelAtlas *score;
    Label *txtGold;
    
    int level = 0;                      //当前为第几关
    int levelType = 0;                  //关卡类型, 最大为5 最小为0, 0和1均为默认关卡
    bool isStartUmbrella = false;
    float timerUmbrella = 0; //雨伞计时器    2秒

    bool isTimeOver = false;
    float timerTimeOver = 0; //时间暂停计时器 2秒
    
    Text *txtEndlessRank;
    Text *txtEndlessBestScore;
    
    Text *txtLoseRank; //闯关模式失败弹窗排行数
    Text *txtLoseBestScore;
    
//    Text *lPass;
    Text *txtWinRank;
    Text *txtWinfloor;
    Text *txtWinRanking;
    Text *lblMaxFloorNumber;
    Text *lblCurrentRankNumber;
    Text *txtEndlessWinRank;
    Text *txtEndlessWinBestScore;
//    float timerSpeed = 0;    //减速计时器    8秒
//

    Jishiqi *jishi;
    int ran;
    BoxType boxtype = BoxType::normalbox;
    
    
    /**
     弹窗
     **/
    PopupLayer *popupLose;
    PopupLayer *popupPause;
    PopupLayer *popupWin;
    PopupLayer *popupEndless;
    PopupLayer *popupLeaveGame; // 退出游戏弹窗
    PopupLayer *popupReturnOfTheKing;
    PopupLayer *popupEndlessWin;
    PopupLayer *rankPop;
    
    //自定义组件
    Tip* tips[8] = {};                  //提示条模块
    Tip* dripTip;
    DottedLine *line;                   //虚线模块
    Health *health;                     //血条模块
    
    
    bool isPlayAttackAnimotion;
    bool isAttack = false;
    
    int track[5] = {};                  //随机轨道容器,用来放需要下落箱子应该在那些轨道,0为不放, 1 为放箱子
    int finalFloor = 30;                //过关楼层
    int floor = 0;                      //当前层
    
    bool isBullet = false;
    bool isShowBoss = false;
    bool isMenu;                    //是否打开菜单
    bool isShowTips = true;
    bool isMove = true;             //是否可以移动箱子
    bool isDrop = true;             //是否可以放下一个新箱子的标记
    bool isMoveBottonBox = false;   //是否移动底部的箱子
    bool isDetectionBox = false;    //检测箱子是否满行
    bool isForcedDown = false;      //轨道是否是空的,没有任何箱子
//    bool flag = true;
    bool isBossBattle = false;
    

    map<int, deque<string>> boxMatrix;
    
    list<Box*> boxlist;             //参与游戏运算箱子的集合
    list<Box*> dropBoxList;         //正在下落的箱子
    int emptyTrack[9];              //8个轨道中空的轨道
    
    float deadline;                 //参与游戏检测的箱子底线,低过这一条线的,就不参与游戏
    float firstline;                //第一行箱子的高度
    int verticalCount;              //垂直箱子的行数
    float time;                     //帧数累计时间

    
    Button *btnPause;
//    Button *btnWudi;            //无敌 按钮
//    Button *btnTimeOver;        //时间停止 按钮
//    Button *btnUmbrella;        //伞 按钮
    
//    Label *txtCoin;                         //屏幕下方显示的金币数
    
    BeyMac* player;
    
private :
    
    PropCd *propcd;
    int* generateRandomNumber();
    static PlayScene* create(int level,const char *name, int targetFloor);
    void initData();
    void showWinReward(int type);
    void initPopup();
    void initBtn();
    void setBg();
    void restartGame();
    void removeActionChild(Node* node);
//    void removeTrackBox(int track);
    void giveGift();
    void overLine();

    int getItemPrice(int num);
    void itemEnable(float delta);
    void hammerEnd();
    void startGame();
    void prop1();
    void prop2();
    void prop3();
    void prop4();
    void prop5();
    void prop6();
    void prop7();
    void prop8();
    
//    void dropdownBullet(float delta);             //放下子弹
    void waterBall(Sprite * sprite);
    
    void moveAllBox(int targetFloor);
    void hideTips();                        //隐藏下落箱子的提示

    int itemDropTime(int level);
    
    void boxRemoveAction(Box *box);
    void boxBangAction(float x, float y);
    void moveAllBox();                      //移动所有box
    void moveAllBoxTo(float _y);
    void finash();                          //游戏结束
    void monitoringItem(float delta);       //监控道具
    void showBox(Box *box);
    CC_SYNTHESIZE(PlaySceneDelegate*, delegate, Delegate);              //对外代理
};

#endif /* defined(__PuzzleBobble2__PlaySence__) */
