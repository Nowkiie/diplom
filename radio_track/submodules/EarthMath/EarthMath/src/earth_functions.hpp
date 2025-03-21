#ifndef EARTHFUNCTIONS_H
#define EARTHFUNCTIONS_H
#include <cmath>
#include "earth_point.hpp"
namespace earth_math
{
/**
     * \brief Радиус земли
     */
const double earth_radius = 6371;
/**
     * \brief Функция, возвращающая минимальное расстояние между двумя точками
     * в градусах, погрешности в милисекундах могут возникать на расстоянии 
     * меньшем полсекунды
     * \param a первая точка
     * \param b вторая точка
     * \return расстояние в градусах
     */
static degree_abstract distance(earth_point a, earth_point b)
{
    double res;
    if (a == b)
        res = 0;
    else
    {
        double cos_delta_longitude =
            cos(a.longitude().to_radians() - b.longitude().to_radians());
        double sin_multiply =
            sin(a.latitude().to_radians()) * sin(b.latitude().to_radians());
        double cos_multiply =
            cos(a.latitude().to_radians()) * cos(b.latitude().to_radians());
        res = acos(sin_multiply + cos_multiply * cos_delta_longitude);
    }
    //return degree_abstract{ degree_abstract::from_radians(res)+eps};
    return degree_abstract::from_radians(res);
}

/**
     * \brief Функция, возвращающая минимальное расстояние между двумя точками
     * в километрах
     * \param a первая точка
     * \param b вторая точка
     * \return расстояние в километрах
     */
static double distance_in_km(earth_point a, earth_point b)
{
    return distance(a, b).to_radians() * earth_radius;
}

/**
	 * \brief Функция вычисления азимута от первой точки на вторую
	 * \param from_point Первая точка
	 * \param to_point Вторая точка
	 * \return Значение азимута в диапазоне 0..360
	 */
static degree_abstract azimuth(earth_point from_point, earth_point to_point)
{
    double w1 = from_point.latitude().to_radians();
    double d1 = from_point.longitude().to_radians();
    double w2 = to_point.latitude().to_radians();
    double d2 = to_point.longitude().to_radians();

    double cosab = sin(w1) * sin(w2) + cos(w1) * cos(w2) * cos(d2 - d1);
    double x = sin(d2 - d1) * sin(pi / 2. - w1) * sin(pi / 2. - w2);
    double y = cos(pi / 2. - w2) - cos(pi / 2. - w1) * cosab;
    double az = atan2(x, y);
    if (az < -eps)
        az += pi * 2;
    //return degree_abstract{ degree_abstract::from_radians(az) + eps };
    return degree_abstract::from_radians(az);
}
/**
	 * \brief  Функция вычисления конечной точки по азимуту 
	 * и длине дуги в градусах
	 * \param start_point Начальная точка
	 * \param azimuth Азимут от точки
	 * \param length Длина дуги в градусах
	 * \return Результирующая точка
	 */
static earth_point target_point(earth_point start_point,
                                degree_abstract azimuth, degree_abstract length)
{
    double pa = pi / 2 - start_point.latitude().to_radians();
    double az = azimuth.to_radians();
    double ab = length.to_radians();
    double cospb = cos(pa) * cos(ab) + sin(pa) * sin(ab) * cos(az);
    double pb = acos(cospb);
    earth_point result_point(start_point);
    result_point.set_latitude(
        degree_latitude(degree_latitude::from_radians(pi / 2 - pb)));
    double x = sin(az) * sin(ab) * sin(pa);
    double y = cos(ab) - cos(pa) * cospb;
    double delta_long = atan2(x, y);
    if ((fabs(x) < eps) && (fabs(y) < eps))
        delta_long = 0;
    degree_longitude longitude = result_point.longitude();
    longitude += degree_abstract(degree_abstract::from_radians(delta_long));
    result_point.set_longitude(longitude);
    return result_point;
}
/**
	* \brief  Функция вычисления конечной точки по азимуту
	* и длине дуги в километрах
	* \param start_point Начальная точка
	* \param azimuth Азимут от точки
	* \param kilometres Длина дуги в километрах
	* \return Результирующая точка
	*/
static earth_point target_point(earth_point start_point,
                                degree_abstract azimuth, double kilometres)
{
    return target_point(start_point, azimuth,
                        degree_abstract{degree_abstract::from_radians(
                            kilometres / earth_radius)});
}

/**
	* \brief Функция подсчёта точки пересечения двух пеленгов бин. поиском.
	* \param point_one Точка начала первого пеленга
	* \param azimuth_one Азимут из первой точки
	* \param point_two Точка начала второго пеленга
	* \param azimuth_two Азимут из второй точки
	* \param result_point Точка пересечения пеленгов
	* \return Существует ли точка пересечения пеленгов
	 */
static bool peleng_intersection(earth_point point_one,
                                degree_abstract azimuth_one,
                                earth_point point_two,
                                degree_abstract azimuth_two,
                                earth_point* result_point)
{
    auto diametr_point_one =
        target_point(point_one, azimuth_one, degree_abstract::from_degree(180));
    auto point_one_90 =
        target_point(point_one, azimuth_one, degree_abstract::from_degree(90.));

    auto az_on_point_one = azimuth(point_two, point_one);
    auto az_on_diametr_point_one = azimuth(point_two, diametr_point_one);
    auto az_on_point_one_90 = azimuth(point_two, point_one_90);

    if (az_on_diametr_point_one < az_on_point_one)
        az_on_diametr_point_one += (degree_abstract::from_degree(360.));
    if (az_on_point_one_90 < az_on_point_one)
        az_on_point_one_90 += (degree_abstract::from_degree(360.));
    auto target_az = azimuth_two;
    while (target_az < az_on_point_one)
        target_az += (degree_abstract::from_degree(360.));

    bool reverse_direction = false;
    if (az_on_point_one_90 > az_on_diametr_point_one)
    {
        reverse_direction = true;
    }
    if (target_az == az_on_point_one)
    {
        *result_point = point_one;
    }
    else if (target_az == az_on_diametr_point_one)
    {
        *result_point = diametr_point_one;
    }
    else
    {
        if (reverse_direction)
        {
            if ((target_az > az_on_point_one)
                && (target_az < az_on_diametr_point_one))
                return false;
        }
        else
        {
            if ((target_az < az_on_point_one)
                || (target_az > az_on_diametr_point_one))
                return false;
        }
        auto l_bound = degree_abstract::from_degree(0.);
        auto r_bound = degree_abstract::from_degree(180.);
        while (!(l_bound > r_bound))
        {
            auto middle = (l_bound + r_bound) / 2;
            auto middle_point = target_point(point_one, azimuth_one, middle);
            auto res_az = azimuth(point_two, middle_point);
            while (res_az < az_on_point_one)
                res_az += degree_abstract::from_degree(360.);
            if (reverse_direction)
            {
                if (res_az > target_az)
                    l_bound = middle + degree_abstract::from_milliseconds(1ll);
                else
                    r_bound = middle - degree_abstract::from_milliseconds(1ll);
            }
            else
            {
                if (res_az < target_az)
                    l_bound = middle + degree_abstract::from_milliseconds(1ll);
                else
                    r_bound = middle - degree_abstract::from_milliseconds(1ll);
            }
        }
        *result_point = target_point(point_one, azimuth_one, l_bound);
    }
    return true;
}
}  // namespace earth_math
#endif
