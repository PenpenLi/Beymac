//
//  Manage.cpp
//  WaterWars
//
//  Created by lingzerg on 15/3/11.
//
//

#include "Manager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSHelper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "AndroidHelper.h"
#endif

Manager *Manager::manager = NULL;

Manager *Manager::getInstance()
{
    if (!manager) {
        manager = Manager::create();
        manager->retain();
    }
    return manager;
}

bool Manager::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    return true;
}

bool Manager::isNetworkConnected() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOSHelper::checkNetworkConnectedInIOS();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return isNetworkConnectedInAndroid();
#endif
}

bool Manager::isQQInstalled() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOSHelper::isQQInstalledIOS();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return true;
#endif
    return false;
}

void Manager::shareQQ() {
    log("分享......");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOSHelper::sendNewsMessageWithNetworkImage();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendNewsMessageWithNetworkImage();
#endif
}

std::string Manager::getImei() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOSHelper::getIMEI();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return getImeiForAndroid();
#endif
}

void Manager::playBackgroundMusic(const char* file) {
    if (getIsSound()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    }
}

void Manager::resumeBackgroundMusic() {
    
    if (getIsSound()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}

void Manager::pauseBackgroundMusic() {
    if (getIsSound()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}


void Manager::playSoundEffect(const char* file)
{
    if (getIsSound()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file);
    }
}

