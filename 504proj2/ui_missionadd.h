/********************************************************************************
** Form generated from reading UI file 'missionadd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONADD_H
#define UI_MISSIONADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionAdd
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QLineEdit *lineEdit;
    QTimeEdit *timeEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLabel *label_5;
    QLabel *label_6;
    QTimeEdit *timeEdit_2;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label;
    QDateEdit *dateEdit;
    QLabel *label_3;

    void setupUi(QMainWindow *MissionAdd)
    {
        if (MissionAdd->objectName().isEmpty())
            MissionAdd->setObjectName(QString::fromUtf8("MissionAdd"));
        MissionAdd->resize(1000, 300);
        MissionAdd->setMinimumSize(QSize(1000, 300));
        MissionAdd->setMaximumSize(QSize(1000, 300));
        MissionAdd->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MissionAdd);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1001, 301));
        widget->setStyleSheet(QString::fromUtf8("#widget{border-image: url(:/image/blue.jpg)}"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 180, 121, 41));
        timeEdit = new QTimeEdit(widget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(260, 180, 131, 41));
        QFont font;
        font.setPointSize(19);
        timeEdit->setFont(font);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 180, 151, 41));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 180, 111, 41));
        pushButton_3->setFont(font);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(710, 80, 111, 41));
        pushButton->setFont(font);
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(470, 80, 151, 41));
        comboBox->setFont(font);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(470, 130, 151, 41));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(470, 40, 161, 41));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        timeEdit_2 = new QTimeEdit(widget);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));
        timeEdit_2->setGeometry(QRect(260, 80, 131, 41));
        timeEdit_2->setFont(font);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(260, 40, 161, 41));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 130, 151, 41));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 111, 41));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(50, 80, 121, 41));
        dateEdit->setFont(font);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 130, 161, 41));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        MissionAdd->setCentralWidget(centralwidget);

        retranslateUi(MissionAdd);

        QMetaObject::connectSlotsByName(MissionAdd);
    } // setupUi

    void retranslateUi(QMainWindow *MissionAdd)
    {
        MissionAdd->setWindowTitle(QApplication::translate("MissionAdd", "MainWindow", nullptr));
        pushButton_2->setText(QApplication::translate("MissionAdd", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_3->setText(QApplication::translate("MissionAdd", "\347\273\223\346\235\237", nullptr));
        pushButton->setText(QApplication::translate("MissionAdd", "\346\267\273\345\212\240", nullptr));
        comboBox->setItemText(0, QApplication::translate("MissionAdd", "node1", nullptr));
        comboBox->setItemText(1, QApplication::translate("MissionAdd", "node2", nullptr));
        comboBox->setItemText(2, QApplication::translate("MissionAdd", "node3", nullptr));
        comboBox->setItemText(3, QApplication::translate("MissionAdd", "node4", nullptr));
        comboBox->setItemText(4, QApplication::translate("MissionAdd", "node5", nullptr));

        label_5->setText(QApplication::translate("MissionAdd", "\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        label_6->setText(QApplication::translate("MissionAdd", "\344\273\273\345\212\241\350\212\202\347\202\271", nullptr));
        label_4->setText(QApplication::translate("MissionAdd", "\350\265\267\345\247\213\346\227\266\351\227\264", nullptr));
        label_2->setText(QApplication::translate("MissionAdd", "\347\273\210\346\255\242\346\227\266\351\227\264", nullptr));
        label->setText(QApplication::translate("MissionAdd", "\346\227\245\346\234\237", nullptr));
        label_3->setText(QApplication::translate("MissionAdd", "\344\273\273\345\212\241\344\273\243\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MissionAdd: public Ui_MissionAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONADD_H
