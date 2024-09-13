/********************************************************************************
** Form generated from reading UI file 'missionedit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONEDIT_H
#define UI_MISSIONEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_missionedit
{
public:
    QLabel *label_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *missionedit)
    {
        if (missionedit->objectName().isEmpty())
            missionedit->setObjectName(QString::fromUtf8("missionedit"));
        missionedit->resize(1063, 711);
        label_7 = new QLabel(missionedit);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(390, 60, 181, 31));
        QFont font;
        font.setPointSize(18);
        label_7->setFont(font);
        widget = new QWidget(missionedit);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(310, 190, 351, 211));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout_2->addWidget(lineEdit_3);

        dateTimeEdit = new QDateTimeEdit(widget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));

        verticalLayout_2->addWidget(dateTimeEdit);

        dateTimeEdit_2 = new QDateTimeEdit(widget);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));

        verticalLayout_2->addWidget(dateTimeEdit_2);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout_2->addWidget(lineEdit_4);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(missionedit);

        QMetaObject::connectSlotsByName(missionedit);
    } // setupUi

    void retranslateUi(QWidget *missionedit)
    {
        missionedit->setWindowTitle(QApplication::translate("missionedit", "Form", nullptr));
        label_7->setText(QApplication::translate("missionedit", "\344\273\273\345\212\241\347\274\226\350\276\221\347\225\214\351\235\242", nullptr));
        label->setText(QApplication::translate("missionedit", "\345\267\245\347\250\213\345\220\215\347\247\260", nullptr));
        label_2->setText(QApplication::translate("missionedit", "\344\273\273\345\212\241\344\273\243\345\217\267", nullptr));
        label_3->setText(QApplication::translate("missionedit", "XX\345\236\213\345\217\267", nullptr));
        label_4->setText(QApplication::translate("missionedit", "\344\273\273\345\212\241\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_5->setText(QApplication::translate("missionedit", "\344\273\273\345\212\241\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_6->setText(QApplication::translate("missionedit", "\344\273\273\345\212\241\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class missionedit: public Ui_missionedit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONEDIT_H
