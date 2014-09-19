// ***********************************************************************
// Filename         : GBKtoUTF8.h
// Author           : LIZHENG
// Created          : 2014-04-28
// Description      : GBK��Utf8���໥ת��
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-04-30
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef GBK_TO_UTF8_FILE_H
#define GBK_TO_UTF8_FILE_H

#include <string>

///   \brief    ����ַ����Ƿ���utf8����
///   \param    str : Դ�ַ���.
bool IsTextUTF8(const std::string& str);

///   \brief    ����ַ����Ƿ���utf8����
///   \param    str : �ַ���
///   \param    len : �ַ�������
bool IsTextUTF8(const char *str, int len);

///   \brief    ת��utf8�ַ���Ϊgbk�ַ���
///   \param    strGBK : ����Ϊgbk���ַ���
///   \return   ���ر���Ϊutf8���ַ���,ת��ʧ��ʱ���ؿմ�
std::string ConvertGBKToUtf8(const std::string& strGBK);

///   \brief    ת��utf8�ַ���Ϊgbk�ַ���
///   \param    strGBK : ����Ϊgbk���ַ���
///   \param    len    : Դ�ַ�������
///   \return   ���ر���Ϊutf8���ַ���,ת��ʧ��ʱ���ؿմ�
std::string ConvertGBKToUtf8(const char *strGBK, int len);

///   \brief    ת��gbk�ַ���Ϊutf8�ַ���
///   \param    strUtf8 : ����Ϊutf8���ַ���
///   \return   ���ر���Ϊgbk���ַ���,ת��ʧ��ʱ���ؿմ�
std::string ConvertUtf8ToGBK(const std::string& strUtf8);

///   \brief    ת��gbk�ַ���Ϊutf8�ַ���
///   \param    strUtf8 : ����Ϊutf8���ַ���
///   \param    len     : Դ�ַ�������
///   \return   ���ر���Ϊgbk���ַ���,ת��ʧ��ʱ���ؿմ�
std::string ConvertUtf8ToGBK(const char *strUtf8, int len);

/**�����ַ����Ķ����Ʊ�ʾ*/
std::string PrintStringAsBinaryString(const char *p);
std::string PrintStringAsBinaryString(const std::string& str);

/**Unicode��UTF-8�ı���ת��*/
unsigned short one_gbk_to_unicode(unsigned char ch, unsigned char cl);
unsigned short one_unicode_to_gbk(unsigned short unicode); //not implement
void unicode_to_gbk(unsigned short *punicode, char *pgbk, int len);
int one_unicode_to_utf8(unsigned long unic, unsigned char *pOutput, int outSize);

//����1��UTF8�ַ�����ǰλ��ָ�룬�������Ҫ��ָ�룬��Ϊ����Ҫͨ����1���ַ������жϲ�֪��һ���������ַ��ı���Ҫ���ȡ���ٸ��ַ�
//����2�Ƿ��ص�UCS-2�����Unicode�ַ�
int one_utf8_to_unicode(const char *utf8, unsigned short& wch);
//����1��UTF8������ַ���
//����2�������UCS-2��Unicode�ַ���
//����3�ǲ���1�ַ����ĳ���
//ʹ�õ�ʱ����Ҫע�����2��ָ����ڴ���㹻�á���ʵ��ȫ�İ취���ж�һ��pUniBuf�Ƿ�ΪNULL�����ΪNULL��ֻͳ��������Ȳ�дpUniBuf������
//ͨ�����κ������þͿ��Լ����ʵ������Ҫ��Unicode����������ȡ���Ȼ�����򵥵�˼·�ǣ��������ת����UTF8���ַ����������ܱ�Unicode�٣���
//�Կ��Լ򵥵İ���sizeof(wchar_t) * utf8Leng������pUniBuf���ڴ桭��
int utf8_to_unicode(const char *utf8Buf, unsigned short *pUniBuf, int utf8Leng);

int unicode_to_utf8(unsigned short wchar, char *utf8);

#endif