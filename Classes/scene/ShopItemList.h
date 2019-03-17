//
//  ShopItemList.h
//  WaterWars
//
//  Created by je on 4/15/15.
//
//


#include "cocos2d.h"
#include "CommonHeader.h"

#define LANGUAGE_ZH 0

USING_NS_CC;


//商品
class ShopItem{
public:
    int id; //ios和android使用同一个使用
    int gold;
    float price;
};



//商品列表
class ShopItemList{
private:
    static std::map<int,ShopItem> mapItems;
    
public:
    static std::map<int,ShopItem> get();
};