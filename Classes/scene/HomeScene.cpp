//
//  Home.cpp
//  WaterWars
//
//  Created by je on 3/10/15.
//
//

#include "HomeScene.h"
#include <SimpleAudioEngine.h>
#include "Background.h"
#include "PlayScene.h"
#include "CheckpointScene.h"
#include "ShopScene.h"
#include "ButtonFactory.h"
#include "AboutScene.h"
#include "UpgradeScene.h"
#include "RankingPop.h"
#include "TutorialScene.h"
#include "SkillSelectScene.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "AndroidHelper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSHelper.h"
#endif


USING_NS_CC;
using namespace cocos2d::ui;


void HomeScene::payResult(bool result)
{
    if (result) {
        log("支付成功,礼包");
        CommonData::getInstance()->addCrystal(20);
        CommonData::getInstance()->addEnergy(100);
        if(this->isRunning()){
            this->refreshData();
            giftPop->hide();  //关闭礼包弹窗
        }
    }else{
        log("支付失败");
    }
    //判断释放条件。
    if(this->isRunning()){
        if(this->getReferenceCount()>1){
            this->release();
        }
    }else{
        if(this->getReferenceCount()>0){
            this->release();
        }
    }
}


// on "init" you need to initialize your instance
bool HomeScene::init()
{
    //创建ws，并传入回调
    rankws=new Rankws(this);
    
    //背景
    auto bg=Background::createBackground();
    
    //标题
    txtTitle=Sprite::create(LSTRINGIMAGE("img_title"));
    txtTitle->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT-170);
    
    
    //能量
    auto sprGold=Sprite::create("img_number_bg_gold.png");
    sprGold->setPosition(110, SCREEN_HEIGHT-50);
    //能量值
    txtGold=Text::create();
    txtGold->setFontSize(32);
    txtGold->setString(StringUtils::format("%d",CommonData::getInstance()->getEnergy()));
    txtGold->cocos2d::Node::setPosition(115, 45);
    sprGold->addChild(txtGold);
    
    //晶核
    auto sprCrystal=Sprite::create("img_number_bg_crystal.png");
    sprCrystal->setPosition(SCREEN_WIDTH-110, SCREEN_HEIGHT-50);
    //晶核数
    txtCrystal=Text::create();
    txtCrystal->setFontSize(32);
    txtCrystal->setString(StringUtils::format("%d",CommonData::getInstance()->getCrystal()));
    txtCrystal->cocos2d::Node::setPosition(115, 45);
    sprCrystal->addChild(txtCrystal);

    
    //连接杆
    auto linkStick1=Sprite::create("img_string.png");
    linkStick1->setPosition(100,500);
    auto linkStick2=Sprite::create("img_string.png");
    linkStick2->setPosition(SCREEN_WIDTH-100,500);
    
    
    //闯关模式按钮
    btnMission=Button::create(LSTRINGIMAGE("img_select1"));
    btnMission->setPosition(Point(SCREEN_WIDTH/2,715));
    //    btnMission->setTitleText("闯关模式");
    btnMission->setTitleFontSize(50);
    btnMission->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(CheckpointScene::create());
        }
    });
    
    //神级挑战按钮
    btnWuJin=Button::create(LSTRINGIMAGE("img_select2"));
    btnWuJin->setPosition(Point(SCREEN_WIDTH/2-95,435));
    //    btnWuJin->setTitleText("无尽模式");
    btnWuJin->setTitleFontSize(50);
    btnWuJin->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            
            if(this->isSceneRunning==false){
                log("等待动画完毕");
                return;
            }
            
            
            //判断是否已玩过第三关。
            auto hasPassCheckpointThree=CommonData::getInstance()->get(3);
            if(hasPassCheckpointThree!=CHECKPOINT_PLAYED){
                this->popCantEnterShenjitiaozhan->show();
                return;
            }
            
            //判断是否有昵称
            auto hasName=CommonData::getInstance()->getNickname();
            log("名字:%s",hasName.c_str());
            if(!hasName.empty()){
                log("已有名字:%s",hasName.c_str());
                //匹配
                rankws->matchWithOther();
            }else{
                //.....检查名字
                log("获取名称");
                rankws->getUsername();
            }
            
        }
    });
    
    //排行榜弹窗
    rankPop=RankingPop::create();
    rankPop->setPosition(SCREEN_CENTER);
    this->addChild(rankPop,100);
    
    
    //排行榜按钮
    btnRank=Button::create("img_select4.png");
    btnRank->cocos2d::Node::setPosition(545, 435);
    btnRank->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            //是否播放过帮助
            rankPop->show();
        }
    });
    
    //基地升级按钮
    btnCamp=Button::create("img_select3.png");
    btnCamp->cocos2d::Node::setPosition(SCREEN_WIDTH/2, 215);
    btnCamp->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(UpgradeScene::createScene());
        }
    });
    
    
    //商店按钮
    auto btnShop=Button::create(LSTRINGIMAGE("img_btn_shop_mainpage"));
    btnShop->setPosition(Vec2(SCREEN_WIDTH-120,60));
    //    btnShop->setTitleText("商店");
    btnShop->setTitleFontSize(50);
    btnShop->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->pushScene(ShopScene::create());            
        }
    });
    
    //设置
    auto btnSetting=ButtonFactory::createButtonCircle("img_btn_set.png");
    btnSetting->cocos2d::Node::setPosition(70, 60);
    btnSetting->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            if(shadowOfSetting->isVisible()){
                shadowOfSetting->setVisible(false);
                _eventDispatcher->removeEventListenersForTarget(shadowOfSetting);
            }else{
                shadowOfSetting->setVisible(true);
                
                auto listener2=EventListenerTouchOneByOne::create();
                listener2->setSwallowTouches(true);
                listener2->onTouchBegan=[](Touch *touch,Event *event){
                    return true;
                };
                listener2->onTouchMoved=[](Touch *touch,Event *event){
                };
                listener2->onTouchEnded=[=](Touch *touch,Event *event){
                    shadowOfSetting->setVisible(false);
                    _eventDispatcher->removeEventListenersForTarget(shadowOfSetting);
                };
                
                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, shadowOfSetting);
                
            }
        }
    });
    
    
    //设置遮罩
    shadowOfSetting=Sprite::create("img_bg_gray.png");
    shadowOfSetting->cocos2d::Node::setPosition(btnSetting->getContentSize().width/2, 200);
    shadowOfSetting->setVisible(false);
    
    
    //关于
    auto btnAbout=ButtonFactory::createButtonCircleGreen("img_btn_about.png");
    btnAbout->cocos2d::Node::setPosition(shadowOfSetting->getContentSize().width/2, 355);
    btnAbout->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            log("关于");
            Director::getInstance()->replaceScene(AboutScene::create());
        }
    });
    
    
    //帮助按钮
    auto btnHelp=ButtonFactory::createButtonCircleGreen("img_btn_prompt.png");
    btnHelp->setPosition(Point(shadowOfSetting->getContentSize().width/2,255));
    //    btnHelp->setTitleText("帮助");
    btnHelp->setTitleFontSize(50);
    btnHelp->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            Director::getInstance()->replaceScene(TutorialScene::createScene());
        }
    });
    
    //静音
    btnMute=ButtonFactory::createButtonCircleGreen("img_btn_voice.png");
    //    btnMute->setTitleText("静音");
    btnMute->setTitleFontSize(50);
    btnMute->cocos2d::Node::setPosition(shadowOfSetting->getContentSize().width/2,150);
    btnMute->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            this->mute();
        }
    });
    
    //取消静音
    btnCancelMute=ButtonFactory::createButtonCircleGreen("img_btn_voice_close.png");
    btnCancelMute->setTitleFontSize(50);
    btnCancelMute->cocos2d::Node::setPosition(shadowOfSetting->getContentSize().width/2, 150);
    btnCancelMute->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            this->cancelMute();
        }
    });
    if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        btnCancelMute->setVisible(false);
    }else{
        btnMute->setVisible(false);
    }

    //将设置面板的元素加入。
    btnSetting->addChild(shadowOfSetting,-1);
    shadowOfSetting->addChild(btnAbout);
    shadowOfSetting->addChild(btnHelp);
    shadowOfSetting->addChild(btnMute);
    shadowOfSetting->addChild(btnCancelMute);
    
    
    //限量包弹窗
    giftPop=PopupLayer::create("img_window_bg.png");
    giftPop->setCloseButton("img_window_btn_close.png");
    giftPop->setPosition(SCREEN_CENTER);
    giftPop->setTitleImage("img_window_title1.png");
    //礼品列表图片
    auto giftDetail=Sprite::create("img_window_paper5.png");
    giftPop->addChild(giftDetail);
    //购买按钮
    auto btnAccept=Button::create("img_window_green.png");
    btnAccept->setTitleFontSize(40);
    btnAccept->setTitleColor(Color3B::BLACK);
    btnAccept->setTitleText("购买");
    btnAccept->cocos2d::Node::setPosition(0, -230);
    btnAccept->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            this->retain();
            Payment::pay(GIFT, this);
        }
    });
    giftPop->addChild(btnAccept);
    this->addChild(giftPop,999);
    //限量包按钮
    auto btnGift=ButtonFactory::createButtonCircle("img_btn_gift.png");
    btnGift->cocos2d::Node::setPosition(170,60);
    btnGift->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            giftPop->show();
        }
    });
    
    
    
    
    
    
    //神级挑战未过第三关提示弹窗
    {
        popCantEnterShenjitiaozhan=PopupLayer::create("img_window_bg.png");
        popCantEnterShenjitiaozhan->setCloseButton("img_window_btn_close.png");
        popCantEnterShenjitiaozhan->setPosition(SCREEN_CENTER);
        popCantEnterShenjitiaozhan->setTitleImage("img_window_title2.png");
        auto popForeground=Sprite::create("img_window_paper.png");
        popCantEnterShenjitiaozhan->addChild(popForeground);
        //文字
        auto txtPopCES=Text::create();
        txtPopCES->setString("您还没有过闯关模式第三关\n请过关后再进入神级挑战\n加油哦！么么哒");
        txtPopCES->setTextHorizontalAlignment(TextHAlignment::CENTER);
        txtPopCES->cocos2d::Node::setPosition(popForeground->getContentSize()/2);
        txtPopCES->setFontSize(32);
        txtPopCES->setColor(Color3B(203,73,24));
        popForeground->addChild(txtPopCES);
        //确定按钮
        auto btnConfirm=Button::create("img_window_green.png");
        btnConfirm->setTitleFontSize(40);
        btnConfirm->setTitleColor(Color3B::BLACK);
        btnConfirm->setTitleText("确定");
        btnConfirm->cocos2d::Node::setPosition(0, -230);
        btnConfirm->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                this->popCantEnterShenjitiaozhan->hide();
            }
        });
        popCantEnterShenjitiaozhan->addChild(btnConfirm);
    }
    
    //神级挑战昵称
    {
        namePop=PopupLayer::create("img_window_bg.png");
//        namePop->setCloseButton("img_window_btn_close.png");
        namePop->setPosition(SCREEN_CENTER);
        namePop->setTitleImage("img_window_title2.png");
        auto popNameForeground=Sprite::create("img_window_paper.png");
        namePop->addChild(popNameForeground);
        
        //文字提示
        auto noticeForNamePanel=Text::create();
        noticeForNamePanel->setString("大侠，先来个称谓吧！");
        noticeForNamePanel->setFontSize(35);
        noticeForNamePanel->setColor(Color3B(203,73,24));
        noticeForNamePanel->cocos2d::Node::setPosition(0, 50);
        namePop->addChild(noticeForNamePanel);
        
        //输入框
        auto boxSpr=Sprite::create("img_window_inputbox.png");
        boxSpr->cocos2d::Node::setPosition(0, -30);
        namePop->addChild(boxSpr);
//        nameField=TextField::create();
//        nameField->setColor(Color3B::WHITE);
//        nameField->setFontSize(40);
//        nameField->cocos2d::Node::setPosition(boxSpr->getContentSize()/2);
//        nameField->setAnchorPoint(Vec2(0.5, 0.5));
//        nameField->setPlaceHolder("超能战士");
//        nameField->setPlaceHolderColor(Color3B(134,174,255));
//        nameField->setFocused(true);
//        nameField->setMaxLength(18);
//        nameField->setFocusEnabled(true);
//        nameField->setAttachWithIME(true);
//        boxSpr->addChild(nameField);
        
        Scale9Sprite* sacel9SprY = Scale9Sprite::create("img_blank.png"); //创建9宫格自动缩放按钮
        m_editbox = EditBox::create(Size(372, 50), sacel9SprY); //创建输入框，需要参数：巨型，9宫格背景
        //设置编辑框内的文字
//        m_editbox->setPlaceholderFontColor(Color3B(134,174,255));
        m_editbox->setPlaceHolder("超能战士");
        //设置位置
        m_editbox->setPosition(boxSpr->getContentSize()/2);
//        m_editbox->setAnchorPoint(ccp(0.5, 0.5));
        m_editbox->setFontSize(30);
        //获取编辑框内的文字
        //CCLOG(“Text:%s”,box->getText());
        m_editbox->setDelegate(this);
        //设置文本的颜色
        m_editbox->setFontColor(Color3B(52,115,244));
        //最大输入文本长度
        m_editbox->setMaxLength(7);
        //设置输入键盘模式
        m_editbox->setInputMode(EditBox::InputMode::ANY);
        //默认使用键盘return类型为“Done”字样
        m_editbox->setReturnType(EditBox::KeyboardReturnType::DONE);
        boxSpr->addChild(m_editbox);
//        m_editbox->setTouchPriority(-130);
        
        
        
        
        noticeRepeat=Text::create();
        noticeRepeat->setString("称谓重复!");
        noticeRepeat->setFontSize(25);
        noticeRepeat->setColor(Color3B::RED);
        noticeRepeat->cocos2d::Node::setPosition(0, -80);
        noticeRepeat->setVisible(false);
        namePop->addChild(noticeRepeat);
        
        //确定按钮
        auto btnConfirm=Button::create("img_window_green.png");
        btnConfirm->setTitleFontSize(40);
        btnConfirm->setTitleColor(Color3B::BLACK);
        btnConfirm->setTitleText("确定");
        btnConfirm->cocos2d::Node::setPosition(0, -230);
        btnConfirm->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                
                noticeRepeat->setVisible(false);
                
                auto name=std::string(m_editbox->getText());
                if(name.empty()){
                    name=m_editbox->getPlaceHolder();
                }
            
                
                log("确定注册:%s",name.c_str());
                rankws->registerUsername(name);
                namePop->hide();
            }
        });
        namePop->addChild(btnConfirm);
    }
    
    //匹配结果弹窗
    {
        matchPop=PopupLayer::create("img_window_pk_bg.png");
        matchPop->setCloseButton("img_window_btn_close.png",275,210);
        matchPop->setPosition(SCREEN_CENTER);
        
        //对手名字
        opponentName=Text::create();
        opponentName->setAnchorPoint(Vec2(0,0.5));
        opponentName->setString("超能力战士001");
        opponentName->setFontSize(32);
        opponentName->setColor(Color3B::WHITE);
        opponentName->cocos2d::Node::setPosition(-80,40);
        matchPop->addChild(opponentName);
        
        //对手层数
        opponentFloor=Text::create();
        opponentFloor->setAnchorPoint(Vec2(0,0.5));
        opponentFloor->setString("最高层数:24");
        opponentFloor->setFontSize(25);
        opponentFloor->setColor(Color3B(116,162,255));
        opponentFloor->cocos2d::Node::setPosition(-80,-10);
        matchPop->addChild(opponentFloor);
        
        //自己的名字
        myName=Text::create();
        myName->setAnchorPoint(Vec2(0,0.5));
        myName->setString("超能力战士002");
        myName->setFontSize(32);
        myName->setColor(Color3B::WHITE);
        myName->cocos2d::Node::setPosition(-80,-130);
        matchPop->addChild(myName);
        
        //自己的层数
        myFloor=Text::create();
        myFloor->setAnchorPoint(Vec2(0,0.5));
        myFloor->setString("最高层数:25");
        myFloor->setFontSize(25);
        myFloor->setColor(Color3B(116,162,255));
        myFloor->cocos2d::Node::setPosition(-80,-180);
        matchPop->addChild(myFloor);
        
        
        //刷新对手
        auto btnJump=Button::create("img_window_btn_red.png");
        btnJump->setTitleFontSize(40);
        btnJump->setTitleColor(Color3B::WHITE);
        btnJump->setTitleText("刷新对手");
        btnJump->cocos2d::Node::setPosition(-130, -330);
        btnJump->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                rankws->matchWithOther();
                this->refreshOpponent=true;
            }
        });
        matchPop->addChild(btnJump);
        //开始挑战
        auto btnConfirm=Button::create("img_window_green.png");
        btnConfirm->setTitleFontSize(40);
        btnConfirm->setTitleColor(Color3B::BLACK);
        btnConfirm->setTitleText("开始挑战");
        btnConfirm->cocos2d::Node::setPosition(130, -330);
        btnConfirm->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                auto sss=SkillSelectScene::createScene(0);
                sss->rank=this->rank;
                sss->floor=this->floor;
                
                log("对手名称:%s",this->username.c_str());
                
                sss->username=this->username;
                
                
                Director::getInstance()->replaceScene(sss);
                
            }
        });
        matchPop->addChild(btnConfirm);
        
        
    }
    
    
    //奔跑的小人
    runner1=RunnerAnimation::create(RoleType::LaserType);
    this->addChild(runner1,15);
    
    runner2=RunnerAnimation::create(RoleType::TomagoType);
    this->addChild(runner2,15);
    
    runner3=RunnerAnimation::create(RoleType::BeymacType);
    this->addChild(runner3,15);
    
    
    
    //顶部组
    headSpr=Sprite::create();
    headSpr->addChild(sprGold,1);
    headSpr->addChild(sprCrystal,1);
    
    //中间组
    bodySpr=Sprite::create();
    bodySpr->addChild(linkStick1);
    bodySpr->addChild(linkStick2);
    bodySpr->addChild(btnMission);
    bodySpr->addChild(btnWuJin);
    bodySpr->addChild(btnRank);
    bodySpr->addChild(btnCamp);
    
    //底部组
    footSpr=Sprite::create();
    footSpr->addChild(btnSetting,30);
    footSpr->addChild(btnGift,1);
    footSpr->addChild(btnShop);
    
    
    this->addChild(popCantEnterShenjitiaozhan,100);
    this->addChild(namePop,100);
    this->addChild(matchPop,100);
    this->addChild(bg,-10);
    this->addChild(txtTitle,5);
    this->addChild(headSpr);
    this->addChild(bodySpr);
    this->addChild(footSpr);
    
    txtTitle->setVisible(false);
    headSpr->setPosition(0, 200);
    bodySpr->setPosition(0, 1000);
    footSpr->setPosition(0,-200);
    txtTitle->setScale(4);
    
    
    log("total gold:%d",CommonData::getInstance()->getGold());
    
    
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(HomeScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void HomeScene::refreshData()
{
    txtGold->setString(StringUtils::format("%d",CommonData::getInstance()->getEnergy()));
    txtCrystal->setString(StringUtils::format("%d",CommonData::getInstance()->getCrystal()));
    
    log("crystal:%d",CommonData::getInstance()->getCrystal());
    log("energy:%d",CommonData::getInstance()->getEnergy());
    
}


void HomeScene::onEnter()
{
    log("onEnter");
    cocos2d::Node::onEnter();
    
    
    log("crystal:%d",CommonData::getInstance()->getCrystal());
    log("energy:%d",CommonData::getInstance()->getEnergy());
    
    RankingPop::refreshData();
    
    this->refreshData();
    
    auto rec=Manager::getInstance()->isNetworkConnected();
    log("rec:%d",rec);
    
    
    //中间组下落
    auto mt=MoveTo::create(0.5, Vec2(0,0));
    auto mtTanxing=EaseElasticOut::create(mt,1);
    
    //中间组分别晃动
    auto func3=CallFunc::create([&](){
        float perid=0.3;
        int ss=5;
        {
            auto st=RotateBy::create(perid, ss);
            auto stFan=st->reverse();
            auto seq=Sequence::create(st,stFan, NULL);
            btnMission->runAction(seq);
        }
        {
            auto st=RotateBy::create(perid, -ss);
            auto stFan=st->reverse();
            auto seq=Sequence::create(st,stFan, NULL);
            btnWuJin->runAction(seq);
        }
        {
            auto st=RotateBy::create(perid, -ss);
            auto stFan=st->reverse();
            auto seq=Sequence::create(st,stFan, NULL);
            btnRank->runAction(seq);
        }
        {
            auto st=RotateBy::create(perid, ss);
            auto stFan=st->reverse();
            auto seq=Sequence::create(st,stFan, NULL);
            btnCamp->runAction(seq);
        }
    });
    
    //标题缩放
    auto func1=CallFunc::create([&](){
        txtTitle->setVisible(true);
        
        txtTitle->setOpacity(0);
        
        auto scaleTo=ScaleTo::create(0.6, 1);
        auto stTanxing=EaseElasticOut::create(scaleTo,1.2);
        
        txtTitle->runAction(stTanxing);
        auto fi=FadeIn::create(0.5);
        txtTitle->runAction(fi);
    });
    
    //头尾滑出
    auto func2=CallFunc::create([&](){
        auto mt1=MoveTo::create(0.5, Vec2(0, 0));
        auto mt2=MoveTo::create(0.5, Vec2(0, 0));
        headSpr->runAction(mt1);
        footSpr->runAction(mt2);
    });
    
    
    //奔跑的小人
    runner1->setPosition(SCREEN_WIDTH/2+40, SCREEN_HEIGHT+260);
    runner2->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT+260);
    runner3->setPosition(SCREEN_WIDTH/2-40, SCREEN_HEIGHT+260);
    
    
    //falling小人
    auto func4=CallFunc::create([&](){
        this->runner1->fall();
    });
    //falling小人
    auto func5=CallFunc::create([&](){
        this->runner2->fall();
    });
    //falling小人
    auto func6=CallFunc::create([&](){
        this->runner3->fall();
    });
    //播放人物落地音效
    auto func7=CallFunc::create([&](){
        Manager::getInstance()->playSoundEffect("homeRoleFall.mp3");
        //挑战模式回调开启
        this->isSceneRunning=true;
    });
    
    auto seq=Sequence::create(DelayTime::create(0.1),func3,mtTanxing,func1,func2,DelayTime::create(0.3),func4,DelayTime::create(0.2),func5,DelayTime::create(0.2),func6,DelayTime::create(0.2),func7, NULL);
    
    
    
    bodySpr->runAction(seq);
}

void HomeScene::onExit()
{
    //挑战模式回调关闭
    this->isSceneRunning=false;
    
    //动画模块重置
    shadowOfSetting->setVisible(false);
    txtTitle->setVisible(false);
    headSpr->setPosition(0, 200);
    bodySpr->setPosition(0, 1000);
    footSpr->setPosition(0,-200);
    txtTitle->setScale(4);
    
    //重置小人
    runner1->reset();
    runner2->reset();
    runner3->reset();
    
    
    cocos2d::Node::onExit();
}

//语言切换
void HomeScene::switchLanguage()
{
    if(CommonData::getInstance()->getLanguage()==0){
        //替换为英文
        CommonData::getInstance()->setLanguage(1);
    }else{
        //替换为中文
        CommonData::getInstance()->setLanguage(0);
    }
    Director::getInstance()->replaceScene(HomeScene::create());
}

void HomeScene::mute()
{
    if(Manager::getInstance()->getIsSound()){
        Manager::getInstance()->pauseBackgroundMusic();
    }
    Manager::getInstance()->setIsSound(false);
    btnMute->setVisible(false);
    btnCancelMute->setVisible(true);
}


//..................rankws请求回调
//名称是否存在
void HomeScene::isUsernameExist(bool exist)
{
    if(exist){
        log("名字存在");
    }else{
        log("名字不存在");
    }
    
}
//获取名称
void HomeScene::onGetUsername(bool succeed,std::string username)
{
    this->registeringName=username;
    CommonData::getInstance()->setNickname(username);
    if(succeed){
        log("获取到名字:%s",username.c_str());
        rankws->matchWithOther();
    }else{
        log("获取名字失败，自动取名:%s",username.c_str());
        namePop->show();
//        nameField->setPlaceHolder(username);
        m_editbox->setPlaceHolder(username.c_str());
    }
    
}
//注册名称
void HomeScene::onRegistered(bool succeed)
{
    if(succeed){
        auto name=this->registeringName;
        log("注册成功的名字:%s",name.c_str());
        CommonData::getInstance()->setNickname(name);
        rankws->matchWithOther();
    }else{
        log("注册名字失败");
        noticeRepeat->setVisible(true);
    }
}

//匹配到对手
void HomeScene::onMatchedWithOther(const int floor,const int rank,const int score,std::string username,const int myFloor,std::string myUsername)
{
    log("对手信息：层数 %d,排名 %d,得分 %d ,名字 %s",floor,rank,score,username.c_str());
    
    this->floor=floor;
    this->rank=rank;
    this->score=score;
    this->username=username;
    
    this->RankwsDelegate::myFloor=myFloor;
    this->myUsername=myUsername;
    
    opponentName->setString(username);
    opponentFloor->setString(StringUtils::format("最高层数:%d",floor));
    
    myName->setString(myUsername);
    this->myFloor->setString(StringUtils::format("最高层数:%d",myFloor));
    
    if(refreshOpponent){
        refreshOpponent=false;
    }else{
        matchPop->show();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        IOSHelper::hidenAdBar();
//#endif
    }
    
}

//离线模式
void HomeScene::onOffline()
{
    log("离线模式");
    auto sss=SkillSelectScene::createScene(0);
    sss->rank=100;
    sss->floor=100;
    sss->username=std::string("至尊宝992");
    sss->isOffline=true;
    
    Director::getInstance()->replaceScene(sss);
}


void HomeScene::cancelMute()
{
    Manager::getInstance()->setIsSound(true);
    Manager::getInstance()->resumeBackgroundMusic();
    btnCancelMute->setVisible(false);
    btnMute->setVisible(true);
    
}

//开始时的函数
void HomeScene::editBoxEditingDidBegin( EditBox *editBox )
{
    
}
//结束时的函数
void HomeScene::editBoxEditingDidEnd( EditBox *editBox )
{
    
}

//输入完后点击回车时的处理
void HomeScene::editBoxReturn( EditBox *editBox )
{
    
}

//文字更改函数
void HomeScene::editBoxTextChanged( EditBox *editBox, const std::string &text )
{
    
}



void HomeScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event) {
    if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_BACK) {
        return;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            noticeAndroidToExit();
#endif
    
}




