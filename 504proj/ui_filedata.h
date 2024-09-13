/********************************************************************************
** Form generated from reading UI file 'filedata.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEDATA_H
#define UI_FILEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_filedata
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *filedata)
    {
        if (filedata->objectName().isEmpty())
            filedata->setObjectName(QString::fromUtf8("filedata"));
        filedata->resize(606, 347);
        tableWidget = new QTableWidget(filedata);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(30, 30, 531, 291));

        retranslateUi(filedata);

        QMetaObject::connectSlotsByName(filedata);
    } // setupUi

    void retranslateUi(QWidget *filedata)
    {
        filedata->setWindowTitle(QApplication::translate("filedata", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class filedata: public Ui_filedata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEDATA_H
