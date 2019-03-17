//
//  MonsterAttackSequence.h
//  beymac
//
//  Created by je on 5/8/15.
//
//

#ifndef __beymac__MonsterAttackSequence__
#define __beymac__MonsterAttackSequence__

#include "cocos2d.h"

///1.吐子弹，2.吐炸弹，3.吐冰块.4.吐粘液，5.激光，6.反射激光 7.水泡

class MonsterAttack{
public:
    int attackModeNumber;
    int power;
    float speed;
};

class MonsterAttackSequence{
public:
    void addMonsterAttack(MonsterAttack *ma);
    
    MonsterAttack *next();
    
private:
    int curMonsterAttack;
    
    std::vector<MonsterAttack *> maVector;
};



#endif