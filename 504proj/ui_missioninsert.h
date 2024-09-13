/********************************************************************************
** Form generated from reading UI file 'missioninsert.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONINSERT_H
#define UI_MISSIONINSERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_missioninsert
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QWidget *missioninsert)
    {
        if (missioninsert->objectName().isEmpty())
            missioninsert->setObjectName(QString::fromUtf8("missioninsert"));
        missioninsert->resize(775, 641);
        widget = new QWidget(missioninsert);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 781, 641));
        widget->setStyleSheet(QString::fromUtf8("#widget{background-color: rgb(114,161,211);}\n"
"QPushButton{background-color: rgb(0, 105, 173);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 460, 161, 61));
        QFont font;
        font.setPointSize(19);
        pushButton->setFont(font);
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(330, 150, 371, 41));
        lineEdit_2->setFont(font);
        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(330, 205, 371, 41));
        lineEdit_3->setFont(font);
        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(330, 260, 371, 41));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(0, 28));
        lineEdit_4->setMaximumSize(QSize(16777215, 999));
        lineEdit_4->setFont(font);
        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(330, 310, 371, 41));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMinimumSize(QSize(0, 28));
        lineEdit_5->setMaximumSize(QSize(16777215, 999));
        lineEdit_5->setFont(font);
        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(330, 360, 371, 41));
        lineEdit_6->setMinimumSize(QSize(0, 28));
        lineEdit_6->setMaximumSize(QSize(16777215, 999));
        lineEdit_6->setFont(font);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(330, 97, 371, 41));
        lineEdit->setFont(font);
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(135, 90, 181, 311));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);


        retranslateUi(missioninsert);

        QMetaObject::connectSlotsByName(missioninsert);
    } // setupUi

    void retranslateUi(QWidget *missioninsert)
    {
        missioninsert->setWindowTitle(QApplication::translate("missioninsert", "\344\273\273\345\212\241\345\256\217\346\267\273\345\212\240", nullptr));
        pushButton->setText(QApplication::translate("missioninsert", "\346\217\222\345\205\245", nullptr));
        label->setText(QApplication::translate("missioninsert", "Node:", nullptr));
        label_2->setText(QApplication::translate("missioninsert", "\344\273\273\345\212\241\347\212\266\346\200\201:", nullptr));
        label_3->setText(QApplication::translate("missioninsert", "param2:", nullptr));
        label_4->setText(QApplication::translate("missioninsert", "param3:", nullptr));
        label_5->setText(QApplication::translate("missioninsert", "param4:", nullptr));
        label_6->setText(QApplication::translate("missioninsert", "param5:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class missioninsert: public Ui_missioninsert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONINSERT_H
