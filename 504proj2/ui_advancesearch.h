/********************************************************************************
** Form generated from reading UI file 'advancesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCESEARCH_H
#define UI_ADVANCESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvanceSearch
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QDateEdit *dateEdit_2;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *AdvanceSearch)
    {
        if (AdvanceSearch->objectName().isEmpty())
            AdvanceSearch->setObjectName(QString::fromUtf8("AdvanceSearch"));
        AdvanceSearch->resize(491, 327);
        verticalLayout_2 = new QVBoxLayout(AdvanceSearch);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AdvanceSearch);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(AdvanceSearch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(AdvanceSearch);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(AdvanceSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(AdvanceSearch);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        checkBox_2 = new QCheckBox(AdvanceSearch);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(AdvanceSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        dateEdit = new QDateEdit(AdvanceSearch);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        horizontalLayout_4->addWidget(dateEdit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        checkBox_3 = new QCheckBox(AdvanceSearch);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_4->addWidget(checkBox_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(AdvanceSearch);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        dateEdit_2 = new QDateEdit(AdvanceSearch);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));

        horizontalLayout_5->addWidget(dateEdit_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        checkBox_4 = new QCheckBox(AdvanceSearch);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_5->addWidget(checkBox_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(AdvanceSearch);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(AdvanceSearch);

        QMetaObject::connectSlotsByName(AdvanceSearch);
    } // setupUi

    void retranslateUi(QWidget *AdvanceSearch)
    {
        AdvanceSearch->setWindowTitle(QApplication::translate("AdvanceSearch", "Form", nullptr));
        label->setText(QApplication::translate("AdvanceSearch", "\344\273\273\345\212\241\344\273\243\345\217\267\357\274\232", nullptr));
        checkBox->setText(QApplication::translate("AdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_2->setText(QApplication::translate("AdvanceSearch", "\344\277\235\351\232\234\345\206\205\345\256\271\357\274\232", nullptr));
        checkBox_2->setText(QApplication::translate("AdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_3->setText(QApplication::translate("AdvanceSearch", "\346\227\266\351\227\264\350\265\267\345\247\213\357\274\232", nullptr));
        checkBox_3->setText(QApplication::translate("AdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_4->setText(QApplication::translate("AdvanceSearch", "\346\227\266\351\227\264\347\273\210\346\255\242\357\274\232", nullptr));
        checkBox_4->setText(QApplication::translate("AdvanceSearch", "\345\220\257\347\224\250", nullptr));
        pushButton_2->setText(QApplication::translate("AdvanceSearch", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdvanceSearch: public Ui_AdvanceSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCESEARCH_H
