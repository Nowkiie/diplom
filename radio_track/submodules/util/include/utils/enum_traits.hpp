#pragma once

// (c) Copyright Dmitriy Shikhov 2016, 2017, 2018

#include <optional>
#include <stdexcept>
#include <type_traits>

// ReSharper disable CppUnusedIncludeDirective
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
// ReSharper restore CppUnusedIncludeDirective

namespace utils
{
namespace enum_traits
{
using string = const char*;

namespace detail
{
template <typename T>
constexpr auto is_equal(T x, T y) noexcept
    -> std::enable_if_t<std::is_integral<T>::value || std::is_enum<T>::value,
                        bool>
{
    return x == y;
}

constexpr auto is_equal(string x, string y, size_t i = 0) noexcept -> bool
{
    return x[i] == y[i] ? (x[i] == '\0' ? true : is_equal(x, y, i + 1)) : false;
}

}  // namespace detail

template <typename T, size_t Size>
struct array
{
    constexpr auto begin() const noexcept
    {
        return &vals_[0];
    }
    constexpr auto end() const noexcept
    {
        return &vals_[0] + Size;
    }
    constexpr auto size() const noexcept
    {
        return Size;
    }
    constexpr auto at(size_t i) const noexcept -> std::optional<T>
    {
        return i < Size ? std::optional<T>{vals_[i]} : std::optional<T>{};
    }
    constexpr auto index_of(T val, size_t i = 0) const noexcept -> size_t
    {
        return i < Size
                   ? (detail::is_equal(vals_[i], val) ? i
                                                      : index_of(val, i + 1))
                   : Size;
    }

    T vals_[Size];
};

namespace detail
{
template <typename>
class info;

template <typename T>
constexpr auto value_or_throw(std::optional<T> val) -> T
{
    return val ? val.value() : throw std::logic_error("enum out of range");
}

}  // namespace detail

template <typename E>
using integral_t = typename detail::info<E>::integral_type;

template <typename E>
constexpr auto name() noexcept -> string
{
    return detail::info<E>::name();
}

template <typename E>
constexpr auto values() noexcept
{
    return detail::info<E>::values();
}

template <typename E>
constexpr auto names() noexcept
{
    return detail::info<E>::names();
}

template <typename E>
constexpr auto integrals() noexcept
{
    return detail::info<E>::integrals();
}

namespace nothrow
{
template <typename E>
constexpr auto to_string(E val) noexcept -> std::optional<string>
{
    return names<E>().at(values<E>().index_of(val));
}

template <typename E>
constexpr auto from_string(string val) noexcept -> std::optional<E>
{
    return values<E>().at(names<E>().index_of(val));
}

template <typename E>
constexpr auto to_integral(E val) noexcept -> std::optional<integral_t<E>>
{
    return integrals<E>().at(values<E>().index_of(val));
}

template <typename E>
constexpr auto from_integral(integral_t<E> val) noexcept -> std::optional<E>
{
    return values<E>().at(integrals<E>().index_of(val));
}

}  // namespace nothrow

template <typename E>
constexpr auto to_string(E val) -> string
{
    return detail::value_or_throw(nothrow::to_string(val));
}

template <typename E>
constexpr auto from_string(string val) -> E
{
    return detail::value_or_throw(nothrow::from_string<E>(val));
}

template <typename E>
constexpr auto to_integral(E val) -> integral_t<E>
{
    return detail::value_or_throw(nothrow::to_integral(val));
}

template <typename E>
constexpr auto from_integral(integral_t<E> val) -> E
{
    return detail::value_or_throw(nothrow::from_integral<E>(val));
}

}  // namespace enum_traits
}  // namespace utils

#define UTILS_ENUM_TRAITS_DETAIL_TO_TUPLE(V) \
    BOOST_PP_IF(BOOST_PP_IS_BEGIN_PARENS(V), V, (V))
/**/
#define UTILS_ENUM_TRAITS_DETAIL_ELEM(N, V) \
    BOOST_PP_TUPLE_ELEM(N, UTILS_ENUM_TRAITS_DETAIL_TO_TUPLE(V))
/**/
#define UTILS_ENUM_TRAITS_DETAIL_DECL(R, N, V)              \
    UTILS_ENUM_TRAITS_DETAIL_ELEM(0, V)                     \
    BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_TUPLE_SIZE(           \
                    UTILS_ENUM_TRAITS_DETAIL_TO_TUPLE(V))), \
                = UTILS_ENUM_TRAITS_DETAIL_ELEM(1, V), ),
/**/
#define UTILS_ENUM_TRAITS_DETAIL_VALUE(R, N, V) \
    N::UTILS_ENUM_TRAITS_DETAIL_ELEM(0, V),
/**/
#define UTILS_ENUM_TRAITS_DETAIL_STRING(R, N, V) \
    BOOST_PP_STRINGIZE(UTILS_ENUM_TRAITS_DETAIL_ELEM(0, V)),
/**/
#define UTILS_ENUM_TRAITS_DETAIL_INTEGRAL(R, N, V) \
    static_cast<integral_type>(N::UTILS_ENUM_TRAITS_DETAIL_ELEM(0, V)),
/**/
#define UTILS_ENUM_TRAITS_DETAIL_ENUM_INFO(N, T, ...)                        \
    struct BOOST_PP_CAT(enum_info_, N)                                       \
    {                                                                        \
        using integral_type = T;                                             \
                                                                             \
        static constexpr auto name() noexcept                                \
        {                                                                    \
            return BOOST_PP_STRINGIZE(N);                                    \
        }                                                                    \
        static constexpr auto values() noexcept                              \
        {                                                                    \
            return utils::enum_traits::array<N, BOOST_PP_VARIADIC_SIZE(      \
                                                    __VA_ARGS__)>{           \
                {BOOST_PP_SEQ_FOR_EACH(                                      \
                    UTILS_ENUM_TRAITS_DETAIL_VALUE, N,                       \
                    BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))}};                \
        }                                                                    \
        static constexpr auto names() noexcept                               \
        {                                                                    \
            return utils::enum_traits::array<                                \
                utils::enum_traits::string,                                  \
                BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)>{{BOOST_PP_SEQ_FOR_EACH( \
                UTILS_ENUM_TRAITS_DETAIL_STRING, N,                          \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))}};                    \
        }                                                                    \
        static constexpr auto integrals() noexcept                           \
        {                                                                    \
            return utils::enum_traits::array<T, BOOST_PP_VARIADIC_SIZE(      \
                                                    __VA_ARGS__)>{           \
                {BOOST_PP_SEQ_FOR_EACH(                                      \
                    UTILS_ENUM_TRAITS_DETAIL_INTEGRAL, N,                    \
                    BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))}};                \
        }                                                                    \
    };
/**/
// FIX: work with Qt moc
#define UTILS_ENUM_DECLARATION(N, T, ...)                            \
    enum class N : T                                                 \
    {                                                                \
        BOOST_PP_SEQ_FOR_EACH(UTILS_ENUM_TRAITS_DETAIL_DECL, N,      \
                              BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
    };                                                               \
    UTILS_ENUM_TRAITS_DETAIL_ENUM_INFO(N, T, __VA_ARGS__)
/**/
#define UTILS_ENUM_DECLARATION_Q(N, T, S, ...) \
    enum class N : T                           \
    {                                          \
        _ = S - 1,                             \
        __VA_ARGS__                            \
    };                                         \
    UTILS_ENUM_TRAITS_DETAIL_ENUM_INFO(N, T, __VA_ARGS__)
/**/
#define UTILS_ENUM_REGISTRATION(S, N)                      \
    namespace utils                                        \
    {                                                      \
    namespace enum_traits                                  \
    {                                                      \
    namespace detail                                       \
    {                                                      \
    template <>                                            \
    class info<S N> : public S BOOST_PP_CAT(enum_info_, N) \
    {                                                      \
    };                                                     \
    }                                                      \
    }                                                      \
    }
/**/

#ifndef UTILS_ENUM_TRAITS_NO_SHORT_MACRO
#    define ENUM(N, T, ...) UTILS_ENUM_DECLARATION(N, T, __VA_ARGS__)
#    define ENUM_Q(N, T, S, ...) UTILS_ENUM_DECLARATION_Q(N, T, S, __VA_ARGS__)
#    define ENUM_REG(S, N) UTILS_ENUM_REGISTRATION(S, N)
#endif
