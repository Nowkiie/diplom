#include "ncmonitor.h"
#include <QtWidgets/QApplication>
#include <QtPlugin>

#ifndef __linux__
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NcMonitor w;
    w.show();
    return a.exec();
}
