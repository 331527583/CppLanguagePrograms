#include "NetUtil.h"
#include <stdlib.h>
#include <string.h>
NAMESPACE_ZL_NET_START

bool NetUtil::isBroadcastAddress(const char *str)
{
    return (NULL == str) ? false : (0 == strcmp(str, "255.255.255.255"));
}

bool NetUtil::isValidIp(const char *str)
{
    return isValidIpv4(str) || isValidIpv6(str);
}

bool NetUtil::isValidIpv4(const char *str)
{
    if((NULL == str) || (0 == str[0]) || ('0' == str[0])) return false;
    if(0 == strcmp(str, "*")) return true;
    if(0 == strcmp(str, "255.255.255.255")) return false;

    int dot = 0; // .�ĸ���
    const char *strp = str;
	int num = 0; //����ÿһ����'.'�ֿ����ַ�����ֵ
    while(*strp)
    {
        if('.' == *strp)
		{
            ++dot;
			num = 0;
		}
        else if((*strp < '0') || (*strp > '9'))
        {
			return false;
		}
		else
		{
			num *= 10;
			num += (*strp - '0');
			if(num > 255)
				return false;
		}
        ++strp;
    }

    return (3 == dot);  // .�ĸ�������Ϊ3
}

bool NetUtil::isValidIpv6(const char *str)
{
    const char *pos = strchr(str, ':');
    if(NULL == pos) return false;
    return strchr(pos, ':') != NULL;
}

bool NetUtil::isLittleEndian()
{
    //Little-endianģʽ��CPU�Բ������Ĵ�ŷ�ʽ�Ǵӵ��ֽڵ����ֽڣ���Big-endianģʽ�Բ������Ĵ�ŷ�ʽ�ǴӸ��ֽڵ����ֽڡ�
    //[��С�˴洢����]: С�˷�ʽ�У�iռ���������ֽڵĳ��ȣ�,i��������ڴ���С��ַ�Ǹ��ֽ��оʹ���1�������ֽ���0.
    //��˵Ļ���1��i����ߵ�ַ�ֽڴ���ţ�char��һ���ֽڣ�����ǿ�ƽ�char����pָ��i��pָ���һ����i����͵�ַ��
    //��ô�Ϳ����ж�p�е�ֵ�ǲ���1��ȷ���ǲ���С�ˡ�
    //����������Big_endian�ģ��򷵻�0������Little_endian�ģ��򷵻�1

    //������union�Ĵ��˳�������г�Ա���ӵ͵�ַ��ʼ���
    union w
    {
        int i;
        char c;
    } u;
    u.i = 1;

    return (u.c == 1);

    //int i = 0x1;
    //return *(char *)&i == 0x1;  // this is ok
}

void NetUtil::reverseBytes(const void *source, void *result, size_t length)
{
    char *source_begin = (char *)source;
    char *result_end = ((char *)result) + length;

    for(size_t i = 0; i < length; ++i)
        *(--result_end) = source_begin[i];
}

void NetUtil::host2Net(const void *source, void *result, size_t length)
{
    if(isLittleEndian())   //ֻ��С�ֽ������Ҫת�������ֽ���������ֽ�����һ�µ�
        reverseBytes(source, result, length);
}

void NetUtil::net2Host(const void *source, void *result, size_t length)
{
    host2Net(source, result, length);
}

NAMESPACE_ZL_NET_END