/********************************************************************************
** Form generated from reading UI file 'pagestationmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESTATIONMANAGE_H
#define UI_PAGESTATIONMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_pageStationManage
{
public:
    QHBoxLayout *horizontalLayout;
    customTableWidget *widget;

    void setupUi(QWidget *pageStationManage)
    {
        if (pageStationManage->objectName().isEmpty())
            pageStationManage->setObjectName(QString::fromUtf8("pageStationManage"));
        pageStationManage->resize(620, 448);
        horizontalLayout = new QHBoxLayout(pageStationManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new customTableWidget(pageStationManage);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(pageStationManage);

        QMetaObject::connectSlotsByName(pageStationManage);
    } // setupUi

    void retranslateUi(QWidget *pageStationManage)
    {
        pageStationManage->setWindowTitle(QApplication::translate("pageStationManage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageStationManage: public Ui_pageStationManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESTATIONMANAGE_H
