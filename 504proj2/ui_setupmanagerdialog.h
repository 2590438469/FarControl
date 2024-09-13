/********************************************************************************
** Form generated from reading UI file 'setupmanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPMANAGERDIALOG_H
#define UI_SETUPMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetupManagerDialog
{
public:
    QListWidget *listWidgetSetups;
    QLabel *labelSetupInfo;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SetupManagerDialog)
    {
        if (SetupManagerDialog->objectName().isEmpty())
            SetupManagerDialog->setObjectName(QString::fromUtf8("SetupManagerDialog"));
        SetupManagerDialog->resize(556, 387);
        listWidgetSetups = new QListWidget(SetupManagerDialog);
        listWidgetSetups->setObjectName(QString::fromUtf8("listWidgetSetups"));
        listWidgetSetups->setGeometry(QRect(10, 20, 251, 311));
        labelSetupInfo = new QLabel(SetupManagerDialog);
        labelSetupInfo->setObjectName(QString::fromUtf8("labelSetupInfo"));
        labelSetupInfo->setGeometry(QRect(280, 20, 241, 311));
        labelSetupInfo->setFrameShape(QFrame::Box);
        labelSetupInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        pushButtonClose = new QPushButton(SetupManagerDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(450, 350, 75, 23));

        retranslateUi(SetupManagerDialog);

        QMetaObject::connectSlotsByName(SetupManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *SetupManagerDialog)
    {
        SetupManagerDialog->setWindowTitle(QApplication::translate("SetupManagerDialog", "\346\265\217\350\247\210Setups", nullptr));
        labelSetupInfo->setText(QString());
        pushButtonClose->setText(QApplication::translate("SetupManagerDialog", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetupManagerDialog: public Ui_SetupManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPMANAGERDIALOG_H
