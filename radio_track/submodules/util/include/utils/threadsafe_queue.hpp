#pragma once

// (c) Copyright Dmitriy Shikhov 2014, 2016

#include <condition_variable>
#include <queue>
#include <mutex>

namespace utils
{
template <typename T>
class threadsafe_queue
{
public:
    using value_type = T;

    value_type wait_and_pop()
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

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    void push(value_type const& value)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(value);
        }
        condition_.notify_one();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty())
        {
            queue_.pop();
        }
    }

private:
    std::queue<value_type> queue_;
    std::condition_variable condition_;
    mutable std::mutex mutex_;
};

}  // namespace utils
