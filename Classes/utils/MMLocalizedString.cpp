
#include "cocos2d.h"
#include "CommonData.h"
USING_NS_CC;

#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#include "MMLocalizedString.h"

#define kLocalizedEnglishPath "Localized_en"
#define kLocalizedChinesePath "Localized_zh"
#define kLocalizedLevelInfoPath "LevelInfoText"

static map<std::string,std::string> localizedStrings;
static map<std::string,std::string> localizedStringsLevelInfo;

void purgeCCLocalizedStringCached()
{
    localizedStrings.clear();
}

void purgeCCLocalizedStringLevelInfoCached()
{
    localizedStringsLevelInfo.clear();
}

const char * MMLocalizedString(const char * mKey)
{
    const char * fileName;
    
    int i = CommonData::getInstance()->getLanguage();
    switch (i) {
        case 0:
            fileName = kLocalizedChinesePath;
            break;
        default:
            fileName = kLocalizedEnglishPath;
            break;
    }
    

    std::string resultStr;
    
    if (localizedStrings.empty())
    {
        // Initialize variables needed
        ssize_t fileSize = 0;
        unsigned char * fileContents = NULL;
        string line, fullPath, contents;
        
        fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
        
        fileContents = FileUtils::getInstance()->getFileData( fullPath.c_str( ) , "rb", &fileSize );
        contents.assign(fileContents,fileContents+fileSize-1);
        
        // Create a string stream so that we can use getline( ) on it
        istringstream fileStringStream( contents );
        
        // Get file contents line by line
        while ( std::getline( fileStringStream, line ) )
		{
//            debug_Printf("line :%s",line.c_str());
            if (line.find("/*",0) == string::npos && line.find("//",0) == string::npos) //filter the valid string of one line
            {
//                debug_Printf("find the line not start with \" /* \"");
                std::string::size_type validPos= line.find('=',0);
                if ( validPos != string::npos) 
                {
//                    debug_Printf("fimd the line contain \" = \"");
                    std::string keyStr = line.substr(0,validPos);
                    std::string subStr = line.substr(validPos+1,line.size()-1); // get valid string
 
                    //trim space
                    keyStr.erase(0, keyStr.find_first_not_of(" \t")); // 去掉头部空格
                    keyStr.erase(keyStr.find_last_not_of(" \t") + 1); // 去掉尾部空格
                    
                    subStr.erase(0, subStr.find_first_not_of(" \t")); // 去掉头部空格
                    subStr.erase(subStr.find_last_not_of(" \t") + 1); // 去掉尾部空格
                    
                    //trim \" 
                    keyStr.erase(0, keyStr.find_first_not_of("\""));
                    keyStr.erase(keyStr.find_last_not_of("\"") + 1);
                    
                    subStr.erase(0, subStr.find_first_not_of("\""));
                    
                    
                    //trim ; character and last \" character
                    subStr.erase(subStr.find_last_not_of(";") + 1);
                    subStr.erase(subStr.find_last_not_of("\"") + 1);
                    
                    
                    //replace line feed with \n
                    string::size_type pos(0);
                    string old_value("\\n");
                    if((pos=subStr.find(old_value))!=string::npos)
                    {
                        for(; pos!=string::npos; pos+=1)
                        {   
                            if((pos=subStr.find(old_value,pos))!=string::npos)
                            {
                                subStr.erase(pos, 2);
                                subStr.insert(pos, 1, '\n');
                            }   
                            else   
                                break;
                        }
                    }
                    
					//replace line feed with \r
                    old_value = "\"";
                    if((pos=subStr.find(old_value))!=string::npos)
                    {
                        for(; pos!=string::npos; pos+=1)
                        {   
                            if((pos=subStr.find(old_value,pos))!=string::npos)
                            {
                                subStr.erase(pos, 2);
                            }   
                            else   
                                break;
                        }
                    }

                    localizedStrings.insert(std::pair<std::string, std::string>(keyStr,subStr));
                    
                    const char * keyChars = keyStr.c_str();
                    
                    if (strcmp(keyChars,mKey) == 0) {
                        resultStr = subStr;
                    }
                }
            }
        }
        //must delete fileContents
        if (fileContents!= NULL) {
            delete [] fileContents;
            fileContents = NULL;
        }
        
        //return valid value
        if (resultStr.length() > 0){
            return (string(resultStr)).c_str();
        }
        return mKey;
    }
    else
    {
        std::map<std::string,std::string>::iterator itr = localizedStrings.find(std::string(mKey));
        if (itr != localizedStrings.end()) {
            resultStr = itr->second;
            if (resultStr.length() > 0)
            {
                return (itr->second).c_str();
            }
        }
    }
    return mKey;
}

const char * MMLocalizedStringLevelInfo(const char * mKey)
{
    const char * fileName = kLocalizedLevelInfoPath;;
    
    std::string resultStr;
    
    if (localizedStringsLevelInfo.empty())
    {
        // Initialize variables needed
        ssize_t fileSize = 0;
        unsigned char * fileContents = NULL;
        string line, fullPath, contents;
        
        fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
        
        fileContents = FileUtils::getInstance()->getFileData( fullPath.c_str( ) , "rb", &fileSize );
        contents.assign(fileContents,fileContents+fileSize-1);
        
        // Create a string stream so that we can use getline( ) on it
        istringstream fileStringStream( contents );
        
        // Get file contents line by line
        while ( std::getline( fileStringStream, line ) )
        {
            //            debug_Printf("line :%s",line.c_str());
            if (line.find("/*",0) == string::npos && line.find("//",0) == string::npos) //filter the valid string of one line
            {
                //                debug_Printf("find the line not start with \" /* \"");
                std::string::size_type validPos= line.find('=',0);
                if ( validPos != string::npos)
                {
                    //                    debug_Printf("fimd the line contain \" = \"");
                    std::string keyStr = line.substr(0,validPos);
                    std::string subStr = line.substr(validPos+1,line.size()-1); // get valid string
                    
                    //trim space
                    keyStr.erase(0, keyStr.find_first_not_of(" \t")); // 去掉头部空格
                    keyStr.erase(keyStr.find_last_not_of(" \t") + 1); // 去掉尾部空格
                    
                    subStr.erase(0, subStr.find_first_not_of(" \t")); // 去掉头部空格
                    subStr.erase(subStr.find_last_not_of(" \t") + 1); // 去掉尾部空格
                    
                    //trim \"
                    keyStr.erase(0, keyStr.find_first_not_of("\""));
                    keyStr.erase(keyStr.find_last_not_of("\"") + 1);
                    
                    subStr.erase(0, subStr.find_first_not_of("\""));
                    
                    
                    //trim ; character and last \" character
                    subStr.erase(subStr.find_last_not_of(";") + 1);
                    subStr.erase(subStr.find_last_not_of("\"") + 1);
                    
                    
                    //replace line feed with \n
                    string::size_type pos(0);
                    string old_value("\\n");
                    if((pos=subStr.find(old_value))!=string::npos)
                    {
                        for(; pos!=string::npos; pos+=1)
                        {
                            if((pos=subStr.find(old_value,pos))!=string::npos)
                            {
                                subStr.erase(pos, 2);
                                subStr.insert(pos, 1, '\n');
                            }
                            else
                                break;
                        }
                    }
                    
                    //replace line feed with \r
                    old_value = "\"";
                    if((pos=subStr.find(old_value))!=string::npos)
                    {
                        for(; pos!=string::npos; pos+=1)
                        {
                            if((pos=subStr.find(old_value,pos))!=string::npos)
                            {
                                subStr.erase(pos, 2);
                            }
                            else
                                break;
                        }
                    }
                    
                    localizedStringsLevelInfo.insert(std::pair<std::string, std::string>(keyStr,subStr));
                    
                    const char * keyChars = keyStr.c_str();
                    
                    if (strcmp(keyChars,mKey) == 0) {
                        resultStr = subStr;
                    }
                }
            }
        }
        //must delete fileContents
        if (fileContents!= NULL) {
            delete [] fileContents;
            fileContents = NULL;
        }
        
        //return valid value
        if (resultStr.length() > 0){
            return (string(resultStr)).c_str();
        }
        return "";
    }
    else
    {
        std::map<std::string,std::string>::iterator itr = localizedStringsLevelInfo.find(std::string(mKey));
        if (itr != localizedStringsLevelInfo.end()) {
            resultStr = itr->second;
            if (resultStr.length() > 0)
            {
                return (itr->second).c_str();
            }
        }
    }
    return "";
}

// 拼接字符
const char * MMImageNameLink(const char * mKey, bool flag /*= true*/)
{
    if(flag)
    {
        int i = CommonData::getInstance()->getLanguage();
        switch (i) {
            case 0:
                mKey = __String::createWithFormat("%s.png", mKey)->getCString();
                break;
            default:
                mKey = __String::createWithFormat("%s_en.png", mKey)->getCString();
                break;
        }
    }
    else
    {
        int i = CommonData::getInstance()->getLanguage();
        switch (i) {
            case 0:
                mKey = __String::createWithFormat("%s.jpg", mKey)->getCString();
                break;
            default:
                mKey = __String::createWithFormat("%s_en.jpg", mKey)->getCString();
                break;
        }
    }
    
    return mKey;
}