// Filename         : HttpRequest.h
// Author           : LIZHENG
// Created          : 2013-05-12
// Description      : ��libcurl�İ�װ�������ṩGET��POST�ӿ�
//
// Last Modified By : LIZHENG
// Last Modified On : 2015-06-04
//
// Copyright (c) lizheng@thinkit.cn. All rights reserved.
// ***********************************************************************
#ifndef ZL_HTTPREQUEST_H
#define ZL_HTTPREQUEST_H
#include <vector>
#include <string>
struct curl_slist;

class HttpRequest
{
public:
    struct Reponse
    {
        std::string header_;
        std::string body_;
    };

public:
    HttpRequest();
    ~HttpRequest();

public:
    /**
    * @brief �����Ƿ�������
    * @param bDebug    �������,Ϊtrue�����������Ϣ
    */
    static void SetDebug(bool bDebug)
    {
        debug_ = bDebug;
    }

    static bool IsDebug()
    {
        return debug_;
    }

    /**
    * @brief ��ȡ�������Ӧ�Ĵ�����Ϣ
    * @param errcode   �������,curl�����루�μ�curl.h��CURLcode���壩
    * @return          ���������errcodeΪcurl��׼�����룬�򷵻���Ч�ַ���������ΪNULL
    */
    static const char* GetErrorMessage(int errcode);

public:
    /**
    * @brief ����Http��Ӧ����Ϣͷ
    */
    std::string  GetHeader() const { return reponse_.header_; }

    /**
    * @brief ����Http��Ӧ����Ϣ��
    */
    std::string  GetBody() const   { return reponse_.body_; }

public:
    /**
    * @brief ����http����ʱ��ͷ
    * @param key         �������,key
    * @param value       �������,value
    */
    void AddHeader(const char *key, const char *value);

    /**
    * @brief HTTP GET����
    * @param url         �������,�����url��ַ
    * @param timeoutMs   �����������������ĳ�ʱʱ��,��λ���룬��ͬ
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int Get(const char *url, int timeoutMs = 4000);

    /**
    * @brief HTTP POST����
    * @param url         �������,�����url��ַ
    * @param postData    �����������Ҫpost������
    * @param dataSize    �������,��Ҫpost�����ݴ�С
    * @param strResponse �������,���ص�����
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int Post(const char *url, const char *postData, int dataSize, int timeoutMs = 4000);

    /**
    * @brief HTTP POST����
    * @param url         �������,�����url��ַ
    * @param postData    �����������Ҫpost������
    * @param strResponse �������,���ص�����
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int Post(const char *url, const std::string& postData, int timeoutMs = 4000);

    /**
    * @brief HTTPS GET����,֤��汾
    * @param url         �������,�����url��ַ
    * @param strResponse �������,���ص�����
    * @param pCaPath     �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int Gets(const char *url, const char *pCaPath = NULL, int timeoutMs = 4000);

    /**
    * @brief HTTPS POST����,֤��汾
    * @param url         �������,�����url��ַ
    * @param strPost     �������,��Ҫpost������
    * @param strResponse �������,���ص�����
    * @param pCaPath     �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int Posts(const char *url, const std::string& postData, const char *pCaPath = NULL, int timeoutMs = 4000);

private:
    static bool          debug_;       /**�Ƿ����������*/

private:
    struct curl_slist    *headers_;
    //CURL                 *curl;
    Reponse              reponse_;
};

#endif  /* ZL_HTTPREQUEST_H */