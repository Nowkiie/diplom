#include "citylabelsmapextention.h"

#include <QStaticText>
#include <QFont>

#include <QFileInfo>

#include <QtSql>
#include <QSqlQuery>

using namespace qmapcontrol;
//------------------------------------------------------------------------------
// CityLabelsMapExtention
//------------------------------------------------------------------------------
CityLabelsMapExtention::CityLabelsMapExtention(QString dbfFilePath, MapControl *mapControl, Layer *layer, QObject *parent)
: CheckableMapExtention(mapControl, parent), layer_(layer)
{
    QFileInfo fi(dbfFilePath);
    QString dbDir = fi.absoluteDir().path();
    QString dbName = fi.baseName();

    QString connectionName = "CityLabelsConnection";

    QSqlDatabase db;
    if (QSqlDatabase::connectionNames().contains(connectionName))
    {
        db = QSqlDatabase::database(connectionName);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QODBC", connectionName);
    }

    QString connectionString;

    connectionString = "DRIVER={Driver do Microsoft dBase (*.dbf)}; DefaultDir=" + dbDir + "; FIL=dBASE IV;";

    db.setConnectOptions();
    db.setDatabaseName(connectionString);

    if (db.open())
    {
        QSqlQuery query(db);
        if (query.exec("SELECT NAMEASCII, LATITUDE, LONGITUDE FROM [" + dbName + "]"))
        {
            while (query.next()) {
                QString label = query.value(0).toString();
                qreal y = query.value(1).toDouble();
                qreal x = query.value(2).toDouble();

                CityLabelGeometry *g = new CityLabelGeometry();
                g->setLabel(label);
                g->setPosition(QPointF(x, y));
                labels_.append(g);
            }
        }
        else
        {
            qDebug() << "QUERY ERROR = " << db.lastError().text();
        }
        db.close();
    }
    else
    {
        qDebug() << "ERROR = " << db.lastError().text();
        return;
    }
}

CityLabelsMapExtention::~CityLabelsMapExtention()
{
    foreach(CityLabelGeometry *l, labels_)
    {
        delete l;
    }
    labels_.clear();
}

void CityLabelsMapExtention::setChecked(bool checked)
{
    if (checked && !isChecked())
    {
        foreach(CityLabelGeometry *l, labels_)
        {
            layer_->addGeometry(l);
        }
    }
    else if (!checked && isChecked())
    {
        foreach(CityLabelGeometry *l, labels_)
        {
            layer_->removeGeometry(l);
        }
    }
    mapControl_->update();

    CheckableMapExtention::setChecked(checked);
}

void CityLabelsMapExtention::start()
{
}

void CityLabelsMapExtention::stop(MapExtention *sender)
{
}
