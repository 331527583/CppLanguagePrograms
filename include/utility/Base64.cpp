#include "utility/Base64.h"
#include <string.h>
NAMESPACE_ZL_BASE_START

static int base64EncodeImpl(const char *src, int len, std::string& dst);
static int base64DecodeImpl(const char *src, int len, std::string& dst);

static const char base_CODE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64Encode(const char *src, int len, char *dst)
{
    std::string dest;
    int size = base64EncodeImpl(src, len, dest);
    ::memcpy(dst, dest.c_str(), size);
    return size;
}

int base64Encode(const char *src, int len, std::string& dst)
{
    return base64EncodeImpl(src, len, dst);
}

int base64Encode(const std::string& src, std::string& dst)
{
    return base64EncodeImpl(src.data(), src.size(), dst);
}

int base64Decode(const char *src, size_t len, char *dst)
{
    std::string dest;
    int size = base64DecodeImpl(src, len, dest);
    ::memcpy(dst, dest.c_str(), size);
    return size;
}

int base64Decode(const char *src, int len, std::string& dst)
{
    return base64DecodeImpl(src, len, dst);
}

int base64Decode(const std::string& src, std::string& dst)
{
    return base64DecodeImpl(src.data(), src.size(), dst);
}


//������������
inline char GetCharIndex(char c)
{
    if((c >= 'A') && (c <= 'Z'))
        return c - 'A';
    else if((c >= 'a') && (c <= 'z'))
        return c - 'a' + 26;
    else if((c >= '0') && (c <= '9'))
        return c - '0' + 52;
    else if(c == '+')
        return 62;
    else if(c == '/')
        return 63;
    else if(c == '=')
        return 0;

    return 0;
}

static int base64EncodeImpl(const char *src, int len, std::string& dst)
{
    dst.resize(len * 2);
    int idx = 0, dstLen = 0;

    while(len > 0)
    {
        dst[idx++] = base_CODE[(src[0] >> 2) & 0x3F];	//������λ����00111111�Ƿ�ֹ������Լ�
        if(len > 2)	//��3���ַ�
        {
            dst[idx++] = base_CODE[((src[0] & 3) << 4) | (src[1] >> 4)];
            dst[idx++] = base_CODE[((src[1] & 0xF) << 2) | (src[2] >> 6)];
            dst[idx++] = base_CODE[src[2] & 0x3F];
        }
        else
        {
            switch(len)	//׷�ӡ�=��
            {
                case 1:
                    dst[idx++] = base_CODE[(src[0] & 3) << 4 ];
                    dst[idx++] = '=';
                    dst[idx++] = '=';
                    break;
                case 2:
                    dst[idx++] = base_CODE[((src[0] & 3) << 4) | (src[1] >> 4)];
                    dst[idx++] = base_CODE[((src[1] & 0x0F) << 2) | (src[2] >> 6)];
                    dst[idx++] = '=';
                    break;
            }
        }

        src += 3;
        len -= 3;
        dstLen += 4;
    }
    dst[idx++] = 0;
    return dstLen;
}

static int base64DecodeImpl(const char *src, int len, std::string& dst)
{
    int vLen = 0;
    if(len % 4)		//base64���볤�ȱض���4�ı���������'='
    {
        dst[0] = '\0';
        return -1;
    }

    dst.resize(len);
    int idx = 0;
    char lpCode[4];
    while(len > 2)		//���������ַ�������
    {
        lpCode[0] = GetCharIndex(src[0]);
        lpCode[1] = GetCharIndex(src[1]);
        lpCode[2] = GetCharIndex(src[2]);
        lpCode[3] = GetCharIndex(src[3]);

        dst[idx++] = (lpCode[0] << 2) | (lpCode[1] >> 4);
        dst[idx++] = (lpCode[1] << 4) | (lpCode[2] >> 2);
        dst[idx++] = (lpCode[2] << 6) | (lpCode[3]);

        src += 4;
        len -= 4;
        vLen += 3;
    }

    return vLen;
}

NAMESPACE_ZL_BASE_END