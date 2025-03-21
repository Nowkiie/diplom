#pragma once
#include <QWidget>

namespace track
{
class Helper : public QObject
{
    Q_OBJECT
public:
    static int64_t fromDegree(float degree)
    {
        return degree * 3600000;
    }
};
}  // namespace track
