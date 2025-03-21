#pragma once
#include <QString>
#include <QPointF>
#include "../PelengCaption.h"
#include "../calculate/ToDegree.h"

namespace track
{
struct GeoCoord
{
    int degree;
    int sec;
    int arsec;
    QString card_direction;  //N S E W
};

struct Point
{
    GeoCoord lat;
    GeoCoord lon;
};

class coordinate
{
public:
    coordinate();
    ~coordinate() = default;

    //перевод градусы в радианы
    qreal deg_rad(qreal x);

    //перевод радиан в градусы
    qreal rad_deg(qreal x);

    //выделение секунд и арксекунд из дробных коордиант точки
    Point getCoordFromPoint(QPointF coord);

    QPointF geoCoordToDecart(QPointF geoCoord);

    double getDoubleCoordFromPoint(int degree, int sec, int arcsec);

    QString convertCoordinateWithPelengCaption(QPointF coordinate);

    QPointF geoToCK(double latitude, double longitude);

private:
    double PI;
};
}  // namespace track
