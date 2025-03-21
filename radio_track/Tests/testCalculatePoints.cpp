
#include <gtest/gtest.h>

#include "../radio_track/calculate/calculatePoint.h"


using namespace track;
std::unique_ptr<calculatePoint> calcPoints_ =
    std::make_unique<calculatePoint>();

TEST(Diff_x_more_diff_y_Double, checkFirstQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {8, 6};

    QVector<QPointF> controlValue = {{4, 8},      {4.5, 7.75}, {5, 7.5},
                                     {5.5, 7.25}, {6, 7},      {6.5, 6.75},
                                     {7, 6.5},    {7.5, 6.25}, {8, 6}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 0.5);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_more_diff_y, checkFirstQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {8, 6};

    QVector<QPointF> controlValue = {
        {4, 8}, {5, 7.5}, {6, 7}, {7, 6.5}, {8, 6}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_less_diff_y, checkFirstQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {7, 4};

    QVector<QPointF> controlValue = {
        {4, 8}, {4.75, 7}, {5.5, 6}, {6.25, 5}, {7, 4}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_less_diff_y_Double, checkSecondQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {3, 4};

    QVector<QPointF> controlValue = {{4, 8},      {3.875, 7.5}, {3.75, 7},
                                     {3.625, 6.5}, {3.5, 6},     {3.375, 5.5},
                                     {3.25, 5},    {3.125, 4.5} ,{3, 4}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 0.5);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_less_diff_y, checkSecondQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {3, 4};

    QVector<QPointF> controlValue = {
        {4, 8}, {3.75, 7}, {3.5, 6}, {3.25, 5}, {3, 4}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_TRUE(coordTrack.size() != 1);
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_more_diff_y, checkSecondQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {0, 5};

    QVector<QPointF> controlValue = {
        {4, 8}, {3, 7.25}, {2, 6.5}, {1, 5.75}, {0, 5}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_more_diff_y_Double, checkSecondQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {0, 5};

    QVector<QPointF> controlValue = {{4, 8},       {3.5, 7.625}, {3, 7.25},
                                     {2.5, 6.875}, {2, 6.5},     {1.5, 6.125},
                                     {1, 5.75},    {0.5, 5.375}, {0, 5}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 0.5);
    ASSERT_EQ(coordTrack.size(), controlValue.size());
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_more_diff_y, checkThirdQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {0, 10};

    QVector<QPointF> controlValue = {
        {4, 8}, {3, 8.5}, {2, 9}, {1, 9.5}, {0, 10}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_less_diff_y, checkThirdQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {2, 12};

    QVector<QPointF> controlValue = {
        {4, 8}, {3.5, 9}, {3, 10}, {2.5, 11}, {2, 12}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_less_diff_y, checkFourQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {6, 12};

    QVector<QPointF> controlValue = {
        {4, 8}, {4.5, 9}, {5, 10}, {5.5, 11}, {6, 12}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_TRUE(coordTrack.size() != 1);
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}

TEST(Diff_x_more_diff_y, checkFourQuarter)
{
    QPointF coord_begin = {4, 8};
    QPointF coord_end = {8, 10};

    QVector<QPointF> controlValue = {
        {4, 8}, {5, 8.5}, {6, 9}, {7, 9.5}, {8, 10}};

    QVector<QPointF> coordTrack =
        calcPoints_->calculatePointsTrack(coord_begin, coord_end, 1);
    ASSERT_TRUE(coordTrack.size() != 1);
    for (int i = 0; i <= coordTrack.size() - 1; i++)
    {
        EXPECT_DOUBLE_EQ(coordTrack[i].x(), controlValue[i].x());
        EXPECT_DOUBLE_EQ(coordTrack[i].y(), controlValue[i].y());
    }
}
