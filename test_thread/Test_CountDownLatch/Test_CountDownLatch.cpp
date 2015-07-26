#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "thread/Thread.h"
#include "thread/CountDownLatch.h"
#include "base/StringUtil.h"
#include "base/Logger.h"
using namespace std;
using namespace zl;
using namespace zl::thread;
using namespace zl::base;

// ����1�� ������̵߳ȴ����߳��ͷ��źţ�Ȼ��ͬʱ��ʼ����
class KidsThreadsWaitMainThread
{
public:
    KidsThreadsWaitMainThread(int numThreads) : latch_(1)
    {
        for (int i = 0; i < numThreads; ++i)
        {
            string name("thread_");
            name += zl::base::toStr(i);
            threads_.push_back(new Thread(std::bind(&KidsThreadsWaitMainThread::threadFunc, this), name));
        }
        LOG_INFO("KidsThreadsWaitMainThread()");
    }
    void run()
    {
        LOG_INFO("KidsThreadsWaitMainThread run: start release signal");
        latch_.countDown();
        LOG_INFO("KidsThreadsWaitMainThread run: start release signal over");
    }
    void joinAll()
    {
        LOG_INFO("void joinAll() start");
        for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1)); 
        LOG_INFO("void joinAll() end");
    }
private:
    void threadFunc()
    {
        LOG_INFO("tid(threadFunc)=%d ready, waiting signal...", this_thread::get_id().value());
        latch_.wait();
        LOG_INFO("tid(threadFunc)=%d run, doing....", this_thread::get_id().value());

        this_thread::sleep_for(chrono::milliseconds(4000));
        //while (true) { }

        LOG_INFO("tid(threadFunc)=%d finish, stopped", this_thread::get_id().value());
    }
private:
    CountDownLatch latch_;
    vector<Thread*> threads_;
};

// ����2: ������߳�һ�����Ϳ�ʼ��������ɹ�����֪ͨ���̣߳� ���̵߳ȴ����������߳���ɹ���
class MainThreadWaitKidsThreads
{
public:
    MainThreadWaitKidsThreads(int numThreads) : latch_(numThreads)
    {
        for (int i = 0; i < numThreads; ++i)
        {
            string name("thread_");
            name += zl::base::toStr(i);
            Thread *trd = new Thread(std::bind(&MainThreadWaitKidsThreads::threadFunc, this), name);
            threads_.push_back(trd);
        }
        LOG_INFO("MainThreadWaitKidsThreads()");
    }
    void wait()
    {
        LOG_INFO("MainThreadWaitKidsThreads wait: wait children starting....");
        latch_.wait();      //�˴�����ʱ���������̱߳�Ȼ
        LOG_INFO("MainThreadWaitKidsThreads wait: wait children started\n");
    }
    void joinAll()
    {
        LOG_INFO("void joinAll() start");
        for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1));
        LOG_INFO("void joinAll() end");
    }
private:
    void threadFunc()
    {
        LOG_INFO("tid(threadFunc)=%d start, doing...", this_thread::get_id().value());

        this_thread::sleep_for(chrono::milliseconds(3000));
        //while (true) { }
        latch_.countDown();   // ������ɣ�֪ͨ���̣߳�����˾�д�ڱ�������һ�У���ʾ���߳���������֪ͨ���߳�

        LOG_INFO("tid(threadFunc)=%d finish, stopped", this_thread::get_id().value());
    }
private:
    CountDownLatch latch_;
    vector<Thread*> threads_;
};

int main()
{
    LOG_INFO("-------------------");
    LOG_INFO("tid(main)=%d running....", this_thread::get_id().value());
    KidsThreadsWaitMainThread t1(3);
    this_thread::sleep_for(chrono::milliseconds(3000));
    LOG_INFO("tid(main)=%d create thread ok ...", this_thread::get_id().value());
    t1.run();
    this_thread::sleep_for(chrono::milliseconds(1000));
    t1.joinAll();

    
    LOG_INFO("-------------------\n");
    LOG_INFO("tid(main)=%d running....", this_thread::get_id().value());
    MainThreadWaitKidsThreads t2(3);
    this_thread::sleep_for(chrono::milliseconds(3000));
    LOG_INFO("tid(main)=%d create thread ok ...", this_thread::get_id().value());
    t2.wait();
    this_thread::sleep_for(chrono::milliseconds(1000));
    t2.joinAll();

    LOG_INFO("game over\n");
    getchar();
    return 0;
}