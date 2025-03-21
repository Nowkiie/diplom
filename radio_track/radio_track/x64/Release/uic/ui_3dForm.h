/********************************************************************************
** Form generated from reading UI file '3dForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_3DFORM_H
#define UI_3DFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout_2;
    QGroupBox* groupHeights;
    QVBoxLayout* verticalLayout;
    QLabel* label_min;
    QSlider* sliderMinHeight;
    QLabel* label_max;
    QSlider* sliderMaxHeight;
    QGroupBox* groupTypeCoord;
    QRadioButton* radioButtonGeo;
    QRadioButton* radioButtonDecart;
    QSpacerItem* verticalSpacer;

    void setupUi(QWidget* Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(129, 289);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupHeights = new QGroupBox(Form);
        groupHeights->setObjectName(QString::fromUtf8("groupHeights"));
        groupHeights->setMaximumSize(QSize(111, 121));
        verticalLayout = new QVBoxLayout(groupHeights);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_min = new QLabel(groupHeights);
        label_min->setObjectName(QString::fromUtf8("label_min"));

        verticalLayout->addWidget(label_min);

        sliderMinHeight = new QSlider(groupHeights);
        sliderMinHeight->setObjectName(QString::fromUtf8("sliderMinHeight"));
        sliderMinHeight->setMinimumSize(QSize(91, 22));
        sliderMinHeight->setMaximumSize(QSize(91, 22));
        sliderMinHeight->setMaximum(500);
        sliderMinHeight->setOrientation(Qt::Horizontal);
        sliderMinHeight->setTickPosition(QSlider::NoTicks);
        sliderMinHeight->setTickInterval(500);

        verticalLayout->addWidget(sliderMinHeight);

        label_max = new QLabel(groupHeights);
        label_max->setObjectName(QString::fromUtf8("label_max"));

        verticalLayout->addWidget(label_max);

        sliderMaxHeight = new QSlider(groupHeights);
        sliderMaxHeight->setObjectName(QString::fromUtf8("sliderMaxHeight"));
        sliderMaxHeight->setMinimumSize(QSize(91, 22));
        sliderMaxHeight->setMaximumSize(QSize(91, 22));
        sliderMaxHeight->setMinimum(200);
        sliderMaxHeight->setMaximum(4000);
        sliderMaxHeight->setPageStep(10);
        sliderMaxHeight->setTracking(true);
        sliderMaxHeight->setOrientation(Qt::Horizontal);
        sliderMaxHeight->setInvertedControls(false);
        sliderMaxHeight->setTickPosition(QSlider::NoTicks);
        sliderMaxHeight->setTickInterval(500);

        verticalLayout->addWidget(sliderMaxHeight);

        verticalLayout_2->addWidget(groupHeights);

        groupTypeCoord = new QGroupBox(Form);
        groupTypeCoord->setObjectName(QString::fromUtf8("groupTypeCoord"));
        groupTypeCoord->setMinimumSize(QSize(111, 80));
        groupTypeCoord->setMaximumSize(QSize(111, 80));
        radioButtonGeo = new QRadioButton(groupTypeCoord);
        radioButtonGeo->setObjectName(QString::fromUtf8("radioButtonGeo"));
        radioButtonGeo->setGeometry(QRect(10, 20, 82, 17));
        radioButtonDecart = new QRadioButton(groupTypeCoord);
        radioButtonDecart->setObjectName(
            QString::fromUtf8("radioButtonDecart"));
        radioButtonDecart->setGeometry(QRect(10, 50, 82, 17));

        verticalLayout_2->addWidget(groupTypeCoord);

        verticalSpacer = new QSpacerItem(109, 48, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout->addLayout(verticalLayout_2);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    }  // setupUi

    void retranslateUi(QWidget* Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        groupHeights->setTitle(
            QApplication::translate("Form", "Height range", nullptr));
        label_min->setText(QApplication::translate("Form", "min", nullptr));
        label_max->setText(QApplication::translate("Form", "max", nullptr));
        groupTypeCoord->setTitle(
            QApplication::translate("Form", "Type coordinate", nullptr));
        radioButtonGeo->setText(
            QApplication::translate("Form", "Geo", nullptr));
        radioButtonDecart->setText(
            QApplication::translate("Form", "Decart", nullptr));
    }  // retranslateUi
};

namespace Ui
{
class Form : public Ui_Form
{
};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_3DFORM_H
