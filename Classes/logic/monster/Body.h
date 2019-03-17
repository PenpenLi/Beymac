//
//  Hitable.h
//  beymac
//
//  Created by je on 5/25/15.
//
//

#ifndef __beymac__Body__
#define __beymac__Body__


class Body{
public:
    
    virtual Point getPosition()=0;
    
    virtual void hit(float damage,bool trueDamage=false)=0;
    
    //范围攻击
    virtual void hit(Vec2 pos1,Vec2 pos2,float damage,bool trueDamage=false)=0;
    
};




#endif /* defined(__beymac__Body__) */
