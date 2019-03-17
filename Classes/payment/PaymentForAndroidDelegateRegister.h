//
//  PaymentForAndroidDelegateRegister.h
//  WaterWars
//
//  Created by je on 4/15/15.
//
//  支付委托暂存器


#ifndef __beymac__PaymentForAndroidDelegateRegister__
#define __beymac__PaymentForAndroidDelegateRegister__

#include "cocos2d.h"
#include "Payment.h"

USING_NS_CC;


////支付委托接口
//class PaymentForAndroidDelegate{
//public:
//    virtual void onPaymentForAndroidFinished(bool succeed)=0;    //支付结果回调
//};


//支付委托暂存器（只管存储，不负责执行）
class PaymentForAndroidDelegateRegister{
    
private:
    
    //委托集合map
    static std::map<int,PaymentDelegate *> mapItems;
    
    //委托编号，自增
    static int uniqueNo;
    
public:
    
    //存入委托
    static int add(PaymentDelegate *delegate);
    
    //取出委托
    static PaymentDelegate *get(int delegateId);
    
};


#endif