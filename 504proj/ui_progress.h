/********************************************************************************
** Form generated from reading UI file 'progress.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESS_H
#define UI_PROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_progress
{
public:
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *progress)
    {
        if (progress->objectName().isEmpty())
            progress->setObjectName(QString::fromUtf8("progress"));
        progress->resize(800, 278);
        progress->setMinimumSize(QSize(800, 200));
        progress->setMaximumSize(QSize(9999, 9999));
        progress->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(progress);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(progress);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 786, 264));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        retranslateUi(progress);

        QMetaObject::connectSlotsByName(progress);
    } // setupUi

    void retranslateUi(QWidget *progress)
    {
        progress->setWindowTitle(QApplication::translate("progress", "\344\274\240\350\276\223\350\277\233\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class progress: public Ui_progress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESS_H
