#pragma once

#include "coordinate.h"
#include <QPixmap>
#include "color_height.h"
#include <memory>
#include <optional>

namespace track
{
struct tile
{
    int pos_x;
    int pos_y;
    QPixmap pix_map;
};

enum class typeMap
{
    sat,
    height
};

class workWithTile
{
public:
    workWithTile();
    ~workWithTile();

    //перевод коодинаты точки в пиксельные координаты
    QPoint coordinateTodisplay(const QPointF& coordinate, int zoom);

    QPointF posTileToGeoCoord(int posX, int posY, int zoom);

    QPoint convertCoordDisplayToPosTile(const QPointF& coord_point, int zoom);

    //сохранение координат нового тайла в массив
    void saveTile(tile new_tile, typeMap type);

    //вычисление матрицы тайлов по 2м точкам
    void calcMatrixTiles(const QPointF& coord_begin, const QPointF& coord_end,
                         int zoom, typeMap type);

    //вычисление матрицы тайлов по 4м точкам
    void calcMatrixTiles(const QPointF& coord_right, const QPointF& coord_up,
                         const QPointF& coord_left, const QPointF& coord_down,
                         int zoom);

    //получение тайла по его координатам
    QPixmap getPixmapByCoordTile(int pos_param_x, int pos_param_y,
                                 typeMap type);

    //сохранение картинки тайла
    void setPixmapByCoordTile(int pos_param_x, int pos_param_y, QPixmap pixmap,
                              typeMap type);

    //получение ссылки на вектор тайлов
    QVector<tile>& getPointerOnVectorTile();

    QVector<tile>& getPointerOnVectorSatTile();

    //получение координат тайла по номеру тайла в массиве
    QPoint getCoordTileByNumber(int numberRequestTile, typeMap type);

    //очистка массива тайлов
    void clearTiles();

    void clearSatTiles();

    void clearArrayHeights();

    //преобразование цвета пикселя в высоту
    void convertColorToHeight(QPoint coord_tile, QPoint coord_px);

    //получение ссылки на массив вычисленных высот
    QVector<int>& getPointsOnCalcHeights();

    int getValueHeight(int number);

    QImage makeCombinedImage();

    QImage makeCombinedImageSat(QPointF coordPointSend, QPointF coordPointRec);

    QPoint calcCoordTileInCombinedImage(int numberTile, int diff_y);

    int getNumberTileByCoord(int pos_x, int pos_y, typeMap type);

private:
    std::unique_ptr<coordinate> valueCoord_;
    std::unique_ptr<converter_toHeight> converter_;
    int numberOfTiles = 0;
    int mytilesize = 256;
    QVector<tile> tiles_;
    QVector<tile> tilesSat_;

    void findMinCoord(QPoint& coord_begin, QPoint& coord_end);

    QPoint calcCoordPointInCombinedImage(QPointF coordPoint, int diff_y);

    std::optional<int> findIndexElementInVectorByCoord(
        const QVector<tile>& tiles, int x, int y);

    QImage drawCombinedImage(int diff_x, int diff_y, typeMap type);
};
}  // namespace track
