//
//  Payment.h
//  BeyMac
//
//  Created by lingzerg on 15/6/8.
//
//

#ifndef __BeyMac__Payment__
#define __BeyMac__Payment__

#define CRYSTAL1 1//1 crystal1   cn.pingames.beymac.crystal1
#define CRYSTAL2 2//2 crystal2   cn.pingames.beymac.crystal2
#define CRYSTAL3 3//3 crystal3   cn.pingames.beymac.crystal3

#define GIFT 4//4 gift   cn.pingames.beymac.gift

#define MYSTERYSHOP1 5//5 mysteryshop1   cn.pingame…ymac.mysteryshop1
#define MYSTERYSHOP2 6//6 mysteryshop2   cn.pingame…ymac.mysteryshop2

#define PHOENIX 7//7 phoenix   cn.pingames.phoenix
#define POWER1 8//8 power1   cn.pingames.beymac.power1
#define POWER2 9//9 power2   cn.pingames.beymac.power2
#define POWER3 10//10 power3   cn.pingames.beymac.power3

#define ROLEFULLLEVEL 11//11 rolefulllevel   cn.pingame…mac.rolefulllevel
#define SKILLFULLEVEL 12//12 skillfulllevel   cn.pingame…ac.skillfulllevel
#define UNLOCKLEVEL 13//13 unlocklevel   cn.pingame…eymac.unlocklevel
#define UNLOCKROLE 14//14 unlockrole   cn.pingame…beymac.unlockrole
#define UNLOCKSKILL 15//15 unlockskill   cn.pingame…eymac.unlockskill




class PaymentDelegate {
    
public:
    virtual void payResult(bool result) = 0;
};

namespace Payment {
    void pay(int type);
    void pay(int type,PaymentDelegate *delegate);
}

#endif /* defined(__BeyMac__Payment__) */


