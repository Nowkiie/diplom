#ifndef MAPEXTENTIONMANAGER_H
#define MAPEXTENTIONMANAGER_H

#include <QList>
#include "mapextention.h"

namespace qmapcontrol
{
/*!
    *    Класс для управления работой раширений карты MapExtentions
    *    @author Maxim Poylov
    */
class MapExtentionManager : public QObject
{
    Q_OBJECT

public:   
    MapExtentionManager(QObject* parent = NULL);
    MapExtentionManager(bool needToStopButLast = true, QObject* parent = NULL);
    ~MapExtentionManager();

    void AddExtention(MapExtention* extention);
    void RemoveExtention(MapExtention* extention);

private slots:
    void started_(MapExtention* extention);
    void done_(MapExtention* extention);

private:
    QList<MapExtention*> mapExtentions_;
    bool needToStopButLast_;
};
}  // namespace qmapcontrol
#endif
