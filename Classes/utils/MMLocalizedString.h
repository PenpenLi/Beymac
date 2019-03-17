
#ifndef _CCLocalizedString_h
#define _CCLocalizedString_h

//语言文本工具
//文本的资源文件内lang/Localized_en，lang/Localized_zh

/**get the localized string by the key, if can't get the value then return mComment
 support for file name below:
 "Localized_en";//english
 "Localized_zh";//chinese
 "Localized_fr";//french
 "Localized_it";//italian
 "Localized_ge";//german
 "Localized_sp";//spanish
 "Localized_ru";//russian
 "Localized_ko";//korean
 "Localized_jp";//japanese
 "Localized_hu";//hungarian
 */

#define LSTRING(key) MMLocalizedString(key)
#define LSTRINGIMAGE(key) MMImageNameLink(key)
#define LSTRINGLEVELINFO(key) MMLocalizedStringLevelInfo(key)

//通过key获取文本内容
const char * MMLocalizedString(const char * mKey);
//读取关卡信息
const char * MMLocalizedStringLevelInfo(const char * mKey);
// 拼接字符
const char * MMImageNameLink(const char * mKey, bool flag = true);

/**purge localize string cached
 */
void purgeCCLocalizedStringCached();
void purgeCCLocalizedStringLevelInfoCached();

#endif
