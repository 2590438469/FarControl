/********************************************************************************
** Form generated from reading UI file 'basicinfoedit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICINFOEDIT_H
#define UI_BASICINFOEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicInfoEdit
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_2;
    QDateEdit *dateEdit;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QTimeEdit *timeEdit;
    QTimeEdit *timeEdit_2;
    QComboBox *comboBox_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *BasicInfoEdit)
    {
        if (BasicInfoEdit->objectName().isEmpty())
            BasicInfoEdit->setObjectName(QString::fromUtf8("BasicInfoEdit"));
        BasicInfoEdit->resize(523, 314);
        verticalLayout_4 = new QVBoxLayout(BasicInfoEdit);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(BasicInfoEdit);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(BasicInfoEdit);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(BasicInfoEdit);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(BasicInfoEdit);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 0));
        label_4->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(BasicInfoEdit);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label_5);

        label_7 = new QLabel(BasicInfoEdit);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setMaximumSize(QSize(9999, 16777215));

        verticalLayout->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dateEdit = new QDateEdit(BasicInfoEdit);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        verticalLayout_2->addWidget(dateEdit);

        comboBox = new QComboBox(BasicInfoEdit);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        comboBox_2 = new QComboBox(BasicInfoEdit);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        verticalLayout_2->addWidget(comboBox_2);

        timeEdit = new QTimeEdit(BasicInfoEdit);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));

        verticalLayout_2->addWidget(timeEdit);

        timeEdit_2 = new QTimeEdit(BasicInfoEdit);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));

        verticalLayout_2->addWidget(timeEdit_2);

        comboBox_3 = new QComboBox(BasicInfoEdit);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        verticalLayout_2->addWidget(comboBox_3);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_8 = new QLabel(BasicInfoEdit);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setMinimumSize(QSize(0, 0));
        label_8->setMaximumSize(QSize(9999, 16777215));
        label_8->setSizeIncrement(QSize(50, 0));

        horizontalLayout->addWidget(label_8);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        horizontalLayout->addLayout(gridLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(BasicInfoEdit);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(BasicInfoEdit);

        QMetaObject::connectSlotsByName(BasicInfoEdit);
    } // setupUi

    void retranslateUi(QWidget *BasicInfoEdit)
    {
        BasicInfoEdit->setWindowTitle(QApplication::translate("BasicInfoEdit", "Form", nullptr));
        label->setText(QApplication::translate("BasicInfoEdit", "\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("BasicInfoEdit", "\345\217\202\350\260\213\357\274\232", nullptr));
        label_3->setText(QApplication::translate("BasicInfoEdit", "\350\264\237\350\264\243\344\272\272\357\274\232", nullptr));
        label_4->setText(QApplication::translate("BasicInfoEdit", "\350\277\233\345\234\272\346\227\266\351\227\264\357\274\232", nullptr));
        label_5->setText(QApplication::translate("BasicInfoEdit", "\345\274\200\351\245\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_7->setText(QApplication::translate("BasicInfoEdit", "\350\201\224\347\263\273\347\224\265\350\257\235\357\274\232", nullptr));
        label_8->setText(QApplication::translate("BasicInfoEdit", "\344\272\272\345\221\230\357\274\232", nullptr));
        pushButton->setText(QApplication::translate("BasicInfoEdit", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BasicInfoEdit: public Ui_BasicInfoEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICINFOEDIT_H
