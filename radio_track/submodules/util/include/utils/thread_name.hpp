#pragma once

// (c) Copyright Dmitriy Shikhov 2023

#include <atomic>
#include <string>

namespace utils
{
inline auto thread_name(std::string const& name = {}) -> std::string const&
{
    static std::atomic_int number{};
    const thread_local auto thread_name =
        !name.empty() ? name : "Thread-" + std::to_string(number++);
    return thread_name;
}

}  // namespace utils
