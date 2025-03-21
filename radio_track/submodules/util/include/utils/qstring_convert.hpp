#pragma once

// (c) Copyright Dmitriy Shikhov 2018

#include <optional>
#include <QString>

namespace utils::detail
{
template <typename>
struct qstring_converter_impl;

#define UTILS_DETAIL_QSTRING_CONVERTER_IMPL(F)                   \
    template <>                                                  \
    struct qstring_converter_impl<decltype(QString{}.F())>       \
    {                                                            \
        template <typename... Args>                              \
        static auto convert(QString const& string, Args... args) \
        {                                                        \
            return string.F(args...);                            \
        }                                                        \
    };

UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toDouble)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toFloat)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toInt)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toLong)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toLongLong)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toShort)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toUInt)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toULong)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toULongLong)
UTILS_DETAIL_QSTRING_CONVERTER_IMPL(toUShort)

#undef UTILS_DETAIL_QSTRING_CONVERTER_IMPL

}  // namespace utils::detail

namespace utils
{
template <typename T, typename... Args>
auto to(QString const& string, Args... args) -> std::optional<T>
{
    bool is_ok = false;
    const auto value =
        detail::qstring_converter_impl<T>::convert(string, &is_ok, args...);

    if (is_ok)
    {
        return value;
    }
    return {};
}

}  // namespace utils
