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
#include "sendfile/sendfile.h"
#include "station.h"
#include "Config/configinfo.h"
#include "agreement/agreement.h"
#include "healthdata.h"
#include "geshan.h"
#include "childfile.h"
#include "remotedata.h"
#include "filelog.h"
#include "head.h"
#include <QRandomGenerator>
#include "baseband.h"
#include <iostream>
#include <stdexcept>
#include <QProcess>


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
QList<Station*> FirstWindow::stations;

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred";
    }
};

void throwException() {
    throw MyException();
}

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{

    ui->setupUi(this);
    AgreeMent::sendAllMissionInfo();
    qDebug() << "执行完";

    initialAllCustomTableWidget();
    initialMenuSlots();
    initial_multiFile();

//    ui->pushButton_7->hide();
    ui->pushButton_3->hide();
    ui->pushButton_11->hide();

//    ui->widget->hide();
//    ui->pushButton_6->hide();
    packageLength = 0;

    printfile();
    initialtcp();
    initialAllDownloadTcp();

    testDelay();
    initialTimer();

    connect(ui->pushButton_9,&QPushButton::clicked,this,&FirstWindow::logButtonPush);

    connect(&currentTimer,SIGNAL(timeout()), this, SLOT(handleCurrentTime()));
    currentTimer.start(1000);

    QRandomGenerator::securelySeeded();
    QRandomGenerator randomGenerator;
    ui->tableWidget_2->setRowCount(mutiFile.size());
    for(int i=0;i<mutiFile.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(mutiFile.at(i)->stationName);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(i,0,item);

        item = new QTableWidgetItem("未流入");
        QIcon *icon = new QIcon(":/image/greenlight.png");
        item->setIcon(*icon);
        ui->tableWidget_2->setItem(i,4,item);

        int xinzao = randomGenerator.bounded(70, 110);
        item = new QTableWidgetItem(QString::number(xinzao));
        ui->tableWidget_2->setItem(i,5,item);

        double randomFloat = randomGenerator.generateDouble() * (20 - 7) + 7;
        item = new QTableWidgetItem(QString::number(randomFloat));
        ui->tableWidget_2->setItem(i,6,item);

        randomFloat = randomGenerator.generateDouble() * (90 - 40) + 40;
        item = new QTableWidgetItem(QString::number(randomFloat));
        ui->tableWidget_2->setItem(i,7,item);

        randomFloat = randomGenerator.generateDouble() * (90 - 40) + 40;
        item = new QTableWidgetItem(QString::number(randomFloat));
        ui->tableWidget_2->setItem(i,8,item);

    }
//    printMission();


    QStringList headerList;
    headerList << "序号" << "任务名称" << "型号厂家" << "代号" << "处理平台"
                  << "显示平台" << "状态备注" << "解算程序" << "SETUP名称" << "是否硬件加密"
                  << "加密信息备注"<<"任务宏" << "显示画面版本" << "解算软件" << "备注"
                     << "版本更新时间" << "编制人";
    ui->widget_3->set_widget_column_header(headerList);
    ui->widget_3->set_database(QString("geshan"));
    QList<quint8> string_column_list;
    string_column_list << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10
                          << 11 << 12 << 13 << 14 << 15<< 16;
    ui->widget_3->set_string_column_number(string_column_list);
    ui->widget_3->set_primaryKeyIndex(0);
    ui->widget_3->set_fileIndex(13);
    ui->widget_3->set_resizeMode(QHeaderView::ResizeToContents);
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
    ui->widget_3->set_combobox_map(combobox_map);
    ui->widget_3->set_codeIndex(11);
    ui->widget_3->initial_widget();
    qDebug() << 1;
    qRegisterMetaType<QHostAddress>("QHostAddress");

    udpsocket = new QUdpSocket(this);
    bool isBindOk = udpsocket->bind(9001);
    if(!isBindOk){
        QMessageBox::information(this,"socket绑定信息","socket绑定端口失败,请确保9001端口开放");
        qApp->quit();
    }

    testOutSocket = new QUdpSocket(this);
    bool isBindOk2 = testOutSocket->bind(9012);
    if(!isBindOk2){
        QMessageBox::information(this,"socket绑定信息","socket绑定端口失败,请确保9012端口开放");
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
    connect(worker,&receieveData::sendDownLoadRuquest,this,&FirstWindow::getDownloadRequest);
    customTableWidget *custom = new customTableWidget();
    connect(worker,&receieveData::sendinfo,custom,&customTableWidget::sendInfo_slot);
    connect(worker,&receieveData::addNewGeshan,this,&FirstWindow::addNewGeshan);

    connect(worker,&receieveData::sendWenJianjia,this,&FirstWindow::getWenJianjia);
    connect(worker,&receieveData::sendDeleteGeshan,this,&FirstWindow::deleteGeshan);
    connect(worker,&receieveData::sendDeleteChild,this,&FirstWindow::deleteChild);

    connect(worker,&receieveData::sendAdvance,this,&FirstWindow::getAdvance);
    connect(worker,&receieveData::sendDataAdvance,this,&FirstWindow::getDataAdvance);
    connect(worker,&receieveData::sendGeshanAdvance,this,&FirstWindow::getGeshanAdvance);
    connect(worker,&receieveData::sendDataDownfileRequest,this,&FirstWindow::getDataDownloadRequest);
    connect(worker,&receieveData::sendDianziDownfileRequest,this,&FirstWindow::getDianziDownloadRequest);

    connect(worker,&receieveData::sendMd5ResultFileName,this,&FirstWindow::getmd5DataDownloadRequest);
    connect(worker,&receieveData::sendDianziMd5ResultFileName,this,&FirstWindow::getDianzimd5DataDownloadRequest);

    t->start();

    arraylin.resize(0);
    QIcon *icon = new QIcon(":/image/greenlight.png");


    connect(pro,&progress::finishFile,this,&FirstWindow::finishFile);

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget->setStyleSheet("font-size: 14pt;");
    ui->tableWidget->setAlternatingRowColors(true);

    ui->tableWidget_3->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white;border:2px solid white}");
    ui->tableWidget_3->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 19pt;color:white}");
    ui->tableWidget_3->setStyleSheet("font-size: 14pt;");
    ui->tableWidget_3->setAlternatingRowColors(true);

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

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setRowHeight(0,40);
    ui->tableWidget_4->verticalHeader()->setVisible(0);

    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_5->setRowHeight(0,40);
    ui->tableWidget_5->verticalHeader()->setVisible(0);


    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_4->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget_5->setContextMenuPolicy(Qt::CustomContextMenu);








    ui->tableWidget->verticalHeader()->setVisible(0);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setVisible(0);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(testSlot(int,int)));

    QListWidgetItem *item = new QListWidgetItem();
    QColor *color = new QColor();
    color->setRgb(0,170,0);
    item->setTextColor(*color);
    item->setText("服务启动");

    QFont font;
    font.setPointSize(19);

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

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0,150)); // 最后一项为透明度

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
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        setPushStyleSheet(ui->pushButton_4);
        setCommonStyleSheet(ui->pushButton);
        setCommonStyleSheet(ui->pushButton_3);
        setCommonStyleSheet(ui->pushButton_10);
        setCommonStyleSheet(ui->pushButton_2);
        setCommonStyleSheet(ui->pushButton_6);
        setCommonStyleSheet(ui->pushButton_7);
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
    });

    connect(ui->actionlogout,&QAction::triggered,[this](){
        MainWindow *p = new MainWindow;
        post();
        response = "";
        p->show();
        this->hide();
    });

    this->setWindowFlags(this->windowFlags()|Qt::WindowMaximizeButtonHint);
    this->setWindowState(Qt::WindowNoState);

    FirstWindow::stations = Station::selectAllStations();
    startSendAllSecondsInfo();
    sqlTimer = new QTimer(this);
    connect(sqlTimer, &QTimer::timeout,[=](){
        QSqlQuery query(db);
        QString qs = QString("select * from `missionnew2`");
        query.exec(qs);
        if(!db.isOpen()){
            db.open();
        }
    });
    sqlTimer->start(60000);

    ui->tableWidget_2->setColumnHidden(4, true);
    connect(ui->pushButton_15,&QPushButton::clicked,[=](){
        ui->listWidget->clear();
    });
    qDebug() <<3;

}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::start0803(int port)
{
    QUdpSocket *udpsocket0803 = new QUdpSocket(this);
    bool isBindOk = udpsocket0803->bind(port);
    if(!isBindOk){
        QMessageBox::information(this,"socket绑定信息","socket绑定0803端口失败,请确保端口开放");
        qApp->quit();
    }
    connect(udpsocket0803,&QUdpSocket::readyRead, [=](){
        while (udpsocket0803->hasPendingDatagrams()) //数据报等待被读取
        {
            quint64 socketava = udpsocket0803->bytesAvailable();
            quint64 pend = udpsocket0803->pendingDatagramSize();

            QByteArray arrjudge;
            arrjudge.resize(pend);
            int x = udpsocket0803->readDatagram(arrjudge.data(),arrjudge.size());

            QByteArray subArray = arrjudge.mid(10, 13);
            QDataStream stream(subArray);
            stream.setByteOrder(QDataStream::BigEndian);
            char planeName[13];
            stream.readRawData(planeName, 13);//飞机名

            QByteArray subArray2 = arrjudge.mid(23, 7);
            QDataStream stream2(subArray2);
            stream2.setByteOrder(QDataStream::BigEndian);
            char planeNo[7];
            stream2.readRawData(planeNo,7);//飞机号

            QByteArray subArray3 = arrjudge.mid(30, 2);
            QDataStream stream3(subArray3);
            stream3.setByteOrder(QDataStream::BigEndian);
            short flightNum;
            stream3 >> flightNum;//飞机号

            QByteArray subArray4 = arrjudge.mid(8, 2);
            QDataStream stream4(subArray4);
            stream4.setByteOrder(QDataStream::BigEndian);
            ushort streamNo;
            stream4 >> streamNo;//流序号
        }
    });
}

void FirstWindow::start1004(int port)
{
    QUdpSocket *udpsocket1004 = new QUdpSocket(this);
    bool isBindOk = udpsocket1004->bind(port);
    if(!isBindOk){
        QMessageBox::information(this,"socket绑定信息","socket绑定0803端口失败,请确保端口开放");
        qApp->quit();
    }
    connect(udpsocket1004,&QUdpSocket::readyRead, [=](){
        while (udpsocket1004->hasPendingDatagrams()) //数据报等待被读取
        {
            quint64 socketava = udpsocket1004->bytesAvailable();
            quint64 pend = udpsocket1004->pendingDatagramSize();

            QByteArray arrjudge;
            arrjudge.resize(pend);
            int x = udpsocket1004->readDatagram(arrjudge.data(),arrjudge.size());


            QByteArray subArray0 = arrjudge.mid(0, 4);
            QDataStream stream0(subArray0);
            stream0.setByteOrder(QDataStream::BigEndian);
            uint   packLen;
            stream0 >> packLen;//包长

            QByteArray subArray = arrjudge.mid(39, 4);
            QDataStream stream(subArray);
            stream.setByteOrder(QDataStream::BigEndian);
            uint    planeID;
            stream >> planeID;//飞机号

            QByteArray subArray4 = arrjudge.mid(8, 2);
            QDataStream stream4(subArray4);
            stream4.setByteOrder(QDataStream::BigEndian);
            ushort streamNo;
            stream4 >> streamNo;//流序号

            float hour1;
            float minute1;
            float second1;
            float millsecond1;

            QByteArray subArray5 = arrjudge.mid(56, 4);
            QDataStream stream5(subArray5);
            stream5.setByteOrder(QDataStream::BigEndian);
            stream5 >> hour1;//时

            QByteArray subArray6 = arrjudge.mid(60, 4);
            QDataStream stream6(subArray6);
            stream6.setByteOrder(QDataStream::BigEndian);
            stream6 >> minute1;//流序号

            QByteArray subArray7 = arrjudge.mid(64, 4);
            QDataStream stream7(subArray7);
            stream7.setByteOrder(QDataStream::BigEndian);
            stream7 >> second1;//流序号

            QByteArray subArray8 = arrjudge.mid(68, 4);
            QDataStream stream8(subArray8);
            stream8.setByteOrder(QDataStream::BigEndian);
            stream8 >> millsecond1;//流序号

            float hour2;
            float minute2;
            float second2;
            float millsecond2;

            QByteArray subArray9 = arrjudge.mid(72, 4);
            QDataStream stream9(subArray9);
            stream9.setByteOrder(QDataStream::BigEndian);
            stream9 >> hour2;//时

            QByteArray subArray10 = arrjudge.mid(76, 4);
            QDataStream stream10(subArray10);
            stream10.setByteOrder(QDataStream::BigEndian);
            stream10 >> minute2;//流序号

            QByteArray subArray11 = arrjudge.mid(80, 4);
            QDataStream stream11(subArray11);
            stream11.setByteOrder(QDataStream::BigEndian);
            stream11 >> second2;//流序号

            QByteArray subArray12 = arrjudge.mid(84, 4);
            QDataStream stream12(subArray12);
            stream12.setByteOrder(QDataStream::BigEndian);
            stream12 >> millsecond2;//流序号

            uint restLen = packLen - 88;
            QByteArray arrayLast = arrjudge.mid(88, restLen);
            QDataStream streamlast(arrayLast);
            streamlast.setByteOrder(QDataStream::BigEndian);
            int num = 1;
            while(restLen!=0){
                QString fileName = ConfigInfo::headPath+"/"+QString::number(num)+".txt";
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    qDebug() << "Failed to open file for writing.";
                    return -1;
                }

                // 创建一个 QTextStream 对象，用于写入数据
                QTextStream stream(&file);

                // 写入数据到文件
                stream << hour1 << minute1 << second1 <<millsecond1;
                stream << hour2 << minute2 << second2 <<millsecond2;
                uint singleData;
                streamlast >> singleData;
                stream << singleData << "/n";
                num++;
            }
        }
    });
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
}

void FirstWindow::initialMenuSlots()
{
    connect(ui->actionuser,&QAction::triggered,this,&FirstWindow::MenuUserSlots);
    connect(ui->actionji,&QAction::triggered,this,&FirstWindow::MenuStationSlots);
    connect(ui->actionhong,&QAction::triggered,this,&FirstWindow::MenuMissionSlots);
//    connect(ui->actiongeshan,&QAction::triggered,this,&FirstWindow::MenuGeshanSlots);
    connect(ui->actiondirectory,&QAction::triggered,this,&FirstWindow::MenuDirectorySlots);
    connect(ui->actiondaochu,&QAction::triggered,[=](){
        QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
        if(directoryPath!=""){
            QString dateDir = directoryPath+QString("/1");
            QDir dir2;
            if (!dir2.mkdir(dateDir)) {
                qDebug() << "Failed to create folder";
            }else{
                qDebug() << "Folder created successfully";
            }

            QString dateDir3 = directoryPath+QString("/2");
            QDir dir3;
            if (!dir3.mkdir(dateDir3)) {
                qDebug() << "Failed to create folder";
            }else{
                qDebug() << "Folder created successfully";
            }
            copyFolder(ConfigInfo::datPath,dateDir);
            copyFolder(ConfigInfo::grillePath,dateDir3);
        }
        QMessageBox::information(this,"导出提示","导出成功");
    });
    connect(ui->actiondaoru,&QAction::triggered,[=](){
        QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
        if(directoryPath!=""){
            copyFolder(directoryPath+"/"+"1",ConfigInfo::datPath);
            copyFolder(directoryPath+"/"+"2",ConfigInfo::grillePath);
        }
        QMessageBox::information(this,"导出提示","导入成功");
    });
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
    int name = rec.indexOf("遥测站名");
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
    for(int i=0;i<mutiFile.size();i++){
        QThread *t = new QThread;
        worker3 = new DelayTest;
        worker3->setIp(mutiFile.at(i)->stationIp);
        worker3->moveToThread(t);
        connect(this,&FirstWindow::emitDelayTest,worker3,&DelayTest::delayTest);
        connect(worker3,&DelayTest::dalayReturn,this,&FirstWindow::getDelayReturn);
        t->start();

        mutiFile.at(i)->testDelaySocket->moveToThread(t);
        emit emitDelayTest(mutiFile.at(i));
    }
    delayTimer = new QTimer(this);
    connect(delayTimer,&QTimer::timeout,[=](){
        for(int i=0;i<mutiFile.size();i++){
            emit emitDelayTest(mutiFile.at(i));
        }
    });
    delayTimer->start(1000);

}

void FirstWindow::initialAllDownloadTcp()
{
    QList<Station*> list = Station::selectAllStations();
    for(int i=0;i<list.size();i++){
        QThread *t = new QThread;
        sendfile *sendFileWorker = new  sendfile();
        sendFileWorker->moveToThread(t);
        sendFileWorker->setAddr(list.at(i)->stationIp);
        sendFileWorker->setPort(ConfigInfo::grilleTcpPort);
        sendFileWorker->fileType =  sendfile::GRILLE;
        connect(this,&FirstWindow::startSendFile,sendFileWorker,& sendfile::sendFile);
        connect(this,&FirstWindow::startSendAbortFile,sendFileWorker,&sendfile::sendAbortFile);
        connect(this,&FirstWindow::startSendDianziFile,sendFileWorker,& sendfile::sendDianziFile);
        t->start();
    }

//    for(int i=0;i<list.size();i++){
//        QThread *t = new QThread;
//         sendfile *sendFileWorker = new  sendfile();
//        sendFileWorker->moveToThread(t);
//        sendFileWorker->setAddr(list.at(i)->stationIp);
//        sendFileWorker->setPort(ConfigInfo::displayTcpPort);
//        sendFileWorker->fileType =  sendfile::DISPLAY_FRAME;
//        connect(this,&FirstWindow::startSendFile,sendFileWorker,& sendfile::sendFile);
//        t->start();
//    }

}

void FirstWindow::startSendAllSecondsInfo()
{
    healthTimer = new QTimer(this);
    connect(healthTimer, SIGNAL(timeout()), this, SLOT(handleSendHealthDataSlot()));
    healthTimer->start(1000);
}

bool FirstWindow::copyFolder(const QString &srcFolderPath, const QString &destFolderPath)
{
    QDir srcDir(srcFolderPath);
        QDir destDir(destFolderPath);

        if (!srcDir.exists()) {
            qDebug() << "源文件夹不存在";
            return false;
        }

        if (!destDir.exists()) {
            destDir.mkdir(destFolderPath);
        }

        QStringList fileList = srcDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        foreach (const QString &fileName, fileList) {
            QString srcFilePath = srcDir.filePath(fileName);
            QString destFilePath = destDir.filePath(fileName);
            if (!QFile::copy(srcFilePath, destFilePath)) {
                qDebug() << "复制文件失败:" << srcFilePath;
                return false;
            }
        }

        QStringList subFolderList = srcDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (const QString &subFolder, subFolderList) {
            QString srcSubFolderPath = srcFolderPath + "/" + subFolder;
            QString destSubFolderPath = destFolderPath + "/" + subFolder;
            if (!copyFolder(srcSubFolderPath, destSubFolderPath)) {
                return false;
            }
        }

        return true;
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
    bool tcpListenOk = tcpServer->listen(QHostAddress::Any,9002);
    if(!tcpListenOk){
        QMessageBox::information(this,"绑定信息","9002端口绑定失败，请查看端口是否被占用");
        qApp->quit();
    }

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出等待链接的下一个socket
        qDebug() << "tcp连接请求";

        QTcpSocket *tcpSocket11;
        tcpSocket11 = tcpServer->nextPendingConnection();


        QHostAddress ip = tcpSocket11->peerAddress();
        quint16 port = tcpSocket11->peerPort();


        QString filename;
        quint64 filesize;
        int num;
        QString code;
        int type;
        QString parentPath;
        for(int i=0;i<mutiFile.size();i++){
            if(mutiFile.at(i)->stationIp == QHostAddress(ip.toIPv4Address()).toString()){
                qDebug() << mutiFile.at(i)->stationIp << QHostAddress(ip.toIPv4Address()).toString();
                filename = mutiFile.at(i)->filePath;
                filesize = mutiFile.at(i)->fileSize;
                type = mutiFile.at(i)->type;
                code = mutiFile.at(i)->code;
                parentPath = mutiFile.at(i)->parentPath;
                num = i;
                break;
            }
        }

        qInfo("用户: %s\t\t 基站%s开始传输%s", currentUser.toUtf8().constData(),mutiFile.at(num)->stationName.toUtf8().constData(),filename.toUtf8().constData());

        mutiFile.at(num)->socket = tcpSocket11;

        mutiFile.at(num)->t = new QThread;

        disconnect(this,&FirstWindow::sendWriteFile,mutiFile.at(num)->worker,&WriteFiledata::writeFile);
        mutiFile.at(num)->worker = new WriteFiledata;
        mutiFile.at(num)->worker->setType(type);
        mutiFile.at(num)->worker->setParentPath(parentPath);
        mutiFile.at(num)->worker->moveToThread(mutiFile.at(num)->t);
        if(mutiFile.at(num)->isgoon==1){
            mutiFile.at(num)->worker->setFile2(filename);
        }else{
            mutiFile.at(num)->worker->setFile(filename);
        }
        mutiFile.at(num)->worker->setFileSize(filesize);
        mutiFile.at(num)->worker->setNum(num);
        mutiFile.at(num)->worker->setCode(code);

        mutiFile.at(num)->t->start();
        connect(this,&FirstWindow::sendWriteFile,mutiFile.at(num)->worker,&WriteFiledata::writeFile);
        connect(mutiFile.at(num)->worker,&WriteFiledata::sentValue,pro,&progress::setFileValue);
        connect(mutiFile.at(num)->worker,&WriteFiledata::finishWrite,this,&FirstWindow::finishJudgeMd5);





         QMetaObject::Connection connection;

         connection = QObject::connect(tcpSocket11,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcpSocket11->readAll();
            QString getIp = QHostAddress(tcpSocket11->peerAddress().toIPv4Address()).toString();
            int numb;
            for(int i=0;i<mutiFile.size();i++){
                if(mutiFile.at(i)->stationIp==getIp){

                    if(mutiFile.at(i)->type == 1){
                        QString lin;
                        for(int i=0;i<array.size();i++){
                            lin.append(QString::number(quint16(array.at(i)),2));
                        }
                        ui->listWidget->addItem(lin);
                    }else{
                        numb=i;
                        emit sendWriteFile(array,numb);
                        break;
                    }
                }
            }

        });


         connect(tcpSocket11,&QTcpSocket::disconnected,[=](){
            qDebug() << "断开连接";
            disconnect(this,&FirstWindow::sendWriteFile,mutiFile.at(num)->worker,&WriteFiledata::writeFile);

            mutiFile.at(num)->socket->disconnect();

            mutiFile.at(num)->t->terminate();
            mutiFile.at(num)->t->quit();
            mutiFile.at(num)->t->deleteLater();

            mutiFile.at(num)->worker->disconnect();
            mutiFile.at(num)->worker->deleteLater();

        //            tcpSocket1->disconnectFromHost();

            // 使用deleteLater()函数来销毁socket对象
            mutiFile.at(num)->socket->deleteLater();
         });


//        connect(tcpSocket,&QTcpSocket::readyRead,[=](){

//            QByteArray arr = tcpSocket->readAll();

//            qDebug() << "打印传入值" << arr;
//            if(QString(arr).section("##",0,0) == QString("recsize")){
//                recsize = QString(arr).section("##",1,1).toInt();
//                qDebug() << "here" << recsize;
//            }


//            if(QString(arr)=="file done"){
//                QMessageBox::information(this,"finish","文件已全部发送完毕");
//                file.close();
//                recsize = 0;

//                tcpSocket->disconnectFromHost();
//                tcpSocket->close();
//            }
//        });

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

        }
        else
        {
            qDebug() << "用户被锁定";
        }
        }
}

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
                ui->tableWidget_3->setItem(i,j,new QTableWidgetItem(QDateTime::fromTime_t(query.value(j).toInt()).toString("hh:mm")));
            }else{
                QTableWidgetItem *Item = new QTableWidgetItem(
                            query.value(j).toString());
                ui->tableWidget_3->setItem(i,j,Item);
            }

        }
        i++;
    }
}

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

void FirstWindow::setPushStyleSheet(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(47, 64, 80);");
}

void FirstWindow::setCommonStyleSheet(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(87, 104, 120);");
}

void FirstWindow::getFinish(int num,QString filename,QString code)
{
    BattleForm *battleForm = new BattleForm();

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

    if(ui->tableWidget_2->item(mutiFile.indexOf(muti),1)!=nullptr){
        ui->tableWidget_2->item(mutiFile.indexOf(muti),1)->setText(QString::number(time));
    }else{
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(time));
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),1,item);
    }

    if(time<1000){
        QTableWidgetItem *item3 = new QTableWidgetItem("良好");
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item3->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),3,item3);
    }else if(time<5000){
        QTableWidgetItem *item3 = new QTableWidgetItem("拥堵");
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item3->flags());//选中变换蓝底
        ui->tableWidget_2->setItem(mutiFile.indexOf(muti),3,item3);
    }else{
        QTableWidgetItem *item3 = new QTableWidgetItem("极差");
        item3->setFlags(Qt::ItemIsEnabled);//不可编辑
        item3->setFlags(Qt::ItemIsSelectable|item3->flags());//选中变换蓝底
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

void FirstWindow::handleSendHealthDataSlot()
{
    QList<HealthData*> list;
    for(int i=0;i<ui->tableWidget_2->rowCount();i++){
        HealthData *data = new HealthData();
        if(ui->tableWidget_2->item(i,0)!=nullptr)  data->name = ui->tableWidget_2->item(i,0)->text();
        else data->name = "";
        if(ui->tableWidget_2->item(i,1)!=nullptr)  data->delay = ui->tableWidget_2->item(i,1)->text();
        else data->delay = "";
        if(ui->tableWidget_2->item(i,2)!=nullptr)  data->lost = ui->tableWidget_2->item(i,2)->text();
        else data->lost = "";
        if(ui->tableWidget_2->item(i,3)!=nullptr)  data->status = ui->tableWidget_2->item(i,3)->text();
        else data->status = "";
        if(ui->tableWidget_2->item(i,4)!=nullptr)  data->dataIn = ui->tableWidget_2->item(i,4)->text();
        else data->dataIn = "";
        list.append(data);
    }
    for(int i=0;i<stations.size();i++){
        QHostAddress *addr = new QHostAddress(stations.at(i)->stationIp);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendAllHealthData(list)),*addr,9051);
        delete addr;
    }
    for(int i=0;i<list.size();i++){
        delete list.at(i);
    }
}

void FirstWindow::getDownloadRequest(fileDownloadRquest *request)
{
//    qDebug() << "打印解析的文件信息" << request->fileName <<request->fileType;
//    if(request->fileType==0){
//        emit startSendFile( sendfile::GRILLE,request->stationIp,request->fileName,0);
//    }
//    if(request->fileType==1){
//        emit startSendFile( sendfile::DISPLAY_FRAME,request->stationIp,request->fileName,0);
//    }
}



void FirstWindow::finishJudgeMd5(int number,QString filename,QString missionCode)
{
    int i=number;

    mutiFile.at(i)->worker->file->close();
    QCryptographicHash hash(QCryptographicHash::Md5);
    if(!mutiFile.at(i)->worker->file->isOpen()){
        mutiFile.at(i)->worker->file->open(QIODevice::ReadOnly);
    }
    mutiFile.at(i)->worker->file->seek(0);

    hash.addData(mutiFile.at(i)->worker->file);
    if (hash.result() == mutiFile.at(i)->md5) {

        QHostAddress *addr = new QHostAddress(mutiFile.at(i)->stationIp);
        if(mutiFile.at(i)->type == 0){
//            getFinish(number,filename,missionCode);
            RemoteData *remoteData = new RemoteData();
            remoteData->code = missionCode;
            remoteData->fileName = filename;
            remoteData->fileSize = mutiFile.at(i)->worker->file->size();
            remoteData->time = QDateTime::currentDateTime().toTime_t();
            remoteData->model = MissionBasicInfo::selectGeshanByCode(missionCode);
            remoteData->user = mutiFile.at(i)->user;
            int ok = RemoteData::insertNewRemoteData(remoteData);
            FileLog *log = new FileLog();
            log->people = mutiFile.at(i)->user;
            log->time = QDateTime::currentDateTime().toTime_t();
            log->operation = 0;
            log->fileName = filename;
            int ok2 = FileLog::insertNewLog(log);
        }else if(mutiFile.at(i)->type == 2){
            ChildFile *childFile = new ChildFile();
            childFile->fileName = filename;
            childFile->fileSize = mutiFile.at(i)->worker->file->size();
            childFile->updatetime = QDateTime::currentDateTime().toTime_t();
            childFile->fileid = GeShan::selectFileidByWenjianjia(mutiFile.at(i)->parentPath);

            int ok =  ChildFile::insertNewInfo(childFile);
            FileLog *log = new FileLog();
            log->people = mutiFile.at(i)->user;
            log->time = QDateTime::currentDateTime().toTime_t();
            log->operation = 2;
            log->fileName = filename;
            int ok2 = FileLog::insertNewLog(log);
            qDebug() << "执行第二个函数" << ok;
        }else if(mutiFile.at(i)->type == 3){
            qDebug() << mutiFile.at(i)->worker->file->fileName() << mutiFile.at(i)->parentPath << mutiFile.at(i)->worker->file->size();
            int ok = GeShan::insertDianziByWenjianjia(mutiFile.at(i)->filePath,mutiFile.at(i)->parentPath,mutiFile.at(i)->worker->file->size());
            qDebug() << "执行第三个函数" << ok;

            QList<GeShan*> geshanList;
            geshanList = GeShan::selectAllGeshan();
            qDebug() << "格栅大小" << geshanList.size();
            FileLog *log = new FileLog();
            log->people = mutiFile.at(i)->user;
            log->time = QDateTime::currentDateTime().toTime_t();
            log->operation = 2;
            log->fileName = filename;
            int ok2 = FileLog::insertNewLog(log);
            udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGeShan(geshanList)),*addr,9051);
        }else if(mutiFile.at(i)->type == 4){
            qDebug() << mutiFile.at(i)->worker->file->fileName() << mutiFile.at(i)->parentPath << mutiFile.at(i)->worker->file->size();
            int ok = GeShan::insertXianshiByWenjianjia(mutiFile.at(i)->filePath,mutiFile.at(i)->parentPath,mutiFile.at(i)->worker->file->size());
            qDebug() << "执行第三个函数" << ok;

            QList<GeShan*> geshanList;
            geshanList = GeShan::selectAllGeshan();
            qDebug() << "格栅大小" << geshanList.size();
            FileLog *log = new FileLog();
            log->people = mutiFile.at(i)->user;
            log->time = QDateTime::currentDateTime().toTime_t();
            log->operation = 2;
            log->fileName = filename;
            int ok2 = FileLog::insertNewLog(log);
            udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGeShan(geshanList)),*addr,9051);
        }

        qDebug() << "校验成功" << mutiFile.at(i)->stationIp << mutiFile.at(i)->md5;
        qDebug() << "校验成功" << mutiFile.at(i)->stationIp << hash.result();

        qDebug() << "销毁";
        disconnect(this,&FirstWindow::sendWriteFile,mutiFile.at(i)->worker,&WriteFiledata::writeFile);
        mutiFile.at(i)->worker->disconnect();
        mutiFile.at(i)->socket->disconnect();
        mutiFile.at(i)->t->quit();
        mutiFile.at(i)->t->terminate();
        mutiFile.at(i)->t->deleteLater();
        mutiFile.at(i)->worker->deleteLater();
        mutiFile.at(i)->socket->deleteLater();

        udpsocket->writeDatagram(getInvert(AgreeMent::sendMd5Result(1)),*addr,9051);

    }else{
        qDebug() << "校验失败" << mutiFile.at(i)->stationIp << mutiFile.at(i)->md5;
        qDebug() << "校验失败" << mutiFile.at(i)->stationIp << hash.result();

        qDebug() << "销毁";
        disconnect(this,&FirstWindow::sendWriteFile,mutiFile.at(i)->worker,&WriteFiledata::writeFile);
        mutiFile.at(i)->worker->disconnect();
        mutiFile.at(i)->socket->disconnect();
        mutiFile.at(i)->t->quit();
        mutiFile.at(i)->t->terminate();
        mutiFile.at(i)->t->deleteLater();
        mutiFile.at(i)->worker->deleteLater();
        mutiFile.at(i)->socket->deleteLater();

        QHostAddress *addr = new QHostAddress(mutiFile.at(i)->stationIp);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendMd5Result(0)),*addr,9051);
    }

}

void FirstWindow::addNewGeshan(GeShan *geshan,QHostAddress addr)
{
    int ok = GeShan::insertNewGeshan(geshan);
    if(ok){
        qDebug() << "格栅插入成功";
        QString dateDir = ConfigInfo::grillePath+"/"+QString(geshan->jiesuanruanjianwenjianjia);
        QDir dir2;
        if (!dir2.mkdir(dateDir)) {
            qDebug() << "Failed to create folder";
            qDebug() << dateDir;
        }else{
            qDebug() << "Folder created successfully";
        }
        udpsocket->writeDatagram(getInvert(AgreeMent::addGeshanComplete()),addr,9051);
    }else{
        qDebug() << "格栅插入失败";
        udpsocket->writeDatagram(getInvert(AgreeMent::addGeshanWrong()),addr,9051);
    }
}

void FirstWindow::getWenJianjia(QString wenJianjia,QHostAddress addr)
{
    int id = GeShan::selectFileidByWenjianjia(wenJianjia);
    QList<ChildFile*> list = ChildFile::selectByFileid(id);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllChildfile(list,wenJianjia)),addr,9051);
}

void FirstWindow::deleteGeshan(QString geshan,QHostAddress addr)
{
    int ok = GeShan::deleteGeshan(geshan);
    QList<GeShan*> geshanList;
    geshanList = GeShan::selectAllGeshan();
    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGeShan(geshanList)),addr,9051);
}

void FirstWindow::deleteChild(ChildFile *childFile,QHostAddress addr)
{
    int fileid = GeShan::selectFileidByWenjianjia(childFile->parentString);
    int ok = ChildFile::deleteChildFileByFileidAndName(childFile->fileName,fileid);
    if(ok){
        int id = GeShan::selectFileidByWenjianjia(childFile->parentString);
        QList<ChildFile*> list = ChildFile::selectByFileid(id);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendAllChildfile(list,childFile->parentString)),addr,9051);
    }

    qDebug() <<"删除子" << ok;
}

void FirstWindow::getAdvance(Advance *advance, QHostAddress addr)
{
    QList<MissionBasicInfo*> basic = MissionBasicInfo::selectByAdvance(advance);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendAdvanceResult(basic)),addr,9051);
}

void FirstWindow::getDataAdvance(DataAdvance *advance, QHostAddress addr)
{
    QList<RemoteData *> remote = RemoteData::selectByAdvance(advance);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendDataAdvanceResult(remote)),addr,9051);
}

void FirstWindow::getGeshanAdvance(GeshanAdvance *advance, QHostAddress addr)
{
    QList<GeShan *> geshan = GeShan::selectAllGeshanByAdvance(advance);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGeShan(geshan)),addr,9051);
}

void FirstWindow::getDataDownloadRequest(FileInfo *info, QString ip)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    QFile *file = new QFile();
    file->setFileName(ConfigInfo::datPath+"/"+info->parentPath+"/"+ info->fileName);
    file->open(QIODevice::ReadOnly);

    hash.addData(file);

    qDebug() << "文件md5?" << hash.result();
    FileLog *log = new FileLog();
    log->people = info->user;
    log->time = QDateTime::currentDateTime().toTime_t();
    log->operation = 1;
    log->fileName = info->fileName;
    int ok2 = FileLog::insertNewLog(log);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendDataMd5(hash.result())),QHostAddress(ip),9051);
    file->close();


}

void FirstWindow::getDianziDownloadRequest(ChildFile *childFile, QString ip)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    QFile *file = new QFile();
    file->setFileName(ConfigInfo::grillePath+"/"+childFile->parentString+"/"+childFile->fileName);
    file->open(QIODevice::ReadOnly);

    hash.addData(file);

    qDebug() << "文件md5?" << hash.result();
    FileLog *log = new FileLog();
    log->people = childFile->user;
    log->time = QDateTime::currentDateTime().toTime_t();
    log->operation = 3;
    log->fileName = childFile->fileName;
    int ok2 = FileLog::insertNewLog(log);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendDianziMd5(hash.result())),QHostAddress(ip),9051);
    file->close();
}

void FirstWindow::getmd5DataDownloadRequest(FileInfo *fileInfo, QString ip)
{
    if(fileInfo->fileSize==0){
        emit startSendFile( sendfile::GRILLE,ip,fileInfo->fileName,0,fileInfo->parentPath);
    }else{
        emit startSendAbortFile(sendfile::GRILLE,ip,fileInfo->fileName,fileInfo->fileSize);
    }
}

void FirstWindow::getDianzimd5DataDownloadRequest(ChildFile *childFile, QString ip)
{
    emit startSendDianziFile( sendfile::GRILLE,ip,childFile->fileName,0,childFile->parentString);
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

void FirstWindow::MenuUserSlots()
{
    pageUserManage = new UserManage();
    pageUserManage->show();
}

void FirstWindow::MenuStationSlots()
{
    pageStationManage = new StationManage();
    pageStationManage->show();
}

void FirstWindow::MenuMissionSlots()
{
    pageMissionManage = new MissionManage();
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
