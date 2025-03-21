#pragma once
#include "ui_3dForm.h"
#include "QtDataVisualization/q3dsurface.h"
#include "QtWidgets/qmessagebox.h"
#include <QtGui/qscreen.h>
#include "../calculate/calculateTile.h"
#include "surfaceGraph.h"
#include "../calculate/coordinate.h"

using namespace QtDataVisualization;
namespace track
{
class Form : public QWidget
{
    Q_OBJECT
public:
    Form();
    ~Form();
    void createComponetes(QVector<tile>& tiles, QImage heights, QImage texture);
    void clearComponents();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::Form form;
    Q3DSurface* graph;
    QWidget* container;
    std::unique_ptr<SurfaceGraph> modifier;
    std::unique_ptr<workWithTile> workWithTile_;
    std::unique_ptr<coordinate> valueCoord_;
    QPointF geoCoordTileBegin;
    QPointF geoCoordTileEnd;
    QImage combinedImageHeights;
    QImage combinedImageTexture;
signals:
    void workWith3DEnd();
};
}  // namespace track
