/********************************************************************************
** Form generated from reading UI file 'missionallconfigsingle.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONALLCONFIGSINGLE_H
#define UI_MISSIONALLCONFIGSINGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionAllConfigSingle
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QLabel *label_5;
    QComboBox *comboBox_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MissionAllConfigSingle)
    {
        if (MissionAllConfigSingle->objectName().isEmpty())
            MissionAllConfigSingle->setObjectName(QString::fromUtf8("MissionAllConfigSingle"));
        MissionAllConfigSingle->resize(788, 430);
        horizontalLayout = new QHBoxLayout(MissionAllConfigSingle);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(MissionAllConfigSingle);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(MissionAllConfigSingle);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_3 = new QLabel(MissionAllConfigSingle);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox = new QComboBox(MissionAllConfigSingle);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_4 = new QLabel(MissionAllConfigSingle);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        comboBox_2 = new QComboBox(MissionAllConfigSingle);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        label_5 = new QLabel(MissionAllConfigSingle);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        comboBox_3 = new QComboBox(MissionAllConfigSingle);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        horizontalLayout->addWidget(comboBox_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(MissionAllConfigSingle);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/begin.png);"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(MissionAllConfigSingle);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(MissionAllConfigSingle);

        QMetaObject::connectSlotsByName(MissionAllConfigSingle);
    } // setupUi

    void retranslateUi(QWidget *MissionAllConfigSingle)
    {
        MissionAllConfigSingle->setWindowTitle(QApplication::translate("MissionAllConfigSingle", "Form", nullptr));
        label->setText(QApplication::translate("MissionAllConfigSingle", "\345\272\217\345\217\267\357\274\232", nullptr));
        label_3->setText(QApplication::translate("MissionAllConfigSingle", "\347\261\273\345\236\213\357\274\232", nullptr));
        label_4->setText(QApplication::translate("MissionAllConfigSingle", "\351\243\236\346\234\272\345\220\215/\351\243\236\346\234\272\347\274\226\345\217\267\357\274\232", nullptr));
        label_5->setText(QApplication::translate("MissionAllConfigSingle", "\346\225\260\346\215\256\346\272\220", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QApplication::translate("MissionAllConfigSingle", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MissionAllConfigSingle: public Ui_MissionAllConfigSingle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONALLCONFIGSINGLE_H
