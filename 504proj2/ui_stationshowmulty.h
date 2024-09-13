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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationShowMulty
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *StationShowMulty)
    {
        if (StationShowMulty->objectName().isEmpty())
            StationShowMulty->setObjectName(QString::fromUtf8("StationShowMulty"));
        StationShowMulty->resize(400, 299);
        verticalLayout_2 = new QVBoxLayout(StationShowMulty);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(StationShowMulty);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(StationShowMulty);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(StationShowMulty);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);


        verticalLayout_2->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(StationShowMulty);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 386, 259));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_2->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(StationShowMulty);

        QMetaObject::connectSlotsByName(StationShowMulty);
    } // setupUi

    void retranslateUi(QWidget *StationShowMulty)
    {
        StationShowMulty->setWindowTitle(QApplication::translate("StationShowMulty", "Form", nullptr));
        pushButton->setText(QApplication::translate("StationShowMulty", "\346\267\273\345\212\240", nullptr));
        pushButton_2->setText(QApplication::translate("StationShowMulty", "\345\210\240\351\231\244", nullptr));
        pushButton_3->setText(QApplication::translate("StationShowMulty", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationShowMulty: public Ui_StationShowMulty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONSHOWMULTY_H
