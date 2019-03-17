//
//  LeadBombTestScene.h
//  beymac
//
//  Created by je on 6/16/15.
//
//

#ifndef __beymac__LeadBombTestScene__
#define __beymac__LeadBombTestScene__


#include <cocos2d.h>
#include <cocostudio/CocoStudio.h>

USING_NS_CC;
using namespace cocostudio;

class LeadBombTestScene:public Scene{
public:
    CREATE_FUNC(LeadBombTestScene);
    
    virtual bool init();
        
private:
    
    Armature *amt;
    
    
};





#endif /* defined(__beymac__LeadBombTestScene__) */
