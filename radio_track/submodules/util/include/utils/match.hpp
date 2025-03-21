#pragma once

// (c) Copyright Dmitriy Shikhov 2018

#include <variant>
#include <utils/overloaded.hpp>

namespace utils
{
template <typename T, typename... Fs>
constexpr auto match(T&& value, Fs&&... fs)
{
    return std::visit(make_overloaded(std::forward<Fs>(fs)...),
                      std::forward<T>(value));
}

}  // namespace utils
