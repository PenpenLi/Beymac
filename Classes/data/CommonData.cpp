//
//  CommonData.cpp
//  WaterWars
//
//  Created by je on 3/24/15.
//
//  全局公用数据本地持久化对象

#include "CommonData.h"
#include "cocos2d.h"
#include <string>
#include "MMLocalizedString.h"

USING_NS_CC;
using namespace std;

static CommonData *cmData=0;

//单例
CommonData *CommonData::getInstance()
{
    if(!cmData){
        cmData=new CommonData();
    }
    return cmData;
}

/////////////////////基本实现////////////////////////以下////

//存值,整型key
void CommonData::put(const int key,const int value)
{
    string strKey;
    strKey=StringUtils::format("%d",key);
    UserDefault::getInstance()->setIntegerForKey(strKey.data(), value);
}

//取值,整型key,空返回0
int CommonData::get(const int key)
{
    string strKey=StringUtils::format("%d",key);
    return UserDefault::getInstance()->getIntegerForKey(strKey.data(),0);//空值返回0
}

//存值,字符串key
void CommonData::put(std::string key,const int value)
{
    UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
}

//取值,字符串key,空返回0
int CommonData::get(std::string key)
{
    return UserDefault::getInstance()->getIntegerForKey(key.c_str(),0);
}

/////////////////////基本实现////////////////////////以上////



/////////////////////扩展//////////////////////////////////

//是否新手
bool CommonData::isNewPlayer()
{
    bool notNew=UserDefault::getInstance()->getBoolForKey("notNew",false);
    return !notNew;
}

//移除新手状态
void CommonData::removeNewPlayer()
{
    UserDefault::getInstance()->setBoolForKey("notNew", true);
}



////获取金币数量
int CommonData::getGold()
{
    return this->get("gold");
}
//
////金币增减,负数为减
void CommonData::addGold(int count)
{
    log("金币数量：%d+%d",getGold(),count);
    this->put("gold", getGold()+count);
}

//设置无尽模式层数
int CommonData::setEndlessFloor(const int count)
{
    this->put("levelCount", count);
    return getEndlessFloor();
}

//获取无尽模式层数
int CommonData::getEndlessFloor()
{
    return this->get("levelCount");
}

//设置水滴血量
void CommonData::setHealth(const int health)
{
    this->put("health", health);
}

//获取水滴血量
int CommonData::getHealth()
{
    return this->get("health");
}

//是否播放过帮助
bool CommonData::isPlayedHelp()
{
    if(this->get("playedHelp")==0){
        return false;
    }
    return true;
}

//设置已播放过帮助
void CommonData::setPlayedHelp()
{
    this->put("playedHelp", 1);
}

//获取语言类型：0 中文 1 英文
int CommonData::getLanguage()
{
    int i = UserDefault::getInstance()->getIntegerForKey(SELECTLANGUAGE,-1);
    
    if (i == -1) {
        LanguageType curLanguage = Application::getInstance()->getCurrentLanguage();
        switch (curLanguage) {
            case LanguageType::CHINESE:
                CommonData::getInstance()->setLanguage(0);
                i = 0;
                break;
            default:
                CommonData::getInstance()->setLanguage(1);
                i = 1;
                break;
        }
    }
    
    return 0;
}

void CommonData::setLanguage(int flag)
{
    UserDefault::getInstance()->setIntegerForKey(SELECTLANGUAGE, flag);
    purgeCCLocalizedStringCached();
}

bool CommonData::IsShareSendGold() {
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%j",localtime(&t));
    log("%s",UserDefault::getInstance()->getStringForKey("date").c_str());
    log("%s",tmp);
    if (strcmp(UserDefault::getInstance()->getStringForKey("date").c_str(), tmp) == 0) {
        int count = UserDefault::getInstance()->getIntegerForKey("shareCount");
        if (count<3) {
            UserDefault::getInstance()->setIntegerForKey("shareCount", count+1);
        } else {
            return false;
        }
    } else {
        UserDefault::getInstance()->setStringForKey("date", tmp);
        UserDefault::getInstance()->setIntegerForKey("shareCount", 0);
    }
    
    return true;
}

//设置角色等级，(1.大白，2.激光，3.神行姐)
void CommonData::setRoleLevel(int roleNo,int level)
{
    std::string role="roleLevel";
    role.append(StringUtils::format("%d",roleNo));
    this->put(role, level);
}

//获取角色等级
int CommonData::getRoleLevel(int roleNo)
{
    std::string role="roleLevel";
    role.append(StringUtils::format("%d",roleNo));
    if(roleNo==1&&this->get(role)==0){
        return 1;
    }
    return this->get(role.c_str());
}


//设置角色技能等级，(编号:1-8)
void CommonData::setRoleSkillLevel(int roleSkillNo,int level)
{
    std::string roleSkill="roleSkill";
    roleSkill.append(StringUtils::format("%d",roleSkillNo));
    this->put(roleSkill, level);
}

//获取角色技能等级
int CommonData::getRoleSkillLevel(int roleSkillNo)
{
    std::string roleSkill="roleSkill";
    roleSkill.append(StringUtils::format("%d",roleSkillNo));
    
    if (roleSkillNo == 1) {
        // 金钟罩默认为1级
        if (this->get(roleSkill) == 0) {
            this->put(roleSkill, 1);
        }
    }
    
    if (this->get(roleSkill) == 0) {
        return 0;
    }
    
    return this->get(roleSkill);
}


//设置关卡技能,checkpoint为关卡号，number为第几个技能,skill为技能编号
void CommonData::setCheckpointSkill(int number,int skill)
{
    auto str=StringUtils::format("cps%d",number);
//    log("设置关卡%d技能%s",number,str);
    this->put(str, skill);
}

//获取关卡技能
int CommonData::getCheckpointSkill(int number)
{
    auto str=StringUtils::format("cps%d",number);
//    log("获取关卡:%d 技能:%s, %d",number,str,this->get(str));

    if (this->get(str) == 5) {
        return 6;
    }
    return this->get(str);
}


//角色排序——设置指定位置的角色编号(position:第几位[从1开始]，roleNo:[1.大白，2.激光，3.神行姐])
void CommonData::setRoleToPosition(const int position,const int roleNo)
{
    std::string pos=StringUtils::format("rolePosition%d",position);
    this->put(pos, roleNo);
}

//角色排序——获取指定位置的角色编号
int CommonData::getRoleByPosition(const int position)
{
    std::string pos=StringUtils::format("rolePosition%d",position);
    int roleNo=this->get(pos);
    if(roleNo==0){
        switch (position) {
            case 1:
                roleNo=1;
                break;
            case 2:
                roleNo=3;
                break;
            case 3:
                roleNo=2;
                break;
            default:
                break;
        }
    }
    return roleNo;
}

//获取金币数量
int CommonData::getCrystal()
{
    return this->get("crystal");
}

//金币增减，负数为减
void CommonData::addCrystal(int count)
{
    this->put("crystal",getCrystal()+count);
}

//获取能量数量
int CommonData::getEnergy()
{
    return this->get("energy");
}

//能量增减,负数为减
void CommonData::addEnergy(int count)
{
    this->put("energy", getEnergy()+count);
}

int CommonData::getDoorNumber() {
    return UserDefault::getInstance()->getIntegerForKey("door");
}

void CommonData::addDoorNumber(int count)
{
    this->put("door", getDoorNumber()+count);
}

void CommonData::setDoorNumber(int num) {
    if(num < 0) {
        num = 0;
    }
    this->put("door", num);
}


//获取昵称
string CommonData::getNickname()
{
    string str=UserDefault::getInstance()->getStringForKey("nkname");
    
    return str;
}
//设置昵称
void CommonData::setNickname(std::string name)
{
    UserDefault::getInstance()->setStringForKey("nkname", name);
}
