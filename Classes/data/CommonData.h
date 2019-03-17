//
//  CommonData.h
//  WaterWars
//
//  Created by je on 3/24/15.
//
//此类主要封装掉int型数据作为key的时候,string和int的转换过程
//如果重复插入，则不提示直接覆盖



#ifndef __beymac__CommonData__
#define __beymac__CommonData__

#include "cocos2d.h"

#define SELECTLANGUAGE "selectLangage"

class CommonData {
public:
    //单例
    static CommonData *getInstance();
    
    //存值,整型key
    void put(const int key,const int value);
    
    //取值,整型key,空返回0
    int get(const int key);
    
    //存值,字符串key
    void put(std::string key,const int value);
    
    //取值,字符串key,空返回0
    int get(std::string key);
    
    //是否新手
    bool isNewPlayer();
    
    //移除新手状态
    void removeNewPlayer();
    
    //获取金币数量
    int getGold();
    
    //金币增减,负数为减
    void addGold(int count);
    
    //设置无尽模式层数
    int setEndlessFloor(const int count);
    
    //获取无尽模式层数
    int getEndlessFloor();
    
    //设置水滴血量
    void setHealth(const int health);
    
    //获取水滴血量
    int getHealth();
    
    //是否播放过帮助
    bool isPlayedHelp();
    
    //设置已播放过帮助
    void setPlayedHelp();
    
    //获取语言类型：0 中文 1 英文及其他
    int getLanguage();
    void setLanguage(int flag);
    
    bool IsShareSendGold();
    
    //设置角色等级，(1.大白，2.激光，3.神行姐)
    void setRoleLevel(int roleNo,int level);
    
    //获取角色等级
    int getRoleLevel(int roleNo);
    
    //设置角色技能等级，(编号:1-8)
    void setRoleSkillLevel(int roleSkillNo,int level);
    
    //获取角色技能等级
    int getRoleSkillLevel(int roleSkillNo);
    
    //设置关卡技能，number为第几个技能,skill为技能编号
    void setCheckpointSkill(int number,int skill);
    
    //获取关卡技能
    int getCheckpointSkill(int number);
    
    //获取晶核数量
    int getCrystal();
    
    //晶核增减，负数为减
    void addCrystal(int count);
    
    //角色排序——设置指定位置的角色编号(position:第几位[从1开始]，roleNo:[1.大白，2.激光，3.神行姐])
    void setRoleToPosition(const int position,const int roleNo);
    
    //角色排序——获取指定位置的角色编号
    int getRoleByPosition(const int position);

    //获取能量数量
    int getEnergy();
    //能量增减,负数为减
    void addEnergy(int count);
    
    
    //传送门使用的次数, 达到次数触发冷却, 归零次数
    int getDoorNumber();
    void addDoorNumber(int count);
    void setDoorNumber(int num);
    //获取昵称
    std::string getNickname();
    //设置昵称
    void setNickname(std::string name);
};


#endif
