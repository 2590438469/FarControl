/********************************************************************************
** Form generated from reading UI file 'missioncheck.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONCHECK_H
#define UI_MISSIONCHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MissionCheck
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *widget;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QCustomPlot *customPlot;

    void setupUi(QMainWindow *MissionCheck)
    {
        if (MissionCheck->objectName().isEmpty())
            MissionCheck->setObjectName(QString::fromUtf8("MissionCheck"));
        MissionCheck->resize(2200, 1350);
        MissionCheck->setMinimumSize(QSize(2200, 1350));
        MissionCheck->setMaximumSize(QSize(2200, 1350));
        MissionCheck->setStyleSheet(QString::fromUtf8(" #MissionCheck {border-image: url(:/image/blue.jpg)}"));
        centralwidget = new QWidget(MissionCheck);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 10, 121, 31));
        QFont font;
        font.setPointSize(19);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 2200, 1350));
        widget->setMinimumSize(QSize(2200, 1350));
        widget->setMaximumSize(QSize(2200, 1350));
        widget->setStyleSheet(QString::fromUtf8("#widget{border-image: url(:/image/blue.jpg)}"));
        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(70, 50, 241, 51));
        dateEdit->setFont(font);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 50, 201, 51));
        pushButton->setFont(font);
        customPlot = new QCustomPlot(widget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(80, 150, 1841, 1131));
        customPlot->setMinimumSize(QSize(0, 0));
        customPlot->setMaximumSize(QSize(9999, 9999));
        MissionCheck->setCentralWidget(centralwidget);
        widget->raise();
        label->raise();

        retranslateUi(MissionCheck);

        QMetaObject::connectSlotsByName(MissionCheck);
    } // setupUi

    void retranslateUi(QMainWindow *MissionCheck)
    {
        MissionCheck->setWindowTitle(QApplication::translate("MissionCheck", "MainWindow", nullptr));
        label->setText(QApplication::translate("MissionCheck", "\346\227\245\346\234\237", nullptr));
        pushButton->setText(QApplication::translate("MissionCheck", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MissionCheck: public Ui_MissionCheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONCHECK_H
