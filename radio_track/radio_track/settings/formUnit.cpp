#include <QErrorMessage>
#include <QCheckBox>
#include "formUnit.h"

//TODO: удалить кнопки для аппаратуры в окне создания пункта
unitWindow::unitWindow()
{
    unitForm_.setupUi(this);

    workWithHardware_ = std::make_shared<workWithHardware>();
    workWithCoord_ = std::make_shared<coordinate>();

    connect(unitForm_.btnApply, &QPushButton::clicked,
            [this](bool clicked)
            {
                if (!updating)
                {
                    if (getDataUnitForm().has_value())
                    {
                        unit newUnit = getDataUnitForm().value();
                        emit unitCreated(newUnit);
                    }
                    else
                    {
                        QErrorMessage* errMessage = new QErrorMessage();
                        errMessage->showMessage(
                            QObject::tr("uncorrect eneterd data"));
                        errMessage->activateWindow();
                    }
                }
                else
                {
                    if (getDataUnitForm().has_value())
                    {
                        unit updateUnit = getDataUnitForm().value();
                        updating = false;
                        emit unitUpdate(updateUnit);
                    }
                    else
                    {
                        QErrorMessage* errMessage = new QErrorMessage();
                        errMessage->showMessage(
                            QObject::tr("uncorrect eneterd data"));
                        errMessage->activateWindow();
                    }
                }
            });

    connect(unitForm_.lineEdit_degree, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 90)
                {
                    unitForm_.lineEdit_degree->setText("90");
                }
            });

    connect(unitForm_.lineEdit_degree_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 180)
                {
                    unitForm_.lineEdit_degree_2->setText("180");
                }
            });

    connect(unitForm_.lineEdit_sec, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    unitForm_.lineEdit_sec->setText("60");
                }
            });

    connect(unitForm_.lineEdit_sec_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    unitForm_.lineEdit_sec_2->setText("60");
                }
            });

    connect(unitForm_.lineEdit_arcsec, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    unitForm_.lineEdit_arcsec->setText("60");
                }
            });

    connect(unitForm_.lineEdit_arcsec_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    unitForm_.lineEdit_arcsec_2->setText("60");
                }
            });
}

//void unitWindow::closeEvent(QCloseEvent* event)
//{
//    emit close();
//}

void unitWindow::writeCoord(QPointF coordinate)
{
    Point coord = workWithCoord_->getCoordFromPoint(coordinate);
    unitForm_.lineEdit_degree->setText(QString::number(coord.lat.degree));
    unitForm_.lineEdit_sec->setText(QString::number(coord.lat.sec));
    unitForm_.lineEdit_arcsec->setText(QString::number(coord.lat.arsec));
    unitForm_.name_lat->setText(coord.lat.card_direction);

    unitForm_.lineEdit_degree_2->setText(QString::number(coord.lon.degree));
    unitForm_.lineEdit_sec_2->setText(QString::number(coord.lon.sec));
    unitForm_.lineEdit_arcsec_2->setText(QString::number(coord.lon.arsec));
    unitForm_.name_lon->setText(coord.lon.card_direction);
}

void unitWindow::initialMenu(QVariant listsHardware)
{
    unitForm_.combo_nameAntSystem->clear();
    unitForm_.combo_nameSender->clear();
    unitForm_.combo_nameRec->clear();

    paramHardware hardwares = listsHardware.value<paramHardware>();
    for (auto el : hardwares.ant_system)
    {
        unitForm_.combo_nameAntSystem->addItem(el.name);
    }

    unitForm_.combo_nameSender->addItem("none");
    for (auto el : hardwares.send)
    {
        unitForm_.combo_nameSender->addItem(el.name);
    }
    unitForm_.combo_nameRec->addItem("none");
    for (auto el : hardwares.recv)
    {
        unitForm_.combo_nameRec->addItem(el.name);
    }
}

bool unitWindow::checkDataOnCorrectEnter(unit data)
{
    if (data.name == "")
    {
        return false;
    }
    structures::coordInsideLineEdit coordStr = data.coord_str.value();
    if (coordStr.lonDegree == "" || coordStr.latDegree == "")
    {
        return false;
    }
    if (data.hardware_.ant_system.name == "")
    {
        return false;
    }
    if (data.hardware_.send.name == "-" && data.hardware_.rec.name == "-")
    {
        return false;
    }
    return true;
}

std::optional<unit> unitWindow::getDataUnitForm()
{
    unit data;
    QString name = unitForm_.nameEdit->text();
    double coordLat = workWithCoord_->getDoubleCoordFromPoint(
        unitForm_.lineEdit_degree->text().toInt(),
        unitForm_.lineEdit_sec->text().toInt(),
        unitForm_.lineEdit_arcsec->text().toInt());
    double coordLon = workWithCoord_->getDoubleCoordFromPoint(
        unitForm_.lineEdit_degree_2->text().toInt(),
        unitForm_.lineEdit_sec_2->text().toInt(),
        unitForm_.lineEdit_arcsec_2->text().toInt());
    QVector<QString> listNameHardware;
    listNameHardware.push_back(unitForm_.combo_nameAntSystem->currentText());

    data.name = name;
    data.coord = QPointF{coordLon, coordLat};

    structures::coordInsideLineEdit coordStr;
    coordStr.latDegree = unitForm_.lineEdit_degree->text();
    coordStr.latSec = unitForm_.lineEdit_sec->text();
    coordStr.latArcsec = unitForm_.lineEdit_arcsec->text();

    coordStr.lonDegree = unitForm_.lineEdit_degree_2->text();
    coordStr.lonSec = unitForm_.lineEdit_sec_2->text();
    coordStr.lonArcsec = unitForm_.lineEdit_arcsec_2->text();

    data.coord_str = coordStr;
    //заполнение только названий аппартуры
    antSystem ant;
    ant.name = unitForm_.combo_nameAntSystem->currentText();
    data.hardware_.ant_system = ant;

    structParamNet::sender send;
    if (unitForm_.combo_nameSender->currentText() == "none")
    {
        send.name = "-";
    }
    else
        send.name = unitForm_.combo_nameSender->currentText();

    data.hardware_.send = send;

    recvier recv;
    if (unitForm_.combo_nameRec->currentText() == "none")
    {
        recv.name = "-";
    }
    else
        recv.name = unitForm_.combo_nameRec->currentText();
    data.hardware_.rec = recv;

    bool resultCheckingDataOnCorretFormat = checkDataOnCorrectEnter(data);
    if (resultCheckingDataOnCorretFormat)
        return data;
    return {};
}

void unitWindow::initUnitForm() {}

void unitWindow::updateUnit(unit unit)
{
    updating = true;
    unitForm_.nameEdit->setText(unit.name);

    Point geoCoord = workWithCoord_->getCoordFromPoint(unit.coord);
    //latitude
    unitForm_.lineEdit_degree->setText(QString::number(geoCoord.lat.degree));
    unitForm_.lineEdit_sec->setText(QString::number(geoCoord.lat.sec));
    unitForm_.lineEdit_arcsec->setText(QString::number(geoCoord.lat.arsec));
    unitForm_.name_lat->setText(geoCoord.lat.card_direction);

    //longitude
    unitForm_.lineEdit_degree_2->setText(QString::number(geoCoord.lon.degree));
    unitForm_.lineEdit_sec_2->setText(QString::number(geoCoord.lon.sec));
    unitForm_.lineEdit_arcsec_2->setText(QString::number(geoCoord.lon.arsec));
    unitForm_.name_lon->setText(geoCoord.lon.card_direction);

    unitForm_.combo_nameAntSystem->setCurrentText(
        unit.hardware_.ant_system.name);
    if (unit.hardware_.rec.name != "-")
    {
        unitForm_.combo_nameRec->setCurrentText(unit.hardware_.rec.name);
    }
    else
        unitForm_.combo_nameRec->setCurrentText("none");

    if (unit.hardware_.send.name != "-")
    {
        unitForm_.combo_nameSender->setCurrentText(unit.hardware_.send.name);
    }
    else
        unitForm_.combo_nameSender->setCurrentText("none");
}

unitWindow::~unitWindow() {}
