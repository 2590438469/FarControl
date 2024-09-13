#include "stationshowmulty.h"
#include "ui_stationshowmulty.h"
#include "stationshow.h"
#include "firstwindow.h"
#include "station.h"
#include "QSqlQuery"
#include "mainwindow.h"
#include "qsqlrecord.h"
#include "missionsendwidget.h"

StationShowMulty::StationShowMulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationShowMulty)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&StationShowMulty::addItem);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&StationShowMulty::deletItem);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&StationShowMulty::yes);
}

StationShowMulty::~StationShowMulty()
{
    delete ui;
}

void StationShowMulty::setStationString(QString station)
{


    staionString = station;

    QStringList list = staionString.split(",");
    for(int j=0;j<stationInfo.size();j++){
        Station *st = stationInfo.at(j);
        for(int j=0;j<list.size();j++){
            QString stationItem= list.at(j);
            if(st->stationId == stationItem){
                StationShow *show = new StationShow;
                show->setIp(st->stationIp);
                show->setName(st->stationName);
                ui->verticalLayout->addWidget(show);
            }
        }
    }

}

void StationShowMulty::setStations(QList<Station *> list)
{

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();

    stationList = list;
    for(int j=0;j<list.size();j++){
        StationShow *show = new StationShow;
//        show->setIp(list.at(j)->stationIp);
        show->setName(list.at(j)->stationName);
        show->setFalse();
        ui->verticalLayout->addWidget(show);
    }
}

void StationShowMulty::setNothing()
{
    QStringList list;
    if(unsendStationList.contains(code)){
        list = unsendStationList.value(code);

        for(int i=0;i<list.size();i++){
            for(int j=0;j<baseBandInfo.size();j++){
                if(QString::number( baseBandInfo.at(j)->id)==list.at(i)){
                    qDebug() << "排列的" << baseBandInfo.at(j)->id <<baseBandInfo.at(j)->stationName << baseBandInfo.at(j)->port;
                    StationShow *p = new StationShow();
                    p->setName(QString::number( baseBandInfo.at(j)->id));
                    p->setPort(QString::number(baseBandInfo.at(j)->port));
                    ui->verticalLayout->addWidget(p);
                    allStationShow.append(p);
                }
            }
        }
    }
}

void StationShowMulty::setIsSend(bool isSend)
{
    this->isSend = isSend;
}

void StationShowMulty::addItem()
{
    StationShow *p = new StationShow();
    ui->verticalLayout->addWidget(p);
    allStationShow.append(p);
}

void StationShowMulty::deletItem()
{
    for(int i=0;i<allStationShow.size();i++){
        if(allStationShow.at(i)->isChecked){
            StationShow *singleShow = allStationShow.at(i);
            ui->verticalLayout->removeWidget(allStationShow.at(i));
            allStationShow.removeAt(i);
            delete singleShow;
            i=0;
        }
    }
}

void StationShowMulty::yes()
{
    unsendStationList.remove(code);
    QStringList list;
    for(int i=0;i<allStationShow.size();i++){
        for(int j=0;j<baseBandInfo.size();j++){
            if(baseBandInfo.at(j)->stationName==allStationShow.at(i)->getStationName()
                    &&QString::number(baseBandInfo.at(j)->port) == allStationShow.at(i)->getPort()){
                qDebug() << "插入" << baseBandInfo.at(j)->id;
                list << QString::number(baseBandInfo.at(j)->id);
            }
        }
    }
    unsendStationList.insert(code,list);
    qDebug() << "插入结果" << unsendStationList.value(code);
    QMessageBox::information(this,"更改提示","更改成功");
    this->close();
}

void StationShowMulty::setMissionCode(QString code)
{
    this->code = code;
}
