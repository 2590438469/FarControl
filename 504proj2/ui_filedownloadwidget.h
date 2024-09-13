/********************************************************************************
** Form generated from reading UI file 'filedownloadwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEDOWNLOADWIDGET_H
#define UI_FILEDOWNLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileDownLoadWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *FileDownLoadWidget)
    {
        if (FileDownLoadWidget->objectName().isEmpty())
            FileDownLoadWidget->setObjectName(QString::fromUtf8("FileDownLoadWidget"));
        FileDownLoadWidget->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(FileDownLoadWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FileDownLoadWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(FileDownLoadWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(FileDownLoadWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(35, 35));
        pushButton->setMaximumSize(QSize(35, 35));
        pushButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/image/upload.svg);"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(FileDownLoadWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 386, 245));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_2->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(FileDownLoadWidget);

        QMetaObject::connectSlotsByName(FileDownLoadWidget);
    } // setupUi

    void retranslateUi(QWidget *FileDownLoadWidget)
    {
        FileDownLoadWidget->setWindowTitle(QApplication::translate("FileDownLoadWidget", "Form", nullptr));
        label->setText(QApplication::translate("FileDownLoadWidget", "\346\225\260\346\215\256\346\240\274\346\240\205\357\274\232", nullptr));
        label_2->setText(QApplication::translate("FileDownLoadWidget", "\346\227\240", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileDownLoadWidget: public Ui_FileDownLoadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEDOWNLOADWIDGET_H
