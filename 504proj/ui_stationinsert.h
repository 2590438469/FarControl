/********************************************************************************
** Form generated from reading UI file 'stationinsert.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONINSERT_H
#define UI_STATIONINSERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stationinsert
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;

    void setupUi(QWidget *stationinsert)
    {
        if (stationinsert->objectName().isEmpty())
            stationinsert->setObjectName(QString::fromUtf8("stationinsert"));
        stationinsert->resize(700, 541);
        stationinsert->setMinimumSize(QSize(700, 541));
        stationinsert->setMaximumSize(QSize(700, 541));
        stationinsert->setStyleSheet(QString::fromUtf8("#userinsert{border-image: url(:/image/blue.jpg)}"));
        widget = new QWidget(stationinsert);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 701, 541));
        widget->setStyleSheet(QString::fromUtf8("#widget{background-color: rgb(114,161,211);}\n"
"QPushButton{background-color: rgb(0, 105, 173);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 420, 161, 61));
        QFont font;
        font.setPointSize(19);
        pushButton->setFont(font);
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(100, 60, 491, 291));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 7, -1, 15);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_4);

        label_9 = new QLabel(widget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_9);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(widget1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setFont(font);

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(widget1);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setFont(font);

        verticalLayout_2->addWidget(lineEdit_3);

        lineEdit_7 = new QLineEdit(widget1);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setFont(font);

        verticalLayout_2->addWidget(lineEdit_7);

        lineEdit_8 = new QLineEdit(widget1);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setFont(font);

        verticalLayout_2->addWidget(lineEdit_8);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(stationinsert);

        QMetaObject::connectSlotsByName(stationinsert);
    } // setupUi

    void retranslateUi(QWidget *stationinsert)
    {
        stationinsert->setWindowTitle(QApplication::translate("stationinsert", "\346\267\273\345\212\240\345\237\272\347\253\231\344\277\241\346\201\257", nullptr));
        pushButton->setText(QApplication::translate("stationinsert", "\346\217\222\345\205\245", nullptr));
        label->setText(QApplication::translate("stationinsert", "\345\237\272\347\253\231\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("stationinsert", "ip\357\274\232", nullptr));
        label_3->setText(QApplication::translate("stationinsert", "\345\217\202\346\225\2601\357\274\232", nullptr));
        label_4->setText(QApplication::translate("stationinsert", "\345\217\202\346\225\2602\357\274\232", nullptr));
        label_9->setText(QApplication::translate("stationinsert", "\345\217\202\346\225\2603\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stationinsert: public Ui_stationinsert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONINSERT_H
