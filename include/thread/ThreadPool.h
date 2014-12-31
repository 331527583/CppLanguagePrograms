﻿// ***********************************************************************
// Filename         : ThreadPool.h
// Author           : LIZHENG
// Created          : 2014-10-06
// Description      :
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-12-31
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_THREADPOOL_H
#define ZL_THREADPOOL_H
#include "Define.h"
#include "base/NonCopy.h"
#include "thread/BlockingQueue.h"
NAMESPACE_ZL_THREAD_START

class Thread;

class ThreadPool : NonCopy
{
public:
    typedef std::function<void ()> Task;

public:
    explicit ThreadPool(const std::string& name = "ThreadPool");
    ~ThreadPool();

public:
    void start(int numThreads);
    void stop();
    void run(const Task& f);
    size_t size() const { return queue_.size(); }

private:
    void executeThread();

private:
    std::string           name_;
    bool                  running_;
    BlockingQueue<Task>   queue_;
    std::vector<Thread *> threads_;
};

NAMESPACE_ZL_THREAD_END
#endif  /* ZL_THREADPOOL_H */