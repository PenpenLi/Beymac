//
//  WebService.h
//  WaterWars
//
//  Created by je on 3/24/15.
//
//

#include "cocos2d.h"
#include "HttpClient.h"

USING_NS_CC;

class WebServiceDelegate{
public:
    bool isSceneRunning;
    
    virtual void onNormalRankGot(int rank)=0;
    virtual void onUnlimitedRankGot(int rank)=0;
};


class WebService{
public:
    WebService(WebServiceDelegate *callback);
    
    void getNormalRank();
    
    void getNormalRank(const int level);
    
    void getUnlimitedRank();
    
    void getUnlimitedRank(const int floor);
    
    
public:
    //匹配信息
    static int enemyFloor;
    static int enemyRank;
    static int myRank;
    
private:
    
    std::string getImei();
    
    void httpGet(std::string url,std::string tag);
    
private:
    WebServiceDelegate *callback;
    
};