#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <memory.h>
#include <assert.h>

#include "GBKtoUTF8.h"
#include "gbk2unicode.h"

using namespace std;

void GetText(bool isUtf8, std::vector<std::string>& vecStr)
{
	const char* filename = isUtf8 ? "utf8.txt" : "gbk.txt";
	std::ifstream ifs(filename);
	assert(!ifs.fail());

	while(!ifs.eof())
	{
		std::string str;
		ifs >> str;
		vecStr.push_back(str);
	}

	ifs.close();
}

/*****************************************************************************
* �ô������ԣ�http://blog.csdn.net/csfreebird/article/details/8571726
* ����ַ����Ķ����Ƹ�ʽ
****************************************************************************/

// Get the bit value specified by the index  
// index starts with 0  
template<class T>  
int Bit_Value(T value, int index) {  
	return (value & (1 << index)) == 0 ? 0 : 1;  
}  

// T must be one of integer type  
template<class T>  
string PrintIntAsBinaryString(T v) {  
	stringstream stream;  
	int i = sizeof(T) * 8 - 1;  
	while (i >= 0) {  
		stream << Bit_Value(v, i);  
		--i;  
	}  

	return stream.str();  
}  

/**�����ַ����Ķ����Ʊ�ʾ*/
string PrintStringAsBinaryString(const char* p) {  
	stringstream stream;  
	for (size_t i = 0; i < strlen(p); ++i) {  
		stream << PrintIntAsBinaryString(p[i]);  
		stream << " ";  
	}  
	return stream.str();  
}  

/**�����ַ����Ķ����Ʊ�ʾ*/
string PrintStringAsBinaryString(const string& str) {  
	stringstream stream;  
	for (size_t i = 0; i < str.size(); ++i) {  
		stream << PrintIntAsBinaryString(str[i]);  
		stream << " ";  
	}  
	return stream.str();  
}  

/*****************************************************************************
 * �ô������ԣ�http://blog.csdn.net/tge7618291/article/details/7608510
 * ��һ���ַ���Unicode(UCS-2��UCS-4)����ת����UTF-8����.
 *
 * ����:
 *    unic     �ַ���Unicode����ֵ
 *    pOutput  ָ����������ڴ洢UTF8����ֵ�Ļ�������ָ��
 *    outsize  pOutput����Ĵ�С
 *
 * ����ֵ:
 *    ����ת������ַ���UTF8������ռ���ֽ���, ��������򷵻� 0 .
 *
 * ע��:
 *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��;
 *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����;
 *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ)
 *     2. �뱣֤ pOutput �������������� 6 �ֽڵĿռ��С!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
        int outSize)
{
    assert(pOutput != NULL);
    assert(outSize >= 6);

    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }

    return 0;
}

/*****************************************************************************
 * ��һ���ַ���UTF8����ת����Unicode(UCS-2��UCS-4)����.
 *
 * ����:
 *    pInput      ָ�����뻺����, ��UTF-8����
 *    Unic        ָ�����������, �䱣������ݼ���Unicode����ֵ,
 *                ����Ϊunsigned long .
 *
 * ����ֵ:
 *    �ɹ��򷵻ظ��ַ���UTF8������ռ�õ��ֽ���; ʧ���򷵻�0.
 *
 * ע��:
 *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��;
 *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����;
 *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ)
 ****************************************************************************/
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    assert(pInput != NULL && Unic != NULL);

    // b1 ��ʾUTF-8�����pInput�еĸ��ֽ�, b2 ��ʾ�θ��ֽ�, ...
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // �� *Unic ��ʼ��Ϊȫ��
    int utfbytes  = 100;//= enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *) Unic;

    switch ( utfbytes )
    {
        case 0:
            *pOutput     = *pInput;
            utfbytes    += 1;
            break;
        case 2:
            b1 = *pInput;
            b2 = *(pInput + 1);
            if ( (b2 & 0xE0) != 0x80 )
                return 0;
            *pOutput     = (b1 << 6) + (b2 & 0x3F);
            *(pOutput+1) = (b1 >> 2) & 0x07;
            break;
        case 3:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b2 << 6) + (b3 & 0x3F);
            *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
            break;
        case 4:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b3 << 6) + (b4 & 0x3F);
            *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
            *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
            break;
        case 5:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            b5 = *(pInput + 4);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b4 << 6) + (b5 & 0x3F);
            *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
            *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
            *(pOutput+3) = (b1 << 6);
            break;
        case 6:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            b5 = *(pInput + 4);
            b6 = *(pInput + 5);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                    || ((b6 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b5 << 6) + (b6 & 0x3F);
            *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
            *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
            *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
            break;
        default:
            return 0;
            break;
    }

    return utfbytes;
}

void test_gbbk_utf_unicode()
{
	char const * p = "һ��";
	std::cout<<PrintStringAsBinaryString(p)<<"\n";
	std::cout<<PrintStringAsBinaryString("λ")<<"\n";

	//��bgbk���ո�ֿ���ÿ����������ʾ��һ���ַ��Ķ����Ʊ��룬ת��int���ͺ�ͨ��gbk2unicode���ã��õ����ַ���unicode���룬Ȼ��ͨ��enc_unicode_to_utf8_oneתΪutf-8

	//һ�Ķ����Ʊ�ʾ��11010010 10111011��D2BB��210-187����ͨ��gbk2unicodeת��Ϊunicode��4E00��Ȼ��ͨ��enc_unicode_to_utf8_oneתΪutf-8
	cout << std::hex<<gbk2unicode(210,187) <<"\n";
	cout << std::hex<<gbk2unicode(182,254) <<"\n";
	unsigned long one = 0x4E8C; //0xD2BB;//0x4E00;
	unsigned char pOutput[32]; //utf-8���4�ֽ�
	memset(pOutput,0,24);
	enc_unicode_to_utf8_one(one,pOutput,24);
	cout << pOutput << "\n";
}
int main()
{
	//test_gbbk_utf_unicode();
	
	std::string ghello = "���";
	std::string gthank = "лл";

	std::vector<std::string> uVecStr;
	std::vector<std::string> gVecStr;
	GetText(true,uVecStr);
	GetText(false,gVecStr);

	std::cout<<ghello<<"\t"<<ConvertGBKToUtf8(ghello)<<"\t"<<IsTextUTF8(ghello.c_str(),ghello.size())<<"\t"<<IsTextUTF8(ghello)<<"\n";
	std::cout<<gthank<<"\t"<<ConvertGBKToUtf8(gthank)<<"\t"<<IsTextUTF8(gthank.c_str(),gthank.size())<<"\t"<<IsTextUTF8(gthank)<<"\n";

	std::cout<<"--------------utf8--->gbk----------------\n";
	for (std::vector<std::string>::iterator itr = uVecStr.begin();itr!=uVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertUtf8ToGBK(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"--------------gbk--->utf8----------------\n";
	for (std::vector<std::string>::iterator itr = gVecStr.begin();itr!=gVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertGBKToUtf8(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"---------------------------------\n";
	system("pause");
	return 0;
}