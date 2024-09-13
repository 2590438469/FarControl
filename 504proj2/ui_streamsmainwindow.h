/********************************************************************************
** Form generated from reading UI file 'streamsmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMSMAINWINDOW_H
#define UI_STREAMSMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StreamsMainWindow
{
public:
    QAction *actionOpenDataSourceConfigDialog;
    QAction *actionViewSetups;
    QAction *actionParseDatFile;
    QAction *actionViewModules;
    QAction *actionAddDataFlow;
    QAction *actionOpenFrameSenderConfigDialog;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBoxStreams;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAddStream;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuSetup;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StreamsMainWindow)
    {
        if (StreamsMainWindow->objectName().isEmpty())
            StreamsMainWindow->setObjectName(QString::fromUtf8("StreamsMainWindow"));
        StreamsMainWindow->resize(1040, 600);
        actionOpenDataSourceConfigDialog = new QAction(StreamsMainWindow);
        actionOpenDataSourceConfigDialog->setObjectName(QString::fromUtf8("actionOpenDataSourceConfigDialog"));
        actionViewSetups = new QAction(StreamsMainWindow);
        actionViewSetups->setObjectName(QString::fromUtf8("actionViewSetups"));
        actionParseDatFile = new QAction(StreamsMainWindow);
        actionParseDatFile->setObjectName(QString::fromUtf8("actionParseDatFile"));
        actionViewModules = new QAction(StreamsMainWindow);
        actionViewModules->setObjectName(QString::fromUtf8("actionViewModules"));
        actionAddDataFlow = new QAction(StreamsMainWindow);
        actionAddDataFlow->setObjectName(QString::fromUtf8("actionAddDataFlow"));
        actionOpenFrameSenderConfigDialog = new QAction(StreamsMainWindow);
        actionOpenFrameSenderConfigDialog->setObjectName(QString::fromUtf8("actionOpenFrameSenderConfigDialog"));
        centralwidget = new QWidget(StreamsMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1026, 521));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBoxStreams = new QGroupBox(scrollAreaWidgetContents);
        groupBoxStreams->setObjectName(QString::fromUtf8("groupBoxStreams"));

        horizontalLayout_2->addWidget(groupBoxStreams);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        pushButtonAddStream = new QPushButton(centralwidget);
        pushButtonAddStream->setObjectName(QString::fromUtf8("pushButtonAddStream"));

        horizontalLayout->addWidget(pushButtonAddStream);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        StreamsMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StreamsMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1040, 17));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuSetup = new QMenu(menubar);
        menuSetup->setObjectName(QString::fromUtf8("menuSetup"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        StreamsMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(StreamsMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StreamsMainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menuSetup->menuAction());
        menu->addAction(actionAddDataFlow);
        menu->addAction(actionOpenDataSourceConfigDialog);
        menu->addAction(actionOpenFrameSenderConfigDialog);
        menuSetup->addAction(actionViewSetups);
        menuSetup->addAction(actionParseDatFile);
        menu_3->addAction(actionViewModules);

        retranslateUi(StreamsMainWindow);

        QMetaObject::connectSlotsByName(StreamsMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StreamsMainWindow)
    {
        StreamsMainWindow->setWindowTitle(QApplication::translate("StreamsMainWindow", "\347\273\274\345\220\210\346\225\260\346\215\256\345\244\204\347\220\206\350\275\257\344\273\266", nullptr));
        actionOpenDataSourceConfigDialog->setText(QApplication::translate("StreamsMainWindow", "\351\205\215\347\275\256\346\225\260\346\215\256\346\272\220...", nullptr));
        actionViewSetups->setText(QApplication::translate("StreamsMainWindow", "\346\237\245\347\234\213...", nullptr));
        actionParseDatFile->setText(QApplication::translate("StreamsMainWindow", "\344\272\213\345\220\216\345\244\204\347\220\206...", nullptr));
        actionViewModules->setText(QApplication::translate("StreamsMainWindow", "\346\237\245\347\234\213...", nullptr));
        actionAddDataFlow->setText(QApplication::translate("StreamsMainWindow", "\345\242\236\345\212\240\346\265\201", nullptr));
        actionOpenFrameSenderConfigDialog->setText(QApplication::translate("StreamsMainWindow", "\351\205\215\347\275\256\345\256\242\346\210\267\347\253\257...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenFrameSenderConfigDialog->setToolTip(QApplication::translate("StreamsMainWindow", "\351\205\215\347\275\256\345\256\242\346\210\267\347\253\257", nullptr));
#endif // QT_NO_TOOLTIP
        groupBoxStreams->setTitle(QApplication::translate("StreamsMainWindow", "\346\225\260\346\215\256\346\265\201\347\212\266\346\200\201", nullptr));
        pushButtonAddStream->setText(QApplication::translate("StreamsMainWindow", "\345\242\236\345\212\240\346\265\201", nullptr));
        menu->setTitle(QApplication::translate("StreamsMainWindow", "\346\225\260\346\215\256\346\265\201", nullptr));
        menuSetup->setTitle(QApplication::translate("StreamsMainWindow", "Setups", nullptr));
        menu_3->setTitle(QApplication::translate("StreamsMainWindow", "\346\250\241\345\235\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreamsMainWindow: public Ui_StreamsMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMSMAINWINDOW_H
