#pragma once

#include <vector>
#include <list>
#include <exception>
#include <map>
#include <unordered_map>
#include <cstdint>
#include <optional>
#include <variant>
#include <cstring>
#include <array>
#include <cstring>
#include <serializer_cxx17.hpp>
#include <serializer_traits.hpp>
#include <serializer_detail.hpp>

/*
    Класс сериализации.
    1. Простые типы записываются последовательно в соответствии с их размерами.
    2. Для стандартных контейнеров сначала записывается число элементов(uint32), затем 
        записываются сами элементы. Строки записываются так-же.
    3. Для простых массивов просто записыываются элементы без указания размера.
    4. Сложные типы записываются в следущем порядке:
        - число элементов структуры(uint32)
        - размер элемента в байтах (uint32)
        - данные элемента
*/

namespace serializer
{
//класс для чтения объектов из потока байт в памяти
class memory_istream
{
public:
    memory_istream(const void* data, size_t size)
        : data(static_cast<const uint8_t*>(data))
        , size(size)
        , pos(0)
    {
    }
    template <typename T>
    inline void process(T& t)
    {
        if (size - pos < sizeof(T))
        {
            //если достигла конца - пропускаем байты
            pos = size;
        }
        else
        {
            std::memcpy(&t, data + pos, sizeof(T));
            pos += sizeof(T);
        }
    }
    enum : bool
    {
        is_saving = false,
        is_loading = true
    };

private:
    const uint8_t* data;
    size_t size;
    size_t pos;
};
//класс для чтения объектов из массива в векторе
template <typename Vector>
class vector_istream : public memory_istream
{
public:
    vector_istream(const Vector& v)
        : memory_istream(v.data(), v.size())
    {
        static_assert(sizeof(typename Vector::value_type) == 1,
                      "Invalid vector element size");
    }
};
//класс для записи объектов в вектор
template <typename Vector>
class vector_ostream
{
public:
    vector_ostream(Vector& v)
        : v(v)
    {
        static_assert(sizeof(typename Vector::value_type) == 1,
                      "Invalid vector element size");
    }
    template <typename T>
    inline void process(const T& t)
    {
        size_t old_size = v.size();
        v.resize(old_size + sizeof(T));
        std::memcpy(v.data() + old_size, &t, sizeof(T));
    }
    enum : bool
    {
        is_saving = true,
        is_loading = false
    };

private:
    Vector& v;
};

class size_calculator
{
public:
    size_calculator(uint32_t& size)
        : size(size)
    {
    }
    template <typename T>
    inline void process(const T&)
    {
        size += sizeof(T);
    }
    enum : bool
    {
        is_saving = true,
        is_loading = false
    };

private:
    uint32_t& size;
};



class child_counter
{
public:
    child_counter(uint32_t& child_count)
        : child_count(child_count)
    {
    }
    template <typename T>
    void do_serialize(T&)
    {
        ++child_count;
    }

private:
    uint32_t& child_count;
};

template <typename Archive>
class archive_limited
{
public:
    archive_limited(uint32_t& count_limit, Archive& archive)
        : count_limit(count_limit)
        , archive(archive)
    {
    }

    template <typename T>
    void do_serialize(T& t)
    {
        if (count_limit == 0)
            return;  // попытка десериализовать больше полей, чем было сериализовано
        uint32_t current_size = 0;
        if (Archive::is_saving)
        {
            current_size = detail::serializable_size(t);
        }
        archive.do_serialize(current_size);
        archive.do_serialize(t);
        --count_limit;
    }

private:
    uint32_t& count_limit;
    Archive& archive;
};

template <typename Base>
class archive_versioned : public Base
{
public:
    template <typename... Args>
    archive_versioned(Args&&... args)
        : Base(std::forward<Args>(args)...)
    {
    }

    template <typename T>
    void do_serialize(T&& t)
    {
        do_serialize(*this, t);
    }

private:
    //простые массивы
    template <typename Archive, typename T, size_t N>
    void do_serialize(Archive& ar, T (&t)[N])
    {
        for (auto& elem : t) ar.do_serialize(elem);
    }
    template <typename Archive, typename T>
    void do_serialize(Archive& ar, T& t)
    {
        if constexpr (traits::is_simple_v<T>)
        {
            //для простых типов - запись напраямую
            ar.process(t);
        }
        else if constexpr (traits::is_container_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_container_save(ar, t);
            else
                detail::serialize_container_load(ar, t);
        }
        else if constexpr (traits::is_map_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_map_save(ar, t);
            else
                detail::serialize_map_load(ar, t);
        }
        else if constexpr (traits::is_set_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_set_save(ar, t);
            else
                detail::serialize_set_load(ar, t);
        }
        else if constexpr (traits::is_optional_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_optional_save(ar, t);
            else
                detail::serialize_optional_load(ar, t);
        }
        else if constexpr (traits::is_variant_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_variant_save(ar, t);
            else
                detail::serialize_variant_load(ar, t);
        }
        else if constexpr (traits::is_rational_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_rational_save(ar, t);
            else
                detail::serialize_rational_load(ar, t);
        }
        else if constexpr (traits::is_uuid_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_uuid_save(ar, t);
            else
                detail::serialize_uuid_load(ar, t);
        }
        else if constexpr (traits::is_array_v<T>)
        {
            if constexpr (Base::is_saving)
                detail::serialize_array_save(ar, t);
            else
                detail::serialize_array_load(ar, t);
        }
        else if constexpr (traits::is_pair_v<T>)
        {
            static_assert(sizeof(T) == 0, "unsupported type");
        }
        else if constexpr (traits::is_tuple_v<T>)
        {
            static_assert(sizeof(T) == 0, "unsupported type");
        }
        else
        {
            serialize_external(ar, t);
        }
    }
};

namespace detail
{
template <typename T>
uint32_t serializable_size(T& t)
{
    uint32_t size = 0;
    archive_versioned<size_calculator> calc_archive(size);
    serialize(calc_archive, t);
    return size;
}
}  // namespace detail
template <typename Archive, typename T>
void serialize_external(Archive& ar, T& t)
{
    //для сложных типов (сериализуемых структур) запускаем рекурсию
    uint32_t child_count = 0;
    if (Archive::is_saving)
    {
        serialize_internal(child_counter(child_count), t);
    }
    ar.do_serialize(
        child_count);  //при десереализации заполняем поле
    serialize_internal(
        archive_limited<Archive>(child_count, ar), t);
    if (Archive::is_loading)
    {
        //неизвестные поля, пропускаем
        while (child_count--)
        {
            uint32_t child_size = 0;
            ar.do_serialize(child_size);
            detail::skip_bytes(ar, child_size);
        }
    }
}

template <typename Archive, typename T>
void serialize_internal(Archive&& ar, T& t)
{
    detail::visit(
        t, [&ar](auto& obj)
        {
            ar.do_serialize(obj);
        });
}

template <typename T, typename C>
void visit(T&& t, C&& cb)
{
    detail::visit(std::forward<T>(t), std::forward<C>(cb));
}

typedef archive_versioned<vector_ostream<std::vector<char>>>
    vector_ostream_archive;
typedef archive_versioned<vector_istream<std::vector<char>>>
    vector_istream_archive;
typedef archive_versioned<memory_istream> memory_istream_archive;

//главная функция сериализации
template <typename Archive, typename T>
void serialize(Archive&& ar, T&& t)
{
    ar.do_serialize(t);
}

}  // namespace serializer
