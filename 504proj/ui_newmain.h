/********************************************************************************
** Form generated from reading UI file 'newmain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAIN_H
#define UI_NEWMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newmain
{
public:
    QWidget *widget_8;
    QWidget *widget_6;
    QPushButton *pushButton_8;
    QWidget *widget_5;
    QPushButton *pushButton_7;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QWidget *widget;
    QPushButton *pushButton;
    QWidget *widget_4;
    QPushButton *pushButton_6;
    QWidget *widget_3;
    QPushButton *pushButton_5;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_10;
    QWidget *widget_2;
    QPushButton *pushButton_4;

    void setupUi(QWidget *newmain)
    {
        if (newmain->objectName().isEmpty())
            newmain->setObjectName(QString::fromUtf8("newmain"));
        newmain->resize(2200, 1350);
        newmain->setMinimumSize(QSize(2200, 1350));
        newmain->setMaximumSize(QSize(2200, 1350));
        newmain->setStyleSheet(QString::fromUtf8(""));
        widget_8 = new QWidget(newmain);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(0, 0, 2200, 1350));
        widget_8->setMinimumSize(QSize(2200, 1350));
        widget_8->setMaximumSize(QSize(2200, 1350));
        widget_8->setStyleSheet(QString::fromUtf8("#widget_8{border-image: url(:/image/main.jpg)}"));
        widget_6 = new QWidget(widget_8);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(1620, 460, 481, 231));
        widget_6->setStyleSheet(QString::fromUtf8("#widget_6{border-image: url(:/image/kuangnew.png)}"));
        pushButton_8 = new QPushButton(widget_6);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(70, 40, 321, 141));
        QFont font;
        font.setPointSize(25);
        pushButton_8->setFont(font);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}\n"
";"));
        widget_5 = new QWidget(widget_8);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(1620, 720, 481, 231));
        widget_5->setStyleSheet(QString::fromUtf8("#widget_5{border-image: url(:/image/kuangnew.png)}"));
        pushButton_7 = new QPushButton(widget_5);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(70, 40, 321, 141));
        pushButton_7->setFont(font);
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}\n"
";"));
        gridLayoutWidget = new QWidget(widget_8);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(700, 880, 821, 371));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        label = new QLabel(widget_8);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(500, 30, 1171, 141));
        QFont font2;
        font2.setPointSize(62);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);
        widget = new QWidget(widget_8);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(110, 460, 471, 231));
        widget->setStyleSheet(QString::fromUtf8("#widget{border-image: url(:/image/kuangnew.png)}"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 40, 321, 141));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}"));
        widget_4 = new QWidget(widget_8);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(1620, 1010, 481, 231));
        widget_4->setStyleSheet(QString::fromUtf8("#widget_4{border-image: url(:/image/kuangnew.png)}"));
        pushButton_6 = new QPushButton(widget_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(70, 40, 321, 141));
        pushButton_6->setFont(font);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}\n"
";"));
        widget_3 = new QWidget(widget_8);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(110, 1010, 471, 231));
        widget_3->setStyleSheet(QString::fromUtf8("#widget_3{border-image: url(:/image/kuangnew.png)}"));
        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(70, 40, 321, 141));
        pushButton_5->setFont(font);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}\n"
";"));
        widget_7 = new QWidget(widget_8);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(1620, 50, 481, 391));
        widget_7->setStyleSheet(QString::fromUtf8("#widget_7{border-image: url(:/image/kuangnew.png)}"));
        verticalLayout = new QVBoxLayout(widget_7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 28);
        label_6 = new QLabel(widget_7);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font3;
        font3.setPointSize(20);
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(widget_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font3);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        label_9 = new QLabel(widget_7);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_9);

        label_8 = new QLabel(widget_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font3);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_8);

        label_10 = new QLabel(widget_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font3);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_10->setAlignment(Qt::AlignCenter);
        label_10->setMargin(0);

        verticalLayout->addWidget(label_10);

        widget_2 = new QWidget(widget_8);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(110, 720, 471, 231));
        widget_2->setStyleSheet(QString::fromUtf8("#widget_2{border-image: url(:/image/kuangnew.png)}"));
        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(70, 40, 321, 141));
        pushButton_4->setFont(font);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{border:none;background:transparent;color: rgb(255, 255, 255)}\n"
";"));

        retranslateUi(newmain);

        QMetaObject::connectSlotsByName(newmain);
    } // setupUi

    void retranslateUi(QWidget *newmain)
    {
        newmain->setWindowTitle(QApplication::translate("newmain", "Form", nullptr));
        pushButton_8->setText(QApplication::translate("newmain", "\344\273\273\345\212\241\347\256\200\344\273\213", nullptr));
        pushButton_7->setText(QApplication::translate("newmain", "\350\257\225\351\252\214\344\277\241\346\201\257", nullptr));
        label_5->setText(QApplication::translate("newmain", "\347\273\235\345\257\271\345\277\240\350\257\232", nullptr));
        label_4->setText(QApplication::translate("newmain", "\344\275\234\351\243\216\344\274\230\350\211\257", nullptr));
        label_3->setText(QApplication::translate("newmain", "\345\220\254\345\205\232\346\214\207\346\214\245", nullptr));
        label_2->setText(QApplication::translate("newmain", "\350\203\275\346\211\223\350\203\234\344\273\227", nullptr));
        label->setText(QApplication::translate("newmain", "\350\257\225\351\252\214\346\214\207\346\214\245\346\230\276\347\244\272\347\263\273\347\273\237", nullptr));
        pushButton->setText(QApplication::translate("newmain", "\344\273\273\345\212\241\345\233\236\351\241\276", nullptr));
        pushButton_6->setText(QApplication::translate("newmain", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        pushButton_5->setText(QApplication::translate("newmain", "\344\270\211\347\253\231\346\246\202\345\206\265", nullptr));
        label_6->setText(QApplication::translate("newmain", "\345\214\227\344\272\254\346\227\266\351\227\264:16:04", nullptr));
        label_7->setText(QApplication::translate("newmain", "\347\273\235\345\257\271\346\227\266\351\227\264:16:04", nullptr));
        label_9->setText(QApplication::translate("newmain", "\344\275\234\344\270\232\346\227\266\351\227\264:16:04", nullptr));
        label_8->setText(QApplication::translate("newmain", "\345\275\223\345\211\215\344\275\234\344\270\232:16:04", nullptr));
        label_10->setText(QApplication::translate("newmain", "\344\275\234\344\270\232\351\233\266\347\202\271:16:04", nullptr));
        pushButton_4->setText(QApplication::translate("newmain", "\347\240\224\345\210\266\345\216\206\347\250\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newmain: public Ui_newmain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAIN_H
