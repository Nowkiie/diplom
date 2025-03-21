#pragma once

// (c) Copyright Konstantin Krasheninnikov 2018

#include <condition_variable>
#include <mutex>
#include <list>

namespace utils
{
enum class insert_place
{
    begin,
    end
};

template <typename T>
class threadsafe_list
{
public:
    using value_type = T;

    value_type wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(
            lock, [this]
            {
                return !list_.empty();
            });
        auto value = list_.front();
        list_.pop_front();
        return value;
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_.size();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_.empty();
    }

    void push(value_type const& value, insert_place place = insert_place::end)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (place == insert_place::begin)
            {
                list_.push_front(value);
            }
            else
            {
                list_.push_back(value);
            }
        }
        condition_.notify_one();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!list_.empty())
        {
            list_.pop_back();
        }
    }

private:
    std::list<value_type> list_;
    std::condition_variable condition_;
    mutable std::mutex mutex_;
};

}  // namespace utils
