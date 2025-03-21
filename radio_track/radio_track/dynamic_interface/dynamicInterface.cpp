#include "dynamicInterface.h"
#include <QVBoxLayout>
#include <QToolButton>

using namespace track;

dynamicInterface::dynamicInterface()
{
    testF.setupUi(this);
    factoryInterface_ = std::make_shared<factoryInterface>();
    //create QWidget like as QToolBar
    toolBar = new QWidget(this);
    toolBar->setMaximumHeight(35);

    //create component for toolBar
    widgetCountStep = new QWidget();
    widgetCountStep->setMaximumHeight(20);
    widgetCountStep->setMinimumHeight(20);

    drawStep = new widgetForDrawStep(3, widgetCountStep);

    QVBoxLayout* layoutDrawWidget = new QVBoxLayout();
    layoutDrawWidget->addWidget(drawStep);
    layoutDrawWidget->setContentsMargins(0, 0, 0, 0);
    widgetCountStep->setLayout(layoutDrawWidget);

    /*  prevStep = new QPushButton();
    prevStep->setMaximumSize(20, 20);
    prevStep->setText("prev");*/

    QHBoxLayout* layoutToolBar = new QHBoxLayout();
    /* layoutToolBar->addWidget(prevStep);*/
    layoutToolBar->addWidget(widgetCountStep);
    layoutToolBar->setContentsMargins(0, 0, 0, 0);
    //add component to toolBar
    toolBar->setLayout(layoutToolBar);

    //create btn next step
    btnNextStep = new QPushButton();
    btnNextStep->setText(tr("Apply"));

    //add component on main window
    vbox = new QVBoxLayout;

    vbox->insertWidget(0, toolBar);
    vbox->insertWidget(2, btnNextStep);
    vbox->setContentsMargins(0, 0, 0, 0);
    testF.wi->setLayout(vbox);
    connect(btnNextStep, &QPushButton::clicked,
            [this](bool clicked)
            {
                returnParametr param = interface_->getStateAndData();
                state_ = param.first;
                createInterface(state_);
                emit nextStep(param);
                // drawStep->setParam(this->width(), this->height(), 2);
            });
}

void dynamicInterface::resizeEvent(QResizeEvent* event)
{
    drawStep->setParam(this->width(), this->height(), getNumberByState(state_));
}

void dynamicInterface::setEnableNextStep(bool enable)
{
    btnNextStep->setVisible(enable);
}

std::optional<QVariant> dynamicInterface::getDataFromWidgetInterface()
{
    return interface_->getStateAndData().second;
}

bool dynamicInterface::sendData(QVariant data)
{
    if (interface_.get() == nullptr)
    {
        QErrorMessage* errMessage = new QErrorMessage();
        errMessage->showMessage(
            tr("Choose an action by clicking on the button"));
        return true;
    }
    else
    {
        return interface_->setData(data);
    }
}

void dynamicInterface::addWidget(QWidget* test)
{
    vbox->insertWidget(1, test);
}

void dynamicInterface::createInterface(stateRadiotrack state)
{
    state_ = state;
    drawStep->setParam(this->width(), this->height(), getNumberByState(state_));
    interface_ = factoryInterface_->createInterface(state_);
    addWidget(interface_->getWidget());
    this->setWindowTitle(getWindowNameByState(state_));
}
