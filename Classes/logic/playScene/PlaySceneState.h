//
//  PlaySceneState.h
//  BeyMac
//
//  Created by lingzerg on 15/5/6.
//
//

#ifndef __BeyMac__PlaySceneState__
#define __BeyMac__PlaySceneState__

#include "cocos2d.h"

class PlayScene;


USING_NS_CC;

enum EnumState{
    gamePause,
    dropReady,
    drop,
    dropOver,
    battleReady,
    battleStart,
    battleWait,
    battleOver
};

class PlaySceneState : public Node
{
public:
    /* 当前状态 */
    EnumState enCurState;
    
public :
    /* 切换状态 */
    void changeState(EnumState enState);
    void execute(float delta);
    
    PlaySceneState();
    ~PlaySceneState();
    static PlaySceneState* createNode(PlayScene *ps, int tipDropTimeLevel);
    bool init(PlayScene *ps,int tipDropTimeLevel);
    //CREATE_FUNC(PlaySceneState);

private :
    float time = 0;
    PlayScene *playScene;
    int tipDropTimeLevel;
private:
    void initData();
    int tipDropTime(int level);    
};

#endif /* defined(__BeyMac__PlaySceneState__) */
