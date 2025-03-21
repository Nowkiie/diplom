#include "calculateTile.h"
#include "boost/math/constants/constants.hpp"
#include <iterator>
#include <fstream>
#include <qpainter.h>

using namespace track;

workWithTile::workWithTile()
{
    valueCoord_ = std::make_unique<coordinate>();
    converter_ = std::make_unique<converter_toHeight>();
}

QImage workWithTile::drawCombinedImage(int diff_x, int diff_y, typeMap type)
{
    QImage combinedImage(diff_x * 256, diff_y * 256, QImage::Format_ARGB32);
    QPainter painter(&combinedImage);
    for (int i = 0; i < diff_x; i++)
    {
        for (int j = 0; j < diff_y; j++)
        {
            int numberTile = i * diff_y + j;
            QImage img;
            switch (type)
            {
                case typeMap::height:
                {
                    img = tiles_[numberTile].pix_map.toImage();
                    break;
                }
                case typeMap::sat:
                {
                    img = tilesSat_[numberTile].pix_map.toImage();
                    break;
                }
            }

            int pos_x = i * 256;
            int pos_y = j * 256;
            painter.drawImage(pos_x, pos_y, img);
        }
    }
    QMatrix matrix;
    matrix.rotate(0);
    QImage transform = combinedImage.transformed(matrix);

    return transform;
}

QImage workWithTile::makeCombinedImage()
{
    int diff_x = tiles_[tiles_.size() - 1].pos_x - tiles_[0].pos_x + 1;
    int diff_y = tiles_[tiles_.size() - 1].pos_y - tiles_[0].pos_y + 1;

    QImage result = drawCombinedImage(diff_x, diff_y, typeMap::height);

    return result;
}

QPoint workWithTile::calcCoordPointInCombinedImage(QPointF coordPoint,
                                                   int diff_y)
{
    QPoint coordPointPx = coordinateTodisplay(coordPoint, 11);
    //вычисление позиций тайла для карты
    int posTile_x = coordPointPx.x() / 256;
    int posTile_y = coordPointPx.y() / 256;

    //вычислении пиксельных координат начала тайла для карты
    int coordBeginTilePx_x = posTile_x * 256;
    int coordBeginTilePx_y = posTile_y * 256;

    //определение координат пикселя внутри тайла
    int coordPixInTile_x = coordPointPx.x() - coordBeginTilePx_x;
    int coordPixInTile_y = coordPointPx.y() - coordBeginTilePx_y;

    //определение номера тайла в массиве тайлов по его координатам
    int numberTile = getNumberTileByCoord(posTile_x, posTile_y, typeMap::sat);

    //определение пиксельных координат начала тайла внутри созданной картинки области
    QPoint coordTileInCombinedImage =
        calcCoordTileInCombinedImage(numberTile, diff_y);

    //вычисление пиксельных координат точки внутри созданной картинки области
    int coordPointInCombinedImage_x =
        coordTileInCombinedImage.y() + coordPixInTile_x;

    int coordPointInCombinedImage_y =
        coordTileInCombinedImage.x() + coordPixInTile_y;

    return {coordPointInCombinedImage_x, coordPointInCombinedImage_y};
}

QImage workWithTile::makeCombinedImageSat(QPointF coordPointSend,
                                          QPointF coordPointRec)
{
    int diff_x = tilesSat_[tilesSat_.size() - 1].pos_x - tilesSat_[0].pos_x + 1;
    int diff_y = tilesSat_[tilesSat_.size() - 1].pos_y - tilesSat_[0].pos_y + 1;

    QImage transform = drawCombinedImage(diff_x, diff_y, typeMap::sat);

    QImage copy = transform;
    QPainter p(&copy);

    //отрисовка точек на картинке
    QPoint coordPointSendInCombinedImage =
        calcCoordPointInCombinedImage(coordPointSend, diff_y);

    for (int i = coordPointSendInCombinedImage.x();
         i <= coordPointSendInCombinedImage.x() + 10; i++)
    {
        for (int j = coordPointSendInCombinedImage.y();
             j <= coordPointSendInCombinedImage.y() + 10; j++)
        {
            p.setBrush(QBrush(Qt::red));
            p.setPen(QPen(Qt::red));
            p.drawPoint(i, j);
            copy.save("test_alg.jpg", "JPEG");
        }
    }

    QPoint coordPointRecInCombinedImage =
        calcCoordPointInCombinedImage(coordPointRec, diff_y);

    for (int i = coordPointRecInCombinedImage.x();
         i <= coordPointRecInCombinedImage.x() + 10; i++)
    {
        for (int j = coordPointRecInCombinedImage.y();
             j <= coordPointRecInCombinedImage.y() + 10; j++)
        {
            p.setBrush(QBrush(Qt::red));
            p.setPen(QPen(Qt::red));
            p.drawPoint(i, j);
            copy.save("test_alg.jpg", "JPEG");
        }
    }

    return copy;
}

void workWithTile::convertColorToHeight(QPoint coord_tile, QPoint coord_px)
{
    QPixmap pixmap =
        getPixmapByCoordTile(coord_tile.x(), coord_tile.y(), typeMap::height);

    QImage image(pixmap.toImage());
    QColor color(image.pixel(coord_px.x(), coord_px.y()));
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int height = converter_->convert(red, green, blue);
}

QPoint workWithTile::calcCoordTileInCombinedImage(int numberTile, int diff_y)
{
    int numberRow = numberTile / diff_y;
    int numberStr = numberTile - diff_y * numberRow;

    return {numberStr * 256, numberRow * 256};
}

QVector<int>& workWithTile::getPointsOnCalcHeights()
{
    return converter_->getPointerOnCalcHeights();
}

QPoint workWithTile::coordinateTodisplay(const QPointF& coordinate, int zoom)
{
    double PI = boost::math::constants::pi<double>();
    numberOfTiles = pow(2, zoom);

    qreal y = coordinate.y();
    qreal x = (coordinate.x() + 180) * (numberOfTiles * mytilesize)
              / 360.;  // coord to pixel!
    y = (1 - (log(tan(PI / 4 + valueCoord_->deg_rad(y) / 2)) / PI)) / 2
        * (numberOfTiles * mytilesize);

    return QPoint(int(x), int(y));
}

QPointF workWithTile::posTileToGeoCoord(int posX, int posY, int zoom)
{
    double PI = boost::math::constants::pi<double>();
    numberOfTiles = pow(2, zoom);
    double displayCoordPosX = posX * 256.;
    double displayCoordPosY = posY * 256.;
    QPointF point = {displayCoordPosX, displayCoordPosY};

    qreal longitude =
        (point.x() * (360. / (numberOfTiles * mytilesize))) - 180.;
    qreal latitude = valueCoord_->rad_deg(atan(
        sinh((1. - point.y() * (2. / (numberOfTiles * mytilesize))) * PI)));

    return QPointF(longitude, latitude);
}

void workWithTile::saveTile(tile new_tile, typeMap type)
{
    switch (type)
    {
        case typeMap::height:
        {
            tiles_.push_back(new_tile);
            break;
        }
        case typeMap::sat:
        {
            tilesSat_.push_back(new_tile);
            break;
        }
        default:
        {
            break;
        }
    }
}

void workWithTile::findMinCoord(QPoint& coord_begin, QPoint& coord_end)
{
    if (coord_begin.x() > coord_end.x())
    {
        int temp = coord_begin.x();
        coord_begin.setX(coord_end.x());
        coord_end.setX(temp);
    }

    if (coord_begin.y() > coord_end.y())
    {
        int temp = coord_begin.y();
        coord_begin.setY(coord_end.y());
        coord_end.setY(temp);
    }
}

QPoint workWithTile::convertCoordDisplayToPosTile(const QPointF& coord_point,
                                                  int zoom)
{
    auto coord_point_px = coordinateTodisplay(coord_point, zoom);
    int coord_tile_x = coord_point_px.x() / mytilesize;
    int coord_tile_y = coord_point_px.y() / mytilesize;
    QPoint coord_tile = {coord_tile_x, coord_tile_y};

    return coord_tile;
}

void workWithTile::calcMatrixTiles(const QPointF& coord_begin,
                                   const QPointF& coord_end, int zoom,
                                   typeMap type)
{
    QPoint coord_tile_begin = convertCoordDisplayToPosTile(coord_begin, zoom);

    QPoint coord_tile_end = convertCoordDisplayToPosTile(coord_end, zoom);
    findMinCoord(coord_tile_begin, coord_tile_end);

    for (auto i = coord_tile_begin.x(); i <= coord_tile_end.x(); i++)
    {
        for (auto j = coord_tile_begin.y(); j <= coord_tile_end.y(); j++)
        {
            switch (type)
            {
                case typeMap::height:
                {
                    tile new_tile;
                    new_tile.pos_x = i;
                    new_tile.pos_y = j;
                    saveTile(new_tile, typeMap::height);
                    break;
                }
                case typeMap::sat:
                {
                    tile new_tile;
                    new_tile.pos_x = i;
                    new_tile.pos_y = j;
                    saveTile(new_tile, typeMap::sat);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void workWithTile::calcMatrixTiles(const QPointF& coord_right,
                                   const QPointF& coord_up,
                                   const QPointF& coord_left,
                                   const QPointF& coord_down, int zoom)
{
    QPoint coord_tile_left = convertCoordDisplayToPosTile(coord_left, zoom);
    QPoint coord_tile_right = convertCoordDisplayToPosTile(coord_right, zoom);
    QPoint coord_tile_up = convertCoordDisplayToPosTile(coord_up, zoom);
    QPoint coord_tile_down = convertCoordDisplayToPosTile(coord_down, zoom);

    findMinCoord(coord_tile_left, coord_tile_up);
    findMinCoord(coord_tile_right, coord_tile_down);

    for (int i = coord_tile_left.x(); i <= coord_tile_down.x(); i++)
    {
        for (int j = coord_tile_left.y(); j <= coord_tile_down.y(); j++)
        {
            tile new_tile;
            new_tile.pos_x = i;
            new_tile.pos_y = j;
            saveTile(new_tile, typeMap::height);
        }
    }
}

QPoint workWithTile::getCoordTileByNumber(int numberRequestTile, typeMap type)
{
    int coord_x;
    int coord_y;

    switch (type)
    {
        case typeMap::height:
        {
            coord_x = tiles_[numberRequestTile].pos_x;
            coord_y = tiles_[numberRequestTile].pos_y;
            break;
        }
        case typeMap::sat:
        {
            coord_x = tilesSat_[numberRequestTile].pos_x;
            coord_y = tilesSat_[numberRequestTile].pos_y;
            break;
        }
        default:
        {
            break;
        }
    }

    QPoint coord_tile = {coord_x, coord_y};

    return coord_tile;
}

QVector<tile>& workWithTile::getPointerOnVectorTile()
{
    return tiles_;
}

QVector<tile>& workWithTile::getPointerOnVectorSatTile()
{
    return tilesSat_;
}

std::optional<int> workWithTile::findIndexElementInVectorByCoord(
    const QVector<tile>& tiles, int x, int y)
{
    auto it = std::find_if(tiles.begin(), tiles.end(),
                           [x, y](const tile& el)
                           {
                               return el.pos_y == y && el.pos_x == x;
                           });
    if (it != tiles.end())
    {
        return it - tiles.begin();
    }
    else
        return {};
}

void workWithTile::setPixmapByCoordTile(int pos_param_x, int pos_param_y,
                                        QPixmap pixmap, typeMap type)
{
    switch (type)
    {
        case typeMap::height:
        {
            if (auto it = findIndexElementInVectorByCoord(tiles_, pos_param_x,
                                                          pos_param_y))
            {
                tiles_[*it].pix_map = pixmap;
            }

            break;
        }
        case typeMap::sat:
        {
            if (auto it = findIndexElementInVectorByCoord(
                    tilesSat_, pos_param_x, pos_param_y))
            {
                tilesSat_[*it].pix_map = pixmap;
            }

            break;
        }
        default:
        {
            break;
        }
    }
}

QPixmap workWithTile::getPixmapByCoordTile(int pos_x_param, int pos_y_param,
                                           typeMap type)
{
    switch (type)
    {
        case typeMap::height:
        {
            if (auto it = findIndexElementInVectorByCoord(tiles_, pos_x_param,
                                                          pos_y_param))
            {
                return tiles_[*it].pix_map;
            }

            break;
        }
        case typeMap::sat:
        {
            if (auto it = findIndexElementInVectorByCoord(
                    tilesSat_, pos_x_param, pos_y_param))
            {
                return tilesSat_[*it].pix_map;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    //add return empty pixmap and checking pixmap after get
}

int workWithTile::getNumberTileByCoord(int pos_x, int pos_y, typeMap type)
{
    switch (type)
    {
        case typeMap::height:
        {
            if (auto it = findIndexElementInVectorByCoord(tiles_, pos_x, pos_y))
            {
                return *it;
            }
            break;
            //return it;
        }
        case typeMap::sat:
        {
            if (auto it =
                    findIndexElementInVectorByCoord(tilesSat_, pos_x, pos_y))
            {
                return *it;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

int workWithTile::getValueHeight(int number)
{
    return converter_->getvalueHeightByNumber(number);
}

void workWithTile::clearTiles()
{
    tiles_.clear();
}

void workWithTile::clearSatTiles()
{
    tilesSat_.clear();
}

void workWithTile::clearArrayHeights()
{
    converter_->clearHeights();
}

workWithTile::~workWithTile() {}
