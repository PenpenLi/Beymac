//
//  PaymentForAndroid.h
//  WaterWars
//
//  Created by je on 4/8/15.
//
//

#include "cocos2d.h"
#include "Payment.h"

USING_NS_CC;


class PaymentForAndroid{
public:
    
    static void pay(int itemId,PaymentDelegate *delegate);
    
};