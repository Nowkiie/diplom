
//#include "../radio_track/calculateTile.h"
#include <gtest/gtest.h>
#include "../radio_track/calculate/coordinate.h"


using namespace track;

std::unique_ptr<coordinate> coordinate_ = std::make_unique<coordinate>();


TEST(checkValueFromCoordinate, Coord)
{
    
    QPointF point_ = {33.7422, 44.562314};
    Point valueCoordPoint_ = coordinate_->getCoordFromPoint(point_);
    GeoCoord lonValueCoordPoint_ = valueCoordPoint_.lon;

    ASSERT_TRUE(lonValueCoordPoint_.degree == 33);
    ASSERT_TRUE(lonValueCoordPoint_.sec == 44);
    ASSERT_TRUE(lonValueCoordPoint_.arsec == 31);

}

TEST(checkCardDiraction, Coord)
{
    QPointF pointNE_ = {33.7422, 44.562314};
    Point valueCoordPoint_ = coordinate_->getCoordFromPoint(pointNE_);
    GeoCoord lonValueCoordPoint_ = valueCoordPoint_.lon;
    GeoCoord latValueCoordPoint_ = valueCoordPoint_.lat;

    ASSERT_TRUE(latValueCoordPoint_.card_direction == "N");
    ASSERT_TRUE(lonValueCoordPoint_.card_direction == "E");

    QPointF pointNW_ = {-33.7422, 44.562314};
    valueCoordPoint_ = coordinate_->getCoordFromPoint(pointNW_);
    lonValueCoordPoint_ = valueCoordPoint_.lon;
    ASSERT_TRUE(lonValueCoordPoint_.card_direction == "W");

    QPointF pointSE_ = {33.7422, -44.562314};
    valueCoordPoint_ = coordinate_->getCoordFromPoint(pointSE_);
    latValueCoordPoint_ = valueCoordPoint_.lat;
    ASSERT_TRUE(latValueCoordPoint_.card_direction == "S");
}