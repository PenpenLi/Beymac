//
//  WebService.cpp
//  WaterWars
//
//  Created by je on 3/24/15.
//
//

#include "WebService.h"
#include "HttpClient.h"
#include <json/document.h>
#include "Manager.h"


#define URL_HEAD "http://42.96.192.233/waterwar/";


USING_NS_CC;
using namespace cocos2d::network;
using namespace rapidjson;


int WebService::enemyFloor;
int WebService::enemyRank;
int WebService::myRank;


WebService::WebService(WebServiceDelegate *callback)
{
    this->callback=callback;
}

void WebService::getNormalRank()
{
    std::string url=URL_HEAD;
    url.append("member/getNormalRank?imei=");
    url.append(getImei());
    httpGet(url,std::string("1"));
}

void WebService::getNormalRank(const int level)
{
    std::string url=URL_HEAD;
    url.append("member/getNormalRank?imei=");
    url.append(getImei());
    url.append("&level=");
    url.append(StringUtils::format("%d",level));
    httpGet(url,std::string("2"));
}

void WebService::getUnlimitedRank()
{
    std::string url=URL_HEAD;
    url.append("member/getUnlimitedRank?imei=");
    url.append(getImei());
    httpGet(url,std::string("3"));
}

void WebService::getUnlimitedRank(const int floor)
{
    std::string url=URL_HEAD;
    url.append("member/isWin?imei=");
    url.append(getImei());
    url.append("&rank=");
    url.append(StringUtils::format("%d",myRank));
    url.append("&floor=");
    url.append(StringUtils::format("%d",floor));
    url.append("&enemyFloor=");
    url.append(StringUtils::format("%d",enemyFloor));
    url.append("&enemyRank=");
    url.append(StringUtils::format("%d",enemyRank));
    httpGet(url,std::string("4"));
}



//void WebService::getUnlimitedRank(const int floor)
//{
//    std::string url=URL_HEAD;
//    url.append("member/getUnlimitedRank?imei=");
//    url.append(getImei());
//    url.append("&floor=");
//    url.append(StringUtils::format("%d",floor));
//    httpGet(url.data(),"4");
//}




std::string WebService::getImei()
{
    return Manager::getInstance()->getImei();
}


void WebService::httpGet(std::string url,std::string tag)
{
    if(!Manager::getInstance()->isNetworkConnected()){
        log("无网络连接");
        return;
    }
    
    auto request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback([&](HttpClient* client, HttpResponse* response){
        log("http callback.");
        
        std::vector<char, std::allocator<char>> *buffer = response->getResponseData();
        //取长度
        unsigned long len=buffer->size();
        log("长度:%lu", len);
        
        //判断是否为空
        if(len>0){
            //清除乱码（返回的数据偶尔会在最后附加乱码）
            
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
            
            if(callback){
                if(callback->isSceneRunning){
                    log("call begin");

                    std::string tag=response->getHttpRequest()->getTag();
                    
                    int rank=0;//排名
                    
                    if(tag.compare("1")==0){
                        rank=std::atoi(data);//失败返回0
                        log("rank:%d",rank);
                        callback->onNormalRankGot(rank);
                    }
                    if(tag.compare("2")==0){
                        rank=std::atoi(data);//失败返回0
                        log("rank:%d",rank);
                        callback->onNormalRankGot(rank);
                    }
                    if(tag.compare("3")==0){
                        rank=std::atoi(data);//失败返回0
                        log("rank:%d",rank);
                        callback->onUnlimitedRankGot(rank);
                    }
                    if(tag.compare("4")==0){
                        log("tag 4");
                        
                        Document doc;
                        doc.Parse<kParseDefaultFlags>(data);
                        if(doc.HasMember("status")){
                            if(doc["status"].GetInt()==1){
                                rank=doc["rank"].GetInt();
                                log("rank:%d",rank);
                                callback->onUnlimitedRankGot(rank);
                            }
                        }else{
                            log("解析错误");
                        }

                        
                        
                        
                    }
                    log("call end");
                }
            }
        }
    });
    
    request->setTag(tag.c_str());
    HttpClient::getInstance()->send(request);
//    request->release();
}






