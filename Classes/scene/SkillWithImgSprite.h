//
//  SkillWithImgSprite.h
//  beymac
//
//  Created by je on 5/29/15.
//
//

#ifndef __beymac__SkillWithImgSprite__
#define __beymac__SkillWithImgSprite__

#include <cocos2d.h>
#include <CocosGUI.h>

USING_NS_CC;
using namespace ui;
using namespace std;

class SkillWithImgSprite:public Node{
public:
    
    static SkillWithImgSprite *create();
    
    virtual bool init();
    
    void show(string title,string img);
    
private:
    Text *title;
    
    Sprite *img;
    
};



#endif /* defined(__beymac__SkillWithImgSprite__) */
