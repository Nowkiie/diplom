/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *wi;

    void setupUi(QWidget *testForm)
    {
        if (testForm->objectName().isEmpty())
            testForm->setObjectName(QString::fromUtf8("testForm"));
        testForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(testForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wi = new QWidget(testForm);
        wi->setObjectName(QString::fromUtf8("wi"));

        verticalLayout->addWidget(wi);


        retranslateUi(testForm);

        QMetaObject::connectSlotsByName(testForm);
    } // setupUi

    void retranslateUi(QWidget *testForm)
    {
        testForm->setWindowTitle(QApplication::translate("testForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testForm: public Ui_testForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
