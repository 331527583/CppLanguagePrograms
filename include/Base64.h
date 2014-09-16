// ***********************************************************************
// Filename         : Base64.h
// Author           : LIZHENG
// Created          : 2014-09-16
// Description      : Base64 �����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-09-16
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_BASE64_H
#define ZL_BASE64_H
#include <string>

// len == strlen(src), and strlen(dst) >= len * 4 / 3
// ���ر������ַ�������
int         Base64Encode(const char *src, int len, char *dst);
int         Base64Encode(const char *src, int len, std::string& dst);
int         Base64Encode(const std::string& src, std::string& dst);

// len == strlen(src), and strlen(dst) >= len * 3 / 4
// ���ؽ������ַ�������
int         Base64Decode(const char *src, size_t len, char *dst);
int         Base64Decode(const char *src, int len, std::string& dst);
int         Base64Decode(const std::string& src, std::string& dst);

#endif  /* ZL_BASE64_H */