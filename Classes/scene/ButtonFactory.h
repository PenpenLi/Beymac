//
//  ButtonFactory.h
//  beymac
//
//  Created by je on 4/27/15.
//
//

#include "cocos2d.h"
#include <CocosGUI.h>

USING_NS_CC;
using namespace ui;

class ButtonFactory{
public:
    //圆形按钮
    static Button *createButtonCircle(const char *image);
    
    //圆形绿色按钮
    static Button *createButtonCircleGreen(const char *image);
    
    //长方形——价钱（购买按钮)
    static Button *createButtonPrice(const char *image);
    
    
    
};