#include "stationshowmulty.h"
#include "ui_stationshowmulty.h"
#include "stationshow.h"
#include "firstwindow.h"
#include "station.h"
#include "QSqlQuery"
#include "mainwindow.h"
#include "qsqlrecord.h"

StationShowMulty::StationShowMulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationShowMulty)
{
    ui->setupUi(this);
}

StationShowMulty::~StationShowMulty()
{
    delete ui;
}

void StationShowMulty::setStationString(QString station)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `stationnew`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList <Station*> stations;

    int ip = rec.indexOf("ip地址");
    int name = rec.indexOf("遥测站名");
    int member = rec.indexOf("联系人");
    int phone = rec.indexOf("联系电话");
    int longitude = rec.indexOf("经度");
    int latitude = rec.indexOf("纬度");
    int id = rec.indexOf("id");
    while (query.next())
    {
        Station *station = new Station(query.value(ip).toString()
                                      ,query.value(name).toString()
                                      ,query.value(member).toString()
                                      ,query.value(phone).toString()
                                      ,query.value(longitude).toString()
                                      ,query.value(latitude).toString()
                                      ,query.value(id).toString(),this);
        stations.append(station);
    }


    staionString = station;

    QStringList list = staionString.split(",");
    for(int j=0;j<stations.size();j++){
        Station *st = stations.at(j);
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
