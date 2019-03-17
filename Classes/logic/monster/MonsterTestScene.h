//
//  MonsterTestScene.h
//  beymac
//
//  Created by je on 4/24/15.
//
//

#ifndef __beymac__MonsterTestScene__
#define __beymac__MonsterTestScene__


#include <cocos2d.h>
#include <CocosGUI.h>

USING_NS_CC;
using namespace ui;

class MonsterTestScene:public Scene{
public:
    
    CREATE_FUNC(MonsterTestScene);
        
    virtual bool init();
    
    void update(float dt) override;
  
private:
    
    Button *btnShadowLayer;
};


#endif