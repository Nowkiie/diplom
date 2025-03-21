#pragma once
#include "qpoint.h"
//#include <qvector.h>

#include <earth_point.hpp>
#include "../commonType.h"

namespace track
{
class visiable_coverage
{
public:
    visiable_coverage() = default;
    ~visiable_coverage() = default;

    void clearAll();
    void makeMapWeight(QVector<QPointF> heights,
                       QVector<QPointF> heights_signal, QPointF coord);
    void makeMapWeight(double gain, double power, double sensitive, double a_db,
                       QPointF coord);

    weight& getMapWeight(int n);
    coordCoverageVisible_& getVisible();
    void start();

private:
    int number = 0;
    test test_;
    weight mapWeight_;
    coordCoverageVisible_ visible;
};
}  // namespace track
