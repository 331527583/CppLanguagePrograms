#include <iostream>
#include "HttpRestClient.h"
#include <assert.h>
#include "base/GBKtoUTF8.h"
using namespace std;

int main()
{
    {
        HttpRestClient req(true, true);
        std::string s = "��������";
        s =  zl::base::convertGBKToUtf8(s);
        string url = "http://192.168.9.2:8080/szly/parser?line=" + s;
        url += "&userid=5345sd233345xdgdfgdfg345sdgdfg23";
        req.setUserAgent("MyTestClient");
        req.get(url.c_str());  // �Զ�����tts
        //req.get("http://192.168.14.104:80/tts.php?data=��خ��&speed=5&decode=6", "1.pcm");  // ��ͨtts

        cout << req.getHeader() << "\n";
        cout << req.getBody() << "\n";
        system("pause");
    }
    std::cout << zl::base::convertGBKToUtf8("Ҧ����ĺ�����28972828") << "\n";
    {
        HttpRestClient req(true, true);
        req.setUserAgent("MyTestClient");
        req.get("http://192.168.14.215:80/tts_new.php?synth=Ҧ����ĺ�����28972828", "1.pcm");  // �Զ�����tts
        //req.get("http://192.168.14.104:80/tts.php?data=��خ��&speed=5&decode=6", "1.pcm");  // ��ͨtts
        
        cout << req.getHeader() << "\n";
        cout << req.getBody() << "\n";
        system("pause");
    }
    {
        //std::string s = "��������";
        std::string s = "�������� ����˰���ֹܾ��ڼ�����߳�Ʒ������˰��֪ͨ������˰��2015��11�ţ��涨�������͡�ʯ���͡��ܼ��ͺ����͵�����˰��λ˰����1.4Ԫ/����ߵ�1.52Ԫ/���������͡�����ú�͡�ȼ���͵�����˰��λ˰����1.1Ԫ/����ߵ�1.2Ԫ/����";

        cout << s << "\n";
        cout << zl::base::convertUtf8ToGBK(s) << "\n";
        cout << zl::base::convertGBKToUtf8(s) << "\n";

        s = zl::base::convertUtf8ToGBK(s);
        std::string url("http://219.234.149.147/tts.php?data=������������˰���ֹܾ��ڼ�����߳�Ʒ������˰��֪ͨ������˰��2015��11�ţ��涨�������͵�����˰��λ˰����1.4Ԫ/����ߵ� 1.52Ԫ/����&speed=3&decode=1");
        //url += s;

        //url = zl::base::ConvertUtf8ToGBK(url);
        //url += "&speed=5&decode=6";
        cout << url << "\n";
        HttpRestClient req(false, true);
        req.get(url.c_str(), "ttt.pcm");
        cout << req.getHeader() << "\n\n";
        return 0;
        //cout << req.getBody() << "\n\n";
        {
            string m_strResponse(req.getBody());
            cout << m_strResponse.size() << "\n";

            short *src=(short *)m_strResponse.c_str();
            int len = m_strResponse.size()/2;
            short* Buf_8k = (short *)malloc(len*sizeof(short));
            printf("ParseTtsVoice 2.2[%d]\n", len);
            for(int i = 0;i<len; i++)
            {
                if(i > 16630)
                    printf("ParseTtsVoice 2.3[%d]\n", i);
                assert(src);
                assert((Buf_8k+i));
                memcpy(Buf_8k+i,src,sizeof(short));
                src+=2;
            }
            FILE* fp = fopen("1.pcm", "wb");
            printf("ParseTtsVoice 3\n");
            fwrite(Buf_8k, 2, len/2, fp);
            if(Buf_8k)
            {
                free(Buf_8k);
                Buf_8k = NULL;
            }
            fclose(fp);
        }
        system("pause");
    }
    {
        HttpRestClient req(false, false);
        req.get("http://www.baidu.com");
        assert(req.getHeader().empty());
        assert(req.getBody().empty());
        system("pause");
    }
    {
        HttpRestClient req(true, false);
        req.get("http://www.baidu.com");
        cout << req.getHeader() << "\n";
        assert(req.getBody().empty());
        system("pause");
    }
    {
        HttpRestClient req(false, true);
        req.get("http://www.baidu.com");
        assert(req.getHeader().empty());
        cout << req.getBody() << "\n";
        system("pause");
    }
    {
        HttpRestClient req(true, true);
        req.addHeader("User-Agent", "Mozilla/4.04[en](Win95;I;Nav)");
        req.get("https://www.baidu.com");
        cout << req.getHeader() << "\n";
        cout << req.getBody() << "\n";
        system("pause");
    }

    cout << "###### GAME OVER ######\n";
    system("pause");
}