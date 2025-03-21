#pragma once

// (c) Copyright Dmitriy Shikhov 2023

#include <algorithm>
#include <memory>
#include <numeric>
#include <utils/active.hpp>
#include <utils/propagate_const.hpp>

namespace utils
{
template <template <typename> class ThreadsafeContainer>
class multi_active_template
{
    using active_type = active_template<ThreadsafeContainer>;

public:
    using task_type = typename active_type::task_type;

    multi_active_template(multi_active_template const&) = delete;
    multi_active_template& operator=(multi_active_template const&) = delete;

    multi_active_template(multi_active_template&&) = default;
    multi_active_template& operator=(multi_active_template&&) = default;

    explicit multi_active_template(size_t actives_count,
                                   std::string const& name = {})
    {
        actives_.reserve(actives_count);
        for (size_t i = 0; i < actives_count; ++i)
        {
            actives_.push_back(
                std::make_unique<active_type>(name + "-" + std::to_string(i)));
        }
    }

    ~multi_active_template()
    {
        stop();
    }

    /**
     * \brief Ожидание выполнения всех задач и завершение
     */
    void stop()
    {
        for (auto& a : actives_)
        {
            a->stop();
        }
    }

    /**
     * \brief Количество невыполненных задач
     */
    size_t size() const
    {
        const auto s = sizes();
        return std::accumulate(begin(s), end(s), size_t{0});
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
        if (task)
        {
            // Не учитывается текущая занятость, только очередь
            const auto s = sizes();
            const auto i = std::distance(std::begin(s),
                                         std::min_element(begin(s), end(s)));

            actives_[i]->push_task(task, args...);
        }
    }

    /**
     * \brief Удаление всех невыполненных задач
     */
    void clear()
    {
        for (auto& a : actives_)
        {
            a->clear();
        }
    }

private:
    std::vector<size_t> sizes() const
    {
        std::vector<size_t> result(std::size(actives_));
        std::transform(
            begin(actives_), end(actives_), begin(result),
            [](auto const& a)
            {
                return a->size();
            });
        return result;
    }

    std::vector<propagate_const<std::unique_ptr<active_type>>> actives_;
};

using multi_active = multi_active_template<threadsafe_queue>;

}  // namespace utils
