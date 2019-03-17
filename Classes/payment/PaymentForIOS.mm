//
//  Payment.cpp
//  WaterWars
//
//  Created by lingzerg on 15/4/1.
//
//

#include "PaymentForIOS.h"
#import "StoreObserver.h"
#include "Reachability.h"
#include "CommonData.h"

StoreObserver* observer = NULL;

PaymentForIOSDelegate *mDelegate;

void registerDelegate(PaymentForIOSDelegate *delegate) {
    mDelegate = delegate;
}


namespace store {
    class GetStoreDelegate :public StoreDelegate {
    public :
        static GetStoreDelegate *getStore;
        static GetStoreDelegate* getInstance(int type) {
            
            if (!getStore) {
                getStore = new GetStoreDelegate();
            }
            
            observer = [[StoreObserver alloc] init];
            [observer Create];
            [observer setDelegate:getStore];
            [observer Buy:type];
            
            return getStore;
        }
        
    public:
        void payResult(bool result) {
            if (result) {
                mDelegate->payResult(result);
            } else {
                mDelegate->payResult(result);
            }
        }
    };
    
    GetStoreDelegate *GetStoreDelegate::getStore = NULL;
    
    void pay(int type) {
        
        Reachability *r = [Reachability reachabilityWithHostName:@"www.apple.com"];
        switch ([r currentReachabilityStatus]) {
            case NotReachable:
                // 没有网络连接
                mDelegate->payResult(false);
                break;
            case ReachableViaWWAN:
                // 使用3G网络
                store::GetStoreDelegate::getInstance(type);
                break;
            case ReachableViaWiFi:
                // 使用WiFi网络
                store::GetStoreDelegate::getInstance(type);
                break;
        }
    }
}

