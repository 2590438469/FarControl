/********************************************************************************
** Form generated from reading UI file 'geshanadvancesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESHANADVANCESEARCH_H
#define UI_GESHANADVANCESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeshanAdvanceSearch
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDateEdit *dateEdit_2;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;

    void setupUi(QWidget *GeshanAdvanceSearch)
    {
        if (GeshanAdvanceSearch->objectName().isEmpty())
            GeshanAdvanceSearch->setObjectName(QString::fromUtf8("GeshanAdvanceSearch"));
        GeshanAdvanceSearch->resize(400, 300);
        verticalLayout = new QVBoxLayout(GeshanAdvanceSearch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(GeshanAdvanceSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dateEdit = new QDateEdit(GeshanAdvanceSearch);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        horizontalLayout_3->addWidget(dateEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        checkBox_3 = new QCheckBox(GeshanAdvanceSearch);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_3->addWidget(checkBox_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(GeshanAdvanceSearch);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        dateEdit_2 = new QDateEdit(GeshanAdvanceSearch);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));

        horizontalLayout_4->addWidget(dateEdit_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        checkBox_4 = new QCheckBox(GeshanAdvanceSearch);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_4->addWidget(checkBox_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(GeshanAdvanceSearch);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(GeshanAdvanceSearch);

        QMetaObject::connectSlotsByName(GeshanAdvanceSearch);
    } // setupUi

    void retranslateUi(QWidget *GeshanAdvanceSearch)
    {
        GeshanAdvanceSearch->setWindowTitle(QApplication::translate("GeshanAdvanceSearch", "Form", nullptr));
        label_3->setText(QApplication::translate("GeshanAdvanceSearch", "\350\265\267\345\247\213\346\227\266\351\227\264:", nullptr));
        checkBox_3->setText(QApplication::translate("GeshanAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_4->setText(QApplication::translate("GeshanAdvanceSearch", "\347\273\223\346\235\237\346\227\266\351\227\264:", nullptr));
        checkBox_4->setText(QApplication::translate("GeshanAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        pushButton->setText(QApplication::translate("GeshanAdvanceSearch", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeshanAdvanceSearch: public Ui_GeshanAdvanceSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESHANADVANCESEARCH_H
