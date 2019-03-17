//
//  RoleAttributeList.cpp
//  beymac
//
//  Created by wang on 15/4/27.
//
//

#include "RoleAttributeList.h"
#include "CommonData.h"

static std::map<int,RoleAttribute> mapAttributes;

std::map<int,RoleAttribute> RoleAttributeList::getCurAttributes()
{
    int bLevel = CommonData::getInstance()->getRoleLevel(1);
    int lLevel = CommonData::getInstance()->getRoleLevel(2);
    int tLevel = CommonData::getInstance()->getRoleLevel(3);
    
    // 大白
    float speed = 5;
    float attack = 1;
    
    switch (bLevel) {
        case 1:
            
            break;
        case 2:
            break;
        case 3:
 
            break;
        case 4:

            break;
        case 5:

            break;
        default:
            break;
    }
    mapAttributes[0].speed = speed;
    mapAttributes[0].attack = attack;
    
    // 激光
    speed = 5;
    attack = 1;
    
    switch (lLevel) {
        case 1:
            attack = attack * (1+0.5);
            break;
        case 2:
            
            attack = attack * (1+0.8);
            break;
        case 3:
            
            attack = attack * (1+1.1);
            break;
        case 4:
            
            attack = attack * (1+1.5);
            break;
        case 5:
            attack = attack * (1+1.5);
            break;
        default:
            break;
    }
    mapAttributes[1].speed = speed;
    mapAttributes[1].attack = attack;
    
    // 神行姐
    speed = 5;
    attack = 1;

    switch (tLevel) {
        case 1:
            speed = speed * (1+0.3);
            break;
        case 2:
            
            speed = speed * (1+0.6);
            break;
        case 3:
            
            speed = speed * (1+0.9);
            break;
        case 4:
            
            speed = speed * (1+1.2);
            break;
        case 5:
            speed = speed * (1+1.2);
            break;
        default:
            break;
    }
    mapAttributes[2].speed = speed;
    mapAttributes[2].attack = attack;
    
    return mapAttributes;
}