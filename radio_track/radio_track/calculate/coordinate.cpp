#include "coordinate.h"
#include <boost/math/constants/constants.hpp>

using namespace track;

coordinate::coordinate()
{
    PI = boost::math::constants::pi<double>();
}

QString coordinate::convertCoordinateWithPelengCaption(QPointF coordinate)
{
    auto latitude = Helper::fromDegree(coordinate.y());
    auto longitude = Helper::fromDegree(coordinate.x());
    auto coordiante_str = PelengCaption::placeString(latitude, longitude);
    auto coordinate_point = PelengCaption::placePoint(latitude, longitude);

    return coordiante_str;
}

QPointF coordinate::geoToCK(double latitude, double longitude)
{
    auto B = latitude * PI / 180.0;
    auto L = longitude;
    int n = std::floor((6 + L) / 6);
    auto l = (L - (3 + 6 * (n - 1))) / 57.29577951;

    auto dx1 = pow(l, 2)
               * (109500 - 574700 * pow(sin(B), 2) + 863700 * pow(sin(B), 4)
                  - 398600 * pow(sin(B), 6));
    auto dx2 = pow(l, 2)
               * (278194 - 830174 * pow(sin(B), 2) + 572434 * pow(sin(B), 4)
                  - 16010 * pow(sin(B), 6) + dx1);
    auto dx3 = pow(l, 2)
               * (672483.4 - 811219.9 * pow(sin(B), 2) + 5420 * pow(sin(B), 4)
                  - 10.6 * pow(sin(B), 6) + dx2);
    auto dx4 = pow(l, 2)
               * (1594561.25 + 5336.535 * pow(sin(B), 2)
                  + 26.79 * pow(sin(B), 4) + 0.149 * pow(sin(B), 6) + dx3);
    auto Xwgs = 6367558.4968 * B
                - sin(2 * B)
                      * (16002.89 + 66.9607 * pow(sin(B), 2)
                         + 0.3515 * pow(sin(B), 4) - dx4);

    auto dy1 = pow(l, 2)
               * (79690 - 866190 * pow(sin(B), 2) + 1730360 * pow(sin(B), 4)
                  - 945460 * pow(sin(B), 6));
    auto dy2 = pow(l, 2)
               * (270806 - 1523417 * pow(sin(B), 2) + 1327645 * pow(sin(B), 4)
                  - 21701 * pow(sin(B), 6) + dy1);
    auto dy3 = pow(l, 2)
               * (1070204.16 - 2136826.66 * pow(sin(B), 2)
                  + 17.98 * pow(sin(B), 4) - 11.99 * pow(sin(B), 6) + dy2);
    auto Ywgs =
        (5 + 10 * n) * pow(10, 5)
        + l * cos(B)
              * (6378245 + 21346.1415 * pow(sin(B), 2)
                 + 107.159 * pow(sin(B), 4) + 0.5977 * pow(sin(B), 6) + dy3);

    auto Xpz90 =
        (1 - 0.008 * pow(10, -6)) * (Xwgs - 2.041066 * pow(10, -8) * Ywgs)
        - 0.013;
    auto Ypz90 =
        (1 - 0.008 * pow(10, -6)) * (2.041066 * pow(10, -8) * Xwgs + Ywgs)
        + 0.106;
    auto x =
        (1 + 0.228 * pow(10, -6)) * (Xpz90 + 3.850439 * pow(10, -6) * Ypz90)
        - 23.557;
    auto y =
        (1 + 0.228 * pow(10, -6)) * (-3.850439 * pow(10, -6) * Xpz90 + Ypz90)
        + 140.844;

    return QPointF{x, y};
}

qreal coordinate::deg_rad(qreal x)
{
    return x * (PI / 180.0);
}

qreal coordinate::rad_deg(qreal x)
{
    return x * (180 / PI);
}

QPointF coordinate::geoCoordToDecart(QPointF geoCoord)
{
    double PI = boost::math::constants::pi<double>();

    const double a = 6378245.0;  // Большая (экваториальная) полуось
    const double b = 6356863.019;  // Малая (полярная) полуось
    const double e2 = (pow(a, 2) - pow(b, 2)) / pow(a, 2);  // Эксцентриситет
    const double n = (a - b) / (a + b);  // Приплюснутость

    const auto dLon = geoCoord.x();
    const auto dLat = geoCoord.y();

    // Номер зоны Гаусса-Крюгера
    const auto zone = static_cast<int>(dLon / 6.0 + 1);

    // Масштабный коэффициент
    const auto F = 1.0;
    const auto lat0 = 0.0;  // Начальная параллель (в радианах)
    const auto lon0 =
        (zone * 6 - 3) * PI / 180.0;  // Центральный меридиан (в радианах)
    const auto N0 = 0.0;  // Условное северное смещение для начальной параллели
    const auto E0 =
        zone * 1e6
        + 500000.0;  // Условное восточное смещение для центрального меридиана

    const auto lon = dLon * PI / 180.0;
    const auto lat = dLat * PI / 180.0;

    const auto sinLat = sin(lat);
    const auto cosLat = cos(lat);
    const auto tanLat = tan(lat);

    const auto v = a * F * pow(1 - e2 * pow(sinLat, 2), -0.5);
    const auto p = a * F * (1 - e2) * pow(1 - e2 * pow(sinLat, 2), -1.5);
    const auto n2 = v / p - 1;
    const auto M1 =
        (1 + n + 0.5 / 0.4 * pow(n, 2) + 5.0 / 4.0 * pow(n, 3)) * (lat - lat0);
    const auto M2 = (3 * n + 3 * pow(n, 2) + 21.0 / 8.0 * pow(n, 3))
                    * sin(lat - lat0) * cos(lat + lat0);
    const auto M3 = (15.0 / 8.0 * pow(n, 2) + 15.0 / 8.0 * pow(n, 3))
                    * sin(2 * (lat - lat0)) * cos(2 * (lat + lat0));
    const auto M4 =
        35.0 / 24.0 * pow(n, 3) * sin(3 * (lat - lat0)) * cos(3 * (lat + lat0));
    const auto M = b * F * (M1 - M2 + M3 - M4);
    const auto I = M + N0;
    const auto II = v / 2 * sinLat * cosLat;
    const auto III =
        v / 24 * sinLat * pow(cosLat, 3) * (5 - pow(tanLat, 2) + 9 * n2);
    const auto IIIA = v / 720 * sinLat * pow(cosLat, 5)
                      * (61 - 58 * pow(tanLat, 2) + pow(tanLat, 4));
    const auto IV = v * cosLat;
    const auto V = v / 6 * pow(cosLat, 3) * (v / p - pow(tanLat, 2));
    const auto VI = v / 120 * pow(cosLat, 5)
                    * (5 - 18 * pow(tanLat, 2) + pow(tanLat, 4) + 14 * n2
                       - 58 * pow(tanLat, 2) * n2);

    const auto N = I + II * pow(lon - lon0, 2) + III * pow(lon - lon0, 4)
                   + IIIA * pow(lon - lon0, 6);  // x
    const auto E = E0 + IV * (lon - lon0) + V * pow(lon - lon0, 3)
                   + VI * pow(lon - lon0, 5);

    return {E, N};
}

double coordinate::getDoubleCoordFromPoint(int degree, int sec, int arcsec)
{
    double coord = degree * 1.00;
    double secToDouble = sec * 1.0 / 60.0;
    double arcsecToDouble = arcsec * 1.0 / 3600.0;

    coord = coord + secToDouble + arcsecToDouble;

    return coord;
}

Point coordinate::getCoordFromPoint(QPointF coord)
{
    double x_coord = abs(coord.x());
    double y_coord = abs(coord.y());

    GeoCoord lon_coord;
    double fractpart, intpart;

    fractpart = modf(x_coord, &intpart);
    lon_coord.degree = int(abs(intpart));

    intpart = 0;
    double sec = fractpart * 60;
    fractpart = modf(sec, &intpart);
    lon_coord.sec = int(intpart);

    double arcsec = fractpart * 60;
    fractpart = modf(arcsec, &intpart);
    lon_coord.arsec = int(intpart);

    lon_coord.card_direction = coord.x() < 0 ? "W" : "E";

    GeoCoord lat_coord;
    fractpart, intpart = 0;

    fractpart = modf(y_coord, &intpart);
    lat_coord.degree = int(abs(intpart));

    intpart = 0;
    sec = fractpart * 60;
    fractpart = modf(sec, &intpart);
    lat_coord.sec = int(intpart);

    arcsec = fractpart * 60;
    fractpart = modf(arcsec, &intpart);
    lat_coord.arsec = int(intpart);

    lat_coord.card_direction = coord.y() < 0 ? "S" : "N";

    Point coord_point;

    coord_point.lat = lat_coord;
    coord_point.lon = lon_coord;

    return coord_point;
}
