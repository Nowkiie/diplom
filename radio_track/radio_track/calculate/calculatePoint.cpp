#include "calculatePoint.h"
#include <fstream>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include "earth_functions.hpp"
using namespace track;

calculatePoint::calculatePoint()
{
    coord = std::make_unique<coordinate>();
}

QVector<QPointF> calculatePoint::calculatePhrenelZone(
    QVector<QPointF>& h_linesignal, const QVector<double>& dist_point_track,
    double distance_, double freq)
{
    double H = 0;

    QVector<QPointF> points_f;
    for (int i = 0; i < h_linesignal.size(); i++)
    {
        //
        double d1 = dist_point_track[i];
        double d2 = distance_ - dist_point_track[i];

        H = 17.3 * sqrt(1 / freq * (d1 * d2) / (d1 + d2));

        points_f << QPointF(dist_point_track[i], H);
    }

    return points_f;
}

//определение расстояния между 2мя точками
double calculatePoint::DistanceBTWPoints(double lat_beg, double lon_beg,
                                         double lat_end, double lon_end)
{
    lat_beg = coord->deg_rad(lat_beg);
    lat_end = coord->deg_rad(lat_end);
    lon_beg = coord->deg_rad(lon_beg);
    lon_end = coord->deg_rad(lon_end);

    double cos_d = sin(lat_beg) * sin(lat_end)
                   + cos(lat_beg) * cos(lat_end) * cos(lon_beg - lon_end);

    const auto earth_radius = 6371;

    double distance = acos(cos_d) * earth_radius;

    return distance;
}

QVector<double> calculatePoint::DistanceBTWBegin_PointFromPointsTrack(
    QPointF coordinate_point_begin)
{
    for (int i = 0; i < coordinate_points_track.size(); i++)
    {
        double distance = DistanceBTWPoints(
            coordinate_point_begin.y(), coordinate_point_begin.x(),
            coordinate_points_track[i].y(), coordinate_points_track[i].x());

        distance_points_track.push_back(distance);
    }

    return distance_points_track;
}

double calculatePoint::getValueDistByNumber(int number)
{
    return distance_points_track[number];
}

QVector<QPointF> calculatePoint::calculatePointsTrack(
    const QVector<double>& distance, int height_send, int height_rec)
{
    double begin = 0;
    double end = 0;

    double x1 = distance[0];
    double y1 = height_send;
    double x2 = distance[distance.size() - 1];
    double y2 = height_rec;

    double a = (y2 - y1) / (x2 - x1);
    double b = (x2 * y1 - x1 * y2) / (x2 - x1);

    QVector<QPointF> points;

    for (auto dist : distance)
    {
        double y = a * dist + b;
        QPointF new_point_track;
        new_point_track.setX(dist);
        new_point_track.setY(y);
        points.push_back(new_point_track);
    }

    return points;
}

//расчитывает координаты точек между 2мя выбранными точками
QVector<QPointF> calculatePoint::calculatePointsTrack(
    QPointF coordinate_point_begin, QPointF coordinate_point_end, double step)
{
    auto p1 = earth_math::earth_point(coordinate_point_begin.ry(),
                                      coordinate_point_begin.rx());
    auto p2 = earth_math::earth_point(coordinate_point_end.ry(),
                                      coordinate_point_end.rx());
    coordinate_points_track.clear();

    auto dist = earth_math::distance_in_km(p1, p2);
    auto vector = earth_math::azimuth(p1, p2);
    double cur_dist = 0;
    auto cur_point = p1;

    auto step_km = earth_math::earth_radius * step * earth_math::pi / 180;

    while (cur_dist < dist)
    {
        auto meridian_degree_koef =
            fabs(cos(cur_point.latitude().to_radians()));
        auto k = 0.;
        // если вертикальное движение преобладает
        if (fabs(cos(vector.to_radians())) > fabs(sin(vector.to_radians())))
        {
            auto sq_sin = sin(vector.to_radians()) * sin(vector.to_radians());
            k = sqrt(step_km * step_km
                     + step_km * step_km * meridian_degree_koef
                           * meridian_degree_koef * sq_sin);
        }
        else
        {
            auto sq_cos = cos(vector.to_radians()) * cos(vector.to_radians());
            k = sqrt(step_km * step_km * sq_cos
                     + step_km * step_km * meridian_degree_koef
                           * meridian_degree_koef);
        }

        QPointF CoordNewPoint;
        CoordNewPoint.setX(cur_point.longitude().to_degree());
        CoordNewPoint.setY(cur_point.latitude().to_degree());
        cur_point = earth_math::target_point(cur_point, vector, k);
        cur_dist = earth_math::distance_in_km(p1, cur_point);

        coordinate_points_track.push_back(CoordNewPoint);

        vector = earth_math::azimuth(cur_point, p2);
    }
    return coordinate_points_track;
}

QPointF calculatePoint::calcReferancePoint(QPointF coord_center, double radius,
                                           double arc)
{
    double lat_beg = coord->deg_rad(coord_center.y());
    double lon_beg = coord->deg_rad(coord_center.x());

    const auto earth_radius = 6371;
    double lat_end =
        asin(sin(lat_beg) * cos(radius / earth_radius)
             + cos(lat_beg) * sin(radius / earth_radius) * cos(arc));
    double lon_end =
        lon_beg
        + atan2(sin(arc) * sin(radius / earth_radius) * cos(lat_beg),
                cos(radius / earth_radius) - sin(lat_beg) * sin(lat_end));

    QPointF new_point = {coord->rad_deg(lon_end), coord->rad_deg(lat_end)};

    DataItem new_item;
    new_item.coordRefencePoint = new_point;

    RefPoints_.push_back(new_item);

    return new_point;
}

QPointF calculatePoint::getRefPoint(int numberReferencePoint)
{
    return RefPoints_[numberReferencePoint].coordRefencePoint;
}

void calculatePoint::clearVectorsCoordAndDistance()
{
    coordinate_points_track.clear();
    distance_points_track.clear();
}

void calculatePoint::clearVectorReferencePoints()
{
    RefPoints_.clear();
}

QVector<QPointF>& calculatePoint::getPointerOnCoordPointsTrack()
{
    return coordinate_points_track;
}

QVector<double>& calculatePoint::getPointerOnVectorDist()
{
    return distance_points_track;
}
