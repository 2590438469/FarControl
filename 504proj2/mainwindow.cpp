#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>
#include <QMessageBox>
#include "QSqlDatabase"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QApplication>
#include "config/configinfo.h"

QString response;
QString name;
QSqlDatabase db;
//QUdpSocket *socket;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QProcess *process = new QProcess();
        QString programPath = "C:/Users/user/Desktop/ca/504proj.exe";
        process->setProgram(programPath);

        // 检查程序是否已经启动
        process->start();

    ConfigInfo *info = new ConfigInfo();
    info->initialAllConfig();
    manager = new QNetworkAccessManager(this);
    ui->lineEdit_2->setEchoMode ( QLineEdit::Password );
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("pro504");
    db.setUserName("root");
    db.setPassword("123456");
//    bool ok = db.open();
    QSqlError er = db.lastError();
    qDebug() << er.text();
//    if(ok==true)
//    {
//        qDebug() << "连接成功";
//    }else{
//        QMessageBox::information(this,"数据库连接信息",er.text());
//        qApp->quit();
//    }

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    connect(ui->lineEdit_2,&QLineEdit::returnPressed,this,&MainWindow::SendLoginInfo);
//    ui->lineEdit->eventFilter()



    //点击新建，跳转页面
    connect(ui->actionlogout,&QAction::triggered,[this](){
        FirstWindow *p = new FirstWindow;
        p->show();
        this->hide();

    });

    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::SendLoginInfo);

    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<receieveData::opResult>("opResult");
    udpsocket = new QUdpSocket(this);
    bool isBindOk = udpsocket->bind(9017);
    if(!isBindOk){
        QMessageBox::information(this,"socket绑定信息","socket绑定端口失败,请确保9017端口开放");
        qApp->quit();
    }

    QThread *t = new QThread;
    worker = new receieveData;
    worker->moveToThread(t);
    connect(this,&MainWindow::sendSocketData,worker,&receieveData::readPendingDatagrams);
    connect(udpsocket,&QUdpSocket::readyRead, this,&MainWindow::readPendingDatagrams);
    connect(worker,&receieveData::setLastname,this,&MainWindow::setLastname);
    connect(worker,&receieveData::login,this,&MainWindow::login);
    t->start();

    SendLastNameQuest();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::post(QString name,QString password){
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/orm/user/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json.insert("name", name);
    json.insert("password", password);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    manager->post(request,dataArray);
}



bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->lineEdit){
        if(event->type() == QEvent::MouseButtonPress)    //如果label触发了鼠标点击的事件
        {
            ui->line->setStyleSheet("background-color: rgb(255, 255, 255);");
            ui->line_4->setStyleSheet("background-color: rgb(47, 64, 80);");
            return true;                            //表示停止处理该事件，此时目标对象和后面安装的事件过滤器就无法获得该事件
        }
    }
    if(watched==ui->lineEdit_2){
        if(event->type() == QEvent::MouseButtonPress)    //如果label触发了鼠标点击的事件
        {
            ui->line->setStyleSheet("background-color: rgb(47, 64, 80);");
            ui->line_4->setStyleSheet("background-color: rgb(255, 255, 255);");
            return true;                            //表示停止处理该事件，此时目标对象和后面安装的事件过滤器就无法获得该事件
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::login(receieveData::opResult opresult)
{
    qDebug() << "开始判断";
    QString name=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    if(name == "" ||password == "")
    {
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    }
    else if(opresult.opresult == 0x03)
    {
        QMessageBox::information(this,"警告","用户名不存在",QMessageBox::Ok);
    }
    else if(opresult.opresult == 0x02)
    {
        QMessageBox::information(this,"警告","三次错误输入密码，用户已被锁定，不可再登陆！",QMessageBox::Ok);
    }
    else if(opresult.opresult == 0x00)
    {
        QMessageBox::information(this,"警告","密码错误",QMessageBox::Ok);
    }
    else if(opresult.opresult == 0x01)
    {
        QString qs = QString("用户 %1 登陆成功").arg(name);
        QMessageBox::information(this,"提醒",qs,QMessageBox::Ok);
        FirstWindow *p = new FirstWindow;
        p->role = opresult.frame;
        p->setRoleText(opresult.frame);
        p->setName(name);
        p->show();
        this->close();
    }
}

void MainWindow::readPendingDatagrams(){
    QHostAddress addr;
    quint16 port;
    QByteArray arrjudge;
    QByteArray arrCurrent;
    quint32 point = 0;
    qDebug() << "readpendingdatagrams";
    while (udpsocket->hasPendingDatagrams()) //数据报等待被读取
    {
        qDebug() << "haspend";
        point = 0;
        quint64 socketava = udpsocket->bytesAvailable();
        qDebug() << "socketava"<< socketava;
        quint64 pend = udpsocket->pendingDatagramSize();

        qDebug() << "pend ava " << pend << socketava;

        arrjudge.resize(pend);
        int x = udpsocket->readDatagram(arrjudge.data(),arrjudge.size(),&addr,&port);


        arrjudge = getInvert(arrjudge);
        qDebug() << "ip地址为" << addr << "发出请求";
        emit sendSocketData(pend,arrjudge,addr,port);
    }

}

QByteArray MainWindow::PackLastNameQuest()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x96);
    sendByte.append(sendByteo);

    return sendByte;
}

void MainWindow::SendLastNameQuest()
{
    QByteArray array = PackLastNameQuest();
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,9001);
}

QByteArray MainWindow::PackLoginInfo()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    qDebug() << name;
    qDebug() << password;
    streao << name << password;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x98);
    sendByte.append(sendByteo);

    return sendByte;
}

void MainWindow::SendLoginInfo()
{
    QByteArray array = PackLoginInfo();
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    qDebug() << ConfigInfo::centerIp;
    udpsocket->writeDatagram(getInvert(array),addre,9001);
}

QByteArray MainWindow::getInvert(QByteArray array)
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

void MainWindow::setLastname(QString lastname)
{
//    ui->lineEdit->setText(lastname);
    qDebug() << lastname;
}

