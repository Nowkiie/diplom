#include "layerswitchmapextention.h"

#include <QListIterator>

using namespace qmapcontrol;

LayerSwitcher::LayerSwitcher(LayerSwitchMapExtention *switcher, QAction *action)
: QObject(switcher), action_(action)
{
}

void LayerSwitcher::run()
{
    static_cast<LayerSwitchMapExtention*>(parent())->switchLayers(action_);
}

LayerSwitchMapExtention::LayerSwitchMapExtention(qmapcontrol::MapControl *mapControl, bool singleActive, QObject *parent)
: qmapcontrol::PersistentMapExtention(mapControl, parent), singleActive_(singleActive)
{
}

LayerSwitchMapExtention::~LayerSwitchMapExtention()
{
}

void LayerSwitchMapExtention::addLayerToAction(qmapcontrol::Layer *layer, QAction *action)
{
    // если действия еще нет, то привязываем к нему событие переключения
    if (!actions_.contains(action))
    {
        LayerSwitcher *ls = new LayerSwitcher(this, action);
        connect(action, SIGNAL(triggered()), ls, SLOT(run()));
    }

    actions_[action].append(layer);
}

void LayerSwitchMapExtention::switchLayers(QAction *action)
{
    if (!actions_.contains(action)) return;

    if (singleActive_)
    {
        hideLayers_();
        setLayersVisibility_(action, true);
    }
    else
    {
        setLayersVisibility_(action, action->isChecked());
    }

}

QList<qmapcontrol::Layer*> LayerSwitchMapExtention::layers(QAction *action)
{
    return actions_[action];
}

QSet<qmapcontrol::Layer*> LayerSwitchMapExtention::activeLayers()
{
    // цикл необходим для того, чтобы список возвращаемых слоев выводился всегда в порядке добавленных действий
    QSet<qmapcontrol::Layer*> result;
    QList<QAction*> keys = actions_.keys();
    for (int i = 0; i < keys.count(); i++)
    {
        QAction *action = keys.at(i);
        if (activeActions_.contains(action))
        {
            result.unite(actions_[action].toSet());
        }
    }

    return result;
}

void LayerSwitchMapExtention::hideLayers_()
{
    QList<QAction*> keys = actions_.keys();
    for (int i = 0; i < keys.count(); i++)
    {
        setLayersVisibility_(keys.at(i), false);
    }
}

void LayerSwitchMapExtention::setLayersVisibility_(QAction* action, bool visible)
{
    if (visible) activeActions_.insert(action);
    else activeActions_.remove(action);

    QListIterator<qmapcontrol::Layer*> it(actions_[action]);
    while (it.hasNext())
    {
        it.next()->setVisible(visible);
    }
}


