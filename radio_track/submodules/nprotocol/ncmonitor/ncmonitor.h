#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QUdpSocket>

class NcMonitor : public QMainWindow
{
public:
    NcMonitor(QWidget* parent = Q_NULLPTR);

private:
    void readPending();
    void processDatagram(const QByteArray& data, const QString& address);
    void addItem(bool server, QString pointName, QString remote, int category,
                 unsigned short port, unsigned long long key);

    QTableWidget* statusTable_;
    QUdpSocket* recvSocket_;
    QMap<QString, int> counter_;
};
