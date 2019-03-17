//
//  PopupWindow.h
//  WaterWars
//
//  Created by je on 3/11/15.
//
//

#ifndef __beymac__PopupLayer__
#define __beymac__PopupLayer__


#include "cocos2d.h"

USING_NS_CC;


class PopupDelegate {
public:
    virtual void popupCloseCallBack(Ref *pSender) = 0;
};


//notice:遮挡层需要在其它层之上，即z轴设置为较大的数值
class PopupLayer:public Layer{
public:
    //创建一个弹出层。参数：backgroundImage背景图。
    static PopupLayer *create(const char *backgroundImage);
    
    //创建一个弹出层。参数：backgroundImage后景图，width、height，要创建的弹出层宽和高。
    static PopupLayer *create(const char *backgroundImage,float width,float height);
    
    //显示(默认)
    void show();
    
    //隐藏
    void hide();
    
    //设置标题(旧版)
    void setTitle(const char *title,int fontsize=40);
    
    //设置标题
    void setTitle(const char *title,Color4B color,float x,float y,int fontsize=40);
    
    //设置图片标题（内容是图片）
    void setTitleImage(const char *filename);
    
    //设置文本内容
    void setContentText(const char *text,int fontsize=20);
    
    //设置关闭按钮
    void setCloseButton(const char *buttonImage);
    
    //设置关闭按钮,并设置位置
    void setCloseButton(const char *buttonImage,float x,float y);
    
    //委托
    CC_SYNTHESIZE(PopupDelegate*, delegate, Delegate);
    
private :
    
    Node *shadeLayer=nullptr;
    
    Node *bg;
    
private:
    
    //遮挡层
    Node *createShadeLayer();
    
};


#endif



