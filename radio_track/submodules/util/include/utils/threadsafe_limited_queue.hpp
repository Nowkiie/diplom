#pragma once

// (c) Copyright Alexandr Belits 2018

#include <condition_variable>
#include <boost/circular_buffer.hpp>
#include <mutex>

namespace utils
{
template <typename T, size_t capacity>
class threadsafe_limited_queue
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
        queue_.pop_front();
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
            queue_.push_back(value);
        }
        condition_.notify_one();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty())
        {
            queue_.pop_back();
        }
    }

private:
    boost::circular_buffer<value_type> queue_{capacity};
    std::condition_variable condition_;
    mutable std::mutex mutex_;
};

template <typename T>
using default_treadsafe_limited_queue = threadsafe_limited_queue<T, 64>;

}  // namespace utils
