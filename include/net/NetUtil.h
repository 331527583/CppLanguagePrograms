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
    static bool        isBroadcastAddress(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv4��IPv6��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IP��ַ���򷵻�true�����򷵻�false
    */
    static bool        isValidIp(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv4��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IPv4��ַ���򷵻�true�����򷵻�false
    */
    static bool        isValidIpv4(const char *str);

    /**
    * @brief           �жϸ������ַ����Ƿ�Ϊһ��IPv6��ַ
    * @param  str      IP��ַ�ַ���
    * @return          �����һ��IPv6��ַ���򷵻�true�����򷵻�false
    */
    static bool        isValidIpv6(const char *str);

    /**
    * @brief           CPU��С�ˣ��ֽ����ж�
    * @return          �����С���ֽ�������Ƿ���true�����򷵻�false
    */
    static bool        isLittleEndian();

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @param  result   ��ת����ֽ�
    * @param  length   ��ת�ĳ���
    */
    static void        reverseBytes(const void *source, void *result, size_t length);

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @return          ��ת����ֽ�
    */
    template <typename DataType>
    static DataType    reverseBytes(const DataType& source)
    {
        DataType result = 0;
        reverseBytes(&source, &result, sizeof(result));
        return result;
    }

    /**
    * @brief           ��ת�ֽ����Ա��������ϴ���
    * @param  source   Դ�ֽ�
    * @param  result   ��ת����ֽ�
    */
    template <typename DataType>
    static void        reverseBytes(const DataType *source, DataType *result)
    {
        reverseBytes(source, result, sizeof(DataType));
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    * @param  length   ��Ҫת�����ֽڳ���
    */
    static void        host2Net(const void *source, void *result, size_t length);

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    */
    template <typename DataType>
    static void        host2Net(const DataType& source, DataType& result)
    {
        host2Net(&source, &result, sizeof(result));
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @return          ���ת����������ֽ���������
    */
    template <typename DataType>
    static DataType    host2Net(const DataType& source)
    {
        DataType result;
        host2Net(&source, &result, sizeof(result));
        return result;
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    * @param  length   ��Ҫת�����ֽڳ���
    */
    static void        net2Host(const void *source, void *result, size_t length);

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @param  result   ���ת����������ֽ���������
    */
    template <typename DataType>
    static void        net2Host(const DataType& source, DataType& result)
    {
        host2Net<DataType>(source, result);
    }

    /**
    * @brief           ��Դ���ݴ������ֽ���ת���������ֽ���
    * @param  source   �����ֽ���Դ����
    * @return          ת����������ֽ���������
    */
    template <typename DataType>
    static DataType net2Host(const DataType& source)
    {
        return host2Net<DataType>(source);
    }
};

NAMESPACE_ZL_NET_END
#endif  /* ZL_NETUTIL_H */