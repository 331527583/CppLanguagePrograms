#include <iostream>

#if defined(_WIN32) || defined(WIN32)        /**Windows*/
#define WINDOWS_IMPL
#include <windows.h>
#include <time.h>           //time() �� clock()
#include <Mmsystem.h>       //timeGetTime()
#pragma comment(lib, "Winmm.lib") //timeGetTime()
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(BSD)    /**Linux*/
#define LINUX_IMPL
#include <sys/time.h>        //gettimeofday()
#endif
#include <stdio.h>

/***********************************************************
ͨ�õģ�
time_t time(time_t *tloc);     //���ش�1970��1��1��0������������,����Ϊ��
clock_t clock(): ���ظó������������������ռ��CPU��ʱ�䣬����Ϊ����,��һ����С������33ms

Windows���У�
GetTickCount(): ���شӲ���ϵͳ�����������������ĺ����������Ⱥ��룬����С������18ms
                ����ֵ��32λ��˫������DWORD�洢����˿��Դ洢�����ֵ��2^32 msԼΪ49.71�죬
timeGetTime()��    �����Ժ���Ƶ�ϵͳʱ�䣬��ʱ��Ϊ��ϵͳ����������������ʱ�䣬����Ϊ����
QueryPerformanceCounter()�� ���ظ߾�ȷ�����ܼ�������ֵ,����Ϊ΢��,����ȷ�еľ�ȷ��ʱ����С��λ����ϵͳ�йص�

Linux���У�
gettimeofday(struct timeval *tv,struct timezone *tz); ��õ�ǰ��ȷʱ�䣨1970��1��1�յ����ڵ�ʱ�䣩,����Ϊ΢��
***********************************************************/

void MySleep(int sec_time)
{
    #if defined(WINDOWS_IMPL)
        Sleep(sec_time*1000);
    #elif defined(LINUX_IMPL)
        sleep(sec_time);
    #endif
}

void test_time()
{
    //ͨ�õ�
    //��time()����ʱ  ��
    time_t timeBegin, timeEnd;
    timeBegin = time(NULL);
    MySleep(1);
    timeEnd = time(NULL);
    printf("%d\n", timeEnd - timeBegin);

    /*
     * Structure used in select() call, taken from the BSD file sys/time.h.
     */
    //struct timeval {
    //        long    tv_sec;         /* seconds */
    //        long    tv_usec;        /* and microseconds */
    //};
    timeval  val;

    //��clock()����ʱ  ����
    clock_t  clockBegin, clockEnd;
    clockBegin = clock();
    MySleep(1);
    clockEnd = clock();
    printf("%d\n", clockEnd - clockBegin);

#ifdef WINDOWS_IMPL
    //Windows

    //��GetTickCount()����ʱ  ����
    DWORD  dwGTCBegin, dwGTCEnd;
    dwGTCBegin = GetTickCount();
    Sleep(1000);
    dwGTCEnd = GetTickCount();
    printf("%d\n", dwGTCEnd - dwGTCBegin);

    //��timeGetTime()����ʱ  ����
    DWORD  dwBegin, dwEnd;
    dwBegin = timeGetTime();
    Sleep(1000);
    dwEnd = timeGetTime();
    printf("%d\n", dwEnd - dwBegin);
    
    //��QueryPerformanceCounter()����ʱ  ΢��
    LARGE_INTEGER  large_interger;
    double dff;
    __int64  c1, c2;
    QueryPerformanceFrequency(&large_interger);
    dff = large_interger.QuadPart;
    QueryPerformanceCounter(&large_interger);
    c1 = large_interger.QuadPart;
    Sleep(1000);
    QueryPerformanceCounter(&large_interger);
    c2 = large_interger.QuadPart;
    printf("�߾��ȼ�ʱ��Ƶ��%lf\n", dff);
    printf("��һ�μ�ʱ��ֵ%I64d �ڶ��μ�ʱ��ֵ%I64d ��ʱ����%I64d\n", c1, c2, c2 - c1);
    printf("��ʱ%lf����\n", (c2 - c1) * 1000 / dff);

#elif  defined(LINUX_IMPL)
    //Linux

    struct timeval tpstart,tpend;
    double timeuse;
    gettimeofday(&tpstart,NULL);
    sleep(1);
    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;//ע�⣬��Ķ�����΢��Ķ�����Ӧ��������
    printf("used time:%fus\n",timeuse);
#endif

}

int main()
{
    test_time();
	getchar();
    return 0;
}