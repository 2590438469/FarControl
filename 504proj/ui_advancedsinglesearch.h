/********************************************************************************
** Form generated from reading UI file 'advancedsinglesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEDSINGLESEARCH_H
#define UI_ADVANCEDSINGLESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvancedSingleSearch
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QComboBox *comboBox_3;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *AdvancedSingleSearch)
    {
        if (AdvancedSingleSearch->objectName().isEmpty())
            AdvancedSingleSearch->setObjectName(QString::fromUtf8("AdvancedSingleSearch"));
        AdvancedSingleSearch->resize(515, 69);
        horizontalLayout = new QHBoxLayout(AdvancedSingleSearch);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AdvancedSingleSearch);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(AdvancedSingleSearch);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_2 = new QLabel(AdvancedSingleSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(AdvancedSingleSearch);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        label_3 = new QLabel(AdvancedSingleSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit = new QLineEdit(AdvancedSingleSearch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        comboBox_3 = new QComboBox(AdvancedSingleSearch);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        horizontalLayout->addWidget(comboBox_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(AdvancedSingleSearch);

        QMetaObject::connectSlotsByName(AdvancedSingleSearch);
    } // setupUi

    void retranslateUi(QWidget *AdvancedSingleSearch)
    {
        AdvancedSingleSearch->setWindowTitle(QApplication::translate("AdvancedSingleSearch", "Form", nullptr));
        label->setText(QApplication::translate("AdvancedSingleSearch", "\345\255\227\346\256\265\357\274\232", nullptr));
        label_2->setText(QApplication::translate("AdvancedSingleSearch", "\347\255\233\351\200\211\346\235\241\344\273\266\357\274\232", nullptr));
        label_3->setText(QApplication::translate("AdvancedSingleSearch", "\345\200\274\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdvancedSingleSearch: public Ui_AdvancedSingleSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCEDSINGLESEARCH_H
