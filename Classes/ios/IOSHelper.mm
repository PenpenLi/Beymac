//
//  IOSHelper.cpp
//  WaterWars
//
//  Created by lingzerg on 15/4/8.
//
//

#include "IOSHelper.h"
#import <AdSupport/AdSupport.h>
#include "RootViewController.h"
#include "Reachability.h"

namespace IOSHelper {
    
    std::string getIMEI() {
        return [[[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString] UTF8String];
    }
    
    bool checkNetworkConnectedInIOS() {
        Reachability *r = [Reachability reachabilityWithHostName:@"www.apple.com"];
        switch ([r currentReachabilityStatus]) {
            case NotReachable:
                // 没有网络连接
                return false;
                break;
            case ReachableViaWWAN:
                // 使用3G网络
                return true;
                break;
            case ReachableViaWiFi:
                // 使用WiFi网络
                return true;
                break;
        }
        return false;
    }
    
    void showAdBar() {
        //[[RootViewController shareRootViewController] showAdBar];
    }
    
    void hidenAdBar() {
        //[[RootViewController shareRootViewController] hidenAdBar];
    }
    
    void showAdInterstitial() {
        //[[RootViewController shareRootViewController] showAdInterstitial];
    }
    
    void loadAdInterstitial() {
        //[[RootViewController shareRootViewController] loadAdInterstitial];
    }
    
    bool isQQInstalledIOS (){
        
        return [QQApiInterface isQQInstalled];
    }
    
    void sendNewsMessageWithNetworkImage() {
        [[RootViewController shareRootViewController] sendNewsMessageWithNetworkImage];
    }
}
