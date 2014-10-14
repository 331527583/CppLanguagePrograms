// ***********************************************************************
// Filename         : NetUtil.h
// Author           : LIZHENG
// Created          : 2014-09-17
// Description      : ������ع�����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-09-17
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_NETUTIL_H
#define ZL_NETUTIL_H
#include "Define.h"
NAMESPACE_ZL_NET_START

class NetUtil
{
public:
    /**
    * @brief           �жϴ����IP�ַ����Ƿ��ǹ㲥��ַ
    * @param  str      IP��ַ�ַ���
    * @return          ���strΪ�㲥��ַ���򷵻�true�����򷵻�false
    */
    static bool        IsBroadcastAddress(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv4��IPv6��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IP��ַ���򷵻�true�����򷵻�false
    */
    static bool        IsValidIp(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv4��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IPv4��ַ���򷵻�true�����򷵻�false
    */
    static bool        IsValidIpv4(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv6��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IPv6��ַ���򷵻�true�����򷵻�false
    */
    static bool        IsValidIpv6(const char *str);

    /**
    * @brief           CPU��С�ˣ��ֽ����ж�
    * @return          �����С���ֽ�������Ƿ���true�����򷵻�false
    */
    static bool        IsLittleEndian();

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @param  result   ��ת����ֽ�
    * @param  length   ��ת�ĳ���
    */
    static void        ReverseBytes(const void *source, void *result, size_t length);

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @return          ��ת����ֽ�
    */
    template <typename DataType>
    static DataType    ReverseBytes(const DataType& source)
    {
        DataType result = 0;
        ReverseBytes(&source, &result, sizeof(result));
        return result;
    }

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @param  result   ��ת����ֽ�
    */
    template <typename DataType>
    static void        ReverseBytes(const DataType *source, DataType *result)
    {
        ReverseBytes(source, result, sizeof(DataType));
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    * @param  length   ��Ҫת�����ֽڳ���
    */
    static void        Host2Net(const void *source, void *result, size_t length);

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    */
    template <typename DataType>
    static void        Host2Net(const DataType& source, DataType& result)
    {
        Host2Net(&source, &result, sizeof(result));
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @return          ���ת����������ֽ���������
    */
    template <typename DataType>
    static DataType    Host2Net(const DataType& source)
    {
        DataType result;
        Host2Net(&source, &result, sizeof(result));
        return result;
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    * @param  length   ��Ҫת�����ֽڳ���
    */
    static void        Net2Host(const void *source, void *result, size_t length);

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    */
    template <typename DataType>
    static void        Net2Host(const DataType& source, DataType& result)
    {
        Host2Net<DataType>(source, result);
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @return          ת����������ֽ���������
    */
    template <typename DataType>
    static DataType Net2Host(const DataType& source)
    {
        return Host2Net<DataType>(source);
    }
};

NAMESPACE_ZL_NET_END
#endif  /* ZL_NETUTIL_H */