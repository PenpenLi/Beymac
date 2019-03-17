//
//  AllBomb.h
//  BeyMac
//
//  Created by lingzerg on 15/5/13.
//
//

#ifndef __BeyMac__AllBomb__
#define __BeyMac__AllBomb__

#include "cocos2d.h"
USING_NS_CC;

class AllBomb : public Node
{
public:
    AllBomb();
    ~AllBomb();
    static AllBomb* createNode();
    virtual bool init();
    CREATE_FUNC(AllBomb);
    
private:
    void initData();
};

#endif /* defined(__BeyMac__AllBomb__) */
