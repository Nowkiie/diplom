#pragma once
#include <vector>
#include <list>
#include <exception>
#include <map>
#include <unordered_map>
#include <cstdint>
#include <optional>
#include <variant>
#include <boost/rational.hpp>
#include <boost/uuid/uuid.hpp>

namespace serializer::detail
{
template <typename T>
uint32_t serializable_size(T& t);

// пропустить size байтов в входящем потоке
template <typename Archive>
void skip_bytes(Archive& ar, uint32_t size)
{
    char dummy;
    while (size--)
    {
        ar.do_serialize(dummy);
    }
}

//для обработки простых контейнеров
template <typename Archive, typename Container>
static void serialize_container_save(Archive& ar, const Container& t)
{
    uint32_t size = uint32_t(t.size());
    ar.do_serialize(size);
    for (const auto& e : t)
    {
        ar.do_serialize(e);
    }
}

template <typename Archive, typename Container>
static void serialize_container_load(Archive& ar, Container& t)
{
    uint32_t size{};
    t.clear();
    ar.do_serialize(size);
    t.resize(size);
    for (auto& e : t)
    {
        ar.do_serialize(e);
    }
}
//для обработки set типов
template <typename Archive, typename Set>
static void serialize_set_save(Archive& ar, Set& t)
{
    uint32_t size = uint32_t(t.size());
    ar.do_serialize(size);
    for (const auto& e : t)
    {
        ar.do_serialize(e);
    }
}

template <typename Archive, typename Set>
static void serialize_set_load(Archive& ar, Set& t)
{
    uint32_t size{};
    t.clear();
    ar.do_serialize(size);

    while (size--)
    {
        typename Set::value_type e{};
        ar.do_serialize(e);
        t.insert(std::move(e));
    }
}
//для обработки map типов
template <typename Archive, typename Map>
static void serialize_map_save(Archive& ar, Map& t)
{
    uint32_t size = uint32_t(t.size());
    ar.do_serialize(size);
    for (auto& e : t)
    {
        auto k = e.first;
        ar.do_serialize(k);
        ar.do_serialize(e.second);
    }
}

template <typename Archive, typename Map>
static void serialize_map_load(Archive& ar, Map& t)
{
    uint32_t size{};
    t.clear();
    ar.do_serialize(size);

    while (size--)
    {
        std::pair<typename Map::key_type, typename Map::mapped_type> e{};
        ar.do_serialize(e.first);
        ar.do_serialize(e.second);
        t.insert(std::move(e));
    }
}

//для обработки optional типов
template <typename Archive, typename Optional>
static void serialize_optional_save(Archive& ar, Optional& t)
{
    if (t.has_value())
    {
        ar.do_serialize(uint32_t{1});
        ar.do_serialize(t.value());
    }
    else
    {
        ar.do_serialize(uint32_t{0});
    }
}

template <typename Archive, typename Optional>
static void serialize_optional_load(Archive& ar, Optional& t)
{
    uint32_t flag{};
    ar.do_serialize(flag);
    if (flag)
    {
        typename Optional::value_type value{};
        ar.do_serialize(value);
        t = Optional{std::move(value)};
    }
    else
    {
        t = Optional{};
    }
}
//для обработки variant типов
template <typename Archive, typename Variant>
static void serialize_variant_save(Archive& ar, Variant& t)
{
    if (t.valueless_by_exception())
    {
        //не нужно подсовывать плохой variant
        throw std::bad_variant_access();
    }
    uint32_t index = static_cast<uint32_t>(t.index());
    std::visit(
        [&ar, index](auto&& arg)
        {
            uint32_t size = serializable_size(arg);
            ar.do_serialize(index);
            ar.do_serialize(size);
            ar.do_serialize(arg);
        },
        t);
}

struct serialize_variant
{
    template <size_t I, typename Archive, typename Variant>
    static void init_one(uint32_t index, Archive& ar, Variant& t)
    {
        if (I == index)
        {
            t.template emplace<I>();
            std::visit(
                [&ar](auto&& arg)
                {
                    ar.do_serialize(arg);
                },
                t);
        }
    }
    template <typename Archive, typename Variant, size_t... Is>
    static void init_sequence(uint32_t index, Archive& ar, Variant& t,
                              std::index_sequence<Is...>)
    {
        (init_one<Is>(index, ar, t), ...);
    }
};

template <typename Archive, typename Variant>
static void serialize_variant_load(Archive& ar, Variant& t)
{
    uint32_t index{};
    uint32_t size{};
    ar.do_serialize(index);
    ar.do_serialize(size);

    constexpr auto variant_size = std::variant_size_v<Variant>;
    if (index >= variant_size)
    {
        // не нашли подходящий тип
        skip_bytes(ar, size);
    }
    else
    {
        serialize_variant::init_sequence(
            index, ar, t, std::make_index_sequence<variant_size>{});
    }
}

//для обработки variant типов
template <typename Archive, typename Rational>
static void serialize_rational_save(Archive& ar, const Rational& t)
{
    ar.do_serialize(t.numerator());
    ar.do_serialize(t.denominator());
}
template <typename Archive, typename Rational>
static void serialize_rational_load(Archive& ar, Rational& t)
{
    typename Rational::int_type num{};
    typename Rational::int_type den{};
    ar.do_serialize(num);
    ar.do_serialize(den);
    t = Rational(num, den);
}

// обработка uuid
template <typename Archive>
static void serialize_uuid_save(Archive& ar, const boost::uuids::uuid& t)
{
    for (unsigned int i = 0; i < t.size(); i++)
    {
        ar.do_serialize(t.data[i]);
    }
}
//для обработки array типов
template <typename Archive, typename Array>
static void serialize_array_save(Archive& ar, Array& t)
{
    for (const auto& e : t)
    {
        ar.do_serialize(e);
    }
}

template <typename Archive, typename Array>
static void serialize_array_load(Archive& ar, Array& t)
{
    for (auto& e : t)
    {
        ar.do_serialize(e);
    }
}

template <typename Archive>
static void serialize_uuid_load(Archive& ar, boost::uuids::uuid& t)
{
    for (unsigned int i = 0; i < t.size(); i++)
    {
        ar.do_serialize(t.data[i]);
    }
}


}  // namespace serializer::detail
