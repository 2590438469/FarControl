/********************************************************************************
** Form generated from reading UI file 'modulemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULEMANAGERDIALOG_H
#define UI_MODULEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ModuleManagerDialog
{
public:
    QListWidget *listWidgetModules;
    QPushButton *pushButtonClose;
    QPlainTextEdit *plainTextEditModuleInfo;

    void setupUi(QDialog *ModuleManagerDialog)
    {
        if (ModuleManagerDialog->objectName().isEmpty())
            ModuleManagerDialog->setObjectName(QString::fromUtf8("ModuleManagerDialog"));
        ModuleManagerDialog->resize(589, 417);
        listWidgetModules = new QListWidget(ModuleManagerDialog);
        listWidgetModules->setObjectName(QString::fromUtf8("listWidgetModules"));
        listWidgetModules->setGeometry(QRect(20, 30, 256, 331));
        pushButtonClose = new QPushButton(ModuleManagerDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(500, 380, 75, 23));
        plainTextEditModuleInfo = new QPlainTextEdit(ModuleManagerDialog);
        plainTextEditModuleInfo->setObjectName(QString::fromUtf8("plainTextEditModuleInfo"));
        plainTextEditModuleInfo->setGeometry(QRect(280, 30, 291, 331));
        plainTextEditModuleInfo->setReadOnly(true);

        retranslateUi(ModuleManagerDialog);

        QMetaObject::connectSlotsByName(ModuleManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *ModuleManagerDialog)
    {
        ModuleManagerDialog->setWindowTitle(QApplication::translate("ModuleManagerDialog", "\345\212\240\350\275\275\347\232\204\346\250\241\345\235\227", nullptr));
        pushButtonClose->setText(QApplication::translate("ModuleManagerDialog", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModuleManagerDialog: public Ui_ModuleManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULEMANAGERDIALOG_H
