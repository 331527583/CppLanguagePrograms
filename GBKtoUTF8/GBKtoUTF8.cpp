#include "GBKtoUTF8.h"
#include <string>
#include <cstdlib>
#include <string.h>
#include <memory.h>
#include <assert.h>


#if defined(_WIN32) || defined(WIN32)
#define OS_WINDOWS
#include <Windows.h>

#else
#define OS_LINUX
#include <iconv.h>
#endif

#ifdef OS_WINDOWS
std::string ConvertGBKToUtf8(const std::string& strGBK)
{
	int len = MultiByteToWideChar( CP_ACP, 0, (LPCTSTR)strGBK.c_str(), -1, NULL, 0 );
	unsigned short * wszUtf8 = new unsigned short[len+1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar( CP_ACP, 0, (LPCTSTR)strGBK.c_str(), -1, (LPWSTR)wszUtf8, len );
	len = WideCharToMultiByte( CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL );
	char *szUtf8 = new char[len + 1];
	memset( szUtf8, 0, len + 1 );
	WideCharToMultiByte ( CP_UTF8, 0, (LPWSTR)wszUtf8, -1, (LPSTR)szUtf8, len, NULL,NULL );
	std::string strUtf8 = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;

	return strUtf8;
}
std::string ConvertUtf8ToGBK(const std::string& strUtf8)
{
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8.c_str(), -1, NULL,0);
	unsigned short * wszGBK = new unsigned short[len+1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8.c_str(), -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK=new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, (LPWSTR)wszGBK, -1, (LPSTR)szGBK, len, NULL,NULL);
	std::string strGBK = szGBK;
	delete[] szGBK;
	delete[] wszGBK;

	return strGBK;
}
#elif defined(OS_LINUX)
bool code_convert(const char * from_charset ,const char *to_charset , char * inbuf , size_t  inlen , char* outbuf , size_t outlen ) 
{ 
	iconv_t cd ; 
	int rc ; 
	char ** pin = &inbuf ; 
	char **pout = &outbuf ;

	cd = iconv_open( to_charset , from_charset ); 
	if( cd == 0 ) 
	{  
		return false;     
	}  

	memset( outbuf , 0 , outlen );
	int convert = iconv( cd , pin , &inlen , pout , &outlen ); 
	if( convert == -1 )
	{ 
		iconv_close( cd );
		return false ;
	}
	iconv_close(cd);
	
	return true ;
}  

std::string ConvertGBKToUtf8(const std::string& strGBK)
{
	const size_t length = strGBK.length();

	char *cname = new char[length + 1];
	memset(cname, '\0', length + 1);
	memcpy(cname, strGBK.c_str(), length);

	char *cdst = new char[length * 3];
	memset(cdst, '\0', length * 3);

	bool code = code_convert( "gbk" , "utf-8" , cname, length, cdst, length * 3);
	std::string strUtf8;
	if (code)
	{
		strUtf8 = cdst;
	}
	else    //ת��ʧ�ܾ�ʹ��ԭ���ı������ݣ����ܱ�û�кðɣ�Ҫ�������ط�ʹ�õĻ���δ�����Ŷ
	{
		strUtf8 = cname;
	}

	delete[] cname;
	delete[] cdst;

	return strUtf8;
}

std::string ConvertUtf8ToGBK(const std::string& strUtf8)
{
	const size_t length = strUtf8.length();

	char *cname = new char[length+1];
	memset(cname, '\0', length + 1);
	memcpy(cname, strUtf8.c_str(), length);

	char *cdst = new char[length+1];
	memset(cdst, '\0', length+1);

	bool code = code_convert( "utf-8" , "gbk" , cname, length, cdst, length);
	std::string strGBK;
	if (code)
	{
		strGBK = cdst;
	}
	else    //ת��ʧ�ܾ�ʹ��ԭ���ı������ݣ����ܱ�û�кðɣ�Ҫ�������ط�ʹ�õĻ���δ�����Ŷ
	{
		strGBK = cname;
	}

	delete[] cname;
	delete[] cdst;

	return strGBK;
}
#endif


/*��������IsTextUTF8���޷�����gb2312����ĺ��֡�лл��*/
bool IsTextUTF8(const char* str, int length)
{
#ifndef WIN32    
	typedef unsigned long DWORD;
	typedef unsigned char UCHAR;
#endif    
	int i;
	DWORD nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�
	UCHAR chr;
	bool bAllAscii =true; //���ȫ������ASCII, ˵������UTF-8
	for(i=0; i<length; i++)
	{
		chr = (UCHAR)*(str+i);

		if( (chr & 0x80) != 0 ) // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx
			bAllAscii = false;

		if(nBytes == 0) //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���
		{
			if(chr >= 0x80)
			{
				if(chr >=0xFC && chr <= 0xFD)
					nBytes=6;
				else if(chr >= 0xF8)
					nBytes=5;
				else if(chr >= 0xF0)
					nBytes=4;
				else if(chr >= 0xE0)
					nBytes=3;
				else if(chr>=0xC0)
					nBytes=2;
				else
				{
					return false;
				}
				nBytes--;
			}
		}
		else //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx
		{
			if((chr&0xC0) != 0x80 )
			{
				return false;
			}
			nBytes--;
		}
	}
	if( nBytes > 0 ) //Υ������
	{
		return false;
	}
	if(bAllAscii) //���ȫ������ASCII, ˵������UTF-8
	{
		return false;
	}

	return true;
}

int is_utf8_special_byte(unsigned char c)
{
	unsigned special_byte = 0X02; //binary 00000010    
	if (c >> 6 == special_byte) {
		return 1;
	} else {
		return 0;
	}    
}

bool IsTextUTF8(const std::string& str)
{
	unsigned one_byte   = 0X00;    //binary 00000000
	unsigned two_byte   = 0X06;    //binary 00000110
	unsigned three_byte = 0X0E;    //binary 00001110  
	unsigned four_byte  = 0X1E;    //binary 00011110
	unsigned five_byte  = 0X3E;    //binary 00111110
	unsigned six_byte   = 0X7E;    //binary 01111110

	unsigned char k = 0;
	unsigned char m = 0;
	unsigned char n = 0;
	unsigned char p = 0;
	unsigned char q = 0;

	unsigned char c = 0; 
	bool	isUtf8 = false;
	for (size_t i=0; i<str.size();)
	{
		c = (unsigned char)str[i]; 
		if (c>>7 == one_byte) 
		{
			i++;
			continue;
		} 
		else if (c>>5 == two_byte) 
		{
			k = (unsigned char)str[i+1];
			if ( is_utf8_special_byte(k) )
			{
				isUtf8 = true; //utf8_yes++;
				i += 2;
				continue;
			}
		} 
		else if (c>>4 == three_byte)
		{
			m = (unsigned char)str[i+1];
			n = (unsigned char)str[i+2];
			if ( is_utf8_special_byte(m) && is_utf8_special_byte(n) )
			{
				isUtf8 = true; //utf8_yes++;
				i += 3;
				continue;
			}
		} 
		else if (c>>3 == four_byte)
		{
			k = (unsigned char)str[i+1];
			m = (unsigned char)str[i+2];
			n = (unsigned char)str[i+3];
			if ( is_utf8_special_byte(k)
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n) )
			{
				isUtf8 = true; //utf8_yes++;  
				i += 4;
				continue;
			}
		} 
		else if (c>>2 == five_byte)
		{
			unsigned char k = (unsigned char)str[i+1];
			unsigned char m = (unsigned char)str[i+2];
			unsigned char n = (unsigned char)str[i+3];
			unsigned char p = (unsigned char)str[i+4];
			if ( is_utf8_special_byte(k) 
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)
				&& is_utf8_special_byte(p) ) 
			{
				isUtf8 = true; //utf8_yes++;  
				i += 5;
				continue;
			}
		} 
		else if (c>>1 == six_byte)
		{
			k = (unsigned char)str[i+1];
			m = (unsigned char)str[i+2];
			n = (unsigned char)str[i+3];
			p = (unsigned char)str[i+4];
			q = (unsigned char)str[i+5];
			if ( is_utf8_special_byte(k) 
				&& is_utf8_special_byte(m)
				&& is_utf8_special_byte(n)
				&& is_utf8_special_byte(p) 
				&& is_utf8_special_byte(q) )
			{
				isUtf8 = true; //utf8_yes++;  
				i += 6;
				continue;
			}
		}

		if(!isUtf8)
			return false;
		else
			i++;
	}

	return true;
}


