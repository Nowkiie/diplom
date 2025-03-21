#pragma once
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include "topographySeries.h"
#include "../calculate/calculateTile.h"

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface* surface, QVector<tile>& tiles_,
                          QImage texture, QSlider* slidermaxHeight,
                          QSlider* sliderMinHeight);
    ~SurfaceGraph() = default;

    void toggleSurfaceTexture(bool enable);
    void clearSeries(Q3DSurface* surface);
    void drawReliefForGeoCoord(Q3DSurface* surface, QImage texture,
                               QImage heights, QPointF coordTileBegin,
                               QPointF coordTileEnd);

    void drawReliefForDecartCoord(Q3DSurface* surface, QImage texture,
                                  QImage heights, QPointF decartCoordTileBegin,
                                  QPointF decartCoordTileEnd);

private:
    TopographySeries* m_topography;

    int m_highlightWidth;
    int m_highlightHeight;
};
