#include "firstwindow.h"
#include "ui_firstwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include<QJsonObject>
#include<QTextCodec>
#include <QJsonArray>
#include <QtEndian>
#include "QSqlDatabase"
#include <QObject>
#include <QAxObject>
#include <QSqlRecord>
#include <QSqlQuery>
#include "filedata.h"
#include <QSqlError>
#include "receievedata.h"
#include <QApplication>
#include "customtablewidget.h"
#include "stationmanage.h"
#include "missionmanage.h"
#include "gemanage.h"
#include "writefiledata.h"
#include <QtcpServer>
#include "delaytest.h"
#include "loginfo.h"
#include "remotedatawidget.h"
#include "config/configinfo.h"
#include "writefile/writefileworker.h"
#include "software_insert.h"
#include "util/bytemethod.h"
#include "entity/mission.h"
#include "entity/missionbasicinfo.h"
#include "entity/missionmacroinfo.h"
#include "missionmanage.h"
#include "missiontablewidget.h"
#include "datastatistic.h"
#include "basebandmanage.h"
#include "missionallconfig.h"
#include "datasourcemanage.h"
#include "ui/streamsmainwindow.h"

#define TIMER_TIMEOUT   (1000)
#define TIMER_TIMEOUT2   (1000)
#define TIMER_TIMEOUT3   (300)

QJsonArray array2;
QUdpSocket *udpsocket;
QTcpSocket *tcpSocket1;
QTcpSocket *tcpSocket2;
QTcpServer *tcpServer;
QList<MutiFile*> mutiFile;
QString currentUser;
FileDownLoadWidget *grilleWidget;
FileDownLoadWidget *displayWidget;

QTcpServer *grilleTcpserver;
QTcpServer *displayTcpserver;

WriteFileWorker *grilleWorker;
WriteFileWorker *displayWorker;

RemoteDataWidget *p;

QList<MissionMacroInfo*> macroInfo;
QList<MissionBasicInfo*> basicInfo;
QList<Mission*> missionInfo;
QList<Station*> stationInfo;
QList<User*> userInfo;
QList<QString> geshanInfo;
QList<BaseBand*> baseBandInfo;

int FirstWindow::role;
QString userName;
FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{

    ui->setupUi(this);


    initialAllCustomTableWidget();
    initialMenuSlots();
    initial_multiFile();

//    ui->pushButton->hide();
//    ui->pushButton_2->hide();
    ui->pushButton_6->hide();
//    ui->pushButton_23->hide();
    ui->pushButton_9->hide();
//    ui->pushButton_23->hide();

    grilleWidget = new FileDownLoadWidget("格栅下载");
    grilleWidget->settype(AgreeMent::GRILLE);
    displayWidget = new FileDownLoadWidget("显示画面下载");
    displayWidget->settype(AgreeMent::DISPLAY);

//    ui->widget->hide();
//    ui->pushButton_6->hide();
    packageLength = 0;

    softewareInsert();

    printfile();
    printStationInfo();
    initialtcp();

    testDelay();
    initialTimer();

    initialDataGeshanManage();
    connect(ui->pushButton_9,&QPushButton::clicked,this,&FirstWindow::logButtonPush);

    connect(&currentTimer,SIGNAL(timeout()), this, SLOT(handleCurrentTime()));
    currentTimer.start(1000);


    testPackgeSocket = new QUdpSocket(this);
    bool isBindOk2 = testPackgeSocket->bind(9013);
    if(!isBindOk2){
        QMessageBox::information(this,"绑定信息","9013端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }

    connect(testPackgeSocket,&QUdpSocket::readyRead, this,&FirstWindow::testPackgeSocketSlot);

    QTcpServer *tcpServer = new QTcpServer(this);
    bool tcpListenOk = tcpServer->listen(QHostAddress::Any,9011);
    connect(tcpServer,&QTcpServer::newConnection,[=](){

        QTcpSocket *tcpSocket = new QTcpSocket();
        tcpSocket = tcpServer->nextPendingConnection();



    });
    if(!tcpListenOk){
        QMessageBox::information(this,"绑定信息","9011端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }
    ui->tableWidget_2->setRowCount(mutiFile.size());
    for(int i=0;i<mutiFile.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(mutiFile.at(i)->stationName);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(i,0,item);
    }
//    printMission();



    QSqlQuery query(db);
    QString qs = QString("select * from `missionnew2`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    int code = rec.indexOf("任务标识");

    QStringList comboboxList;

    qDebug () << "0";
    while (query.next())
    {
        QString codestr = query.value(code).toString();
        comboboxList.append(codestr);
    }
    QMap<quint8,QStringList> combobox_map;
    combobox_map.insert(quint8(11),comboboxList);


    qRegisterMetaType<QHostAddress>("QHostAddress");

    udpsocket = new QUdpSocket(this);
    bool isBindOk = udpsocket->bind(9051);
    if(!isBindOk){
        QMessageBox::information(this,"socket绑定信息","socket绑定端口失败,请确保9051端口开放");
        qApp->quit();
    }

    testOutSocket = new QUdpSocket(this);
    bool isBindOk3 = testOutSocket->bind(9062);
    if(!isBindOk3){
        QMessageBox::information(this,"socket绑定信息","socket绑定端口失败,请确保9062端口开放");
        qApp->quit();
    }
    connect(testOutSocket,&QUdpSocket::readyRead, this,&FirstWindow::outSocketRead);

    connect(this,&FirstWindow::emitdeleteProgress,pro,&progress::getDeleteProgress);

    QThread *t = new QThread;
    worker = new receieveData;
    worker->moveToThread(t);
    connect(worker,&receieveData::signalSendBasicInfo,pro,&progress::setFileNameCodeRange);
    connect(worker,&receieveData::sendAllMission,ui->missionSendWidget,&MissionSendWidget::sendAllMission);

    connect(worker,&receieveData::sendUser,this,&FirstWindow::getUser);
    connect(worker,&receieveData::sendDelete,this,&FirstWindow::getDelete);

//    connect(worker,&receieveData::sendPro,this,&FirstWindow::getPro);
//    connect(this,&FirstWindow::sendPro,pro,&progress::getPro);

//    connect(this,&missionreview::sendFile,worker,&SendFile::sendFile);
    connect(this,&FirstWindow::sendSocketData,worker,&receieveData::readPendingDatagrams);
    connect(udpsocket,&QUdpSocket::readyRead, this,&FirstWindow::readPendingDatagrams);

    connect(worker,&receieveData::sendWriteFile,this,&FirstWindow::writeSendFile);
    connect(worker,&receieveData::initialGrille,this,&FirstWindow::initialGrille);
    connect(worker,&receieveData::initialDisplay,this,&FirstWindow::initialDisplay);
    connect(worker,&receieveData::refreshAllMission,ui->missionSendWidget,&MissionSendWidget::refreshAllMission);
    connect(worker,&receieveData::startSendDllFile,remoteDataWidget,&RemoteDataSingleWidget::startSendingFile);

    connect(worker,&receieveData::addNewMission,ui->missionSendWidget,&MissionSendWidget::addNewMission);
    connect(worker,&receieveData::retrieveMission,ui->missionSendWidget,&MissionSendWidget::retrieveMission);
    connect(worker,&receieveData::abortMission,ui->missionSendWidget,&MissionSendWidget::abortMission);
    connect(worker,&receieveData::goonMission,ui->missionSendWidget,&MissionSendWidget::goonMission);

    connect(worker,&receieveData::sendMd5Result,remoteDataWidget,&RemoteDataSingleWidget::getMd5Result);
    connect(worker,&receieveData::sendHealthData,this,&FirstWindow::refreshHealthData);
    connect(worker,&receieveData::sendProcessData,pro,&progress::getProcessData);
    connect(worker,&receieveData::sendAllGeshan,ui->widget_3,&GeManage::initial_table_item);
    connect(worker,&receieveData::finishAddGeshan,ui->widget_3,&GeManage::finishAddGeshan);
    connect(worker,&receieveData::wrongAddGeshan,ui->widget_3,&GeManage::wrongAddGeshan);
    connect(worker,&receieveData::sendChildFile,ui->widget_3,&GeManage::refreshChildFile);
    connect(worker,&receieveData::sendAdvanceResult,ui->missionSendWidget,&MissionSendWidget::refreshMissionBasic);
    connect(worker,&receieveData::sendDataAdvanceResult,ui->widget_2,&DataManage::refreshAll);
    connect(worker,&receieveData::sendAllRemote,ui->widget_2,&DataManage::refreshAll);

    connect(worker,&receieveData::sendDataMd5,this,&FirstWindow::getDataMd5);
    connect(worker,&receieveData::sendDianziMd5,this,&FirstWindow::getDianziMd5);

    connect(worker,&receieveData::sendStatisticResult,dataStatistic,&DataStatistic::initialall);
    connect(worker,&receieveData::sendDeleteDataResult,ui->widget_2,&DataManage::getDeleteResult);
    connect(worker,&receieveData::sendUpdateDataResult,ui->widget_2,&DataManage::getUpdateResult);

    connect(worker,&receieveData::sendUpdateGeshanResult,ui->widget_3,&GeManage::getUpdateResult);

    t->start();

    arraylin.resize(0);
    QIcon *icon = new QIcon(":/image/greenlight.png");

//    printRTimeChart();


//    connect(udpsocket,&QUdpSocket::readyRead, this,&FirstWindow::readPendingDatagrams);

//    db.setHostName("127.0.0.1");
//    db.setPort(3306);
//    db.setDatabaseName("pro504");
//    db.setUserName("root");
//    db.setPassword("123456");
//    bool ok = db.open();
//    if(ok==true)
//    {
//        qDebug() << "连接成功";
//    }

    connect(pro,&progress::finishFile,this,&FirstWindow::finishFile);
//    printChart();
//    connect(ui->customPlot, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)),
//            this, SLOT(change(QCPAbstractPlottable*,int,QMouseEvent*)));

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget->setStyleSheet("font-size: 14pt;");
    ui->tableWidget->setAlternatingRowColors(true);

    ui->tableWidget_3->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget_3->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget_3->setStyleSheet("font-size: 14pt;");
    ui->tableWidget_3->setAlternatingRowColors(true);


//    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white;border:2px solid white}");
//    ui->tableWidget_2->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white}");
//    ui->tableWidget_2->setStyleSheet("font-size: 12pt;");
//    ui->tableWidget_2->setAlternatingRowColors(true);

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->setRowHeight(0,40);
    ui->tableWidget_2->verticalHeader()->setVisible(0);

    ui->tableWidget_4->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget_4->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget_4->setStyleSheet("font-size: 14pt;");
    ui->tableWidget_4->setAlternatingRowColors(true);

    ui->tableWidget_5->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget_5->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget_5->setStyleSheet("font-size: 14pt;");
    ui->tableWidget_5->setAlternatingRowColors(true);

//    ui->tableWidget_6->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
//    ui->tableWidget_6->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
//    ui->tableWidget_6->setStyleSheet("font-size: 14pt;");
//    ui->tableWidget_6->setAlternatingRowColors(true);



//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_4->verticalHeader()->setVisible(0);
//    ui->tableWidget_4->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
//    ui->tableWidget_4->verticalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setRowHeight(0,40);
    ui->tableWidget_4->verticalHeader()->setVisible(0);

    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_5->setRowHeight(0,40);
    ui->tableWidget_5->verticalHeader()->setVisible(0);

//    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_6->setRowHeight(0,40);
//    ui->tableWidget_6->verticalHeader()->setVisible(0);

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_4->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_5->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->tableWidget_6->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->tableWidget->verticalHeader()->setVisible(0);
//    ui->tableWidget_2->verticalHeader()->setVisible(0);
//    ui->tableWidget_3->verticalHeader()->setVisible(0);
//    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


//    ui->tableWidget_5->verticalHeader()->setVisible(0);
//    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_5->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
//    ui->tableWidget_5->verticalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");

//    ui->tableWidget_6->verticalHeader()->setVisible(0);
//    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_6->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
//    ui->tableWidget_6->verticalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");







    ui->tableWidget->verticalHeader()->setVisible(0);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setVisible(0);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
//    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
//    printUserInfo();

//     = new Q(this);
//    ->listen(QHostAddress::Any,7777);


    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(testSlot(int,int)));

//    QSqlQuery queryfilepro=QSqlQuery(db);
////    queryfilepro.exec("select * from fileproperty where id = (select max(id) from fileproperty);");
//    queryfilepro.exec("select * from fileproperty;");
//    QSqlRecord rec = queryfilepro.record();

//    qDebug() << "Number of columns: " << rec.count();

////    initialstack();

//    if(queryfilepro.size()<8){
//        ui->tableWidget->setRowCount(8);
//    }else{
//        ui->tableWidget->setRowCount(queryfilepro.size());
//    }
//    int nameCol = rec.indexOf("name"); // index of the field "name"

//    int j=0;
//    QVariantList list;
//    list.append("name");
//    list.append("unit");
//    list.append("model");
//    list.append("time");
//    list.append("edition");

//    while (queryfilepro.next())
//    {
//        qDebug() << j;
//        for(int i=0;i<5;i++){
//            qDebug() << i<<"  "<<j;
//            ui->tableWidget->setItem(j,i,new QTableWidgetItem(queryfilepro.value(list.at(i).toString()).toString()));
//            if(i==3)
//            {
//                ui->tableWidget->setItem(j,i,new QTableWidgetItem(QDateTime::fromTime_t(queryfilepro.value(list.at(i).toString()).toInt()).toString("yyyy-MM-dd hh:mm:ss")));
//            }
//        }
//        j++;
//        ui->tableWidget->setItem();
//        id = queryfilepro.value(nameCol).toInt();
//        qDebug() << id; // output all names
//    }

//    qDebug() << "here";

//    isfile = false;
//    recsize = 0;
//    heart = 0;
//    h=0;

    QListWidgetItem *item = new QListWidgetItem();
    QColor *color = new QColor();
    color->setRgb(0,170,0);
    item->setTextColor(*color);
    item->setText("服务启动");
//    ui->listWidget_2->addItem(item);

    QFont font;
    font.setPointSize(19);

//    ui->listWidget_2->setFont(font);

//    connect(,&Q::newConnection,[=](){

//        m_pTimer2->start(TIMER_TIMEOUT2);
//        m_pTimer3->start(TIMER_TIMEOUT3);
//        qDebug() << "new connection";
//        //取出等待链接的下一个socket
//        tcpSocket = ->nextPendingConnection();

//        QString ip = tcpSocket->peerAddress().toString();
//        quint16 port = tcpSocket->peerPort();

//        QString temp = QString ("[%1:%2]已成功接入").arg(ip).arg(port);

//        QListWidgetItem *item = new QListWidgetItem();
//        QColor *color = new QColor();
//        color->setRgb(0,170,0);
//        item->setTextColor(*color);
//        item->setText(temp);

//        ui->listWidget_2->addItem(item);

//        QTableWidgetItem *item2 = new QTableWidgetItem();
//        QColor *color2 = new QColor();
//        color2->setRgb(255,255,255);
//        item2->setTextColor(*color2);
//        item2->setText("已连接");

//        ui->tableWidget_5->setItem(0,2,item2);

//        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
//            qDebug() << "readyread";
//            if(isfile)
//            {
//                dealfiledata();
//            }else{
//                dealdata();
//            }
//        });
//    });

    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&FirstWindow::postback);

    manager2 = new QNetworkAccessManager(this);
    connect(manager2,&QNetworkAccessManager::finished,this,&FirstWindow::postback2);

    manager3 = new QNetworkAccessManager(this);
    connect(manager3,&QNetworkAccessManager::finished,this,&FirstWindow::postback3);

    manager4 = new QNetworkAccessManager(this);
    connect(manager4,&QNetworkAccessManager::finished,this,&FirstWindow::postback4);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);

    m_pTimer2 = new QTimer(this);
    connect(m_pTimer2, SIGNAL(timeout()), this, SLOT(handleTimeout2()));

    m_pTimer3 = new QTimer(this);
    connect(m_pTimer3, SIGNAL(timeout()), this, SLOT(handleTimeout3()));

    QFont font10;
    font10.setPointSize(19);
//    ui->tableWidget_5->setFont(font10);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0,150)); // 最后一项为透明度
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));

    print1();
    print2();
    print3();
    print4();


    ui->stackedWidget->setCurrentIndex(0);
    setPushStyleSheet(ui->pushButton_4);
    setCommonStyleSheet(ui->pushButton);
    setCommonStyleSheet(ui->pushButton_3);
    setCommonStyleSheet(ui->pushButton_10);
    setCommonStyleSheet(ui->pushButton_2);
    setCommonStyleSheet(ui->pushButton_6);
    setCommonStyleSheet(ui->pushButton_7);
    setCommonStyleSheet(ui->pushButton_3);
    setCommonStyleSheet(ui->pushButton_11);
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        setPushStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });

    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setPushStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });


    connect(ui->pushButton_10,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(3);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setPushStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(7);
        setCommonStyleSheet(ui->pushButton_4);
        setPushStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(8);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setPushStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(9);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setPushStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });
    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(10);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setPushStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(11);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setPushStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_11);
    });
    connect(ui->pushButton_11,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(12);
        setCommonStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
        setCommonStyleSheet(ui->pushButton_3);
        setPushStyleSheet(ui->pushButton_11);
    });

    connect(ui->actionlogout,&QAction::triggered,[this](){
        MainWindow *p = new MainWindow;
        post();
        response = "";
        p->show();
        this->hide();
    });


//    connect(ui->pushButton,&QPushButton::clicked,[=](){

//        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
//        if(!items.empty()) //表格有某行被选中
//        {
//            //获取该行的成员数
//            int count = items.count();
//            // 获取该行的行号
////            int rowindex = ui->listWidget->row(items.at(0));
//            // 打印该行所有成员内容
//            for(int i = 0; i < count; i++)
//            {
//                QListWidgetItem *item = items.at(i); //该行第i列的item
//                qDebug() << item->text(); //获取内容
//                post2(item->text());


//            }
//        }
//    });

    QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendAllMissionRequest()),*addr,ConfigInfo::centerUdpPort);
    qDebug() << "请求任务信息加载";
    this->setWindowFlags(this->windowFlags()|Qt::WindowMaximizeButtonHint);
    this->setWindowState(Qt::WindowNoState);

    ui->tableWidget_2->setColumnHidden(4, true);

    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::requestGeshan()),*addr,ConfigInfo::centerUdpPort);

    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::requestRemoteGeshan()),*addr,ConfigInfo::centerUdpPort);
    connect(ui->pushButton_15,&QPushButton::clicked,[=](){
        dataStatistic->initial();
        dataStatistic->show();
    });
    connect(remoteDataWidget,&RemoteDataSingleWidget::sendFinishSend,ui->widget_3,&GeManage::sendFolderFile);
    MissionAllConfig *missionAllConfig = new MissionAllConfig();
    ui->verticalLayout_9->addWidget(missionAllConfig);
}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::initialAllCustomTableWidget()
{
    QStringList columnList;
    columnList << "任务宏" << "参数1"<< "参数2"<< "参数3"<< "参数4"<< "参数5";
    ui->mission_macro_widget->set_widget_column_header(columnList);
    ui->mission_macro_widget->initial_widget();



    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
    ui->tableWidget_2->verticalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
    ui->tableWidget_2->setStyleSheet("font-size: 12pt;");
//    ui->tableWidget->setAlternatingRowColors(true);
    QPalette pal = ui->tableWidget_2->palette();
    pal.setColor(QPalette::Base, QColor(255, 255, 255));
    pal.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
    ui->tableWidget_2->setPalette(pal);
    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->viewport()->update();



    p = new RemoteDataWidget();
    ui->verticalLayout_7->addWidget(p);
    p->show();

}

void FirstWindow::initialMenuSlots()
{
    connect(ui->actionuser,&QAction::triggered,this,&FirstWindow::MenuUserSlots);
    connect(ui->actionji,&QAction::triggered,this,&FirstWindow::MenuStationSlots);
    connect(ui->actionhong,&QAction::triggered,this,&FirstWindow::MenuMissionSlots);
//    connect(ui->actiongeshan,&QAction::triggered,this,&FirstWindow::MenuGeshanSlots);
    connect(ui->actiondirectory,&QAction::triggered,this,&FirstWindow::MenuDirectorySlots);
    connect(ui->actionjidai,&QAction::triggered,this,&FirstWindow::MenuJidaiSlots);
    connect(ui->actionshujvyuan,&QAction::triggered,this,&FirstWindow::MenuDatasourceSlots);
}
//void FirstWindow::dealfiledata(){
//    qDebug() << "deadata2";
//    QByteArray array = tcpSocket->readAll();
//    qint64 len = file.write(array);
//    recsize+=len;
//    qDebug() << "recsize" << recsize << "filesize" << filesize;
//    if(recsize == filesize)
//    {
//        qDebug() << "wancheng ";
//        file.close();

//        QString head1 = "filefinish";
//        int len2 = qToBigEndian(head1.size());
//        QByteArray data((char*)&len2,4);
//        data.append(head1.toUtf8().data());

//        qint64 sentlen = tcpSocket->write(data);
//        isfile = false;
//    }
//}

//void FirstWindow::dealdata()
//{
//    if(->bytesAvailable()==0)
//    {
//        return;
//    }
//    qDebug() << "dealdata";
//    unsigned int totalBytes = 0;
//    unsigned int recvBytes = 0;
//    QByteArray block;

//    QByteArray head = tcpSocket->read(sizeof(int));
//    totalBytes = qFromBigEndian(*(int*)head.data());


//    qDebug() << "包头长度" << totalBytes;

//    while(totalBytes - recvBytes >0)
//    {
//        block.append(tcpSocket->read(totalBytes-recvBytes));
//        recvBytes = block.size();
//    }
//    if(totalBytes = recvBytes)
//    {
//        QString str = QString(block);
//        qDebug() << "first block"<<str;
//        if(str == "namesize")
//        {
//            QByteArray block;
//            totalBytes = 0;
//            recvBytes = 0;
//            QByteArray head = tcpSocket->read(sizeof(int));
//            totalBytes = qFromBigEndian(*(int*)head.data());
//            qDebug() << "包头长度" << totalBytes;

//            while(totalBytes - recvBytes >0)
//            {
//                block.append(tcpSocket->read(totalBytes-recvBytes));
//                recvBytes = block.size();
//            }
//            if(totalBytes = recvBytes)
//            {
//                QString str = QString(block);
//                qDebug() << "second block"<<str;
//                fileName = QString(block).section("##",0,0);
//                filesize = QString(block).section("##",1,1).toInt();

//                QListWidgetItem *item = new QListWidgetItem();
//                QColor *color = new QColor();
//                color->setRgb(0,170,0);
//                item->setTextColor(*color);
//                item->setText(fileName+"已接收");

//                QFont font;
//                font.setPointSize(14);

//                QTableWidgetItem *item0 = new QTableWidgetItem(fileName);
//                item0->setFont(font);
//                QColor *color1 = new QColor();
//                color1->setRgb(255,255,255);
//                item0->setTextColor(*color1);
////                ui->tableWidget->setItem(h,0,item0);

//                QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间

//                QString str1 = dateTime .toString("hh时mm分ss秒");//格式化时间


//                QTableWidgetItem *item01 = new QTableWidgetItem(str1);
//                item01->setFont(font);
//                QColor *color2 = new QColor();
//                color2->setRgb(255,255,255);
//                item01->setTextColor(*color2);
////                ui->tableWidget->setItem(h,1,item01);
//                h++;

////                ui->listWidget_2->addItem(item);


//                file.setFileName(fileName);
//                bool isok = file.open(QIODevice::WriteOnly);
//                if(isok == true)
//                {
//                    QString head1 = "beginsend";
//                    int len2 = qToBigEndian(head1.size());
//                    QByteArray data((char*)&len2,4);
//                    data.append(head1.toUtf8().data());

//                    qint64 sentlen = tcpSocket->write(data);
//                    isfile = true;
//                }
//            }


//            if(tcpSocket->bytesAvailable()>0)
//            {
//                dealdata();
//            }
//        }

//        if(str == "heart")
//        {
//            qDebug() << "heart3" ;
//            heart = 0;
//            if(tcpSocket->bytesAvailable()>0)
//            {
//                dealdata();
//            }
//        }


//    }
//}

void FirstWindow::handleTimeout()
 {
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间

    QString str = dateTime .toString("yyyy年MM月dd日 hh时mm分ss秒");//格式化时间

 }

void FirstWindow::handleTimeout2()
 {
    if(heart>3)
    {
        QListWidgetItem *item = new QListWidgetItem();
        QColor *color = new QColor();
        color->setRgb(0,170,0);
        item->setTextColor(*color);
        item->setText("连接断开");

        m_pTimer2->stop();
        m_pTimer3->stop();
//        ui->listWidget_2->addItem(item);


        QTableWidgetItem *item2 = new QTableWidgetItem();
        QColor *color2 = new QColor();
        color2->setRgb(255,255,255);
        item2->setTextColor(*color2);
        item2->setText("连接断开");

//        ui->tableWidget_5->setItem(0,2,item2);
    }
    qDebug() << heart;
 }

void FirstWindow::handleTimeout3()
 {
    heart++;
    QString head1 = "heart";
    int len2 = qToBigEndian(head1.size());
    QByteArray data((char*)&len2,4);
    data.append(head1.toUtf8().data());

    qint64 sentlen = tcpSocket->write(data);
}

void FirstWindow::handleCurrentTime()
{
    QDateTime time = QDateTime::currentDateTime();//获取当前日期和时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");//格式为年-月-日 小时-分钟-秒 星期
    ui->label_3->setText(str);
}
void FirstWindow::post(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/orm/user/logout"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray token =  response.toLocal8Bit();
    request.setRawHeader("token",token);
    qDebug() <<token;
    QJsonObject json;
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    manager->post(request,dataArray);
}

void FirstWindow::postback(QNetworkReply *reply){
    QByteArray arr = reply->readAll();


    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QString content = utf8->toUnicode(arr);

    qDebug() << "content2:"<<content;
    QJsonParseError jError;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &jError);

    if(jError.error != QJsonParseError::NoError){
        qDebug() << "parse json wrong";
        qDebug() << jError.error;
    }

}


void FirstWindow::post2(QString name){
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/orm/sfile/select"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray token =  response.toLocal8Bit();
    request.setRawHeader("token",token);
    qDebug() <<token;
    QJsonObject json;
    json.insert("name", name);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    manager2->post(request,dataArray);
}

void FirstWindow::postback2(QNetworkReply *reply){
    QByteArray arr = reply->readAll();


    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QString content = utf8->toUnicode(arr);
    qDebug() << "as";
    qDebug() << "content123:"<<content;
    qDebug() << "content323:"<<content;
    QJsonParseError jError;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &jError);

    qDebug() << "as";
    if(jError.error != QJsonParseError::NoError){
        qDebug() << "parse json wrong";
        qDebug() << jError.error;
    }
    else{

        QJsonArray jObj = jDoc.array();
        qDebug() << jObj;

        array2 = jObj;
        QJsonObject a1 = jObj.at(0).toObject();
        QString ree = a1["code"].toString();

        for (int i = 0;i<array2.size();i++) {
            qDebug() << "xunhuanei";

            QJsonObject a1 = array2.at(i).toObject();
            QString name = a1["filename"].toString();
            QString time = a1["time"].toString();
            QBrush nullColor(Qt::white);
            QTableWidgetItem *item = new QTableWidgetItem(name);

            QTableWidgetItem *item2 = new QTableWidgetItem(time);
            item->setForeground(nullColor);
            item2->setForeground(nullColor);
//            ui->tableWidget->setItem(i,0,item);
//            ui->tableWidget->setItem(i,1,item2);
        }
        QFont font;
        font.setPointSize(19);
//        ui->tableWidget->setFont(font);
    }
}

void FirstWindow::print1(){
    QBarSet *set0 = new QBarSet("数据1");
    QBarSet *set1 = new QBarSet("数据2");
    QBarSet *set2 = new QBarSet("数据3");
    QBarSet *set3 = new QBarSet("数据4");
    QBarSet *set4 = new QBarSet("数据5");
    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);


    //图形中添加显示数据//
    QChart *chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("柱状图绘制实例");
    chart1->setAnimationOptions(QChart::SeriesAnimations);


    //坐标轴//
    QStringList categories;
    categories << "1月" << "2月" << "3月"<<"4月"<< "5月"<<"6月";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart1->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart1->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    //显示图例//
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);


}

void FirstWindow::print2(){
    QChart *chart2 = new QChart;

    chart2->setTitle("GDP增长图"); //设置标题


    //设置坐标轴
    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText("年份"); //设置标题
    axisX->setRange(1960, 2020); //设置范围
    axisX->setTickCount(7);      //设置主刻度个数
    axisX->setLineVisible(true); //设置轴线和刻度线可见性
    axisX->setGridLineVisible(false); //设置网格线可见性

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText("GDP(万亿:美元)"); //设置标题
    axisY->setRange(0, 20);       //设置范围
    axisY->setTickCount(21);      //设置主刻度个数
    axisY->setLineVisible(true); //设置轴线和刻度线可见性
    axisY->setGridLineVisible(false); //设置网格线可见性

    //设置序列1
    QLineSeries *series = new QLineSeries;
    series->setName("中国");    //设置序列名
    series->setColor(QColor(255,0,0)); //设置序列颜色

    //添加数据点到序列
    series->append(1960, 0.06);
    series->append(1965, 0.07);
    series->append(1970, 0.09);
    series->append(1975, 0.16);
    series->append(1980, 0.19);
    series->append(1985, 0.30);
    series->append(1990, 0.36);
    series->append(1995, 0.73);
    series->append(2000, 1.21);
    series->append(2005, 2.29);
    series->append(2010, 6.09);
    series->append(2015, 11.06);
    series->append(2020, 14.72);

    //设置序列2
    QLineSeries *series2 = new QLineSeries;
    series2->setName("美国");    //设置序列名称
    series2->setColor(QColor(0,0,255)); //设置序列颜色

    //添加数据点到序列
    series2->append(1960, 0.54);
    series2->append(1965, 0.74);
    series2->append(1970, 1.07);
    series2->append(1975, 1.68);
    series2->append(1980, 2.85);
    series2->append(1985, 4.34);
    series2->append(1990, 5.96);
    series2->append(1995, 7.64);
    series2->append(2000, 10.25);
    series2->append(2005, 13.04);
    series2->append(2010, 15.00);
    series2->append(2015, 18.24);
    series2->append(2020, 20.93);

    //设置序列3
    QLineSeries *series3 = new QLineSeries;
    series3->setName("印度");    //设置序列名称
    series3->setColor(QColor(128,128,128)); //设置序列颜色

    //添加数据点到序列
    series3->append(1960, 0.03);
    series3->append(1965, 0.06);
    series3->append(1970, 0.06);
    series3->append(1975, 0.10);
    series3->append(1980, 0.18);
    series3->append(1985, 0.23);
    series3->append(1990, 0.32);
    series3->append(1995, 0.36);
    series3->append(2000, 0.47);
    series3->append(2005, 0.82);
    series3->append(2010, 1.67);
    series3->append(2015, 2.10);
    series3->append(2020, 2.62);


    //设置序列4
    QLineSeries *series4 = new QLineSeries;
    series4->setName("日本");    //设置序列名称
    series4->setColor(QColor(144,238,144)); //设置序列颜色

    //添加数据点到序列
    series4->append(1960, 0.04);
    series4->append(1965, 0.09);
    series4->append(1970, 0.21);
    series4->append(1975, 0.52);
    series4->append(1980, 1.10);
    series4->append(1985, 1.40);
    series4->append(1990, 3.13);
    series4->append(1995, 5.55);
    series4->append(2000, 4.97);
    series4->append(2005, 4.83);
    series4->append(2010, 5.76);
    series4->append(2015, 4.44);
    series4->append(2020, 5.06);

    //给Qchart添加序列
    chart2->addSeries(series);
    chart2->addSeries(series2);
    chart2->addSeries(series3);
    chart2->addSeries(series4);


    //把序列设置到坐标轴
    chart2->setAxisX(axisX, series);
    chart2->setAxisY(axisY, series);
    chart2->setAxisX(axisX, series2);
    chart2->setAxisY(axisY, series2);
    chart2->setAxisX(axisX, series3);
    chart2->setAxisY(axisY, series3);
    chart2->setAxisX(axisX, series4);

}

void FirstWindow::print3(){
    QChart *chart3 = new QChart();
    chart3->setTitle("散点图演示");

    QScatterSeries *scatterSeries1 = new QScatterSeries(chart3);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart3);

    scatterSeries1->setName("A店铺接单数");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible();
    scatterSeries1->setMarkerSize(16);

    scatterSeries2->setName("B店铺接单数");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible();
    scatterSeries2->setMarkerSize(16);

    scatterSeries1->append(0,6);
    scatterSeries1->append(1,10);
    scatterSeries1->append(4,12);
    scatterSeries1->append(6,5);
    scatterSeries2->append(0,18);
    scatterSeries2->append(3,13);
    scatterSeries2->append(5,7);
    scatterSeries2->append(6,2);
    chart3->addSeries(scatterSeries1);
    chart3->addSeries(scatterSeries2);


    chart3->createDefaultAxes();
    chart3->axes(Qt::Horizontal).first()->setRange(0, 7);// x轴范围
    chart3->axes(Qt::Vertical).first()->setRange(0, 20);// y轴范围
    // Add space to label to add space between labels and axis在标签和轴之间加空格
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart3->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    chart3->setTheme(QChart::ChartThemeLight);

}

void FirstWindow::print4(){
    QPieSeries* series = new QPieSeries();            // 创建一个饼图对象（设置孔径就是圆环）
    series->append("Y1", 1);                          // 添加饼图切片
    series->append("Y2", 2);
    series->append("Y3", 3);
    series->append("Y4", 4);
    series->append("Y5", 5);
    series->setHoleSize(0);//饼图中间是否需要填洞
    series->setPieSize(1);//设置大小：这里的大小就是占据整个view的大小

    QPieSlice* slice;       // 获取饼图中某一个切片（在绘制圆环图Demo中是通过appent函数获取，这里换一种方式）
    QFont font("Arial", 5);

//    slice->setExploded();                            // 将切片分离饼图
//    slice->setLabelVisible();                        // 显示当前切片的标签
//    slice->setPen(QPen(Qt::darkGreen, 2));           // 设置画笔颜色和粗细
//    slice->setBrush(Qt::green);                      // 设置切片背景色

    QChart* chart = new QChart();
    chart->addSeries(series);                        // 将创建好的饼图对象添加进QChart
    chart->setTitle("饼图标题");                      // 设置图表标题

    for(int i=0;i<5;i++)
    {
        slice = series->slices().at(i);
        slice->setLabel(QString::asprintf("%.0f人,%.1f",slice->value(),slice->percentage()));
        slice->setLabelPosition(QPieSlice::LabelInsideNormal);
        slice->setLabelFont(font);
    }
    chart->addSeries(series);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setBackgroundVisible(true);  //去背景

}

void FirstWindow::initial_multiFile()
{
    QSqlQuery query(db);
    QString qs = QString("select * from stationnew");

    query.exec(qs);
    QSqlRecord rec = query.record();
    int name = rec.indexOf("基站名");
    int ip = rec.indexOf("ip地址");
    while (query.next())
    {
        MutiFile *file = new MutiFile();
        file->stationName = query.value(name).toString();
        file->stationIp = query.value(ip).toString();
        mutiFile.append(file);
    }

    for(int i=0;i<mutiFile.size();i++){
        pro->addItem(mutiFile.at(i)->stationName);
    }
}

void FirstWindow::testDelay()
{
    QThread *t = new QThread;
    worker3 = new DelayTest;
    worker3->moveToThread(t);
    connect(this,&FirstWindow::emitDelayTest,worker3,&DelayTest::delayTest);
    connect(worker3,&DelayTest::dalayReturn,this,&FirstWindow::getDelayReturn);
    t->start();

    for(int i=0;i<mutiFile.size();i++){
        mutiFile.at(i)->testDelaySocket->moveToThread(t);
        emit emitDelayTest(mutiFile.at(i));
    }

}

void FirstWindow::softewareInsert()
{
    StreamsMainWindow *streamsMainWindow = new StreamsMainWindow();

    ui->verticalLayout_11->addWidget(streamsMainWindow);

}

void FirstWindow::setName(QString name)
{
    ui->label_2->setText(name);
    userName = name;
}

void FirstWindow::setRoleText(int frame)
{
    if(frame == 0){
        ui->label_7->setText("一级用户");
    }else if(frame == 1){
        ui->label_7->setText("二级用户");
    }else if(frame == 2){
        ui->label_7->setText("三级用户");
    }
}

//void FirstWindow::initialstack()
//{
//    ui->lineEdit_8->setEnabled(false);
//    ui->lineEdit_9->setEnabled(false);
//    ui->lineEdit_10->setEnabled(false);
//    ui->lineEdit_11->setEnabled(false);
//    ui->lineEdit_12->setEnabled(false);
//    ui->lineEdit_13->setEnabled(false);
//    ui->lineEdit_14->setEnabled(false);
//    ui->pushButton_19->hide();
//    ui->pushButton_20->hide();
//    QList<QString> stacknames;
//    QList<QString> stackips;
//    QSqlQuery query(db);
//    QString qs = QString("select * from stackinfo");

//    query.exec(qs);
//    QSqlRecord rec = query.record();
//    qDebug() << "1:Number of columns: " << rec.count();
//    int stackn = rec.indexOf("stackname");
//    int stacki = rec.indexOf("stackip");


//    while (query.next())
//    {
//         qDebug() << "基站信息:" << query.value(stackn).toString() << query.value(stacki).toString();
//         stacknames << query.value(stackn).toString();
//         stackips << query.value(stacki).toString();
//    }
//    ui->pushButton_21->setText(stacknames.at(0));
//    ui->pushButton_22->setText(stacknames.at(1));

//    ui->lineEdit_8->setText(stacknames.at(0));
//    ui->lineEdit_9->setText(stackips.at(0));

//    connect(ui->pushButton_21,&QPushButton::clicked,this,[=](){
//        ui->lineEdit_8->setText(stacknames.at(0));
//        ui->lineEdit_9->setText(stackips.at(0));
//    });
//    connect(ui->pushButton_22,&QPushButton::clicked,this,[=](){
//        ui->lineEdit_8->setText(stacknames.at(1));
//        ui->lineEdit_9->setText(stackips.at(1));
//    });
//    connect(ui->pushButton_17,&QPushButton::clicked,this,[=](){
//        ui->pushButton_17->hide();
//        ui->pushButton_19->show();
//        ui->pushButton_20->show();
//        ui->lineEdit_8->setEnabled(true);
//        ui->lineEdit_9->setEnabled(true);
//        ui->lineEdit_10->setEnabled(true);
//        ui->lineEdit_11->setEnabled(true);
//        ui->lineEdit_12->setEnabled(true);
//        ui->lineEdit_13->setEnabled(true);
//        ui->lineEdit_14->setEnabled(true);
//        oldStackInfo.stackname = ui->lineEdit_8->text();
//        oldStackInfo.stackip = ui->lineEdit_9->text();
//    });
//    connect(ui->pushButton_19,&QPushButton::clicked,this,[=](){
//        QSqlQuery query(db);
//        QString qs = QString("update stackinfo set stackname ='%1',stackip ='%2' where stackname ='%3'")
//                .arg(ui->lineEdit_8->text()).arg(ui->lineEdit_9->text()).arg(oldStackInfo.stackname);

//        bool updateok = query.exec(qs);
//        if(updateok){
//            QMessageBox::information(this,"提示信息","更新成功");
//        }
//        ui->pushButton_21->setText(stacknames.at(0));
//        ui->pushButton_22->setText(stacknames.at(1));

//        ui->pushButton_17->show();
//        ui->pushButton_19->hide();
//        ui->pushButton_20->hide();
//        ui->lineEdit_8->setEnabled(false);
//        ui->lineEdit_9->setEnabled(false);
//        ui->lineEdit_10->setEnabled(false);
//        ui->lineEdit_11->setEnabled(false);
//        ui->lineEdit_12->setEnabled(false);
//        ui->lineEdit_13->setEnabled(false);
//        ui->lineEdit_14->setEnabled(false);
//    });connect(ui->pushButton_20,&QPushButton::clicked,this,[=](){
//        ui->lineEdit_8->setText(oldStackInfo.stackname);
//        ui->lineEdit_9->setText(oldStackInfo.stackip);

//        ui->pushButton_17->show();
//        ui->pushButton_19->hide();
//        ui->pushButton_20->hide();
//        ui->lineEdit_8->setEnabled(false);
//        ui->lineEdit_9->setEnabled(false);
//        ui->lineEdit_10->setEnabled(false);
//        ui->lineEdit_11->setEnabled(false);
//        ui->lineEdit_12->setEnabled(false);
//        ui->lineEdit_13->setEnabled(false);
//        ui->lineEdit_14->setEnabled(false);
//    });
//}

void FirstWindow::initialtcp()
{
    tcpServer = new QTcpServer(this);
    bool tcpListenOk = tcpServer->listen(QHostAddress::Any,9052);
    if(!tcpListenOk){
        QMessageBox::information(this,"绑定信息","9052端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出等待链接的下一个socket
        qDebug() << "tcp连接请求";

        QTcpSocket *tcpSocket1;
        tcpSocket1 = tcpServer->nextPendingConnection();


        QHostAddress ip = tcpSocket1->peerAddress();
        quint16 port = tcpSocket1->peerPort();


        QString filename;
        quint64 filesize;
        int num;
        QString code;
        for(int i=0;i<mutiFile.size();i++){
            if(mutiFile.at(i)->stationIp == QHostAddress(ip.toIPv4Address()).toString()){
                qDebug() << mutiFile.at(i)->stationIp << QHostAddress(ip.toIPv4Address()).toString();
                filename = mutiFile.at(i)->filePath;
                filesize = mutiFile.at(i)->fileSize;
                code = mutiFile.at(i)->code;
                num = i;
            }
        }

        qInfo("用户: %s\t\t 基站%s开始传输%s", currentUser.toUtf8().constData(),mutiFile.at(num)->stationName.toUtf8().constData(),filename.toUtf8().constData());
        mutiFile.at(num)->socket = tcpSocket1;

        mutiFile.at(num)->t = new QThread;
        mutiFile.at(num)->worker = new WriteFiledata;
        mutiFile.at(num)->worker->moveToThread(mutiFile.at(num)->t);
        mutiFile.at(num)->worker->setFile(filename);
        mutiFile.at(num)->worker->setFileSize(filesize);
        mutiFile.at(num)->worker->setNum(num);
        mutiFile.at(num)->worker->setCode(code);
        mutiFile.at(num)->t->start();
        connect(this,&FirstWindow::sendWriteFile,mutiFile.at(num)->worker,&WriteFiledata::writeFile);
        connect(mutiFile.at(num)->worker,&WriteFiledata::sentValue,pro,&progress::setFileValue);
        connect(mutiFile.at(num)->worker,&WriteFiledata::finishWrite,this,&FirstWindow::getFinish);
        connect(mutiFile.at(num)->worker,&WriteFiledata::finishWrite,[=](){
            qDebug() << "销毁";
            mutiFile.at(num)->t->quit();
            mutiFile.at(num)->t->wait();
            mutiFile.at(num)->t->deleteLater();

            tcpSocket1->disconnectFromHost();

            // 使用deleteLater()函数来销毁socket对象
            tcpSocket1->deleteLater();
        });



        connect(tcpSocket1,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcpSocket1->readAll();
//            qDebug() << "节点" << tcpSocket1->peerAddress() << "数据" << array.at(0);
            QString getIp = QHostAddress(tcpSocket1->peerAddress().toIPv4Address()).toString();
            int numb;
            for(int i=0;i<mutiFile.size();i++){
                if(mutiFile.at(i)->stationIp==getIp) numb=i;
            }
            emit sendWriteFile(array,numb);
        });

    });

    grilleTcpserver = new QTcpServer(this);
    bool grilletcpListenOk = grilleTcpserver->listen(QHostAddress::Any,ConfigInfo::grilleTcpPort.toInt());
    if(!grilletcpListenOk){
        QMessageBox::information(this,"绑定信息",ConfigInfo::grilleTcpPort+"端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }else{
        qDebug() << ConfigInfo::grilleTcpPort+"tcp绑定成功";
        qDebug() << ConfigInfo::grilleTcpPort;
    }

    grilleWorker = new WriteFileWorker;
    grilleWorker->fileDirectoryPath = ConfigInfo::geShanMulu;
    grilleWorker->type = AgreeMent::GRILLE;
    grilleThread = new QThread;
    grilleWorker->moveToThread(grilleThread);
    connect(grilleWorker,&WriteFileWorker::setPorgress,this,&FirstWindow::getGrilleProgress);
    connect(this,&FirstWindow::sendGrilleFileData,grilleWorker,&WriteFileWorker::writeFileData);
    connect(grilleWorker,&WriteFileWorker::okReceieve,fileDownload1,&RemoteDataSingleWidget::okReceieve);
    connect(grilleWorker,&WriteFileWorker::okReceieve,[=](){
        tcpSocket33->disconnect();
    });
    connect(grilleWorker,&WriteFileWorker::falseReceieve,[=](){
        tcpSocket33->disconnect();
    });
    connect(grilleWorker,&WriteFileWorker::falseReceieve,fileDownload1,&RemoteDataSingleWidget::falseReceieve);
    grilleThread->start();

    connect(grilleTcpserver,&QTcpServer::newConnection,[=](){
        //取出等待链接的下一个socket
        qDebug() << "tcp连接请求";

        tcpSocket33 = grilleTcpserver->nextPendingConnection();
        connect(tcpSocket33,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcpSocket33->readAll();
            emit sendGrilleFileData(array);
        });
        connect(tcpSocket33,&QTcpSocket::disconnected,[=](){
            if(fileDownload1->nowsize!=0){
                QMessageBox::information(this,"下载提示","下载断开");
                fileDownload1->setButtonEnabled();
                tcpSocket33->disconnect();
                tcpSocket33->deleteLater();
            }
        });
    });

    displayTcpserver = new QTcpServer(this);
    bool displaytcpListenOk = displayTcpserver->listen(QHostAddress::Any,ConfigInfo::displayTcpPort.toInt());
    if(!displaytcpListenOk){
        QMessageBox::information(this,"绑定信息",ConfigInfo::displayTcpPort+"端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }

    displayWorker = new WriteFileWorker;
    displayWorker->fileDirectoryPath = ConfigInfo::displayMulu;
    displayWorker->type = AgreeMent::DISPLAY;
    displayThread = new QThread;
    displayWorker->moveToThread(displayThread);
    connect(displayWorker,&WriteFileWorker::setPorgress,this,&FirstWindow::getDisplayProgress);
    connect(this,&FirstWindow::sendDisplayFileData,displayWorker,&WriteFileWorker::writeFileData);
    displayThread->start();

    connect(displayTcpserver,&QTcpServer::newConnection,[=](){
        //取出等待链接的下一个socket
        qDebug() << "tcp连接请求";

        QTcpSocket *tcpSocket1;
        tcpSocket1 = displayTcpserver->nextPendingConnection();
        connect(tcpSocket1,&QTcpSocket::readyRead,[=](){
            tt++;
            qDebug() << "接收的包个数" << tt;
            QByteArray array = tcpSocket1->readAll();
            emit sendDisplayFileData(array);
        });
    });

}

void FirstWindow::connecttcprec(QTcpSocket *tcpSocket){
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        QByteArray arrjudge = tcpSocket->readAll();


        QHostAddress addr;
        quint16 port;
    //    arrjudge.resize(4);
        QByteArray arrCurrent;
        quint32 point = 0;

        qDebug() << "haspend";
        point = 0;
        quint64 socketava = arrjudge.size();
        qDebug() << "socketava"<< socketava;
        quint64 pend = arrjudge.size();

        qDebug() << "pend ava " << pend << socketava;

        arrjudge.resize(pend);
        addr = tcpSocket->peerAddress();
        port = tcpSocket->peerPort();


        arrjudge = getInvert(arrjudge);
        emit sendSocketData(pend,arrjudge,addr,port);

/*
        while(point !=pend){
            qDebug() << pend << point;
            qDebug() << "内部循环";
            qDebug() << quint8(arrjudge.at(0));
            qDebug() << quint8(arrjudge.at(1));


            if(quint8(arrjudge.at(0))==0x5A && quint8(arrjudge.at(1))==0x5A){
                qDebug() << "成立";
                QDataStream stre(&arrjudge,QIODevice::ReadOnly);
                stre.setVersion(QDataStream::Qt_5_1);
                stre.device()->seek(2);
                quint32 length;
                stre >> length;
                arrCurrent.resize(length+2);
                arrCurrent = arrjudge.mid(0,length+2);
                qDebug() << "tet";

                arrjudge = arrjudge.mid(length+2,arrjudge.length()-length-2);
                arrjudge.resize(arrjudge.length()-length-2);
                point +=length+2;
                qDebug() << "tet";

                qDebug() << arrCurrent.size();
                quint8 mesmark = quint8(arrCurrent.at(6));
                qDebug() << "tet";

                User user;
                File filestr;
                MissionResult result;
                switch (mesmark) {
                case 0x09:
                     user = analysis09(arrCurrent);
                     judgeUser(user);

//                    analysis09(arrCurrent);
                    break;
                case 0x07:
                    filestr =  analysis07(arrCurrent);
                    qDebug() << "filename"<<filestr.fileName<< "fileframe"<<filestr.frame;
                    writeFile(filestr);
                    qDebug() << "写文件完成";
                    break;
                case 0x04:
                    result = analysis04(arrCurrent);

                }

            }
        }*/



    });
}



void FirstWindow::on_pushButton_5_clicked()
{
//    if(ui->lineEdit->text()=="")
//    {
//        qDebug() << "post3";
//        post3();
//    }else{
//        post4(ui->lineEdit->text());
//        qDebug() << "post4";
//    }


    QString input_name=ui->lineEdit->text();
        int row_num=ui->tableWidget_4->rowCount();
        if (input_name=="")//判断是否是空，如果是空就显示所有行
        {

            QSqlQuery query(db);
                    if(query.exec("select name,islock,realname,phonenumber from user"))
                    {
                       ui->tableWidget_4->clearContents();
                       ui->tableWidget_4->setRowCount(0);

                       //ui->tableWidget_4->item(i, 4)->setFlags((ItemFlags)63);

                        while(query.next())
                        {
                            int rowCount = ui->tableWidget_4->rowCount();


                            ui->tableWidget_4->insertRow(rowCount);

                            QTableWidgetItem *columnItem1 = new QTableWidgetItem(QString("未锁定"));
                            QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                        query.value(0).toString());

                            if(query.value(1).toInt()==0){
                                columnItem1 = new QTableWidgetItem(QString("未锁定"));
                            }else{
                                columnItem1 = new QTableWidgetItem(QString("锁定"));
                            }

                            QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                        query.value(2).toString());

                            QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                        query.value(3).toString());


                            ui->tableWidget_4->setItem(rowCount,0, columnItem0);
                            ui->tableWidget_4->setItem(rowCount,1, columnItem1);
                            ui->tableWidget_4->setItem(rowCount,2, columnItem2);
                            ui->tableWidget_4->setItem(rowCount,3, columnItem3);

                        }



                        for(int i=0;i<ui->tableWidget_4->rowCount();i++)
                        {
                            for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                            {
                                o = ui->tableWidget_4->item(i,j);
                                o->setFlags(Qt::ItemIsEnabled);
                            }
                        }
                    }
        }
        else
        {
            QList <QTableWidgetItem *> item = ui->tableWidget_4->findItems(input_name, Qt::MatchContains);
            for(int i=0;i<row_num;i++)
            {
                ui->tableWidget_4->setRowHidden(i,true);//隐藏

            }
            //判断符合条件索引是不是空
            if(!item.empty())
            {
                for(int i=0;i<item.count();i++)
                {
                    ui->tableWidget_4->setRowHidden(item.at(i)->row(),false);

                }
            }
        }
}

void FirstWindow::post3(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/orm/users/select"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray token =  response.toLocal8Bit();
    request.setRawHeader("token",token);
    qDebug() <<token;
    QJsonObject json;
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    manager3->post(request,dataArray);
}

void FirstWindow::post4(QString param){
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/orm/user/select"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray token =  response.toLocal8Bit();
    request.setRawHeader("token",token);
    qDebug() <<token;
    QJsonObject json;
    json.insert("name", param);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    manager4->post(request,dataArray);
}

void FirstWindow::postback3(QNetworkReply *reply){
    QByteArray arr = reply->readAll();


    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QString content = utf8->toUnicode(arr);

    qDebug() << "content4asdasda:"<<content;
    QJsonParseError jError;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &jError);

    if(jError.error != QJsonParseError::NoError){
        qDebug() << "parse json wrong";
        qDebug() << jError.error;
    }else
    {
        QJsonArray jObj = jDoc.array();
        int size = jObj.size();
        qDebug() << "size:" << size;
        qDebug() << jObj;
        QFont font;
        font.setPointSize(19);
        for(int i=0;i<size;i++)
        {
            QJsonObject a1 = jObj.at(i).toObject();
            QString name = a1["name"].toString();
            QTableWidgetItem *item = new QTableWidgetItem(name);
            item->setFont(font);
            ui->tableWidget_4->setItem(i,0,item);

            QString realname = a1["realname"].toString();
            QTableWidgetItem *item2 = new QTableWidgetItem(realname);
            item2->setFont(font);
            ui->tableWidget_4->setItem(i,1,item2);

            QString role = a1["role"].toString();
            QTableWidgetItem *item3 = new QTableWidgetItem(role);
            item3->setFont(font);
            ui->tableWidget_4->setItem(i,2,item3);

            QString createtime = a1["createtime"].toString();
            QTableWidgetItem *item4 = new QTableWidgetItem(createtime);
            item4->setFont(font);
            ui->tableWidget_4->setItem(i,3,item4);

            QString logintime = a1["logintime"].toString();
            QTableWidgetItem *item5 = new QTableWidgetItem(logintime);
            item5->setFont(font);
            ui->tableWidget_4->setItem(i,4,item5);

            QString modifytime = a1["modifytime"].toString();
            QTableWidgetItem *item6 = new QTableWidgetItem(modifytime);
            item6->setFont(font);
            ui->tableWidget_4->setItem(i,5,item6);
        }






    }
}

void FirstWindow::postback4(QNetworkReply *reply){
    QByteArray arr = reply->readAll();


    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QString content = utf8->toUnicode(arr);

    qDebug() << "content4:"<<content;
    QJsonParseError jError;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &jError);

    if(jError.error != QJsonParseError::NoError){
        qDebug() << "parse json wrong";
        qDebug() << jError.error;
    }else
    {
        QJsonObject jObj = jDoc.object();
        QString name = jObj["name"].toString();
        QString realname = jObj["realname"].toString();
        QString role = jObj["role"].toString();
        QString createtime = jObj["createtime"].toString();
        QString logintime = jObj["logintime"].toString();
        QString modifytime = jObj["modifytime"].toString();

        for(int i=0;i<6;i++)
        {
            ui->tableWidget_4->removeRow(i);
        }
\
        QFont font;
        font.setPointSize(19);

        QTableWidgetItem *item = new QTableWidgetItem(name);
        item->setFont(font);
        ui->tableWidget_4->setItem(0,0,item);

        QTableWidgetItem *item2 = new QTableWidgetItem(realname);
        item2->setFont(font);
        ui->tableWidget_4->setItem(0,1,item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(role);
        item3->setFont(font);
        ui->tableWidget_4->setItem(0,2,item3);
        QTableWidgetItem *item4 = new QTableWidgetItem(createtime);
        item4->setFont(font);
        ui->tableWidget_4->setItem(0,3,item4);
        QTableWidgetItem *item5 = new QTableWidgetItem(logintime);
        item5->setFont(font);
        ui->tableWidget_4->setItem(0,4,item5);
        QTableWidgetItem *item6 = new QTableWidgetItem(modifytime);
        item6->setFont(font);
        ui->tableWidget_4->setItem(0,5,item6);

    }
}

//void FirstWindow::on_pushButton_15_clicked()
//{
//    QList<QString> list;
//    QList<QString> list2;
//    list2 << "参数1" << "参数2" << "参数3" << "参数4" << "参数5" ;
//    list << ui->lineEdit_3->text() << ui->lineEdit_4->text() << ui->lineEdit_5->text() << ui->lineEdit_6->text() << ui->lineEdit_7->text() ;
//    QString fileName = QFileDialog::getSaveFileName(this,tr("Excle file"),QString("./parameter/test.xlsx"),tr("Excel Files(*.xlsx)"));    //设置保存的文件名
//    qDebug() << "查看文件名" << fileName;
//        if(fileName != NULL)
//        {
//            QAxObject *excel = new QAxObject;
//            if(excel->setControl("Excel.Application"))
//            {
//                excel->dynamicCall("SetVisible (bool Visible)",false);
//                excel->setProperty("DisplayAlerts",false);
//                QAxObject *workbooks = excel->querySubObject("WorkBooks");
//                workbooks->dynamicCall("Add");
//                QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
//                QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
//                QAxObject *cell;
//                int rowCount = 1;
//                int columnCount = 5;
//                for(int i = 1; i <= columnCount ; i++)
//                {
//                    cell = worksheet->querySubObject("Cells(int,int)", 1, i);
//                    cell->setProperty("RowHeight", 40);
//                    cell->dynamicCall("SetValue(const QString&)", list2.at(i-1));
//                }
//                for(int j = 2; j <= rowCount + 1;j++)
//                {
//                    for(int k = 1;k <= 5;k++)
//                    {

//                        cell = worksheet->querySubObject("Cells(int,int)", j, k);
//                        cell->dynamicCall("SetValue(const QString&)",list.at(k-1));

//                        int value = 8;
//                        if(value > 20000)
//                        {
//                            QAxObject*interior = cell->querySubObject("Interior");
//                            interior->setProperty("Color", QColor(Qt::red));
//                        }
//                    }
//                }

//                workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));
//                workbook->dynamicCall("Close()");
//                excel->dynamicCall("Quit()");
//                delete excel;
//                excel = NULL;
//            }
//        }
//        QMessageBox::information(this,"保存提示","保存成功");
//        ui->lineEdit_3->setText("");
//        ui->lineEdit_4->setText("");
//        ui->lineEdit_5->setText("");
//        ui->lineEdit_6->setText("");
//        ui->lineEdit_7->setText("");
//}

//void FirstWindow::on_pushButton_13_clicked()
//{
//    QString fileName = QFileDialog::getSaveFileName(ui->tableWidget, "保存",                                           QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Excel 文件(*.xls *.xlsx)");
//        if(fileName != "")
//        {
//            QString title = "title";
//            QAxObject *excel = new QAxObject;
//            if(excel->setControl("Excel.Application")) //连接Excel控件
//            {
//                excel->dynamicCall("SetVisible (bool Visible)","false"); //不显示当前窗体
//                excel->setProperty("DisplayAlerts", false); //不显示任何警告消息，如果为true那么在关闭是会出现类似"文件已修改，是否保存"的提示
//                QAxObject *workBooks = excel->querySubObject("WorkBooks");//获取工作簿集合
//                workBooks->dynamicCall("Add"); //新建一个工作簿
//                QAxObject *workBook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
//                QAxObject *workSheet = workBook->querySubObject("Worksheets(int)", 1); //获取第一个工作表（后面的参数代表的是第几张工作表）

//                int colCount = ui->tableWidget->columnCount();
//                int rowCount = ui->tableWidget->rowCount();

//                QAxObject *cell, *col;

//                //标题行
//                cell = workSheet->querySubObject("Cells(int, int)", 1, 1);
//                cell->dynamicCall("SetValue(const QString&)", title);
//                cell->querySubObject("Font")->setProperty("Size", 18);
//                //调整行高
//                workSheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
//                //合并标题行
//                QString cellTitle;
//                cellTitle.append("A1:");
//                cellTitle.append(QChar(colCount - 1 + 'A'));
//                cellTitle.append(QString::number(1));
//                QAxObject *range = workSheet->querySubObject("Range(const QString&)", cellTitle);
//                range->setProperty("WrapText", true);
//                range->setProperty("MergeCells", true);
//                range->setProperty("HorizontalAlignment", -4108);
//                range->setProperty("VertivcalAlignment", -4108);

//                //列标题
//                for (int i = 0; i < colCount; i++)
//                {
//                    QString columnName;
//                    columnName.append(QChar(i + 'A'));
//                    columnName.append(":");
//                    columnName.append(QChar(i + 'A'));
//                    col = workSheet->querySubObject("Columns(const QString&)", columnName);
//                    col->setProperty("ColumnWidth", ui->tableWidget->columnWidth(i)/6);
//                    cell = workSheet->querySubObject("Cells(int, int)", 2, i+1);
//                    columnName = ui->tableWidget->horizontalHeaderItem(i)->text();
//                    cell->dynamicCall("SetValue(const QString&)", columnName);
//                    cell->querySubObject("Font")->setProperty("Bold", true);
//                    cell->querySubObject("Interior")->setProperty("Color", QColor(191, 191, 191));
//                    cell->setProperty("HorizontalAlignment", -4108);
//                    cell->setProperty("VertivcalAlignment", -4108);
//                }

//                //处理数据
//                for (int i = 0; i < rowCount; i++)
//                {
//                    for (int j = 0; j < colCount; j++)
//                    {
//                        workSheet->querySubObject("Cells(int, int)", i + 3, j + 1)->dynamicCall(
//                                    "SetValue(const QString&)", ui->tableWidget->item(i, j)? ui->tableWidget->item(i, j)->text():"");
//                    }
//                }

//                //画框线
//                QString l_range;
//                l_range.append("A2:");
//                l_range.append(colCount -1 + 'A');
//                l_range.append(QString::number(ui->tableWidget->rowCount() + 2));
//                range = workSheet->querySubObject("Range(const QString&)", l_range);
//                range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
//                range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

//                //调整数据区行高
//                QString rowsName;
//                rowsName.append("2:");
//                rowsName.append(QString::number(ui->tableWidget->rowCount() + 2));
//                range = workSheet->querySubObject("Range(const QString&)", rowsName);
//                range->setProperty("RowHeight", 20);
//                workBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName)); //保存到fileName

//                workBook->dynamicCall("Close()"); //关闭工作簿
//                excel->dynamicCall("Quit()"); //关闭excel
//                delete  excel;
//                excel = NULL;
//                if ((QMessageBox::question(NULL, tr("完成"), tr("文件已导出，是否现在打开？")), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
//                {
//                    QDesktopServices().openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
//                }
//            }
//            else
//            {
//                QMessageBox::warning(NULL, tr("错误"), tr("未能创建 Excel 对象，请安装 Microsoft Excel。"), QMessageBox::Apply);
//            }
//    }
//}




void FirstWindow::testSlot(int x,int y)
{
    qDebug() << "x:" << x <<"y:" <<y;


    filedata *p = new filedata;
    p->show();
    connect(this,SIGNAL(SendData(int,int)),p,SLOT(GetData(int,int)));
    emit SendData(x,y);
}

//void FirstWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
//{
//    QMenu menu;
//    QAction *selectAll = menu.addAction(tr("全选"));
//    menu.addSeparator();
//    QAction *clear = menu.addAction(tr("清空内容"));
//    menu.addSeparator();
//    QAction *init = menu.addAction(tr("初始化表格"));

//    connect(selectAll, &QAction::triggered, [=](){
//        qDebug() << "select all";
//    });

//    connect(clear, &QAction::triggered, [=](){
//        qDebug() << "clear";
//    });



//    menu.exec(QCursor::pos());
//}



//void FirstWindow::on_pushButton_clicked()
//{
//    insertWindow *configWindow = new insertWindow;
//    connect(configWindow,&insertWindow::sendNewStr,this,&FirstWindow::getNewStr);
//    configWindow->show();
//}

void FirstWindow::printUserInfo(){
    QSqlQuery query(db);
            if(query.exec("select name,islock,realname,phonenumber from user"))
            {
               ui->tableWidget_4->clearContents();
               ui->tableWidget_4->setRowCount(0);

               //ui->tableWidget_4->item(i, 4)->setFlags((ItemFlags)63);

                while(query.next())
                {
                    int rowCount = ui->tableWidget_4->rowCount();


                    ui->tableWidget_4->insertRow(rowCount);
                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(QString("未锁定"));

                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                query.value(0).toString());

                    if(query.value(1).toInt()==0){
                        columnItem1 = new QTableWidgetItem(QString("未锁定"));
                    }else{
                        columnItem1 = new QTableWidgetItem(QString("锁定"));
                    }

                    QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                query.value(2).toString());

                    QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                query.value(3).toString());


                    ui->tableWidget_4->setItem(rowCount,0, columnItem0);
                    ui->tableWidget_4->setItem(rowCount,1, columnItem1);
                    ui->tableWidget_4->setItem(rowCount,2, columnItem2);
                    ui->tableWidget_4->setItem(rowCount,3, columnItem3);

                }
            }

            ui->tableWidget_4->setEditTriggers(QAbstractItemView::CurrentChanged);


            for(int i=0;i<ui->tableWidget_4->rowCount();i++){
                for(int j=0;j<ui->tableWidget_4->columnCount();j++){

                    o = ui->tableWidget_4->item(i,j);
                    o->setFlags(Qt::ItemIsEnabled);
                }
            }
}



void FirstWindow::cellClickedSlot(int x, int y)
{
    if(rowEdit!=x && isedit == 1)
        {
            QString newname = ui->tableWidget_4->item(rowEdit,0)->text();
            QString newrealname = ui->tableWidget_4->item(rowEdit,2)->text();
            QString newnumber = ui->tableWidget_4->item(rowEdit,3)->text();
    //        QString newrole = editor->currentText();
            QString newislockstr = editor2->currentText();
            int newislock;
            if(!QString::compare(newislockstr,QString("未锁定"))){
                newislock = 0;
            }else{
                newislock = 1;
            }

            QSqlQuery query(db);
            QString qs = QString("update user set name ='%1',islock ='%2',realname ='%3',phonenumber ='%4' where name ='%5'").arg(newname).arg(newislock).arg(newrealname).arg(newnumber).arg(oldname);

            if(query.exec(qs))
            {
                QMessageBox::information(this,"提醒","修改成功！",QMessageBox::Ok);

                for(int i=0;i<ui->tableWidget_4->rowCount();i++)
                {
                    for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                    {
                        o = ui->tableWidget_4->item(i,j);
                        o->setFlags(Qt::ItemIsEnabled);
                    }
                }
                qDebug() << "1";
            }
            else
            {
                QMessageBox::information(this,"警告","用户名重复，修改失败！",QMessageBox::Ok);
                QTableWidgetItem *item1 = new QTableWidgetItem(oldname);
                ui->tableWidget_4->setItem(rowEdit,0,item1);

                for(int i=0;i<ui->tableWidget_4->rowCount();i++)
                {
                    for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                    {
                        o = ui->tableWidget_4->item(i,j);
                        o->setFlags(Qt::ItemIsEnabled);
                    }
                }
                qDebug() << "0";
            }

                    if(query.exec("select name,islock,realname,phonenumber from user"))
                    {
                       ui->tableWidget_4->clearContents();
                       ui->tableWidget_4->setRowCount(0);

                       //ui->tableWidget_4->item(i, 4)->setFlags((ItemFlags)63);

                        while(query.next())
                        {
                            int rowCount = ui->tableWidget_4->rowCount();


                            ui->tableWidget_4->insertRow(rowCount);
                            QTableWidgetItem *columnItem1 = new QTableWidgetItem(QString("未锁定"));

                            QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                        query.value(0).toString());

                            if(query.value(1).toInt()==0){
                                columnItem1 = new QTableWidgetItem(QString("未锁定"));
                            }else{
                                columnItem1 = new QTableWidgetItem(QString("锁定"));
                            }

                            QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                        query.value(2).toString());

                            QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                        query.value(3).toString());


                            ui->tableWidget_4->setItem(rowCount,0, columnItem0);
                            ui->tableWidget_4->setItem(rowCount,1, columnItem1);
                            ui->tableWidget_4->setItem(rowCount,2, columnItem2);
                            ui->tableWidget_4->setItem(rowCount,3, columnItem3);

                        }
                    }


                                for(int i=0;i<ui->tableWidget_4->rowCount();i++)
                                {
                                    for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                                    {
                                        o = ui->tableWidget_4->item(i,j);
                                        o->setFlags(Qt::ItemIsEnabled);
                                    }
                                }
                            }
    isedit = 0;
}




void FirstWindow::on_tableWidget_4_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *change = menu.addAction(tr("编辑"));
    menu.addSeparator();
    QAction *deleteUser = menu.addAction(tr("删除"));
    connect(change, &QAction::triggered, [=]()
    {


        isedit = 1;
        qDebug() << "change";
        int row = ui->tableWidget_4->currentRow();
        rowEdit = row;
        qDebug() << row;
//        ui->tableWidget_4->setEditTriggers(QAbstractItemView::CurrentChanged);
        for(int i=0;i<ui->tableWidget_4->rowCount();i++){
            for(int j=0;j<ui->tableWidget_4->columnCount();j++){
                o = ui->tableWidget_4->item(i,j);
                o->setFlags(Qt::ItemIsEditable|o->flags());//可编辑
            }
        }
        for(int i=0;i<ui->tableWidget_4->rowCount();i++){
            for(int j=0;j<ui->tableWidget_4->columnCount();j++){
                if(i!=row){
                    o = ui->tableWidget_4->item(i,j);
  //                o->setFlags(Qt::ItemIsEnabled|o->flags());
                    o->setFlags(Qt::ItemIsEnabled);
                    qDebug() << i << j;
                }

            }
        }

        oldname = ui->tableWidget_4->item(row,0)->text();//oldname


        editor2 = new QComboBox;
        QStringList strList1;
        strList1<<"未锁定"<<"锁定";
        editor2->addItems(strList1);
        ui->tableWidget_4->setCellWidget(row,1,editor2);

        connect(ui->tableWidget_4,SIGNAL(cellClicked(int,int)),this,SLOT(cellClickedSlot(int ,int )));
        //获取原先的数据
        //获取qtablewidget的单击信号
        //如果信号不在所编辑的那一行，获取新的内容，校验所编辑的姓名是否合法
        //如果合法，更新数据库内容
        //反之恢复数据到原始状态，并重新设置所有为不可编辑状态

    });



    connect(deleteUser, &QAction::triggered, [=]()
    {
        int row = ui->tableWidget_4->currentRow();
        QString oldname1 = ui->tableWidget_4->item(row,0)->text();
        QSqlQuery query(db);
        QString qs = QString("delete from user where name ='%1'").arg(oldname1);
        qDebug() << oldname1;
        if(query.exec(qs))
        {
            qDebug() << "删除1";


                    if(query.exec("select name,islock,realname,phonenumber from user"))
                    {
                       ui->tableWidget_4->clearContents();
                       ui->tableWidget_4->setRowCount(0);

                       //ui->tableWidget_4->item(i, 4)->setFlags((ItemFlags)63);

                        while(query.next())
                        {
                            int rowCount = ui->tableWidget_4->rowCount();


                            ui->tableWidget_4->insertRow(rowCount);
                            QTableWidgetItem *columnItem1 = new QTableWidgetItem(QString("未锁定"));

                            QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                        query.value(0).toString());

                            if(query.value(1).toInt()==0){
                                columnItem1 = new QTableWidgetItem(QString("未锁定"));
                            }else{
                                columnItem1 = new QTableWidgetItem(QString("锁定"));
                            }

                            QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                        query.value(2).toString());

                            QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                        query.value(3).toString());


                            ui->tableWidget_4->setItem(rowCount,0, columnItem0);
                            ui->tableWidget_4->setItem(rowCount,1, columnItem1);
                            ui->tableWidget_4->setItem(rowCount,2, columnItem2);
                            ui->tableWidget_4->setItem(rowCount,3, columnItem3);

                        }
                    }

                for(int i=0;i<ui->tableWidget_4->rowCount();i++)
                {
                    for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                    {
                        o = ui->tableWidget_4->item(i,j);
                        o->setFlags(Qt::ItemIsEnabled);
                    }
                }

                QMessageBox::information(this,"提醒","删除成功！",QMessageBox::Ok);

        }
        else
        {
            qDebug() << "删除0";
            for(int i=0;i<ui->tableWidget_4->rowCount();i++)
            {
                for(int j=0;j<ui->tableWidget_4->columnCount();j++)
                {
                    o = ui->tableWidget_4->item(i,j);
                    o->setFlags(Qt::ItemIsEnabled);
                }
            }
            QMessageBox::information(this,"警告","删除失败！",QMessageBox::Ok);
        }

        qDebug() << "delete";

    });


    menu.exec(QCursor::pos());
}

void FirstWindow::mousePressEvent(QMouseEvent *event){
    qDebug() << "right";
}


QByteArray FirstWindow::getInvert(QByteArray array)
{
    unsigned char k = 0x80;
    QByteArray invertArray;
    quint8 tempCharAsc = 0;
    char tempChar;
    invertArray.resize(array.size());
    for(int i=0;i<array.size();i++){
        for(int j=0;j<8;j++){
            if(quint8(array.at(i)) & k){
            }else{
                tempCharAsc += pow(2,7-j);
            }
            k >>=1;
        }
        tempChar = tempCharAsc;
        invertArray[i] = tempChar;
        tempChar = 0;
        tempCharAsc = 0;
        k = 0x80;
    }
    return invertArray;
}

quint8 FirstWindow::calChecksum(QByteArray array){
    quint8 result = 0;
    for(int i=3;i<array.size()-1;i++){
        result += array.at(i);
    }
    return result & 0xFF;
}

QByteArray FirstWindow::s07(File file){
    QByteArray array;
    array.resize(188);
    array[0] = 0x5A;
    array[1] = 0x5A;
    array[2] = 0x00;
    array[3] = 0x07;
    array[4] = file.fileName.length();
    for(int i=0;i<file.fileName.length();i++){
        array[i+5] = quint8(file.fileName.at(i).toLatin1());
    }
    array[25] = (file.fileSize>>24)&0xFF;
    array[26] = (file.fileSize>>16)&0xFF;
    array[27] = (file.fileSize>>8)&0xFF;
    array[28] = (file.fileSize)&0xFF;

    array[29] = (file.fileBlockLength>>24)&0xFF;
    array[30] = (file.fileBlockLength>>16)&0xFF;
    array[31] = (file.fileBlockLength>>8)&0xFF;
    array[32] = (file.fileBlockLength)&0xFF;



    array[33] = (file.beginPosition>>24)&0xFF;
    array[34] = (file.beginPosition>>16)&0xFF;
    array[35] = (file.beginPosition>>8)&0xFF;
    array[36] = (file.beginPosition)&0xFF;

    array.resize(37);
    array.append(filestr.fileBlockData);
    array.resize(188);
//    for(int i=37;i<187;i++){
//        array[i] = filestr.fileBlockData.at(i-37);
//    }

    array[187] = file.frame;
    return array;
}

QByteArray FirstWindow::s09(User user){
    QByteArray sendByte;
    UserLoginSend userLoginSend;
    qDebug() << "datalength +2" <<userLoginSend.dataLength+2;
    sendByte.resize(userLoginSend.dataLength+2);
    sendByte[0] = 0x5A;
    sendByte[1] = 0x5A;
    sendByte[2] = userLoginSend.dataLength;
    sendByte[3] = userLoginSend.mesMark;
    sendByte[4] = user.name.length();
    for(int i=0;i<user.name.length();i++){
        sendByte[i+5] = quint8(user.name.at(i).toLatin1());
    }
    sendByte[25] = user.password.length();
    for(int j=0;j<user.password.length();j++){
        sendByte[j+26] = quint8(user.password.at(j).toLatin1());
    }
    sendByte.append(user.password);
    sendByte[46] = user.frame;
    sendByte[47] = calChecksum(sendByte);

    sendByte.resize(userLoginSend.dataLength+2);
    return sendByte;
}

QByteArray FirstWindow::s10(LoginResult loginResult){
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(0x07) << quint8(0x10)
            << quint8(loginResult.loginStatus) << quint8(loginResult.frame);


    return sendByte;
}

QByteArray FirstWindow::s01(quint8 frame){
    QByteArray sendByte;
    sendByte[0] = 0x5A;
    sendByte[1] = 0x5A;
    sendByte[2] = 0x04;
    sendByte[3] = 0x01;
    sendByte[4] = frame;

    return sendByte;
}

QByteArray FirstWindow::s02(SelfDetect selfDetect){
    QByteArray sendByte;
    sendByte[0] = 0x5A;
    sendByte[1] = 0x5A;
    sendByte[2] = 0x05;
    sendByte[3] = 0x02;
    sendByte[4] = selfDetect.resultMes;
    sendByte[5] = selfDetect.frame;

    return sendByte;
}

QByteArray FirstWindow::s05(quint8 frame){
    QByteArray sendByte;
    sendByte[0] = 0x5A;
    sendByte[1] = 0x5A;
    sendByte[2] = 0x03;
    sendByte[3] = 0x05;
    sendByte[4] = frame;

    return sendByte;
}

QByteArray FirstWindow::s06(healthInfo info){
    QByteArray sendByte;
    sendByte[0] = 0x5A;
    sendByte[1] = 0x5A;
    sendByte[2] = 0x05;
    sendByte[3] = 0x06;
    sendByte[4] = info.stationNode;
    sendByte[5] = info.frame;

    return sendByte;
}







FirstWindow::File FirstWindow::analysis07(QByteArray array){
    File fileRet;
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QString code;

    strea >> head1 >> head2 >> noneLength >> dataStyle >> code;
    fileRet.node = code;
    qDebug() << "code:" << code;
//    QByteArray ara;
    char *po = fileRet.fileBlockData;
    strea >> fileRet.fileName;

    qDebug() << "第一千位：" << array.at(1000);
    strea >> fileRet.fileSize >> fileRet.fileBlockLength >> fileRet.beginPosition;
//    strea >> po;
    strea.readRawData(po,4096);
//    strea.readRawData(fileRet.fileBlockData,4096);
    qDebug() << "测试";
    qDebug() << head1<<head2;
    qDebug() << noneLength;
    qDebug() << dataStyle;
    qDebug() << fileRet.fileName;
    qDebug() << fileRet.fileBlockLength;
    qDebug() << fileRet.fileSize;
    qDebug() << fileRet.beginPosition;
    qDebug() << po;
    qDebug() << fileRet.fileBlockData;
    strea >> fileRet.frame;
    qDebug() << fileRet.frame;
    qDebug() << "wkkl";
    qDebug() << array.size();


//    filestr.fileBlockData = array.mid(23+fileNameLength,4096);

//    quint8 fileNameLength = (quint8)array.at(4);
//    fileRet.fileName = QString(array.mid(5,fileNameLength));
//    fileRet.beginPosition = ((quint8)array.at(33)<<24)+
//                            ((quint8)array.at(34)<<16)+
//                            ((quint8)array.at(35)<<8)+
//                            ((quint8)array.at(36));
//    fileRet.fileSize = ((quint8)array.at(25)<<24)+
//                        ((quint8)array.at(26)<<16)+
//                        ((quint8)array.at(27)<<8)+
//                        ((quint8)array.at(28));
//    fileRet.fileBlockLength = ((quint8)array.at(29)<<24)+
//                                ((quint8)array.at(30)<<16)+
//                                ((quint8)array.at(31)<<8)+
//                                ((quint8)array.at(32));
//    fileRet.fileBlockData = array.mid(37,fileRet.fileBlockLength);
//    qDebug() <<"size"<<array.size() << fileRet.fileBlockLength<< fileRet.fileBlockData.size()<<fileRet.beginPosition<<fileRet.fileSize;
//    fileRet.frame = (quint8)array.at(187);
    return fileRet;
}

void FirstWindow::writeFile(File filestr){
    QString filename = filestr.fileName;
    if(fileNameList.indexOf(filename)<0){
        fileNameList.append(filename);
        QFile file;
        file.setFileName(filename);
        bool ok = file.open(QIODevice::WriteOnly);
        if (!ok)
            qDebug() << "文件打开失败" ;
        else{
            qDebug() << "重头写";
            qDebug() << filestr.fileBlockData[4095];

            file.write(filestr.fileBlockData,filestr.fileBlockLength);
            file.close();
        }
        qDebug() << "tete";
        if(file.size()==filestr.fileSize){

            fileNameList.removeAt(fileNameList.indexOf(filename));
        }
        qDebug() << "tete";
    }else{
        QFile file;
        file.setFileName(filename);
        bool ok = file.open(QIODevice::Append);
        if (!ok)
            qDebug() << "文件打开失败" ;
        else{
            qDebug() << "续写";
            qDebug() << filestr.fileBlockData[4095];
            file.write(filestr.fileBlockData,filestr.fileBlockLength);
            file.close();
        }
        qDebug() << "nameList" << fileNameList.size()<< fileNameList.indexOf(filename);
        qDebug() << file.size() << filestr.fileSize;
        if(file.size()==filestr.fileSize){
            fileNameList.removeAt(fileNameList.indexOf(filename));

            writebase(filestr);
        }
        qDebug() << "zheli ";
    }
}

FirstWindow::User  FirstWindow::analysis09(QByteArray array){
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    User user;

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> user.name >> user.password >> user.frame;

    qDebug() << "用户信息";
    qDebug() << user.name << user.password << user.frame;
//    qDebug() <<"test0";
//    int namelength = (int)array.at(4);
//    int pwlength = (int)array.at(25);
//    qDebug() <<"test1";
//    QString name = QString(array.mid(5,namelength));
//    QString password = QString(array.mid(26,pwlength));
//    int frame = (int)array.at(46);
//    user.name = name;
//    user.password = password;
//    user.frame = frame;
    return user;
}

FirstWindow::LoginResult FirstWindow::analysis10(QByteArray array){

    LoginResult loginresult;
    quint8 loginstatus = (quint8)array.at(4);
    quint8 frame = (quint8)array.at(5);
    loginresult.loginStatus = loginstatus;
    loginresult.frame = frame;

    return loginresult;

}



quint8  FirstWindow::analysis01(QByteArray array){

    quint8 frame = (quint8)array.at(4);
    return frame;

}

quint8 FirstWindow::analysis05(QByteArray array){
    quint8 frame = (quint8)array.at(4);
    return frame;
}

FirstWindow::SelfDetect FirstWindow::analysis02(QByteArray array){

    SelfDetect selfDetect;
    quint8 result = (quint8)array.at(4);
    quint8 frame = (quint8)array.at(5);
    selfDetect.resultMes = result;
    selfDetect.frame = frame;

    return selfDetect;

}

FirstWindow::healthInfo FirstWindow::analysis06(QByteArray array){

    healthInfo healthinfo;
    quint8 stationNode = (quint8)array.at(4);
    quint8 frame = (quint8)array.at(5);
    healthinfo.stationNode = stationNode;
    healthinfo.frame = frame;

    return healthinfo;
}

FirstWindow::Mission FirstWindow::analysis03(QByteArray arr){
    Mission mission;

        mission.greatNode=QString(arr.mid(4,8));

        mission.greatVersion=quint8(arr.at(12));

        mission.changeMark = int(arr.at(13));

        mission.startYear=quint8(arr.at(14));
        mission.startMonth=quint8(arr.at(15));
        mission.startDay=quint8(arr.at(16));
        mission.startHour=quint8(arr.at(17));
        mission.startMinute=quint8(arr.at(18));

        mission.endYear=quint8(arr.at(19));
        mission.endMonth=quint8(arr.at(20));
        mission.endDay=quint8(arr.at(21));
        mission.endHour=quint8(arr.at(22));
        mission.endMinute=quint8(arr.at(23));

        mission.modelName=QString(arr.mid(24,7));
        mission.missionStatus=quint8(arr.at(32));
        mission.memberId=QString(arr.mid(33,2));
        mission.frame=quint8(arr.at(35));
        mission.checksum=quint8(arr.at(36));

        return mission;

}




void FirstWindow::readPendingDatagrams(){
    QHostAddress addr;
    quint16 port;
    QByteArray arrjudge;
//    arrjudge.resize(4);
    QByteArray arrCurrent;
    quint32 point = 0;
    while (udpsocket->hasPendingDatagrams()) //数据报等待被读取
    {
        point = 0;
        quint64 socketava = udpsocket->bytesAvailable();
        quint64 pend = udpsocket->pendingDatagramSize();


        arrjudge.resize(pend);
        int x = udpsocket->readDatagram(arrjudge.data(),arrjudge.size(),&addr,&port);


        arrjudge = getInvert(arrjudge);
        emit sendSocketData(pend,arrjudge,addr,port);

/*
        while(point !=pend){
            qDebug() << pend << point;
            qDebug() << "内部循环";
            qDebug() << quint8(arrjudge.at(0));
            qDebug() << quint8(arrjudge.at(1));


            if(quint8(arrjudge.at(0))==0x5A && quint8(arrjudge.at(1))==0x5A){
                qDebug() << "成立";
                QDataStream stre(&arrjudge,QIODevice::ReadOnly);
                stre.setVersion(QDataStream::Qt_5_1);
                stre.device()->seek(2);
                quint32 length;
                stre >> length;
                arrCurrent.resize(length+2);
                arrCurrent = arrjudge.mid(0,length+2);
                qDebug() << "tet";

                arrjudge = arrjudge.mid(length+2,arrjudge.length()-length-2);
                arrjudge.resize(arrjudge.length()-length-2);
                point +=length+2;
                qDebug() << "tet";

                qDebug() << arrCurrent.size();
                quint8 mesmark = quint8(arrCurrent.at(6));
                qDebug() << "tet";

                User user;
                File filestr;
                MissionResult result;
                switch (mesmark) {
                case 0x09:
                     user = analysis09(arrCurrent);
                     judgeUser(user);

//                    analysis09(arrCurrent);
                    break;
                case 0x07:
                    filestr =  analysis07(arrCurrent);
                    qDebug() << "filename"<<filestr.fileName<< "fileframe"<<filestr.frame;
                    writeFile(filestr);
                    qDebug() << "写文件完成";
                    break;
                case 0x04:
                    result = analysis04(arrCurrent);

                }

            }
        }*/
    }

}

void FirstWindow::writebase(File filestr){
    QSqlQuery query=QSqlQuery(db);
    bool getidok = query.exec(QString("select id from task where missionNode = '%1'").arg(filestr.node));
    qDebug() << "查询id成功？" << getidok;
    QSqlRecord rec1 = query.record();
    int idinde = rec1.indexOf("id");
    int id;
    while (query.next())
    {
         id = query.value(idinde).toInt();
         qDebug() << "id是多少" << id;
    }
    QString selectall = QString("select * from task where id = %1").arg(id);
    getidok = query.exec(selectall);

    qDebug() << "查询全部成功？" << getidok;
    rec1 = query.record();
    int proname = rec1.indexOf("projectName");
    QString name;
    int model = rec1.indexOf("XXmodel");
    QString models;
    while (query.next())
    {
         name = query.value(proname).toString();
         models = query.value(model).toString();
         qDebug() << "name和model是多少" << name<<models;
    }

    QString qs6 = QString("insert into disfile(node,name,model,filename,time) values('%1','%2','%3','%4',%5)").arg(filestr.node).arg(name).arg(models).arg(filestr.fileName).arg(QDateTime::currentDateTime().toTime_t());


    getidok = query.exec(qs6);
    qDebug() << "插入成功？" << getidok;
    qDebug() << query.lastError().text();
//    QSqlRecord rec2 = query.record();
//    qDebug() << "3:Number of columns: " << rec2.count();
//    int nameCol = rec2.indexOf("name")
//    QString lastname;


}
void FirstWindow::updateDatabase(MissionResult result){
    qDebug() << "返回结果" << result.result;
}

FirstWindow::MissionResult FirstWindow::analysis04(QByteArray array){
    MissionResult missionresult;
    missionresult.result=quint8(array.at(7));
    missionresult.frame = quint8(array.at(8));
    return missionresult;
}

void FirstWindow::judgeUser(User user){
    QSqlQuery query(db);
        QString qs = QString("select 密码,状态 from usernew where 账号 ='%1'").arg(user.name);

        query.exec(qs);
        QSqlRecord rec = query.record();
        qDebug() << "1:Number of columns: " << rec.count();
        int passwordCol = rec.indexOf("密码");
        int statusCol = rec.indexOf("状态");
        QString password1;
        QString status;
        int islock;

        if(!query.next())
        {
            LoginResult result;
            result.loginStatus = 0x01;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);
        }
        else
        {
            query.exec(qs);
            while (query.next())
            {
                 password1 = query.value(passwordCol).toString();
                 status = query.value(statusCol).toString();
            }


            if( (QString::compare(status, QString("正常"),Qt::CaseSensitive)) == 0)
            {
                islock = 0;
            }
            else
            {
                islock = 1;
            }

            QString qs1 = QString("select 错误次数 from usernew where 账号 ='%1'").arg(user.name);
            query.exec(qs1);
            QSqlRecord rec1 = query.record();
            qDebug() << "2:Number of columns: " << rec1.count();
            int errorCol = rec1.indexOf("错误次数");
            int error;
            while (query.next())
            {
                 error = query.value(errorCol).toInt();
            }

            QString password2 = QCryptographicHash::hash(user.password.toLatin1(),QCryptographicHash::Md5).toHex();
            qDebug() << islock;
            int x = QString::compare(password1, password2);
            bool a;

            if(x == 0)
            {
                a = true;
            }
            else
            {
                a = false;
            }

        if(!a && islock!=1)
        {
            error++;
            QString qs3 = QString("update usernew set 错误次数 ='%1' where 账号 ='%2'").arg(error).arg(user.name);
            query.exec(qs3);
            if(error==3)
            {
                islock=1;
                QString qs2 = QString("update usernew set 状态 = '%2' where 账号 ='%1'").arg(user.name).arg("已锁定");
                query.exec(qs2);
                QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(user.name);
                query.exec(qs4);
            }
            LoginResult result;
            result.loginStatus = 0x01;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);

        }
        else if(a && islock!=1)
        {
            //QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);
            LoginResult result;
            result.loginStatus = 0x00;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);

            QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(user.name);
            query.exec(qs4);

    //        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    //        QString currenttime = dateTime.toString("hh时mm分ss秒");//格式化时间
    //        qDebug() << currenttime;
    //        qDebug() << name;
    //        QString qs5 = QString("insert into loginlog(name,logintime) values('%1','%2')").arg(user.name).arg(currenttime);
    //        query.exec(qs5);

        }
        else
        {
            qDebug() << "用户被锁定";
        }
        }
}

/*
void FirstWindow::printChart(){
    ui->customPlot->plotLayout()->insertRow(0);
    QCPTextElement *legend_txt = new QCPTextElement(ui->customPlot,"任务信息", QFont("sans", 20, QFont::Bold));                  // 要把标题设置为legend层上显示，否则无法显示标题
    legend_txt->setTextColor(Qt::white);                //修改颜色
    ui->customPlot->plotLayout()->addElement(0, 0, legend_txt);

    ui->customPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);
    //绘制柱状图
    QCPAxis *xAxis = ui->customPlot->xAxis;//x轴
    QCPAxis *yAxis = ui->customPlot->yAxis;//y轴
    bars = new QCPBars(yAxis, xAxis);  // 使用yAxis作为柱状图的x轴，xAxis作为y轴

    bars->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars->setName("Bars"); // 设置图例
    bars->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色
    QColor *barColor = new QColor(20,68,106);
    barColor->setAlpha(0);
    QBrush *a = new QBrush(*barColor);
    bars->setBrush(*a);  // 设置柱状图的画刷颜色
    QPen *pen = new QPen();
    pen->setBrush(*a);
    bars->setPen(*pen);

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9<<10<<11<<12<<13<<14<<15<<16<<17<<18<<19<<20<<21<<22<<23<<24<<25;//轴的范围
    labels << "00:00" << "01:00" << "02:00" << "03:00" << "04:00" << "05:00" << "06:00"
              << "07:00" << "08:00" << "09:00" << "10:00" << "11:00" << "12:00" << "13:00"
                 << "14:00" << "15:00" << "16:00" << "17:00" << "18:00" << "19:00" << "20:00"
                    << "21:00" << "22:00" << "23:00"<< "24:00" ;//轴的刻度文字显示
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks,labels);
    xAxis->setTicker(textTicker);        // 设置为文字轴
    xAxis->setTickLabelRotation(60);     // 轴刻度文字旋转60度
    xAxis->setSubTicks(false);           // 不显示子刻度
    xAxis->setTickLength(0, 4);          // 轴内外刻度的长度分别是0,4,也就是轴内的刻度线不显示
    xAxis->setRange(0, 26);               // 设置x轴范围
    xAxis->setTickLabelColor(QColor(255,255,255));
    xAxis->setBasePen(QColor(255,255,255));
    QFont font;
    font.setPointSize(19);
    xAxis->setTickLabelFont(font);
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);


    //数据库部分
//    qDebug() << QSqlDatabase::drivers();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");



    QSqlQuery query=QSqlQuery(db);
    query.exec("SELECT * FROM pro504.task");  // 查询数据库pro504的表task的所有行和列

    QSqlRecord rec = query.record();

    qDebug() << "表的列数：" << rec.count();         // 表一共有多少列
    qDebug() << "表的行数：" << query.size();       // 表一共有多少行


    QString str=QString("select * from pro504.task");//取出包含同一地区的第一列湿度的数据用来画折线图
    query.exec(str);
    QList<QString> list0;
    QList<QString> list;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
    int missionNode = rec.indexOf("missionNode");

    int taskStatus = rec.indexOf("taskStatus");
    qDebug()<<"taskStatus"<<"query.size()"<<query.size();

    while (query.next())
    {
       //list.append(query.value(missionNode).toString());
       if(!(query.value(taskStatus)=="已完成"))
       {
           list0.append(query.value(missionNode).toString());                 //如果有数据，取第一列,也就是shidu，添加到list
       }
       else
       {
           list.append(query.value(missionNode).toString());
       }
    }

    //db.close();	 // 关闭数据库

    //    while(i<=size)
    //    {
    //        ticks2 << i;
    //        labels2 << missionNodeList.at(i);
    //        i++;
    //    }
    // 添加数据使用time控件
    // 拿到当天日期
    // 通过time控件的时分秒和今天的日期组合生成时间戳存入数据库

    // 从数据库读出来时间戳提取其中的小时和分钟
     //QString str=QString("select 任务开始时间, from task where id = '%1'").arg(b);


    QVector<double> ticks2;
    QVector<QString> labels2;
    //ticks2 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    //labels2 << "node1" << "node2" << "node3" << "node4" << "node5" << "node6" << "node7";
//    int n=0;
//    int i=1,j=0;
//    while(n<query.size())
//    {

//        ticks2<<i;
//        labels2 <<list.at(j);
//        qDebug()<<"任务代号"<<list.at(j);
//        i++;
//        j++;
//        n++;
//    }

    int n=0;
    while(n<list0.size())
    {
        ticks2<<n+1;
        labels2 <<list0.at(n);
        qDebug()<<"任务代号0"<<list0.at(n);
        n++;
    }

    QVector<double> ticks3;
    QVector<QString> labels3;
    int i=0;
    while(i<list.size())
    {
        ticks3<<list0.size()+i+1;
        labels3<<list.at(i);
        qDebug()<<"任务代号1"<<list.at(i);
        i++;
    }

    QSharedPointer<QCPAxisTickerText> textTicker2(new QCPAxisTickerText);
    textTicker2->addTicks(ticks2,labels2);
    textTicker2->addTicks(ticks3,labels3);
    yAxis->setTicker(textTicker2);        //

    yAxis->setTickLabelFont(font);
    yAxis->setRange(0, 12.1);          //设置y轴范围
    yAxis->setPadding(35);             // 轴的内边距
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    yAxis->setTickLabelColor(QColor(255,255,255));
    yAxis->setBasePen(QColor(255,255,255));

    QVector<double> fossilData1;
    QVector<double> fossilData2;
    QVector<double> fossilData3;
    QVector<double> fossilData4;
    // fossilData  << 13 << 9 << 2 << 5 << 7 << 4 << 1;//y轴坐标值

    QList<double> list1;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
    QList<double> list2;
    QList<double> list4;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
    QList<double> list5;

    int starttime = rec.indexOf("starttime");
    int endtime = rec.indexOf("endtime");
//    int taskStatus = rec.indexOf("taskStatus");
//    qDebug()<<"taskStatus"<<"query.size()"<<query.size();

    query.first();
    query.previous();
    while (query.next())
    {
       if(!(query.value(taskStatus)=="已完成"))
       {

           QDateTime dd = QDateTime::fromTime_t(query.value(starttime).toInt());
           list1.append(dd.toString("hh").toFloat()+(dd.toString("mm").toFloat())/60);
           qDebug() << "sta"<<dd;
       }
       else
       {
           QDateTime dd4 = QDateTime::fromTime_t(query.value(starttime).toInt());
           list4.append(dd4.toString("hh").toFloat()+(dd4.toString("mm").toFloat())/60);
           qDebug() << "sta"<<dd4;
       }
    }

    query.first();
    query.previous();
    while (query.next())
    {
        if(!(query.value(taskStatus)=="已完成"))
        {
            qDebug()  << query.value(endtime).toInt();
            QDateTime dd1 = QDateTime::fromTime_t(query.value(endtime).toInt());
            list2.append(dd1.toString("hh").toFloat()+(dd1.toString("mm").toFloat())/60);
            qDebug() << "sto"<<dd1;
        }
        else
        {
            qDebug()  << query.value(endtime).toInt();
            QDateTime dd5 = QDateTime::fromTime_t(query.value(endtime).toInt());
            list5.append(dd5.toString("hh").toFloat()+(dd5.toString("mm").toFloat())/60);
            qDebug() << "sto"<<dd5;
        }
    }

    QVector<double> ticks4;
    QVector<double> ticks5;
    int k=0;
    qDebug()<<query.size();
    qDebug()<<list1.size();
    qDebug()<<list2.size();
    while(k<list1.size())
    {
        qDebug() << k;
        ticks4<<k+1;
        fossilData1<<(list1.at(k)+1);
        fossilData2<<(list2.at(k)-list1.at(k));
        qDebug()<<"fossilData1:"<<fossilData1;
        qDebug()<<"fossilData2:"<<fossilData2;
        qDebug()<<"开始时间:"<<list1.at(k);
        qDebug()<<"结束时间:"<<list2.at(k);
        k++;
    }

    int L=0;
    qDebug()<<query.size();
    qDebug()<<list4.size();
    qDebug()<<list5.size();
    while(L<list4.size())
    {
        qDebug() << L;
        qDebug()<<"list1.size()"<<list1.size();
        ticks5<<list1.size()+L+1;
        fossilData4<<(list4.at(L)+1);
        fossilData3<<(list5.at(L)-list4.at(L));
        qDebug()<<"fossilData4:"<<fossilData4;
        qDebug()<<"fossilData3:"<<fossilData3;
        qDebug()<<"开始时间:"<<list4.at(L);
        qDebug()<<"结束时间:"<<list5.at(L);
        L++;
    }


    QLinearGradient plotGradient;

    plotGradient.setStart(0, 0);

    plotGradient.setFinalStop(0, 350);

    plotGradient.setColorAt(0, QColor(2, 34, 85));

    plotGradient.setColorAt(1, QColor(2, 34, 85));

    ui->customPlot->setBackground(plotGradient);

    ui->customPlot->yAxis->grid()->setVisible(false);

    bars->setData(ticks4, fossilData1);

    bars0 = new QCPBars(yAxis, xAxis);  // 使用yAxis作为柱状图的x轴，xAxis作为y轴

    bars0->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars0->setName("Bars"); // 设置图例
    bars0->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色
    QColor *barColor4 = new QColor(20,68,106);
    barColor4->setAlpha(0);
    QBrush *a1 = new QBrush(*barColor4);
    bars0->setBrush(*a1);  // 设置柱状图的画刷颜色
    QPen *pen1 = new QPen();
    pen1->setBrush(*a1);
    bars0->setPen(*pen1);

    bars0->setData(ticks5, fossilData4);

    bars2 = new QCPBars(yAxis, xAxis);  // 使用yAxis作为柱状图的x轴，xAxis作为y轴

    bars2->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars2->setName("Bars"); // 设置图例
    bars2->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色

    QColor *barColor2 = new QColor(254,192,0);
    QBrush *b2 = new QBrush(*barColor2);
    bars2->setBrush(*b2);

    bars2->moveAbove(bars);
    bars2->setData(ticks4, fossilData2);


    bars3 = new QCPBars(yAxis, xAxis);  // 使用yAxis作为柱状图的x轴，xAxis作为y轴

    bars3->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars3->setName("Bars"); // 设置图例
    bars3->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色

    QColor *barColor3 = new QColor(128,128,128);
    QBrush *b3 = new QBrush(*barColor3);
    bars3->setBrush(*b3);

    bars3->moveAbove(bars0);
    bars3->setData(ticks5, fossilData3);
}
*/

/*
void FirstWindow::change(QCPAbstractPlottable *a, int b, QMouseEvent *c){
    qDebug() << "yes"<< b;

    //通过b获取任务名
//    //数据库部分
//    qDebug() << QSqlDatabase::drivers();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

//    db.setHostName("127.0.0.1");
//    db.setPort(3306);
//    db.setDatabaseName("pro504");
//    db.setUserName("root");
//    db.setPassword("123456");
//    bool ok = db.open();
//    QSqlError er = db.lastError();
//    qDebug() << er.text();
//    if(ok==true)
//    {
//        qDebug() << "连接成功";
//    }

//    QSqlQuery query=QSqlQuery(db);
//    //query.exec("SELECT * FROM pro504.task");  // 查询数据库与id对应的任务名
//    QString str=QString("select * from task"); //取出包含同一地区的第一列湿度的数据用来画折线图
//    query.exec(str);
//    QList<QString> list;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
//    QList<QString> list1;
//    QList<QString> list2;

//    QList<double> list3;
//    QList<double> list4;

//    QList<QString> list5;
//    QString projectName = rec.indexOf("projectName");
//    QString missionNode = rec.indexOf("missionNode");
//    QString XXmodel = rec.indexOf("XXmodel");
//    int starttime = rec.indexOf("starttime");
//    int endtime = rec.indexOf("endtime");
//    QString taskStatus = rec.indexOf("taskStatus");

//    while (query.next())
//    {
//         list.append(query.value(projectName).toString());                 //如果有数据，取第一列,也就是shidu，添加到list
//         list1.append(query.value(missionNode).toString());
//         list2.append(query.value(XXmodel).toString());

//         QDateTime dd = QDateTime::fromTime_t(query.value(starttime).toInt());
//         list3.append(dd.toString("hh").toFloat()+(dd.toString("mm").toFloat())/60);

//         QDateTime dd1 = QDateTime::fromTime_t(query.value(endtime).toInt());
//         list4.append(dd1.toString("hh").toFloat()+(dd1.toString("mm").toFloat())/60);

//         list5.append(query.value(taskStatus).toString());
//    }


//    db.close();	 // 关闭数据库

    missionreview *p = new missionreview();
    connect(p,&missionreview::sendNewStr,this,&FirstWindow::getNewStr);
    connect(this,SIGNAL(sendStr(int)),p,SLOT(getStr(int)));
    connect(worker,&receieveData::finishSend,p,&missionreview::finishSend);

    emit sendStr(b);
    p->show();
}
*/

//void FirstWindow::on_pushButton_9_clicked()
//{
//    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
//    if(filePath.isEmpty()==false)
//    {
//        QFileInfo info(filePath);
//        filestr.fileName = info.fileName();
//        filestr.fileSize = info.size();

//        file.setFileName(filePath);
//        bool isOk = file.open(QIODevice::ReadOnly | QIODevice::Text);
//        if(isOk == false)
//        {
//            qDebug()<<"文件未成功打开 54";
//        }
//        else
//        {
//            int i=0;
//            QTextStream in(&file);
//            while (!in.atEnd())
//            {
//                QString line = in.readLine();
//                ui->listWidget->insertItem(i++,line);
//            }
//            file.close();
//        }
//    }
//    ui->listWidget->show();
//    ui->widget->show();
//}

//void FirstWindow::on_pushButton_18_clicked()
//{
//    ui->listWidget->hide();
//    ui->widget->hide();
//}



void FirstWindow::printfile(){
    QSqlQuery query=QSqlQuery(db);
    query.exec("SELECT * FROM disfile");  // 查询数据库pro504的表task的所有行和列

    QSqlRecord rec = query.record();

    qDebug() << "表的列数：" << rec.count();         // 表一共有多少列
    qDebug() << "表的行数：" << query.size();       // 表一共有多少行

    ui->tableWidget_3->setColumnCount(rec.count()-1);
    ui->tableWidget_3->setRowCount(query.size());
          //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
    int node = rec.indexOf("node");
    int name = rec.indexOf("name");
    int model = rec.indexOf("model");
    int filename = rec.indexOf("filename");
    int time = rec.indexOf("time");

    int i=0;
    while (query.next())
    {
        qDebug() << "循环次数" << i;
        for(int j=0;j<rec.count();j++){
            if(j==rec.count()-2){
//                int time_sec=100;
//                   QString timer=QTime(0, 0, 0).addSecs(int(time_sec)).toString(QString::fromLatin1("HH:mm:ss"));
//                QTableWidgetItem *Item = new QTableWidgetItem(
//                            query.value(j).toInt());
                ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(QDateTime::fromTime_t(query.value(j).toInt()).toString("hh:mm")));
            }else{
                QTableWidgetItem *Item = new QTableWidgetItem(
                            query.value(j).toString());
                ui->tableWidget_3->setItem(i,j,Item);
            }

        }
        i++;

//       query.value(node).toString();                 //如果有数据，取第一列,也就是shidu，添加到list
    }
}

//void FirstWindow::getPro(QString filename, quint64 allsize, quint64 nowsize,QString node){
//    emit sendPro(filename,allsize,nowsize,node);
//    if(allsize == nowsize){
//        qDebug() <<"调用了此方法";
//        packageLength = 0;
//        printfile();
//    }
//}

//void FirstWindow::refreshMission()
//{
//    QSqlQuery query(db);
//            if(query.exec("select missionNode,param1,param2,param3,param4,param5 from missiontable"))
//            {
//               ui->tableWidget_6->clearContents();
//               ui->tableWidget_6->setRowCount(0);

//                while(query.next())
//                {
//                    int rowCount = ui->tableWidget_6->rowCount();


//                    ui->tableWidget_6->insertRow(rowCount);

//                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(
//                                query.value(1).toString());
//                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                                query.value(0).toString());

//                    QTableWidgetItem *columnItem2 = new QTableWidgetItem(
//                                query.value(2).toString());

//                    QTableWidgetItem *columnItem3 = new QTableWidgetItem(
//                                query.value(3).toString());
//                    QTableWidgetItem *columnItem4 = new QTableWidgetItem(
//                                query.value(4).toString());
//                    QTableWidgetItem *columnItem5 = new QTableWidgetItem(
//                                query.value(5).toString());

//                    ui->tableWidget_6->setItem(rowCount,0, columnItem0);
//                    ui->tableWidget_6->setItem(rowCount,1, columnItem1);
//                    ui->tableWidget_6->setItem(rowCount,2, columnItem2);
//                    ui->tableWidget_6->setItem(rowCount,3, columnItem3);
//                    ui->tableWidget_6->setItem(rowCount,4, columnItem4);
//                    ui->tableWidget_6->setItem(rowCount,5, columnItem5);
//                }



//                for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//                {
//                    for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                    {
//                        o = ui->tableWidget_6->item(i,j);
//                        o->setFlags(Qt::ItemIsEnabled);
//                    }
//                }
//            }
//}

/*
void FirstWindow::getNewStr(QString missionnode,int startTime,int endTime)  //将Dialog传回的值设为treeWidget当前节点的内容
{
    qDebug()<<"更新柱状图";

    qDebug()<<missionnode<<startTime<<endTime;

    // 清除绘图区域并重新绘制
    //ui->customPlot->clearPlottables();  //横纵坐标没有删除
//    ui->customPlot->plotLayout()->removeAt(0);
    // 删除背景颜色和图片
    //ui->customPlot->setBackground(QBrush(Qt::NoBrush));
    ui->customPlot->replot();

//    printChart();

//    qDebug()<<newstr;

    ui->customPlot->setBackgroundScaledMode(Qt::IgnoreAspectRatio);
    //绘制柱状图
    xAxis = ui->customPlot->xAxis;//x轴
    yAxis = ui->customPlot->yAxis;//y轴

    QSqlQuery query=QSqlQuery(db);
    query.exec("SELECT * FROM task");  // 查询数据库pro504的表task的所有行和列

    QSqlRecord rec = query.record();

    qDebug() << "表的列数：" << rec.count();         // 表一共有多少列
    qDebug() << "表的行数：" << query.size();       // 表一共有多少行


//    QString str=QString("select * from task");//取出包含同一地区的第一列湿度的数据用来画折线图
//    query.exec(str);
    QList<QString> list0;
    QList<QString> list;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
    int missionNode = rec.indexOf("missionNode");

    int taskStatus = rec.indexOf("taskStatus");
    qDebug()<<"taskStatus"<<"query.size()"<<query.size();

    while (query.next())
    {
       //list.append(query.value(missionNode).toString());
       if(!(query.value(taskStatus)=="已完成"))
       {
           list0.append(query.value(missionNode).toString());                 //如果有数据，取第一列,也就是shidu，添加到list
       }
       else
       {
           list.append(query.value(missionNode).toString());
       }
    }

    //db.close();	 // 关闭数据库

    //    while(i<=size)
    //    {
    //        ticks2 << i;
    //        labels2 << missionNodeList.at(i);
    //        i++;
    //    }
    // 添加数据使用time控件
    // 拿到当天日期
    // 通过time控件的时分秒和今天的日期组合生成时间戳存入数据库

    // 从数据库读出来时间戳提取其中的小时和分钟
     //QString str=QString("select 任务开始时间, from task where id = '%1'").arg(b);


//    QVector<double> ticks2;
//    QVector<QString> labels2;
    //ticks2 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    //labels2 << "node1" << "node2" << "node3" << "node4" << "node5" << "node6" << "node7";
    int n=0;
    ticks2.clear();
    labels2.clear();
    while(n<list0.size())
   {
       ticks2<<n+1;
       labels2 <<list0.at(n);
       qDebug()<<"任务代号0"<<list0.at(n);
       n++;
   }

    int i=0;
    ticks3.clear();
    labels3.clear();
    while(i<list.size())
    {
        ticks3<<list0.size()+i+1;
        labels3<<list.at(i);
        qDebug()<<"任务代号1"<<list.at(i);
        i++;
    }


    QSharedPointer<QCPAxisTickerText> textTicker2(new QCPAxisTickerText);
    textTicker2->addTicks(ticks2, labels2);
    textTicker2->addTicks(ticks3,labels3);
    yAxis->setTicker(textTicker2);

//    yAxis->setTickLabelFont(font);
    yAxis->setRange(0, 12.1);          //设置y轴范围
    yAxis->setPadding(35);             // 轴的内边距
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    yAxis->setTickLabelColor(QColor(255,255,255));
    yAxis->setBasePen(QColor(255,255,255));

   QVector<double> fossilData1;
   QVector<double> fossilData2;
   QVector<double> fossilData3;
   QVector<double> fossilData4;
   // fossilData  << 13 << 9 << 2 << 5 << 7 << 4 << 1;//y轴坐标值

   QList<double> list1;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
   QList<double> list2;
   QList<double> list4;            //创建取结果的列表，之所以使用列表，不用数组，因为现在还不知道结果有多少，不能确定数组长度，所有先用list接收，然后转为数组
   QList<double> list5;

   int starttime = rec.indexOf("starttime");
   int endtime = rec.indexOf("endtime");

   query.first();
   query.previous();
   while (query.next())
   {
      if(!(query.value(taskStatus)=="已完成"))
      {

          QDateTime dd = QDateTime::fromTime_t(query.value(starttime).toInt());
          list1.append(dd.toString("hh").toFloat()+(dd.toString("mm").toFloat())/60);
          qDebug() << "sta"<<dd;
      }
      else
      {
          QDateTime dd4 = QDateTime::fromTime_t(query.value(starttime).toInt());
          list4.append(dd4.toString("hh").toFloat()+(dd4.toString("mm").toFloat())/60);
          qDebug() << "sta"<<dd4;
      }
   }

   query.first();
   query.previous();
   while (query.next())
   {
       if(!(query.value(taskStatus)=="已完成"))
       {
           qDebug()  << query.value(endtime).toInt();
           QDateTime dd1 = QDateTime::fromTime_t(query.value(endtime).toInt());
           list2.append(dd1.toString("hh").toFloat()+(dd1.toString("mm").toFloat())/60);
           qDebug() << "sto"<<dd1;
       }
       else
       {
           qDebug()  << query.value(endtime).toInt();
           QDateTime dd5 = QDateTime::fromTime_t(query.value(endtime).toInt());
           list5.append(dd5.toString("hh").toFloat()+(dd5.toString("mm").toFloat())/60);
           qDebug() << "sto"<<dd5;
       }
   }


   ticks4.clear();
   ticks5.clear();
   int k=0;
   qDebug()<<query.size();
   qDebug()<<list1.size();
   qDebug()<<list2.size();
   while(k<list1.size())
   {
       qDebug() << k;
       ticks4<<k+1;
       fossilData1<<(list1.at(k)+1);
       fossilData2<<(list2.at(k)-list1.at(k));
       qDebug()<<"fossilData1:"<<fossilData1;
       qDebug()<<"fossilData2:"<<fossilData2;
       qDebug()<<"开始时间:"<<list1.at(k);
       qDebug()<<"结束时间:"<<list2.at(k);
       k++;
   }

   int L=0;
   qDebug()<<query.size();
   qDebug()<<list4.size();
   qDebug()<<list5.size();
   while(L<list4.size())
   {
       qDebug() << L;
       qDebug()<<"list1.size()"<<list1.size();
       ticks5<<list1.size()+L+1;
       fossilData4<<(list4.at(L)+1);
       fossilData3<<(list5.at(L)-list4.at(L));
       qDebug()<<"fossilData4:"<<fossilData4;
       qDebug()<<"fossilData3:"<<fossilData3;
       qDebug()<<"开始时间:"<<list4.at(L);
       qDebug()<<"结束时间:"<<list5.at(L);
       L++;
   }
//   QLinearGradient plotGradient;

//   plotGradient.setStart(0, 0);

//   plotGradient.setFinalStop(0, 350);

//   plotGradient.setColorAt(0, QColor(2, 34, 85));

//   plotGradient.setColorAt(1, QColor(2, 34, 85));

//   ui->customPlot->setBackground(plotGradient);

//   ui->customPlot->yAxis->grid()->setVisible(false);

   ticks.clear();
   labels.clear();
   ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9<<10<<11<<12<<13<<14<<15<<16<<17<<18<<19<<20<<21<<22<<23<<24<<25;//轴的范围
   labels << "00:00" << "01:00" << "02:00" << "03:00" << "04:00" << "05:00" << "06:00"
             << "07:00" << "08:00" << "09:00" << "10:00" << "11:00" << "12:00" << "13:00"
                << "14:00" << "15:00" << "16:00" << "17:00" << "18:00" << "19:00" << "20:00"
                   << "21:00" << "22:00" << "23:00"<< "24:00" ;//轴的刻度文字显示

   qDebug() << "数据" << ticks2<< fossilData1;


   bars->setData(ticks2, fossilData1);
   qDebug() << "123";

   bars0->setData(ticks5, fossilData4);


//   QCPBars *bars2 = new QCPBars(yAxis, xAxis);  // 使用yAxis作为柱状图的x轴，xAxis作为y轴

   bars2->setData(ticks4, fossilData2);
   bars3->setData(ticks5, fossilData3);
   ui->customPlot->replot();
}
*/

//void FirstWindow::realtimeChartSlot()
//{
//      //static QTime time(QTime::currentTime());
//      // calculate two new data points:
////      double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
//      double nowtime = QTime::currentTime().msecsSinceStartOfDay();
//      double nowtime1 = nowtime*0.001;
//      double key = nowtime;
//      static double lastPointKey = 0;
//      if (key-lastPointKey > 0.002) // at most add point every 2 ms
//      {
//        // add data to lines:
//        ui->customPlot2->graph(0)->addData(nowtime1, qSin(nowtime1)+qrand()/(double)RAND_MAX*1*qSin(nowtime1/0.3843));
//        ui->customPlot2->graph(1)->addData(nowtime1, qCos(nowtime1)+qrand()/(double)RAND_MAX*0.5*qSin(nowtime1/0.4364));
//        ui->customPlot2->graph(2)->addData(nowtime1,1);

//        lastPointKey = key;
//      }
//      // make key axis range scroll with the data (at a constant range size of 8):   滚动范围

//      ui->customPlot2->xAxis->setRange(nowtime1, 8, Qt::AlignRight);
//      ui->customPlot2->replot();

//      // calculate frames per second:
//      static double lastFpsKey;
//      static int frameCount;
//      ++frameCount;
//      if (key-lastFpsKey > 2) // average fps over 2 seconds
//      {
//          lastFpsKey = key;
//          frameCount = 0;
//      }
//}

//void FirstWindow::realtimeDataSlot()
//{
//      double nowtime = QTime::currentTime().msecsSinceStartOfDay();
//      double nowtime1 = nowtime*0.001;
//      double key = nowtime;
//      static double lastPointKey = 0;
//      if (key-lastPointKey > 0.002) // at most add point every 2 ms
//      {
//        double data1 = (qSin(nowtime1)+qrand()/(double)RAND_MAX*1*qSin(nowtime1/0.3843));
//        QString str1 = QString("%1").arg(QString::number(data1,'f',2));
//        double data2 = (qCos(nowtime1)+qrand()/(double)RAND_MAX*0.5*qSin(nowtime1/0.4364));
//        QString str2 = QString("%1").arg(QString::number(data2,'f',2));
//        ui->tableWidget_2->setItem(0,2, new QTableWidgetItem(str1));
//        ui->tableWidget_2->setItem(0,3, new QTableWidgetItem(str2));


//        lastPointKey = key;
//      }

//}

//void FirstWindow::printRTimeChart()
//{
//      ui->customPlot2->legend->setVisible(false);
//      ui->customPlot2->addGraph(); // blue line
//      ui->customPlot2->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//      ui->customPlot2->graph(0)->setName("参数1");
//      ui->customPlot2->addGraph(); // red line
//      ui->customPlot2->graph(1)->setPen(QPen(QColor(255, 110, 40)));
//      ui->customPlot2->graph(1)->setName("参数2");
//      ui->customPlot2->addGraph(); // black line
//      ui->customPlot2->graph(2)->setPen(QPen(QColor(0, 0, 0)));
//      ui->customPlot2->graph(2)->setName("参数3");
//      ui->customPlot2->legend->setVisible(true);
//      ui->customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//      QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
//      timeTicker->setTimeFormat("%h:%m:%s");
//      ui->customPlot2->xAxis->setTicker(timeTicker);

//      ui->customPlot2->axisRect()->setupFullAxesBox();
//      ui->customPlot2->yAxis->setRange(-1.2, 1.2);

//      // make left and bottom axes transfer their ranges to right and top axes:
//      connect(ui->customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot2->xAxis2, SLOT(setRange(QCPRange)));
//      connect(ui->customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot2->yAxis2, SLOT(setRange(QCPRange)));

////      connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
////      dataTimer.start(2000);
//      // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//      connect(&chartTimer, SIGNAL(timeout()), this, SLOT(realtimeChartSlot()));
//      chartTimer.start(25);

//}

void FirstWindow::writeSendFile(QString fileName, QString node, quint32 fileSize, quint32 fileBlockLength, quint32 beginPosition, quint8 frame){
    qDebug() << "触发了写数据的方法";
    File filee;
    filee.fileName = fileName;
    filee.node = node;
    filee.fileSize = fileSize;
    filee.fileBlockLength = fileBlockLength;
    filee.beginPosition = beginPosition;
    filee.frame = frame;
    writebase(filee);
}

//void FirstWindow::on_pushButton_16_clicked()
//{

//    ui->lineEdit_3->setText("");
//    ui->lineEdit_4->setText("");
//    ui->lineEdit_5->setText("");
//    ui->lineEdit_6->setText("");
//    ui->lineEdit_7->setText("");
//}

void FirstWindow::getUser(QString name, QString password, QHostAddress addr)
{
    User user;
    user.name = name;
    user.password = password;
    QSqlQuery query(db);
    QString qs = QString("select password,islock from user where name ='%1'").arg(user.name);

    query.exec(qs);
    QSqlRecord rec = query.record();
    qDebug() << "1:Number of columns: " << rec.count();
    int passwordCol = rec.indexOf("password");
    int islockCol = rec.indexOf("islock");
    QString password1;
    int islock;

    while (query.next())
    {
         password1 = query.value(passwordCol).toString();
         islock = query.value(islockCol).toInt();
    }

    QString qs1 = QString("select error from user where name ='%1'").arg(user.name);
    query.exec(qs1);
    QSqlRecord rec1 = query.record();
    qDebug() << "2:Number of columns: " << rec1.count();
    int errorCol = rec1.indexOf("error");
    int error;
    while (query.next())
    {
         error = query.value(errorCol).toInt();
    }

    QString password2 = QCryptographicHash::hash(user.password.toLatin1(),QCryptographicHash::Md5).toHex();
    qDebug() << islock;
    int x = QString::compare(password1, password2);
    bool a;

    if(x == 0)
    {
        a = true;
    }
    else
    {
        a = false;
    }

    if(!a && islock!=1)
    {
        error++;
        QString qs3 = QString("update user set error ='%1' where name ='%2'").arg(error).arg(user.name);
        query.exec(qs3);
        if(error==3)
        {
            islock=1;
            QString qs2 = QString("update user set islock = 1 where name ='%1'").arg(user.name);
            query.exec(qs2);
        }
        LoginResult result;
        result.loginStatus = 0x01;
        result.frame = 1;
        QByteArray array = s10(result);
        quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);

    }
    else if(a && islock!=1)
    {
        //QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);
        LoginResult result;
        result.loginStatus = 0x00;
        result.frame = 1;
        QByteArray array = s10(result);
        quint64 hassend = udpsocket->writeDatagram(getInvert(array),addr,9010);

        QString qs4 = QString("update user set error =0 where name ='%1'").arg(user.name);
        query.exec(qs4);

        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
        QString currenttime = dateTime.toString("hh时mm分ss秒");//格式化时间
        qDebug() << currenttime;
        qDebug() << name;
        QString qs5 = QString("insert into loginlog(name,logintime) values('%1','%2')").arg(user.name).arg(currenttime);
        query.exec(qs5);

    }
    else
    {
        qDebug() << "用户被锁定";
    }
}

void FirstWindow::on_pushButton_23_clicked()
{
    pro->show();
}

void FirstWindow::finishFile(QString filename, QString node)
{
    QString finishAlert = QString("文件%1已接收完成").arg(filename);
    QMessageBox::information(this ,"文件接收提示",finishAlert);
}


void FirstWindow::printStationInfo(){
    QSqlQuery query(db);
            if(query.exec("select name,ip,data1,data2,data3 from station"))
            {
               ui->tableWidget_5->clearContents();
               ui->tableWidget_5->setRowCount(0);

                while(query.next())
                {
                    int rowCount = ui->tableWidget_5->rowCount();


                    ui->tableWidget_5->insertRow(rowCount);
//                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(QString("未锁定"));

//                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                                query.value(0).toString());

//                    if(query.value(1).toInt()==0){
//                        columnItem1 = new QTableWidgetItem(QString("未锁定"));
//                    }else{
//                        columnItem1 = new QTableWidgetItem(QString("锁定"));
//                    }

                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                query.value(0).toString());

                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                                query.value(1).toString());

                    QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                query.value(2).toString());

                    QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                query.value(3).toString());

                    QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                                query.value(4).toString());


                    ui->tableWidget_5->setItem(rowCount,0, columnItem0);
                    ui->tableWidget_5->setItem(rowCount,1, columnItem1);
                    ui->tableWidget_5->setItem(rowCount,2, columnItem2);
                    ui->tableWidget_5->setItem(rowCount,3, columnItem3);
                    ui->tableWidget_5->setItem(rowCount,4, columnItem4);

                }
            }

            ui->tableWidget_5->setEditTriggers(QAbstractItemView::CurrentChanged);


            for(int i=0;i<ui->tableWidget_5->rowCount();i++){
                for(int j=0;j<ui->tableWidget_5->columnCount();j++){

                    item = ui->tableWidget_5->item(i,j);
                    item->setFlags(Qt::ItemIsEnabled);
                }
            }
}

void FirstWindow::setPushStyleSheet(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(47, 64, 80);");
}

void FirstWindow::setCommonStyleSheet(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(87, 104, 120);");
}

void FirstWindow::initialDataGeshanManage()
{
    QStringList headerList;
    headerList << "型号" << "平台" << "格栅路径" << "格栅版本" ;
    ui->widget_5->set_widget_column_header(headerList);
    ui->widget_5->set_database(QString("datageshan"));
    QList<quint8> string_column_list;
    string_column_list << 0 << 1 << 2 << 3 ;
    ui->widget_5->set_string_column_number(string_column_list);
    QMap<quint8,QStringList> combobox_map;
    QStringList strList1;
    strList1 << "遥测地面站" << "试飞监控系统" << "联合试飞系统";
    combobox_map.insert(quint8(1),strList1);
    ui->widget_5->set_combobox_map(combobox_map);
    ui->widget_5->set_primaryKeyIndex(0);
    ui->widget_5->set_resizeMode(QHeaderView::Stretch);
    ui->widget_5->initial_widget();
}

//void FirstWindow::printMission()
//{
//    qDebug() << "printmission";
//    QSqlQuery query(db);
//        if(query.exec("select missionNode,param1,param2,param3,param4,param5 from missiontable"))
//        {
//            qDebug() << "查询mission宏信息成功";
//           ui->tableWidget_6->clearContents();
//           ui->tableWidget_6->setRowCount(0);
//           while(query.next())
//           {
//              int rowCount = ui->tableWidget_6->rowCount();
//              ui->tableWidget_6->insertRow(rowCount);

//              QTableWidgetItem *columnItem1 = new QTableWidgetItem(query.value(1).toString());

//              QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                        query.value(0).toString());

//              QTableWidgetItem *columnItem2 = new QTableWidgetItem(
//                        query.value(2).toString());

//              QTableWidgetItem *columnItem3 = new QTableWidgetItem(
//                        query.value(3).toString());

//              QTableWidgetItem *columnItem4 = new QTableWidgetItem(
//                        query.value(4).toString());

//              QTableWidgetItem *columnItem5 = new QTableWidgetItem(
//                        query.value(5).toString());

//              qDebug() << "任务信息1" << columnItem0->text();
//              qDebug() << "任务信息2" << columnItem1->text();
//              qDebug() << "任务信息3" << columnItem2->text();
//              qDebug() << "任务信息4" << columnItem3->text();
//              qDebug() << "任务信息5" << columnItem4->text();
//              qDebug() << "rowcount" << rowCount;

//              ui->tableWidget_6->setItem(rowCount,0, columnItem0);
//              ui->tableWidget_6->setItem(rowCount,1, columnItem1);
//              ui->tableWidget_6->setItem(rowCount,2, columnItem2);
//              ui->tableWidget_6->setItem(rowCount,3, columnItem3);
//              ui->tableWidget_6->setItem(rowCount,4, columnItem4);
//              ui->tableWidget_6->setItem(rowCount,5, columnItem5);
//            }
//        }else{

//            qDebug() << "查询mission宏信息失败";
//        }

//        ui->tableWidget_6->verticalHeader()->hide();
//        ui->tableWidget_6->setEditTriggers(QAbstractItemView::CurrentChanged);

//        for(int i=0;i<ui->tableWidget_6->rowCount();i++){
//            for(int j=0;j<ui->tableWidget_6->columnCount();j++){

//                o = ui->tableWidget_6->item(i,j);
//                o->setFlags(Qt::ItemIsEnabled);

//            }
//        }

//        QTableWidgetItem *columnItem10 = new QTableWidgetItem(
//                  QString("test"));
//        ui->tableWidget_6->setItem(0,0, columnItem10);
//}





void FirstWindow::cellClickedSlot1(int x, int y)
{
    // 判断x是不是所编辑的那一行，如果不是，就取出它所编辑的所有数据，校验，成功后提示修改成功，失败后提示失败原因

    if(rowEdit1!=x && isedit1 == 1)
    {
        QString newname = ui->tableWidget_5->item(rowEdit1,0)->text();
        QString newip = ui->tableWidget_5->item(rowEdit1,1)->text();
        QString newdata1 = ui->tableWidget_5->item(rowEdit1,2)->text();
        QString newdata2 = ui->tableWidget_5->item(rowEdit1,3)->text();
        QString newdata3 = ui->tableWidget_5->item(rowEdit1,4)->text();

        QSqlQuery query(db);
        QString qs = QString("update station set name ='%1',data1 ='%2',data2 ='%3',data3 ='%4',ip='%6' where name ='%5'").arg(newname).arg(newdata1).arg(newdata2).arg(newdata3).arg(oldname).arg(newip);

        if(query.exec(qs))
        {
            QMessageBox::information(this,"提醒","修改成功！",QMessageBox::Ok);

            for(int i=0;i<ui->tableWidget_5->rowCount();i++)
            {
                for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                {
                    item = ui->tableWidget_5->item(i,j);
                    item->setFlags(Qt::ItemIsEnabled);
                }
            }
            qDebug() << "1";
        }
        else
        {
            QMessageBox::information(this,"警告","用户名重复，修改失败！",QMessageBox::Ok);
            QTableWidgetItem *item1 = new QTableWidgetItem(oldname);
            ui->tableWidget_5->setItem(rowEdit1,0,item1);

            for(int i=0;i<ui->tableWidget_5->rowCount();i++)
            {
                for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                {
                    item = ui->tableWidget_5->item(i,j);
                    item->setFlags(Qt::ItemIsEnabled);
                }
            }
            qDebug() << "0";
        }

        if(query.exec("select name,ip,data1,data2,data3 from station"))
        {
           ui->tableWidget_5->clearContents();
           ui->tableWidget_5->setRowCount(0);

            while(query.next())
            {
                int rowCount = ui->tableWidget_5->rowCount();


                ui->tableWidget_5->insertRow(rowCount);

                QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                            query.value(0).toString());

                QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                            query.value(1).toString());

                QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                            query.value(2).toString());

                QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                            query.value(3).toString());

                QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                            query.value(4).toString());


                ui->tableWidget_5->setItem(rowCount,0, columnItem0);
                ui->tableWidget_5->setItem(rowCount,1, columnItem1);
                ui->tableWidget_5->setItem(rowCount,2, columnItem2);
                ui->tableWidget_5->setItem(rowCount,3, columnItem3);
                ui->tableWidget_5->setItem(rowCount,4, columnItem4);


                    }
                }


                            for(int i=0;i<ui->tableWidget_5->rowCount();i++)
                            {
                                for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                                {
                                    item = ui->tableWidget_5->item(i,j);
                                    item->setFlags(Qt::ItemIsEnabled);
                                }
                            }
                        }
        isedit1 = 0;

}

void FirstWindow::getFinish(int num,QString filename,QString code)
{
//    QMessageBox::information(this,"提示信息",filename+QString("已接收完成"));

    qInfo("用户: %s\t\t 任务宏：%s  任务文件%s接收", currentUser.toUtf8().constData(),code.toUtf8().constData(),filename.toUtf8().constData());
    QSqlQuery query=QSqlQuery(db);
    //query.exec("SELECT * FROM pro504.task");  // 查询数据库与id对应的任务名
    QString str=QString("select * from `missionnew2` where `任务标识` in (select `任务宏` from `missionsend` where `任务代号` = '%1')").arg(code); //取出包含同一地区的第一列湿度的数据用来画折线图
    query.exec(str);

    QSqlRecord rec = query.record();

    int maxing = rec.indexOf("码型");
    int malv = rec.indexOf("码率");
    int zichang = rec.indexOf("字长");
    int zhenchang = rec.indexOf("帧长");
    int zhenmazu = rec.indexOf("帧码组");
    int zhenmazuchang = rec.indexOf("帧码组长");
    int fuzhenfangshi = rec.indexOf("副帧方式");
    int fuzhenchang = rec.indexOf("副帧长");
    int idziweizhi = rec.indexOf("ID字位置");
    int idzijizhi = rec.indexOf("ID字基值");
    int idzijishu = rec.indexOf("ID字计数方向");
    int jiemizhuangtai = rec.indexOf("解密状态");
    int xunhuanfuzhenweizhi = rec.indexOf("循环副帧位置");
    int xunhuanfuzhenmazu = rec.indexOf("循环副帧码组");
    int duofuhaojianyan = rec.indexOf("多符号检验");
    int tpc = rec.indexOf("TPC/LDPC校验");
    int kuaitongbuzhenmazu = rec.indexOf("块同步帧码组");
    int AGC = rec.indexOf("AGC时间常数");
    int zhongpindaikuan = rec.indexOf("中频带宽");
    int AFC = rec.indexOf("AFC时间常数");
    int AFCmoshi = rec.indexOf("AFC模式");
    int jiaowucha = rec.indexOf("角误差输出带宽");
    int gongzuodianpin = rec.indexOf("工作点频");
    int xinghao = rec.indexOf("任务型号");
    int miaoshu = rec.indexOf("任务描述");
    int biaoshi = rec.indexOf("任务标识");

    while (query.next())
    {
        battleForm->maxing = query.value(maxing).toString();
        battleForm->malv = query.value(malv).toString();
        battleForm->zichang = query.value(zichang).toString();
        battleForm->zhenchang = query.value(zhenchang).toString();
        battleForm->zhenmazu = query.value(zhenmazu).toString();
        battleForm->zhenmazuchang = query.value(zhenmazuchang).toString();
        battleForm->fuzhenfangshi = query.value(fuzhenfangshi).toString();
        battleForm->fuzhenchang = query.value(fuzhenchang).toString();
        battleForm->idziweizhi = query.value(idziweizhi).toString();
        battleForm->idzijizhi = query.value(idzijizhi).toString();
        battleForm->idzijishu = query.value(idzijishu).toString();
        battleForm->jiemizhuangtai = query.value(jiemizhuangtai).toString();
        battleForm->xunhuanfuzhenweizhi = query.value(xunhuanfuzhenweizhi).toString();
        battleForm->xunhuanfuzhenmazu = query.value(xunhuanfuzhenmazu).toString();
        battleForm->duofuhaojianyan = query.value(duofuhaojianyan).toString();
        battleForm->tpc = query.value(tpc).toString();
        battleForm->kuaitongbuzhenmazu = query.value(kuaitongbuzhenmazu).toString();
        battleForm->AGC = query.value(AGC).toString();
        battleForm->zhongpindaikuan = query.value(zhongpindaikuan).toString();
        battleForm->AFC = query.value(AFC).toString();
        battleForm->AFCmoshi = query.value(AFCmoshi).toString();
        battleForm->jiaowucha = query.value(jiaowucha).toString();
        battleForm->gongzuodianpin = query.value(gongzuodianpin).toString();
        battleForm->xinghao = query.value(xinghao).toString();
        battleForm->miaoshu = query.value(miaoshu).toString();
        battleForm->biaoshi = query.value(biaoshi).toString();
    }
    battleForm->code = code;
    battleForm->filename = filename;
    QString startendtime;
    QSqlQuery query2=QSqlQuery(db);
    //query.exec("SELECT * FROM pro504.task");  // 查询数据库与id对应的任务名
    QString str2=QString("select * from `missionsend` where `任务代号` = '%1'").arg(code); //取出包含同一地区的第一列湿度的数据用来画折线图
    query2.exec(str2);

    QSqlRecord rec2 = query2.record();

    int start = rec2.indexOf("时间节点(起始)");
    int end = rec2.indexOf("时间节点(终止)");

    while (query2.next())
    {
        battleForm->startendtime = query2.value(start).toString()+"-"+query2.value(end).toString();
    }
    battleForm->date = QDateTime::currentDateTime().toString("yyyy.MM.dd");
    battleForm->setTableWidgetItem();
    battleForm->exportExcel();
}

void FirstWindow::getDelayReturn(MutiFile *muti, int time)
{
    emit emitDelayTest(muti);
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(time));
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget_2->setItem(mutiFile.indexOf(muti),1,item);

    if(time<1000){
        QIcon *icon = new QIcon(":/image/greenlight.png");
        QTableWidgetItem *item3 = new QTableWidgetItem("良好");
        item3->setIcon(*icon);
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),3,item3);
    }else if(time<5000){
        QIcon *icon = new QIcon(":/image/yellowlight.png");
        QTableWidgetItem *item3 = new QTableWidgetItem("拥堵");
        item3->setIcon(*icon);
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),3,item3);
    }else{
        QIcon *icon = new QIcon(":/image/redlight.png");
        QTableWidgetItem *item3 = new QTableWidgetItem("极差");
        item3->setIcon(*icon);
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),3,item3);
    }

}

void FirstWindow::getDownloadReturn(QString ip, int time)
{
    emit emitDelayDownloadTest(ip);
    qDebug() << ip << "下载:" << time;
}

void FirstWindow::getCurrentUser(QString user)
{
    currentUser = user;
    ui->label_2->setText(user);
}

void FirstWindow::getDelete(QString ip)
{
    for(int i=0;i<mutiFile.size();i++){
        if(mutiFile.at(i)->stationIp==ip){
            mutiFile.at(i)->t->quit();
            mutiFile.at(i)->t->deleteLater();

            mutiFile.at(i)->socket->disconnectFromHost();

            // 使用deleteLater()函数来销毁socket对象
            mutiFile.at(i)->socket->deleteLater();
            emit emitdeleteProgress(i);
        }
    }
}

void FirstWindow::logButtonPush()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "./", "Text Files (*.txt);;All Files (*.*)");
    LogInfo *p = new LogInfo(fileName);
    p->show();
}

void FirstWindow::initialGrille(QList<FileInfo*> list)
{
    grilleWidget->initialFileInfo(list);
}

void FirstWindow::initialDisplay(QList<FileInfo*> list)
{
    displayWidget->initialFileInfo(list);
}

void FirstWindow::getGrilleProgress(quint64 pro)
{
    fileDownload1->setValue(pro);
}

void FirstWindow::getDisplayProgress(quint64 pro)
{
    fileDownload2->setValue(pro);
}




void FirstWindow::on_pushButton_20_clicked()
{
    QString input_name=ui->lineEdit_8->text();
        int row_num=ui->tableWidget_5->rowCount();
        if (input_name=="")//判断是否是空，如果是空就显示所有行
        {

            QSqlQuery query(db);
                    if(query.exec("select name,ip,data1,data2,data3 from station"))
                    {
                       ui->tableWidget_5->clearContents();
                       ui->tableWidget_5->setRowCount(0);

                        while(query.next())
                        {
                            int rowCount = ui->tableWidget_5->rowCount();


                            ui->tableWidget_5->insertRow(rowCount);

                            QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                        query.value(0).toString());

                            QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                                        query.value(1).toString());

                            QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                        query.value(2).toString());

                            QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                        query.value(3).toString());

                            QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                                        query.value(4).toString());


                            ui->tableWidget_5->setItem(rowCount,0, columnItem0);
                            ui->tableWidget_5->setItem(rowCount,1, columnItem1);
                            ui->tableWidget_5->setItem(rowCount,2, columnItem2);
                            ui->tableWidget_5->setItem(rowCount,3, columnItem3);
                            ui->tableWidget_5->setItem(rowCount,4, columnItem4);

                        }



                        for(int i=0;i<ui->tableWidget_5->rowCount();i++)
                        {
                            for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                            {
                                item = ui->tableWidget_5->item(i,j);
                                item->setFlags(Qt::ItemIsEnabled);
                            }
                        }
                    }
        }
        else
        {
            QList <QTableWidgetItem *> item = ui->tableWidget_5->findItems(input_name, Qt::MatchContains);
            for(int i=0;i<row_num;i++)
            {
                ui->tableWidget_5->setRowHidden(i,true);//隐藏

            }
            //判断符合条件索引是不是空
            if(!item.empty())
            {
                for(int i=0;i<item.count();i++)
                {
                    ui->tableWidget_5->setRowHidden(item.at(i)->row(),false);

                }
            }
        }
}


void FirstWindow::on_tableWidget_5_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *change = menu.addAction(tr("编辑"));
    menu.addSeparator();
    QAction *deleteUser = menu.addAction(tr("删除"));
    connect(change, &QAction::triggered, [=]()
    {


        isedit1 = 1;
        qDebug() << "change";
        int row = ui->tableWidget_5->currentRow();
        rowEdit1 = row;
        qDebug() << row;
//        ui->tableWidget_4->setEditTriggers(QAbstractItemView::CurrentChanged);
        for(int i=0;i<ui->tableWidget_5->rowCount();i++){
            for(int j=0;j<ui->tableWidget_5->columnCount();j++){
                item = ui->tableWidget_5->item(i,j);
                item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            }
        }
        for(int i=0;i<ui->tableWidget_5->rowCount();i++){
            for(int j=0;j<ui->tableWidget_5->columnCount();j++){
                if(i!=row){
                    item = ui->tableWidget_5->item(i,j);
  //                o->setFlags(Qt::ItemIsEnabled|o->flags());
                    item->setFlags(Qt::ItemIsEnabled);
                    qDebug() << i << j;
                }

            }
        }

        oldname = ui->tableWidget_5->item(row,0)->text();//oldname

        connect(ui->tableWidget_5,SIGNAL(cellClicked(int,int)),this,SLOT(cellClickedSlot1(int ,int )));

    });



    connect(deleteUser, &QAction::triggered, [=]()
    {
        int row = ui->tableWidget_5->currentRow();
        QString oldname1 = ui->tableWidget_5->item(row,0)->text();
        QSqlQuery query(db);
        QString qs = QString("delete from station where name ='%1'").arg(oldname1);
        qDebug() << oldname1;
        if(query.exec(qs))
        {
            qDebug() << "删除1";


            if(query.exec("select name,ip,data1,data2,data3 from station"))
            {
               ui->tableWidget_5->clearContents();
               ui->tableWidget_5->setRowCount(0);

                while(query.next())
                {
                    int rowCount = ui->tableWidget_5->rowCount();


                    ui->tableWidget_5->insertRow(rowCount);

                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                query.value(0).toString());

                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                                query.value(1).toString());

                    QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                query.value(2).toString());

                    QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                query.value(3).toString());

                    QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                                query.value(4).toString());


                    ui->tableWidget_5->setItem(rowCount,0, columnItem0);
                    ui->tableWidget_5->setItem(rowCount,1, columnItem1);
                    ui->tableWidget_5->setItem(rowCount,2, columnItem2);
                    ui->tableWidget_5->setItem(rowCount,3, columnItem3);
                    ui->tableWidget_5->setItem(rowCount,4, columnItem4);

                        }
                    }

                for(int i=0;i<ui->tableWidget_5->rowCount();i++)
                {
                    for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                    {
                        item = ui->tableWidget_5->item(i,j);
                        item->setFlags(Qt::ItemIsEnabled);
                    }
                }

                QMessageBox::information(this,"提醒","删除成功！",QMessageBox::Ok);

        }
        else
        {
            qDebug() << "删除0";
            for(int i=0;i<ui->tableWidget_5->rowCount();i++)
            {
                for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                {
                    item = ui->tableWidget_5->item(i,j);
                    item->setFlags(Qt::ItemIsEnabled);
                }
            }
            QMessageBox::information(this,"警告","删除失败！",QMessageBox::Ok);
        }

        qDebug() << "delete";

    });


    menu.exec(QCursor::pos());
}

void FirstWindow::refreshStationInfo()
{
    QSqlQuery query(db);
            if(query.exec("select name,ip,data1,data2,data3 from station"))
            {
               ui->tableWidget_5->clearContents();
               ui->tableWidget_5->setRowCount(0);

                while(query.next())
                {
                    int rowCount = ui->tableWidget_5->rowCount();


                    ui->tableWidget_5->insertRow(rowCount);

                    QTableWidgetItem *columnItem0 = new QTableWidgetItem(
                                query.value(0).toString());

                    QTableWidgetItem *columnItem1 = new QTableWidgetItem(
                                query.value(1).toString());

                    QTableWidgetItem *columnItem2 = new QTableWidgetItem(
                                query.value(2).toString());

                    QTableWidgetItem *columnItem3 = new QTableWidgetItem(
                                query.value(3).toString());

                    QTableWidgetItem *columnItem4 = new QTableWidgetItem(
                                query.value(4).toString());


                    ui->tableWidget_5->setItem(rowCount,0, columnItem0);
                    ui->tableWidget_5->setItem(rowCount,1, columnItem1);
                    ui->tableWidget_5->setItem(rowCount,2, columnItem2);
                    ui->tableWidget_5->setItem(rowCount,3, columnItem3);
                    ui->tableWidget_5->setItem(rowCount,4, columnItem4);

                }



                for(int i=0;i<ui->tableWidget_5->rowCount();i++)
                {
                    for(int j=0;j<ui->tableWidget_5->columnCount();j++)
                    {
                        item = ui->tableWidget_5->item(i,j);
                        item->setFlags(Qt::ItemIsEnabled);
                    }
                }
            }
}

void FirstWindow::MenuUserSlots()
{
    customTableWidget *custom = new customTableWidget();
    custom->sendInitialQuest(quint8(0x00));

    qRegisterMetaType<QVector<QVector<QString> >>("QVector<QVector<QString>>");

    pageUserManage = new UserManage();
    connect(worker,&receieveData::sendAddUserResult,pageUserManage,&UserManage::sendAddUserResult);
    connect(pageUserManage,&UserManage::disconnectUserManage,this,&FirstWindow::disconnectUserManage);
    qDebug() << "连接信号";
    pageUserManage->show();
}

void FirstWindow::MenuStationSlots()
{
    customTableWidget *custom = new customTableWidget();
    custom->sendInitialQuest(quint8(0x01));

    qRegisterMetaType<QVector<QVector<QString> >>("QVector<QVector<QString>>");

    pageStationManage = new StationManage();
    connect(worker,&receieveData::sendStationResult,pageStationManage,&StationManage::sendStationResult);
    connect(pageStationManage,&StationManage::disconnectStationManage,this,&FirstWindow::disconnectStationManage);
    pageStationManage->show();
}

void FirstWindow::MenuMissionSlots()
{
    MissionTableWidget *mission = new MissionTableWidget();
    mission->sendInitialQuest(quint8(0x02));

    qRegisterMetaType<QVector<QVector<QString> >>("QVector<QVector<QString>>");

    pageMissionManage = new MissionManage();
    connect(worker,&receieveData::sendMissionResult,pageMissionManage,&MissionManage::sendMissionResult);
    connect(worker,&receieveData::sendMissionInitial,pageMissionManage,&MissionManage::sendMissionInitial);
    connect(pageMissionManage,&MissionManage::disconnectMissionManage,this,&FirstWindow::disconnectMissionManage);
    pageMissionManage->show();
}

void FirstWindow::MenuGeshanSlots()
{
    pageGeManage = new GeManage();
    pageGeManage->show();
}

void FirstWindow::MenuDirectorySlots()
{
    dire->show();
}

void FirstWindow::MenuJidaiSlots()
{
    customTableWidget *custom = new customTableWidget();
    custom->sendInitialQuest(quint8(0x03));


    qRegisterMetaType<QVector<QVector<QString> >>("QVector<QVector<QString>>");

    BaseBandManage *baseBandManage = new BaseBandManage();
    connect(worker,&receieveData::sendBaseBandResult,baseBandManage,&BaseBandManage::sendBaseBandResult);
    connect(baseBandManage,&BaseBandManage::disconnectBaseBandManage,this,&FirstWindow::disconnectBaseBandManage);
    qDebug() << "连接信号";
    baseBandManage->show();
}

void FirstWindow::MenuDatasourceSlots()
{
    customTableWidget *custom = new customTableWidget();
    custom->sendInitialQuest(quint8(0x04));

    qRegisterMetaType<QVector<QVector<QString> >>("QVector<QVector<QString>>");

    DataSourceManage *dataSourceManage = new DataSourceManage();
    connect(worker,&receieveData::sendDataSourceResult,dataSourceManage,&DataSourceManage::sendDataSourceResult);
    connect(dataSourceManage,&DataSourceManage::disconnectDataSourceManage,this,&FirstWindow::disconnectDataSourceManage);
    qDebug() << "连接信号";
    dataSourceManage->show();
}

void FirstWindow::outSocketRead()
{
    QHostAddress addr;
    quint16 port;
    QByteArray arr;
    while (testOutSocket->hasPendingDatagrams()) //数据报等待被读取
    {
        quint64 pend = testOutSocket->pendingDatagramSize();
        arr.resize(pend);
        int x = testOutSocket->readDatagram(arr.data(),arr.size(),&addr,&port);
        QString arrst = arr;
        if(arrst == QString("ping")){
            for(int i=0;i<mutiFile.size();i++){
                if(mutiFile.at(i)->stationIp==QHostAddress(addr.toIPv4Address()).toString()){
                    mutiFile.at(i)->packgeGet = mutiFile.at(i)->packgeGet+1;
                }
            }
        }
    }
}

void FirstWindow::initialTimer()
{
    for(int i=0;i<mutiFile.size();i++){
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout,[=](){

            double lostRate = (1.0-(mutiFile.at(i)->packgeGet/10.0))*100;
            QString lostRateStr = QString::number(lostRate);
            QTableWidgetItem *item = new QTableWidgetItem(lostRateStr);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            if(ui->tableWidget_2->item(i,2)!=nullptr){
                if(ui->tableWidget_2->item(i,2)->text()!="100"&&item->text()=="100"){
                    QMessageBox::critical(this,"警告",QString("%1连接已断开").arg(ui->tableWidget_2->item(i,0)->text()));
                }
            }
            ui->tableWidget_2->setItem(i,2,item);
            mutiFile.at(i)->packgeGet=0;
            QByteArray arr;
            arr.append("ping");
            QHostAddress addr;
            addr.setAddress(mutiFile.at(i)->stationIp);
            testOutSocket->writeDatagram(arr,addr,9013);
        });
        timer->start(1000);
    }

}

//void FirstWindow::on_tableWidget_6_customContextMenuRequested(const QPoint &pos)
//{
//    qDebug() << "编辑删除编辑删除";
//        QMenu menu;
//        QAction *change = menu.addAction(tr("编辑"));
//        menu.addSeparator();
//        QAction *deleteUser = menu.addAction(tr("删除"));

//        connect(change, &QAction::triggered, [=]()
//        {
//            isedit2 = 1;
//            qDebug() << "change";
//            int row = ui->tableWidget_6->currentRow();
//            rowEdit2 = row;
//            qDebug() << row;
//            for(int i=0;i<ui->tableWidget_6->rowCount();i++){
//                for(int j=0;j<ui->tableWidget_6->columnCount();j++){
//                    o = ui->tableWidget_6->item(i,j);
//                    o->setFlags(Qt::ItemIsEditable|o->flags());//可编辑
//                }
//            }

//            for(int i=0;i<ui->tableWidget_6->rowCount();i++){
//                for(int j=0;j<ui->tableWidget_6->columnCount();j++){
//                    if(i!=row){
//                        o = ui->tableWidget_6->item(i,j);
//      //                o->setFlags(Qt::ItemIsEnabled|o->flags());
//                        o->setFlags(Qt::ItemIsEnabled);
//                        qDebug() << i << j;
//                    }
//                }
//            }

//            oldmissionNode = ui->tableWidget_6->item(row,0)->text();
//            connect(ui->tableWidget_6,SIGNAL(cellClicked(int,int)),this,SLOT(cellClickedSlot2(int,int)));
//            //获取原先的数据
//            //获取qtablewidget的单击信号
//            //如果信号不在所编辑的那一行，获取新的内容，校验所编辑的姓名是否合法
//            //如果合法，更新数据库内容
//            //反之恢复数据到原始状态，并重新设置所有为不可编辑状态

//        });


//        connect(deleteUser, &QAction::triggered, [=]()
//        {
//            int row = ui->tableWidget_6->currentRow();
//            QString missionNode = ui->tableWidget_6->item(row,0)->text();
//            QSqlQuery query(db);
//            QString qs = QString("delete from missiontable where missionNode ='%1'").arg(missionNode);
//            qDebug() << missionNode;
//            if(query.exec(qs))
//            {
//                qDebug() << "删除1";

//                if(query.exec("select missionNode,param1,param2,param3,param4,param5 from missiontable"))
//                {
//                   ui->tableWidget_6->clearContents();
//                   ui->tableWidget_6->setRowCount(0);

//                    while(query.next())
//                    {
//                        int rowCount = ui->tableWidget_6->rowCount();


//                        ui->tableWidget_6->insertRow(rowCount);

//                        QTableWidgetItem *columnItem1 = new QTableWidgetItem(query.value(1).toString());

//                        QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                                  query.value(0).toString());

//                        QTableWidgetItem *columnItem2 = new QTableWidgetItem(
//                                  query.value(2).toString());

//                        QTableWidgetItem *columnItem3 = new QTableWidgetItem(
//                                  query.value(3).toString());

//                        QTableWidgetItem *columnItem4 = new QTableWidgetItem(
//                                  query.value(4).toString());

//                        QTableWidgetItem *columnItem5 = new QTableWidgetItem(
//                                  query.value(5).toString());

//                        ui->tableWidget_6->setItem(rowCount,0, columnItem0);
//                        ui->tableWidget_6->setItem(rowCount,1, columnItem1);
//                        ui->tableWidget_6->setItem(rowCount,2, columnItem2);
//                        ui->tableWidget_6->setItem(rowCount,3, columnItem3);
//                        ui->tableWidget_6->setItem(rowCount,4, columnItem4);
//                        ui->tableWidget_6->setItem(rowCount,5, columnItem5);

//                    }
//                }

//                for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//                {
//                    for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                    {
//                        o = ui->tableWidget_6->item(i,j);
//                        o->setFlags(Qt::ItemIsEnabled);
//                    }
//                }

//                QMessageBox::information(this,"提醒","删除成功！",QMessageBox::Ok);

//            }
//            else
//            {
//                qDebug() << "删除0";
//                for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//                {
//                    for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                    {
//                        o = ui->tableWidget_6->item(i,j);
//                        o->setFlags(Qt::ItemIsEnabled);
//                    }
//                }
//                QMessageBox::information(this,"警告","删除失败！",QMessageBox::Ok);
//            }

//            qDebug() << "delete";

//        });
//        menu.exec(QCursor::pos());
//}

//void FirstWindow::on_pushButton_15_clicked()
//{
//    QString input=ui->lineEdit_3->text();
//        int row_num=ui->tableWidget_6->rowCount();
//        if (input=="")//判断是否是空，如果是空就显示所有行
//        {
//            QSqlQuery query(db);
//                    if(query.exec("select missionNode,param1,param2,param3,param4,param5 from missiontable"))
//                    {
//                       ui->tableWidget_6->clearContents();
//                       ui->tableWidget_6->setRowCount(0);

//                        while(query.next())
//                        {
//                            int rowCount = ui->tableWidget_6->rowCount();


//                            ui->tableWidget_6->insertRow(rowCount);

//                            QTableWidgetItem *columnItem1 = new QTableWidgetItem(
//                                        query.value(1).toString());
//                            QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                                        query.value(0).toString());

//                            QTableWidgetItem *columnItem2 = new QTableWidgetItem(
//                                        query.value(2).toString());

//                            QTableWidgetItem *columnItem3 = new QTableWidgetItem(
//                                        query.value(3).toString());
//                            QTableWidgetItem *columnItem4 = new QTableWidgetItem(
//                                        query.value(4).toString());
//                            QTableWidgetItem *columnItem5 = new QTableWidgetItem(
//                                        query.value(5).toString());

//                            ui->tableWidget_6->setItem(rowCount,0, columnItem0);
//                            ui->tableWidget_6->setItem(rowCount,1, columnItem1);
//                            ui->tableWidget_6->setItem(rowCount,2, columnItem2);
//                            ui->tableWidget_6->setItem(rowCount,3, columnItem3);
//                            ui->tableWidget_6->setItem(rowCount,4, columnItem4);
//                            ui->tableWidget_6->setItem(rowCount,5, columnItem5);
//                        }



//                        for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//                        {
//                            for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                            {
//                                o = ui->tableWidget_6->item(i,j);
//                                o->setFlags(Qt::ItemIsEnabled);
//                            }
//                        }
//                    }
//        }
//        else
//        {
//            QList <QTableWidgetItem *> item = ui->tableWidget_6->findItems(input, Qt::MatchContains);
//            for(int i=0;i<row_num;i++)
//            {
//                ui->tableWidget_6->setRowHidden(i,true);//隐藏

//            }
//            //判断符合条件索引是不是空
//            if(!item.empty())
//            {
//                for(int i=0;i<item.count();i++)
//                {
//                    ui->tableWidget_6->setRowHidden(item.at(i)->row(),false);

//                }
//            }
//        }
//}


//void FirstWindow::cellClickedSlot2(int x, int y)
//{
//    // 判断x是不是所编辑的那一行，如果不是，就取出它所编辑的所有数据，校验，成功后提示修改成功，失败后提示失败原因
//    qDebug() << "编辑编辑编辑";

//    if(rowEdit2!=x && isedit2 == 1)
//    {
//        QString missionNode = ui->tableWidget_6->item(rowEdit2,0)->text();
//        QString param1 = ui->tableWidget_6->item(rowEdit2,1)->text();
//        QString param2 = ui->tableWidget_6->item(rowEdit2,2)->text();
//        QString param3 = ui->tableWidget_6->item(rowEdit2,3)->text();
//        QString param4 = ui->tableWidget_6->item(rowEdit2,4)->text();
//        QString param5 = ui->tableWidget_6->item(rowEdit2,5)->text();

//        QSqlQuery query(db);
//        QString qs = QString("update missiontable missionNode ='%1',param1 ='%2',param2 = '%3',param3 = '%4',param4 = '%5',param5 = '%6'where missionNode ='%6'").arg(missionNode).arg(param1).arg(param2).arg(param3).arg(param4).arg(param5).arg(oldmissionNode);

//        if(query.exec(qs))
//        {
//            QMessageBox::information(this,"提醒","修改成功！",QMessageBox::Ok);

//            for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//            {
//                for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                {
//                    o = ui->tableWidget_6->item(i,j);
//                    o->setFlags(Qt::ItemIsEnabled);
//                }
//            }
//            qDebug() << "1";
//        }
//        else
//        {
//            QMessageBox::information(this,"警告","重复，修改失败！",QMessageBox::Ok);
//            QTableWidgetItem *item1 = new QTableWidgetItem(oldmissionNode);
//            ui->tableWidget_6->setItem(rowEdit2,0,item1);

//            for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//            {
//                for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//                {
//                    o = ui->tableWidget_6->item(i,j);
//                    o->setFlags(Qt::ItemIsEnabled);
//                }
//            }
//            qDebug() << "0";
//        }

//        if(query.exec("select missionNode,param1,param2,param3,param4,param5 from missiontable"))
//        {
//           ui->tableWidget_6->clearContents();
//           ui->tableWidget_6->setRowCount(0);

//            while(query.next())
//            {
//                int rowCount = ui->tableWidget_6->rowCount();


//                ui->tableWidget_6->insertRow(rowCount);

//                QTableWidgetItem *columnItem1 = new QTableWidgetItem(query.value(1).toString());

//                QTableWidgetItem *columnItem0 = new QTableWidgetItem(
//                          query.value(0).toString());

//                QTableWidgetItem *columnItem2 = new QTableWidgetItem(
//                          query.value(2).toString());

//                QTableWidgetItem *columnItem3 = new QTableWidgetItem(
//                          query.value(3).toString());

//                QTableWidgetItem *columnItem4 = new QTableWidgetItem(
//                          query.value(4).toString());

//                QTableWidgetItem *columnItem5 = new QTableWidgetItem(
//                          query.value(5).toString());

//                ui->tableWidget_6->setItem(rowCount,0, columnItem0);
//                ui->tableWidget_6->setItem(rowCount,1, columnItem1);
//                ui->tableWidget_6->setItem(rowCount,2, columnItem2);
//                ui->tableWidget_6->setItem(rowCount,3, columnItem3);
//                ui->tableWidget_6->setItem(rowCount,4, columnItem4);
//                ui->tableWidget_6->setItem(rowCount,5, columnItem5);

//            }
//        }

//        for(int i=0;i<ui->tableWidget_6->rowCount();i++)
//        {
//            for(int j=0;j<ui->tableWidget_6->columnCount();j++)
//            {
//                o = ui->tableWidget_6->item(i,j);
//                o->setFlags(Qt::ItemIsEnabled);
//            }
//        }
//    }
//    isedit2 = 0;
//}


void FirstWindow::disconnectUserManage()
{
    // 断开信号与槽连接
    qDebug() << "信号断开";
    pageUserManage = new UserManage();
    disconnect(worker, &receieveData::sendAddUserResult,nullptr,nullptr);
}

void FirstWindow::disconnectStationManage()
{
    // 断开信号与槽连接
    qDebug() << "信号断开";
    pageStationManage = new StationManage();
    disconnect(worker, &receieveData::sendStationResult,nullptr,nullptr);
}

void FirstWindow::disconnectMissionManage()
{
    // 断开信号与槽连接
    qDebug() << "信号断开";
    pageMissionManage = new MissionManage();
    disconnect(worker, &receieveData::sendMissionResult,nullptr,nullptr);
}

void FirstWindow::disconnectBaseBandManage()
{
    // 断开信号与槽连接
    qDebug() << "信号断开";
    BaseBandManage *baseBandManage = new BaseBandManage();
    disconnect(worker,&receieveData::sendBaseBandResult,nullptr,nullptr);
}

void FirstWindow::disconnectDataSourceManage()
{
    // 断开信号与槽连接
    qDebug() << "信号断开";
    DataSourceManage *dataSourceManage = new DataSourceManage();
    disconnect(worker,&receieveData::sendDataSourceResult,nullptr,nullptr);
}

void FirstWindow::refreshHealthData(QList<HealthData *> list)
{
    ui->tableWidget_2->setRowCount(list.size());
    for(int i=0;i<list.size();i++){
        if(ui->tableWidget_2->item(i,0)==nullptr){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->name);

            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget_2->setItem(i,0,item);
        }else{
            ui->tableWidget_2->item(i,0)->setText(list.at(i)->name);
        }
        if(ui->tableWidget_2->item(i,1)==nullptr){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->delay);

            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget_2->setItem(i,1,item);
        }else{
            ui->tableWidget_2->item(i,1)->setText(list.at(i)->delay);
        }
        if(ui->tableWidget_2->item(i,2)==nullptr){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->lost);

            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget_2->setItem(i,2,item);
        }else{
            ui->tableWidget_2->item(i,2)->setText(list.at(i)->lost);
        }
        if(ui->tableWidget_2->item(i,3)==nullptr){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->status);

            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget_2->setItem(i,3,item);
        }else{
            ui->tableWidget_2->item(i,3)->setText(list.at(i)->status);
        }
        if(ui->tableWidget_2->item(i,3)->text()=="良好"){
            ui->tableWidget_2->item(i,3)->setIcon(QIcon(":/image/greenlight.png"));
        }else if(ui->tableWidget_2->item(i,3)->text()=="拥堵"){
            ui->tableWidget_2->item(i,3)->setIcon(QIcon(":/image/yellowlight.png"));
        }else{
            ui->tableWidget_2->item(i,3)->setIcon(QIcon(":/image/redlight.png"));
        }

        if(ui->tableWidget_2->item(i,4)==nullptr){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->dataIn);

            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget_2->setItem(i,4,item);
        }else{
            ui->tableWidget_2->item(i,4)->setText(list.at(i)->dataIn);
        }
        if(ui->tableWidget_2->item(i,4)->text()=="已流入"){
            ui->tableWidget_2->item(i,4)->setIcon(QIcon(":/image/greenlight.png"));
        }else{
            ui->tableWidget_2->item(i,4)->setIcon(QIcon(":/image/redlight.png"));
        }

    }
}

void FirstWindow::testPackgeSocketSlot()
{
    while (testPackgeSocket->hasPendingDatagrams()) //数据报等待被读取
    {
        QByteArray arr;
        quint64 pend = testPackgeSocket->pendingDatagramSize();
        arr.resize(pend);
        int x = testPackgeSocket->readDatagram(arr.data(),arr.size());
        QString arrst = arr;
        if(arrst == QString("ping")){
            for(int i=0;i<10;i++){
                QByteArray ar;
                ar.append("ping");
                QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
                testPackgeSocket->writeDatagram(ar,*addr,9012);
            }
        }
    }
}

void FirstWindow::getDataMd5(QByteArray array)
{
    grilleWorker->md5 = array;
    qDebug() << "再次发送的文件名" << grilleWorker->fileName;
    udpsocket->writeDatagram(getInvert(AgreeMent::Datamd5StorgeFinish(grilleWorker->fileName,0,grilleWorker->parentString)),QHostAddress(ConfigInfo::centerIp),ConfigInfo::centerUdpPort);
}

void FirstWindow::getDianziMd5(QByteArray array)
{
    grilleWorker->md5 = array;
    qDebug() << "再次发送的文件名" << grilleWorker->fileName;
    udpsocket->writeDatagram(getInvert(AgreeMent::Dianzimd5StorgeFinish(grilleWorker->parentString,grilleWorker->fileName)),QHostAddress(ConfigInfo::centerIp),ConfigInfo::centerUdpPort);
}
