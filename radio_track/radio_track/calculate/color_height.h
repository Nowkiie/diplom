#pragma once
#include <QVector>

namespace track
{
struct color_control_point
{
    int red;
    int green;
    int blue;
    int height;
};

class converter_toHeight
{
public:
    converter_toHeight();
    ~converter_toHeight();
    int convert(int red, int green, int blue);
    QVector<int>& getPointerOnCalcHeights();
    void clearHeights();
    int getvalueHeightByNumber(int number);

private:
    QVector<color_control_point> range_color;
    QVector<int> calculatedHeights_;
};
}  // namespace track
