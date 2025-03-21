#pragma once
#include <QString>
#include <QStringList>

namespace qmapcontrol
{
const char * const tileLocalPath = "/%1/%2/%3";

static QString tilesToUrl(int x, int y, int z, const void *uniq = nullptr)
{
    //для разных экземпляров класса - разные url
    return QString::number(size_t(uniq)) +
        QString(tileLocalPath).arg(z).arg(x).arg(y);
}
static bool urlToTiles(QString query, int &x, int &y, int &z)
{
    auto splitted = query.split('/');
    if (splitted.size() == 4)
    {
        z = splitted[1].toInt();
        x = splitted[2].toInt();
        y = splitted[3].toInt();
        return true;
    }
    return false;
}

}