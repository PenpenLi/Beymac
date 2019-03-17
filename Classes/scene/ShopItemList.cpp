//
//  ShopItemList.cpp
//  WaterWars
//
//  Created by je on 4/15/15.
//
//

#include "ShopItemList.h"



//商品列表
std::map<int,ShopItem> ShopItemList::mapItems;

std::map<int,ShopItem> ShopItemList::get()
{
#if (CC_TARGET_PLATFORM ==CC_PLATFORM_IOS )
    
    mapItems[0].id=1;
    mapItems[0].gold=20;
    mapItems[1].id=2;
    mapItems[1].gold=45;
    mapItems[2].id=3;
    mapItems[2].gold=100;
    //中英文,RMB和美元数值不同。
    if(CommonData::getInstance()->getLanguage()==LANGUAGE_ZH){
        mapItems[0].price=6;
        mapItems[1].price=12;
        mapItems[2].price=18;
    }else{
        mapItems[0].price=0.99;
        mapItems[1].price=1.99;
        mapItems[2].price=3.99;
    }
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    mapItems[0].id=2;
    mapItems[0].gold=20;
    mapItems[0].price=6;
    mapItems[1].id=3;
    mapItems[1].gold=45;
    mapItems[1].price=12;
    mapItems[2].id=4;
    mapItems[2].gold=100;
    mapItems[2].price=20;
#endif
    
    return mapItems;
}