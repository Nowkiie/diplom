#pragma once

// (c) Copyright Sergey Musikhin 2021

#include <condition_variable>
#include <queue>
#include <mutex>

namespace utils
{
template <typename T>
class threadsafe_queue_batch
{
public:
    using value_type = T;

    void wait_and_swap(std::queue<value_type>& values)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(
            lock, [this]
            {
                return !queue_.empty();
            });
        std::swap(values, queue_);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    void push_values(const std::vector<value_type>& values)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& value : values)
            {
                queue_.push(value);
            }
        }
        condition_.notify_one();
    }

private:
    std::queue<value_type> queue_;
    std::condition_variable condition_;
    std::mutex mutex_;
};

}  // namespace utils
