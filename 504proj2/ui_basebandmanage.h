/********************************************************************************
** Form generated from reading UI file 'basebandmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEBANDMANAGE_H
#define UI_BASEBANDMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_BaseBandManage
{
public:
    QHBoxLayout *horizontalLayout;
    customTableWidget *widget;

    void setupUi(QWidget *BaseBandManage)
    {
        if (BaseBandManage->objectName().isEmpty())
            BaseBandManage->setObjectName(QString::fromUtf8("BaseBandManage"));
        BaseBandManage->resize(459, 344);
        horizontalLayout = new QHBoxLayout(BaseBandManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new customTableWidget(BaseBandManage);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(BaseBandManage);

        QMetaObject::connectSlotsByName(BaseBandManage);
    } // setupUi

    void retranslateUi(QWidget *BaseBandManage)
    {
        BaseBandManage->setWindowTitle(QApplication::translate("BaseBandManage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseBandManage: public Ui_BaseBandManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEBANDMANAGE_H
