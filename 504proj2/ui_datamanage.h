/********************************************************************************
** Form generated from reading UI file 'datamanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMANAGE_H
#define UI_DATAMANAGE_H

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

class Ui_DataManage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_7;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QTableWidget *tableWidget;

    void setupUi(QWidget *DataManage)
    {
        if (DataManage->objectName().isEmpty())
            DataManage->setObjectName(QString::fromUtf8("DataManage"));
        DataManage->resize(523, 300);
        verticalLayout = new QVBoxLayout(DataManage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(DataManage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));
        lineEdit->setMaximumSize(QSize(150, 16777215));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(DataManage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/search.png);"));

        horizontalLayout->addWidget(pushButton);

        pushButton_8 = new QPushButton(DataManage);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(100, 40));
        pushButton_8->setMaximumSize(QSize(100, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        pushButton_8->setFont(font);
        pushButton_8->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);border-radius: 5px;padding: 10px;color: black;}QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}\n"
"QPushButton{color: rgb(0, 0, 0);}\n"
"QPushButton{border:2px groove gray;border-radius:12px;padding:2px 4px;}"));

        horizontalLayout->addWidget(pushButton_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_7 = new QPushButton(DataManage);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(35, 35));
        pushButton_7->setMaximumSize(QSize(35, 35));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/refresh.png);"));

        horizontalLayout->addWidget(pushButton_7);

        pushButton_2 = new QPushButton(DataManage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(35, 35));
        pushButton_2->setMaximumSize(QSize(35, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/add.png);"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(DataManage);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(35, 35));
        pushButton_5->setMaximumSize(QSize(35, 35));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/edit.png);"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(DataManage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(35, 35));
        pushButton_3->setMaximumSize(QSize(35, 35));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/delete.png);"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(DataManage);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(35, 35));
        pushButton_4->setMaximumSize(QSize(35, 35));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/ok.png);"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(DataManage);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(35, 35));
        pushButton_6->setMaximumSize(QSize(35, 35));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/download.svg);"));

        horizontalLayout->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(DataManage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(DataManage);

        QMetaObject::connectSlotsByName(DataManage);
    } // setupUi

    void retranslateUi(QWidget *DataManage)
    {
        DataManage->setWindowTitle(QApplication::translate("DataManage", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_8->setText(QApplication::translate("DataManage", "\351\253\230\347\272\247\347\255\233\351\200\211", nullptr));
        pushButton_7->setText(QString());
        pushButton_2->setText(QString());
        pushButton_5->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataManage: public Ui_DataManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMANAGE_H
