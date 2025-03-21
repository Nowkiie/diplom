#pragma once
#include <serializer.hpp>
#include <string>
#include <set>
#include <unordered_set>
#include <list>
#include <map>
#include <unordered_map>
#include <optional>
#include <variant>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/rational.hpp>
#include <type_traits>

namespace stringizer
{
namespace detail
{
const char* const name_int = "int";
const char* const name_uint = "uint";
const char* const name_bool = "bool";
const char* const name_enum = "enum";
const char* const name_vector = "vector";
const char* const name_map = "map";
const char* const name_list = "list";
const char* const name_set = "set";
const char* const name_string = "string";
const char* const name_pair = "pair";
const char* const name_float = "float";
const char* const name_double = "double";
const char* const name_optional = "optional";
const char* const name_uuid = "uuid";
const char* const name_rational = "rational";
const char* const name_variant = "variant";
const char* const name_struct = "struct";
const char* const name_array = "array";

template <typename T>
struct type_helper;

//преобразование простого типа
template <typename T>
std::string to_string(const T& value)
{
    return type_helper<T>::string(value);
}

// рассчёт отступов
inline std::string shift(const std::string& source)
{
    std::string space = " ";
    std::string result = space;
    for (char c : source)
    {
        result += c;
        if (c == '\n')
        {
            result += space;
        }
    }
    return result;
}
// имя целого типа
template <typename T>
std::string integer_name()
{
    static_assert(std::is_integral_v<T>);
    if constexpr (std::is_signed_v<T>)
    {
        return name_int + std::to_string(sizeof(T) * 8);
    }
    else
    {
        return name_uint + std::to_string(sizeof(T) * 8);
    }
}
// типы - контейнеры
template <typename T>
std::string to_string_container(const T& c)
{
    std::string result;
    for (const auto& elem : c)
    {
        result += to_string(elem) + ", ";
    }
    // удаление последнего разделителя
    if (!result.empty())
    {
        result.pop_back();
        result.pop_back();
    }
    return "[" + result + "]";
}

// преобразование поля структуры
template <typename T>
std::string to_string_field(const T& value, int index)
{
    return std::to_string(index) + "<" + type_helper<T>::name()
           + ">: " + type_helper<T>::string(value);
}

// преобразование структуры
template <typename T>
std::string to_string_struct(const T& value)
{
    std::string result;
    int field_index{};
    serializer::visit(
        value, [&](const auto& item)
        {
            result += shift(to_string_field(item, field_index++)) + "\n";
        });
    return "{\n" + result + "}";
}

// default type helper
template <typename T>
struct type_helper
{
    static std::string name()
    {
        if constexpr (std::is_integral_v<T>)
        {
            return integer_name<T>();
        }
        else if constexpr (std::is_enum_v<T>)
        {
            return name_enum;
        }
        else if constexpr (std::is_array_v<T>)
        {
            return name_array;
        }
        else
        {
            return name_struct;
        }
    }
    static std::string string(const T& value)
    {
        if constexpr (std::is_integral_v<T>)
        {
            if constexpr (std::is_signed_v<T>)
            {
                return std::to_string(static_cast<int64_t>(value));
            }
            else
            {
                return std::to_string(static_cast<uint64_t>(value));
            }
        }
        else if constexpr (std::is_enum_v<T>)
        {
            return std::to_string(static_cast<int64_t>(value));
        }
        else if constexpr (std::is_array_v<T>)
        {
            return to_string_container(value);
        }
        else
        {
            return to_string_struct(value);
        }
    }
};

template <typename... Ts>
struct type_helper<std::vector<Ts...>>
{
    static std::string name()
    {
        return name_vector;
    }
    static std::string string(const std::vector<Ts...>& value)
    {
        return to_string_container(value);
    }
};
template <typename T, typename A>
struct type_helper<std::map<T, A>>
{
    static std::string name()
    {
        return name_map;
    }
    static std::string string(const std::map<T, A>& value)
    {
        return to_string_container(value);
    }
};

template <typename... Ts>
struct type_helper<std::multimap<Ts...>>
{
    static std::string name()
    {
        return name_map;
    }
    static std::string string(const std::multimap<Ts...>& value)
    {
        return to_string_container(value);
    }
};
template <typename... Ts>
struct type_helper<std::unordered_map<Ts...>>
{
    static std::string name()
    {
        return name_map;
    }
    static std::string string(const std::unordered_map<Ts...>& value)
    {
        return to_string_container(value);
    }
};
template <typename... Ts>
struct type_helper<std::unordered_multimap<Ts...>>
{
    static std::string name()
    {
        return name_map;
    }
    static std::string string(const std::unordered_multimap<Ts...>& value)
    {
        return to_string_container(value);
    }
};
template <typename T, typename A>
struct type_helper<std::list<T, A>>
{
    static std::string name()
    {
        return name_list;
    }
    static std::string string(const std::list<T, A>& value)
    {
        return to_string_container(value);
    }
};

template <typename... Ts>
struct type_helper<std::set<Ts...>>
{
    static std::string name()
    {
        return name_set;
    }
    static std::string string(const std::set<Ts...>& value)
    {
        return to_string_container(value);
    }
};
template <>
struct type_helper<std::string>
{
    static std::string name()
    {
        return name_string;
    }
    static std::string string(const std::string& value)
    {
        return "\"" + value + "\"";
    }
};
template <typename... Ts>
struct type_helper<std::basic_string<Ts...>>
{
    static std::string name()
    {
        return name_string;
    }
    static std::string string(const std::basic_string<Ts...> value)
    {
        return to_string_container(value);
    }
};
template <>
struct type_helper<float>
{
    static std::string name()
    {
        return name_float;
    }
    static std::string string(const float& value)
    {
        return std::to_string(value);
    }
};
template <>
struct type_helper<double>
{
    static std::string name()
    {
        return name_float;
    }
    static std::string string(const double& value)
    {
        return std::to_string(value);
    }
};
template <>
struct type_helper<bool>
{
    static std::string name()
    {
        return name_bool;
    }
    static std::string string(const bool& value)
    {
        return std::to_string(value);
    }
};
template <typename T1, typename T2>
struct type_helper<std::pair<T1, T2>>
{
    static std::string name()
    {
        return name_pair;
    }
    static std::string string(const std::pair<T1, T2>& value)
    {
        return "[" + to_string(value.first) + ", " + to_string(value.second)
               + "]";
    }
};
template <typename T>
struct type_helper<std::optional<T>>
{
    static std::string name()
    {
        return name_optional;
    }
    static std::string string(const std::optional<T>& value)
    {
        if (value)
            return to_string(*value);
        else
            return {};
    }
};
template <typename... Ts>
struct type_helper<std::variant<Ts...>>
{
    static std::string name()
    {
        return name_variant;
    }
    static std::string string(const std::variant<Ts...>& value)
    {
        if (value.valueless_by_exception())
            return {};
        return expand_variant<0, sizeof...(Ts)>(value, value.index());
    }
    template <size_t I, size_t L>
    static std::string expand_variant(const std::variant<Ts...>& value,
                                      size_t i)
    {
        if constexpr (I == L)
        {
            return {};
        }
        else
        {
            if (I == i)
            {
                return to_string(std::get<I>(value));
            }
            else
            {
                return expand_variant<I + 1, L>(value, i);
            }
            return "";
        }
    }
};
template <>
struct type_helper<boost::uuids::uuid>
{
    static std::string name()
    {
        return name_uuid;
    }
    static std::string string(const boost::uuids::uuid& value)
    {
        return boost::uuids::to_string(value);
    }
};
template <typename T>
struct type_helper<boost::rational<T>>
{
    static std::string name()
    {
        return name_rational;
    }
    static std::string string(const boost::rational<T>& value)
    {
        return to_string(value.numerator()) + " / "
               + to_string(value.denominator());
    }
};

template <typename T, size_t S>
struct type_helper<std::array<T, S>>
{
    static std::string name()
    {
        return name_array;
    }
    static std::string string(const std::array<T, S>& value)
    {
        return to_string_container(value);
    }
};


}  // namespace detail

//преобразование простого типа
template <typename T>
std::string to_string(const T& value)
{
    return detail::to_string(value);
}

}  // namespace stringizer
