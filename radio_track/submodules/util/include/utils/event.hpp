#pragma once

// (c) Copyright Dmitriy Shikhov 2014, 2016, 2018, 2020

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace utils
{
class event
{
public:
    event()
        : signalled_(0)
    {
    }

    ~event() = default;

    event(event const&) = delete;
    event& operator=(event const&) = delete;

    event(event&&) = delete;
    event& operator=(event&&) = delete;

    void reset()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        signalled_ = 0;
    }

    void notify()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ++signalled_;
        condition_.notify_all();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(
            lock, [this]
            {
                return signalled_ > 0;
            });
        --signalled_;
    }

    template <typename... DurationPs>
    bool wait_for(std::chrono::duration<DurationPs...> const& duration)
    {
        return wait_with_timeout(
            duration, [](auto& cv, auto&&... args)
            {
                return cv.wait_for(args...);
            });
    }

    template <typename... TimePointPs>
    bool wait_until(std::chrono::time_point<TimePointPs...> const& time_point)
    {
        return wait_with_timeout(
            time_point, [](auto& cv, auto&&... args)
            {
                return cv.wait_until(args...);
            });
    }

    int get() const
    {
        return signalled_;
    }

private:
    template <typename Timeout, typename WaitFn>
    bool wait_with_timeout(Timeout const& timeout, WaitFn&& wait_fn)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        const bool result = wait_fn(
            condition_, lock, timeout,
            [this]
            {
                return signalled_ > 0;
            });

        if (result)
        {
            --signalled_;
        }
        return result;
    }

    int signalled_;
    std::condition_variable condition_;
    std::mutex mutex_;
};

}  // namespace utils
