//
//  UpgradeScene.cpp
//  beymac
//
//  Created by mumu on 15/5/27.
//
//

#include "UpgradeScene.h"
#include "HomeScene.h"
#include "ButtonFactory.h"

#define PLAY_BUTTON_SOUND_EFFECT Manager::getInstance()->playSoundEffect("btnPress.mp3")

UpgradeScene::UpgradeScene()
{

}

UpgradeScene::~UpgradeScene()
{

}

bool UpgradeScene::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initBG();
    initBtn();
    initLayer();
    initPopup();
    
//    CommonData::getInstance()->addCrystal(200);
    
    return true;
}

void UpgradeScene::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    refreshCrystal();
}

void UpgradeScene::onExit()
{
    Node::onExit();
}

void UpgradeScene::initBG()
{
    //背景
    auto bg=Sprite::create("img_lucky_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    addChild(bg,0);
    
    //头部
    auto head=Sprite::create("img_upgrade_title_bg.png");
    head->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-head->getContentSize().height/2);
    addChild(head,999);
    
    //返回
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_back.png");
    btnBack->setPosition(Point(70,SCREEN_HEIGHT-head->getContentSize().height/2));
    //    btnBack->setTitleText("返回");
    btnBack->setTitleFontSize(50);
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(HomeScene::create());
        }
    });
    addChild(btnBack,999);
    
    auto *power = Sprite::create("img_shop_icon_power.png");
    power->setPosition(SCREEN_WIDTH-140,SCREEN_HEIGHT-head->getContentSize().height/4-10);
    power->setLocalZOrder(101);
    addChild(power,999);
    
    auto *crystal = Sprite::create("img_shop_icon_crystal.png");
    crystal->setPosition(SCREEN_WIDTH-140,SCREEN_HEIGHT-(head->getContentSize().height*3)/4);
    crystal->setLocalZOrder(101);
    addChild(crystal,999);
    
    txtPower = Label::create();
    txtPower->setTextColor(Color4B::WHITE);
    txtPower->setAnchorPoint(Vec2(0,0.5));
    txtPower->setString(NUM_TO_STR(CommonData::getInstance()->getEnergy()));
    txtPower->setSystemFontSize(30);
    txtPower->setPosition(SCREEN_WIDTH-110,power->getPositionY());
    addChild(txtPower,999);
    
    txtCrystal = Label::create();
    txtCrystal->setTextColor(Color4B::WHITE);
    txtCrystal->setAnchorPoint(Vec2(0,0.5));
    txtCrystal->setString(NUM_TO_STR(CommonData::getInstance()->getCrystal()));
    txtCrystal->setSystemFontSize(30);
    txtCrystal->setPosition(SCREEN_WIDTH-110,crystal->getPositionY());
    addChild(txtCrystal,999);
}

void UpgradeScene::initBtn()
{
    btnRank=Button::create("img_upgrade_tap_unselected1.png","img_upgrade_tap_selected1.png");
    btnRank->setPosition(Point(btnRank->getContentSize().width/2,btnRank->getContentSize().height/2));
    btnRank->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            setAllBtnUnSelect();
            setAllLayerDispear();
            Button* b = (Button*)pSender;
            b->setHighlighted(true);
            
            layer1->refreshBtn();
            layer1->refreshHero();
            layer1->setVisible(true);
            
        }
    });
    addChild(btnRank,999);
    btnRank->setHighlighted(true);
    
    float width = btnRank->getContentSize().width;
    
    btnHero=Button::create("img_upgrade_tap_unselected2.png","img_upgrade_tap_selected2.png");
    btnHero->setPosition(Point(width/2+width,btnHero->getContentSize().height/2));
    btnHero->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            setAllBtnUnSelect();
            setAllLayerDispear();
            Button* b = (Button*)pSender;
            b->setHighlighted(true);
            
            layer1->refreshBtn();
            layer1->refreshHero();
            layer2->setVisible(true);
            
        }
    });
    addChild(btnHero,999);
    btnHero->setHighlighted(false);
    
//    btnBayMac=Button::create("img_upgrade_tap_unselected.png","img_upgrade_tap_selected.png");
//    btnBayMac->setPosition(Point(width/2+width,btnBayMac->getContentSize().height/2));
//    btnBayMac->setTitleText(LSTRING("Baymac"));
//    btnBayMac->setTitleFontSize(30);
//    btnBayMac->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
//        if(type==Widget::TouchEventType::ENDED){
//            PLAY_BUTTON_SOUND_EFFECT;
//            setAllBtnUnSelect();
//            setAllLayerDispear();
//            Button* b = (Button*)pSender;
//            b->setHighlighted(true);
//            b->setTitleColor(Color3B(255, 198, 0));
//            
//            layer2->setVisible(true);
//            layer1->refreshBtn();
//            layer1->refreshHero();
//            
//        }
//    });
//    addChild(btnBayMac,999);
    
//    btnLaser=Button::create("img_upgrade_tap_unselected.png","img_upgrade_tap_selected.png");
//    btnLaser->setPosition(Point(width/2+width*3,btnLaser->getContentSize().height/2));
//    btnLaser->setTitleText(LSTRING("Laser"));
//    btnLaser->setTitleFontSize(30);
//    btnLaser->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
//        if(type==Widget::TouchEventType::ENDED){
//            PLAY_BUTTON_SOUND_EFFECT;
//            
//            if (CommonData::getInstance()->getRoleLevel(2) < 1) {
//                // 角色没有解锁
//                
//                popupUnlockRoleNum = 2;
//                popupImage->setTexture("img_upgrade_brother.png");
//                
//                popupUnlockRole->show();
//            }
//            else
//            {
//                setAllBtnUnSelect();
//                setAllLayerDispear();
//                Button* b = (Button*)pSender;
//                b->setHighlighted(true);
//                b->setTitleColor(Color3B(255, 198, 0));
//                layer1->refreshBtn();
//                layer1->refreshHero();
//                layer3->setVisible(true);
//            }
//            
//            
//            
//        }
//    });
//    addChild(btnLaser,999);
//    
//    btnTomago=Button::create("img_upgrade_tap_unselected.png","img_upgrade_tap_selected.png");
//    btnTomago->setPosition(Point(width/2+width*2,btnRank->getContentSize().height/2));
//    btnTomago->setTitleText(LSTRING("Tomago"));
//    btnTomago->setTitleFontSize(30);
//    btnTomago->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
//        if(type==Widget::TouchEventType::ENDED){
//            PLAY_BUTTON_SOUND_EFFECT;
//            if (CommonData::getInstance()->getRoleLevel(3) < 1) {
//                // 角色没有解锁
//                popupUnlockRoleNum = 3;
//                popupImage->setTexture("img_upgrade_sister.png");
//                
//                popupUnlockRole->show();
//            }
//            else
//            {
//                setAllBtnUnSelect();
//                setAllLayerDispear();
//                Button* b = (Button*)pSender;
//                b->setHighlighted(true);
//                b->setTitleColor(Color3B(255, 198, 0));
//                layer1->refreshBtn();
//                layer1->refreshHero();
//                layer4->setVisible(true);
//            }
//        }
//    });
//    addChild(btnTomago,999);
    
    btnSkill=Button::create("img_upgrade_tap_unselected3.png","img_upgrade_tap_selected3.png");
    btnSkill->setPosition(Point(width/2+width*2,btnRank->getContentSize().height/2));
    btnSkill->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            setAllLayerDispear();
            setAllBtnUnSelect();
            Button* b = (Button*)pSender;
            b->setHighlighted(true);
            
            layer5->setVisible(true);
        }
    });
    addChild(btnSkill,999);
    
//    btnRank->setTitleColor(Color3B::WHITE);
//    btnBayMac->setTitleColor(Color3B::WHITE);
//    btnLaser->setTitleColor(Color3B::WHITE);
//    btnSkill->setTitleColor(Color3B::WHITE);
//    btnTomago->setTitleColor(Color3B::WHITE);
}

Scene* UpgradeScene::createScene()
{
    Scene* scene = Scene::create();
    UpgradeScene* layer = UpgradeScene::create();
    scene->addChild(layer,0,100);
    
    return scene;
}

void UpgradeScene::setAllBtnUnSelect()
{
    btnRank->setHighlighted(false);
//    btnRank->setTitleColor(Color3B::WHITE);
//    btnBayMac->setHighlighted(false);
//    btnBayMac->setTitleColor(Color3B::WHITE);
//    btnLaser->setHighlighted(false);
//    btnLaser->setTitleColor(Color3B::WHITE);
    btnSkill->setHighlighted(false);
//    btnSkill->setTitleColor(Color3B::WHITE);
//    btnTomago->setHighlighted(false);
//    btnTomago->setTitleColor(Color3B::WHITE);
    btnHero->setHighlighted(false);
}

void UpgradeScene::initLayer()
{
    layer1 = HeroRankLayer::create();
    layer1->setPosition(Vec2::ZERO);
    addChild(layer1);
    
//    layer2 = HeroUpgradeLayer::create(BeymacType);
//    layer2->setPosition(Vec2::ZERO);
//    addChild(layer2);
//    layer2->setVisible(false);
    
//    layer3 = HeroUpgradeLayer::create(LaserType);
//    layer3->setPosition(Vec2::ZERO);
//    addChild(layer3);
//    layer3->setVisible(false);
//    
//    layer4 = HeroUpgradeLayer::create(TomagoType);
//    layer4->setPosition(Vec2::ZERO);
//    addChild(layer4);
//    layer4->setVisible(false);
    
    layer2 = HeroUpgradeLayerNew::create();
    layer2->setPosition(Vec2::ZERO);
    addChild(layer2);
    layer2->setVisible(false);
    
    layer5 = SkillUpgradeLayer::create();
    layer5->setPosition(Vec2::ZERO);
    addChild(layer5);
    layer5->setVisible(false);
}

void UpgradeScene::setAllLayerDispear()
{
    layer1->setVisible(false);
    layer2->setVisible(false);
//    layer3->setVisible(false);
//    layer4->setVisible(false);
    layer5->setVisible(false);
}

void UpgradeScene::initPopup()
{
    popupUnlockRole = PopupLayer::create("img_window_bg.png");
    popupUnlockRole->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    
    Sprite* titlebg = Sprite::create("img_window_title_bg.png");
    titlebg->setPosition(Vec2(0, 190));
    popupUnlockRole->addChild(titlebg);
    
    Sprite* title = Sprite::create("img_window_title7.png");
    title->setPosition(Vec2(0, 190));
    popupUnlockRole->addChild(title);
    
    Sprite* content = Sprite::create("img_window_paper.png");
    content->setPosition(Vec2::ZERO);
    popupUnlockRole->addChild(content);
    
    Sprite* content2 = Sprite::create("img_window_paper6.png");
    content2->setPosition(Vec2::ZERO);
    popupUnlockRole->addChild(content2);
    
    Label* context = Label::createWithSystemFont(LSTRING("UnlockNewRole"), "arial", 30);
    context->setDimensions(260, 80);
    context->setPosition(Vec2(115,70));
    context->setColor(Color3B(203,  73,  24));
    context->setHorizontalAlignment(TextHAlignment::CENTER);
    context->setVerticalAlignment(TextVAlignment::CENTER);
    popupUnlockRole->addChild(context);
    
    auto btnOK=cocos2d::ui::Button::create("img_window_green.png");
    btnOK->setPosition(Point(0,-240));
    btnOK->setTitleText(LSTRING("UNLOCK"));
    btnOK->setTitleFontName("Arial");
    btnOK->setTitleFontSize(40);
    btnOK->setTitleColor(Color3B(12, 63, 10));
    btnOK->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
            unlockNewRoleSuccess();
            log("解锁新人物");
        }
    });
    popupUnlockRole->addChild(btnOK);
    addChild(popupUnlockRole, 9999);
    
    auto btnClose=Button::create("img_window_btn_close.png");
    btnClose->setPosition(Point(260,160));
    btnClose->addTouchEventListener([&](Ref *pSender,cocos2d::ui::Widget::TouchEventType type){
        if(type==cocos2d::ui::Widget::TouchEventType::ENDED){
            Manager::getInstance()->playSoundEffect("btnPress.mp3");
           
            popupUnlockRole->hide();
        }
    });
    popupUnlockRole->addChild(btnClose);
    
    popupUnlockRoleNum = 2;
    
    popupImage = Sprite::create("img_upgrade_brother.png");
    popupImage->setScale(0.4);
    popupImage->setPosition(-100, 0);
    popupUnlockRole->addChild(popupImage);
    
}

void UpgradeScene::popupCloseCallBack(Ref *pSender)
{
    
}

void UpgradeScene::unlockNewRoleSuccess()
{
    popupUnlockRole->hide();
    CommonData::getInstance()->setRoleLevel(popupUnlockRoleNum, 1);
//    layer3->refreshBtn();
//    layer3->refreshLevel();
//    layer4->refreshLevel();
//    layer4->refreshBtn();
}

void UpgradeScene::refreshCrystal()
{
    txtCrystal->setString(NUM_TO_STR(CommonData::getInstance()->getCrystal()));
}