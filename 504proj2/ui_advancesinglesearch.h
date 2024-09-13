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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvanceSingleSearch
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QTimeEdit *timeEdit;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *AdvanceSingleSearch)
    {
        if (AdvanceSingleSearch->objectName().isEmpty())
            AdvanceSingleSearch->setObjectName(QString::fromUtf8("AdvanceSingleSearch"));
        AdvanceSingleSearch->resize(652, 300);
        horizontalLayout = new QHBoxLayout(AdvanceSingleSearch);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AdvanceSingleSearch);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(AdvanceSingleSearch);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_2 = new QLabel(AdvanceSingleSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(AdvanceSingleSearch);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        label_3 = new QLabel(AdvanceSingleSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        timeEdit = new QTimeEdit(AdvanceSingleSearch);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setMinimumSize(QSize(80, 0));
        timeEdit->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(timeEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(AdvanceSingleSearch);

        QMetaObject::connectSlotsByName(AdvanceSingleSearch);
    } // setupUi

    void retranslateUi(QWidget *AdvanceSingleSearch)
    {
        AdvanceSingleSearch->setWindowTitle(QApplication::translate("AdvanceSingleSearch", "Form", nullptr));
        label->setText(QApplication::translate("AdvanceSingleSearch", "\345\255\227\346\256\265\357\274\232", nullptr));
        label_2->setText(QApplication::translate("AdvanceSingleSearch", "\347\255\233\351\200\211\347\261\273\345\236\213\357\274\232", nullptr));
        label_3->setText(QApplication::translate("AdvanceSingleSearch", "\345\200\274\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdvanceSingleSearch: public Ui_AdvanceSingleSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCESINGLESEARCH_H
