#pragma once
#include <functional>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

namespace nc
{
class node_active
{
    using function_t = std::function<void()>;

public:
    node_active()
        : done_{}
    {
    }
    ~node_active()
    {
        stop();
    }
    void send(const function_t& func)
    {
        push(func);
        condition_.notify_one();
    }
    void stop()
    {
        send(
            [this]
            {
                done_ = true;
            });
        if (thread_.joinable())
        {
            thread_.join();
        }
        while (queue_.size())
        {
            queue_.pop();
        }
    }
    void start()
    {
        stop();
        done_ = false;
        thread_ = std::thread(
            [this]
            {
                thread_func();
            });
    }

private:
    void thread_func()
    {
        while (!done_)
        {
            try
            {
                auto task = pop();
                task();
            }
            catch (...)
            {
            }
        }
    }
    void push(const function_t& func)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(func);
    }
    function_t pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(
            lock, [this]
            {
                return !queue_.empty();
            });
        auto value = queue_.front();
        queue_.pop();
        return value;
    }
    bool done_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<function_t> queue_;
    std::thread thread_;
};
}  // namespace nc
