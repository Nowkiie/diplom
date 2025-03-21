#pragma once
#include <earth_functions.hpp>
#include <vector>
#include <chrono>
#include "picoseconds.hpp"

namespace object_finder
{
const double light_speed = 299792.458;  //[км/с]

using namespace earth_math;
using position_line_t = std::vector<earth_point>;

/*
	Возвращает линию положения радара

	--- параметры -----
    delta - разница во времени прихода сигнала от объекта и от самолета (t_обкт + dt = t_смлт)
        "на сколько микросекунд сигнал от самолета пришел позже сигнала от искомого радара"
	base - координаты наблюдателя
	airplane - координаты самолета
	airplane_height_km - высота самолёта в км
	
	--- опциональные параметры -----
	angle_start -(опционально) угол начала сектора перебора азимута на объект(по умолчанию 0°) (0-360)
	angle_finish -(опционально) угол конца сектора перебора азимута на объект(по умолчанию 359°) (0-360)
	angle_step -(опционально) шаг для перебора азимута (по умолачанию 1°)
		"ищем объект в заданном секторе с зданным шагом"
		"если начальный угол больше конечного, то расчет идет в секторе с переходом через 360-0"
*/
static position_line_t calc_radar_pos_line(const picoseconds_t& delta,
                                           const earth_point& base,
                                           const earth_point& airplaine_point,
                                           const double airplane_height_km,
                                           const degree_abstract& angle_start,
                                           const degree_abstract& angle_finish,
                                           const degree_abstract& angle_step)
{
    position_line_t result;
    //д.б. dt >= 0
    if (delta.count() < 0)
        return result;
    if (delta.count() == 0)
    {
        result.push_back(airplaine_point);
        return result;
    }

    //д.б. dt < 2l/c
    const double dt_sec = double(delta.count()) * picoseconds_t::period::num
                          / picoseconds_t::period::den;
    const auto airplane_distance_km = distance_in_km(base, airplaine_point);
    double l = std::sqrt(airplane_distance_km * airplane_distance_km
                         + airplane_height_km * airplane_height_km);
    if (dt_sec > 2 * l / light_speed)
        return result;

    //д.б. angle_step > 0
    if (angle_step.to_degree() < eps)
        return result;

    //angle_start, angle_finish -> [0...360)
    double a_start = angle_start.to_radians();
    while (a_start > 2 * pi - eps) a_start -= 2 * pi;
    while (a_start < 0) a_start += 2 * pi;
    double a_finish = angle_finish.to_radians();
    while (a_finish > 2 * pi - eps) a_finish -= 2 * pi;
    while (a_finish < 0) a_finish += 2 * pi;

    int points_count;
    if (a_finish < a_start)
    {
        points_count =
            int((2 * pi - (a_start - a_finish)) / angle_step.to_radians() + 1);
    }
    else
        points_count = int((a_finish - a_start) / angle_step.to_radians() + 1);

    result.resize(points_count);

    l /= earth_radius;
    const double dr = l - light_speed * dt_sec / earth_radius;
    double A = cos(dr) - cos(l);
    const degree_abstract azimuth_to_plane = azimuth(base, airplaine_point);

    for (int num = 0; num < points_count; num++)
    {
        const double b =
            -sin(l) * cos(a_start - azimuth_to_plane.to_radians()) + sin(dr);
        const double c = sqrt(pow(A, 2) + pow(b, 2));
        const double omega = atan2(b / c, A / c);
        const double r = pi / 2 + omega;

        const auto query_point =
            target_point(base, degree_abstract::from_radians(a_start),
                         degree_abstract::from_radians(r));
        /* получена точка возможного положения запросчика, путь сигнала от
         * запросчика до самолёта до нас не учитывал высоту самолёта*/
        const auto query_airplane =
            distance_in_km(query_point, airplaine_point);
        if (query_airplane > airplane_height_km + eps)
        {
            const auto corrected_query_airplane =
                std::sqrt(query_airplane * query_airplane
                          - airplane_height_km * airplane_height_km);
            const auto airplane_query_az =
                azimuth(airplaine_point, query_point);
            result[num] = target_point(airplaine_point, airplane_query_az,
                                       corrected_query_airplane);
        }
        a_start += angle_step.to_radians();
        if (a_start > 2 * pi)
            a_start -= 2 * pi;
    }

    return result;
}

static position_line_t calc_radar_pos_line(const picoseconds_t& delta,
                                           const earth_point& base,
                                           const earth_point& airplaine_point,
                                           const double airplane_height_km = 0)
{
    const auto airplane_azimuth = earth_math::azimuth(base, airplaine_point);
    const auto airplane_distance_km =
        earth_math::distance_in_km(base, airplaine_point);
    const auto start_az = airplane_azimuth - degree_abstract::from_degree(179.);
    const auto stop_az = airplane_azimuth + degree_abstract::from_degree(179.);
    const auto step = degree_abstract::from_degree(1.);
    return calc_radar_pos_line(delta, base, airplaine_point, airplane_height_km,
                               start_az, stop_az, step);
}

/*
	Возвращает дугу эллипса - линии положения самолета, ограниченную лепестком от радара
	
	--- параметры -----
	base - координаты наблюдателя
	radar - координаты радара
	dt - разница во времени прихода сигнала от радара и от самолета (t_обкт + dt = t_смлт)
		"на сколько микросекунд сигнал от самолета пришел позже сигнала от искомого радара"
	radar_azimuth - азимут луча радара
	lobe_width - ширина лепестка сигнала радара (сектора). Будет возвращена линия положения самолета,
		ограниченная сектором [radar_azimuth - lobe_width/2 .. radar_azimuth + lobe_width/2]
	lobe_step -(опционально) шаг для перебора азимута внутри лепестка (по умолачанию 1°)
	"ищем объект в заданном секторе с зданным шагом"
*/
static position_line_t calc_plane_pos_line(
    const earth_point& base, const earth_point& radar, const picoseconds_t& dt,
    const degree_abstract& radar_azimuth, const degree_abstract& lobe_width,
    const degree_abstract& lobe_step = degree_abstract::from_degree(1))
{
    position_line_t result;

    //д.б. dt >= 0
    if (dt.count() < 0)
        return result;
    if (dt.count() == 0)
    {
        //result.push_back(radar);
        //неопределенность
        return result;
    }

    //д.б. step >= 0
    if (lobe_step.to_degree() < eps)
        return result;

    const int point_count =
        (int)(lobe_width.to_degree() / lobe_step.to_degree()) + 1;
    if (point_count < 1)
        return result;
    result.resize(point_count);

    const double dt_sec = double(dt.count()) * picoseconds_t::period::num
		/ picoseconds_t::period::den;
    const double l = distance_in_km(base, radar) / earth_radius;
    const double d = l + light_speed * dt_sec / earth_radius;

    const degree_abstract azimuth_to_nabl = azimuth(radar, base);
    double beta_start = (radar_azimuth - lobe_width / 2.0).to_radians();
    while (beta_start < 0) beta_start += 2 * pi;
    while (beta_start > 2 * pi - eps) beta_start -= 2 * pi;

    for (int num = 0; num < point_count; num++)
    {
        const double A =
            1 - cos(l) * cos(d)
            - sin(l) * sin(d) * cos(beta_start - azimuth_to_nabl.to_radians());
        const double B =
            -cos(l) * sin(d)
            + sin(l) * cos(d) * cos(beta_start - azimuth_to_nabl.to_radians());
        const double C = sqrt(pow(A, 2) + pow(B, 2));
        const double omega = atan2(B / C, A / C);
        const double r = pi / 2 + omega;
        result[num] =
            target_point(radar, degree_abstract::from_radians(beta_start),
                         degree_abstract::from_radians(d - r));

        beta_start += lobe_step.to_radians();
        if (beta_start > 2 * pi)
            beta_start -= 2 * pi;
    }

    return result;
}

/*
	Возвращает позицию самолета (точку перечечения эллипса и луча от радара)

	--- параметры -----
	base - координаты наблюдателя
	radar - координаты радара
	dt - разница во времени прихода сигнала от радара и от самолета (t_обкт + dt = t_смлт)
		"на сколько микросекунд сигнал от самолета пришел позже сигнала от искомого радара"
	radar_azimuth - азимут луча радара
	*/
static position_line_t calc_plane_pos_line(const earth_point& base,
                                           const earth_point& radar,
                                           const picoseconds_t& dt,
                                           const degree_abstract& radar_azimuth)
{
    position_line_t result;
    result = calc_plane_pos_line(base, radar, dt, radar_azimuth,
                                 degree_abstract::from_degree(0));
    return result;
}

/*
	Возвращает эллипс - линию положения самолета

	--- параметры -----
	base - координаты наблюдателя
	radar - координаты радара
	dt - разница во времени прихода сигнала от радара и от самолета (t_обкт + dt = t_смлт)
		"на сколько микросекунд сигнал от самолета пришел позже сигнала от искомого радара"
	*/

static position_line_t calc_plane_pos_line(const earth_point& base,
                                           const earth_point& radar,
                                           const picoseconds_t& dt)
{
    position_line_t result;
    result = calc_plane_pos_line(
        base, radar, dt,
        degree_abstract::from_degree(0),  //earth_math::azimuth(radar, base),
        degree_abstract::from_degree(360));
    return result;
}

}  // namespace object_finder
