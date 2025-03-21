#pragma once

#include <vector>
#include <list>
#include <exception>
#include <map>
#include <unordered_map>
#include <cstdint>

namespace serializer
{
namespace detail
{
template <std::size_t>
struct value
{
    std::size_t value;
};

template <std::size_t I>
struct calc_fields;
template <>
struct calc_fields<0>
{
    template <typename T>
    static constexpr auto calc(bool) noexcept -> value<0>
    {
        return {0};
    }
};

#define CALC_DECLARE(I, ...)                       \
    template <>                                    \
    struct calc_fields<I>                          \
    {                                              \
        template <typename T>                      \
        static constexpr auto calc(bool) noexcept  \
        {                                          \
            return calc_fields<I - 1>::calc<T>(0); \
        }                                          \
        template <typename T>                      \
        static constexpr auto calc(int) noexcept   \
            -> value<sizeof(T{__VA_ARGS__})>       \
        {                                          \
            return {I};                            \
        }                                          \
    };

// clang-format off
CALC_DECLARE(1, {});
CALC_DECLARE(2, {},{});
CALC_DECLARE(3, {},{},{});
CALC_DECLARE(4, {},{},{},{});
CALC_DECLARE(5, {},{},{},{},{});
CALC_DECLARE(6, {},{},{},{},{},{});
CALC_DECLARE(7, {},{},{},{},{},{},{});
CALC_DECLARE(8, {},{},{},{},{},{},{},{});
CALC_DECLARE(9, {},{},{},{},{},{},{},{},{});
CALC_DECLARE(10, {},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(11, {},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(12, {},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(13, {},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(14, {},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(15, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(16, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(17, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(18, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(19, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(20, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(21, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(22, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(23, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(24, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(25, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(26, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(27, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(28, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(29, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(30, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(31, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
CALC_DECLARE(32, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{});
#undef CALC_DECLARE
// clang-format on

template <std::size_t I>
struct visit_fields;

template <>
struct visit_fields<0>
{
    template <typename T, typename V>
    static void call(T& /*src*/, V&& /*visitor*/)
    {
        static_assert(sizeof(T) == 1);
    }
};

#define VISIT_DECLARE(I, ...)                 \
    template <>                               \
    struct visit_fields<I>                    \
    {                                         \
        template <typename T, typename V>     \
        static void call(T& src, V&& visitor) \
        {                                     \
            auto& [__VA_ARGS__] = src;        \
            visitor(__VA_ARGS__);             \
        }                                     \
    };
// clang-format off
VISIT_DECLARE(1, x1);
VISIT_DECLARE(2, x1, x2);
VISIT_DECLARE(3, x1, x2, x3);
VISIT_DECLARE(4, x1, x2, x3, x4);
VISIT_DECLARE(5, x1, x2, x3, x4, x5);
VISIT_DECLARE(6, x1, x2, x3, x4, x5, x6);
VISIT_DECLARE(7, x1, x2, x3, x4, x5, x6, x7);
VISIT_DECLARE(8, x1, x2, x3, x4, x5, x6, x7, x8);
VISIT_DECLARE(9, x1, x2, x3, x4, x5, x6, x7, x8, x9);
VISIT_DECLARE(10, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10);
VISIT_DECLARE(11, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11);
VISIT_DECLARE(12, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12);
VISIT_DECLARE(13, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13);
VISIT_DECLARE(14, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14);
VISIT_DECLARE(15, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
VISIT_DECLARE(16, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16);
VISIT_DECLARE(17, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17);
VISIT_DECLARE(18, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18);
VISIT_DECLARE(19, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19);
VISIT_DECLARE(20, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20);
VISIT_DECLARE(21, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21);
VISIT_DECLARE(22, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22);
VISIT_DECLARE(23, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23);
VISIT_DECLARE(24, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24);
VISIT_DECLARE(25, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25);
VISIT_DECLARE(26, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26);
VISIT_DECLARE(27, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27);
VISIT_DECLARE(28, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28);
VISIT_DECLARE(29, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29);
VISIT_DECLARE(30, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30);
VISIT_DECLARE(31, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31);
VISIT_DECLARE(32, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32);
#undef VISIT_DECLARE
// clang-format on

template <typename T>
constexpr std::size_t fields_count()
{
    return calc_fields<32>::calc<std::remove_reference_t<T>>(0).value;
}

template <typename T, typename V>
constexpr void visit(T&& object, V&& visitor)
{
    visit_fields<fields_count<T>()>::call(
        object, [visitor_call = std::forward<V>(visitor)](auto&... args)
        {
            (visitor_call(args), ...);
        });
}

}  // namespace detail

}  // namespace serializer
