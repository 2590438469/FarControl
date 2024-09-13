/********************************************************************************
** Form generated from reading UI file 'missiontablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONTABLEWIDGET_H
#define UI_MISSIONTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionTableWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTableWidget *tableWidget;

    void setupUi(QWidget *MissionTableWidget)
    {
        if (MissionTableWidget->objectName().isEmpty())
            MissionTableWidget->setObjectName(QString::fromUtf8("MissionTableWidget"));
        MissionTableWidget->resize(560, 323);
        verticalLayout = new QVBoxLayout(MissionTableWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(MissionTableWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));
        lineEdit->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(MissionTableWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/search.png);"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(MissionTableWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(35, 35));
        pushButton_2->setMaximumSize(QSize(35, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/add.png);"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(MissionTableWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(35, 35));
        pushButton_5->setMaximumSize(QSize(35, 35));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/edit.png);"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(MissionTableWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(35, 35));
        pushButton_3->setMaximumSize(QSize(35, 35));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/delete.png);"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(MissionTableWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(35, 35));
        pushButton_4->setMaximumSize(QSize(35, 35));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/ok.png);"));

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(MissionTableWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(MissionTableWidget);

        QMetaObject::connectSlotsByName(MissionTableWidget);
    } // setupUi

    void retranslateUi(QWidget *MissionTableWidget)
    {
        MissionTableWidget->setWindowTitle(QApplication::translate("MissionTableWidget", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_5->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MissionTableWidget: public Ui_MissionTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONTABLEWIDGET_H
