//
//  Manage.h
//  WaterWars
//
//  Created by lingzerg on 15/3/11.
//
//

#ifndef __WaterWars__Manage__
#define __WaterWars__Manage__

#include "cocos2d.h"

USING_NS_CC;

class Manager :public Node {
public :
    static Manager *manager;
    
public :
    
    static Manager *getInstance();
    CREATE_FUNC(Manager);
    virtual bool init();
    
    std::string getImei();
    
    
    bool isNetworkConnected();
    
    bool isQQInstalled();
    void shareQQ();
    
    void playBackgroundMusic(const char* file);
    void resumeBackgroundMusic();
    void pauseBackgroundMusic();
    void playSoundEffect(const char* file);
private :
    CC_SYNTHESIZE(bool, isSound, IsSound);              //对外代理
};

#endif /* defined(__WaterWars__Manage__) */
