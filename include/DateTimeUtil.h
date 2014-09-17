// ***********************************************************************
// Filename         : DateTimeUtil.h
// Author           : LIZHENG
// Created          : 2014-09-17
// Description      : ���ڡ�ʱ�乤����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-09-17
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_DATETIMEUTIL_H
#define ZL_DATETIMEUTIL_H
#include <string>

class DateTimeUtil
{
public:
	/**
	* @brief           �ж�ָ������Ƿ�Ϊ����
	* @param year      ָ�������
	* @return          �������ں�ʱ���ʽ������ַ���: YYYY-MM-DD HH:MM:SS
	*/
	static bool        IsLeapYear(int year);

	/**
	* @brief           ��ȡ��ǰ���ں�ʱ��
	* @param ptm       ָ��ǰ���ں�ʱ��Ľṹ��ָ��
	*/
	static void        CurrentDateTime(struct tm *ptm);
	/** 
	* @brief           ��ȡ��ǰ���ں�ʱ��: YYYY-MM-DD HH:MM:SS
	* @param buf       �����洢��ǰ���ں�ʱ��Ļ�����
	* @param size      buf�Ĵ�С��len > sizeof("YYYY-MM-DD HH:MM:SS")
	*/
	static void        CurrentDateTime(char* buf, size_t size);
	/**
	* @brief           ��ȡ��ǰ���ں�ʱ��: YYYY-MM-DD HH:MM:SS
	* @return          �������ں�ʱ���ʽ������ַ���
	*/
	static std::string CurrentDateTime();

	/**
	* @brief           ��ȡ��ǰ����: YYYY-MM-DD
	* @param buf       �����洢��ǰ���ڵĻ�����
	* @param size      buf�Ĵ�С��len > sizeof("YYYY-MM-DD")
	*/
	static void        CurrentDate(char* buf, size_t size);
	/**
	* @brief           ��ȡ��ǰ����: YYYY-MM-DD
	* @return          �������ں�ʱ���ʽ������ַ���
	*/
	static std::string CurrentDate();

	/**
	* @brief           ��ȡ��ǰʱ��: HH:SS:MM
	* @param buf       �����洢��ǰʱ��Ļ�����
	* @param size      buf�Ĵ�С��len > sizeof("HH:SS:MM")
	*/
	static void        CurrentTime(char* buf, size_t size);
	/**
	* @brief           ��ȡ��ǰʱ��: HH:SS:MM
	* @return          ����ʱ���ʽ������ַ���
	*/
	static std::string CurrentTime();

	/**
	* @brief           ��һ���ַ���ת��������ʱ���ʽ��Ҫ��ԭ�ַ�����ʽΪ: YYYY-MM-DD HH:MM:SS
	* @param strTime   ����ʱ���ʽ���ַ���
	* @param datetime  �����洢�ַ���ת����ʱ��Ľṹ��ָ��
	* @return          ת���ɹ�����true�����򷵻�false
	*/
	static bool        StringToDataTime(const char *strTime, struct tm *datetime);
	/**
	* @brief           ��һ���ַ���ת��������ʱ���ʽ��Ҫ��ԭ�ַ�����ʽΪ: YYYY-MM-DD HH:MM:SS
	* @param strTime   ����ʱ���ʽ���ַ���
	* @param datetime  �����洢�ַ���ת����ʱ��Ľṹ��ָ��
	* @return          ת���ɹ�����true�����򷵻�false
	*/
	static bool        StringToDataTime(const char *strTime, time_t *datetime);

	/**
	* @brief           ��һ���ַ���ת��������ʱ���ʽ��Ҫ��ԭ�ַ�����ʽΪ: YYYY-MM-DD HH:MM:SS
	* @param datetime  ָ�����ں�ʱ��Ľṹ��ָ��
	* @param buf       �����洢�ַ���ת����ʱ��Ļ�����
	* @param size      ��������С
	*/
	static void        DateTimeToString(struct tm *datetime, char *buf, size_t size);
	/**
	* @brief           ��һ�����ں�ʱ��ת��Ϊ�ַ���: YYYY-MM-DD HH:MM:SS
	* @param datetime  �洢���ں�ʱ��Ľṹ��ָ��
	* @return          ����ʱ���ʽ������ַ���
	*/
	static std::string DateTimeToString(struct tm *datetime);

	/**
	* @brief           ��һ������ת��Ϊ�ַ���: YYYY-MM-DD
	* @param datetime  ָ�����ں�ʱ��Ľṹ��ָ��
	* @param buf       �����洢�ַ���ת����ʱ��Ļ�����
	* @param size      ��������С
	*/
	static void        DateToString(struct tm *datetime, char *buf, size_t size);
	/**
	* @brief           ��һ������ת��Ϊ�ַ���: YYYY-MM-DD
	* @param datetime  ָ�����ں�ʱ��Ľṹ��ָ��
	* @return          ����ʱ���ʽ������ַ���
	*/
	static std::string DateToString(struct tm* datetime);

	/**
	* @brief           ��һ��ʱ��ת��Ϊ�ַ���: HH:MM:SS
	* @param datetime  ָ�����ں�ʱ��Ľṹ��ָ��
	* @param buf       �����洢�ַ���ת����ʱ��Ļ�����
	* @param size      ��������С
	*/
	static void        TimeToString(struct tm *datetime, char *buf, size_t size);
	/**
	* @brief           ��һ��ʱ��ת��Ϊ�ַ���: HH:MM:SS
	* @param datetime  ָ�����ں�ʱ��Ľṹ��ָ��
	* @return          ����ʱ���ʽ������ַ���
	*/
	static std::string TimeToString(struct tm *datetime);
};

#endif /* ZL_DATETIMEUTIL_H */