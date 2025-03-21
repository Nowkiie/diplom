/********************************************************************************
** Form generated from reading UI file 'settingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWIDGET_H
#define UI_SETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setForm
{
public:
    QGridLayout* gridLayout_2;
    QPushButton* buttonApply;
    QSpacerItem* horizontalSpacer;
    QFrame* frameInfo;
    QGridLayout* gridLayout;
    QPushButton* btn4CloseInfo;
    QSpacerItem* verticalSpacer;
    QTextEdit* textInfo;
    QTabWidget* tabWidget;
    QWidget* unit;
    QGridLayout* gridLayout_3;
    QLabel* label;
    QToolButton* btnChange;
    QToolButton* btnSave;
    QToolButton* btnAdd;
    QToolButton* btnDel;
    QTableView* tableView;
    QWidget* hardware;
    QVBoxLayout* verticalLayout;
    QGroupBox* group_antSystem;
    QHBoxLayout* horizontalLayout;
    QComboBox* combo_nameAntSystem;
    QPushButton* btn_addAntSystem;
    QPushButton* btn_delAntSystem;
    QPushButton* btn_changeAntSystem;
    QGroupBox* group_sender;
    QHBoxLayout* horizontalLayout_2;
    QComboBox* combo_nameSender;
    QPushButton* btn_addSender;
    QPushButton* btn_delSender;
    QPushButton* btn_changeSender;
    QGroupBox* group_recvier;
    QHBoxLayout* horizontalLayout_3;
    QComboBox* combo_nameRec;
    QPushButton* btn_addRec;
    QPushButton* btn_delRec;
    QPushButton* btn_changeRec;

    void setupUi(QWidget* setForm)
    {
        if (setForm->objectName().isEmpty())
            setForm->setObjectName(QString::fromUtf8("setForm"));
        setForm->resize(396, 539);
        gridLayout_2 = new QGridLayout(setForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        buttonApply = new QPushButton(setForm);
        buttonApply->setObjectName(QString::fromUtf8("buttonApply"));
        buttonApply->setMinimumSize(QSize(75, 23));
        buttonApply->setMaximumSize(QSize(75, 23));

        gridLayout_2->addWidget(buttonApply, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(299, 20, QSizePolicy::Expanding,
                                           QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        frameInfo = new QFrame(setForm);
        frameInfo->setObjectName(QString::fromUtf8("frameInfo"));
        frameInfo->setMinimumSize(QSize(378, 73));
        frameInfo->setMaximumSize(QSize(378, 73));
        frameInfo->setStyleSheet(
            QString::fromUtf8("background-color: rgba(255,0,0,20)"));
        frameInfo->setFrameShape(QFrame::StyledPanel);
        frameInfo->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frameInfo);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn4CloseInfo = new QPushButton(frameInfo);
        btn4CloseInfo->setObjectName(QString::fromUtf8("btn4CloseInfo"));
        btn4CloseInfo->setMinimumSize(QSize(20, 20));
        btn4CloseInfo->setMaximumSize(QSize(20, 20));
        btn4CloseInfo->setStyleSheet(
            QString::fromUtf8("background-color:rgba(0,0,0,0)"));
        btn4CloseInfo->setCheckable(false);

        gridLayout->addWidget(btn4CloseInfo, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 88, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        textInfo = new QTextEdit(frameInfo);
        textInfo->setObjectName(QString::fromUtf8("textInfo"));
        textInfo->setMinimumSize(QSize(351, 71));
        textInfo->setStyleSheet(
            QString::fromUtf8("background-color:rgba(0,0,0,0)"));
        textInfo->setFrameShape(QFrame::NoFrame);
        textInfo->setLineWidth(0);

        gridLayout->addWidget(textInfo, 0, 0, 2, 1);

        gridLayout_2->addWidget(frameInfo, 0, 0, 1, 2);

        tabWidget = new QTabWidget(setForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(361, 161));
        unit = new QWidget();
        unit->setObjectName(QString::fromUtf8("unit"));
        gridLayout_3 = new QGridLayout(unit);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(unit);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        btnChange = new QToolButton(unit);
        btnChange->setObjectName(QString::fromUtf8("btnChange"));

        gridLayout_3->addWidget(btnChange, 0, 1, 1, 1);

        btnSave = new QToolButton(unit);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout_3->addWidget(btnSave, 0, 2, 1, 1);

        btnAdd = new QToolButton(unit);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout_3->addWidget(btnAdd, 0, 3, 1, 1);

        btnDel = new QToolButton(unit);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));

        gridLayout_3->addWidget(btnDel, 0, 4, 1, 1);

        tableView = new QTableView(unit);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(tableView, 1, 0, 1, 5);

        tabWidget->addTab(unit, QString());
        hardware = new QWidget();
        hardware->setObjectName(QString::fromUtf8("hardware"));
        verticalLayout = new QVBoxLayout(hardware);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        group_antSystem = new QGroupBox(hardware);
        group_antSystem->setObjectName(QString::fromUtf8("group_antSystem"));
        horizontalLayout = new QHBoxLayout(group_antSystem);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        combo_nameAntSystem = new QComboBox(group_antSystem);
        combo_nameAntSystem->setObjectName(
            QString::fromUtf8("combo_nameAntSystem"));

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
        btn_changeAntSystem->setObjectName(
            QString::fromUtf8("btn_changeAntSystem"));
        btn_changeAntSystem->setMinimumSize(QSize(31, 23));
        btn_changeAntSystem->setMaximumSize(QSize(31, 23));

        horizontalLayout->addWidget(btn_changeAntSystem);

        verticalLayout->addWidget(group_antSystem);

        group_sender = new QGroupBox(hardware);
        group_sender->setObjectName(QString::fromUtf8("group_sender"));
        horizontalLayout_2 = new QHBoxLayout(group_sender);
        horizontalLayout_2->setObjectName(
            QString::fromUtf8("horizontalLayout_2"));
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

        group_recvier = new QGroupBox(hardware);
        group_recvier->setObjectName(QString::fromUtf8("group_recvier"));
        horizontalLayout_3 = new QHBoxLayout(group_recvier);
        horizontalLayout_3->setObjectName(
            QString::fromUtf8("horizontalLayout_3"));
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

        tabWidget->addTab(hardware, QString());

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 2);

        retranslateUi(setForm);

        btn4CloseInfo->setDefault(false);
        tabWidget->setCurrentIndex(1);

        QMetaObject::connectSlotsByName(setForm);
    }  // setupUi

    void retranslateUi(QWidget* setForm)
    {
        setForm->setWindowTitle(
            QApplication::translate("setForm", "Form", nullptr));
        buttonApply->setText(
            QApplication::translate("setForm", "Apply", nullptr));
        btn4CloseInfo->setText(
            QApplication::translate("setForm", "x", nullptr));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QApplication::translate(
            "setForm", "<html><head/><body><p><br/></p></body></html>",
            nullptr));
#endif  // QT_NO_TOOLTIP
        label->setText(QApplication::translate("setForm", "Units", nullptr));
        btnChange->setText(QApplication::translate("setForm", "chan", nullptr));
        btnSave->setText(QApplication::translate("setForm", "save", nullptr));
        btnAdd->setText(QApplication::translate("setForm", "add", nullptr));
        btnDel->setText(QApplication::translate("setForm", "del", nullptr));
        tabWidget->setTabText(
            tabWidget->indexOf(unit),
            QApplication::translate("setForm", "Unit", nullptr));
        group_antSystem->setTitle(
            QApplication::translate("setForm", "ant system", nullptr));
        btn_addAntSystem->setText(
            QApplication::translate("setForm", "+", nullptr));
        btn_delAntSystem->setText(
            QApplication::translate("setForm", "-", nullptr));
        btn_changeAntSystem->setText(
            QApplication::translate("setForm", "!", nullptr));
        group_sender->setTitle(
            QApplication::translate("setForm", "sender", nullptr));
        btn_addSender->setText(
            QApplication::translate("setForm", "+", nullptr));
        btn_delSender->setText(
            QApplication::translate("setForm", "-", nullptr));
        btn_changeSender->setText(
            QApplication::translate("setForm", "!", nullptr));
        group_recvier->setTitle(
            QApplication::translate("setForm", "recvier", nullptr));
        btn_addRec->setText(QApplication::translate("setForm", "+", nullptr));
        btn_delRec->setText(QApplication::translate("setForm", "-", nullptr));
        btn_changeRec->setText(
            QApplication::translate("setForm", "!", nullptr));
        tabWidget->setTabText(
            tabWidget->indexOf(hardware),
            QApplication::translate("setForm", "hardware", nullptr));
    }  // retranslateUi
};

namespace Ui
{
class setForm : public Ui_setForm
{
};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_SETTINGSWIDGET_H
