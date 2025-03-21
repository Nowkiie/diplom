#pragma once

// (c) Copyright Dmitriy Shikhov 2012, 2019, 2020

#include <functional>

namespace utils
{
template <typename>
struct free_function_helper;

template <typename Result, typename... Args>
struct free_function_helper<Result(Args...)>
{
    using function_type = std::function<Result(Args...)>;

    using free_function_type = auto (*)(void*, Args...) -> Result;

    static auto free_function(void* uptr, Args... args) -> Result
    {
        return (*static_cast<function_type*>(uptr))(args...);
    }

    static auto from_free_function(void* uptr, free_function_type fptr)
        -> function_type
    {
        return [uptr, fptr](Args... args) -> Result
        {
            return fptr(uptr, args...);
        };
    }
};

}  // namespace utils
