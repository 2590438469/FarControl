/********************************************************************************
** Form generated from reading UI file 'firstwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTWINDOW_H
#define UI_FIRSTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customtablewidget.h>
#include <datageshanmanage.h>
#include <datamanage.h>
#include <missionsendwidget.h>

QT_BEGIN_NAMESPACE

class Ui_FirstWindow
{
public:
    QAction *actionlogout;
    QAction *actionchangePassword;
    QAction *actionaddMission;
    QAction *actioncheckMission;
    QAction *actionsendMssion;
    QAction *actionuser;
    QAction *actionji;
    QAction *actionhong;
    QAction *actiongeshan;
    QAction *actiondirectory;
    QAction *actiondaochu;
    QAction *actiondaoru;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QWidget *widget_name;
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget;
    QLabel *label_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_11;
    QPushButton *pushButton_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_10;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QPushButton *pushButton_23;
    QPushButton *pushButton_9;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_5;
    MissionSendWidget *missionSendWidget;
    QWidget *page_2;
    QTableWidget *tableWidget_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QWidget *page_3;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget_2;
    QWidget *page_7;
    QTableWidget *tableWidget;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_14;
    QTableWidget *tableWidget_3;
    QWidget *page_5;
    QTableWidget *tableWidget_5;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_20;
    QPushButton *pushButton_19;
    QWidget *page_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    customTableWidget *mission_macro_widget;
    QWidget *page_8;
    QHBoxLayout *horizontalLayout_6;
    DataManage *widget_2;
    QWidget *page_9;
    QHBoxLayout *horizontalLayout_7;
    customTableWidget *widget_3;
    QWidget *page_10;
    QHBoxLayout *horizontalLayout_9;
    DataGeshanManage *widget_5;
    QWidget *page_11;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_15;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuqianyi;

    void setupUi(QMainWindow *FirstWindow)
    {
        if (FirstWindow->objectName().isEmpty())
            FirstWindow->setObjectName(QString::fromUtf8("FirstWindow"));
        FirstWindow->resize(1600, 900);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FirstWindow->sizePolicy().hasHeightForWidth());
        FirstWindow->setSizePolicy(sizePolicy);
        FirstWindow->setMinimumSize(QSize(0, 0));
        FirstWindow->setMaximumSize(QSize(16777215, 16777215));
        FirstWindow->setStyleSheet(QString::fromUtf8("#FirstWindow{background-color: rgb(243,243,243);}\n"
"QStackedWidget{background-color: rgb(114,161,211);}"));
        FirstWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        actionlogout = new QAction(FirstWindow);
        actionlogout->setObjectName(QString::fromUtf8("actionlogout"));
        actionchangePassword = new QAction(FirstWindow);
        actionchangePassword->setObjectName(QString::fromUtf8("actionchangePassword"));
        actionaddMission = new QAction(FirstWindow);
        actionaddMission->setObjectName(QString::fromUtf8("actionaddMission"));
        actioncheckMission = new QAction(FirstWindow);
        actioncheckMission->setObjectName(QString::fromUtf8("actioncheckMission"));
        actionsendMssion = new QAction(FirstWindow);
        actionsendMssion->setObjectName(QString::fromUtf8("actionsendMssion"));
        actionuser = new QAction(FirstWindow);
        actionuser->setObjectName(QString::fromUtf8("actionuser"));
        actionji = new QAction(FirstWindow);
        actionji->setObjectName(QString::fromUtf8("actionji"));
        actionhong = new QAction(FirstWindow);
        actionhong->setObjectName(QString::fromUtf8("actionhong"));
        actiongeshan = new QAction(FirstWindow);
        actiongeshan->setObjectName(QString::fromUtf8("actiongeshan"));
        actiondirectory = new QAction(FirstWindow);
        actiondirectory->setObjectName(QString::fromUtf8("actiondirectory"));
        actiondaochu = new QAction(FirstWindow);
        actiondaochu->setObjectName(QString::fromUtf8("actiondaochu"));
        actiondaoru = new QAction(FirstWindow);
        actiondaoru->setObjectName(QString::fromUtf8("actiondaoru"));
        centralwidget = new QWidget(FirstWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        widget_name = new QWidget(centralwidget);
        widget_name->setObjectName(QString::fromUtf8("widget_name"));
        widget_name->setMinimumSize(QSize(0, 120));
        widget_name->setMaximumSize(QSize(16777215, 120));
        widget_name->setStyleSheet(QString::fromUtf8("QWidget{background-color: rgb(27, 44, 60);}"));
        horizontalLayout_8 = new QHBoxLayout(widget_name);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        widget = new QWidget(widget_name);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 100));
        widget->setMaximumSize(QSize(16777215, 100));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/image/user.png);"));

        horizontalLayout_8->addWidget(widget);

        label_2 = new QLabel(widget_name);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(label_2);


        verticalLayout->addWidget(widget_name);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget{background-color: rgb(47, 64, 80);}\n"
"QPushButton{background-color: rgb(87, 104, 120);}\n"
"QPushButton{color: rgb(255, 255, 255);}"));
        verticalLayout_6 = new QVBoxLayout(widget_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pushButton_4 = new QPushButton(widget_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(200, 60));
        pushButton_4->setMaximumSize(QSize(120, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(pushButton_4);

        pushButton_11 = new QPushButton(widget_4);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setMinimumSize(QSize(200, 60));
        pushButton_11->setMaximumSize(QSize(120, 60));
        pushButton_11->setFont(font1);

        verticalLayout_6->addWidget(pushButton_11);

        pushButton_7 = new QPushButton(widget_4);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(200, 60));
        pushButton_7->setMaximumSize(QSize(200, 60));
        pushButton_7->setFont(font1);

        verticalLayout_6->addWidget(pushButton_7);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(200, 60));
        pushButton_3->setMaximumSize(QSize(120, 60));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(pushButton_3);

        pushButton_10 = new QPushButton(widget_4);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(200, 60));
        pushButton_10->setMaximumSize(QSize(120, 60));
        pushButton_10->setSizeIncrement(QSize(0, 60));
        pushButton_10->setBaseSize(QSize(0, 60));
        pushButton_10->setFont(font1);
        pushButton_10->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(pushButton_10);

        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 60));
        pushButton->setMaximumSize(QSize(120, 60));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(200, 60));
        pushButton_2->setMaximumSize(QSize(120, 60));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(pushButton_2);

        pushButton_6 = new QPushButton(widget_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 60));
        pushButton_6->setMaximumSize(QSize(16777215, 60));
        pushButton_6->setFont(font1);

        verticalLayout_6->addWidget(pushButton_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        verticalLayout->addWidget(widget_4);


        verticalLayout_5->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_5);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("border-top: 1px solid red; background-color: rgb(36,81,120);"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout->addWidget(line);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(25);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(20);
        label_3->setFont(font3);

        horizontalLayout_4->addWidget(label_3);

        pushButton_23 = new QPushButton(centralwidget);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setMinimumSize(QSize(100, 40));
        pushButton_23->setMaximumSize(QSize(100, 16777215));
        pushButton_23->setFont(font1);
        pushButton_23->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{background-color: rgb(21, 158, 130);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:12px;padding:2px 4px;}"));

        horizontalLayout_4->addWidget(pushButton_23);

        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(100, 40));
        pushButton_9->setMaximumSize(QSize(100, 16777215));
        pushButton_9->setFont(font1);
        pushButton_9->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{background-color: rgb(21, 158, 130);}\n"
"QPushButton{color: rgb(255, 255, 255);}\n"
"QPushButton{border:2px groove gray;border-radius:12px;padding:2px 4px;}"));

        horizontalLayout_4->addWidget(pushButton_9);


        verticalLayout_3->addLayout(horizontalLayout_4);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QFont font4;
        font4.setPointSize(26);
        stackedWidget->setFont(font4);
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(243,243,243)"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_5 = new QHBoxLayout(page);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        missionSendWidget = new MissionSendWidget(page);
        missionSendWidget->setObjectName(QString::fromUtf8("missionSendWidget"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Agency FB"));
        missionSendWidget->setFont(font5);
        missionSendWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(missionSendWidget);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        tableWidget_4 = new QTableWidget(page_2);
        if (tableWidget_4->columnCount() < 4)
            tableWidget_4->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget_4->rowCount() < 7)
            tableWidget_4->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(6, __qtablewidgetitem10);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));
        tableWidget_4->setGeometry(QRect(50, 30, 1200, 541));
        tableWidget_4->setStyleSheet(QString::fromUtf8(""));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 640, 181, 61));
        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(260, 640, 191, 61));
        QFont font6;
        font6.setPointSize(19);
        pushButton_5->setFont(font6);
        pushButton_8 = new QPushButton(page_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(520, 640, 211, 61));
        pushButton_8->setFont(font6);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        verticalLayout_4 = new QVBoxLayout(page_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableWidget_2 = new QTableWidget(page_4);
        if (tableWidget_2->columnCount() < 9)
            tableWidget_2->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(8, __qtablewidgetitem19);
        if (tableWidget_2->rowCount() < 9)
            tableWidget_2->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(8, __qtablewidgetitem28);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

        verticalLayout_4->addWidget(tableWidget_2);

        stackedWidget->addWidget(page_4);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        tableWidget = new QTableWidget(page_7);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem33);
        if (tableWidget->rowCount() < 7)
            tableWidget->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem50);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(70, 10, 1221, 261));
        pushButton_12 = new QPushButton(page_7);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(70, 310, 191, 61));
        pushButton_12->setFont(font6);
        pushButton_13 = new QPushButton(page_7);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(380, 310, 191, 61));
        pushButton_13->setFont(font6);
        lineEdit_2 = new QLineEdit(page_7);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(650, 310, 291, 61));
        pushButton_14 = new QPushButton(page_7);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(950, 310, 191, 61));
        pushButton_14->setFont(font6);
        tableWidget_3 = new QTableWidget(page_7);
        if (tableWidget_3->columnCount() < 5)
            tableWidget_3->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem55);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(80, 400, 1211, 281));
        stackedWidget->addWidget(page_7);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        tableWidget_5 = new QTableWidget(page_5);
        if (tableWidget_5->columnCount() < 5)
            tableWidget_5->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(4, __qtablewidgetitem60);
        tableWidget_5->setObjectName(QString::fromUtf8("tableWidget_5"));
        tableWidget_5->setGeometry(QRect(50, 30, 1200, 541));
        lineEdit_8 = new QLineEdit(page_5);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(50, 640, 181, 61));
        pushButton_20 = new QPushButton(page_5);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(260, 640, 191, 61));
        pushButton_20->setFont(font6);
        pushButton_19 = new QPushButton(page_5);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(520, 640, 211, 61));
        pushButton_19->setFont(font6);
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        horizontalLayout_3 = new QHBoxLayout(page_6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mission_macro_widget = new customTableWidget(page_6);
        mission_macro_widget->setObjectName(QString::fromUtf8("mission_macro_widget"));

        horizontalLayout_2->addWidget(mission_macro_widget);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        stackedWidget->addWidget(page_6);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        horizontalLayout_6 = new QHBoxLayout(page_8);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        widget_2 = new DataManage(page_8);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        horizontalLayout_6->addWidget(widget_2);

        stackedWidget->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        horizontalLayout_7 = new QHBoxLayout(page_9);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        widget_3 = new customTableWidget(page_9);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));

        horizontalLayout_7->addWidget(widget_3);

        stackedWidget->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        horizontalLayout_9 = new QHBoxLayout(page_10);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        widget_5 = new DataGeshanManage(page_10);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));

        horizontalLayout_9->addWidget(widget_5);

        stackedWidget->addWidget(page_10);
        page_11 = new QWidget();
        page_11->setObjectName(QString::fromUtf8("page_11"));
        verticalLayout_7 = new QVBoxLayout(page_11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_4 = new QLabel(page_11);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_7->addWidget(label_4);

        listWidget = new QListWidget(page_11);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_7->addWidget(listWidget);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        pushButton_15 = new QPushButton(page_11);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

        horizontalLayout_10->addWidget(pushButton_15);


        verticalLayout_7->addLayout(horizontalLayout_10);

        stackedWidget->addWidget(page_11);

        verticalLayout_3->addWidget(stackedWidget);


        horizontalLayout->addLayout(verticalLayout_3);

        FirstWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FirstWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FirstWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(FirstWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1600, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuqianyi = new QMenu(menuBar);
        menuqianyi->setObjectName(QString::fromUtf8("menuqianyi"));
        FirstWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuqianyi->menuAction());
        menu->addAction(actionuser);
        menu->addAction(actionji);
        menu->addAction(actionhong);
        menu_2->addAction(actiondirectory);
        menuqianyi->addAction(actiondaochu);
        menuqianyi->addAction(actiondaoru);

        retranslateUi(FirstWindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(FirstWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FirstWindow)
    {
        FirstWindow->setWindowTitle(QApplication::translate("FirstWindow", "\344\270\255\345\277\203\350\277\220\346\216\247\347\256\241\347\220\206\350\275\257\344\273\266", nullptr));
        actionlogout->setText(QApplication::translate("FirstWindow", "logout", nullptr));
        actionchangePassword->setText(QApplication::translate("FirstWindow", "changePassword", nullptr));
        actionaddMission->setText(QApplication::translate("FirstWindow", "addMission", nullptr));
        actioncheckMission->setText(QApplication::translate("FirstWindow", "checkMission", nullptr));
        actionsendMssion->setText(QApplication::translate("FirstWindow", "sendMssion", nullptr));
        actionuser->setText(QApplication::translate("FirstWindow", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        actionji->setText(QApplication::translate("FirstWindow", "\351\201\245\346\265\213\347\253\231\347\256\241\347\220\206", nullptr));
        actionhong->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\345\256\217\347\256\241\347\220\206", nullptr));
        actiongeshan->setText(QApplication::translate("FirstWindow", "\346\240\274\346\240\205\346\226\207\344\273\266\347\256\241\347\220\206", nullptr));
        actiondirectory->setText(QApplication::translate("FirstWindow", "\346\226\207\344\273\266\346\240\271\347\233\256\345\275\225\351\200\211\346\213\251", nullptr));
        actiondaochu->setText(QApplication::translate("FirstWindow", "\345\257\274\345\207\272", nullptr));
        actiondaoru->setText(QApplication::translate("FirstWindow", "\345\257\274\345\205\245", nullptr));
        label_2->setText(QApplication::translate("FirstWindow", "\346\227\240\347\224\250\346\210\267", nullptr));
        pushButton_4->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\345\217\221\345\270\203", nullptr));
        pushButton_11->setText(QApplication::translate("FirstWindow", "\350\277\234\345\234\272\346\225\260\346\215\256\344\274\240\350\276\223", nullptr));
        pushButton_7->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\347\273\274\345\220\210\351\205\215\347\275\256", nullptr));
        pushButton_3->setText(QApplication::translate("FirstWindow", "\350\207\252\345\256\232\344\271\211\346\225\260\346\215\256\n"
"\345\274\200\345\217\221\346\216\245\345\217\243", nullptr));
        pushButton_10->setText(QApplication::translate("FirstWindow", "\345\201\245\345\272\267\347\212\266\346\200\201", nullptr));
        pushButton->setText(QApplication::translate("FirstWindow", "\351\201\245\346\265\213\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        pushButton_2->setText(QApplication::translate("FirstWindow", "\346\225\260\346\215\256\346\240\274\346\240\205\347\256\241\347\220\206", nullptr));
        pushButton_6->setText(QApplication::translate("FirstWindow", "\347\224\265\345\255\220\346\240\274\346\240\205\n"
"\346\226\207\346\241\243\347\256\241\346\216\247", nullptr));
        label->setText(QApplication::translate("FirstWindow", "\344\270\255\345\277\203\350\277\220\346\216\247\347\256\241\347\220\206\350\275\257\344\273\266", nullptr));
        label_3->setText(QApplication::translate("FirstWindow", "\346\227\266\351\227\264", nullptr));
        pushButton_23->setText(QApplication::translate("FirstWindow", "\346\216\245\346\224\266\350\277\233\345\261\225", nullptr));
        pushButton_9->setText(QApplication::translate("FirstWindow", "\346\237\245\347\234\213\346\227\245\345\277\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FirstWindow", "\350\264\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FirstWindow", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FirstWindow", "\347\234\237\345\256\236\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FirstWindow", "\347\224\265\350\257\235", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("FirstWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("FirstWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_4->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("FirstWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_4->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("FirstWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_4->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("FirstWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_4->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QApplication::translate("FirstWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_4->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QApplication::translate("FirstWindow", "7", nullptr));
        pushButton_5->setText(QApplication::translate("FirstWindow", "\346\237\245\346\211\276", nullptr));
        pushButton_8->setText(QApplication::translate("FirstWindow", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("FirstWindow", "\347\253\231\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("FirstWindow", "\345\273\266\350\277\237(ms)", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("FirstWindow", "\344\270\242\345\214\205\347\216\207(%)", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("FirstWindow", "\351\200\232\344\277\241\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("FirstWindow", "\346\225\260\346\215\256\346\265\201\345\205\245\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem16->setText(QApplication::translate("FirstWindow", "\344\277\241\345\231\252\346\257\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem17->setText(QApplication::translate("FirstWindow", "AGC\347\224\265\345\216\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem18->setText(QApplication::translate("FirstWindow", "\346\226\271\344\275\215\350\247\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_2->horizontalHeaderItem(8);
        ___qtablewidgetitem19->setText(QApplication::translate("FirstWindow", "\344\277\257\344\273\260\350\247\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_2->verticalHeaderItem(3);
        ___qtablewidgetitem23->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->verticalHeaderItem(4);
        ___qtablewidgetitem24->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_2->verticalHeaderItem(5);
        ___qtablewidgetitem25->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_2->verticalHeaderItem(6);
        ___qtablewidgetitem26->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_2->verticalHeaderItem(7);
        ___qtablewidgetitem27->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_2->verticalHeaderItem(8);
        ___qtablewidgetitem28->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem29->setText(QApplication::translate("FirstWindow", "\346\240\274\346\240\205\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem30->setText(QApplication::translate("FirstWindow", "\345\215\225\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem31->setText(QApplication::translate("FirstWindow", "\345\236\213\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem32->setText(QApplication::translate("FirstWindow", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem33->setText(QApplication::translate("FirstWindow", "\347\211\210\346\234\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("FirstWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem35->setText(QApplication::translate("FirstWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem36->setText(QApplication::translate("FirstWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem37->setText(QApplication::translate("FirstWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem38->setText(QApplication::translate("FirstWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem39->setText(QApplication::translate("FirstWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem40->setText(QApplication::translate("FirstWindow", "New Row", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_12->setText(QApplication::translate("FirstWindow", "\345\257\274\345\205\245", nullptr));
        pushButton_13->setText(QApplication::translate("FirstWindow", "\345\257\274\345\207\272", nullptr));
        pushButton_14->setText(QApplication::translate("FirstWindow", "\346\237\245\350\257\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem41->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem42->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem43->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\346\250\241\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem44->setText(QApplication::translate("FirstWindow", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem45->setText(QApplication::translate("FirstWindow", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem46->setText(QApplication::translate("FirstWindow", "\345\237\272\347\253\231\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem47->setText(QApplication::translate("FirstWindow", "ip\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem48->setText(QApplication::translate("FirstWindow", "\345\217\202\346\225\2601", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem49->setText(QApplication::translate("FirstWindow", "\345\217\202\346\225\2602", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget_5->horizontalHeaderItem(4);
        ___qtablewidgetitem50->setText(QApplication::translate("FirstWindow", "\345\217\202\346\225\2603", nullptr));
        pushButton_20->setText(QApplication::translate("FirstWindow", "\346\237\245\346\211\276", nullptr));
        pushButton_19->setText(QApplication::translate("FirstWindow", "\346\267\273\345\212\240\345\237\272\347\253\231", nullptr));
        label_4->setText(QApplication::translate("FirstWindow", "\344\273\273\345\212\241\347\273\274\345\220\210\351\205\215\347\275\256\350\275\257\344\273\266", nullptr));
        pushButton_15->setText(QApplication::translate("FirstWindow", "\346\270\205\347\251\272", nullptr));
        menu->setTitle(QApplication::translate("FirstWindow", "\351\205\215\347\275\256", nullptr));
        menu_2->setTitle(QApplication::translate("FirstWindow", "\347\256\241\347\220\206", nullptr));
        menuqianyi->setTitle(QApplication::translate("FirstWindow", "\350\277\201\347\247\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FirstWindow: public Ui_FirstWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTWINDOW_H
