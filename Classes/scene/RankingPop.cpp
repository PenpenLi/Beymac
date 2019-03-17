//
//  RankingPop.cpp
//  beymac
//
//  Created by je on 6/2/15.
//
//

#include "RankingPop.h"
#include "HttpClient.h"
#include <json/document.h>
#include "Manager.h"


#define URL_HEAD "http://42.96.192.233/waterwar/";

USING_NS_CC;
using namespace ui;
using namespace cocos2d::network;
using namespace rapidjson;

std::vector<RankItem> RankingPop::rankItemList;


PopupLayer *RankingPop::rl;

ListView *RankingPop::lv;

PopupLayer *RankingPop::create()
{
    auto rp=PopupLayer::create("img_window_ranking_bg.png");
    
    rp->setCloseButton("img_window_btn_close.png",260,290);
    
 
    RankingPop::rl=rp;
    
    
    return rp;
}

void RankingPop::refreshData()
{
    std::string str=URL_HEAD;
    str.append("member/getKing?imei=");
    str.append(getImei());
    str.append("&count=30");
    
    httpGet(str.c_str(), "1");
    
}


std::string RankingPop::getImei()
{
    return Manager::getInstance()->getImei();
}



void RankingPop::httpGet(const char *url,const char *tag)
{
    if(!Manager::getInstance()->isNetworkConnected()){
        log("无网络连接");
        return;
    }
    
    auto request = new HttpRequest();
    request->setUrl(url);
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback([&](HttpClient* client, HttpResponse* response){
        log("http callback.");
        
        std::vector<char, std::allocator<char>> *buffer = response->getResponseData();
        unsigned long len=buffer->size();
        log("长度:%lu", len);
        if(len>0){
            
            //我的排名
            auto myRank=Text::create();
            myRank->setFontSize(35);
            myRank->setColor(Color3B::WHITE);
            myRank->cocos2d::Node::setPosition(0, -320);
            myRank->setString(StringUtils::format("当前排名:暂无"));
            if(rl){
                rl->addChild(myRank);
            }
            
            if(lv){
                lv->removeFromParentAndCleanup(true);
                lv=nullptr;
            }
            
            lv=ListView::create();
            lv->setAnchorPoint(Vec2(0.5, 0.5));
            
            auto txt=Text::create();
            txt->setString("Btn.......");
            txt->setFontSize(40);
            txt->setColor(Color3B::WHITE);
            
            //排名
            auto btnRankModel=Button::create("img_window_ranking_line.png");
            
            
            
            //排名
            auto btnRankM=Button::create("img_window_ranking_round.png");
            btnRankM->setTitleText(StringUtils::format("%d",1));
            btnRankM->setTitleFontSize(35);
            btnRankM->cocos2d::Node::setPosition(-200,0);
            btnRankModel->addChild(btnRankM);
            
            //加上分数
            auto scoreTxtModel=Text::create();
            scoreTxtModel->setString(StringUtils::format("%d",1).c_str());
            scoreTxtModel->setFontSize(30);
            scoreTxtModel->setColor(Color3B::YELLOW);
            btnRankModel->addChild(scoreTxtModel);
            
            
            lv->setItemModel(btnRankModel);
            lv->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
            lv->setItemsMargin(5);
            lv->setContentSize(Size(450,500));
            
            if(rl){
                rl->addChild(lv);
            }else{
                log("rp为空");
            }
            
            //复制出内容
//            std::string *str=new std::string(len,0);
//            str->copy(buffer->data(), len);
//            str->at(len)=0;
//            auto data=str->c_str();
//            log("data:%s",data);
            
            char *data=(char *)alloca(sizeof(char)*len);
            strncpy(data, buffer->data(), len);
            data[len]=0;
            log("data:%s",data);
            
            //判断服务器是否异常
            std::string recData=std::string(data);
            if(recData.find("<html>")!=std::string::npos){
                log("服务端返回错误.");
                return;
            }
            
            Document doc;
            doc.Parse<kParseDefaultFlags>(data);
            
            
            if(doc.HasMember("status")){
                auto status=doc["status"].GetInt();
                if(status==2){
                    log("排行获取失败.");
                    return;
                }
                
                if(doc["rank"].IsInt()){
                    auto myrankInt=doc["rank"].GetInt();
                    myRank->setString(StringUtils::format("您的当前排名:  %d",myrankInt));
                }
                
                if(doc["obj"].IsArray()){
                    
                    for(int i=0;i<doc["obj"].Size();i++){
                        
                        rapidjson::Value &a= doc["obj"][i];
                        
                        std::string str="username:";
                        
                        std::string nameStr;
                        if(a["username"].IsString()){
                            nameStr.append(a["username"].GetString());
                            str.append(a["username"].GetString());
                        }else{
                            str.append("null");
                        }
                        if(a["rank"].IsInt()){
                            
                            auto rank=a["rank"].GetInt();
                            
                            str.append(",rank:");
                            
                            str.append(StringUtils::format("%d",rank));
                        }else{
                            str.append("0");
                        }
                        int score=0;
                        if(a["score"].IsInt()){
                            score=a["score"].GetInt();
                        }
                        
                        auto t=Text::create();
                        t->setString(str.c_str());
                        t->setFontSize(40);
                        t->setColor(Color3B::WHITE);
                        
                        //底板
                        auto itemPanel=Button::create("img_window_ranking_line.png");
                        
                        
                        //排名
                        int curRank=i+1;
                        
                        //排名
                        Button *btnRank;
                        //前3名图片不同
                        if(curRank<=3){
                            if(curRank==1){
                                btnRank=Button::create("img_ranking_1.png");
                            }else if(curRank==2){
                                btnRank=Button::create("img_ranking_2.png");
                            }else if(curRank==3){
                                btnRank=Button::create("img_ranking_3.png");
                            }
                        }else{
                            btnRank=Button::create("img_window_ranking_round.png");
                            //设置名次数字，前3名不需要，图片上写的有。
                            btnRank->setTitleText(StringUtils::format("%d",curRank));
                            btnRank->setTitleFontSize(35);
                            btnRank->setTitleColor(Color3B(106,59,42));
                        }
                        btnRank->cocos2d::Node::setPosition(60,50);
                        itemPanel->addChild(btnRank);
                        
                        //名字
                        auto nameTxt=Text::create();
                        nameTxt->setFontSize(40);
                        nameTxt->setColor(Color3B::WHITE);
                        if(nameStr.empty()){
                            nameStr.append("空");
                        }
                        nameTxt->setString(nameStr.c_str());
                        nameTxt->setAnchorPoint(Vec2(0, 0.5));
                        nameTxt->cocos2d::Node::setPosition(120, 50);
                        itemPanel->addChild(nameTxt);
                        
                        //加上分数
                        auto scoreTxt=Text::create();
                        scoreTxt->setString(StringUtils::format("%d",score).c_str());
                        scoreTxt->setFontSize(35);
                        scoreTxt->setColor(Color3B::YELLOW);
                        scoreTxt->cocos2d::Node::setPosition(450, 50);
                        itemPanel->addChild(scoreTxt);
                        
                        lv->pushBackCustomItem(itemPanel);
                        
                        
                    }
                    
                }
                
                
                
                
            }
            
            
            
        }
        
        
        
    });
    
    request->setTag(tag);
    HttpClient::getInstance()->send(request);
//    request->release();
}



