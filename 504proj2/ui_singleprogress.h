/********************************************************************************
** Form generated from reading UI file 'singleprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEPROGRESS_H
#define UI_SINGLEPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleProgress
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QProgressBar *progressBar;

    void setupUi(QWidget *SingleProgress)
    {
        if (SingleProgress->objectName().isEmpty())
            SingleProgress->setObjectName(QString::fromUtf8("SingleProgress"));
        SingleProgress->resize(400, 94);
        verticalLayout = new QVBoxLayout(SingleProgress);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SingleProgress);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(SingleProgress);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(SingleProgress);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(SingleProgress);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_5 = new QLabel(SingleProgress);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout->addWidget(label_5);

        label_6 = new QLabel(SingleProgress);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(SingleProgress);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        progressBar = new QProgressBar(SingleProgress);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout_2->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SingleProgress);

        QMetaObject::connectSlotsByName(SingleProgress);
    } // setupUi

    void retranslateUi(QWidget *SingleProgress)
    {
        SingleProgress->setWindowTitle(QApplication::translate("SingleProgress", "Form", nullptr));
        label->setText(QApplication::translate("SingleProgress", "\345\237\272\347\253\231\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("SingleProgress", "\346\227\240", nullptr));
        label_3->setText(QApplication::translate("SingleProgress", "\344\273\273\345\212\241\344\273\243\345\217\267\357\274\232", nullptr));
        label_4->setText(QApplication::translate("SingleProgress", "\346\227\240", nullptr));
        label_5->setText(QApplication::translate("SingleProgress", "\346\226\207\344\273\266\345\220\215", nullptr));
        label_6->setText(QApplication::translate("SingleProgress", "\346\227\240", nullptr));
        label_7->setText(QApplication::translate("SingleProgress", "\350\277\233\345\272\246\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleProgress: public Ui_SingleProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEPROGRESS_H
