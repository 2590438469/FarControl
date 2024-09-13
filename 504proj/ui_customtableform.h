/********************************************************************************
** Form generated from reading UI file 'customtableform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMTABLEFORM_H
#define UI_CUSTOMTABLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomTableForm
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *CustomTableForm)
    {
        if (CustomTableForm->objectName().isEmpty())
            CustomTableForm->setObjectName(QString::fromUtf8("CustomTableForm"));
        CustomTableForm->resize(400, 300);
        horizontalLayout = new QHBoxLayout(CustomTableForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(CustomTableForm);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);


        retranslateUi(CustomTableForm);

        QMetaObject::connectSlotsByName(CustomTableForm);
    } // setupUi

    void retranslateUi(QWidget *CustomTableForm)
    {
        CustomTableForm->setWindowTitle(QApplication::translate("CustomTableForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomTableForm: public Ui_CustomTableForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMTABLEFORM_H
