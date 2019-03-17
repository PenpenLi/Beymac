//
//  RankingPop.h
//  beymac
//
//  Created by je on 6/2/15.
//
//

#ifndef __beymac__RankingPop__
#define __beymac__RankingPop__


#include "cocos2d.h"
#include "PopupLayer.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class RankItem{
public:
    int rank;
    std::string name;
};

class RankingPop:PopupLayer{
public:
    static PopupLayer *create();
    
    static void refreshData();
    
    
    static void httpGet(const char *url,const char *tag);
    
    
public:
    
    static std::vector<RankItem> rankItemList;
    
    static PopupLayer *rl;
    
    static ListView *lv;
  
    
private:
    
    static std::string getImei();
    
};


#endif /* defined(__beymac__RankingPop__) */
