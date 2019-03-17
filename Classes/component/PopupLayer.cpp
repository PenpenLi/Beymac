//
//  PopupWindow.cpp
//  WaterWars
//
//  Created by je on 3/11/15.
//
//

#include "PopupLayer.h"
#include "Macro.h"
#include "Manager.h"
#include "IOSHelper.h"
#include "ButtonFactory.h"


using namespace cocos2d::ui;

//遮挡层
Node *PopupLayer::createShadeLayer()
{
    auto lc=LayerColor::create(Color4B::BLACK);
    lc->setOpacity(150);
    //无响应监听器
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[](Touch *touch,Event *event){
        return true;
    };
    listener->onTouchMoved=[](Touch *touch,Event *event){
    };
    listener->onTouchEnded=[&](Touch *touch,Event *event){
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener ,lc);
    lc->retain();//取消自动管理释放
    return lc;
}


////遮挡层
//Node *PopupLayer::createShadeLayer()
//{
//    auto btnShadowLayer=Button::create("img_black.png");
//    btnShadowLayer->loadTexturePressed("img_black.png");
//    btnShadowLayer->setPosition(SCREEN_CENTER);
//    btnShadowLayer->retain();//取消自动管理释放
//    return btnShadowLayer;
//}



//创建一个弹出层。参数：backgroundImage背景图。
PopupLayer *PopupLayer::create(const char *backgroundImage)
{
    auto pl=new PopupLayer();
    
    //背景
    auto bg=Sprite::create(backgroundImage);
    bg->setPosition(0,0);
    
    pl->bg=bg;
    pl->addChild(bg);
    pl->setVisible(false);
    
    return pl;
}

//创建一个弹出层。参数：backgroundImage背景图，width、height，要创建的弹出层宽和高。
PopupLayer *PopupLayer::create(const char *backgroundImage,float width,float height)
{
    auto pl=new PopupLayer();
    
    //背景
    auto bg=Scale9Sprite::create(backgroundImage);
    bg->setContentSize(Size(width,height));
    bg->setCapInsets(Rect(0, 140, 640, 1));
    bg->setPosition(0,0);
    
    pl->bg=bg;
    pl->addChild(bg);
    pl->setVisible(false);
    return pl;
}

//显示(默认)
void PopupLayer::show()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSHelper::showAdBar();
#endif
    if(!this->isVisible()){
        
        //遮挡层
        if(!shadeLayer){
            shadeLayer=createShadeLayer();
        }
        
        if(shadeLayer->getParent()){
            log("ShadeLayer already has parent.");
            return;
        }
        this->getParent()->addChild(shadeLayer,this->getLocalZOrder()-1);
        
        
        this->setVisible(true);
        
        //动画：旋转放大
        auto node=this;
        
        float scale = node->getScale();
        
        node->setScale(scale*0.01f);
        auto scaleTo = ScaleTo::create(0.2f,1.f*scale);
        
        node->setRotation(90);
        auto rotate = RotateTo::create(0.2f, 0);
        
        auto spawn    = Spawn::create(scaleTo,rotate,NULL);
        
        auto scaleTo2 = ScaleTo::create(0.1f,1.1f*scale);
        auto easeTo = EaseElasticOut::create(scaleTo2, 1);
        
        auto scaleBack = ScaleTo::create(0.1, scale);
        auto easeBack = EaseElasticOut::create(scaleBack, 1);
        
        auto action = Sequence::create(spawn,easeTo,easeBack,NULL);
        
        node->runAction(action);
        
    }
}

//隐藏
void PopupLayer::hide()
{
//    log("hide");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSHelper::hidenAdBar();
#endif
    
    auto actionMoveDone=CallFuncN::create([&](Ref *pSender){
        if(shadeLayer){
            shadeLayer->removeFromParent();
        }
        this->setVisible(false);
        this->setPosition(SCREEN_CENTER);
    });
    
    //动画：向上移出屏幕
    if(this->isVisible()){
        MoveTo* moveto2 = MoveTo::create(0.5, Vec2(SCREEN_CENTER.x, SCREEN_HEIGHT));
        EaseBackIn* easeIn = EaseBackIn::create(moveto2);
        this->runAction(CCSequence::create(easeIn,CCDelayTime::create(0.1),actionMoveDone,NULL));
    }
    
    
}

//设置标题
void PopupLayer::setTitle(const char *title,int fontsize)
{
    auto lblTitle=Label::create();
    lblTitle->setColor(Color3B::ORANGE);
    lblTitle->setString(title);
    lblTitle->setSystemFontSize(fontsize);
    lblTitle->setPosition(0,bg->getContentSize().height/2-45);
    this->addChild(lblTitle);//ssss-------------
}


//设置标题，及其颜色、位置
void PopupLayer::setTitle(const char *title,Color4B color,float x,float y,int fontsize)
{
    auto lblTitle=Label::create();
    lblTitle->setTextColor(color);
    lblTitle->setString(title);
    lblTitle->setSystemFontSize(fontsize);
    lblTitle->setPosition(x,y);
    this->addChild(lblTitle);//ssss-------------
}

//设置标题（内容是图片）
void PopupLayer::setTitleImage(const char *filename)
{
    auto title=Sprite::create("img_window_title_bg.png");
    auto titleName=Sprite::create(filename);
    titleName->setPosition(title->getContentSize().width/2 ,title->getContentSize().height/2);
    title->addChild(titleName);
    
    title->setPosition(0, bg->getContentSize().height/2+15);
    this->addChild(title);
}


//设置文本内容
void PopupLayer::setContentText(const char *str,int fontsize)
{
    auto text = Text::create();
    text->setString(str);
    text->setFontSize(40);//大于等于40就报错，但能运行
    text->enableOutline(Color4B(111, 222, 55, 66), 150);
    text->ignoreContentAdaptWithSize(false);
    text->setTextHorizontalAlignment(TextHAlignment::CENTER);
    text->setContentSize(Size(bg->getContentSize().width-50,bg->getContentSize().height));
    this->addChild(text);//ssss-------------
}

//设置关闭按钮
void PopupLayer::setCloseButton(const char *buttonImage)
{
    auto btnClose=Button::create(buttonImage);
    btnClose->cocos2d::Node::setPosition(bg->getPositionX()+bg->getContentSize().width/2-50, bg->getPositionY()+bg->getContentSize().height/2-10);
    btnClose->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            this->hide();
            if (delegate) {
                delegate->popupCloseCallBack(this);
            }
        }
    });
    this->addChild(btnClose);//ssss-------------
}

//设置关闭按钮,并设置位置
void PopupLayer::setCloseButton(const char *buttonImage,float x,float y)
{
    auto btnClose=Button::create(buttonImage);
    btnClose->cocos2d::Node::setPosition(x,y);
    btnClose->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            this->hide();
            if (delegate) {
                delegate->popupCloseCallBack(this);
            }
        }
    });
    this->addChild(btnClose);//ssss-------------
}

