//
//  Health.h
//  WaterWars
//
//  Created by lingzerg on 15/3/18.
//
//

#ifndef __WaterWars__Health__
#define __WaterWars__Health__

#include "cocos2d.h"
USING_NS_CC;

class Health : public Sprite
{
public:
    Health();
    ~Health();
    //创建血条,使用图片
    static Health* createNode();
    
    static Health* createNode(const char *imageName,const char *background); //创建血条,使用自定义图片
    virtual bool init();
    bool init(const char *imageName,const char *background);
    void setValue(int value); //直接设置百分比
    
    void hideHealth();//隐藏血条
    void showHealth();//显示血条
    
    
    void setOriginHealth(float originHealth);//设置血槽血量
    void addHealth(float health); //修改血量,当前血量加上传入参数
    void setHealth(float currentHealth); //直接设置血量
    
    float getOriginHealth();//获取血槽长度
    float getHealth();//获取当前血量
    
private :
    ProgressTimer *mypro;
    float currentHealth;
    float originHealth;
    
private:
    void initData();
    void initData(const char *imageName,const char *background);
    void whitebar();
    void shadow();
    
};

#endif /* defined(__WaterWars__Health__) */