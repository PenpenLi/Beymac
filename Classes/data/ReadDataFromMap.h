//
//  ReadDataFromMap.h
//  beymac
//
//  Created by mumu on 15/6/26.
//
//

#ifndef __beymac__ReadDataFromMap__
#define __beymac__ReadDataFromMap__

#include "cocos2d.h"
#include "LevelConfig.h"
#include "LevelData.h"

USING_NS_CC;

class ReadDataFromMap
{
public:
    
    static ReadDataFromMap* getInstance();
    // 根据关卡数读取关卡数据
    LevelData* readLevelDataByLevel(int level);
    
    
private:
    
};

#endif /* defined(__beymac__ReadDataFromMap__) */
