#pragma once

// (c) Copyright Dmitriy Shikhov 2018

namespace utils
{
// TODO(ShikhovD): эквивалентный код с cppreference.com для полноценного C++17
//
//template <typename... Fs>
//struct overloaded : Fs...
//{
//    using Fs::operator()...;
//};
//
//template <typename... Fs>
//overloaded(Fs...) -> overloaded<Fs...>;
//

template <typename... Fs>
struct overloaded;

template <typename F, typename... Fs>
struct overloaded<F, Fs...>
    : F
    , overloaded<Fs...>
{
    template <typename T, typename... Ts>
    constexpr explicit overloaded(T&& f, Ts&&... fs)
        : F(std::forward<T>(f))
        , overloaded<Fs...>(std::forward<Ts>(fs)...)
    {
    }

    using F::operator();
    using overloaded<Fs...>::operator();
};

template <typename F>
struct overloaded<F> : F
{
    template <typename T, typename = std::enable_if_t<std::is_same_v<T, F>>>
    constexpr explicit overloaded(T&& f)
        : F(std::forward<T>(f))
    {
    }

    using F::operator();
};

template <typename... Fs>
constexpr auto make_overloaded(Fs&&... fs)
{
    return overloaded<Fs...>(std::forward<Fs>(fs)...);
}

}  // namespace utils
