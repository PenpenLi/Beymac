//
//  CampUpgradeScene.h
//  beymac
//
//  Created by je on 4/21/15.
//
//


#include "cocos2d.h"

#include "cocosGui.h"

#define ROLE1 1
#define ROLE2 2
#define ROLE3 3

USING_NS_CC;
using namespace ui;

class CampUpgradeScene:public Scene{
public:
    
    CREATE_FUNC(CampUpgradeScene);
    
    virtual bool init();
    
private:
    
    int selectRole;
    
    Button *btnRole1;
    Button *btnRole2;
    Button *btnRole3;
    
    Text *txtRole1Level;
    Text *txtRole2Level;
    Text *txtRole3Level;
    
private:
    
    Sprite *test();
    
    //角色升级
    void upgrade(int role);
    
    void refreshRolesLevel();
    
};