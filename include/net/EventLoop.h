// ***********************************************************************
// Filename         : EventLoop.h
// Author           : LIZHENG
// Created          : 2014-10-26
// Description      : io service, �ɹ���socket��timer��signal��io
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-10-26
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_EVENTLOOP_H
#define ZL_EVENTLOOP_H
#include "Define.h"
#include "base/Timestamp.h"
#include "base/NonCopy.h"
#include "thread/Mutex.h"
#include "thread/Thread.h"
#include "thread/Atomic.h"
#include "net/CallBacks.h"
NAMESPACE_ZL_NET_START
class Channel;
class Poller;
class Timer;
class TimerQueue;
class EventfdHandler;

class EventLoop : zl::NonCopy
{
public:
    typedef std::function<void()> Functor;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

public:
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    /// �����߳������У�����������̵߳��ã���תΪ����queueInLoop
    /// @param func        : ����������
    void runInLoop(const Functor& func);
    
    /// �����첽���ô洢�����ȴ�poller����ʱ����һ�����첽�����еĲ���
    /// @param func        : ����������
    void queueInLoop(const Functor& func);

    TimerId addTimer(const TimerCallback& cb, const Timestamp& when);
    TimerId addTimer(const TimerCallback& cb, double delaySeconds, bool repeat = false);
    void    cancelTimer(TimerId id);

    bool isRunning() { return running_; }
    bool isInLoopThread() const { return currentThreadId_ == thread::this_thread::get_id(); }
    void assertInLoopThread() const;

private:
    void wakeupPoller();          //wakeup the waiting poller
    void callPendingFunctors();   //call when loop() return

private:
    typedef std::vector<Channel*> ChannelList;

    const thread::Thread::id currentThreadId_;  // thread id of this object created

    ChannelList              activeChannels_;   // active channels when poll return
    Channel                  *currentActiveChannel_; // the current processing active channel 
    Poller                   *poller_;          // I/O poller
    thread::Atomic<bool>     running_;          // status for eventloop running
    thread::Atomic<bool>     eventHandling_;    // status for active channel handling

    EventfdHandler           *wakeupfd_;        // wakeup poller::poll
    Channel                  *wakeupChannel_;   // channel of wakeupfd_

    thread::Atomic<bool>     callingPendingFunctors_;  // status for pending functors calling
    thread::Mutex            mutex_;            // for guard  pendingFunctors_
    std::vector<Functor>     pendingFunctors_;  // functors when polling, need mutex guard

    TimerQueue               *timerQueue_;
};

NAMESPACE_ZL_NET_END
#endif  /* ZL_EVENTLOOP_H */
