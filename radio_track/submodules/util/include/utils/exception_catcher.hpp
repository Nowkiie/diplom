#pragma once

// (c) Copyright Dmitriy Shikhov 2017

#include <exception>
#include <functional>
#include <stdexcept>
#include <vector>

namespace utils
{
class exception_catcher
{
public:
    template <typename F>
    void catch_in(F&& func) noexcept
    {
        try
        {
            func();
        }
        catch (...)
        {
            exception_ptrs_.emplace_back(std::current_exception());
        }
    }

    template <typename E = std::runtime_error, typename F>
    void catch_in(std::string const& error_message, F&& func) noexcept
    {
        try
        {
            func();
        }
        catch (...)
        {
            try
            {
                std::throw_with_nested(E{error_message});
            }
            catch (...)
            {
                exception_ptrs_.emplace_back(std::current_exception());
            }
        }
    }

    bool empty() const
    {
        return exception_ptrs_.empty();
    }

    template <typename V>
    void apply_visitor_to_each(V&& visitor)
    {
        for (auto exception_ptr : exception_ptrs_)
        {
            visitor(exception_ptr);
        }
        exception_ptrs_.clear();
    }

private:
    std::vector<std::exception_ptr> exception_ptrs_;
};

class simple_exception_visitor
{
    using on_visit_t = std::function<void(const char*, size_t)>;

public:
    explicit simple_exception_visitor(on_visit_t on_visit)
        : on_visit_{on_visit}
    {
    }

    template <typename ExceptionObject>
    void operator()(ExceptionObject&& exception_object, size_t level = 0) const
    {
        const auto next_level = visit(exception_object, level);
        try
        {
            rethrow(exception_object);
        }
        catch (std::exception const& exception)
        {
            (*this)(exception, next_level);
        }
        catch (...)
        {
            visit(std::runtime_error{"Unknown exception"}, next_level);
        }
    }

private:
    static void rethrow(std::exception_ptr exception_ptr)
    {
        rethrow_exception(exception_ptr);
    }

    template <typename Exception>
    static void rethrow(Exception&& exception)
    {
        rethrow_if_nested(exception);
    }

    static size_t visit(std::exception_ptr, size_t level)
    {
        return level;
    }

    template <typename Exception>
    size_t visit(Exception&& exception, size_t level) const
    {
        on_visit_(exception.what(), level);
        return level + 1;
    }

private:
    on_visit_t on_visit_;
};

}  // namespace utils
