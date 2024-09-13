/********************************************************************************
** Form generated from reading UI file 'stationshowmulty.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONSHOWMULTY_H
#define UI_STATIONSHOWMULTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationShowMulty
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *StationShowMulty)
    {
        if (StationShowMulty->objectName().isEmpty())
            StationShowMulty->setObjectName(QString::fromUtf8("StationShowMulty"));
        StationShowMulty->resize(400, 299);
        horizontalLayout = new QHBoxLayout(StationShowMulty);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(StationShowMulty);

        QMetaObject::connectSlotsByName(StationShowMulty);
    } // setupUi

    void retranslateUi(QWidget *StationShowMulty)
    {
        StationShowMulty->setWindowTitle(QApplication::translate("StationShowMulty", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationShowMulty: public Ui_StationShowMulty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONSHOWMULTY_H
