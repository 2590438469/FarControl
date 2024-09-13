/********************************************************************************
** Form generated from reading UI file 'missionchart.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONCHART_H
#define UI_MISSIONCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_missionchart
{
public:
    QCustomPlot *customPlot;

    void setupUi(QWidget *missionchart)
    {
        if (missionchart->objectName().isEmpty())
            missionchart->setObjectName(QString::fromUtf8("missionchart"));
        missionchart->resize(964, 565);
        customPlot = new QCustomPlot(missionchart);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(20, 20, 921, 521));
        customPlot->setMaximumSize(QSize(1920, 1720));

        retranslateUi(missionchart);

        QMetaObject::connectSlotsByName(missionchart);
    } // setupUi

    void retranslateUi(QWidget *missionchart)
    {
        missionchart->setWindowTitle(QApplication::translate("missionchart", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class missionchart: public Ui_missionchart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONCHART_H
