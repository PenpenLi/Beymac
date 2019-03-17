//
//  Rankws.h
//  beymac
//
//  Created by je on 6/2/15.
//
//

#ifndef __beymac__Rankws__
#define __beymac__Rankws__

#include "cocos2d.h"
#include "HttpClient.h"

USING_NS_CC;
using namespace network;

class RankwsDelegate{
public:
    
    bool isSceneRunning;//场景是否正在运行
    
    std::string isExistName;//是否存在名字
    
    std::string registeringName;    //正在注册的名字
    
    
    
    //是否刷新的对手
    bool refreshOpponent;
    
    //匹配结果_对手
    int floor;
    int rank;
    int score;
    std::string username;
    
    //匹配结果_自己
    int myFloor;
    std::string myUsername;
    
    //名称是否存在
    virtual void isUsernameExist(bool exist)=0;
    //获取名称
    virtual void onGetUsername(bool succeed,std::string username)=0;
    //注册名称
    virtual void onRegistered(bool succeed)=0;
    //匹配到对手
    virtual void onMatchedWithOther(const int floor,const int rank,const int score,std::string username,const int myFloor,std::string myUsername)=0;
    //离线模式
    virtual void onOffline()=0;
    
    
    
private:

    
};


class Rankws{
public:
    Rankws(RankwsDelegate *ws);
    
    //是否存在名称
//    void hasUsername();
    
    //根据imei获取名字，没有则自动起名
    void getUsername();
    
    //注册名称
    void registerUsername(std::string username);
    
    //匹配对手
    void matchWithOther();
    
private:
    void httpGet(std::string url,std::string tag);
    
    std::string getImei();
    
    RankwsDelegate *callback;
    
    
};

#endif /* defined(__beymac__Rankws__) */
