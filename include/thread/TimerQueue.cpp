#include "thread/TimerQueue.h"
#include "thread/Timer.h"
#include "base/StopWatch.h"

NAMESPACE_ZL_THREAD_START

TimerQueue* TimerQueue::m_instance = NULL;
zl::thread::Mutex TimerQueue::m_mutex;

TimerQueue* TimerQueue::instance()
{
    if(TimerQueue::m_instance==NULL)
    {
        m_mutex.lock();
        if(m_instance==NULL)
        {
            m_instance=new TimerQueue();
        }
        m_mutex.unlock();
    }
    return m_instance;
}

TimerQueue::TimerQueue() : thread_(std::bind(&TimerQueue::processThread, this))
{
    running_ = false;
    timers_.clear();
}

void TimerQueue::start()
{
    if(!running_)
    {
        running_ = true;
        //pthread_t pid;
        //pthread_create(&pid, 0, ProcessThread, this);
    }
}

void TimerQueue::stop()
{
    running_ = false;
}

void TimerQueue::addTimer(Timer * timer)
{
    m_mutex.lock();
    addTimer_(timer);
    m_mutex.unlock();
}

void TimerQueue::deleteTimer(Timer * timer)
{
    m_mutex.lock();
    deleteTimer_(timer);
    m_mutex.unlock();
}

void TimerQueue::addTimer_(Timer * timer)
{
    timers_.push_back(timer);
}

void TimerQueue::deleteTimer_(Timer * timer)
{
    timers_.remove(timer);
}

/*��ʱ���ӳ�ʱ���߳�*/
void TimerQueue::processThread()
{
    struct timeval start,end;
    unsigned int delay;

    struct timeval tm;
    end = zl::base::StopWatch::now(); ////gettimeofday(&end,0);

    const static int DEFULT_INTERVAL = 1;
    while(running_)
    {
        tm.tv_sec=0;
        tm.tv_usec=DEFULT_INTERVAL*100000;
        start.tv_sec=end.tv_sec;
        start.tv_usec=end.tv_usec;

        //������Ը�Ϊ���ӳ�ʱ��ȡlist����С���Ǹ��������֤ÿ���ӳ�ʱ�䵽���лص�
        //����ʹ��multimap���棬ÿ���ҵ���С���
        while(select(0,0,0,0,&tm)<0&&errno==EINTR);
        //int ret = select(0,0,0,0,&tm);
        
        end = zl::base::StopWatch::now(); //gettimeofday(&end,0);
        delay=(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000;

        //pthread_mutex_lock(&manage->m_mutex);
        m_mutex.lock();
        for(std::list<Timer*>::iterator iter = timers_.begin(); iter!=timers_.end(); )
        {
            Timer *timer = *iter;
            timer->timer_duration_ < delay ? timer->timer_duration_ = 0 : timer->timer_duration_ -= delay;
            if(timer->timer_duration_<=0)
            {
                timer->trigger();

                if(timer->timer_type_==Timer::TIMER_ONCE) /* һ���͵ģ���ʱ���Ƴ���������״̬ */
                {
                    //manage->DeleteTimer_(timer);
                    iter = timers_.erase(iter);
                    timer->timer_state_=Timer::TIMER_TIMEOUT;
                }
                else if(timer->timer_type_==Timer::TIMER_CIRCLE) /* ѭ���͵ģ����¼�ʱ */
                {
                    timer->timer_duration_ = timer->timer_interval_;
                    ++iter;
                }
            }
            else
            {
                ++iter;
            }
        }
       m_mutex.unlock();
    } // while

}

NAMESPACE_ZL_THREAD_END
