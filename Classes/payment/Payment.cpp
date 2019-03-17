//
//  Payment.cpp
//  BeyMac
//
//  Created by lingzerg on 15/6/8.
//
//

#include "Payment.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "PaymentForIOS.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "PaymentForAndroid.h"
#endif



//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#import "StoreObserver.h"
//#import "Reachability.h"
//#endif




PaymentDelegate *payDelegate;

namespace Payment {
    
    class PaymentIOS : public PaymentForIOSDelegate {
        
    public:
        void payResult(bool result) {
            if (payDelegate) {
                if (result) {
                    payDelegate->payResult(result);
                } else {
                    payDelegate->payResult(result);
                }
            }
        }
        
        static PaymentIOS *paymentIOS;
        static void getInstance(int type) {
            if (!paymentIOS) {
                paymentIOS = new PaymentIOS();
            }
            registerDelegate(paymentIOS);
            store::pay(type);
            
        }
    };
    
    PaymentIOS *PaymentIOS::paymentIOS = NULL;

    void pay(int type) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PaymentIOS::getInstance(type);
#endif
    }
    
    void pay(int type,PaymentDelegate *delegate) {
        payDelegate = 0;
        payDelegate = delegate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        PaymentIOS::getInstance(type);
#endif
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        payDelegate->payResult(true);
        PaymentForAndroid::pay(type, delegate);
#endif
        
    }
}

