/********************************************************************************
** Form generated from reading UI file 'gemanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEMANAGE_H
#define UI_GEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_GeManage
{
public:
    QHBoxLayout *horizontalLayout;
    customTableWidget *widget;

    void setupUi(QWidget *GeManage)
    {
        if (GeManage->objectName().isEmpty())
            GeManage->setObjectName(QString::fromUtf8("GeManage"));
        GeManage->resize(400, 300);
        horizontalLayout = new QHBoxLayout(GeManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new customTableWidget(GeManage);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(GeManage);

        QMetaObject::connectSlotsByName(GeManage);
    } // setupUi

    void retranslateUi(QWidget *GeManage)
    {
        GeManage->setWindowTitle(QApplication::translate("GeManage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeManage: public Ui_GeManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMANAGE_H
