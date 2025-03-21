#pragma once

// (c) Copyright Dmitriy Shikhov 2017, 2020, 2023

#include <limits>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace utils
{
class integer_cast_error : public std::runtime_error
{
public:
    integer_cast_error()
        : std::runtime_error{"integer_cast error"}
    {
    }
};

namespace detail
{
template <template <typename> typename ReturnStrategy, typename To,
          typename From>
auto integer_cast_impl(From from) -> std::enable_if_t<
    ((std::is_unsigned<From>::value && std::is_unsigned<To>::value)
     || (std::is_signed<From>::value && std::is_signed<To>::value))
        && (sizeof(From) <= sizeof(To)),
    typename ReturnStrategy<To>::return_type>
{
    return static_cast<To>(from);
}

template <template <typename> typename ReturnStrategy, typename To,
          typename From>
auto integer_cast_impl(From from) -> std::enable_if_t<
    ((std::is_unsigned<From>::value && std::is_unsigned<To>::value)
     || (std::is_signed<From>::value && std::is_signed<To>::value))
        && (sizeof(From) > sizeof(To)),
    typename ReturnStrategy<To>::return_type>
{
    if (from < std::numeric_limits<To>::min()
        || from > std::numeric_limits<To>::max())
    {
        return ReturnStrategy<To>::fail();
    }

    return static_cast<To>(from);
}

template <template <typename> typename ReturnStrategy, typename UnsignedTo,
          typename SignedFrom>
auto integer_cast_impl(SignedFrom signed_from)
    -> std::enable_if_t<std::is_signed<SignedFrom>::value
                            && std::is_unsigned<UnsignedTo>::value,
                        typename ReturnStrategy<UnsignedTo>::return_type>
{
    constexpr const auto max_to = std::numeric_limits<UnsignedTo>::max();

    if (signed_from < 0 || static_cast<uintmax_t>(signed_from) > max_to)
    {
        return ReturnStrategy<UnsignedTo>::fail();
    }

    return static_cast<UnsignedTo>(signed_from);
}

template <template <typename> typename ReturnStrategy, typename SignedTo,
          typename UnsignedFrom>
auto integer_cast_impl(UnsignedFrom unsigned_from)
    -> std::enable_if_t<std::is_unsigned<UnsignedFrom>::value
                            && std::is_signed<SignedTo>::value,
                        typename ReturnStrategy<SignedTo>::return_type>
{
    const auto max_to =
        static_cast<uintmax_t>(std::numeric_limits<SignedTo>::max());

    if (unsigned_from > max_to)
    {
        return ReturnStrategy<SignedTo>::fail();
    }

    return static_cast<SignedTo>(unsigned_from);
}

template <typename T>
struct ThrowReturnStrategy
{
    using return_type = T;

    static auto fail() -> return_type
    {
        throw integer_cast_error{};
    }
};

template <typename T>
struct NothrowReturnStrategy
{
    using return_type = std::optional<T>;

    static auto fail() -> return_type
    {
        return {};
    }
};

template <typename To, typename From>
void check_is_integer()
{
    static_assert(std::numeric_limits<From>::is_integer,
                  "integer_cast: from value must be integer");
    static_assert(std::numeric_limits<To>::is_integer,
                  "integer_cast: to value must be integer");
}

}  // namespace detail

template <typename To, typename From>
auto integer_cast(From from) -> To
{
    detail::check_is_integer<To, From>();
    return detail::integer_cast_impl<detail::ThrowReturnStrategy, To>(from);
}

template <typename To, typename From>
auto try_integer_cast(From from) -> std::optional<To>
{
    detail::check_is_integer<To, From>();
    return detail::integer_cast_impl<detail::NothrowReturnStrategy, To>(from);
}

}  // namespace utils
