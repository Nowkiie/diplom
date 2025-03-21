/********************************************************************************
** Form generated from reading UI file 'formUnit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUNIT_H
#define UI_FORMUNIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_unitForm
{
public:
    QGridLayout *gridLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QGroupBox *send_groupBox;
    QLineEdit *lineEdit_degree;
    QLineEdit *lineEdit_sec;
    QLineEdit *lineEdit_arcsec;
    QPushButton *name_lat;
    QLabel *label_lat_send;
    QLabel *label_degree;
    QLabel *label_sec;
    QLabel *label_arcsec;
    QLabel *label_lon_send;
    QLineEdit *lineEdit_degree_2;
    QLabel *label_degree_2;
    QLineEdit *lineEdit_sec_2;
    QLabel *label_sec_2;
    QLineEdit *lineEdit_arcsec_2;
    QLabel *label_arcsec_2;
    QPushButton *name_lon;
    QGroupBox *hardware_groupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *group_antSystem;
    QHBoxLayout *horizontalLayout;
    QComboBox *combo_nameAntSystem;
    QPushButton *btn_addAntSystem;
    QPushButton *btn_delAntSystem;
    QPushButton *btn_changeAntSystem;
    QGroupBox *group_sender;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *combo_nameSender;
    QPushButton *btn_addSender;
    QPushButton *btn_delSender;
    QPushButton *btn_changeSender;
    QGroupBox *group_recvier;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *combo_nameRec;
    QPushButton *btn_addRec;
    QPushButton *btn_delRec;
    QPushButton *btn_changeRec;
    QPushButton *btnApply;

    void setupUi(QWidget *unitForm)
    {
        if (unitForm->objectName().isEmpty())
            unitForm->setObjectName(QString::fromUtf8("unitForm"));
        unitForm->resize(345, 534);
        gridLayout = new QGridLayout(unitForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nameLabel = new QLabel(unitForm);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 0, 0, 1, 1);

        nameEdit = new QLineEdit(unitForm);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        send_groupBox = new QGroupBox(unitForm);
        send_groupBox->setObjectName(QString::fromUtf8("send_groupBox"));
        send_groupBox->setMinimumSize(QSize(291, 81));
        send_groupBox->setMaximumSize(QSize(16777215, 81));
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
        label_lat_send = new QLabel(send_groupBox);
        label_lat_send->setObjectName(QString::fromUtf8("label_lat_send"));
        label_lat_send->setGeometry(QRect(10, 30, 47, 13));
        label_degree = new QLabel(send_groupBox);
        label_degree->setObjectName(QString::fromUtf8("label_degree"));
        label_degree->setGeometry(QRect(102, 20, 16, 16));
        label_degree->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/degree.png")));
        label_sec = new QLabel(send_groupBox);
        label_sec->setObjectName(QString::fromUtf8("label_sec"));
        label_sec->setGeometry(QRect(152, 20, 16, 16));
        label_sec->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/sec.png")));
        label_arcsec = new QLabel(send_groupBox);
        label_arcsec->setObjectName(QString::fromUtf8("label_arcsec"));
        label_arcsec->setGeometry(QRect(202, 20, 21, 16));
        label_arcsec->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/arcsec.png")));
        label_lon_send = new QLabel(send_groupBox);
        label_lon_send->setObjectName(QString::fromUtf8("label_lon_send"));
        label_lon_send->setGeometry(QRect(10, 50, 51, 16));
        lineEdit_degree_2 = new QLineEdit(send_groupBox);
        lineEdit_degree_2->setObjectName(QString::fromUtf8("lineEdit_degree_2"));
        lineEdit_degree_2->setGeometry(QRect(70, 50, 31, 16));
        label_degree_2 = new QLabel(send_groupBox);
        label_degree_2->setObjectName(QString::fromUtf8("label_degree_2"));
        label_degree_2->setGeometry(QRect(102, 42, 16, 16));
        label_degree_2->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/degree.png")));
        lineEdit_sec_2 = new QLineEdit(send_groupBox);
        lineEdit_sec_2->setObjectName(QString::fromUtf8("lineEdit_sec_2"));
        lineEdit_sec_2->setGeometry(QRect(120, 50, 31, 16));
        label_sec_2 = new QLabel(send_groupBox);
        label_sec_2->setObjectName(QString::fromUtf8("label_sec_2"));
        label_sec_2->setGeometry(QRect(152, 42, 16, 16));
        label_sec_2->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/sec.png")));
        lineEdit_arcsec_2 = new QLineEdit(send_groupBox);
        lineEdit_arcsec_2->setObjectName(QString::fromUtf8("lineEdit_arcsec_2"));
        lineEdit_arcsec_2->setGeometry(QRect(170, 50, 31, 16));
        label_arcsec_2 = new QLabel(send_groupBox);
        label_arcsec_2->setObjectName(QString::fromUtf8("label_arcsec_2"));
        label_arcsec_2->setGeometry(QRect(202, 42, 21, 16));
        label_arcsec_2->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/images/arcsec.png")));
        name_lon = new QPushButton(send_groupBox);
        name_lon->setObjectName(QString::fromUtf8("name_lon"));
        name_lon->setGeometry(QRect(230, 48, 31, 20));

        gridLayout->addWidget(send_groupBox, 1, 0, 1, 2);

        hardware_groupBox = new QGroupBox(unitForm);
        hardware_groupBox->setObjectName(QString::fromUtf8("hardware_groupBox"));
        verticalLayout = new QVBoxLayout(hardware_groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        group_antSystem = new QGroupBox(hardware_groupBox);
        group_antSystem->setObjectName(QString::fromUtf8("group_antSystem"));
        horizontalLayout = new QHBoxLayout(group_antSystem);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        combo_nameAntSystem = new QComboBox(group_antSystem);
        combo_nameAntSystem->setObjectName(QString::fromUtf8("combo_nameAntSystem"));

        horizontalLayout->addWidget(combo_nameAntSystem);

        btn_addAntSystem = new QPushButton(group_antSystem);
        btn_addAntSystem->setObjectName(QString::fromUtf8("btn_addAntSystem"));
        btn_addAntSystem->setMinimumSize(QSize(31, 23));
        btn_addAntSystem->setMaximumSize(QSize(31, 23));

        horizontalLayout->addWidget(btn_addAntSystem);

        btn_delAntSystem = new QPushButton(group_antSystem);
        btn_delAntSystem->setObjectName(QString::fromUtf8("btn_delAntSystem"));
        btn_delAntSystem->setMinimumSize(QSize(31, 23));
        btn_delAntSystem->setMaximumSize(QSize(31, 23));

        horizontalLayout->addWidget(btn_delAntSystem);

        btn_changeAntSystem = new QPushButton(group_antSystem);
        btn_changeAntSystem->setObjectName(QString::fromUtf8("btn_changeAntSystem"));
        btn_changeAntSystem->setMinimumSize(QSize(31, 23));
        btn_changeAntSystem->setMaximumSize(QSize(31, 23));

        horizontalLayout->addWidget(btn_changeAntSystem);


        verticalLayout->addWidget(group_antSystem);

        group_sender = new QGroupBox(hardware_groupBox);
        group_sender->setObjectName(QString::fromUtf8("group_sender"));
        horizontalLayout_2 = new QHBoxLayout(group_sender);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        combo_nameSender = new QComboBox(group_sender);
        combo_nameSender->setObjectName(QString::fromUtf8("combo_nameSender"));

        horizontalLayout_2->addWidget(combo_nameSender);

        btn_addSender = new QPushButton(group_sender);
        btn_addSender->setObjectName(QString::fromUtf8("btn_addSender"));
        btn_addSender->setMinimumSize(QSize(31, 23));
        btn_addSender->setMaximumSize(QSize(31, 23));

        horizontalLayout_2->addWidget(btn_addSender);

        btn_delSender = new QPushButton(group_sender);
        btn_delSender->setObjectName(QString::fromUtf8("btn_delSender"));
        btn_delSender->setMinimumSize(QSize(31, 23));
        btn_delSender->setMaximumSize(QSize(31, 23));

        horizontalLayout_2->addWidget(btn_delSender);

        btn_changeSender = new QPushButton(group_sender);
        btn_changeSender->setObjectName(QString::fromUtf8("btn_changeSender"));
        btn_changeSender->setMinimumSize(QSize(31, 23));
        btn_changeSender->setMaximumSize(QSize(31, 23));

        horizontalLayout_2->addWidget(btn_changeSender);


        verticalLayout->addWidget(group_sender);

        group_recvier = new QGroupBox(hardware_groupBox);
        group_recvier->setObjectName(QString::fromUtf8("group_recvier"));
        horizontalLayout_3 = new QHBoxLayout(group_recvier);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        combo_nameRec = new QComboBox(group_recvier);
        combo_nameRec->setObjectName(QString::fromUtf8("combo_nameRec"));

        horizontalLayout_3->addWidget(combo_nameRec);

        btn_addRec = new QPushButton(group_recvier);
        btn_addRec->setObjectName(QString::fromUtf8("btn_addRec"));
        btn_addRec->setMinimumSize(QSize(31, 23));
        btn_addRec->setMaximumSize(QSize(31, 23));

        horizontalLayout_3->addWidget(btn_addRec);

        btn_delRec = new QPushButton(group_recvier);
        btn_delRec->setObjectName(QString::fromUtf8("btn_delRec"));
        btn_delRec->setMinimumSize(QSize(31, 23));
        btn_delRec->setMaximumSize(QSize(31, 23));

        horizontalLayout_3->addWidget(btn_delRec);

        btn_changeRec = new QPushButton(group_recvier);
        btn_changeRec->setObjectName(QString::fromUtf8("btn_changeRec"));
        btn_changeRec->setMinimumSize(QSize(31, 23));
        btn_changeRec->setMaximumSize(QSize(31, 23));

        horizontalLayout_3->addWidget(btn_changeRec);


        verticalLayout->addWidget(group_recvier);


        gridLayout->addWidget(hardware_groupBox, 2, 0, 1, 2);

        btnApply = new QPushButton(unitForm);
        btnApply->setObjectName(QString::fromUtf8("btnApply"));

        gridLayout->addWidget(btnApply, 3, 1, 1, 1);


        retranslateUi(unitForm);

        QMetaObject::connectSlotsByName(unitForm);
    } // setupUi

    void retranslateUi(QWidget *unitForm)
    {
        unitForm->setWindowTitle(QApplication::translate("unitForm", "Unit Form", nullptr));
        nameLabel->setText(QApplication::translate("unitForm", "Name unit", nullptr));
        send_groupBox->setTitle(QApplication::translate("unitForm", "Coordinate", nullptr));
        lineEdit_degree->setInputMask(QApplication::translate("unitForm", "000", nullptr));
        lineEdit_sec->setInputMask(QApplication::translate("unitForm", "00", nullptr));
        lineEdit_arcsec->setInputMask(QApplication::translate("unitForm", "00", nullptr));
        name_lat->setText(QApplication::translate("unitForm", "N", nullptr));
        label_lat_send->setText(QApplication::translate("unitForm", "Latitude:", nullptr));
        label_degree->setText(QString());
        label_sec->setText(QString());
        label_arcsec->setText(QString());
        label_lon_send->setText(QApplication::translate("unitForm", "Longitude:", nullptr));
        lineEdit_degree_2->setInputMask(QApplication::translate("unitForm", "000", nullptr));
        label_degree_2->setText(QString());
        lineEdit_sec_2->setInputMask(QApplication::translate("unitForm", "00", nullptr));
        label_sec_2->setText(QString());
        lineEdit_arcsec_2->setInputMask(QApplication::translate("unitForm", "00", nullptr));
        label_arcsec_2->setText(QString());
        name_lon->setText(QApplication::translate("unitForm", "E", nullptr));
        hardware_groupBox->setTitle(QApplication::translate("unitForm", "Hardware", nullptr));
        group_antSystem->setTitle(QApplication::translate("unitForm", "ant system", nullptr));
        btn_addAntSystem->setText(QApplication::translate("unitForm", "+", nullptr));
        btn_delAntSystem->setText(QApplication::translate("unitForm", "-", nullptr));
        btn_changeAntSystem->setText(QApplication::translate("unitForm", "!", nullptr));
        group_sender->setTitle(QApplication::translate("unitForm", "sender", nullptr));
        btn_addSender->setText(QApplication::translate("unitForm", "+", nullptr));
        btn_delSender->setText(QApplication::translate("unitForm", "-", nullptr));
        btn_changeSender->setText(QApplication::translate("unitForm", "!", nullptr));
        group_recvier->setTitle(QApplication::translate("unitForm", "recvier", nullptr));
        btn_addRec->setText(QApplication::translate("unitForm", "+", nullptr));
        btn_delRec->setText(QApplication::translate("unitForm", "-", nullptr));
        btn_changeRec->setText(QApplication::translate("unitForm", "!", nullptr));
        btnApply->setText(QApplication::translate("unitForm", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class unitForm: public Ui_unitForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUNIT_H
