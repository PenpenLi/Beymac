#include "AppDelegate.h"
#include "Macro.h"
#include "HomeScene.h"
#include "Cutscenes.h"
#include "IOSHelper.h"
#include "AndroidHelper.h"
#include "MonsterTestScene.h"
#include "StartGameTextScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate() 
{
    
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

//     create a scene. it's an autorelease object
//    auto scene = PlayScene::createScene();
    
    
    
    
    //播放背景音乐——要在创建场景之前
    Manager::getInstance()->setIsSound(true);
    Manager::getInstance()->playBackgroundMusic("sceneBGM.mp3");
    
    Scene *scene;
    
    //判断是否第一次打开游戏
    int firstEnter=0;
    firstEnter= CommonData::getInstance()->get("firstEnter");
    if(firstEnter==0){
        scene = StartGameTextScene::createScene();
        CommonData::getInstance()->put("firstEnter", 1);
    }else{
        scene= HomeScene::create();
    }
    
    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}