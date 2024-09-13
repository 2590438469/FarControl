/********************************************************************************
** Form generated from reading UI file 'basicform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICFORM_H
#define UI_BASICFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicForm
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *BasicForm)
    {
        if (BasicForm->objectName().isEmpty())
            BasicForm->setObjectName(QString::fromUtf8("BasicForm"));
        BasicForm->resize(400, 300);
        horizontalLayout = new QHBoxLayout(BasicForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(BasicForm);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);


        retranslateUi(BasicForm);

        QMetaObject::connectSlotsByName(BasicForm);
    } // setupUi

    void retranslateUi(QWidget *BasicForm)
    {
        BasicForm->setWindowTitle(QApplication::translate("BasicForm", "\345\257\274\345\207\272\351\242\204\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BasicForm: public Ui_BasicForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICFORM_H
