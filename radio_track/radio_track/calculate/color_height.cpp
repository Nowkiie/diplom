#include "color_height.h"

#include <iostream>
#include <fstream>
#include <time.h>

using namespace track;

converter_toHeight::converter_toHeight()
{
    //задание граничных высот и значений цвета
    color_control_point height_5;
    height_5.red = 35;
    height_5.green = 132;
    height_5.blue = 28;
    height_5.height = 5;
    range_color.push_back(height_5);

    color_control_point height_200;
    height_200.red = 88;
    height_200.green = 153;
    height_200.blue = 76;
    height_200.height = 200;
    range_color.push_back(height_200);

    color_control_point height_500;
    height_500.red = 106;
    height_500.green = 206;
    height_500.blue = 44;
    height_500.height = 500;
    range_color.push_back(height_500);

    color_control_point height_1000;
    height_1000.red = 186;
    height_1000.green = 234;
    height_1000.blue = 123;
    height_1000.height = 1000;
    range_color.push_back(height_1000);

    color_control_point height_2000;
    height_2000.red = 217;
    height_2000.green = 236;
    height_2000.blue = 196;
    height_2000.height = 2000;
    range_color.push_back(height_2000);

    color_control_point height_3000;
    height_3000.red = 230;
    height_3000.green = 239;
    height_3000.blue = 153;
    height_3000.height = 3000;
    range_color.push_back(height_3000);

    color_control_point height_4000;
    height_4000.red = 244;
    height_4000.green = 213;
    height_4000.blue = 120;
    height_4000.height = 4000;
    range_color.push_back(height_4000);

    color_control_point height_5000;
    height_5000.red = 236;
    height_5000.green = 181;
    height_5000.blue = 16;
    height_5000.height = 5000;
    range_color.push_back(height_5000);

    color_control_point height_9000;
    height_9000.red = 136;
    height_9000.green = 108;
    height_9000.blue = 18;
    height_9000.height = 9000;
    range_color.push_back(height_9000);
}

int converter_toHeight::convert(int red, int green, int blue)
{
    int r = red;
    int g = green;
    int b = blue;
    int height = 0;

    if (r == 255 && g == 255 && b == 255)
    {
        height = 0;
        calculatedHeights_.push_back(0);
    }
    else
    {
        for (int i = 0; i < range_color.size() - 1; i++)
        {
            color_control_point control_point_1 = range_color[i];
            color_control_point control_point_2 = range_color[i + 1];

            int r1 = control_point_1.red;
            int r2 = control_point_2.red;

            if (r >= r1 && r <= r2 || r <= r1 && r >= r2)
            {
                int g1 = control_point_1.green;
                int g2 = control_point_2.green;

                if (g >= g1 && g <= g2 || g <= g1 && g >= g2)
                {
                    int b1 = control_point_1.blue;
                    int b2 = control_point_2.blue;

                    if (b >= b1 && b <= b2 || b <= b1 && b >= b2)
                    {
                        //алгоритм интерпол€ции по методу ближайщих соседей
                        double p = (r - r1) * 1.0 / (r2 - r1);

                        int h1 = control_point_1.height;
                        int h2 = control_point_2.height;

                        height = round(p * (h2 - h1) + h1);

                        break;
                    }
                }
            }
        }

        calculatedHeights_.push_back(height);
    }

    return height;
}

int converter_toHeight::getvalueHeightByNumber(int number)
{
    return calculatedHeights_[number];
}

void converter_toHeight::clearHeights()
{
    calculatedHeights_.clear();
}

QVector<int>& converter_toHeight::getPointerOnCalcHeights()
{
    return calculatedHeights_;
}

converter_toHeight::~converter_toHeight()
{
    range_color.clear();
}