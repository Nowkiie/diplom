#include "surfacegraph.h"
#include "topographyseries.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>

using namespace QtDataVisualization;

SurfaceGraph::SurfaceGraph(Q3DSurface* surface, QVector<tile>& tiles_,
                           QImage texture, QSlider* sliderMaxHeight,
                           QSlider* sliderMinHeight)
{
    sliderMaxHeight->setValue(2000);
    sliderMinHeight->setValue(0);
}

void SurfaceGraph::clearSeries(Q3DSurface* surface)
{
    m_topography->clearSeries();
}

void SurfaceGraph::toggleSurfaceTexture(bool enable)
{
    if (enable)
        m_topography->setTextureFile(":/maps/test");
    else
        m_topography->setTextureFile("");
}

void SurfaceGraph::drawReliefForDecartCoord(Q3DSurface* surface, QImage texture,
                                            QImage heights,
                                            QPointF decartCoordTileBegin,
                                            QPointF decartCoordTileEnd)
{
    surface->clearSelection();
    surface->setAxisX(new QValue3DAxis);
    surface->setAxisY(new QValue3DAxis);
    surface->setAxisZ(new QValue3DAxis);
    surface->axisX()->setLabelFormat("%.2f");
    surface->axisZ()->setLabelFormat("%.2f");
    surface->axisZ()->setRange(decartCoordTileBegin.x(),
                               decartCoordTileEnd.x());  //lon
    surface->axisY()->setRange(0.0f, 2000.0f);
    surface->axisX()->setRange(decartCoordTileEnd.y(),
                               decartCoordTileBegin.y());  //lat
    surface->axisX()->setLabelAutoRotation(30);
    surface->axisY()->setLabelAutoRotation(90);
    surface->axisZ()->setLabelAutoRotation(30);
    surface->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);

    QFont font = surface->activeTheme()->font();
    font.setPointSize(20);
    surface->activeTheme()->setFont(font);

    float diffLon = abs(decartCoordTileEnd.x() - decartCoordTileBegin.x());
    float diffLat = abs(decartCoordTileEnd.y() - decartCoordTileBegin.y());

    m_topography = new TopographySeries();
    m_topography->setTopograhySeries(diffLon, diffLat, decartCoordTileEnd.y(),
                                     decartCoordTileBegin.x(), heights);
    m_topography->setItemLabelFormat(QStringLiteral("@yLabel m"));

    surface->addSeries(m_topography);
    QMatrix matrix;
    matrix.rotate(-90);
    QImage rotateImage = texture.transformed(matrix);
    QImage mirrorImage = rotateImage.mirrored(true, false);
    m_topography->setTexture(mirrorImage);
}

void SurfaceGraph::drawReliefForGeoCoord(Q3DSurface* surface, QImage texture,
                                         QImage heights, QPointF coordTileBegin,
                                         QPointF coordTileEnd)
{
    surface->clearSelection();
    surface->setAxisX(new QValue3DAxis);
    surface->setAxisY(new QValue3DAxis);
    surface->setAxisZ(new QValue3DAxis);
    surface->axisX()->setLabelFormat("%.5f");
    surface->axisZ()->setLabelFormat("%.5f");
    surface->axisZ()->setRange(coordTileBegin.x(), coordTileEnd.x());  //lon
    surface->axisY()->setRange(0.0f, 2000.0f);
    surface->axisX()->setRange(coordTileEnd.y(), coordTileBegin.y());  //lat
    surface->axisX()->setLabelAutoRotation(30);
    surface->axisY()->setLabelAutoRotation(90);
    surface->axisZ()->setLabelAutoRotation(30);
    surface->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);

    QFont font = surface->activeTheme()->font();
    font.setPointSize(20);
    surface->activeTheme()->setFont(font);

    float diffLon = abs(coordTileEnd.x() - coordTileBegin.x());
    float diffLat = abs(coordTileEnd.y() - coordTileBegin.y());

    m_topography = new TopographySeries();
    m_topography->setTopograhySeries(diffLon, diffLat, coordTileEnd.y(),
                                     coordTileBegin.x(), heights);
    m_topography->setItemLabelFormat(QStringLiteral("@yLabel m"));

    surface->addSeries(m_topography);
    QMatrix matrix;
    matrix.rotate(-90);
    QImage rotateImage = texture.transformed(matrix);
    QImage mirrorImage = rotateImage.mirrored(true, false);
    m_topography->setTexture(mirrorImage);
}
