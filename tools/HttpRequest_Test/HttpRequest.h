// Filename         : HttpRequest.h
// Author           : LIZHENG
// Created          : 2013-05-12
// Description      : ��libcurl�İ�װ�������ṩGET��POST�ӿ�
//
// Copyright (c) lizheng@thinkit.cn. All rights reserved.
// ***********************************************************************
#ifndef ZL_HTTPREQUEST_H
#define ZL_HTTPREQUEST_H
#include <vector>
#include <string>
struct curl_slist;
typedef void CURL;

class HttpRequest
{
public:
    struct Reponse
    {
        std::string header_;
        std::string body_;
    };

    struct UploadObject
    {
        const char *data_;
        size_t length_;
    };

public:
    explicit HttpRequest(bool requestHeader = true, bool requestBody = true);
    ~HttpRequest();

public:
    /**
    * @brief �����Ƿ�������
    * @param bDebug    �������,Ϊtrue�����������Ϣ
    */
    static void setDebug(bool bDebug)
    {
        debug_ = bDebug;
    }

    static bool isDebug()
    {
        return debug_;
    }

    /**
    * @brief ��ȡ�������Ӧ�Ĵ�����Ϣ
    * @param errcode   �������,curl�����루�μ�curl.h��CURLcode���壩
    * @return          ���������errcodeΪcurl��׼�����룬�򷵻���Ч�ַ���������ΪNULL
    */
    static const char* getErrorMessage(int errcode);

public:
    /**
    * @brief ����Http��Ӧ����Ϣͷ
    */
    std::string  getHeader() const { return reponse_.header_; }

    /**
    * @brief ����Http��Ӧ����Ϣ��
    */
    std::string  getBody() const   { return reponse_.body_; }

public:
    /**
    * @brief ����http����ʱ��ͷ
    * @param key         �������,key
    * @param value       �������,value
    */
    bool addHeader(const char* key, const char* value);

    /**
    * @brief ����http����ʱ��user-agent
    * @param userAgent   �������,User-Agent
    */
    bool setUserAgent(const char* userAgent);

public:
    /**
    * @brief HTTP GET����
    * @param url         �������,�����url��ַ
    * @param timeoutMs   �����������������ĳ�ʱʱ��,��λ���룬��ͬ
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int get(const char* url, int timeoutMs = 4000);

    /**
    * @brief HTTP GET����
    * @param url         �������,�����url��ַ
    * @param filepath    �������,�����󱣴浽���ص�·��
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int get(const char* url, const char* filepath, int timeoutMs = 4000);

    /**
    * @brief HTTP POST����
    * @param url         �������,�����url��ַ
    * @param postData    �����������Ҫpost������
    * @param dataSize    �������,��Ҫpost�����ݴ�С
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int post(const char* url, const char* postData, int dataSize, int timeoutMs = 4000);

    /**
    * @brief HTTP POST����
    * @param url         �������,�����url��ַ
    * @param postData    �����������Ҫpost������
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int post(const char* url, const std::string& postData, int timeoutMs = 4000);

    /**
    * @brief HTTP DELETE����
    * @param url         �������,�����url��ַ
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int del(const char* url, int timeoutMs = 4000);

    /**
    * @brief HTTP PUT����
    * @param url         �������,�����url��ַ
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int put(const char* url, const char* putData, size_t dataSize);

    /**
    * @brief HTTPS GET����,֤��汾
    * @param url         �������,�����url��ַ
    * @param pCaPath     �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int gets(const char* url, const char* pCaPath = NULL, int timeoutMs = 4000);

    /**
    * @brief HTTPS POST����,֤��汾
    * @param url         �������,�����url��ַ
    * @param strPost     �������,��Ҫpost������
    * @param pCaPath     �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
    * @return            ���ر�ʶ,ֻ��ΪCURLE_OK(0)ʱ��ʾ�ɹ�����������ʧ��
    */
    int posts(const char* url, const std::string& postData, const char* pCaPath = NULL, int timeoutMs = 4000);

private:
    /**
    * @brief ��ʼ���ص�
    * @param requestHeader �������,�Ƿ�����http��Ϣͷ
    * @param requestBody   �������,�Ƿ�����http��Ϣ��
    */
    void  init(bool requestHeader = true, bool requestBody = true);

private:
    static bool          debug_;       /**�Ƿ����������*/

private:
    struct curl_slist    *headers_;
    CURL                 *curl_;
    Reponse              reponse_;
};

#endif  /* ZL_HTTPREQUEST_H */