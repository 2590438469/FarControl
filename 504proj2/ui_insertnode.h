/********************************************************************************
** Form generated from reading UI file 'insertnode.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTNODE_H
#define UI_INSERTNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_insertnode
{
public:
    QWidget *widget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QWidget *insertnode)
    {
        if (insertnode->objectName().isEmpty())
            insertnode->setObjectName(QString::fromUtf8("insertnode"));
        insertnode->resize(648, 650);
        insertnode->setMinimumSize(QSize(648, 650));
        insertnode->setMaximumSize(QSize(648, 650));
        widget = new QWidget(insertnode);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 651, 651));
        widget->setStyleSheet(QString::fromUtf8("#widget{border-image: url(:/image/blue.jpg)}"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(230, 180, 191, 51));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(230, 300, 191, 51));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 130, 151, 31));
        QFont font;
        font.setPointSize(19);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 230, 151, 71));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 380, 191, 61));
        pushButton->setFont(font);

        retranslateUi(insertnode);

        QMetaObject::connectSlotsByName(insertnode);
    } // setupUi

    void retranslateUi(QWidget *insertnode)
    {
        insertnode->setWindowTitle(QApplication::translate("insertnode", "Form", nullptr));
        label->setText(QApplication::translate("insertnode", "\350\212\202\347\202\271\345\220\215", nullptr));
        label_2->setText(QApplication::translate("insertnode", "\350\212\202\347\202\271IP", nullptr));
        pushButton->setText(QApplication::translate("insertnode", "\346\217\222\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class insertnode: public Ui_insertnode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTNODE_H
