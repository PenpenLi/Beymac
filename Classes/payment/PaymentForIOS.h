//
//  Payment.h
//  WaterWars
//
//  Created by lingzerg on 15/4/1.
//
//

#ifndef __WaterWars__Payment__
#define __WaterWars__Payment__

#include "cocos2d.h"
//#include "StoreObserver.h"

namespace store {
    void pay(int type);
}

class PaymentForIOSDelegate {
public:
    virtual void payResult(bool result) = 0;
};

void registerDelegate(PaymentForIOSDelegate *delegate);

#endif /* defined(__WaterWars__Payment__) */
