/********************************************************************************
** Form generated from reading UI file 'changepassword.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPASSWORD_H
#define UI_CHANGEPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangePassword
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *ChangePassword)
    {
        if (ChangePassword->objectName().isEmpty())
            ChangePassword->setObjectName(QString::fromUtf8("ChangePassword"));
        ChangePassword->resize(600, 300);
        ChangePassword->setMinimumSize(QSize(600, 300));
        ChangePassword->setMaximumSize(QSize(600, 300));
        ChangePassword->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(ChangePassword);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 50, 141, 51));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 15, 141, 31));
        QFont font;
        font.setPointSize(19);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 50, 131, 51));
        pushButton->setFont(font);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 601, 301));
        widget->setStyleSheet(QString::fromUtf8("#widget{border-image: url(:/image/blue.jpg)}"));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 190, 141, 51));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 150, 141, 31));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 190, 131, 51));
        pushButton_2->setFont(font);
        ChangePassword->setCentralWidget(centralwidget);
        widget->raise();
        lineEdit->raise();
        label->raise();
        pushButton->raise();

        retranslateUi(ChangePassword);

        QMetaObject::connectSlotsByName(ChangePassword);
    } // setupUi

    void retranslateUi(QMainWindow *ChangePassword)
    {
        ChangePassword->setWindowTitle(QApplication::translate("ChangePassword", "MainWindow", nullptr));
        label->setText(QApplication::translate("ChangePassword", "\346\227\247\345\257\206\347\240\201", nullptr));
        pushButton->setText(QApplication::translate("ChangePassword", "\344\277\256\346\224\271", nullptr));
        label_2->setText(QApplication::translate("ChangePassword", "\346\226\260\345\257\206\347\240\201", nullptr));
        pushButton_2->setText(QApplication::translate("ChangePassword", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangePassword: public Ui_ChangePassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPASSWORD_H
