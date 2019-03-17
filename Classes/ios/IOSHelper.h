//
//  IOSHelper.h
//  WaterWars
//
//  Created by lingzerg on 15/4/8.
//
//

#ifndef __WaterWars__IOSHelper__
#define __WaterWars__IOSHelper__

#include "cocos2d.h"

namespace IOSHelper {
    
    //IEMI
    std::string getIMEI();
    
    //广告组件
    void showAdBar();
    void hidenAdBar();
    void showAdInterstitial();
    void loadAdInterstitial();
    
    //QQ分享
    bool isQQInstalledIOS();
    void sendNewsMessageWithNetworkImage();
    
    bool checkNetworkConnectedInIOS();
}
#endif /* defined(__WaterWars__IOSHelper__) */
