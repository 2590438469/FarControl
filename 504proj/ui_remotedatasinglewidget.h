/********************************************************************************
** Form generated from reading UI file 'remotedatasinglewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEDATASINGLEWIDGET_H
#define UI_REMOTEDATASINGLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteDataSingleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QProgressBar *progressBar;
    QFrame *line;

    void setupUi(QWidget *RemoteDataSingleWidget)
    {
        if (RemoteDataSingleWidget->objectName().isEmpty())
            RemoteDataSingleWidget->setObjectName(QString::fromUtf8("RemoteDataSingleWidget"));
        RemoteDataSingleWidget->resize(562, 96);
        verticalLayout = new QVBoxLayout(RemoteDataSingleWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(RemoteDataSingleWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(RemoteDataSingleWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_3 = new QLabel(RemoteDataSingleWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(RemoteDataSingleWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        label_5 = new QLabel(RemoteDataSingleWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        label_6 = new QLabel(RemoteDataSingleWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        label_7 = new QLabel(RemoteDataSingleWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        label_8 = new QLabel(RemoteDataSingleWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        label_9 = new QLabel(RemoteDataSingleWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(RemoteDataSingleWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        line = new QFrame(RemoteDataSingleWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(RemoteDataSingleWidget);

        QMetaObject::connectSlotsByName(RemoteDataSingleWidget);
    } // setupUi

    void retranslateUi(QWidget *RemoteDataSingleWidget)
    {
        RemoteDataSingleWidget->setWindowTitle(QApplication::translate("RemoteDataSingleWidget", "Form", nullptr));
        label_2->setText(QApplication::translate("RemoteDataSingleWidget", "\351\201\245\346\265\213\346\225\260\346\215\256\344\274\240\350\276\223", nullptr));
        label->setText(QApplication::translate("RemoteDataSingleWidget", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_3->setText(QApplication::translate("RemoteDataSingleWidget", "\346\227\240", nullptr));
        label_4->setText(QApplication::translate("RemoteDataSingleWidget", "\346\255\246\345\231\250\345\236\213\345\217\267\357\274\232", nullptr));
        label_5->setText(QApplication::translate("RemoteDataSingleWidget", "\346\227\240", nullptr));
        label_6->setText(QApplication::translate("RemoteDataSingleWidget", "\346\255\246\345\231\250\347\212\266\346\200\201\357\274\232", nullptr));
        label_7->setText(QApplication::translate("RemoteDataSingleWidget", "\346\227\240", nullptr));
        label_8->setText(QApplication::translate("RemoteDataSingleWidget", "\344\273\273\345\212\241\344\273\243\345\217\267\357\274\232", nullptr));
        label_9->setText(QApplication::translate("RemoteDataSingleWidget", "\346\227\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteDataSingleWidget: public Ui_RemoteDataSingleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEDATASINGLEWIDGET_H
