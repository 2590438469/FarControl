/********************************************************************************
** Form generated from reading UI file 'udpendpointdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPENDPOINTDIALOG_H
#define UI_UDPENDPOINTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_UdpEndpointDialog
{
public:
    QComboBox *comboBoxRecvInterface;
    QLabel *label_8;
    QPushButton *pushButtonAddDataSource;
    QPushButton *pushButtonCanceled;
    QTableWidget *tableWidgetDataSources;
    QPushButton *pushButtonSaveDataSources;

    void setupUi(QDialog *UdpEndpointDialog)
    {
        if (UdpEndpointDialog->objectName().isEmpty())
            UdpEndpointDialog->setObjectName(QString::fromUtf8("UdpEndpointDialog"));
        UdpEndpointDialog->resize(655, 426);
        comboBoxRecvInterface = new QComboBox(UdpEndpointDialog);
        comboBoxRecvInterface->setObjectName(QString::fromUtf8("comboBoxRecvInterface"));
        comboBoxRecvInterface->setGeometry(QRect(90, 10, 241, 31));
        label_8 = new QLabel(UdpEndpointDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 20, 54, 12));
        pushButtonAddDataSource = new QPushButton(UdpEndpointDialog);
        pushButtonAddDataSource->setObjectName(QString::fromUtf8("pushButtonAddDataSource"));
        pushButtonAddDataSource->setGeometry(QRect(320, 370, 75, 23));
        pushButtonCanceled = new QPushButton(UdpEndpointDialog);
        pushButtonCanceled->setObjectName(QString::fromUtf8("pushButtonCanceled"));
        pushButtonCanceled->setGeometry(QRect(480, 370, 75, 23));
        tableWidgetDataSources = new QTableWidget(UdpEndpointDialog);
        tableWidgetDataSources->setObjectName(QString::fromUtf8("tableWidgetDataSources"));
        tableWidgetDataSources->setGeometry(QRect(20, 60, 541, 291));
        pushButtonSaveDataSources = new QPushButton(UdpEndpointDialog);
        pushButtonSaveDataSources->setObjectName(QString::fromUtf8("pushButtonSaveDataSources"));
        pushButtonSaveDataSources->setGeometry(QRect(400, 370, 75, 23));

        retranslateUi(UdpEndpointDialog);

        QMetaObject::connectSlotsByName(UdpEndpointDialog);
    } // setupUi

    void retranslateUi(QDialog *UdpEndpointDialog)
    {
        UdpEndpointDialog->setWindowTitle(QApplication::translate("UdpEndpointDialog", "\347\275\221\347\273\234\351\205\215\347\275\256", nullptr));
        label_8->setText(QApplication::translate("UdpEndpointDialog", "\346\216\245\346\224\266\347\275\221\345\215\241", nullptr));
        pushButtonAddDataSource->setText(QApplication::translate("UdpEndpointDialog", "\345\242\236\345\212\240\346\225\260\346\215\256\346\272\220", nullptr));
        pushButtonCanceled->setText(QApplication::translate("UdpEndpointDialog", "\345\205\263\351\227\255", nullptr));
        pushButtonSaveDataSources->setText(QApplication::translate("UdpEndpointDialog", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UdpEndpointDialog: public Ui_UdpEndpointDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPENDPOINTDIALOG_H
