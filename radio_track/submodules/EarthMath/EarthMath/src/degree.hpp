#pragma once
#include <string>
#include <type_traits>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include "em_exception.hpp"

namespace earth_math
{
class abstract_functional;
class latitude_functional;
class longitude_functional;
/**
     * \brief Точность отображения градусов
     */
using display_formats = enum
{
    only_degrees,
    show_minutes,
    show_seconds,
    show_milliseconds
};

static void get_degree_params(int64_t value, int32_t* degrees, int32_t* minutes,
                              int32_t* seconds, int32_t* milliseconds,
                              int32_t* sign);

const int32_t milli_in_second = 1000;
const int32_t seconds_in_minute = 60;
const int32_t minutes_in_degrees = 60;
const double pi = 3.1415926535897932384626433832795;
const double eps = 1e-10;
const double one_minute_ = 1. / double(minutes_in_degrees);
const double one_second_ = one_minute_ / double(seconds_in_minute);
const double one_millisecond_ = one_second_ / double(milli_in_second);

/**
     * \brief Шаблонный класс градуса
     * \tparam T Класс функционала для конкретного вида градусов.
     */
template <typename T>
class degree : public T
{
public:
    degree();
    static degree from_seconds(int64_t seconds);
    static degree from_milliseconds(int64_t milliseconds);
    static degree from_degree(double degree_value);
    static degree from_radians(double radians_value);
    degree(const degree<T>& deg);
    degree(degree<T>&& deg) noexcept;
    degree(int32_t degrees, int32_t minutes, int32_t seconds = 0,
           int32_t milliseconds = 0, bool isNegative = false);
    degree& operator=(degree&& deg) noexcept;
    degree& operator=(const degree& deg);
    template <typename C>
    degree<T>& operator+=(degree<C> const& deg);
    template <typename C>
    degree<T>& operator-=(degree<C> const& deg);
    degree<T>& operator*=(double value);
    degree<T>& operator/=(double value);
    template <typename C>
    degree<T> operator+(degree<C> const& deg) const;
    template <typename C>
    degree<T> operator-(degree<C> const& deg) const;
    degree<T> operator*(double value) const;
    degree<T> operator/(double value) const;
    bool operator==(degree<T> const& deg) const;
    bool operator<(degree<T> const& deg) const;
    bool operator>(degree<T> const& deg) const;
    std::string to_string(display_formats display_format = show_minutes) const;
    bool is_valid() const;
    double to_radians() const;
    int64_t to_milliseconds() const;
    int32_t to_seconds() const;
    double to_degree() const;
    friend std::ostream& operator<<(std::ostream& stream, const degree& deg);
    ~degree();

private:
    int64_t value_;
    bool valid;
    void swap(degree& deg) noexcept;
};

/**
     * \brief Класс функционала для произвольных градусов.
     */
class abstract_functional
{
protected:
    static int64_t normalize(int64_t value);
    static std::string to_string(int64_t value,
                                 display_formats display_format = show_minutes);
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
    ;
};

/**
     * \brief Класс функционала для градусов широты
     */
class latitude_functional : public abstract_functional
{
protected:
    static int64_t normalize(int64_t value);
    static std::string to_string(int64_t value,
                                 display_formats display_format = show_minutes);
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
    ;
};

/**
    * \brief Класс функционала для градусов долготы
    */
class longitude_functional : public abstract_functional
{
protected:
    static int64_t normalize(int64_t value);
    static std::string to_string(int64_t value,
                                 display_formats display_format = show_minutes);
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
    ;
};

inline std::ostream& operator<<(std::ostream& stream,
                                const degree<abstract_functional>& deg)
{
    stream << deg.to_string();
    return stream;
}
inline std::ostream& operator<<(std::ostream& stream,
                                const degree<latitude_functional>& deg)
{
    stream << deg.to_string();
    return stream;
}
inline std::ostream& operator<<(std::ostream& stream,
                                const degree<longitude_functional>& deg)
{
    stream << deg.to_string();
    return stream;
}

/**
     * \typedef degree_abstract
     * \brief Произвольные градусы
     */
using degree_abstract = degree<abstract_functional>;

/**
    * \typedef degree_latitude
    * \brief Градусы широты
    */
using degree_latitude = degree<latitude_functional>;

/**
    * \typedef degree_longitude
    * \brief Градусы долготы
    */
using degree_longitude = degree<longitude_functional>;

/**

     * \brief Конструктор с невалидным значением
     */
template <typename T>
degree<T>::degree()
    : value_(0)
    , valid(false)
{
}

/**
	 * \brief Создание экземпляра класса градус из секунд
	 * \param seconds градусы в секундах
	 * \return Созданный экземпляр
	 */
template <typename T>
inline degree<T> degree<T>::from_seconds(int64_t seconds)
{
    degree result;
    result.value_ = seconds * milli_in_second;
    result.valid = true;
    T::seconds_value_validate(int32_t(seconds));
    return result;
}

/**
	 * \brief Создание экземпляра класса градус из милисекунд
	 * \param milliseconds градусы в милисекундах
	 * \return Созданный экземпляр
	 */
template <typename T>
inline degree<T> degree<T>::from_milliseconds(int64_t milliseconds)
{
    degree result;
    result.value_ = milliseconds;
    result.valid = true;
    T::milliseconds_value_validate(milliseconds);
    return result;
}

/**
	 * \brief Создание экземпляра класса градус из градусов в double
	 * \param degree_value Значение в градусах в double
	 * \return Созданный экземпляр
	 */
template <typename T>
degree<T> degree<T>::from_degree(double degree_value)
{
    degree result;
    result.valid = true;
    T::double_value_validate(degree_value);
    int32_t sign;
    if (degree_value < -eps)
        sign = -1;
    else
        sign = 1;
    degree_value = fabs(degree_value);
    result.value_ =
        sign * (int64_t((degree_value + eps) / one_millisecond_ + eps));
    return result;
}

/**
    * \brief Конструктор копирования.
    * \param deg Копируемое значение
    */
template <typename T>
degree<T>::degree(const degree<T>& deg)
    : value_(deg.value_)
    , valid(deg.valid)
{
}

/**
     * \brief Конструктор пермещения
     * \param deg Перемещаемое значение
     */
template <typename T>
degree<T>::degree(degree<T>&& deg) noexcept
    : value_(std::move(deg.value_))
    , valid(std::move(deg.valid))
{
    deg.value_ = 0;
    deg.valid = false;
}

/**
     * \brief Конструктор градусов, все параметры должны иметь положительные
     * значения,
     * прочая корректность проверяется в соответствии с шаблонным типом.
     * \param degrees целое, положительное число градусов
     * \param minutes целое, положительное число минут не превосходящее 59
     * \param seconds целое, положительное число секунд не превосходящее 59
     * \param milliseconds целое, положительное число милисекунд не превосходящее
     * 1000
     * \param is_negative флаг отрицательных градусов, true значения будут
     * приниматься
     *  как отрицательные, по-умолчанию имеет значение false положительные
     */
template <typename T>
degree<T>::degree(int32_t degrees, int32_t minutes, int32_t seconds,
                  int32_t milliseconds, bool is_negative)
    : valid(true)
{
    T::all_values_validate(degrees, minutes, seconds, milliseconds);
    int64_t value = degrees;
    value = value * minutes_in_degrees + minutes;
    value = value * seconds_in_minute + seconds;
    value = value * milli_in_second + milliseconds;
    if (is_negative)
        value = -value;
    value_ = value;
}

/**
     * \brief Перегруженный оператор присваивания-перемещения
     * \param deg Перемещяемый экземпляр
     * \return Новый экзепляр
     */
template <typename T>
degree<T>& degree<T>::operator=(degree&& deg) noexcept
{
    assert(this != &deg);
    value_ = std::move(deg.value_);
    valid = std::move(deg.valid);
    deg.value_ = 0;
    deg.valid = false;
    return *this;
}

/**
     * \brief Перегруженный оператор присваивания
     * \param deg Значение произвольных градусов
     * \return Ссылка на экземпляр с такими же значениями
     */
template <typename T>
degree<T>& degree<T>::operator=(const degree& deg)
{
    if (this != &deg)
    {
        degree(deg).swap(*this);
    }
    return *this;
}

/**
    * \brief Перегруженный оператор +=, с нормированием,
    *  в соотвествии с шаблонным типом.
    * \param deg Значение добавляемых градусов
    * \return Ссылка на экземпляр с результирующим значением
    */
template <typename T>
template <typename C>
degree<T>& degree<T>::operator+=(degree<C> const& deg)
{
    T::template type_check<C>();
    value_ += deg.to_milliseconds();
    value_ = T::normalize(value_);
    return *this;
}

/**
    * \brief Перегруженный оператор -=, с нормированием,
    *  в соотвествии с шаблонным типом.
    * \param deg Значение убавляемых градусов
    * \return Ссылка на экземпляр с результирующим значением
    */
template <typename T>
template <typename C>
degree<T>& degree<T>::operator-=(degree<C> const& deg)
{
    T::template type_check<C>();
    value_ -= deg.to_milliseconds();
    value_ = T::normalize(value_);
    return *this;
}

/**
     * \brief Перегруженный оператор *= на double, c нормированием,
     * в соотвествии с шаблонным типом
     * \param value Вещественное значение, на которое происходит умножение
     * \return Ссылка на экземпляр с результирующим значением
     */
template <typename T>
degree<T>& degree<T>::operator*=(double value)
{
    value_ = int64_t(double(value_) * value);
    value_ = T::normalize(value_);
    return *this;
}

/**
    * \brief Перегруженный оператор /= на double, c нормированием,
    * в соотвествии с шаблонным типом
    * \param value Вещественное значение, на которое происходит деление
    * \return Ссылка на экземпляр с результирующим значением
    */
template <typename T>
degree<T>& degree<T>::operator/=(double value)
{
    value_ = int64_t(double(value_) / value);
    value_ = T::normalize(value_);
    return *this;
}

/**
    * \brief Перегруженный оператор +, с нормированием,
    * в соответсвии с шаблонным типом
    * \param deg Значение добавляемых градусов
    * \return Экземпляр с результирующим значением
    */
template <typename T>
template <typename C>
degree<T> degree<T>::operator+(degree<C> const& deg) const
{
    T::template type_check<C>();
    degree result = from_milliseconds(value_);
    result += deg;
    return result;
}

/**
    * \brief Перегруженный оператор -, с нормированием,
    * в соответсвии с шаблонным типом
    * \param deg Значение вычитаемых градусов
    * \return Экземпляр с результирующим значением
    */
template <typename T>
template <typename C>
degree<T> degree<T>::operator-(degree<C> const& deg) const
{
    T::template type_check<C>();
    degree result = from_milliseconds(value_);
    result -= deg;
    return result;
}

/**
     * \brief Перегруженный оператор * на double, с нормированием,
     * в соответсвии с шаблонным типом
     * \param value Вещественное значение, на которое происходит умножение
     * \return Экземпляр с результирующим значением
     */
template <typename T>
degree<T> degree<T>::operator*(double value) const
{
    degree result = from_milliseconds(value_);
    result *= value;
    return result;
}

/**
    * \brief Перегруженный оператор / на double, с нормированием,
    * в соответсвии с шаблонным типом
    * \param value Вещественное значение, на которое происходит деление
    * \return Экземпляр с результирующим значением
    */
template <typename T>
degree<T> degree<T>::operator/(double value) const
{
    degree result = from_milliseconds(value_);
    result /= value;
    return result;
}

/**
     * \brief Перегруженный оператор проверки на равенство,
     * с учётом нормирования, в соответсвии с шаблонным типом,
     * т.е. для широты 5 и 175 одно и тоже
     * \param deg градусы с которыми происходит сравнение
     * \return результат сравнение
     */
template <typename T>
bool degree<T>::operator==(degree<T> const& deg) const
{
    int64_t deg_norm_value = T::normalize(deg.to_milliseconds());
    return value_ == deg_norm_value;
}

/**
     * \brief Перегрузка оператора <. Меньше в зависимости от типа данных.
     * \param deg Второй операнд сравнения градусов
     * \return Результат сравнения, true если меньше.
     */
template <typename T>
bool degree<T>::operator<(degree<T> const& deg) const
{
    return T::less_cmp(this->value_, deg.to_milliseconds());
}

/**
    * \brief Перегрузка оператора >. Больше в зависимости от типа данных.
    * \param deg Второй операнд сравнения градусов
    * \return Результат сравнения, true если больше.
    */
template <typename T>
bool degree<T>::operator>(degree<T> const& deg) const
{
    return T::greater_cmp(this->value_, deg.to_milliseconds());
}

/**
     * \brief  Преобразование градусов в строку
     * \param display_format формат вывода градусов
     * \return Получившаяся строка
     */
template <typename T>
std::string degree<T>::to_string(display_formats display_format) const
{
    return T::to_string(value_, display_format);
}

/**
     * \brief Возвращет значение инициализирован ли экземпляр градусов
     * \return false - не инициализирован, true - инициализирован
     */
template <typename T>
bool degree<T>::is_valid() const
{
    return valid;
}

/**
     * \brief Перевод значения градусов в радианы
     * \return Значение в радианах
     */
template <typename T>
double degree<T>::to_radians() const
{
    return value_ * one_millisecond_ * pi / 180.;
}

/**
	* \brief Перевод значения градусов в милисекунды
	* \return Значение в милисекундах
	*/
template <typename T>
int64_t degree<T>::to_milliseconds() const
{
    return value_;
}

/**
	* \brief Перевод значения градусов в секунды
	* \return Значение в секундах
	*/
template <typename T>
int32_t degree<T>::to_seconds() const
{
    return int32_t(value_ / milli_in_second);
}

/**
     * \brief Преобразование в градусы из радианов
     * \param radians_value Значение в радианах
     * \return Значение в градусах
     */
template <typename T>
inline degree<T> degree<T>::from_radians(double radians_value)
{
    double v = radians_value * 180. / pi;
    return from_degree(v);
}

/**
     * \brief Перевод значения градусов в double
     * \return Значение градусов в double
     */
template <typename T>
double degree<T>::to_degree() const
{
    return value_ * one_millisecond_;
}

/**
     * \brief Деструктор класса градусов
     */
template <typename T>
degree<T>::~degree()
{
}

/**
     * \brief Операция обмена значений с другим классом градусов
     * \param deg Градус, с которым происходит обмен знаечниями
     */
template <typename T>
void degree<T>::swap(degree& deg) noexcept
{
    std::swap(this->value_, deg.value_);
    std::swap(this->valid, deg.valid);
}

/**
    * \brief Проверка типа для доступности арифметических операций
    * \tparam C Проверяемый тип
    */
template <typename C>
void abstract_functional::type_check()
{
}
/**
    * \brief Проверка типа для доступности арифметических операций для широты
    * \tparam C Проверяемый тип
    */
template <typename C>
void latitude_functional::type_check()
{
    static_assert(std::is_same<C, latitude_functional>::value
                      || std::is_same<C, abstract_functional>::value,
                  "Impossible operation on Latitude and Longitude");
}

/**
    * \brief Проверка типа для доступности арифметических операций для долготы
    * \tparam C Проверяемый тип
    */
template <typename C>
void longitude_functional::type_check()
{
    static_assert(std::is_same<C, longitude_functional>::value
                      || std::is_same<C, abstract_functional>::value,
                  "Impossible operation on Latitude and Longitude");
}

/**
     * \brief Функция преобразования милисекунд в формат градусы,
     * минуты, секунды, миллисекунды
     * \param value Градусы в милисекундах
     * \param degrees Градусы
     * \param minutes Минуты
     * \param seconds Секунды
     * \param milliseconds Милисекунды
     * \param sign Знак -1 или 1
     */
void get_degree_params(int64_t value, int32_t* degrees, int32_t* minutes,
                       int32_t* seconds, int32_t* milliseconds, int32_t* sign)
{
    if (value != 0)
        *sign = int32_t(value / abs(value));
    else
        *sign = 1;
    value = abs(value);
    *milliseconds = int32_t(value % milli_in_second);
    value /= milli_in_second;
    *seconds = int32_t(value % seconds_in_minute);
    value /= seconds_in_minute;
    *minutes = int32_t(value % minutes_in_degrees);
    value /= minutes_in_degrees;
    *degrees = int32_t(value);
}

/**
    * \brief Нормализация градусов, для произвольных градусов нормализации как
    * таковой нет.
    * \param value Значение нормализации
    * \return Нормализованное значение
    */
inline int64_t abstract_functional::normalize(int64_t value)
{
    return value;
}

/**
    * \brief Преобразование значения милисекунд в строку
    * \param value Количесвто милисеккунд
    * \param display_format Формат вывода,
    * по умолчанию вывод только градусов и минут
    * \return Строка с количеством градусов
    */
inline std::string abstract_functional::to_string(
    int64_t value, display_formats display_format)
{
    int32_t d, m, s, ms, sign;
    get_degree_params(value, &d, &m, &s, &ms, &sign);
    std::stringstream res;
    if (sign == -1)
        res << "-";
    switch (display_format)
    {
        case only_degrees:
            res << d << "\xC2\xB0";
            break;
        case show_minutes:
            res << d << "\xC2\xB0 " << std::setw(2) << std::setfill('0') << m
                << "'";
            break;
        case show_seconds:
            res << d << "\xC2\xB0 " << std::setw(2) << std::setfill('0') << m
                << "' " << std::setw(2) << std::setfill('0') << s << "''";
            break;
        case show_milliseconds:
            res << d << "\xC2\xB0 " << std::setw(2) << std::setfill('0') << m
                << "' " << std::setw(2) << std::setfill('0') << s << "'' "
                << std::setw(3) << std::setfill('0') << ms << "'''";
            break;
        default:
            break;
    }
    return res.str();
}

/**
    * \brief Сравнение на меньше произвольных градусов в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return true - если первые меньше вторых
    */
inline bool abstract_functional::less_cmp(int64_t value1, int64_t value2)
{
    return value1 < value2;
}

/**
    * \brief Сравнение на больше произвольных градусов в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return true - если первые больше вторых
    */
inline bool abstract_functional::greater_cmp(int64_t value1, int64_t value2)
{
    return value1 > value2;
}

/**
    * \brief Проверка на корректность градусов в double,
    * для произвольных градусов не осуществляется.
    * \param value Значение градусов
    */
inline void abstract_functional::double_value_validate(double value) {}

/**
    * \brief Проверка на корректность градусов в секундах,
    * для произвольных градусов не осуществляется.
    * \param seconds Значение градусов
    */
inline void abstract_functional::seconds_value_validate(int32_t seconds) {}

/**
    * \brief Проверка на корректность градусов в милисекундах,
    * для произвольных градусов не осуществляется.
    * \param milliseconds Значение градусов
    */
inline void abstract_functional::milliseconds_value_validate(
    int64_t milliseconds)
{
}

/**
    * \brief Проверка на корректность градусов в формате:
    * градусы, минуты, секунды, милисекунды
    * \param degrees Значение градусов, может быть произвольным
    * \param minutes Значение минут от 0 до 59
    * \param seconds Значение секунд от 0 до 59
    * \param milliseconds Значение милисекунд от 0 до 999
    */
inline void abstract_functional::all_values_validate(int32_t degrees,
                                                     int32_t minutes,
                                                     int32_t seconds,
                                                     int32_t milliseconds)
{
    if (minutes < 0)
        throw inv_input_error("Minutes can't be negative.");
    if (seconds < 0)
        throw inv_input_error("Seconds can't be negative.");
    if (milliseconds < 0)
        throw inv_input_error("milliseconds can't be negative.");
    if (minutes >= minutes_in_degrees)
        throw inv_input_error("Minutes can't be greater than "
                              + std::to_string(minutes_in_degrees - 1) + ".");
    if (seconds >= seconds_in_minute)
        throw inv_input_error("Seconds can't be greater than "
                              + std::to_string(seconds_in_minute - 1) + ".");
    if (milliseconds >= milli_in_second)
        throw inv_input_error("milliseconds can't be greater than "
                              + std::to_string(milli_in_second - 1) + ".");
}

/**
     * \brief Нормализация градусов широты, значения -90..90
     * градусов в милисекундах
     * \param value Значение до нормализации
     * \return Нормализованное значение
     */
inline int64_t latitude_functional::normalize(int64_t value)
{
    int32_t sign;
    value < 0 ? sign = -1 : sign = 1;
    value = abs(value);
    int64_t degr360 = (int64_t(360) * minutes_in_degrees * seconds_in_minute
                       * milli_in_second);
    int64_t degr180 = degr360 / 2;
    int64_t degr90 = degr360 / 4;
    value %= degr360;
    if (value > degr180)
    {
        sign *= -1;
        value -= degr180;
    }
    if (value > degr90)
        value = degr180 - value;
    return sign * value;
}

/**
    * \brief Преобразование значения милисекунд в строку
    * \param value Количесвто милисеккунд
    * \param display_format Формат вывода,
    * по умолчанию вывод только градусов и минут
    * \return Строка с количеством градусов c указанием ю.ш. или с.ш
    */
inline std::string latitude_functional::to_string(
    int64_t value, display_formats display_format)
{
    std::string res = abstract_functional::to_string(value, display_format);
    if (value != 0)
    {
        if (res[0] == '-')
            res = res.substr(1, res.length() - 1) + " ю.ш.";
        else
            res += " с.ш.";
    }
    return res;
}

/**
    * \brief Сравнение на меньше градусов широты в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return Меньше тот, кто лежит ближе к 0
    */
inline bool latitude_functional::less_cmp(int64_t value1, int64_t value2)
{
    value1 = abs(value1);
    value2 = abs(value2);
    return value1 < value2;
}

/**
    * \brief Сравнение на больше градусов широты в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return Меньше тот, кто лежит дальше от 0
    */
inline bool latitude_functional::greater_cmp(int64_t value1, int64_t value2)
{
    value1 = abs(value1);
    value2 = abs(value2);
    return value1 > value2;
}

/**
    * \brief Проверка на корректность градусов широты в double,
    * градусы должны лежать на интервале -90..90.
    * \param value Значение градусов
    */
inline void latitude_functional::double_value_validate(double value)
{
    if ((value < -90.) || (value > 90.))
        throw inv_input_error("Latitude double value must be in -90..90.");
}

/**
    * \brief Проверка на корректность градусов широты в секундах,
    * градусы должны лежать на интервале -90..90.
    * \param seconds Значение градусов
    */
inline void latitude_functional::seconds_value_validate(int32_t seconds)
{
    if ((seconds < -90 * minutes_in_degrees * seconds_in_minute)
        || (seconds > 90 * minutes_in_degrees * seconds_in_minute))
        throw inv_input_error("Latitude second value must be in -90..90.");
}

/**
    * \brief Проверка на корректность градусов широты в милисекундах,
    * градусы должны лежать на интервале -90..90.
    * \param milliseconds Значение градусов
    */
inline void latitude_functional::milliseconds_value_validate(
    int64_t milliseconds)
{
    int64_t limit_value =
        int64_t(90) * minutes_in_degrees * seconds_in_minute * milli_in_second;
    if ((milliseconds < -limit_value) || (milliseconds > limit_value))
        throw inv_input_error("Latitude value must be in -90..90.");
}

/**
    * \brief Проверка на корректность градусов широты в формате:
    * градусы, минуты, секунды, милисекунды
    * \param degrees Значение градусов от -90 до 90
    * \param minutes Значение минут от 0 до 59
    * \param seconds Значение секунд от 0 до 59
    * \param milliseconds Значение милисекунд от 0 до 999
    */
inline void latitude_functional::all_values_validate(int32_t degrees,
                                                     int32_t minutes,
                                                     int32_t seconds,
                                                     int32_t milliseconds)
{
    abstract_functional::all_values_validate(degrees, minutes, seconds,
                                             milliseconds);
    int64_t value =
        ((int64_t(degrees) * minutes_in_degrees + minutes) * seconds_in_minute
         + seconds)
            * milli_in_second
        + milliseconds;
    milliseconds_value_validate(value);
}

/**
    * \brief Нормализация градусов долготы, значения -180..180 градусов в
    * милисекундах
    * \param value Значение до нормализации
    * \return Нормализованное значение
    */
inline int64_t longitude_functional::normalize(int64_t value)
{
    int64_t degr360 = (int64_t(360) * minutes_in_degrees * seconds_in_minute
                       * milli_in_second);
    int64_t degr180 = degr360 / 2;
    int sign = 1;
    if (value < 0)
        sign = -1;
    value = abs(value);
    value %= degr360;
    value *= sign;
    while (value > degr180)
    {
        value -= degr360;
    }
    while (value < -degr180)
    {
        value += degr360;
    }
    return value;
}

/**
    * \brief Преобразование значения милисекунд в строку
    * \param value Количесвто милисеккунд
    * \param display_format Формат вывода,
    * по умолчанию вывод только градусов и минут
    * \return Строка с количеством градусов c указанием в.д. или з.д.
    */
inline std::string longitude_functional::to_string(
    int64_t value, display_formats display_format)
{
    std::string res = abstract_functional::to_string(value, display_format);
    if (value != 0)
    {
        if (res[0] == '-')
            res = res.substr(1, res.length() - 1) + " з.д.";
        else
            res += " в.д.";
    }
    return res;
}

/**
    * \brief Сравнение на меньше градусов долготы в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return Меньше тот, кто лежит ближе к 0
    */
inline bool longitude_functional::less_cmp(int64_t value1, int64_t value2)
{
    value1 = abs(value1);
    value2 = abs(value2);
    return value1 < value2;
}

/**
    * \brief Сравнение на больше градусов долготы в милисекундах
    * \param value1 Милисекнды первых градусов
    * \param value2 Милисекнды вторых градусов
    * \return Больше тот, кто лежит дальше от 0
    */
inline bool longitude_functional::greater_cmp(int64_t value1, int64_t value2)
{
    value1 = abs(value1);
    value2 = abs(value2);
    return value1 > value2;
}
/**
    * \brief Проверка на корректность градусов долготы в double,
    * градусы должны лежать на интервале -180..180.
    * \param value Значение градусов
    */
inline void longitude_functional::double_value_validate(double value)
{
    if ((value < -180.) || (value > 180.))
        throw inv_input_error("Longitude double value must be in -180..180.");
}

/**
    * \brief Проверка на корректность градусов долготы в секундах,
    * градусы должны лежать на интервале -180..180.
    * \param seconds Значение градусов
    */
inline void longitude_functional::seconds_value_validate(int32_t seconds)
{
    if ((seconds < -180 * minutes_in_degrees * seconds_in_minute)
        || (seconds > 180 * minutes_in_degrees * seconds_in_minute))
        throw inv_input_error("Latitude second value must be in -180..180.");
}

/**
    * \brief Проверка на корректность градусов долготы в милисекундах,
    * градусы должны лежать на интервале -180..180.
    * \param milliseconds Значение градусов
    */
inline void longitude_functional::milliseconds_value_validate(
    int64_t milliseconds)
{
    int64_t limit_value =
        int64_t(180) * minutes_in_degrees * seconds_in_minute * milli_in_second;
    if ((milliseconds < -limit_value) || (milliseconds > limit_value))
        throw inv_input_error("Latitude value must be in -180..180.");
}

/**
    * \brief Проверка на корректность градусов долготы в формате:
    * градусы, минуты, секунды, милисекунды
    * \param degrees Значение градусов от -180 до 180
    * \param minutes Значение минут от 0 до 59
    * \param seconds Значение секунд от 0 до 59
    * \param milliseconds Значение милисекунд от 0 до 999
    */
inline void longitude_functional::all_values_validate(int32_t degrees,
                                                      int32_t minutes,
                                                      int32_t seconds,
                                                      int32_t milliseconds)
{
    abstract_functional::all_values_validate(degrees, minutes, seconds,
                                             milliseconds);
    int64_t value =
        ((int64_t(degrees) * minutes_in_degrees + minutes) * seconds_in_minute
         + seconds)
            * milli_in_second
        + milliseconds;
    milliseconds_value_validate(value);
}
}  // namespace earth_math
