// ***********************************************************************
// Filename         : Timer.h
// Author           : LIZHENG
// Created          : 2014-10-126
// Description      : �������⣬��Windows��select���ò�����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-10-26
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_TIMER_H
#define ZL_TIMER_H
#include "Define.h"
#include "base/NonCopy.h"
#include "thread/Mutex.h"
NAMESPACE_ZL_THREAD_START

class Timer
{
    friend class TimerQueue;
public:
     typedef int32_t  TimerID;
     enum TimerState
     {
         TIMER_IDLE=0,  //startǰ�Լ��ֶ�����stop���״̬
         TIMER_ALIVE,   //��manager��list��ʱ���״̬
         TIMER_TIMEOUT  //��ʱ���Ƴ���״̬��ѭ���͵�û��
     };
     enum TimerType
     {
         TIMER_ONCE=0,  //һ����
         TIMER_CIRCLE   //ѭ����
     };
public:
    Timer(unsigned int interval,void (*func)(Timer *,void *),void *args,TimerType type = TIMER_ONCE);
    ~Timer();

    void start(); // ��ʼ��ʱ��
    void stop();  // ֹͣ��ʱ��
    void reset(unsigned int interval); // ���ö�ʱ��
    bool trigger(); // ������ʱ��

private:   
    TimerState    timer_state_;        //״̬
    TimerType     timer_type_;         //����  
    unsigned int  timer_interval_;     //��ʱ���
    unsigned int  timer_duration_;     //��ʼ����Ϊinterval�����ӳ�ʱ�䵽������
    unsigned long trigger_sum_;        //��������

    void         *args_;               //�ص���������
    void (*callback_)(Timer *,void *); //�ص�����
public:

};

NAMESPACE_ZL_THREAD_END
#endif  /* ZL_TIMER_H */