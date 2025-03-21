#pragma once
#include "ui_settingsWidget.h"
#include <qstring.h>
#include "tableModel.h"
#include "../state.h"
#include "settingsHardware.h"
#include "../structParamNet.h"

namespace settings
{
struct parameters
{
    int heightAntSend;
    int heightAntRec;
    int procForOpenType;
    int procForHalfClosedType;
    double freq;
};

class settingsForm : public QWidget
{
    Q_OBJECT
public:
    settingsForm(tableModel* tableData);
    ~settingsForm() = default;

    // bool checkUploadUnit();
    //Unit getUnitByNumber(int number);
    //QVector<Unit> getPointerOnVectorUnits();
    void setStatusInitalWindow(bool param);
    void updateComboAntSystem(QVector<antSystem> const& antSystems);
    void updateComboSender(QVector<structParamNet::sender> const& send);
    void updateComboRecvier(QVector<structParamNet::recvier> const& recv);
    void getDataUpdatingAntSystem(antSystem ant_system);
    void getDataUpdatingSender(structParamNet::sender sender_);
    void getDataUpdatingRecvier(recvier recv);
    void setVisibleInfoText(bool visible);

private:
    void updateCopmboBox();

    Ui::setForm setForm;
    std::unique_ptr<settingsHardware> widgetSettingsHardware_;
    //std::shared_ptr<tableModel> tableData;
    bool initalForChooseUnit = false;
    QVector<antSystem> antSystems_;
    bool updating = false;
    int currentIndex;
signals:
    void dataUpload(stateRadiotrack state);
    void changeUnit(int idxRow);
    void deleteUnit(int idxRow);
    void appendUnit();

    void appendAntSystem(QVariant data, int number = -1);
    void changeAntSystem(int number);
    void delAntSystem(int number);
    void appendSender(QVariant data, int number = -1);
    void changeSender(int number);
    void delSender(int number);
    void appendRecvier(QVariant data, int number = -1);
    void changeRecvier(int number);
    void delRecvier(int number);
    void writeToJson();
};
}  // namespace settings
