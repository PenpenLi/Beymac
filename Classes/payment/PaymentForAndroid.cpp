//
//  PaymentForAndroid.cpp
//  WaterWars
//
//  Created by je on 4/8/15.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>


#include "PaymentForAndroid.h"
#include "PaymentForAndroidDelegateRegister.h"

USING_NS_CC;


void PaymentForAndroid::pay(int itemId, PaymentDelegate *delegate)
{
    int delegateId=0;   //委托编号
    
    //委托不传给android，暂留在出口处。
    if(delegate){
        delegateId=PaymentForAndroidDelegateRegister::add(delegate);
    }
    
	JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cn.pingames.beymac.MainActivity","pay", "(II)V");
    
    if (!isHave) {
        log("jni:函数不存在");
    }else{
    	log("jni:函数存在");
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,itemId,delegateId);
        log("jni-java函数执行完毕");
    }

}


#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Class:     cn_pingames_waterwars_MainActivity
     * Method:    paySucceed
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_cn_pingames_beymac_MainActivity_paySucceed(JNIEnv *env, jclass b, jint result, jint c, jint delegateId)
    {
        log("回到cpp,开始取出委托");
        auto delegate=PaymentForAndroidDelegateRegister::get(delegateId);
        if(delegate){
            log("取出委托，开始执行");
            //委托在此执行
            if(result==1){
                log("支付成功");
                delegate->payResult(true);
            }else{
                log("支付失败");
                delegate->payResult(false);
            }
        }else{
            log("委托为空，结束");
        }
    }
    
#ifdef __cplusplus
}
#endif


#endif
