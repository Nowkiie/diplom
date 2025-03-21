#include "settingsForm.h"
#include "../structParamNet.h"

using namespace settings;

settingsForm::settingsForm(tableModel* tableData)
{
    setForm.setupUi(this);
    //tableData = std::make_shared<tableModel>();

    setForm.textInfo->setText(
        QObject::tr("You do not have units data."
                    "Please enter them manually or upload them to a file."));
    widgetSettingsHardware_ = std::make_unique<settingsHardware>();

    connect(setForm.btn4CloseInfo, &QPushButton::clicked,
            [this](bool clicked)
            {
                setForm.frameInfo->setVisible(false);
            });

    connect(setForm.buttonApply, &QPushButton::clicked,
            [this](bool cliked)
            {
                if (initalForChooseUnit)
                {
                    emit dataUpload(stateRadiotrack::chooseUnits);
                }
                else
                    emit writeToJson();
            });

    connect(setForm.btnAdd, &QToolButton::clicked,
            [this](bool clicked)
            {
                QModelIndex index = setForm.tableView->currentIndex();
                int selectedRow = index.row() + 1;
                QString text = QString::number(selectedRow);

                emit appendUnit();
                //tableData->append("sfd");
            });

    connect(setForm.btnDel, &QToolButton::clicked,
            [this](bool clicked)
            {
                QModelIndex idx = setForm.tableView->currentIndex();
                int idxRow = idx.row();
                emit deleteUnit(idxRow);
                // tableData->remove(idxRow);
            });

    connect(setForm.btnChange, &QToolButton::clicked,
            [this](bool clicked)
            {
                QModelIndex idx = setForm.tableView->currentIndex();
                int idxRow = idx.row();
                // tableData->change(idxRow);
                emit changeUnit(idxRow);
            });

    connect(setForm.btn_addAntSystem, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = false;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_ant_system);
                widgetSettingsHardware_->show();
            });

    connect(setForm.btn_changeAntSystem, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = true;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_ant_system);
                widgetSettingsHardware_->show();
                currentIndex = setForm.combo_nameAntSystem->currentIndex();
                emit changeAntSystem(currentIndex);
            });

    connect(setForm.btn_delAntSystem, &QPushButton::clicked,
            [this](bool clicked)
            {
                currentIndex = setForm.combo_nameAntSystem->currentIndex();
                emit delAntSystem(currentIndex);
            });

    connect(setForm.btn_addRec, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = false;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_recvier);
                widgetSettingsHardware_->show();
            });

    connect(setForm.btn_changeRec, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = true;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_recvier);
                widgetSettingsHardware_->show();
                currentIndex = setForm.combo_nameRec->currentIndex();
                emit changeRecvier(currentIndex);
            });

    connect(setForm.btn_delRec, &QPushButton::clicked,
            [this](bool clicked)
            {
                currentIndex = setForm.combo_nameRec->currentIndex();
                emit delRecvier(currentIndex);
            });

    connect(setForm.btn_addSender, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = false;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_sender);
                widgetSettingsHardware_->show();
            });

    connect(setForm.btn_changeSender, &QPushButton::clicked,
            [this](bool clicked)
            {
                updating = true;
                widgetSettingsHardware_->createInterface(
                    stateRadiotrack::settings_sender);
                widgetSettingsHardware_->show();
                currentIndex = setForm.combo_nameSender->currentIndex();
                emit changeSender(currentIndex);
            });

    connect(setForm.btn_delSender, &QPushButton::clicked,
            [this](bool clicked)
            {
                currentIndex = setForm.combo_nameSender->currentIndex();
                emit delSender(currentIndex);
            });

    connect(
        widgetSettingsHardware_.get(), &settingsHardware::applySettings,
        [this](settingsHardware::returnParametr param)
        {
            widgetSettingsHardware_->close();
            stateRadiotrack currentState = param.first;
            switch (currentState)
            {
                case stateRadiotrack::settings_ant_system:
                {
                    //TODO: убрать распаковку из Qvarian
                    QVariant qvar_paramAntSystem = param.second;
                    structParamNet::antSystem paramAntSystem =
                        qvar_paramAntSystem.value<structParamNet::antSystem>();
                    if (updating)
                    {
                        emit appendAntSystem(param.second, currentIndex);
                    }
                    else
                        emit appendAntSystem(param.second, -1);

                    break;
                }
                case stateRadiotrack::settings_sender:
                {
                    if (updating)
                    {
                        emit appendSender(param.second, currentIndex);
                    }
                    else
                        emit appendSender(param.second);
                    break;
                }
                case stateRadiotrack::settings_recvier:
                {
                    if (updating)
                    {
                        emit appendRecvier(param.second, currentIndex);
                    }
                    else
                        emit appendRecvier(param.second);
                    break;
                }
                default:
                {
                    break;
                }
            }
        });

    /*  connect(
        setForm.buttonApply, &QPushButton::clicked,
        [this](bool clicked)
        {
            emit writeToJson();
        });*/

    setForm.tableView->setModel(tableData);
}

void settingsForm::setVisibleInfoText(bool visible)
{
    setForm.frameInfo->setVisible(visible);
}

void settingsForm::setStatusInitalWindow(bool param)
{
    initalForChooseUnit = param;
}

//TODO: все функции по обновленную спсикаимен записать в одну
void settingsForm::updateComboRecvier(QVector<structParamNet::recvier> const& recv)
{
    setForm.combo_nameRec->clear();
    for (auto el : recv)
    {
        setForm.combo_nameRec->addItem(el.name);
    }
}

void settingsForm::updateComboAntSystem(QVector<antSystem> const& antSystems)
{
    setForm.combo_nameAntSystem->clear();
    for (auto el : antSystems)
    {
        setForm.combo_nameAntSystem->addItem(el.name);
    }
}

//TODO: все функции по написанную данных внутри поля внести в одну функцию
void settingsForm::getDataUpdatingSender(structParamNet::sender sender_)
{
    QVariant qvar_sender = QVariant::fromValue(sender_);
    widgetSettingsHardware_->writeData(qvar_sender);
}

void settingsForm::getDataUpdatingAntSystem(antSystem ant_system)
{
    QVariant qvar_antSystem = QVariant::fromValue(ant_system);
    widgetSettingsHardware_->writeData(qvar_antSystem);
}

void settingsForm::getDataUpdatingRecvier(recvier recv)
{
    QVariant qvar_recvier = QVariant::fromValue(recv);
    widgetSettingsHardware_->writeData(qvar_recvier);
}

void settingsForm::updateComboSender(QVector<structParamNet::sender> const& send)
{
    setForm.combo_nameSender->clear();

    for (auto el : send)
    {
        setForm.combo_nameSender->addItem(el.name);
    }
}

void settingsForm::updateCopmboBox() {}
