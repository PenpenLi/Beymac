//
//  CastableBody.h
//  beymac
//
//  Created by je on 6/12/15.
//
//

#ifndef __beymac__CastableBody__
#define __beymac__CastableBody__

#include "MonsterAbility.h"

USING_NS_CC;

class CastableBody:public Node{
public:
    
    virtual void onCast(MonsterAbility *abi)=0;
    
    virtual void onCancel(const int abiType)=0;
        
};




#endif /* defined(__beymac__CastableBody__) */
