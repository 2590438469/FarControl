/********************************************************************************
** Form generated from reading UI file 'dataadvancesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAADVANCESEARCH_H
#define UI_DATAADVANCESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataAdvanceSearch
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_2;
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

    void setupUi(QWidget *DataAdvanceSearch)
    {
        if (DataAdvanceSearch->objectName().isEmpty())
            DataAdvanceSearch->setObjectName(QString::fromUtf8("DataAdvanceSearch"));
        DataAdvanceSearch->resize(400, 423);
        verticalLayout = new QVBoxLayout(DataAdvanceSearch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DataAdvanceSearch);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(DataAdvanceSearch);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(DataAdvanceSearch);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DataAdvanceSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(DataAdvanceSearch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        checkBox_2 = new QCheckBox(DataAdvanceSearch);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(DataAdvanceSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dateEdit = new QDateEdit(DataAdvanceSearch);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        horizontalLayout_3->addWidget(dateEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        checkBox_3 = new QCheckBox(DataAdvanceSearch);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_3->addWidget(checkBox_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(DataAdvanceSearch);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        dateEdit_2 = new QDateEdit(DataAdvanceSearch);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));

        horizontalLayout_4->addWidget(dateEdit_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        checkBox_4 = new QCheckBox(DataAdvanceSearch);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_4->addWidget(checkBox_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(DataAdvanceSearch);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(DataAdvanceSearch);

        QMetaObject::connectSlotsByName(DataAdvanceSearch);
    } // setupUi

    void retranslateUi(QWidget *DataAdvanceSearch)
    {
        DataAdvanceSearch->setWindowTitle(QApplication::translate("DataAdvanceSearch", "Form", nullptr));
        label->setText(QApplication::translate("DataAdvanceSearch", "\346\255\246\345\231\250\345\236\213\345\217\267-\347\212\266\346\200\201:", nullptr));
        checkBox->setText(QApplication::translate("DataAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_2->setText(QApplication::translate("DataAdvanceSearch", "\347\261\273\345\236\213\357\274\232", nullptr));
        checkBox_2->setText(QApplication::translate("DataAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_3->setText(QApplication::translate("DataAdvanceSearch", "\350\265\267\345\247\213\346\227\266\351\227\264:", nullptr));
        checkBox_3->setText(QApplication::translate("DataAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        label_4->setText(QApplication::translate("DataAdvanceSearch", "\347\273\223\346\235\237\346\227\266\351\227\264:", nullptr));
        checkBox_4->setText(QApplication::translate("DataAdvanceSearch", "\345\220\257\347\224\250", nullptr));
        pushButton->setText(QApplication::translate("DataAdvanceSearch", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataAdvanceSearch: public Ui_DataAdvanceSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAADVANCESEARCH_H
