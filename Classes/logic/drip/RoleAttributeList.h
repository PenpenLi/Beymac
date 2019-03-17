//
//  RoleAttributeList.h
//  beymac
//
//  Created by wang on 15/4/27.
//
//

#ifndef __beymac__RoleAttributeList__
#define __beymac__RoleAttributeList__

#include "cocos2d.h"

using namespace std;

class RoleAttribute
{
public:
    float speed;
    float attack;
};

class RoleAttributeList
{
public:
    // type 1.大白，2.激光，3.神行姐
    static map<int,RoleAttribute> getCurAttributes();


};

#endif /* defined(__beymac__RoleAttributeList__) */
