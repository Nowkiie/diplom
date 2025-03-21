#pragma once
#include <QVBoxLayout>
#include "ui_formUnit.h"
#include "workWithHardware.h"
#include "../calculate/coordinate.h"
#include "../structParamNet.h"
#include "../structForSendParam.h"

using namespace track;

using namespace structParamNet;

class unitWindow : public QWidget
{
    Q_OBJECT
public:
    unitWindow();
    ~unitWindow();
    void updateUnit(unit unit);
    void initialMenu(QVariant listsHardware);
    void writeCoord(QPointF coordinate);
signals:
    void unitCreated(unit unit);
    void unitUpdate(unit unit);
    // void close();
protected:
    // void closeEvent(QCloseEvent* event) override;

private:
    Ui::unitForm unitForm_;
    bool updating = false;
    std::shared_ptr<workWithHardware> workWithHardware_;
    std::shared_ptr<coordinate> workWithCoord_;
    QVBoxLayout* vbox;

    void initUnitForm();
    std::optional<unit> getDataUnitForm();
    bool checkDataOnCorrectEnter(unit data);
};
