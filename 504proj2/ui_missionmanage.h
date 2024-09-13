/********************************************************************************
** Form generated from reading UI file 'missionmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONMANAGE_H
#define UI_MISSIONMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <missiontablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_MissionManage
{
public:
    QHBoxLayout *horizontalLayout;
    MissionTableWidget *widget;

    void setupUi(QWidget *MissionManage)
    {
        if (MissionManage->objectName().isEmpty())
            MissionManage->setObjectName(QString::fromUtf8("MissionManage"));
        MissionManage->resize(614, 390);
        horizontalLayout = new QHBoxLayout(MissionManage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MissionTableWidget(MissionManage);
        widget->setObjectName(QString::fromUtf8("widget"));
        QFont font;
        font.setPointSize(14);
        widget->setFont(font);

        horizontalLayout->addWidget(widget);


        retranslateUi(MissionManage);

        QMetaObject::connectSlotsByName(MissionManage);
    } // setupUi

    void retranslateUi(QWidget *MissionManage)
    {
        MissionManage->setWindowTitle(QApplication::translate("MissionManage", "\344\273\273\345\212\241\345\256\217\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MissionManage: public Ui_MissionManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONMANAGE_H
