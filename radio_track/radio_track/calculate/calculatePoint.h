#pragma once
#include <qpoint.h>
#include <qstring.h>
#include <qvector.h>
#include "coordinate.h"
#include "../commonType.h"

namespace track
{

class calculatePoint
{
public:
    calculatePoint();
    ~calculatePoint() = default;

    //вычисление точек маршрута радиотрассы
    QVector<QPointF> calculatePointsTrack(QPointF coordinate_point_begin,
                                          QPointF coordinate_point_end,
                                          double step);

    //вычисление расстояние между 2мя точками
    double DistanceBTWPoints(double lat_beg, double lon_beg, double lat_end,
                             double lon_end);

    //вычисление расстояния между начальной точкой и точкой маршрута радиотрассы
    QVector<double> DistanceBTWBegin_PointFromPointsTrack(
        QPointF coordinate_point_begin);

    //вычисление опорных точек
    QPointF calcReferancePoint(QPointF coord_center, double radius, double arc);

    //получение координат опорной точки по номеру
    QPointF getRefPoint(int numberReferencePoint);

    void clearVectorsCoordAndDistance();
    void clearVectorReferencePoints();

    //вычисление координаты точки через расстояние до неё
    QVector<QPointF> calculatePointsTrack(const QVector<double>& distance,
                                          int height_send, int height_rec);

    //вычисление точек 1ой зоны френеля
    QVector<QPointF> calculatePhrenelZone(
        QVector<QPointF>& h_linesignal, const QVector<double>& dist_point_track,
        double distance_, double freq);

    QVector<QPointF>& getPointerOnCoordPointsTrack();
    QVector<double>& getPointerOnVectorDist();
    double getValueDistByNumber(int number);

private:
    std::unique_ptr<coordinate> coord;
    QVector<QPointF> coordinate_points_track;
    QVector<double> distance_points_track;
    DataItems RefPoints_{};
    QPointF coordinate_point_begin;
    QPointF coordinate_point_end;
};
}  // namespace track
