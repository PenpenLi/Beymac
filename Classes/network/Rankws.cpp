//
//  Rankws.cpp
//  beymac
//
//  Created by je on 6/2/15.
//
//

#include "Rankws.h"
#include "HttpClient.h"
#include <json/document.h>
#include "Manager.h"
#include "WebService.h"

#define URL_HEAD "http://42.96.192.233/waterwar/";

USING_NS_CC;

using namespace cocos2d::network;
using namespace rapidjson;


Rankws::Rankws(RankwsDelegate *ws)
{
    callback=ws;
    callback->refreshOpponent=false;
    
}

////是否存在名称
//void Rankws::hasUsername()
//{
//    std::string url=URL_HEAD;
//    url.append("member/isHasUsername?imei=");
//    url.append(getImei());
//    
//    httpGet(url.c_str(),"1");
//}

//起名
void Rankws::getUsername()
{
    std::string url=URL_HEAD;
    url.append("member/getUsername?imei=");
    url.append(getImei());
    
    httpGet(url,std::string("2"));
}

//注册名称
void Rankws::registerUsername(std::string username)
{
    std::string url=URL_HEAD;
    url.append("member/Registered");
    
    callback->registeringName=username;
    
    httpGet(url,std::string("3"));
}

//匹配对手
void Rankws::matchWithOther()
{
    std::string url=URL_HEAD;
    url.append("member/getEnemy?imei=");
    url.append(getImei());
    url.append("&enemynum=5");
    
    httpGet(url,std::string("4"));
}

std::string Rankws::getImei()
{
    return Manager::getInstance()->getImei();
}

void Rankws::httpGet(std::string url,std::string tag)
{
    if(!Manager::getInstance()->isNetworkConnected()){
        log("无网络连接");
        if(callback&&callback->isSceneRunning){
            log("场景不在");
            callback->onOffline();
        }
        return;
    }
    
    auto request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);
    //第三个请求因为有中文参数，所以使用post提交
    if(tag.compare(std::string("3"))==0){
        log("一样");
        request->setRequestType(network::HttpRequest::Type::POST);
        std::string postData="imei=";
        postData.append(getImei());
        postData.append("&username=");
        postData.append(callback->registeringName);
        request->setRequestData(postData.c_str(), postData.length());
        
    }else{
        log("不一样");
    }
    
    request->setResponseCallback([&](HttpClient* client, HttpResponse* response){
        log("http callback.");
        
        //取长度
        std::vector<char, std::allocator<char>> *buffer = response->getResponseData();
        unsigned long len=buffer->size();
        log("长度:%lu", len);
        
        if(len>0){
            //清除乱码（返回的数据偶尔会在最后附加乱码）
//            char *data=(char *)malloc(sizeof(char)*len);
//            strncpy(data, buffer->data(), len);
//            data[len]=0;
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
            
            if(callback&&callback->isSceneRunning){
                auto tag=response->getHttpRequest()->getTag();
                if(strcmp(tag,"1")==0){
                    int isExist=0;
                    isExist=std::atoi(data);
                    if(isExist){
                        callback->isUsernameExist(true);
                    }else{
                        callback->isUsernameExist(false);
                    }
                }else if(strcmp(tag,"2")==0){
                    Document doc;
                    doc.Parse<kParseDefaultFlags>(data);
                    if(doc.HasMember("status")){
                        auto name=doc["obj"].GetString();
                        if(doc["status"].GetInt()==1){
                            callback->onGetUsername(true,std::string(name));
                        }else{
                            callback->onGetUsername(false, std::string(name));
                        }
                    }
                }else if(strcmp(tag,"3")==0){
                    int succeed=0;
                    succeed=std::atoi(data);
                    if(succeed){
                        callback->onRegistered(true);
                    }else{
                        callback->onRegistered(false);
                    }
                }else if(strcmp(tag,"4")==0){
                    Document doc;
                    doc.Parse<kParseDefaultFlags>(data);
                    if(doc.HasMember("status")){
                        if(doc["status"].GetInt()==1){
                            if(doc["obj"].IsArray()){
                                for(int i=0;i<doc["obj"].Size();i++){
                                    rapidjson::Value &a= doc["obj"][i];
                                    auto floor=a["floor"].GetInt();
                                    auto rank=a["rank"].GetInt();
                                    auto score=a["score"].GetInt();
                                    auto username=a["username"].GetString();
                                    //对手
                                    rapidjson::Value &b= doc["obj"][1];
                                    auto myfloor=b["floor"].GetInt();
                                    auto myrank=b["rank"].GetInt();
                                    auto myscore=b["score"].GetInt();
                                    auto myusername=b["username"].GetString();
                                    
                                    WebService::enemyRank=rank;
                                    WebService::enemyFloor=floor;
                                    WebService::myRank=myrank;
                                    
                                    callback->onMatchedWithOther(floor, rank, score,std::string(username),myfloor,std::string(myusername));
                                    break;
                                }
                            }
                        }else{
                            log("imei不存在");
                            Rankws::getUsername();
                        }
                    }

                }
                
                
            }

            
        }else{
            log("网络请求返回空，无网络连接");
            if(callback&&callback->isSceneRunning){
                callback->onOffline();
            }
        }
    });
    
    request->setTag(tag.c_str());
    HttpClient::getInstance()->setTimeoutForConnect(3);
    HttpClient::getInstance()->setTimeoutForRead(1);
    HttpClient::getInstance()->send(request);
//    request->release();
}
