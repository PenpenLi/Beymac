//
//  Checkpoint.h
//  beymac
//
//  Created by je on 5/27/15.
//
//

#ifndef __beymac__Checkpoint__
#define __beymac__Checkpoint__

#include <cocos2d.h>
#include <CocosGUI.h>


#define CHECKPOINT_LOCKED 0 //锁定
#define CHECKPOINT_PLAYED 1 //玩过的
#define CHECKPOINT_PLAYABLE 2   //可玩的

USING_NS_CC;
using namespace ui;

class Checkpoint;

//关卡回调
class CheckpointDelegate{
public:
    virtual void onClick(Checkpoint *cp)=0;
};


class Checkpoint:public Node{
public:
    
    static Checkpoint *create(const int number,CheckpointDelegate *callback=nullptr);
    
    virtual bool init();
    
    void unlock();
    
public:
    
    int number;
    
    int state;
    
    static int firstLockedCheckpoint;
    
private:
    
    Button *btn;
    
    CheckpointDelegate *callback;
    
};

#endif /* defined(__beymac__Checkpoint__) */
