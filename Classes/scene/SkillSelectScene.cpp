//
//  SkillSelectScene.cpp
//  beymac
//
//  Created by je on 6/8/15.
//
//

#include "SkillSelectScene.h"
#include "CommonHeader.h"
#include "Checkpoint.h"
#include "PlayScene.h"
#include "Background.h"
#include "ButtonFactory.h"
#include "HomeScene.h"
#include "CheckpointScene.h"
#include "ReadDataFromMap.h"


#define TAG_SELECTED_SKILL_BUTTON_ADD_CHARACTOR 11
#define TAG_SELECTED_SKILL_BUTTON_IMAGE 12

class RoleSkill{
public:
    int number;
    std::string title;
    std::string filename;
};


class RoleSkillList{
    
public:
    static std::map<int ,RoleSkill *> getInstance(){
        std::map<int ,RoleSkill *> skillMap;
        
        {
            auto rs=new RoleSkill();
            rs->number=1;
            rs->title.append("金钟罩");
            rs->filename.append("img_prop_big_pic1.png");
            skillMap[1]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=2;
            rs->title.append("大白铁拳");
            rs->filename.append("img_prop_big_pic2.png");
            skillMap[2]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=3;
            rs->title.append("时间减缓");
            rs->filename.append("img_prop_big_pic3.png");
            skillMap[3]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=4;
            rs->title.append("喷气背包");
            rs->filename.append("img_prop_big_pic4.png");
            skillMap[4]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=6;
            rs->title.append("伽马射线");
            rs->filename.append("img_prop_big_pic6.png");
            skillMap[6]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=7;
            rs->title.append("饱和轰炸");
            rs->filename.append("img_prop_big_pic7.png");
            skillMap[7]=rs;
        }
        {
            auto rs=new RoleSkill();
            rs->number=8;
            rs->title.append("次元门");
            rs->filename.append("img_prop_big_pic8.png");
            skillMap[8]=rs;
        }
        
        return skillMap;
    }
};


void SkillSelectScene::payResult(bool result)
{
    if(result){
        log("支付成功,解锁关卡%d",this->number);
        CommonData::getInstance()->put(this->number, CHECKPOINT_PLAYABLE);
        state=CHECKPOINT_PLAYABLE;
        
        //释放场景资源
        if(this->isRunning()){
            log("运行中");
            this->unlockPop->hide();
        }else{
            log("不在运行");
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


SkillSelectScene::SkillSelectScene(int number)
{
    this->number=number;
}

SkillSelectScene *SkillSelectScene::createScene(int number)
{
    auto sss=new SkillSelectScene(number);
    if(sss&&sss->init()){
        sss->autorelease();
    }
    
    return sss;
}

bool SkillSelectScene::init()
{
    //背景
    auto bg=Sprite::create("img_lucky_bg.jpg");
    bg->setPosition(SCREEN_CENTER);
    
    this->state=CommonData::getInstance()->get(this->number);
    
    
    
    //返回
    auto btnBack=ButtonFactory::createButtonCircle("img_btn_back.png");
    btnBack->cocos2d::Node::setPosition(70, 60);
    btnBack->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            if(this->number==0){
                Director::getInstance()->replaceScene(HomeScene::create());
            }else{
                Director::getInstance()->replaceScene(CheckpointScene::create());
            }
            
        }
    });
    
    //解锁关卡弹窗
    unlockPop=PopupLayer::create("img_window_bg.png");
    unlockPop->setTitleImage("img_window_title3.png");
    unlockPop->setCloseButton("img_window_btn_close.png");
    unlockPop->setPosition(SCREEN_CENTER);
    auto lockSpr=Sprite::create("img_window_paper2.png");
    unlockPop->addChild(lockSpr);
    //文字提示
    auto noticeUnlock=Text::create();
    noticeUnlock->setString("6元解锁新关卡");
    noticeUnlock->setFontSize(35);
    noticeUnlock->setColor(Color3B(203, 73, 24));
    noticeUnlock->cocos2d::Node::setPosition(0, -90);
    unlockPop->addChild(noticeUnlock);
    //解锁按钮
    auto btnUnlock=Button::create("img_window_green.png");
    btnUnlock->setTitleText("解锁");
    btnUnlock->setTitleFontSize(40);
    btnUnlock->cocos2d::Node::setPosition(0, -230);
    btnUnlock->setTitleColor(Color3B::BLACK);
    btnUnlock->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            this->retain();
            Payment::pay(UNLOCKLEVEL, this);
        }
    });
    unlockPop->addChild(btnUnlock);
    
    
    //主要内容----------------------------------------
    
    //开始游戏
    btnStart=Button::create("img_window_green.png");
    btnStart->setTitleText("开始游戏");
    btnStart->setTitleFontSize(40);
    btnStart->cocos2d::Node::setPosition(0, -450);
    btnStart->setTitleColor(Color3B::BLACK);
    btnStart->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            PLAY_BUTTON_SOUND_EFFECT;
            //            this->pl->hide();
            this->onClickStartGame();
            
        }
    });
    
    //boss图像
    bossSpr=Sprite::create();
    bossSpr->setPosition(0, 220);
    
    //几率解锁技能和推荐技能
    auto skillInfoSpr=Sprite::create("img_window_props_in.png");
    skillInfoSpr->setPosition(0, 80);
    //文字——几率掉落技能
    auto txtUnlockSkill=Text::create();
    txtUnlockSkill->setString("几率解锁技能:");
    txtUnlockSkill->setFontSize(25);
    txtUnlockSkill->setColor(Color3B(2,187,209));
    txtUnlockSkill->cocos2d::Node::setPosition(100, 90);
    skillInfoSpr->addChild(txtUnlockSkill);
    //文字——推荐技能
    auto txtRcmdSkill=Text::create();
    txtRcmdSkill->setString("本关推荐技能:");
    txtRcmdSkill->setFontSize(25);
    txtRcmdSkill->setColor(Color3B(2,187,209));
    txtRcmdSkill->cocos2d::Node::setPosition(100, 35);
    skillInfoSpr->addChild(txtRcmdSkill);
    
    //几率掉落技能_内容
    sws1=SkillWithImgSprite::create();
    sws1->setPosition(160,15);
    txtUnlockSkill->addChild(sws1);
    
    //本关推荐技能_内容
    sws2=SkillWithImgSprite::create();
    sws2->setPosition(160,15);
    txtRcmdSkill->addChild(sws2);
    sws3=SkillWithImgSprite::create();
    sws3->setPosition(290,15);
    txtRcmdSkill->addChild(sws3);
    
    
    
    
    //技能面板
    auto skillListPanel=Sprite::create("img_window_props_select.png");
    skillListPanel->setPosition(0, -100);
    
    auto sList=RoleSkillList::getInstance();
    float posx=57,posy=180;
    int i=0;
    
    //创建技能按钮表
    for(std::map<int ,RoleSkill *>::iterator iter=sList.begin();iter!=sList.end();iter++){
        auto rs=(*iter).second;
        
        auto s=Button::create(rs->filename.c_str());
        s->setTag(rs->number);
        s->setScale(0.325);
        s->cocos2d::Node::setPosition(posx+110*(i%4),posy+ 0);
        s->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                auto btnSender=(Button *)(pSender);
                
                //遍历4个栏位,判断是否已选此技能
                for(int j=0;j<4;j++){
                    auto btn=btnArray[j];
                    if(btn->getTag()==btnSender->getTag()){
                        return;
                    }
                }
                
                //遍历4个栏位,找到未使用栏位
                for(int j=0;j<4;j++){
                    auto btn=btnArray[j];
                    if(btn->getTag()==0){
                        btn->setTag(btnSender->getTag());
                        
                        //给按钮换上技能图标
                        auto skillFound=RoleSkillList::getInstance()[btn->getTag()];
                        auto skillImg=Sprite::create(skillFound->filename);
                        skillImg->setPosition(45,46);
                        skillImg->setScale(0.325);
                        skillImg->setTag(TAG_SELECTED_SKILL_BUTTON_IMAGE);
                        btn->getChildByTag(TAG_SELECTED_SKILL_BUTTON_ADD_CHARACTOR)->setVisible(false);
                        
                        btn->addChild(skillImg);
                        
                        //存入
                        int a=j+1;
                        int b=btn->getTag();
                        CommonData::getInstance()->setCheckpointSkill(a,b);
                        log("第%d个技能为:%d",a,b);
                        
                        break;  //放置过技能后退出循环
                    }
                }
                
            }
        });
        auto btnIsValid=CommonData::getInstance()->getRoleSkillLevel(rs->number);
        if(btnIsValid<=0){
            s->setEnabled(false);
            s->setOpacity(50);
        }
        
        //如果是挑战模式或5的倍数的关卡，则次元门不可使用
        if(this->number==0||this->number%5==0){
            if(rs->number==8){
                s->setEnabled(false);
                s->setOpacity(50);
            }
        }
        
        //第50关的喷气背包不能使用
        if(this->number==0||this->number==50){
            if(rs->number==4){
                s->setEnabled(false);
                s->setOpacity(50);
            }
        }
        
        
        
        //加上文字说明
        auto desc=Text::create();
        desc->setString(rs->title.c_str());
        desc->setFontSize(18);
        desc->setColor(Color3B::WHITE);
        desc->cocos2d::Node::setPosition(posx+110*(i%4),posy-50);
        
        skillListPanel->addChild(desc);
        
        skillListPanel->addChild(s);
        //位置调整
        if(i%4==3){
            posy-=110;
        }
        i++;
    }
    
    
    //文字——请点击上选择……
    auto txtPleaseSelect=Text::create();
    txtPleaseSelect->setString("请点击上方选择本关使用技能");
    txtPleaseSelect->setFontSize(25);
    txtPleaseSelect->setColor(Color3B::WHITE);
    txtPleaseSelect->cocos2d::Node::setPosition(0, -240);
    
    //选择面板
    auto selectPanel=Sprite::create();
    selectPanel->setPosition(0, -315);
    for(int i=0;i<4;i++){
        float offset=-165;
        auto btnSelected=Button::create("img_window_props_frame.png");
        btnSelected->cocos2d::Node::setPosition(offset+110*i,0);
        selectPanel->addChild(btnSelected);
        //加号
        auto addCharactor=Sprite::create("img_window_props_frame_add.png");
        addCharactor->setPosition(btnSelected->getContentSize().width/2, btnSelected->getContentSize().height/2);
        addCharactor->setTag(TAG_SELECTED_SKILL_BUTTON_ADD_CHARACTOR);
        btnSelected->addChild(addCharactor);
        btnSelected->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
            if(type==Widget::TouchEventType::ENDED){
                PLAY_BUTTON_SOUND_EFFECT;
                auto btn=(Button *)(pSender);
                if(btn->getTag()!=0){
                    btn->setTag(0);
                    //换回加号图
                    btn->getChildByTag(TAG_SELECTED_SKILL_BUTTON_ADD_CHARACTOR)->setVisible(true);
                    auto img=btn->getChildByTag(TAG_SELECTED_SKILL_BUTTON_IMAGE);
                    if(img){
                        btn->removeChildByTag(TAG_SELECTED_SKILL_BUTTON_IMAGE);
                    }
                    
                    //删除技能
                    for(int j=0;j<4;j++){
                        //保存
                        if(btnArray[j]->getTag()==0){
                            CommonData::getInstance()->setCheckpointSkill(j+1, 0);
                        }
                    }
                    
                }
                
            }
        });
        
        btnSelected->setTag(0);
        
        btnArray[i]=btnSelected;
        
    }
    
    
    auto rootLayer=Layer::create();
    rootLayer->setPosition(SCREEN_CENTER);
    
    auto rootPanel=Sprite::create("img_window_props_bg.png");
    rootLayer->addChild(rootPanel);
    
    rootLayer->addChild(bossSpr);
    rootLayer->addChild(skillInfoSpr);
    rootLayer->addChild(skillListPanel);
    rootLayer->addChild(txtPleaseSelect);
    rootLayer->addChild(selectPanel);
    rootLayer->addChild(btnStart);

    
    
    
    this->addChild(bg,-10);
    this->addChild(rootLayer);
    this->addChild(btnBack);
    this->addChild(unlockPop,100);
    
    
    this->show();
    return true;
}


void SkillSelectScene::onEnter()
{
    cocos2d::Node::onEnter();
    
    if(isOffline&&this->number==0){
        Text *txt = Text::create();
        txt->setString("您的网络状态异常 进入离线模式");
        txt->setTextColor(Color4B(131, 89, 6,255));
        
        txt->setFontSize(40);
        txt->setPosition(SCREEN_CENTER);
        auto bg = Sprite::create("img_get_gold_bg.png");
        bg->setTag(233);
        bg->setPosition(SCREEN_CENTER);
        addChild(bg,30);
        
        ActionInterval * ai = FadeOut::create(1);
        auto action = Sequence::create(DelayTime::create(1.5),ai,CallFunc::create([&]{
            this->removeChild(txt);
            this->removeChild(getChildByTag(233));
        }),nullptr);
        this->addChild(txt,31);
        txt->runAction(action);
    }
}


void SkillSelectScene::show()
{
    
    //读取boss图像
    int bossNumber=number%5;
    if(bossNumber==0){
        bossNumber=5;
    }
    std::string bossFile="img_window_props_boss";
    bossFile.append(StringUtils::format("%d",bossNumber));
    bossFile.append(".png");
    bossSpr->setTexture(bossFile.c_str());
    
    //读取4个选择的技能
    for(int i=0;i<4;i++){
        auto s=CommonData::getInstance()->getCheckpointSkill(i+1);
        log("第%d个技能已解锁:%d",i+1,s);
        if(s>0){
            //如果是挑战模式，则移除次元门
            if(this->number==0||this->number%5==0){
                if(s==8){
                    btnArray[i]->setTag(0);
                    CommonData::getInstance()->setCheckpointSkill(i+1, 0);
                    continue;
                }
            }
            
            //如果在0关、50关有喷气背包，则移除
            if(this->number==0||this->number==50){
                if(s==4){
                    btnArray[i]->setTag(0);
                    CommonData::getInstance()->setCheckpointSkill(i+1, 0);
                    continue;
                }
            }
            
            
            auto btn=btnArray[i];
            btn->setTag(s);
            //给按钮换上技能图标
            auto skillFound=RoleSkillList::getInstance()[btn->getTag()];
            auto skillImg=Sprite::create(skillFound->filename);
            skillImg->setPosition(45,46);
            skillImg->setScale(0.325);
            skillImg->setTag(TAG_SELECTED_SKILL_BUTTON_IMAGE);
            btn->getChildByTag(TAG_SELECTED_SKILL_BUTTON_ADD_CHARACTOR)->setVisible(false);
            
            btn->addChild(skillImg);
            
            
        }
    }
    
    auto levelData=ReadDataFromMap::getInstance()->readLevelDataByLevel(number);
    if(levelData){
        log("可解锁技能:%d",levelData->getUnlockSkill());
        auto us=RoleSkillList::getInstance()[levelData->getUnlockSkill()];
        if(us){
            sws1->show(us->title, us->filename);
        }else{
            sws1->show(string("无"),string());
        }
        //推荐技能
        //有1个以上技能，且第一个技能编号不是5.
        auto rcList=levelData->recommendSkillList;
        if(rcList.size()>=1&&rcList.at(0)!=5){
            auto rs=RoleSkillList::getInstance()[rcList.at(0)];
            if(rs){
                sws2->show(rs->title, rs->filename);
            }else{
                sws2->show(string("无"),string());
            }
            //只有一个推荐技能则把第二个隐藏掉。
            sws3->setVisible(false);
            log("hide sws3");
            
            
            //有2个以上技能，且第二个技能编号不是5.
            if(rcList.size()>=2&&rcList.at(1)!=5){
                auto rs=RoleSkillList::getInstance()[rcList.at(1)];
                if(rs){
                    sws3->show(rs->title, rs->filename);
                }else{
                    sws3->show(string(),string());
                }
                //有2个推荐技能则把第二个显示出来。
                sws3->setVisible(true);
                log("技能2：%d",rcList.at(1));
                log("show sws3");
            }
        }else{
            sws3->show(string(),string());
        }
        
        
        
    }else{
        log("未读到关卡数据,关卡号:%d",number);
    }
    
    

    //初次使用显示教程
    if(this->number==2){
        
        //
        btnStart->setVisible(false);
        
        //第一步
        auto tt1=Sprite::create("img_guide_blackboard_bg.png");
        tt1Text=Sprite::create("img_guide_blackboard_word1.png");
        tt1Text->setPosition(tt1->getContentSize()/2);
        tt1->addChild(tt1Text);
        tt1->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-345);
        this->addChild(tt1);
        
        tt2=Sprite::create("img_guide_blackboard_light_big.png");
        tt2->cocos2d::Node::setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-484);
        
        auto listner=EventListenerTouchOneByOne::create();
        listner->onTouchBegan=[](Touch *touch,Event *event){
            return true;
        };
        listner->onTouchMoved=[](Touch *touch,Event *event){
        };
        listner->onTouchEnded=[=](Touch *touch,Event *event){
            tt2->setVisible(false);
            tt2->removeFromParentAndCleanup(true);
            tt1Text->setTexture("img_guide_blackboard_word2.png");
            
            {
                
                //第二步
                //方框
                tt3=Button::create("img_guide_blackboard_light_small.png");
                tt3->loadTexturePressed("img_guide_blackboard_light_small.png");
                tt3->cocos2d::Node::setPosition(150, SCREEN_HEIGHT-610);
                tt3->setSwallowTouches(false);
                tt3->addTouchEventListener([&](Ref *pSender,Widget::TouchEventType type){
                    if(type==Widget::TouchEventType::ENDED){
                        
                        tt3->setVisible(false);
                        tt1Text->setTexture("img_guide_blackboard_word3.png");
                        
                        btnStart->setVisible(true);
                        //第三步
                        tt5=Sprite::create("img_guide_arrow2.png");
                        tt5->setPosition(SCREEN_WIDTH/2, 200);
                        this->addChild(tt5);
                        
                        //闪烁动画
                        {
                            auto fi=FadeIn::create(0.4);
                            auto fo=FadeOut::create(0.2);
                            auto seq=Sequence::create(DelayTime::create(0.3),fo,fi, NULL);
                            auto repeatAct=RepeatForever::create(seq);
                            tt5->runAction(repeatAct);
                        }
                    }
                });
                
                this->addChild(tt3);
                
                //箭头
                auto tt4=Sprite::create("img_guide_arrow.png");
                tt4->setPosition(0, tt3->getContentSize().height);
                tt3->addChild(tt4);
                
                //闪烁动画
                {
                    auto fi=FadeIn::create(0.4);
                    auto fo=FadeOut::create(0.2);
                    auto seq=Sequence::create(DelayTime::create(0.3),fo,fi, NULL);
                    auto repeatAct=RepeatForever::create(seq);
                    tt4->runAction(repeatAct);
                }
                
            }
            
        };
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, tt2);
        
        this->addChild(tt2);
        
        //闪烁动画
        {
            auto fi=FadeIn::create(0.4);
            auto fo=FadeOut::create(0.5);
            auto seq=Sequence::create(DelayTime::create(0.3),fo,fi, NULL);
            auto repeatAct=RepeatForever::create(seq);
            tt2->runAction(repeatAct);
        }
        
        
        
    }
    
    
    
    
    
}

//点击开始游戏按钮
void SkillSelectScene::onClickStartGame()
{
    //更新第一个锁定的关卡号
    for(int i=0;i<50;i++){
        int state=CommonData::getInstance()->get(i+1);
        if(state==CHECKPOINT_LOCKED){
            Checkpoint::firstLockedCheckpoint=i+1;
            log("第一个锁定关卡号：%d",Checkpoint::firstLockedCheckpoint);
            break;
        }
    }
    
    //第0关是挑战模式。挑战模式和第一个未解锁关卡不需要解锁。
    if(this->state==CHECKPOINT_LOCKED&&this->number!=0&&this->number!=Checkpoint::firstLockedCheckpoint){
        
        //锁定的关卡
        unlockPop->show();
    }else{
        if(this->number==0){
            Director::getInstance()->replaceScene(PlayScene::createScene(0, this->username.c_str(), this->floor));
        }else{
            Director::getInstance()->replaceScene(PlayScene::createScene(this->number));
        }
    }
    
}