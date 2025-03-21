#pragma once
#include <cmath>
#include <algorithm>
#include "degree.hpp"

namespace earth_math
{
/**
    * \brief Класс функционала для градусов по модулю
    */
template <size_t ModDegree>
class module_functional : public abstract_functional
{
protected:
    static int64_t normalize(int64_t value);
    static bool less_cmp(int64_t value1, int64_t value2);
    static bool greater_cmp(int64_t value1, int64_t value2);
    static void double_value_validate(double value);
    static void seconds_value_validate(int32_t seconds);
    static void milliseconds_value_validate(int64_t milliseconds);
    static void all_values_validate(int32_t degrees, int32_t minutes,
                                    int32_t seconds = 0,
                                    int32_t milliseconds = 0);
    template <typename C>
    static void type_check();
};

/**
* \brief Нормализация градусов в диапазон от 0..ModDegree градусов в
* милисекундах
* \param value Значение до нормализации
* \return Нормализованное значение
*/
template <size_t ModDegree>
int64_t module_functional<ModDegree>::normalize(int64_t value)
{
    const auto degree_in_milisec = int64_t(ModDegree) * minutes_in_degrees
                                   * seconds_in_minute * milli_in_second;
    int sign = 1;
    if (value < 0)
        sign = -1;
    value = abs(value);
    value %= degree_in_milisec;
    value *= sign;
    if (value > degree_in_milisec)
    {
        value -= degree_in_milisec;
    }
    while (value < 0)
    {
        value += degree_in_milisec;
    }
    return value;
}

/**
* \brief Сравнение на меньше произвольных градусов из кольца в милисекундах,
* по минимальному расстоянию до 0
* \param value1 Милисекнды первых градусов
* \param value2 Милисекнды вторых градусов
* \return true - если первые меньше вторых
*/
template <size_t ModDegree>
bool module_functional<ModDegree>::less_cmp(int64_t value1, int64_t value2)
{
    const auto degree_in_milisec = int64_t(ModDegree) * minutes_in_degrees
                                   * seconds_in_minute * milli_in_second;
    const auto dist1 = std::min(value1, degree_in_milisec - value1);
    const auto dist2 = std::min(value2, degree_in_milisec - value2);
    return dist1 < dist2;
}
/**
* \brief Сравнение на больше произвольных градусов из кольца в милисекундах,
* по минимальному расстоянию до 0
* \param value1 Милисекнды первых градусов
* \param value2 Милисекнды вторых градусов
* \return true - если первые меньше вторых
*/
template <size_t ModDegree>
bool module_functional<ModDegree>::greater_cmp(int64_t value1, int64_t value2)
{
    const auto degree_in_milisec = int64_t(ModDegree) * minutes_in_degrees
                                   * seconds_in_minute * milli_in_second;
    const auto dist1 = std::min(value1, degree_in_milisec - value1);
    const auto dist2 = std::min(value2, degree_in_milisec - value2);
    return dist1 > dist2;
}
/**
    * \brief Проверка на корректность градусов в double,
    * для градусов из кольца (диапазон 0..ModGrad).
    * \param value Значение градусов
    */
template <size_t ModDegree>
void module_functional<ModDegree>::double_value_validate(double value)
{
    if ((value < 0) || (value > ModDegree))
        throw inv_input_error("Init double value out of type bound.");
}

template <size_t ModDegree>
void module_functional<ModDegree>::seconds_value_validate(int32_t seconds)
{
    const auto degree_in_sec =
        int64_t(ModDegree) * minutes_in_degrees * seconds_in_minute;
    if ((seconds < 0) || (seconds > degree_in_sec))
        throw inv_input_error("Init seconds value out of type bound.");
}

template <size_t ModDegree>
void module_functional<ModDegree>::milliseconds_value_validate(
    int64_t milliseconds)
{
    const auto degree_in_milisec = int64_t(ModDegree) * minutes_in_degrees
                                   * seconds_in_minute * milli_in_second;
    if ((milliseconds < 0) || (milliseconds > degree_in_milisec))
        throw inv_input_error("Init milliseconds value out of type bound.");
}

/**
    * \brief Проверка на корректность градусов из кольца в формате:
    * градусы, минуты, секунды, милисекунды
    * \param degrees Значение градусов от 0 до ModGrad
    * \param minutes Значение минут от 0 до 59
    * \param seconds Значение секунд от 0 до 59
    * \param milliseconds Значение милисекунд от 0 до 999
    */
template <size_t ModDegree>
void module_functional<ModDegree>::all_values_validate(int32_t degrees,
                                                       int32_t minutes,
                                                       int32_t seconds,
                                                       int32_t milliseconds)
{
    if ((degrees < 0) || (degrees >= ModDegree))
        throw inv_input_error("Init degrees value out of type bound.");
    abstract_functional::all_values_validate(degrees, minutes, seconds,
                                             milliseconds);
}

/**
 * \brief Проверка на совместимые для операций типы.
 * \tparam C
 */
template <size_t ModDegree>
template <typename C>
void module_functional<ModDegree>::type_check()
{
    static_assert(std::is_same<C, module_functional<ModDegree>>::value
                      || std::is_same<C, abstract_functional>::value,
                  "Impossible operation on Module Degrees");
}

}  // namespace earth_math
