//
//  RoleWeaponUpgradeScene.h
//  beymac
//
//  Created by je on 5/21/15.
//
//

#ifndef __beymac__RoleWeaponUpgradeScene__
#define __beymac__RoleWeaponUpgradeScene__

#include "cocos2d.h"
#include "cocosGui.h"


USING_NS_CC;
using namespace ui;

class RoleSkillUpgradeScene:public Layer{
public:
    static Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(RoleSkillUpgradeScene);
    
    
private:
    
    int selectSkill;
    
//    Button *btnRole1;
//    Button *btnRole2;
//    Button *btnRole3;
    
//    Text *txtRole1Level;
//    Text *txtRole2Level;
//    Text *txtRole3Level;
    
private:
    
    Sprite *test();
    
    //角色升级
    void upgrade(int role);
    
    void refreshRolesLevel();
    
};

#endif /* defined(__beymac__RoleWeaponUpgradeScene__) */
