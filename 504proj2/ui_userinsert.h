/********************************************************************************
** Form generated from reading UI file 'userinsert.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINSERT_H
#define UI_USERINSERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userinsert
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
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QComboBox *comboBox;

    void setupUi(QWidget *userinsert)
    {
        if (userinsert->objectName().isEmpty())
            userinsert->setObjectName(QString::fromUtf8("userinsert"));
        userinsert->resize(700, 551);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userinsert->sizePolicy().hasHeightForWidth());
        userinsert->setSizePolicy(sizePolicy);
        userinsert->setMinimumSize(QSize(700, 551));
        userinsert->setMaximumSize(QSize(700, 551));
        userinsert->setStyleSheet(QString::fromUtf8("#userinsert{border-image: url(:/image/blue.jpg)}"));
        widget = new QWidget(userinsert);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 701, 551));
        widget->setStyleSheet(QString::fromUtf8("#widget{background-color: rgb(114,161,211);}\n"
"QPushButton{background-color: rgb(0, 105, 173);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:20px;padding:2px 4px;}"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 420, 161, 61));
        QFont font;
        font.setPointSize(19);
        pushButton->setFont(font);
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(80, 70, 501, 251));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 10, -1, 17);
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

        comboBox = new QComboBox(widget1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        verticalLayout_2->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(userinsert);

        QMetaObject::connectSlotsByName(userinsert);
    } // setupUi

    void retranslateUi(QWidget *userinsert)
    {
        userinsert->setWindowTitle(QApplication::translate("userinsert", "\347\224\250\346\210\267\344\277\241\346\201\257\346\267\273\345\212\240", nullptr));
        pushButton->setText(QApplication::translate("userinsert", "\346\217\222\345\205\245", nullptr));
        label->setText(QApplication::translate("userinsert", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("userinsert", "\347\234\237\345\256\236\345\247\223\345\220\215\357\274\232", nullptr));
        label_3->setText(QApplication::translate("userinsert", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_4->setText(QApplication::translate("userinsert", "\350\247\222\350\211\262\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("userinsert", "USER", nullptr));
        comboBox->setItemText(1, QApplication::translate("userinsert", "ADMIN", nullptr));

    } // retranslateUi

};

namespace Ui {
    class userinsert: public Ui_userinsert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINSERT_H
