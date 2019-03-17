//
//  AndroidHelper.h
//  WaterWars
//
//  Created by lingzerg on 15/4/13.
//
//



#ifndef __WaterWars__AndroidHelper__
#define __WaterWars__AndroidHelper__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

using namespace std;

extern "C" {
    
    //广告组件
    void showAdBar();
    void hidenAdBar();
    void showAdInterstitial();
    void loadAdInterstitial();
    
    //QQ分享
    void sendNewsMessageWithNetworkImage();
    
    
    //判断是否有网络
    bool isNetworkConnectedInAndroid();
    
    std::string getImeiForAndroid();
    
    //退出cocos时通知android
    void noticeAndroidToExit();

}

#endif /* defined(__WaterWars__AndroidHelper__) */
#endif
