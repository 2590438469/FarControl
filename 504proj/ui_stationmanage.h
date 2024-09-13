/********************************************************************************
** Form generated from reading UI file 'stationmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONMANAGE_H
#define UI_STATIONMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_StationManage
{
public:
    QHBoxLayout *horizontalLayout;
    customTableWidget *widget;

    void setupUi(QWidget *StationManage)
    {
        if (StationManage->objectName().isEmpty())
            StationManage->setObjectName(QString::fromUtf8("StationManage"));
        StationManage->resize(1300, 457);
        horizontalLayout = new QHBoxLayout(StationManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new customTableWidget(StationManage);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(StationManage);

        QMetaObject::connectSlotsByName(StationManage);
    } // setupUi

    void retranslateUi(QWidget *StationManage)
    {
        StationManage->setWindowTitle(QApplication::translate("StationManage", "\345\237\272\347\253\231\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationManage: public Ui_StationManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONMANAGE_H
