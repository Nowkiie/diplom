#include "cursorposmapextention.h"

using namespace qmapcontrol;

CursorPosMapExtention::CursorPosMapExtention(MapControl *mapControl, QObject *parent)
    : PersistentMapExtention(mapControl, parent)
{
    connect(mapControl_, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)), this, SLOT(mouseEventCoordinate_(const QMouseEvent*, const QPointF)));
}

CursorPosMapExtention::~CursorPosMapExtention()
{
}

void CursorPosMapExtention::mouseEventCoordinate_(const QMouseEvent* evnt, const QPointF coordinate)
{
    QPointF  cursorpos = coordinate;

    while (cursorpos.x() >= 180) cursorpos.rx() -= 360;
    while (cursorpos.x() <= -180) cursorpos.rx() += 360;

    emit(cursorPos(cursorpos));

    bool neg;
    QString lon, lat;

    neg = cursorpos.x()<0;
    if (neg) cursorpos.setX(-cursorpos.x());

	int g, m, s;
	g = (int)cursorpos.x();
	m = (int)((cursorpos.x() - g) * 60);
	s = int(((cursorpos.x() - g) * 60 - m) * 60);
	
	lon = QString("%1\302\260%2'%3\"")
		.arg(g, 3, 'i', 0, QChar('0'))
		.arg(m, 2, 'i', 0, QChar('0'))
		.arg(s, 2, 'i', 0, QChar('0'));

	if (neg) lon += QString("з.д");
    else lon += QString("в.д");

	

    neg = cursorpos.y()<0;
    if (neg) cursorpos.setY(-cursorpos.y());

	g = (int)cursorpos.y();
	m = (int)((cursorpos.y() - g) * 60);
	s = int(((cursorpos.y() - g) * 60 - m) * 60);
	
	lat = QString("%1\302\260%2'%3\"")
		.arg(g, 3, 'i', 0, QChar('0'))
		.arg(m, 2, 'i', 0, QChar('0'))
		.arg(s, 2, 'i', 0, QChar('0'));
	
	if (neg) lat += QString("ю.ш.");
    else lat += QString("с.ш.");

    QString result = "x" + QString("%1 ").arg(mapControl_->currentZoom() + 1) + lat + " " + lon;

    emit(cursorPos(result));
}
