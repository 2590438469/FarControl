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
#include <config/configinfo.h>

QString response;
QString name;
QSqlDatabase db;
//QUdpSocket *socket;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    ui->lineEdit_2->setEchoMode ( QLineEdit::Password );
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("pro504");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    QSqlError er = db.lastError();
    qDebug() << er.text();
    if(ok==true)
    {
        qDebug() << "连接成功";
    }else{
        QMessageBox::information(this,"数据库连接信息",er.text());
        qApp->quit();
    }

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    connect(ui->lineEdit_2,&QLineEdit::returnPressed,this,&MainWindow::judgePass);
//    ui->lineEdit->eventFilter()


    //点击新建，跳转页面
    connect(ui->actionlogout,&QAction::triggered,[this](){
        FirstWindow *p = new FirstWindow;
        p->show();
        this->hide();
    });

    ConfigInfo *info = new ConfigInfo();
    info->initialAllConfig();
    qDebug() << "打印配置信息22" << ConfigInfo::datFilePath;
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::judgePass);
//    connect(ui->pushButton,&QPushButton::clicked,[=](){

//        QString name=ui->lineEdit->text();
//        QString password=ui->lineEdit_2->text();
//        qDebug() << name;
//        qDebug() << password;

//        qDebug() << QSqlDatabase::drivers();
//        db = QSqlDatabase::addDatabase("QMYSQL");
//        db.setHostName("127.0.0.1");
//        db.setPort(3306);
//        db.setDatabaseName("pro504");
//        db.setUserName("root");
//        db.setPassword("123456");
//        bool ok = db.open();
//        QSqlError er = db.lastError();
//        qDebug() << er.text();
//        if(ok==true)
//        {
//            qDebug() << "连接成功";
//        }

//        QSqlQuery query=QSqlQuery(db);
//        query.exec("select * from user");
//        QSqlRecord rec = query.record();

//          qDebug() << "Number of columns: " << rec.count();

//          int nameCol = rec.indexOf("name"); // index of the field "name"
//          while (query.next())
//              qDebug() << query.value(nameCol).toString(); // output all names
//        post(name,password);

//        FirstWindow *p = new FirstWindow;
//        p->show();
//        this->hide();







//    db = QSqlDatabase::addDatabase("QMYSQL");
//        db.setHostName("127.0.0.1");
//        db.setPort(3306);
//        db.setDatabaseName("test");
//        db.setUserName("root");
//        db.setPassword("089530");
//        bool ok = db.open();
//        if(ok==true)
//        {
//            qDebug() << "连接成功";
//        }
        QSqlQuery query(db);
        QString qs6 = QString("select name from loginlog where id = (select max(id) from loginlog)");
        query.exec(qs6);
        QSqlRecord rec2 = query.record();
        qDebug() << "3:Number of columns: " << rec2.count();
        int nameCol = rec2.indexOf("name");
        QString lastname;


        while (query.next())
        {
             lastname = query.value(nameCol).toString();
        }

        ui->lineEdit->setText(lastname);




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

void MainWindow::judgePass()
{
    QString name=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    qDebug() << name;
    qDebug() << password;

    qDebug() << QSqlDatabase::drivers();

    if(name == "" ||password == "")
    {
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    }
    else{

            QSqlQuery query(db);
            QString qs = QString("select 密码,状态 from usernew where 账号 ='%1'").arg(name);

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
                QMessageBox::information(this,"警告","用户名不存在！",QMessageBox::Ok);
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

                QString qs1 = QString("select 错误次数 from usernew where 账号 ='%1'").arg(name);
                query.exec(qs1);
                QSqlRecord rec1 = query.record();
                qDebug() << "2:Number of columns: " << rec1.count();
                int errorCol = rec1.indexOf("错误次数");
                int error;
                while (query.next())
                {
                     error = query.value(errorCol).toInt();
                }

                QString password2 = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
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
                    QString qs3 = QString("update usernew set 错误次数 ='%1' where 账号 ='%2'").arg(error).arg(name);
                    query.exec(qs3);
                    if(error==3)
                    {
                        islock=1;
                        QString qs2 = QString("update usernew set 状态 = '%2' where 账号 ='%1'").arg(name).arg("已锁定");
                        query.exec(qs2);
                        QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(name);
                        query.exec(qs4);
                    }
                    QMessageBox::information(this,"警告","用户名或密码错误！",QMessageBox::Ok);

                }
                else if(a && islock!=1)
                {
                    QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);

                    QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(name);
                    query.exec(qs4);

                    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
                    QString currenttime = dateTime.toString("hh时mm分ss秒");//格式化时间
                    qDebug() << currenttime;
                    qDebug() << name;
                    QString qs5 = QString("insert into loginlog(name,logintime) values('%1','%2')").arg(name).arg(currenttime);
                    qDebug() << query.exec(qs5);
                    qDebug() << db.lastError().text();


                    FirstWindow *p = new FirstWindow;
                    connect(this,&MainWindow::sendUser,p,&FirstWindow::getCurrentUser);
                    emit sendUser(name);
                    qInfo("用户: %s\t\t 登陆成功", name.toUtf8().constData());
                    p->show();
                    this->close();
                }
                else
                {
                    QMessageBox::information(this,"警告","三次错误输入密码，用户已被锁定，不可再登陆！",QMessageBox::Ok);
                }
            }
        }
}

