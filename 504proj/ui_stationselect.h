/********************************************************************************
** Form generated from reading UI file 'stationselect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONSELECT_H
#define UI_STATIONSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <combolabel.h>

QT_BEGIN_NAMESPACE

class Ui_StationSelect
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    ComboLabel *widget;

    void setupUi(QWidget *StationSelect)
    {
        if (StationSelect->objectName().isEmpty())
            StationSelect->setObjectName(QString::fromUtf8("StationSelect"));
        StationSelect->resize(400, 93);
        verticalLayout_2 = new QVBoxLayout(StationSelect);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(StationSelect);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(StationSelect);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(StationSelect);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new ComboLabel(StationSelect);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(StationSelect);

        QMetaObject::connectSlotsByName(StationSelect);
    } // setupUi

    void retranslateUi(QWidget *StationSelect)
    {
        StationSelect->setWindowTitle(QApplication::translate("StationSelect", "\345\237\272\347\253\231\351\200\211\346\213\251", nullptr));
        pushButton->setText(QApplication::translate("StationSelect", "\346\267\273\345\212\240", nullptr));
        pushButton_3->setText(QApplication::translate("StationSelect", "\345\210\240\351\231\244", nullptr));
        pushButton_2->setText(QApplication::translate("StationSelect", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationSelect: public Ui_StationSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONSELECT_H
