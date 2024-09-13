/********************************************************************************
** Form generated from reading UI file 'datasourcemanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASOURCEMANAGE_H
#define UI_DATASOURCEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_DataSourceManage
{
public:
    QHBoxLayout *horizontalLayout;
    customTableWidget *widget;

    void setupUi(QWidget *DataSourceManage)
    {
        if (DataSourceManage->objectName().isEmpty())
            DataSourceManage->setObjectName(QString::fromUtf8("DataSourceManage"));
        DataSourceManage->resize(483, 374);
        horizontalLayout = new QHBoxLayout(DataSourceManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new customTableWidget(DataSourceManage);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(DataSourceManage);

        QMetaObject::connectSlotsByName(DataSourceManage);
    } // setupUi

    void retranslateUi(QWidget *DataSourceManage)
    {
        DataSourceManage->setWindowTitle(QApplication::translate("DataSourceManage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataSourceManage: public Ui_DataSourceManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASOURCEMANAGE_H
