#pragma once
#include <QtDataVisualization/qsurface3dseries.h>
#include "../calculate/color_height.h"
#include "../calculate/calculateTile.h"

using namespace QtDataVisualization;
using namespace track;

class TopographySeries : public QSurface3DSeries
{
    Q_OBJECT
public:
    explicit TopographySeries();
    ~TopographySeries();

    void setTopograhySeries(float diffLon, float diffLat, float startCoordX,
                            float startCoordZ, QImage combinedImage);
    void setSeriesPoint(float diffLon, float diffLat, float coordX,
                        float coordZ, QImage combinedImage, float startCoordZ,
                        float startCoordX);
    void clearSeries();
    float sampleCountX()
    {
        return m_sampleCountX;
    };
    float sampleCountZ()
    {
        return m_sampleCountZ;
    };

private:
    float m_sampleCountX;
    float m_sampleCountZ;
    std::unique_ptr<converter_toHeight> converter;
    QSurfaceDataArray* dataArray;
    int calcHeightForCurrentPoint(QPointF coordPoint, QPointF startCoord,
                                  QImage combinedImage, double stepX,
                                  double stepZ);
};
