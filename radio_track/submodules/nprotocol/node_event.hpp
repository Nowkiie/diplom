#pragma once
#include <mutex>
#include <condition_variable>

namespace nc
{
class node_event
{
public:
    node_event()
        : signalled_{}
    {
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

    void notify()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        ++signalled_;
        condition_.notify_all();
    }

private:
    int signalled_;
    std::condition_variable condition_;
    std::mutex mutex_;
};
}  // namespace nc
