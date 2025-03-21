#pragma once

// (c) Copyright Alexandr Belits 2018

#include <condition_variable>
#include <boost/circular_buffer.hpp>
#include <mutex>

namespace utils
{
template <typename T, size_t capacity>
class threadsafe_limited_stack
{
public:
    using value_type = T;

    value_type wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(
            lock, [this]
            {
                return !stack_.empty();
            });
        auto value = stack_.back();
        stack_.pop_back();
        return value;
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.size();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return stack_.empty();
    }

    void push(value_type const& value)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stack_.push_back(value);
        }
        condition_.notify_one();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!stack_.empty())
        {
            stack_.pop_back();
        }
    }

private:
    boost::circular_buffer<value_type> stack_{capacity};
    std::condition_variable condition_;
    mutable std::mutex mutex_;
};

template <typename T>
using default_treadsafe_limited_stack = threadsafe_limited_stack<T, 64>;

}  // namespace utils
