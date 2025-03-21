#pragma once
#include <QWidget>
#include <QVariant>
#include "../parse_file/workWithJson.h"
#include "../structParamNet.h"
#include "../structForSendParam.h"

using namespace structParamNet;

class paramNet : public QWidget
{
    Q_OBJECT
public:
    paramNet();

    void add(QVariant sendingParam, typeSendParam param);
    antSystem getDataForChangingAntSystem(int number);
    structParamNet::sender getDataForChangingSender(int number);
    recvier getDataForChangingRecvier(int number);
    void del(int number, typeSendParam param);
    void update(QVariant sendingParam, typeSendParam param, int number);
    void writeDatOnJson(QVector<unit> const& units);
    QVector<unit> readDataFromJson();
    QVector<antSystem> getPointerOnVectorAntSystem();
    QVector<structParamNet::sender> getPointerOnVectorSender();
    QVector<recvier> getPointerOnVectorRecvier();
    void readDataHardwareFromJson();
signals:
    void updateVectorAntSystem(QVector<antSystem>& antSystems);
    void updateVectorSender(QVector<structParamNet::sender>& send);
    void updateVectorRecvier(QVector<recvier>& recvs);

private:
    QVector<systemLink> systemLinks_;
    QVector<antSystem> antSystems_;
    QVector<structParamNet::sender> sender_;
    QVector<recvier> recv_;
    std::shared_ptr<workWithJson> workWithJson_;

    void writeDataOnHardwareIntoUnit(QVector<unit> units);
};
