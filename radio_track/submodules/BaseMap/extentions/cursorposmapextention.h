#ifndef CURSORPOSMAPEXTENTION_H
#define CURSORPOSMAPEXTENTION_H

#include "persistentmapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для получения текущих координат курсора
*    @author Maxim Poylov
*/
class CursorPosMapExtention :
    public PersistentMapExtention
{
    Q_OBJECT

public:
    CursorPosMapExtention(MapControl *mapControl, QObject *parent = NULL);
    virtual ~CursorPosMapExtention();

private slots:
    void mouseEventCoordinate_(const QMouseEvent* evnt, const QPointF coordinate);

signals:
    void cursorPos(QPointF position);
    void cursorPos(QString position);
};
}

#endif