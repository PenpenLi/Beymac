//
//  PaymentForAndroidDelegateRegister.cpp
//  WaterWars
//
//  Created by je on 4/15/15.
//
//  支付委托暂存器

#include "PaymentForAndroidDelegateRegister.h"

USING_NS_CC;

//委托集合map
std::map<int,PaymentDelegate *> PaymentForAndroidDelegateRegister::mapItems;

//委托编号，自增（从1开始）
int PaymentForAndroidDelegateRegister::uniqueNo;

//存入委托
int PaymentForAndroidDelegateRegister::add(PaymentDelegate *delegate)
{
    if(!delegate){
        log("存入委托为空");
        return 0;
    }
    
    int delegateId=++uniqueNo; //为委托编号
    mapItems[delegateId]=delegate; //存入
    log("存入的委托编号：%d",delegateId);
    return delegateId;
}

//取出委托
PaymentDelegate *PaymentForAndroidDelegateRegister::get(int delegateId)
{
    log("取出的委托编号：%d",delegateId);
    
    auto delegate=mapItems[delegateId];
    
    mapItems.erase(delegateId); //即使没有找到，系统仍会自动插入初始值。因此要无论如何都要删除掉。
    
    return delegate;
}
