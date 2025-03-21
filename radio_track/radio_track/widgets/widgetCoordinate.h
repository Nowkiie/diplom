#pragma once
#include <QWidget>
#include <QVariant>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <fstream>
#include "../calculate/coordinate.h"
#include "../struct/structEnetringData.h"

namespace track::widget
{
class widgetCoordinate : public QWidget
{
    Q_OBJECT
public:
    widgetCoordinate(QString titleName);
    QWidget* getWidget();
    track::structures::coordInsideLineEdit getDataFromWidget();
    void setDataFromWidget(QPointF coord);
    void setDataFromWidget(track::structures::coordInsideLineEdit data);
    void clearDataFromWidget();
    QPointF getCoordFromEdit();

private:
    void createWidget(QString fileName);

    /*
     * \brief установка ограничений на ввод значений для координат
     */
    void setRangeForEneteringData();

    QWidget* wnd;
    QGroupBox* send_groupBox;
    QLineEdit* lineEdit_degree;
    QLineEdit* lineEdit_sec;
    QLineEdit* lineEdit_arcsec;
    QPushButton* name_lat;
    QLabel* label_lat_send;
    QLabel* label_degree;
    QLabel* label_sec;
    QLabel* label_arcsec;
    QLabel* label_lon_send;
    QLineEdit* lineEdit_degree_2;
    QLabel* label_degree_2;
    QLineEdit* lineEdit_sec_2;
    QLabel* label_sec_2;
    QLineEdit* lineEdit_arcsec_2;
    QLabel* label_arcsec_2;
    QPushButton* name_lon;
    QGridLayout* send_gridLayout;

    std::shared_ptr<coordinate> workWithCoord_;
};

inline widgetCoordinate::widgetCoordinate(QString titleName)
{
    workWithCoord_ = std::make_shared<coordinate>();
    createWidget(titleName);
    setRangeForEneteringData();
}

inline QWidget* widgetCoordinate::getWidget()
{
    return wnd;
}

inline track::structures::coordInsideLineEdit
    widgetCoordinate::getDataFromWidget()
{
    track::structures::coordInsideLineEdit coord;
    coord.latDegree = lineEdit_degree->text();
    coord.latSec = lineEdit_sec->text();
    coord.latArcsec = lineEdit_arcsec->text();
    coord.lonDegree = lineEdit_degree_2->text();
    coord.lonSec = lineEdit_sec_2->text();
    coord.lonArcsec = lineEdit_arcsec_2->text();
    coord.latPolarCoord = name_lat->text();
    coord.lonPolarCoord = name_lon->text();

    return coord;
}

inline void widgetCoordinate::setDataFromWidget(QPointF coord)
{
    Point point = workWithCoord_->getCoordFromPoint(coord);

    lineEdit_degree->setText(QString::number(point.lat.degree));
    lineEdit_sec->setText(QString::number(point.lat.sec));
    lineEdit_arcsec->setText(QString::number(point.lat.arsec));
    name_lat->setText(point.lat.card_direction);

    lineEdit_degree_2->setText(QString::number(point.lon.degree));
    lineEdit_sec_2->setText(QString::number(point.lon.sec));
    lineEdit_arcsec_2->setText(QString::number(point.lon.arsec));
    name_lon->setText(point.lon.card_direction);
}

inline void widgetCoordinate::setDataFromWidget(
    track::structures::coordInsideLineEdit data)
{
    lineEdit_degree->setText(data.latDegree);
    lineEdit_sec->setText(data.latSec);
    lineEdit_arcsec->setText(data.latArcsec);
    name_lat->setText(data.latPolarCoord);

    lineEdit_degree_2->setText(data.lonDegree);
    lineEdit_sec_2->setText(data.lonSec);
    lineEdit_arcsec_2->setText(data.lonArcsec);
    name_lon->setText(data.lonPolarCoord);
}

inline void widgetCoordinate::clearDataFromWidget()
{
    lineEdit_degree->setText("");
    lineEdit_sec->setText("");
    lineEdit_arcsec->setText("");

    lineEdit_degree_2->setText("");
    lineEdit_sec_2->setText("");
    lineEdit_arcsec_2->setText("");
}

inline QPointF widgetCoordinate::getCoordFromEdit()
{
    double lat = workWithCoord_->getDoubleCoordFromPoint(
        lineEdit_degree->text().toInt(), lineEdit_sec->text().toInt(),
        lineEdit_arcsec->text().toInt());
    double lon = workWithCoord_->getDoubleCoordFromPoint(
        lineEdit_degree_2->text().toInt(), lineEdit_sec_2->text().toInt(),
        lineEdit_arcsec_2->text().toInt());

    if (name_lon->text() == "W")
        lon = 0 - lon;

    if (name_lat->text() == "S")
        lat = 0 - lat;

    return QPointF{lon, lat};
}

inline void widgetCoordinate::createWidget(QString fileName)
{
    wnd = new QWidget();
    send_gridLayout = new QGridLayout(wnd);

    send_groupBox = new QGroupBox(wnd);
    send_groupBox->setObjectName(QString::fromUtf8("send_groupBox"));
    send_groupBox->setMinimumSize(QSize(291, 81));
    send_groupBox->setMaximumSize(QSize(16777215, 81));
    send_groupBox->setTitle(fileName);
    lineEdit_degree = new QLineEdit(send_groupBox);
    lineEdit_degree->setObjectName(QString::fromUtf8("lineEdit_degree"));
    lineEdit_degree->setGeometry(QRect(70, 30, 31, 16));
    lineEdit_degree->setMaxLength(3);
    lineEdit_sec = new QLineEdit(send_groupBox);
    lineEdit_sec->setObjectName(QString::fromUtf8("lineEdit_sec"));
    lineEdit_sec->setGeometry(QRect(120, 30, 31, 16));
    lineEdit_arcsec = new QLineEdit(send_groupBox);
    lineEdit_arcsec->setObjectName(QString::fromUtf8("lineEdit_arcsec"));
    lineEdit_arcsec->setGeometry(QRect(170, 30, 31, 16));
    name_lat = new QPushButton(send_groupBox);
    name_lat->setObjectName(QString::fromUtf8("name_lat"));
    name_lat->setGeometry(QRect(230, 28, 31, 20));
    name_lat->setText("N");
    label_lat_send = new QLabel(send_groupBox);
    label_lat_send->setObjectName(QString::fromUtf8("label_lat_send"));
    label_lat_send->setGeometry(QRect(10, 30, 47, 13));
    label_lat_send->setText(QObject::tr("latitude"));
    label_degree = new QLabel(send_groupBox);
    label_degree->setObjectName(QString::fromUtf8("label_degree"));
    label_degree->setGeometry(QRect(102, 20, 16, 16));
    label_degree->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/degree.png")));
    label_sec = new QLabel(send_groupBox);
    label_sec->setObjectName(QString::fromUtf8("label_sec"));
    label_sec->setGeometry(QRect(152, 20, 16, 16));
    label_sec->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/sec.png")));
    label_arcsec = new QLabel(send_groupBox);
    label_arcsec->setObjectName(QString::fromUtf8("label_arcsec"));
    label_arcsec->setGeometry(QRect(202, 20, 21, 16));
    label_arcsec->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/arcsec.png")));
    label_lon_send = new QLabel(send_groupBox);
    label_lon_send->setObjectName(QString::fromUtf8("label_lon_send"));
    label_lon_send->setGeometry(QRect(10, 50, 51, 16));
    label_lon_send->setText(QObject::tr("longitude"));
    lineEdit_degree_2 = new QLineEdit(send_groupBox);
    lineEdit_degree_2->setObjectName(QString::fromUtf8("lineEdit_degree_2"));
    lineEdit_degree_2->setGeometry(QRect(70, 50, 31, 16));
    label_degree_2 = new QLabel(send_groupBox);
    label_degree_2->setObjectName(QString::fromUtf8("label_degree_2"));
    label_degree_2->setGeometry(QRect(102, 42, 16, 16));
    label_degree_2->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/degree.png")));
    lineEdit_sec_2 = new QLineEdit(send_groupBox);
    lineEdit_sec_2->setObjectName(QString::fromUtf8("lineEdit_sec_2"));
    lineEdit_sec_2->setGeometry(QRect(120, 50, 31, 16));
    label_sec_2 = new QLabel(send_groupBox);
    label_sec_2->setObjectName(QString::fromUtf8("label_sec_2"));
    label_sec_2->setGeometry(QRect(152, 42, 16, 16));
    label_sec_2->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/sec.png")));
    lineEdit_arcsec_2 = new QLineEdit(send_groupBox);
    lineEdit_arcsec_2->setObjectName(QString::fromUtf8("lineEdit_arcsec_2"));
    lineEdit_arcsec_2->setGeometry(QRect(170, 50, 31, 16));
    label_arcsec_2 = new QLabel(send_groupBox);
    label_arcsec_2->setObjectName(QString::fromUtf8("label_arcsec_2"));
    label_arcsec_2->setGeometry(QRect(202, 42, 21, 16));
    label_arcsec_2->setPixmap(
        QPixmap(QString::fromUtf8(":/images/resources/images/arcsec.png")));
    name_lon = new QPushButton(send_groupBox);
    name_lon->setObjectName(QString::fromUtf8("name_lon"));
    name_lon->setGeometry(QRect(230, 48, 31, 20));
    name_lon->setText("E");

    send_gridLayout->addWidget(send_groupBox, 0, 0, 1, 2);

    wnd->setLayout(send_gridLayout);
}

inline void widgetCoordinate::setRangeForEneteringData()
{
    connect(lineEdit_degree, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 90)
                {
                    lineEdit_degree->setText("90");
                }
            });

    connect(lineEdit_degree_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 180)
                {
                    lineEdit_degree_2->setText("180");
                }
            });

    connect(lineEdit_sec, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    lineEdit_sec->setText("60");
                }
            });

    connect(lineEdit_sec_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    lineEdit_sec_2->setText("60");
                }
            });

    connect(lineEdit_arcsec, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    lineEdit_arcsec->setText("60");
                }
            });

    connect(lineEdit_arcsec_2, &QLineEdit::textChanged,
            [this](QString text)
            {
                int value = text.toInt();
                if (value > 60)
                {
                    lineEdit_arcsec_2->setText("60");
                }
            });

    connect(name_lat, &QPushButton::clicked,
            [this](bool clicked)
            {
                if (name_lat->text() == "N")
                    name_lat->setText("S");
                else
                    name_lat->setText("N");
            });

    connect(name_lon, &QPushButton::clicked,
            [this](bool clicked)
            {
                if (name_lon->text() == "W")
                    name_lon->setText("E");
                else
                    name_lon->setText("W");
            });
}
}  // namespace track::widget
