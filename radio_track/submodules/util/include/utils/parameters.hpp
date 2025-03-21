#pragma once

// (c) Copyright Dmitriy Shikhov 2023

#include <map>
#include <optional>
#include <type_traits>
#include <variant>

namespace utils
{
template <typename IdType, template <IdType> typename IdToValueType,
          typename... ValueTypes>
class parameters
{
public:
    /**
     * \brief Тип идентификатора параметров
     */
    using id_type = IdType;

    /**
     * \brief Тип для хранения значений параметров
     */
    using variant_type = std::variant<ValueTypes...>;

    /**
     * \brief Тип параметра для заданного идентификатора параметра
     * \tparam ParameterId Идентификатор параметра
     */
    template <id_type ParameterId>
    using id_to_value_type = IdToValueType<ParameterId>;

    /**
     * \brief Получить параметр по заданному идентификатору параметра
     * \tparam ParameterId Идентификатор параметра
     */
    template <id_type ParameterId>
    auto get() const -> std::optional<id_to_value_type<ParameterId>>
    {
        if (const auto it = parameters_.find(ParameterId);
            it != parameters_.end())
        {
            return std::get<id_to_value_type<ParameterId>>(it->second);
        }
        return {};
    }

    /**
     * \brief Установить параметр по заданному идентификатору параметра
     * \tparam ParameterId Идентификатор параметра
     * \tparam T Тип параметра
     *  (должен совпадать с id_to_value_type<ParameterId>)
     * \param value Значение параметра
     */
    template <id_type ParameterId, typename T>
    void set(T&& value)
    {
        // Сделано через static_assert, а не через вычисленный
        // тип аргумента функции, чтобы гарантировать максимальную
        // строгость типизации - никаких неявных приведений

        static_assert(
            std::is_same_v<id_to_value_type<ParameterId>,
                           std::remove_cv_t<std::remove_reference_t<T>>>,
            "Parameter type mismatch for this ParameterId. "
            "T must be equal to id_to_value_type<ParameterId>");

        parameters_[ParameterId] = value;
    }

    /**
     * \brief Выполнить заданное действие для каждого параметра
     * \tparam Visitor функтор с типом void(id_type id, auto&& value),
     *  где value может быть одного из заданных в ValueTypes типов
     * \param visitor функтор, который будет вызван для каждого параметра
     */
    template <typename Visitor>
    void for_each(Visitor&& visitor) const
    {
        for (auto const& [id, variant] : parameters_)
        {
            std::visit(
                [id, &visitor](auto const& value)
                {
                    visitor(id, value);
                },
                variant);
        }
    }

private:
    std::map<id_type, variant_type> parameters_;
};

}  // namespace utils
