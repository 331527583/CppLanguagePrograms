// ***********************************************************************
// Filename         : BlockQueueWorker.h
// Author           : LIZHENG
// Created          : 2014-05-16
// Description      : �������ȣ���������������BlockingQueue����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-08-25
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_BLOCKQUEUEWORKER_H
#define ZL_BLOCKQUEUEWORKER_H
#include "BlockQueue.h"

NAMESPACE_ZL_THREAD_START

template <typename Queue>
    class JobWorker
    {
    public:
        typedef Queue QueueType;
        typedef typename Queue::JobType JobType;
        typedef boost::function<bool(JobType&)> FunctionType;

        template<typename FunctionType>
        JobWorker(QueueType& queue, FunctionType function, int thread_num = 1):
            queue_(queue), function_(function), thread_num_(thread_num)
        {
        }

        JobWorker(QueueType& queue, int thread_num = 1):
            queue_(queue), thread_num_(thread_num)
        {
        }

        ~JobWorker()
        {
            stop();
        }

        void start()
        {
            if(threads_.size() > 0) return;
            for(int i = 0; i < thread_num_; ++i)
            {
                threads_.create_thread(boost::bind(&JobWorker::doWork, this));
            }
        }

        template<typename Func>
        void start(FunctionType function)
        {
            function_ = function;
            start();
        }

        void stop()
        {
            function_ = 0;
            queue_.Stop();
            threads_.interrupt_all();
            threads_.join_all();//������ֱ��do_workִ���˳�
        }

    private:
        void doWork() //���塣������鹤���������ݣ�ֻҪ�����ݾʹ���֪�����������
        {
            for(;;)
            {
                JobType job;
                bool bret = queue_.pop(job);
                if(!function_ || !function_(job))
                {
                    //break;
                    //TODO:
                }
            }
        }

    private:
        QueueType&        		queue_;
        FunctionType		    function_;
        int						thread_num_;
        boost::thread_group		threads_;
    };    

NAMESPACE_ZL_THREAD_END

#endif  /* ZL_BLOCKQUEUEWORKER_H */