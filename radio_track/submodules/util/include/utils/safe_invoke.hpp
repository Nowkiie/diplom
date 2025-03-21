#pragma once

// (c) Copyright Dmitriy Shikhov 2018

#include <functional>
#include <optional>
#include <type_traits>

namespace utils::detail
{
template <typename Result, typename Fn, typename Ptr, typename... Args>
auto safe_invoke_impl(Fn&& fn, Ptr&& ptr, Args&&... args)
{
    using result_type =
        std::conditional_t<std::is_void_v<Result>, void,
                           std::conditional_t<std::is_pointer_v<Result>, Result,
                                              std::optional<Result>>>;

    return ptr ? result_type(std::invoke(std::forward<Fn>(fn),
                                         std::forward<Ptr>(ptr),
                                         std::forward<Args>(args)...))
               : result_type();
}

template <typename Result, typename T, typename... FnArgs, typename... Args>
auto safe_invoke(Result (T::*fn)(FnArgs...) const, Args&&... args)
{
    return safe_invoke_impl<Result>(std::mem_fn(fn),
                                    std::forward<Args>(args)...);
}

template <typename Result, typename T, typename... FnArgs, typename... Args>
auto safe_invoke(Result (T::*fn)(FnArgs...), Args&&... args)
{
    return safe_invoke_impl<Result>(std::mem_fn(fn),
                                    std::forward<Args>(args)...);
}

}  // namespace utils::detail

namespace utils
{
/**
 * \brief Invoke fn(ptr, args...) if static_cast<bool>(ptr) == true
 *
 * \param fn сallable object
 * \param ptr first parameter
 * \param args other parameters
 * 
 * \return
 *      1) void if result of fn() is void \n
 *      2) pointer if result of fn() is pointer \n
 *      3) std::optional otherwise \n
 */
template <typename Fn, typename Ptr, typename... Args>
auto safe_invoke(Fn&& fn, Ptr&& ptr, Args&&... args)
{
    return detail::safe_invoke(std::forward<Fn>(fn), std::forward<Ptr>(ptr),
                               std::forward<Args>(args)...);
}

}  // namespace utils
