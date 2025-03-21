/********************************************************************************
** Form generated from reading UI file 'settingsHardware.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSHARDWARE_H
#define UI_SETTINGSHARDWARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetHardware
{
public:
    QVBoxLayout* verticalLayout;
    QWidget* canvas;

    void setupUi(QWidget* widgetHardware)
    {
        if (widgetHardware->objectName().isEmpty())
            widgetHardware->setObjectName(QString::fromUtf8("widgetHardware"));
        widgetHardware->resize(400, 300);
        verticalLayout = new QVBoxLayout(widgetHardware);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        canvas = new QWidget(widgetHardware);
        canvas->setObjectName(QString::fromUtf8("canvas"));

        verticalLayout->addWidget(canvas);

        retranslateUi(widgetHardware);

        QMetaObject::connectSlotsByName(widgetHardware);
    }  // setupUi

    void retranslateUi(QWidget* widgetHardware)
    {
        widgetHardware->setWindowTitle(
            QApplication::translate("widgetHardware", "Form", nullptr));
    }  // retranslateUi
};

namespace Ui
{
class widgetHardware : public Ui_widgetHardware
{
};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_SETTINGSHARDWARE_H
