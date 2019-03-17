//
//  MonsterAttackSequence.cpp
//  beymac
//
//  Created by je on 5/8/15.
//
//

#include "MonsterAttackSequence.h"

USING_NS_CC;


void MonsterAttackSequence::addMonsterAttack(MonsterAttack *ma)
{
    maVector.push_back(ma);
}

MonsterAttack *MonsterAttackSequence::next()
{
    if(maVector.size()<=0){
        log("maVector is empty.");
        return nullptr;
    }
    if(curMonsterAttack>=maVector.size()){
        curMonsterAttack=0;
    }
    auto mstAttack=maVector.at(curMonsterAttack);
    curMonsterAttack++;
    return mstAttack;
}