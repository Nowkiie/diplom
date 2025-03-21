#pragma once
#include <vector>
#include <list>
#include <exception>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cstdint>
#include <optional>
#include <variant>
#include <array>
#include <tuple>
#include <boost/rational.hpp>
#include <boost/uuid/uuid.hpp>

namespace serializer::traits
{
//проверка принадлежности типа к простым контейнерам
template <typename Container>
struct is_container : std::false_type
{
};

template <typename... Ts>
struct is_container<std::basic_string<Ts...>> : std::true_type
{
};
template <typename... Ts>
struct is_container<std::list<Ts...>> : std::true_type
{
};
template <typename... Ts>
struct is_container<std::vector<Ts...>> : std::true_type
{
};

template <typename T>
constexpr bool is_container_v = is_container<std::remove_const_t<T>>::value;

//проверка на принадлежность к set типу
template <typename Set>
struct is_set : std::false_type
{
};
template <typename T, typename... Ts>
struct is_set<std::set<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_set<std::unordered_set<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_set<std::multiset<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_set<std::unordered_multiset<T, Ts...>> : std::true_type
{
};

template <typename T>
constexpr bool is_set_v =
    is_set<std::remove_const_t<std::remove_reference_t<T>>>::value;

//проверка на принадлежность к map типу
template <typename Map>
struct is_map : std::false_type
{
};

template <typename T, typename... Ts>
struct is_map<std::map<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_map<std::multimap<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_map<std::unordered_map<T, Ts...>> : std::true_type
{
};
template <typename T, typename... Ts>
struct is_map<std::unordered_multimap<T, Ts...>> : std::true_type
{
};

template <typename T>
constexpr bool is_map_v =
    is_map<std::remove_const_t<std::remove_reference_t<T>>>::value;

//тип optional
template <typename T>
struct is_optional : std::false_type
{
};
template <typename T>
struct is_optional<std::optional<T>> : std::true_type
{
};

template <typename T>
constexpr bool is_optional_v = is_optional<std::remove_const_t<T>>::value;

//тип variant
template <typename T>
struct is_variant : std::false_type
{
};

template <typename... Ts>
struct is_variant<std::variant<Ts...>> : std::true_type
{
};

template <typename T>
constexpr bool is_variant_v = is_variant<std::remove_const_t<T>>::value;

//тип rational
template <typename T>
struct is_rational : std::false_type
{
};

template <typename T>
struct is_rational<boost::rational<T>> : std::true_type
{
};

// тип pair
template <typename... Ts>
struct is_pair : std::false_type
{
};
template <typename... Ts>
struct is_pair<std::pair<Ts...>> : std::true_type
{
};
template <typename T>
constexpr bool is_pair_v = is_pair<std::remove_const_t<T>>::value;

// тип tuple
template <typename... Ts>
struct is_tuple : std::false_type
{
};
template <typename... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type
{
};
template <typename T>
constexpr bool is_tuple_v = is_tuple<std::remove_const_t<T>>::value;

template <typename T>
constexpr bool is_rational_v = is_rational<std::remove_const_t<T>>::value;

// для uuid
template <typename T>
struct is_uuid : std::is_same<boost::uuids::uuid, T>
{
};

template <typename T>
constexpr bool is_uuid_v = is_uuid<std::remove_const_t<T>>::value;

//array
template <typename Arr>
struct is_array : std::false_type
{
};
template <typename T, size_t S>
struct is_array<std::array<T, S>> : std::true_type
{
};

template <typename T>
constexpr bool is_array_v = is_array<std::remove_const_t<T>>::value;

//проверка принадлежности к простым данным
template <typename T>
struct is_simple
    : std::integral_constant<bool, std::is_arithmetic<T>::value
                                       || std::is_enum<T>::value>
{
};

template <typename T>
constexpr bool is_simple_v = is_simple<std::remove_const_t<T>>::value;

}  // namespace serializer::traits
