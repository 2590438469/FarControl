/********************************************************************************
** Form generated from reading UI file 'gemanage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEMANAGE_H
#define UI_GEMANAGE_H

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

class Ui_GeManage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_9;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QPushButton *pushButton_12;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QTableWidget *tableWidget;

    void setupUi(QWidget *GeManage)
    {
        if (GeManage->objectName().isEmpty())
            GeManage->setObjectName(QString::fromUtf8("GeManage"));
        GeManage->resize(673, 454);
        verticalLayout = new QVBoxLayout(GeManage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(GeManage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));
        lineEdit->setMaximumSize(QSize(150, 16777215));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(GeManage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/search.png);"));

        horizontalLayout->addWidget(pushButton);

        pushButton_9 = new QPushButton(GeManage);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(100, 40));
        pushButton_9->setMaximumSize(QSize(100, 40));
        pushButton_9->setSizeIncrement(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        pushButton_9->setFont(font);
        pushButton_9->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);border-radius: 5px;padding: 10px;color: black;}QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}\n"
"QPushButton{color: rgb(0, 0, 0);}\n"
"QPushButton{border:2px groove gray;border-radius:12px;padding:2px 4px;}"));

        horizontalLayout->addWidget(pushButton_9);

        label = new QLabel(GeManage);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_8 = new QPushButton(GeManage);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(35, 35));
        pushButton_8->setMaximumSize(QSize(35, 35));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/refresh.png);"));

        horizontalLayout->addWidget(pushButton_8);

        pushButton_2 = new QPushButton(GeManage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(35, 35));
        pushButton_2->setMaximumSize(QSize(35, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/add.png);"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_12 = new QPushButton(GeManage);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setMinimumSize(QSize(35, 35));
        pushButton_12->setMaximumSize(QSize(35, 35));
        pushButton_12->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/back.svg);"));

        horizontalLayout->addWidget(pushButton_12);

        pushButton_5 = new QPushButton(GeManage);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(35, 35));
        pushButton_5->setMaximumSize(QSize(35, 35));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/edit.png);"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(GeManage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(35, 35));
        pushButton_3->setMaximumSize(QSize(35, 35));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/delete.png);"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(GeManage);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(35, 35));
        pushButton_4->setMaximumSize(QSize(35, 35));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/ok.png);"));

        horizontalLayout->addWidget(pushButton_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_6 = new QPushButton(GeManage);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(35, 35));
        pushButton_6->setMaximumSize(QSize(35, 35));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/upload.svg);"));

        horizontalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(GeManage);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(35, 35));
        pushButton_7->setMaximumSize(QSize(35, 35));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/download.svg);"));

        horizontalLayout->addWidget(pushButton_7);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(GeManage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(GeManage);

        QMetaObject::connectSlotsByName(GeManage);
    } // setupUi

    void retranslateUi(QWidget *GeManage)
    {
        GeManage->setWindowTitle(QApplication::translate("GeManage", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_9->setText(QApplication::translate("GeManage", "\351\253\230\347\272\247\346\243\200\347\264\242", nullptr));
        label->setText(QString());
        pushButton_8->setText(QString());
        pushButton_2->setText(QString());
        pushButton_12->setText(QString());
        pushButton_5->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GeManage: public Ui_GeManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEMANAGE_H
