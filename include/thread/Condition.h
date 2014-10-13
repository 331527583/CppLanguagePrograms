// ***********************************************************************
// Filename         : Condition.h
// Author           : LIZHENG
// Created          : 2014-05-16
// Description      : ����������Windows��Linuxƽ̨�µķ�װ
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-08-25
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_CONTDITION_H
#define ZL_CONTDITION_H
#include "OsDefine.h"
#include "NonCopy.h"
#include "Mutex.h"
#ifdef OS_LINUX
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#elif defined(OS_WINDOWS)
#define OS_WINDOWS
#include <Windows.h>
#endif

namespace zl
{
    class Condition : public zl::NonCopy
    {
    public:
        explicit Condition(Mutex& mu) : mutex_(mu), signaled_(false)
        {
#ifdef OS_WINDOWS
            InitializeConditionVariable(&condition_);
#elif defined(OS_LINUX)
            pthread_cond_init(&condition_, NULL);
#endif
        }

        ~Condition()
        {
#ifdef OS_WINDOWS
            //nothing
#elif defined(OS_LINUX)
            pthread_cond_destroy(&condition_);
#endif
        }

    public:
        void Wait()
        {
#ifdef OS_WINDOWS
            SleepConditionVariableCS(&condition_, mutex_.GetMutex(), INFINITE);
#elif defined(OS_LINUX)
            pthread_cond_wait(&condition_, mutex_.GetMutex());
#endif
        }

        void NotifyOne()
        {
#ifdef OS_WINDOWS
            WakeConditionVariable(&condition_);
#elif defined(OS_LINUX)
            pthread_cond_signal(&condition_);
#endif
        }

        void NotifyAll()
        {
#ifdef OS_WINDOWS
            WakeAllConditionVariable(&condition_);
#elif defined(OS_LINUX)
            pthread_cond_broadcast(&condition_);
#endif
        }

    private:
        bool signaled_;
        Mutex&		mutex_;
#ifdef OS_WINDOWS
        CONDITION_VARIABLE condition_;
#elif defined(OS_LINUX)
        pthread_cond_t     condition_;
#endif
    };

} /* namespace ZL */

#endif /* ZL_CONTDITION_H */