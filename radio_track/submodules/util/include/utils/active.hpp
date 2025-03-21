#pragma once

// (c) Copyright Dmitriy Shikhov 2014, 2016, 2018, 2023

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <utils/event.hpp>
#include <utils/thread_name.hpp>
#include <utils/threadsafe_queue.hpp>

namespace utils
{
template <template <typename> class ThreadsafeContainer>
class active_template
{
public:
    using task_type = std::function<void()>;

    active_template(active_template const&) = delete;
    active_template& operator=(active_template const&) = delete;

    active_template(active_template&&) = delete;
    active_template& operator=(active_template&&) = delete;

    explicit active_template(std::string name = {})
        : done_(false)
    {
        thread_ = std::make_unique<std::thread>(
            [this, name = std::move(name)]
            {
                thread_name(name);
                while (!(done_ && task_container_.empty()))
                {
                    try
                    {
                        auto task = task_container_.wait_and_pop();
                        task();
                    }
                    catch (...)
                    {  // do nothing //-V565
                    }
                }
            });
    }

    ~active_template()
    {
        stop();
    }

    /**
     * \brief Ожидание выполнения всех задач и завершение внутреннего потока
     */
    void stop()
    {
        const auto nop = []
        {
        };

        done_ = true;
        task_container_.push(nop);
        if (thread_->joinable())
        {
            thread_->join();
        }
        clear();
    }

    /**
     * \brief Количество невыполненных задач
     */
    size_t size() const
    {
        return task_container_.size();
    }

    /**
     * \brief Добавление задачи на выполнение
     * 
     * \param[in] task Задача
     * \param[in] args Дополнительные параметры добавления задачи
     *  во внутренний контейнер
     */
    template <typename... Args>
    void push_task(task_type const& task, Args... args)
    {
        if (task && !done_)
        {
            task_container_.push(task, args...);
        }
    }

    /**
     * \brief Удаление всех невыполненных задач
     */
    void clear()
    {
        task_container_.clear();
    }

    //[[deprecated("use stop() instead")]]
    void wait_itself()
    {
        static_assert(std::is_same<ThreadsafeContainer<task_type>,
                                   threadsafe_queue<task_type>>::value,
                      "");

        event e;
        push_task(
            [&e]
            {
                e.notify();
            });
        e.wait();
    }

private:
    std::atomic_bool done_;
    ThreadsafeContainer<task_type> task_container_;
    std::unique_ptr<std::thread> thread_;
};

using active = active_template<threadsafe_queue>;

}  // namespace utils
