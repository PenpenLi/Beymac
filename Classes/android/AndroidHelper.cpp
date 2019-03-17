//
//  AndroidHelper.cpp
//  WaterWars
//
//  Created by lingzerg on 15/4/13.
//
//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "cocos2d.h"
#include "AndroidHelper.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "cn/pingames/beymac/MainActivity"

using namespace cocos2d;

std::string imeiGot;


extern "C" {
    void sendNewsMessageWithNetworkImage() {        
        log("cocos2dx sendNewsMessageWithNetworkImage");
        
        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sendNewsMessageWithNetworkImage", "()V"))
        {
            log("jni:此函数存在");
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }else{
            log("jni:此函数不存在");
        }
    }
    
    
    //判断是否有网络
    bool isNetworkConnectedInAndroid(){
        log("获取网络状态");
        
        JniMethodInfo minfo;
        bool isHave = JniHelper::getStaticMethodInfo(minfo,"cn.pingames.beymac.MainActivity", "isNetworkConnected", "()I");
        
        if (!isHave) {
            log("jni:此函数不存在");
        }else{
            log("jni:此函数存在");
            //调用此函数
            jint rec=minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
            
            int ret=(int)rec;
            
            if(ret==1){
                return true;
            }else{
                return false;
            }
        }
        return false;
    }
    
    
    
    //退出cocos时通知android
    void noticeAndroidToExit(){
        JniMethodInfo minfo;
        
        bool isHave = JniHelper::getStaticMethodInfo(minfo,"cn.pingames.beymac.MainActivity","onCocosExit", "()V");
        
        if (!isHave) {
            log("jni:此函数不存在");
        }else{
            log("jni:此函数存在");
            //调用此函数
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
        log("jni-java函数执行完毕");
        
        
    }
    
    
    
    
    std::string getImeiForAndroid() {
        log("获取imei,call getImeiForAndroid");
        if(!imeiGot.empty()){
            log("imeigot2 :%s",imeiGot.c_str());
            return imeiGot;
        }
        
        JniMethodInfo minfo;
        //        bool isHave = JniHelper::getMethodInfo(minfo,"cn.pingames.beymac.MainActivity", "getIMEI", "()V");
        bool isHave = JniHelper::getStaticMethodInfo(minfo,"cn.pingames.beymac.MainActivity", "getIMEI", "()Ljava/lang/String;");
        
        if (!isHave) {
            log("jni:此函数不存在");
        }else{
            log("jni:此函数存在");
            //调用此函数
//            jstring msg=(jstring)minfo.env->CallVoidMethod(minfo.classID, minfo.methodID);
            jstring msg=(jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            
            const char *str = minfo.env->GetStringUTFChars(msg,0);
            
            log("直接返回imei:%s",str);
            
            imeiGot.append(str);
            return imeiGot;
        }
    }
    
//    JNIEXPORT void JNICALL Java_cn_pingames_beymac_MainActivity_sendIMEI(JNIEnv* env, jclass thiz, jstring imei)
//    {
//        log("sendImei");
//        const char *i = env->GetStringUTFChars(imei, NULL);
//        log("god imei:%s",i);
//        
//        imeiGot.append(i);
//        log("imeigot1 :%s",imeiGot.c_str());
//        log("hi");
//    }
    
    
    
    
}


#endif
