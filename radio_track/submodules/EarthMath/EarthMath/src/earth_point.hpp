#ifndef EARTHPOINT_H
#define EARTHPOINT_H
#include "degree.hpp"

namespace earth_math
{
    /**
     * \brief Класс координатной точки на поверхности земли
     */
    class earth_point
    {
    public:
        earth_point() noexcept;
        earth_point(const earth_point&) = default;
        earth_point(earth_point&&) noexcept = default ;
        earth_point(degree_latitude latitude, degree_longitude longitude);
        earth_point(double latitude_in_double, double longitude_in_double);
        earth_point(int32_t latitude_in_seconds, int32_t longitude_in_seconds);
        earth_point(int64_t latitude_in_milliseconds,
            int64_t longitude_in_milliseconds);
        
        degree_latitude latitude() const;
        degree_longitude longitude() const;

        void set_latitude(degree_latitude latitude);
        void set_longitude(degree_longitude longitude);

        earth_point & operator = (earth_point &&point) noexcept = default;
        earth_point & operator = (const earth_point &point) = default;
        bool operator==(const earth_point & point) const;

        std::string to_string(display_formats display_format = show_minutes) const;

    	bool is_valid() const;
    	
        ~earth_point();
    private:
        degree_latitude latitude_;
        degree_longitude longitude_;
    };

    /**
     * \brief Конструктор по умолчанию
     */
    inline earth_point::earth_point() noexcept: latitude_{}, longitude_{}
    {
    }
    /**
     * \brief Конструктор по долготе и широте
     * \param latitude широта
     * \param longitude долгота
     */
    inline earth_point::earth_point(
        degree_latitude latitude, degree_longitude longitude)
        : latitude_(latitude)
        , longitude_(longitude)
    {
    }

    /**
     * \brief Конструктор по долготе и широте
     * \param latitude_in_double широта в double
     * \param longitude_in_double долгота в double
     */
    inline earth_point::earth_point(
        double latitude_in_double, double longitude_in_double)
        : latitude_(degree_latitude::from_degree(latitude_in_double))
        , longitude_(degree_longitude::from_degree(longitude_in_double))
    {
    }

    /**
     * \brief Конструктор по долготе и широте
     * \param latitude_in_seconds широта в секундах
     * \param longitude_in_seconds долгота в секундах
     */
    inline earth_point::earth_point(
        int32_t latitude_in_seconds, int32_t longitude_in_seconds)
        : latitude_(degree_latitude::from_seconds(latitude_in_seconds))
        , longitude_(degree_longitude::from_seconds(longitude_in_seconds))
    {
    }

    /**
     * \brief Конструктор по долготе и широте
     * \param latitude_in_milliseconds широта в милисекундах
     * \param longitude_in_milliseconds долгота в милисекундах
     */
    inline earth_point::earth_point(
        int64_t latitude_in_milliseconds, int64_t longitude_in_milliseconds)
        : latitude_(degree_latitude::from_milliseconds(latitude_in_milliseconds))
        , longitude_(
			degree_longitude::from_milliseconds(longitude_in_milliseconds))
    {
    }

    /**
     * \brief значение широты
     * \return значение широты
     */
    inline degree_latitude earth_point::latitude() const
    {
        return latitude_;
    }

    /**
     * \brief значение долготы
     * \return значение долготы
     */
    inline degree_longitude earth_point::longitude() const
    {
        return longitude_;
    }

    /**
     * \brief Метод изменения значения широты
     * \param latitude новое значение широты
     */
    inline void earth_point::set_latitude(degree_latitude latitude)
    {
        latitude_ = latitude;
    }

    /**
    * \brief Метод изменения значения долготы
    * \param longitude новое значение долготы
    */
    inline void earth_point::set_longitude(degree_longitude longitude)
    {
        longitude_ = longitude;
    }

    /**
     * \brief Сравнение двух точек на равенство
     * \param point Точка для сравнения
     * \return true - если щирота и долгота равны до милисекунды
     */
    inline bool earth_point::operator==(const earth_point& point) const
    {
        return (latitude_ == point.latitude())
            && (longitude_ == point.longitude());
    }

    /**
     * \brief Преобразование точки в строку
     * \param display_format формат подробности вывода координат
     * \return Текстовое представление точки
     */
    inline std::string earth_point::to_string(
        display_formats display_format) const
    {
        std::string result = latitude_.to_string(display_format) + " "
            + longitude_.to_string(display_format);
        return result;
    }

    /**
     * \brief Проверка, что точка инициализирована
     * \return true - инициализирована
	 * \return false - не инициализирована
     */
	inline bool earth_point::is_valid() const
	{
        return (latitude_.is_valid() && longitude_.is_valid());
	}

	
    /**
     * \brief Деструктор класса
     */
    inline earth_point::~earth_point()
    {
    }
}
#endif
