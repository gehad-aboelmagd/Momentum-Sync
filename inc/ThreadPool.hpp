#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
private:
    std::vector<std::thread> threads_;
    std::queue <std::function<void()>> tasks_;
    std::mutex tasks_mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
public:
    ThreadPool(int threads_num);
    ~ThreadPool();
    void producer(std::function<void()> task);
    void consumer();
};

#endif // THREAD_POOL_HPP_