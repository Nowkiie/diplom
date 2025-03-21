#include "ncmonitor.h"
#include <QVBoxLayout>
#include <QNetworkDatagram>
#include <QHeaderView>
#include <QNetworkProxy>

//максимальный размер строки имени узла
constexpr int maxNameSize = 255;
constexpr uint32_t packetTag = 0x4B414E5A;
constexpr uint16_t resolverServicePort = 781;

enum node_category
{
    node_local = 0,   // локальный узел
    node_global = 1,  // глобальный узел
    node_remote = 2,  // удалённый узел
};

#pragma pack(push, 1)
struct EnumeratorPacket
{
    uint32_t tag;                 //тег
    uint64_t recordKey;           //уникальный ключ записи
    uint16_t port;                //номер порта
    char pointName[maxNameSize];  // имя узла
    uint8_t category;             // тип узла
};
#pragma pack(pop)

class IntegerTableWidgetItem : public QTableWidgetItem
{
public:
    template <typename... Args>
    IntegerTableWidgetItem(Args&&... args)
        : QTableWidgetItem(std::forward<Args>(args)...)
    {
    }
    bool operator<(const QTableWidgetItem& other) const override
    {
        return text().toInt() < other.text().toInt();
    }
};

NcMonitor::NcMonitor(QWidget* parent)
    : QMainWindow(parent)
{
    resize(800, 400);
    setWindowIcon(QIcon(":/icons/icon.png"));
    setWindowTitle("NC Monitor");
    statusTable_ = new QTableWidget(this);
    setCentralWidget(new QWidget(this));
    QVBoxLayout* layout{};
    centralWidget()->setLayout(layout = new QVBoxLayout());
    layout->setMargin(2);
    layout->addWidget(statusTable_);

    statusTable_->setColumnCount(7);
    statusTable_->setHorizontalHeaderLabels(
        {"ID", "IP", "Port", "Type", "Category", "Requests", "Name"});
    statusTable_->horizontalHeader()->setStretchLastSection(true);
    statusTable_->verticalHeader()->setVisible(false);
    statusTable_->verticalHeader()->setDefaultSectionSize(18);
    statusTable_->setSelectionBehavior(QTableWidget::SelectRows);
    statusTable_->setSelectionMode(QTableWidget::SingleSelection);
    statusTable_->setEditTriggers({});
    statusTable_->setSortingEnabled(true);

    recvSocket_ = new QUdpSocket(this);
    recvSocket_->setProxy(QNetworkProxy::NoProxy);
    recvSocket_->bind(QHostAddress::AnyIPv4, resolverServicePort,
                      QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(
        recvSocket_, &QUdpSocket::readyRead, this,
        [this]()
        {
            readPending();
        });
}

void NcMonitor::readPending()
{
    while (recvSocket_->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = recvSocket_->receiveDatagram();
        processDatagram(datagram.data(), datagram.senderAddress().toString());
    }
}

void NcMonitor::processDatagram(const QByteArray& data, const QString& address)
{
    if (data.size() != sizeof(EnumeratorPacket))
    {
        return;
    }
    const EnumeratorPacket* packet =
        reinterpret_cast<const EnumeratorPacket*>(data.data());

    if (packet->tag != packetTag)
    {
        return;
    }
    addItem(packet->port != 0, packet->pointName, address, packet->category,
            packet->port, packet->recordKey);
}

void NcMonitor::addItem(bool server, QString pointName, QString remote,
                        int category, unsigned short port,
                        unsigned long long key)
{
    QString stringTag = key ? QString::number(key, 16) : "";

    QString tableId = stringTag + "$" + remote + "$" + pointName;

    counter_[tableId]++;

    for (int i = 0; i < statusTable_->rowCount(); i++)
    {
        if (statusTable_->item(i, 0)->data(Qt::UserRole).toString() == tableId)
        {
            statusTable_->setItem(
                i, 5,
                new IntegerTableWidgetItem(QString::number(counter_[tableId])));
            return;
        }
    }
    statusTable_->setSortingEnabled(false);
    auto newRowIndex = statusTable_->rowCount();
    statusTable_->insertRow(newRowIndex);

    statusTable_->setItem(newRowIndex, 0, new QTableWidgetItem(stringTag));
    statusTable_->setItem(newRowIndex, 1, new QTableWidgetItem(remote));
    statusTable_->setItem(
        newRowIndex, 2,
        new IntegerTableWidgetItem(port ? QString::number(port) : ""));

    statusTable_->setItem(newRowIndex, 3,
                          new QTableWidgetItem(QString::fromWCharArray(
                              server ? L"Server" : L"Client")));

    QString categoryName;
    switch (category)
    {
        case node_local:
            categoryName = QString::fromWCharArray(L"Local");
            break;
        case node_global:
            categoryName = QString::fromWCharArray(L"Global");
            break;
        case node_remote:
            categoryName = QString::fromWCharArray(L"Remote");
            break;
    }
    statusTable_->setItem(newRowIndex, 4, new QTableWidgetItem(categoryName));

    statusTable_->setItem(
        newRowIndex, 5,
        new IntegerTableWidgetItem(QString::number(counter_[tableId])));
    statusTable_->setItem(newRowIndex, 6, new QTableWidgetItem(pointName));
    statusTable_->item(newRowIndex, 0)->setData(Qt::UserRole, tableId);

    for (int i = 0; i < statusTable_->columnCount() - 1; i++)
    {
        statusTable_->resizeColumnToContents(i);
    }
    statusTable_->setSortingEnabled(true);
}
