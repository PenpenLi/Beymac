//
//  Cutscenes.cpp
//  WaterWars
//
//  
//  Created by wang on 15/3/24.
//
//

#include "Cutscenes.h"
#include "Macro.h"
#include "CommonHeader.h"
#include "HomeScene.h"

Cutscenes::Cutscenes(int t)
:delegate()
{
    type = t;
    init();
}

Cutscenes::~Cutscenes()
{

}

bool Cutscenes::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255),MYSIZE.width,MYSIZE.height);
    layer->setPosition(SCREEN_LEFT_DOWN);
    layer->setCascadeColorEnabled(false);
    layer->setCascadeOpacityEnabled(false);
    addChild(layer);
    
    if (type == 0) {
        playComic1();
    }
    else
    {
//        playComic2();
    }
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->setSwallowTouches(true);//设置是否想下传递触摸
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    return true;
}

void Cutscenes::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void Cutscenes::onExit()
{
    Node::onExit();
}

// type:0 开场动画  1 遇见boss动画
Cutscenes* Cutscenes::createCutscenes(int type)
{
    Cutscenes *node=new Cutscenes(type);
    if (node) {
        node->autorelease();
    }
    else
    {
        delete node;
        node = NULL;
    }
    
    return node;
}

void Cutscenes::playComic2()
{
    
    Vec2 four1[4];
    four1[0] = Vec2(-320, 568);
    four1[1] = Vec2(27, 548);
    four1[2] = Vec2(-31, 10);
    four1[3] = Vec2(-320, 0);
    
    ClippingNode* clipper1 =  createClippingNode(four1);
    this->addChild(clipper1);
    clipper1->setTag(1001);
//    clipper1->setPosition(-20,SCREEN_CENTER.y);
    clipper1->setPosition(-150,SCREEN_CENTER.y);
    
    Vec2 four2[4];
    four2[0] = Vec2(27, 548);
    four2[1] = Vec2(320, 568);
    four2[2] = Vec2(320, 0);
    four2[3] = Vec2(-31, 10);
    
    ClippingNode* clipper2 =  createClippingNode(four2);
    this->addChild(clipper2);
    clipper2->setTag(1002);
//    clipper2->setPosition(SCREEN_RIGHT_UP.x+30,SCREEN_CENTER.y);
    clipper2->setPosition(SCREEN_RIGHT_UP.x+150,SCREEN_CENTER.y);
    
    Vec2 four3[4];
    four3[0] = Vec2(-320, 0);
    four3[1] = Vec2(-4, 0);
    four3[2] = Vec2(56, -568);
    four3[3] = Vec2(-320, -568);
    
    ClippingNode* clipper3 =  createClippingNode(four3);
    this->addChild(clipper3);
    clipper3->setTag(1003);
//    clipper3->setPosition(-50,SCREEN_CENTER.y);
    clipper3->setPosition(-150,SCREEN_CENTER.y);
    
    Vec2 four4[4];
    four4[0] = Vec2(-4, 0);
    four4[1] = Vec2(320, 0);
    four4[2] = Vec2(320, -568);
    four4[3] = Vec2(56, -568);
    
    ClippingNode* clipper4 =  createClippingNode(four4);
    this->addChild(clipper4);
    clipper4->setTag(1004);
//    clipper4->setPosition(SCREEN_RIGHT_UP.x+20,SCREEN_CENTER.y);
    clipper4->setPosition(SCREEN_RIGHT_UP.x+150,SCREEN_CENTER.y);
    
    MoveBy* move1 = MoveBy::create(0.8, Vec2(470,0));
    MoveBy* move2 = MoveBy::create(0.8, Vec2(-470,0));
    MoveBy* move3 = MoveBy::create(0.8, Vec2(470,0));
    MoveBy* move4 = MoveBy::create(0.8, Vec2(-470,0));

    auto move_ease_out1 = EaseElasticOut::create(move1->clone(), 1.5 );
    auto move_ease_out2 = EaseElasticOut::create(move2->clone(), 1.5 );
    auto move_ease_out3 = EaseElasticOut::create(move3->clone(), 1.5 );
    auto move_ease_out4 = EaseElasticOut::create(move4->clone(), 1.5 );
    
    auto t2 = TargetedAction::create(clipper2, move_ease_out2);
    auto t3 = TargetedAction::create(clipper3, move_ease_out3);
    auto t4 = TargetedAction::create(clipper4, move_ease_out4);
    
    CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(Cutscenes::showButton, this));

    auto seq = Sequence::create(move_ease_out1, t2, t3, t4, callback1, nullptr);
    
    clipper1->runAction(seq);
}

void Cutscenes::playComic1()
{
    Vec2 four1[4];
    four1[0] = Vec2(-320, 568);
    four1[1] = Vec2(52, 568);
    four1[2] = Vec2(101, 204);
    four1[3] = Vec2(-320, 143);
    
    ClippingNode* clipper1 =  createClippingNode(four1);
    this->addChild(clipper1);
    clipper1->setTag(1001);
    //    clipper1->setPosition(-20,SCREEN_CENTER.y);
    clipper1->setPosition(-150,SCREEN_CENTER.y);
    
    Vec2 four2[4];
    four2[0] = Vec2(52, 568);
    four2[1] = Vec2(320, 568);
    four2[2] = Vec2(320, 234);
    four2[3] = Vec2(101, 204);
    
    ClippingNode* clipper2 =  createClippingNode(four2);
    this->addChild(clipper2);
    clipper2->setTag(1002);
    //    clipper2->setPosition(SCREEN_RIGHT_UP.x+30,SCREEN_CENTER.y);
    clipper2->setPosition(SCREEN_RIGHT_UP.x+150,SCREEN_CENTER.y);
    
    Vec2 four3[4];
    four3[0] = Vec2(-320, 143);
    four3[1] = Vec2(320, 234);
    four3[2] = Vec2(320, -140);
    four3[3] = Vec2(-320, -94);
    
    ClippingNode* clipper3 =  createClippingNode(four3);
    this->addChild(clipper3);
    clipper3->setTag(1003);
    //    clipper3->setPosition(-50,SCREEN_CENTER.y);
    clipper3->setPosition(SCREEN_RIGHT_UP.x+350,SCREEN_CENTER.y);
    
    Vec2 four4[4];
    four4[0] = Vec2(-320, -94);
    four4[1] = Vec2(320, -140);
    four4[2] = Vec2(320, -568);
    four4[3] = Vec2(-320, -568);
    
    ClippingNode* clipper4 =  createClippingNode(four4);
    this->addChild(clipper4);
    clipper4->setTag(1004);
    //    clipper4->setPosition(SCREEN_RIGHT_UP.x+20,SCREEN_CENTER.y);
    clipper4->setPosition(-350,SCREEN_CENTER.y);
    
    MoveBy* move1 = MoveBy::create(0.8, Vec2(470,0));
    MoveBy* move2 = MoveBy::create(0.8, Vec2(-470,0));
    MoveBy* move3 = MoveBy::create(0.8, Vec2(-670,0));
    MoveBy* move4 = MoveBy::create(0.8, Vec2(670,0));
    
    auto move_ease_out1 = EaseElasticOut::create(move1->clone(), 1.5 );
    auto move_ease_out2 = EaseElasticOut::create(move2->clone(), 1.5 );
    auto move_ease_out3 = EaseElasticOut::create(move3->clone(), 1.5 );
    auto move_ease_out4 = EaseElasticOut::create(move4->clone(), 1.5 );
    
    auto t2 = TargetedAction::create(clipper2, move_ease_out2);
    auto t3 = TargetedAction::create(clipper3, move_ease_out3);
    auto t4 = TargetedAction::create(clipper4, move_ease_out4);
    
    auto t22 = TargetedAction::create(clipper2, move_ease_out2->reverse());
    auto t33 = TargetedAction::create(clipper3, move_ease_out3->reverse());
    auto t44 = TargetedAction::create(clipper4, move_ease_out4->reverse());
    
    CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(Cutscenes::removeLayer, this));
    
    Spawn* spawn = Spawn::create(move_ease_out1->reverse(), t22, t33, t44, NULL);
    
    auto seq = Sequence::create(move_ease_out1, t2, t3, t4, DelayTime::create(1.0), spawn, DelayTime::create(0.3),callfun, nullptr);
    
    clipper1->runAction(seq);
}

ClippingNode* Cutscenes::createClippingNode( Vec2 *verts )
{
    auto shape = DrawNode::create();
    Color4F green(0, 1, 0, 1);
    shape->drawPolygon(verts, 4, green, 0, green);
    shape->setPosition(0, 0);
    
    auto clipper = ClippingNode::create();
    clipper->setAnchorPoint(Vec2(0.5, 0.5));
    
    clipper->setStencil(shape);

    if (type == 0) {
        auto content = Sprite::create(MMImageNameLink("img_four1",false));
        content->setPosition(0, 0);
        clipper->addChild(content);
    }
    else
    {
//        auto content = Sprite::create(MMImageNameLink("img_four2",false));
//        content->setPosition(0, 0);
//        clipper->addChild(content);
    }
    
    return clipper;
}

void Cutscenes::showButton()
{
    Button* button = Button::create("img_four_go.png");
    button->setPosition(SCREEN_CENTER);
    button->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            auto node = (Node*) pSender;
            Manager::getInstance()->playSoundEffect("ready.mp3");
            MoveTo* moveto2 = MoveTo::create(0.8, Vec2(SCREEN_CENTER.x, SCREEN_LEFT_UP.y+1100));
            EaseBackIn* easeIn = EaseBackIn::create(moveto2);
            
            CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(Cutscenes::layerDispear, this));
            
            node->runAction(CCSequence::create(easeIn,CCDelayTime::create(0.1),callfun,NULL));
        }
    });

    addChild(button);
    
    button->setScale(5);
    
    ScaleTo* scaleBack = ScaleTo::create(1.2, 1.0);
    EaseElasticOut* easeBack = EaseElasticOut::create(scaleBack, 1);
    button->runAction(easeBack);
}

void Cutscenes::layerDispear()
{
    
    Node* node1 = getChildByTag(1001);
    Node* node2 = getChildByTag(1002);
    Node* node3 = getChildByTag(1003);
    Node* node4 = getChildByTag(1004);
    if (!node1 || !node2 || !node3 || !node4) {
        return;
    }
    
    MoveBy* move1 = MoveBy::create(0.8, Vec2(470,0));
    MoveBy* move2 = MoveBy::create(0.8, Vec2(-470,0));
    MoveBy* move3 = MoveBy::create(0.8, Vec2(670,0));
    MoveBy* move4 = MoveBy::create(0.8, Vec2(-670,0));
    
    auto move_ease_out1 = EaseElasticOut::create(move1->clone(), 1.5 );
    auto move_ease_out2 = EaseElasticOut::create(move2->clone(), 1.5 );
    auto move_ease_out3 = EaseElasticOut::create(move3->clone(), 1.5 );
    auto move_ease_out4 = EaseElasticOut::create(move4->clone(), 1.5 );
    
//    auto t22 = TargetedAction::create(node2, move_ease_out2->reverse());
//    auto t33 = TargetedAction::create(node3, move_ease_out3->reverse());
//    auto t44 = TargetedAction::create(node4, move_ease_out4->reverse());
    
    CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(Cutscenes::removeLayer, this));
    
//    auto seq = Sequence::create(move_ease_out1->reverse(), t22, t33, t44, callfun, nullptr);
    
    node1->runAction(move_ease_out1->reverse());
    node2->runAction(move_ease_out2->reverse());
    node3->runAction(move_ease_out3->reverse());
    node4->runAction(Sequence::create(move_ease_out4->reverse(), DelayTime::create(0.2), callfun, NULL));

}

void Cutscenes::removeLayer()
{
    log("remove self");
    
    if (delegate) {
        delegate->CutscenesDelegateFinish();
    }
    
    removeFromParent();
    
    
    if (type == 0) {
        Director::getInstance()->replaceScene(HomeScene::create());
    }
}