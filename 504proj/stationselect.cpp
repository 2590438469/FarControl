#include "stationselect.h"
#include "ui_stationselect.h"
#include "combolabel.h"
#include <QDebug>
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include "config/configinfo.h"
#include "util/bytemethod.h"
#include "agreement/agreement.h"

StationSelect::StationSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationSelect)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&StationSelect::addStation);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&StationSelect::send);
    qDebug() << "gouzaofangfa1";
}

StationSelect::StationSelect(MissionBasicInfo *basic, QWidget *parent):
    QWidget(parent),
    ui(new Ui::StationSelect)
{
    ui->setupUi(this);
    missionBasicInfo = basic;
    connect(ui->pushButton,&QPushButton::clicked,this,&StationSelect::addStation);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&StationSelect::send);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&StationSelect::deleteStation);
    comboLabelList.append(ui->widget->getIp());
    comboLabelList2.append(ui->widget);
}


StationSelect::~StationSelect()
{
    delete ui;
}

void StationSelect::addStation()
{
    ComboLabel *com = new ComboLabel();
    comboLabelList.append(com->getIp());
    comboLabelList2.append(com);
    ui->verticalLayout->addWidget(com);
}

void StationSelect::deleteStation()
{
    int count = ui->verticalLayout->count();

    if(count > 0){
        QWidget *widget = ui->verticalLayout->itemAt(count - 1)->widget();

        ui->verticalLayout->removeWidget(widget);

        widget->deleteLater();
        comboLabelList2.removeLast();
    }
}

void StationSelect::send()
{
    QList<Station*> list;
    for(int i=0;i<comboLabelList2.size();i++){
        Station *station = new Station();
        station->stationName = comboLabelList2.at(i)->getName();
        station->stationIp = comboLabelList2.at(i)->getIp();
        list.append(station);
    }
    missionBasicInfo->stations = list;


    for(int i=0;i<FirstWindow::stations.size();i++){
        QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendNewMissionInfo(missionBasicInfo)),*addr,9051);
    }

    QMessageBox::information(this,"发送提示",QString("任务%1发送成功").arg(missionBasicInfo->code));
    emit finishSend(missionBasicInfo->code);

    qInfo("用户: %s\t\t 任务%s发送", currentUser.toUtf8().constData(),missionBasicInfo->code.toUtf8().constData());
    this->close();
    this->deleteLater();
}
