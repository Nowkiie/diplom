#ifndef LAYERSWITCHMAPEXTENTION_H
#define LAYERSWITCHMAPEXTENTION_H

#include "persistentmapextention.h"
#include <QAction>

namespace qmapcontrol
{


/*!
*    Класс расширения для переключения отображаемых слоев с картой/объектами
*    @author Maxim Poylov
*/
class LayerSwitchMapExtention :
    public qmapcontrol::PersistentMapExtention
{
    Q_OBJECT

public:
    LayerSwitchMapExtention(qmapcontrol::MapControl *mapControl, bool singleActive, QObject *parent = NULL);
    virtual ~LayerSwitchMapExtention();

    void addLayerToAction(qmapcontrol::Layer *layer, QAction *action);

    void switchLayers(QAction *action);

    QList<qmapcontrol::Layer*> layers(QAction *action);

    QSet<qmapcontrol::Layer*> activeLayers();

protected:
    QMap<QAction*, QList<qmapcontrol::Layer*> > actions_;

    void hideLayers_();

    void setLayersVisibility_(QAction* action, bool visible);

    bool singleActive_;

    QSet<QAction*> activeActions_;
};

/*!
*    Внутренний класс для переключения слоев по событию
*    @author Maxim Poylov
*/
class LayerSwitcher : public QObject
{
    friend LayerSwitchMapExtention;

    Q_OBJECT
protected:
    LayerSwitcher(LayerSwitchMapExtention *switcher, QAction *action);

public slots:
    void run();

private:
    QAction *action_;
};

}

#endif
