/********************************************************************************
** Form generated from reading UI file 'missionallconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONALLCONFIG_H
#define UI_MISSIONALLCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionAllConfig
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *MissionAllConfig)
    {
        if (MissionAllConfig->objectName().isEmpty())
            MissionAllConfig->setObjectName(QString::fromUtf8("MissionAllConfig"));
        MissionAllConfig->resize(627, 444);
        verticalLayout_2 = new QVBoxLayout(MissionAllConfig);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(MissionAllConfig);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        scrollArea = new QScrollArea(MissionAllConfig);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 613, 404));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(MissionAllConfig);

        QMetaObject::connectSlotsByName(MissionAllConfig);
    } // setupUi

    void retranslateUi(QWidget *MissionAllConfig)
    {
        MissionAllConfig->setWindowTitle(QApplication::translate("MissionAllConfig", "Form", nullptr));
        pushButton->setText(QApplication::translate("MissionAllConfig", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MissionAllConfig: public Ui_MissionAllConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONALLCONFIG_H
