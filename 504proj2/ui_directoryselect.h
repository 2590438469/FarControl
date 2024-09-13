/********************************************************************************
** Form generated from reading UI file 'directoryselect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTORYSELECT_H
#define UI_DIRECTORYSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DirectorySelect
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QWidget *DirectorySelect)
    {
        if (DirectorySelect->objectName().isEmpty())
            DirectorySelect->setObjectName(QString::fromUtf8("DirectorySelect"));
        DirectorySelect->resize(667, 522);
        verticalLayout = new QVBoxLayout(DirectorySelect);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DirectorySelect);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(DirectorySelect);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(DirectorySelect);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        line_3 = new QFrame(DirectorySelect);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(DirectorySelect);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        label_4 = new QLabel(DirectorySelect);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_2 = new QPushButton(DirectorySelect);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        line_2 = new QFrame(DirectorySelect);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(DirectorySelect);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_6->addWidget(label_5);

        label_6 = new QLabel(DirectorySelect);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_3 = new QPushButton(DirectorySelect);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);

        line = new QFrame(DirectorySelect);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(DirectorySelect);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        horizontalLayout_7->addWidget(label_7);

        label_8 = new QLabel(DirectorySelect);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_4 = new QPushButton(DirectorySelect);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_8->addWidget(pushButton_4);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(DirectorySelect);

        QMetaObject::connectSlotsByName(DirectorySelect);
    } // setupUi

    void retranslateUi(QWidget *DirectorySelect)
    {
        DirectorySelect->setWindowTitle(QApplication::translate("DirectorySelect", "Form", nullptr));
        label->setText(QApplication::translate("DirectorySelect", "  \345\275\223\345\211\215\346\240\271\347\233\256\345\275\225\357\274\232", nullptr));
        label_2->setText(QApplication::translate("DirectorySelect", "\346\227\240", nullptr));
        pushButton->setText(QApplication::translate("DirectorySelect", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label_3->setText(QApplication::translate("DirectorySelect", "  \345\275\223\345\211\215\346\240\274\346\240\205\347\233\256\345\275\225\357\274\232", nullptr));
        label_4->setText(QApplication::translate("DirectorySelect", "\346\227\240", nullptr));
        pushButton_2->setText(QApplication::translate("DirectorySelect", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label_5->setText(QApplication::translate("DirectorySelect", "  \345\275\223\345\211\215\351\201\245\346\265\213\346\226\207\344\273\266\347\233\256\345\275\225\357\274\232", nullptr));
        label_6->setText(QApplication::translate("DirectorySelect", "\346\227\240", nullptr));
        pushButton_3->setText(QApplication::translate("DirectorySelect", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label_7->setText(QApplication::translate("DirectorySelect", "  \350\207\252\345\256\232\344\271\211\346\225\260\346\215\256\345\244\204\347\220\206\350\275\257\344\273\266\347\233\256\345\275\225\357\274\232", nullptr));
        label_8->setText(QApplication::translate("DirectorySelect", "\346\227\240", nullptr));
        pushButton_4->setText(QApplication::translate("DirectorySelect", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DirectorySelect: public Ui_DirectorySelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTORYSELECT_H
