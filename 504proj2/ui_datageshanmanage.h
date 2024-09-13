/********************************************************************************
** Form generated from reading UI file 'datageshanmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAGESHANMANAGE_H
#define UI_DATAGESHANMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataGeshanManage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QTableWidget *tableWidget;

    void setupUi(QWidget *DataGeshanManage)
    {
        if (DataGeshanManage->objectName().isEmpty())
            DataGeshanManage->setObjectName(QString::fromUtf8("DataGeshanManage"));
        DataGeshanManage->resize(869, 510);
        verticalLayout = new QVBoxLayout(DataGeshanManage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(DataGeshanManage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));
        lineEdit->setMaximumSize(QSize(150, 16777215));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(DataGeshanManage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/image/search.svg);"));

        horizontalLayout->addWidget(pushButton);

        label = new QLabel(DataGeshanManage);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(DataGeshanManage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(35, 35));
        pushButton_2->setMaximumSize(QSize(35, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/image/add.png);"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(DataGeshanManage);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(35, 35));
        pushButton_5->setMaximumSize(QSize(35, 35));
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/image/edit.png);"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(DataGeshanManage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(35, 35));
        pushButton_3->setMaximumSize(QSize(35, 35));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/image/delete.png);"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(DataGeshanManage);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(35, 35));
        pushButton_4->setMaximumSize(QSize(35, 35));
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/image/ok.png);"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(DataGeshanManage);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(35, 35));
        pushButton_6->setMaximumSize(QSize(35, 35));
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image: url(:/image/download.svg);"));

        horizontalLayout->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(DataGeshanManage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(DataGeshanManage);

        QMetaObject::connectSlotsByName(DataGeshanManage);
    } // setupUi

    void retranslateUi(QWidget *DataGeshanManage)
    {
        DataGeshanManage->setWindowTitle(QApplication::translate("DataGeshanManage", "Form", nullptr));
        pushButton->setText(QString());
        label->setText(QString());
        pushButton_2->setText(QString());
        pushButton_5->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataGeshanManage: public Ui_DataGeshanManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAGESHANMANAGE_H
