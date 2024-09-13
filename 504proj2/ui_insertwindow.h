/********************************************************************************
** Form generated from reading UI file 'insertwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTWINDOW_H
#define UI_INSERTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_insertWindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_2;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QLineEdit *lineEdit_5;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QWidget *insertWindow)
    {
        if (insertWindow->objectName().isEmpty())
            insertWindow->setObjectName(QString::fromUtf8("insertWindow"));
        insertWindow->resize(1000, 661);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(insertWindow->sizePolicy().hasHeightForWidth());
        insertWindow->setSizePolicy(sizePolicy);
        insertWindow->setStyleSheet(QString::fromUtf8("#insertWindow{background-color: rgb(114,161,211);}\n"
"#widget{border:7px solid rgb(0, 105, 173);}\n"
"QPushButton{background-color: rgb(0, 105, 173);border-radius:20px;}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton = new QPushButton(insertWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(280, 540, 131, 61));
        QFont font;
        font.setPointSize(19);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 105, 173);border-radius:20px;"));
        pushButton_2 = new QPushButton(insertWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(540, 540, 121, 61));
        pushButton_2->setFont(font);
        layoutWidget = new QWidget(insertWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 40, 511, 311));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 6, -1, 9);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(13);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font1);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_14 = new QLineEdit(layoutWidget);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_14);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_2);

        dateTimeEdit = new QDateTimeEdit(layoutWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setFont(font1);

        verticalLayout_2->addWidget(dateTimeEdit);

        dateTimeEdit_2 = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setFont(font1);

        verticalLayout_2->addWidget(dateTimeEdit_2);

        lineEdit_5 = new QLineEdit(layoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_5);


        gridLayout->addLayout(verticalLayout_2, 0, 2, 1, 1);

        groupBox = new QGroupBox(insertWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(250, 410, 491, 91));
        groupBox->setFont(font1);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);


        retranslateUi(insertWindow);

        QMetaObject::connectSlotsByName(insertWindow);
    } // setupUi

    void retranslateUi(QWidget *insertWindow)
    {
        insertWindow->setWindowTitle(QApplication::translate("insertWindow", "\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        pushButton->setText(QApplication::translate("insertWindow", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QApplication::translate("insertWindow", "\345\217\226\346\266\210", nullptr));
        label->setText(QApplication::translate("insertWindow", "\345\267\245\347\250\213\345\220\215\347\247\260", nullptr));
        label_2->setText(QApplication::translate("insertWindow", "\344\273\273\345\212\241\344\273\243\345\217\267", nullptr));
        label_3->setText(QApplication::translate("insertWindow", "XX\345\236\213\345\217\267", nullptr));
        label_4->setText(QApplication::translate("insertWindow", "\344\273\273\345\212\241\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_5->setText(QApplication::translate("insertWindow", "\344\273\273\345\212\241\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_6->setText(QApplication::translate("insertWindow", "\344\273\273\345\212\241\347\212\266\346\200\201", nullptr));
        groupBox->setTitle(QApplication::translate("insertWindow", "\345\217\202\350\257\225\347\253\231", nullptr));
        checkBox->setText(QApplication::translate("insertWindow", "CheckBox", nullptr));
        checkBox_2->setText(QApplication::translate("insertWindow", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class insertWindow: public Ui_insertWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTWINDOW_H
