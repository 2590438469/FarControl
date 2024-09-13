/********************************************************************************
** Form generated from reading UI file 'singlefilewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEFILEWIDGET_H
#define UI_SINGLEFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleFileWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *SingleFileWidget)
    {
        if (SingleFileWidget->objectName().isEmpty())
            SingleFileWidget->setObjectName(QString::fromUtf8("SingleFileWidget"));
        SingleFileWidget->resize(400, 123);
        horizontalLayout = new QHBoxLayout(SingleFileWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SingleFileWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(SingleFileWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(SingleFileWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(SingleFileWidget);

        QMetaObject::connectSlotsByName(SingleFileWidget);
    } // setupUi

    void retranslateUi(QWidget *SingleFileWidget)
    {
        SingleFileWidget->setWindowTitle(QApplication::translate("SingleFileWidget", "Form", nullptr));
        label->setText(QApplication::translate("SingleFileWidget", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("SingleFileWidget", "\346\227\240", nullptr));
        pushButton->setText(QApplication::translate("SingleFileWidget", "\344\270\213\350\275\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleFileWidget: public Ui_SingleFileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEFILEWIDGET_H
