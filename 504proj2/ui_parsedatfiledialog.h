/********************************************************************************
** Form generated from reading UI file 'parsedatfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSEDATFILEDIALOG_H
#define UI_PARSEDATFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParseDatFileDialog
{
public:
    QComboBox *comboBoxSetups;
    QLabel *label;
    QLineEdit *lineEditDatFilePath;
    QPushButton *pushButtonBrowserDatFilePath;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonClose;
    QProgressBar *progressBar;
    QLabel *label_5;
    QPushButton *pushButtonBrowserResultFilePath;
    QLineEdit *lineEditResultFilePath;
    QLineEdit *lineEditSkipHeadBytes;

    void setupUi(QDialog *ParseDatFileDialog)
    {
        if (ParseDatFileDialog->objectName().isEmpty())
            ParseDatFileDialog->setObjectName(QString::fromUtf8("ParseDatFileDialog"));
        ParseDatFileDialog->resize(602, 270);
        ParseDatFileDialog->setModal(true);
        comboBoxSetups = new QComboBox(ParseDatFileDialog);
        comboBoxSetups->setObjectName(QString::fromUtf8("comboBoxSetups"));
        comboBoxSetups->setGeometry(QRect(110, 10, 151, 22));
        label = new QLabel(ParseDatFileDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 61, 21));
        lineEditDatFilePath = new QLineEdit(ParseDatFileDialog);
        lineEditDatFilePath->setObjectName(QString::fromUtf8("lineEditDatFilePath"));
        lineEditDatFilePath->setGeometry(QRect(110, 50, 371, 21));
        pushButtonBrowserDatFilePath = new QPushButton(ParseDatFileDialog);
        pushButtonBrowserDatFilePath->setObjectName(QString::fromUtf8("pushButtonBrowserDatFilePath"));
        pushButtonBrowserDatFilePath->setGeometry(QRect(500, 50, 75, 23));
        label_2 = new QLabel(ParseDatFileDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 50, 61, 21));
        label_3 = new QLabel(ParseDatFileDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 140, 71, 21));
        label_4 = new QLabel(ParseDatFileDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 140, 71, 21));
        pushButtonStart = new QPushButton(ParseDatFileDialog);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(400, 220, 75, 23));
        pushButtonClose = new QPushButton(ParseDatFileDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(500, 220, 75, 23));
        progressBar = new QProgressBar(ParseDatFileDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 190, 541, 23));
        progressBar->setValue(0);
        label_5 = new QLabel(ParseDatFileDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 100, 61, 21));
        pushButtonBrowserResultFilePath = new QPushButton(ParseDatFileDialog);
        pushButtonBrowserResultFilePath->setObjectName(QString::fromUtf8("pushButtonBrowserResultFilePath"));
        pushButtonBrowserResultFilePath->setGeometry(QRect(500, 100, 75, 23));
        lineEditResultFilePath = new QLineEdit(ParseDatFileDialog);
        lineEditResultFilePath->setObjectName(QString::fromUtf8("lineEditResultFilePath"));
        lineEditResultFilePath->setGeometry(QRect(110, 100, 371, 21));
        lineEditSkipHeadBytes = new QLineEdit(ParseDatFileDialog);
        lineEditSkipHeadBytes->setObjectName(QString::fromUtf8("lineEditSkipHeadBytes"));
        lineEditSkipHeadBytes->setGeometry(QRect(110, 140, 101, 20));

        retranslateUi(ParseDatFileDialog);

        QMetaObject::connectSlotsByName(ParseDatFileDialog);
    } // setupUi

    void retranslateUi(QDialog *ParseDatFileDialog)
    {
        ParseDatFileDialog->setWindowTitle(QApplication::translate("ParseDatFileDialog", "\344\272\213\345\220\216\345\244\204\347\220\206", nullptr));
        label->setText(QApplication::translate("ParseDatFileDialog", "Setup\351\200\211\346\213\251", nullptr));
        lineEditDatFilePath->setText(QApplication::translate("ParseDatFileDialog", "E:/wmf/qtProject/AttixDeocder/build/release/data/SBD/TFFX-FH.dat", nullptr));
        pushButtonBrowserDatFilePath->setText(QApplication::translate("ParseDatFileDialog", "\346\265\217\350\247\210...", nullptr));
        label_2->setText(QApplication::translate("ParseDatFileDialog", "Dat\346\226\207\344\273\266", nullptr));
        label_3->setText(QApplication::translate("ParseDatFileDialog", "\350\267\263\350\277\207\346\226\207\344\273\266\345\274\200\345\244\264", nullptr));
        label_4->setText(QApplication::translate("ParseDatFileDialog", "\345\255\227\350\212\202", nullptr));
        pushButtonStart->setText(QApplication::translate("ParseDatFileDialog", "\345\274\200\345\247\213", nullptr));
        pushButtonClose->setText(QApplication::translate("ParseDatFileDialog", "\345\205\263\351\227\255", nullptr));
        label_5->setText(QApplication::translate("ParseDatFileDialog", "\347\273\223\346\236\234\346\226\207\344\273\266", nullptr));
        pushButtonBrowserResultFilePath->setText(QApplication::translate("ParseDatFileDialog", "\346\265\217\350\247\210...", nullptr));
        lineEditResultFilePath->setText(QApplication::translate("ParseDatFileDialog", "E:/wmf/qtProject/AttixDeocder/build/release/results/Y3Y4", nullptr));
        lineEditSkipHeadBytes->setText(QApplication::translate("ParseDatFileDialog", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParseDatFileDialog: public Ui_ParseDatFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSEDATFILEDIALOG_H
