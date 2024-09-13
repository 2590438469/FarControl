/********************************************************************************
** Form generated from reading UI file 'loginfo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFO_H
#define UI_LOGINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInfo
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *LogInfo)
    {
        if (LogInfo->objectName().isEmpty())
            LogInfo->setObjectName(QString::fromUtf8("LogInfo"));
        LogInfo->resize(618, 453);
        horizontalLayout = new QHBoxLayout(LogInfo);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(LogInfo);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);


        retranslateUi(LogInfo);

        QMetaObject::connectSlotsByName(LogInfo);
    } // setupUi

    void retranslateUi(QWidget *LogInfo)
    {
        LogInfo->setWindowTitle(QApplication::translate("LogInfo", "\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInfo: public Ui_LogInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFO_H
