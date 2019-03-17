//
//  PlaySceneState.cpp
//  BeyMac
//
//  Created by lingzerg on 15/5/6.
//
//

#include "PlaySceneState.h"
#include "PlayScene.h"

PlaySceneState::PlaySceneState()
{
    
}

PlaySceneState::~PlaySceneState()
{
    
}

PlaySceneState* PlaySceneState::createNode(PlayScene *ps,int tipDropTimeLevel)
{
    PlaySceneState *state = new PlaySceneState();
    state->init(ps,tipDropTimeLevel);
    return state;
}

bool PlaySceneState::init(PlayScene *ps,int tipDropTimeLevel)
{
    if ( !Node::init() )
    {
        return false;
    }
    
    this->tipDropTimeLevel = tipDropTimeLevel;
    this->playScene = ps;
    initData();
    return true;
}

#pragma mark - initData
void PlaySceneState::initData()
{
    log("PlaySceneState initdata");
}



void PlaySceneState::execute(float delta) {
    
    
    
    
    if (enCurState == gamePause ) {
        
    }
    
    if (enCurState == drop || enCurState == dropReady || enCurState == dropOver) {
        if (enCurState == drop) {
            playScene->moveBox(); //全部箱子落地后切换到dropReady
        }
        
        if(enCurState == dropReady) {

            time += delta;
            if(time > tipDropTime(tipDropTimeLevel)-0.8) {
                time = 0.0;
                playScene->dropdownBox(delta);//切换到dropOver
            }
        }
        
        if(enCurState == dropOver) {
            playScene->checkEmptyTrack();       //不改变状态
            playScene->showTips();              //切换到drop
        }

        
        playScene->killBox();
        playScene->readBossBattle();
    }
    
    
    if (enCurState == battleReady || enCurState == battleStart || enCurState == battleOver || enCurState == battleWait) {
//        if(playScene->monster->getHealth() <= 0) {
//            //playScene->bossDead();
//        }
        

        if (enCurState == battleReady) {
            playScene->showBosss();
        }
        
        if(enCurState == battleStart) {
            playScene->moveBullet();
        }
        
        if (enCurState == battleWait) {
            
        }
        
        if(enCurState == battleOver) {
            
        }
        playScene->monster->onUpdate(delta);
    }
}

int PlaySceneState::tipDropTime(int level) {
    switch (level) {
        case 1:
            return 2.3;
        case 2:
            return 2.2;
        case 3:
            return 2.1;
        case 4:
            return 2;
        case 5:
            return 1.9;
        case 6:
            return 1.8;
        case 7:
            return 1.65;
        case 8:
            return 1.55;
        case 9:
            return 1.45;
        case 10:
            return 1.3;
        case 11:
            return 1.15;
        case 12:
            return 1;
        default:
            break;
    }
    return 1.5;
}


void PlaySceneState::changeState(EnumState enState) {
    this->enCurState = enState;
}

