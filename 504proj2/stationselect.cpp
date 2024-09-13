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
    for(int i=0;i<comboLabelList2.size();i++){
        if(comboLabelList2.at(i)->isSelect){
            ComboLabel *label = comboLabelList2.at(i);
            ui->verticalLayout->removeWidget(label);
            comboLabelList2.removeAt(i);
            label->deleteLater();
            i=-1;
        }
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


    QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendNewMission(missionBasicInfo)),*addr,ConfigInfo::centerUdpPort);

    QMessageBox::information(this,"发送提示",QString("任务%1发送成功").arg(missionBasicInfo->code));
    emit finishSend(missionBasicInfo->code);

    qInfo("用户: %s\t\t 任务%s发送", currentUser.toUtf8().constData(),missionBasicInfo->code.toUtf8().constData());
    this->close();
    this->deleteLater();
}
