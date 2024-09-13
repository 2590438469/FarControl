/********************************************************************************
** Form generated from reading UI file 'fileadd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEADD_H
#define UI_FILEADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileadd
{
public:
    QWidget *widget;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;

    void setupUi(QWidget *fileadd)
    {
        if (fileadd->objectName().isEmpty())
            fileadd->setObjectName(QString::fromUtf8("fileadd"));
        fileadd->resize(447, 505);
        widget = new QWidget(fileadd);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 447, 505));
        widget->setStyleSheet(QString::fromUtf8("#widget{background-color: rgb(138,197,255);}\n"
"#widget{border-top: 5px solid QLinearGradient(y0:0, y1:1,stop: 0 #DADADA, stop: 1 transparent);\n"
"border-left: 5px solid QLinearGradient(x0:0, x1:1,stop: 0 #DADADA, stop: 1 transparent);\n"
"border-bottom: 5px solid QLinearGradient(y0:0, y1:1,stop: 0 transparent, stop: 1  #DADADA);\n"
"border-right: 5px solid QLinearGradient(x0:0, x1:1,stop:  0 transparent, stop: 1 #DADADA);border-radius:20px}\n"
"QPushButton{background-color: rgb(0, 105, 173);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 330, 151, 61));
        QFont font;
        font.setPointSize(19);
        pushButton_2->setFont(font);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 110, 121, 71));
        label_4->setFont(font);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 240, 111, 51));
        label_5->setFont(font);
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 70, 141, 41));
        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(180, 250, 141, 41));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 190, 101, 41));
        label_3->setFont(font);
        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(180, 190, 141, 41));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 60, 131, 61));
        label_2->setFont(font);
        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(180, 130, 141, 41));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 330, 151, 61));
        pushButton->setFont(font);
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(329, 20, 111, 51));
        QFont font1;
        font1.setPointSize(13);
        font1.setUnderline(true);
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(114,161,211);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:0px groove gray;border-radius:20px;padding:2px 4px;}"));

        retranslateUi(fileadd);

        QMetaObject::connectSlotsByName(fileadd);
    } // setupUi

    void retranslateUi(QWidget *fileadd)
    {
        fileadd->setWindowTitle(QApplication::translate("fileadd", "Form", nullptr));
        pushButton_2->setText(QApplication::translate("fileadd", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label_4->setText(QApplication::translate("fileadd", "\347\261\273\345\236\213", nullptr));
        label_5->setText(QApplication::translate("fileadd", "\347\211\210\346\234\254", nullptr));
        label_3->setText(QApplication::translate("fileadd", "\345\236\213\345\217\267", nullptr));
        label_2->setText(QApplication::translate("fileadd", "\345\215\225\344\275\215", nullptr));
        pushButton->setText(QApplication::translate("fileadd", "\347\241\256\350\256\244", nullptr));
        pushButton_3->setText(QApplication::translate("fileadd", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fileadd: public Ui_fileadd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEADD_H
