/********************************************************************************
** Form generated from reading UI file 'battleform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLEFORM_H
#define UI_BATTLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BattleForm
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *BattleForm)
    {
        if (BattleForm->objectName().isEmpty())
            BattleForm->setObjectName(QString::fromUtf8("BattleForm"));
        BattleForm->resize(400, 300);
        horizontalLayout = new QHBoxLayout(BattleForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(BattleForm);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);


        retranslateUi(BattleForm);

        QMetaObject::connectSlotsByName(BattleForm);
    } // setupUi

    void retranslateUi(QWidget *BattleForm)
    {
        BattleForm->setWindowTitle(QApplication::translate("BattleForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BattleForm: public Ui_BattleForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLEFORM_H
