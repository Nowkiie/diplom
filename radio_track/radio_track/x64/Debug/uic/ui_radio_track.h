/********************************************************************************
** Form generated from reading UI file 'radio_track.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIO_TRACK_H
#define UI_RADIO_TRACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "map_widget.h"

QT_BEGIN_NAMESPACE

class Ui_radio_trackClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    track::MapWidget *mapWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *radio_trackClass)
    {
        if (radio_trackClass->objectName().isEmpty())
            radio_trackClass->setObjectName(QString::fromUtf8("radio_trackClass"));
        radio_trackClass->resize(1057, 1009);
        centralWidget = new QWidget(radio_trackClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        mapWidget = new track::MapWidget(splitter);
        mapWidget->setObjectName(QString::fromUtf8("mapWidget"));
        splitter->addWidget(mapWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        radio_trackClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(radio_trackClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMovable(false);
        mainToolBar->setOrientation(Qt::Horizontal);
        mainToolBar->setFloatable(false);
        radio_trackClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(radio_trackClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        radio_trackClass->setStatusBar(statusBar);

        retranslateUi(radio_trackClass);

        QMetaObject::connectSlotsByName(radio_trackClass);
    } // setupUi

    void retranslateUi(QMainWindow *radio_trackClass)
    {
        radio_trackClass->setWindowTitle(QApplication::translate("radio_trackClass", "radio_track", nullptr));
    } // retranslateUi

};

namespace Ui {
    class radio_trackClass: public Ui_radio_trackClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIO_TRACK_H
