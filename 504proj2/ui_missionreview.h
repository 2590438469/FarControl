/********************************************************************************
** Form generated from reading UI file 'missionreview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONREVIEW_H
#define UI_MISSIONREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_missionreview
{
public:
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QLineEdit *lineEdit_7;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_yes;
    QPushButton *pushButton_no;

    void setupUi(QWidget *missionreview)
    {
        if (missionreview->objectName().isEmpty())
            missionreview->setObjectName(QString::fromUtf8("missionreview"));
        missionreview->resize(1106, 645);
        missionreview->setStyleSheet(QString::fromUtf8("#missionreview{background-color: rgb(138,197,255);}\n"
"#missionreview{border-top: 5px solid QLinearGradient(y0:0, y1:1,stop: 0 #DADADA, stop: 1 transparent);\n"
"border-left: 5px solid QLinearGradient(x0:0, x1:1,stop: 0 #DADADA, stop: 1 transparent);\n"
"border-bottom: 5px solid QLinearGradient(y0:0, y1:1,stop: 0 transparent, stop: 1  #DADADA);\n"
"border-right: 5px solid QLinearGradient(x0:0, x1:1,stop:  0 transparent, stop: 1 #DADADA);border-radius:20px}\n"
"QPushButton{background-color: rgb(0, 105, 173);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton_2 = new QPushButton(missionreview);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 437, 161, 61));
        QFont font;
        font.setPointSize(19);
        pushButton_2->setFont(font);
        pushButton = new QPushButton(missionreview);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 437, 151, 61));
        pushButton->setFont(font);
        layoutWidget = new QWidget(missionreview);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(180, 70, 671, 301));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 8, -1, 12);
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

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        verticalLayout->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font1);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit_4 = new QLineEdit(layoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_4);

        dateTimeEdit = new QDateTimeEdit(layoutWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setFont(font1);

        verticalLayout_2->addWidget(dateTimeEdit);

        dateTimeEdit_2 = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setFont(font1);

        verticalLayout_2->addWidget(dateTimeEdit_2);

        lineEdit_7 = new QLineEdit(layoutWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_7);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font1);

        verticalLayout_2->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout_2);

        pushButton_3 = new QPushButton(missionreview);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(440, 437, 151, 61));
        pushButton_3->setFont(font);
        pushButton_4 = new QPushButton(missionreview);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(620, 437, 151, 61));
        pushButton_4->setFont(font);
        pushButton_5 = new QPushButton(missionreview);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(810, 437, 151, 61));
        pushButton_5->setFont(font);
        pushButton_yes = new QPushButton(missionreview);
        pushButton_yes->setObjectName(QString::fromUtf8("pushButton_yes"));
        pushButton_yes->setGeometry(QRect(370, 510, 131, 61));
        pushButton_yes->setFont(font);
        pushButton_no = new QPushButton(missionreview);
        pushButton_no->setObjectName(QString::fromUtf8("pushButton_no"));
        pushButton_no->setGeometry(QRect(540, 510, 131, 61));
        pushButton_no->setFont(font);

        retranslateUi(missionreview);

        QMetaObject::connectSlotsByName(missionreview);
    } // setupUi

    void retranslateUi(QWidget *missionreview)
    {
        missionreview->setWindowTitle(QApplication::translate("missionreview", "Form", nullptr));
        pushButton_2->setText(QApplication::translate("missionreview", "\345\205\263\351\227\255", nullptr));
        pushButton->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\347\274\226\350\276\221", nullptr));
        label->setText(QApplication::translate("missionreview", "\345\267\245\347\250\213\345\220\215\347\247\260", nullptr));
        label_2->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\344\273\243\345\217\267", nullptr));
        label_3->setText(QApplication::translate("missionreview", "XX\345\236\213\345\217\267", nullptr));
        label_4->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_5->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_6->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\350\277\233\345\261\225", nullptr));
        label_7->setText(QApplication::translate("missionreview", "\344\273\273\345\212\241\345\256\217\351\200\211\346\213\251", nullptr));
        pushButton_3->setText(QApplication::translate("missionreview", "\346\222\244\345\233\236\344\273\273\345\212\241", nullptr));
        pushButton_4->setText(QApplication::translate("missionreview", "\344\270\255\346\255\242\344\273\273\345\212\241", nullptr));
        pushButton_5->setText(QApplication::translate("missionreview", "\345\217\221\351\200\201\344\273\273\345\212\241", nullptr));
        pushButton_yes->setText(QApplication::translate("missionreview", "\347\241\256\350\256\244", nullptr));
        pushButton_no->setText(QApplication::translate("missionreview", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class missionreview: public Ui_missionreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONREVIEW_H
