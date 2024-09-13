/********************************************************************************
** Form generated from reading UI file 'advancesinglesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCESINGLESEARCH_H
#define UI_ADVANCESINGLESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvanceSingleSearch
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;

    void setupUi(QWidget *AdvanceSingleSearch)
    {
        if (AdvanceSingleSearch->objectName().isEmpty())
            AdvanceSingleSearch->setObjectName(QString::fromUtf8("AdvanceSingleSearch"));
        AdvanceSingleSearch->resize(652, 300);
        horizontalLayout = new QHBoxLayout(AdvanceSingleSearch);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(AdvanceSingleSearch);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(AdvanceSingleSearch);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(AdvanceSingleSearch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 0));
        lineEdit->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(AdvanceSingleSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(AdvanceSingleSearch);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(150, 0));
        lineEdit_2->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(AdvanceSingleSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        lineEdit_3 = new QLineEdit(AdvanceSingleSearch);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(150, 0));
        lineEdit_3->setMaximumSize(QSize(150, 16777215));
        lineEdit_3->setSizeIncrement(QSize(150, 0));

        horizontalLayout->addWidget(lineEdit_3);


        retranslateUi(AdvanceSingleSearch);

        QMetaObject::connectSlotsByName(AdvanceSingleSearch);
    } // setupUi

    void retranslateUi(QWidget *AdvanceSingleSearch)
    {
        AdvanceSingleSearch->setWindowTitle(QApplication::translate("AdvanceSingleSearch", "Form", nullptr));
        label->setText(QApplication::translate("AdvanceSingleSearch", "\345\256\232\345\200\274\346\243\200\347\264\242\357\274\232", nullptr));
        label_2->setText(QApplication::translate("AdvanceSingleSearch", "\345\214\272\351\227\264\351\231\220\345\210\266\357\274\232", nullptr));
        label_3->setText(QApplication::translate("AdvanceSingleSearch", "--", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdvanceSingleSearch: public Ui_AdvanceSingleSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCESINGLESEARCH_H
