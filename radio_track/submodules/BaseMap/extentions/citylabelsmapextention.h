#ifndef CITYLABELSMAPEXTENTION_H
#define CITYLABELSMAPEXTENTION_H

#include "extentions/checkablemapextention.h"
#include "geometries/citylabel.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для включения/выключения отображения координатной сетки
*    @author Maxim Poylov
*/
class CityLabelsMapExtention :
    public qmapcontrol::CheckableMapExtention
{
    Q_OBJECT

public:
    CityLabelsMapExtention(QString dbfFilePath, MapControl *mapControl, Layer *layer, QObject *parent = NULL);
    virtual ~CityLabelsMapExtention();

public slots:
    virtual void setChecked(bool checked);

    virtual void start();
    virtual void stop(MapExtention *sender);

private:
    qmapcontrol::Layer *layer_;
    QList<CityLabelGeometry*> labels_;
};

}

#endif