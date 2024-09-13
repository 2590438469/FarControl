/********************************************************************************
** Form generated from reading UI file 'flowstatuspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWSTATUSPANEL_H
#define UI_FLOWSTATUSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FlowStatusPanel
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelStreamID;
    QLineEdit *lineEditDataFlowNum;
    QLabel *labelStreamTimeStamp;
    QComboBox *comboBoxSetup;
    QLabel *labelStreamConfigName;
    QComboBox *comboBoxDataSource;
    QPushButton *pushButtonStartPause;
    QPushButton *pushButtonRemove;

    void setupUi(QFrame *FlowStatusPanel)
    {
        if (FlowStatusPanel->objectName().isEmpty())
            FlowStatusPanel->setObjectName(QString::fromUtf8("FlowStatusPanel"));
        FlowStatusPanel->resize(1000, 60);
        FlowStatusPanel->setMinimumSize(QSize(0, 60));
        FlowStatusPanel->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(FlowStatusPanel);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelStreamID = new QLabel(FlowStatusPanel);
        labelStreamID->setObjectName(QString::fromUtf8("labelStreamID"));
        labelStreamID->setFrameShape(QFrame::NoFrame);
        labelStreamID->setFrameShadow(QFrame::Plain);
        labelStreamID->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelStreamID);

        lineEditDataFlowNum = new QLineEdit(FlowStatusPanel);
        lineEditDataFlowNum->setObjectName(QString::fromUtf8("lineEditDataFlowNum"));

        horizontalLayout->addWidget(lineEditDataFlowNum);

        labelStreamTimeStamp = new QLabel(FlowStatusPanel);
        labelStreamTimeStamp->setObjectName(QString::fromUtf8("labelStreamTimeStamp"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelStreamTimeStamp->sizePolicy().hasHeightForWidth());
        labelStreamTimeStamp->setSizePolicy(sizePolicy);
        labelStreamTimeStamp->setFrameShape(QFrame::Box);
        labelStreamTimeStamp->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelStreamTimeStamp);

        comboBoxSetup = new QComboBox(FlowStatusPanel);
        comboBoxSetup->setObjectName(QString::fromUtf8("comboBoxSetup"));
        sizePolicy.setHeightForWidth(comboBoxSetup->sizePolicy().hasHeightForWidth());
        comboBoxSetup->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBoxSetup);

        labelStreamConfigName = new QLabel(FlowStatusPanel);
        labelStreamConfigName->setObjectName(QString::fromUtf8("labelStreamConfigName"));
        sizePolicy.setHeightForWidth(labelStreamConfigName->sizePolicy().hasHeightForWidth());
        labelStreamConfigName->setSizePolicy(sizePolicy);
        labelStreamConfigName->setFrameShape(QFrame::Box);
        labelStreamConfigName->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelStreamConfigName);

        comboBoxDataSource = new QComboBox(FlowStatusPanel);
        comboBoxDataSource->setObjectName(QString::fromUtf8("comboBoxDataSource"));
        sizePolicy.setHeightForWidth(comboBoxDataSource->sizePolicy().hasHeightForWidth());
        comboBoxDataSource->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBoxDataSource);

        pushButtonStartPause = new QPushButton(FlowStatusPanel);
        pushButtonStartPause->setObjectName(QString::fromUtf8("pushButtonStartPause"));

        horizontalLayout->addWidget(pushButtonStartPause);

        pushButtonRemove = new QPushButton(FlowStatusPanel);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));

        horizontalLayout->addWidget(pushButtonRemove);


        retranslateUi(FlowStatusPanel);

        QMetaObject::connectSlotsByName(FlowStatusPanel);
    } // setupUi

    void retranslateUi(QFrame *FlowStatusPanel)
    {
        FlowStatusPanel->setWindowTitle(QApplication::translate("FlowStatusPanel", "Frame", nullptr));
        labelStreamID->setText(QApplication::translate("FlowStatusPanel", "\346\265\201\345\217\267", nullptr));
        labelStreamTimeStamp->setText(QApplication::translate("FlowStatusPanel", "00:00:00", nullptr));
        labelStreamConfigName->setText(QApplication::translate("FlowStatusPanel", "\347\254\254\344\272\214\351\230\266\346\256\265\347\254\254\344\270\200\346\211\271", nullptr));
        pushButtonStartPause->setText(QApplication::translate("FlowStatusPanel", "\345\217\221\351\200\201", nullptr));
        pushButtonRemove->setText(QApplication::translate("FlowStatusPanel", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlowStatusPanel: public Ui_FlowStatusPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWSTATUSPANEL_H
