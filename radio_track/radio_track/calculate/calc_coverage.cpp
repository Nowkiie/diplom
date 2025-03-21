#include "calc_coverage.h"
#include "qmath.h"
#include <fstream>

using namespace track;

void visiable_coverage::start()
{
    number = 0;
    test_.clear();
}

void visiable_coverage::clearAll()
{
    mapWeight_.clear();
    visible.clear();
}

weight& visiable_coverage::getMapWeight(int n)
{
    return test_.find(n)->second;
}

coordCoverageVisible_& visiable_coverage::getVisible()
{
    return visible;
}

void visiable_coverage::makeMapWeight(double gain, double power,
                                      double sensitive, double a_db,
                                      QPointF coord)
{
    type_track type = type_track::half_closed;
    double result = power + gain - sensitive + gain - a_db;
    if (result > 6)
    {
        type = type_track::open;
    }
    else if (result <= 6 && result >= -6)
    {
        type = type_track::half_open;
    }
    else
    {
        type = type_track::closed;
    }
    mapWeight_.insert({type, coord});
    test_.insert({number, mapWeight_});
    number++;
}

void visiable_coverage::makeMapWeight(QVector<QPointF> heights,
                                      QVector<QPointF> heights_signal,
                                      QPointF coord)
{
    coordCoverageVisible_ coordVisibleCoverage;
    bool flag_breakpoint = false;

    type_track type;

    for (int i = 0; i < heights.size(); i++)
    {
        if (heights[i].y() < heights_signal[i].y())
        {
            type = type_track::open;
        }
        else
        {
            type = type_track::closed;
            break;
        }
    }

    mapWeight_.insert({type, coord});
    test_.insert({number, mapWeight_});
    number++;
}
