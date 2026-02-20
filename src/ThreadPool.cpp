#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int threads_num)
{
    for(int i=0; i<threads_num; i++)
    {
        threads_.emplace_back(&ThreadPool::consumer, this);
    }
}

void ThreadPool::producer(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(tasks_mutex_);
        tasks_.emplace(std::move(task));
    }
    cv_.notify_one();
}

void ThreadPool::consumer()
{
    while (true)
    {
        std::function<void()> task;
        
        {
            std::unique_lock<std::mutex> lock(tasks_mutex_);

            if(stop_ && tasks_.empty())
            {
                return;
            }

            cv_.wait(lock, 
                [this](){return !tasks_.empty() || stop_;}
            );

            if(stop_ && tasks_.empty())
            {
                return;
            }

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        task(); 
    }
    
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(tasks_mutex_);
        stop_ = true;
    }

    cv_.notify_all();

    for(int i=0; i<threads_.size(); i++)
    {
        threads_[i].join();
    }
}