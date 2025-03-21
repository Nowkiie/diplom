#pragma once

// (c) Copyright Dmitriy Shikhov 2016

#include <type_traits>

namespace utils
{
namespace detail
{
using string = const char*;

constexpr auto is_equal(string x, string y, std::size_t i = 0) noexcept -> bool
{
    return x[i] == y[i] ? (x[i] == '\0' ? true : is_equal(x, y, i + 1)) : false;
}

template <typename T, std::size_t Size>
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
    constexpr auto index_of(T val, std::size_t i = 0) const noexcept
        -> std::size_t
    {
        return i < Size ? (is_equal(vals_[i], val) ? i : index_of(val, i + 1))
                        : Size;
    }

    T vals_[Size];
};

template <typename T>
constexpr auto has_field(detail::string field, int) noexcept ->
    typename T::vs2015_so_stupid_t_
//std::enable_if_t<&T::fields != nullptr, bool>
{
    return T::fields().index_of(field) != T::fields().size();
}

template <typename T>
constexpr bool has_field(detail::string, ...) noexcept
{
    return false;
}

template <bool>
struct call_if
{
    template <std::size_t I, typename T, typename F>
    static void call(T&, F)
    {
    }
};

template <>
struct call_if<true>
{
    template <std::size_t I, typename T, typename F>
    static void call(T& obj, F f)
    {
        f(obj.template get<I>());
    }
};

}  // namespace detail

template <typename T>
constexpr bool has_field(detail::string field) noexcept
{
    return detail::has_field<T>(field, 0);
}

template <typename T>
constexpr auto index_field(detail::string field) noexcept
{
    return T::fields().index_of(field);
}

template <::size_t I, typename T>
constexpr auto const& get_field(T const& obj) noexcept
{
    return obj.template get<I>();
}

}  // namespace utils

// ReSharper disable CppUnusedIncludeDirective
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
// ReSharper restore CppUnusedIncludeDirective

template <int I>
struct integer_argumnet_t
{
};

#define UTILS_DETAIL_STRING(R, N, V) BOOST_PP_STRINGIZE(V),
#define UTILS_DETAIL_GET(R, N, I, V)                 \
    auto const& get_arg(integer_argumnet_t<I>) const \
    {                                                \
        return V;                                    \
    }                                                \
    /**/
#define UTILS_FIELDS(...)                                                    \
    using vs2015_so_stupid_t_ = bool;                                        \
    static constexpr auto fields() noexcept                                  \
    {                                                                        \
        return utils::detail::array<utils::detail::string,                   \
                                    BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)>{    \
            {BOOST_PP_SEQ_FOR_EACH(UTILS_DETAIL_STRING, ,                    \
                                   BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))}}; \
    }                                                                        \
    template <int I>                                                         \
    auto const& get() const                                                  \
    {                                                                        \
        return get_arg(integer_argumnet_t<I>());                             \
    }                                                                        \
                                                                             \
    BOOST_PP_SEQ_FOR_EACH_I(UTILS_DETAIL_GET, ,                              \
                            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))           \
    /**/
#define UTILS_CALL_IF_FIELD_EXIST(OBJ, FIELD, F)                              \
    utils::detail::call_if<utils::has_field<                                  \
        std::remove_reference_t<decltype(OBJ)>>(BOOST_PP_STRINGIZE(FIELD))>:: \
        template call<                                                        \
            utils::index_field<std::remove_reference_t<decltype(OBJ)>>(       \
                BOOST_PP_STRINGIZE(FIELD))>(OBJ, F);                          \
    /**/
