#pragma once
#include "ui_test.h"
#include "factory.h"
#include <QPushButton>
#include <QVariant>
#include <QMetaType>
#include <QToolBar>
#include "../draw_geometry/drawStep.h"

namespace track
{
class dynamicInterface : public QWidget
{
    Q_OBJECT
public:
    using returnParametr = std::pair<stateRadiotrack, QVariant>;
    dynamicInterface();

    void createInterface(stateRadiotrack state);
    void addWidget(QWidget* test);

    bool sendData(QVariant data);

    void setEnableNextStep(bool enable);

    std::optional<QVariant> getDataFromWidgetInterface();

    void resizeEvent(QResizeEvent* event) override;
signals:
    void nextStep(returnParametr);

private:
    Ui::testForm testF;
    std::shared_ptr<factoryInterface> factoryInterface_;
    stateRadiotrack state_;
    QPushButton* btnNextStep;
    std::shared_ptr<baseInterface> interface_;
    QVBoxLayout* vbox;
    QWidget* toolBar;
    QWidget* widgetCountStep;
    QPushButton* prevStep;
    widgetForDrawStep* drawStep;
};
}  // namespace track
