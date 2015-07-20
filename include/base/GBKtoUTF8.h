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
#include "Define.h"
#include <string>
NAMESPACE_ZL_BASE_START

///   \brief    ����ַ����Ƿ���utf8����
///   \param    str : Դ�ַ���.
bool isTextUTF8(const std::string& str);

///   \brief    ����ַ����Ƿ���utf8����
///   \param    str : �ַ���
///   \param    len : �ַ�������
bool isTextUTF8(const char *str, int len);

///   \brief    ת��utf8�ַ���Ϊgbk�ַ���
///   \param    strGBK : ����Ϊgbk���ַ���
///   \return   ���ر���Ϊutf8���ַ���
std::string convertGBKToUtf8(const std::string& strGBK);

///   \brief    ת��utf8�ַ���Ϊgbk�ַ���
///   \param    strGBK : ����Ϊgbk���ַ���
///   \param    len    : Դ�ַ�������
///   \return   ���ر���Ϊutf8���ַ���
std::string convertGBKToUtf8(const char *strGBK, int len);

///   \brief    ת��gbk�ַ���Ϊutf8�ַ���
///   \param    strUtf8 : ����Ϊutf8���ַ���
///   \return   ���ر���Ϊgbk���ַ���
std::string convertUtf8ToGBK(const std::string& strUtf8);

///   \brief    ת��gbk�ַ���Ϊutf8�ַ���
///   \param    strUtf8 : ����Ϊutf8���ַ���
///   \param    len     : Դ�ַ�������
///   \return   ���ر���Ϊgbk���ַ���
std::string convertUtf8ToGBK(const char *strUtf8, int len);

NAMESPACE_ZL_BASE_END
#endif