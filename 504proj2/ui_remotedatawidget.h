/********************************************************************************
** Form generated from reading UI file 'remotedatawidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEDATAWIDGET_H
#define UI_REMOTEDATAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteDataWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *RemoteDataWidget)
    {
        if (RemoteDataWidget->objectName().isEmpty())
            RemoteDataWidget->setObjectName(QString::fromUtf8("RemoteDataWidget"));
        RemoteDataWidget->resize(515, 377);
        verticalLayout_2 = new QVBoxLayout(RemoteDataWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RemoteDataWidget);

        QMetaObject::connectSlotsByName(RemoteDataWidget);
    } // setupUi

    void retranslateUi(QWidget *RemoteDataWidget)
    {
        RemoteDataWidget->setWindowTitle(QApplication::translate("RemoteDataWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteDataWidget: public Ui_RemoteDataWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEDATAWIDGET_H
