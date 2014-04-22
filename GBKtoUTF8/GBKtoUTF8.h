#ifndef GBK_TO_UNICODE_FILE_H
#define GBK_TO_UNICODE_FILE_H

#include <string>

/**����ַ����Ƿ���utf8����*/
bool IsTextUTF8(const char* str, int length);
bool IsTextUTF8(const std::string& str);

/**GBK��UTF-8�ı���ת��*/
std::string ConvertGBKToUtf8(const std::string& strGBK);
std::string ConvertUtf8ToGBK(const std::string& strUtf8);


#endif