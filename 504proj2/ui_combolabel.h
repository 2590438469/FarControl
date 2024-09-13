/********************************************************************************
** Form generated from reading UI file 'combolabel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBOLABEL_H
#define UI_COMBOLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComboLabel
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *ComboLabel)
    {
        if (ComboLabel->objectName().isEmpty())
            ComboLabel->setObjectName(QString::fromUtf8("ComboLabel"));
        ComboLabel->resize(552, 52);
        horizontalLayout = new QHBoxLayout(ComboLabel);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(ComboLabel);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(ComboLabel);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_2 = new QComboBox(ComboLabel);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        checkBox = new QCheckBox(ComboLabel);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setMinimumSize(QSize(20, 0));
        checkBox->setMaximumSize(QSize(20, 16777215));

        horizontalLayout->addWidget(checkBox);


        retranslateUi(ComboLabel);

        QMetaObject::connectSlotsByName(ComboLabel);
    } // setupUi

    void retranslateUi(QWidget *ComboLabel)
    {
        ComboLabel->setWindowTitle(QApplication::translate("ComboLabel", "Form", nullptr));
        label->setText(QApplication::translate("ComboLabel", "ip", nullptr));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ComboLabel: public Ui_ComboLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBOLABEL_H
