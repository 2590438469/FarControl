#include "station.h"
#include <QSqlQuery>
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlRecord>

Station::Station(QObject *parent) : QObject(parent)
{

}

Station::Station(QString ip, QString name, QString member, QString number, QString longitude, QString latitude, QString id, QObject *parent)
{
    stationIp = ip;
    stationName = name;
    stationMember = member;
    stationNumber = number;
    stationLongitude = longitude;
    stationLatitude = latitude;
    stationId = id;
}

QList<Station*> Station::selectAllStations()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `stationnew`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<Station*> stations;
    Station *station = new Station;

    int name = rec.indexOf("遥测站名");
    int ip = rec.indexOf("ip地址");
    int member = rec.indexOf("联系人");
    int number = rec.indexOf("联系电话");
    int longitude = rec.indexOf("经度");
    int latitude = rec.indexOf("纬度");
    int id = rec.indexOf("id");

    while (query.next())
    {
        Station *station = new Station;
        station->stationName = query.value(name).toString();
        station->stationIp = query.value(ip).toString();
        station->stationMember = query.value(member).toString();
        station->stationNumber = query.value(number).toString();
        station->stationLongitude = query.value(longitude).toString();
        station->stationLatitude = query.value(latitude).toString();
        station->stationId = query.value(id).toString();
        stations.append(station);
    }
    return stations;
}

QList<Station *> Station::selectAllStationsBySplitString(QString splintString)
{
    QList<Station*> stations;

    QStringList list = splintString.split(",");
    for(int j=0;j<list.size();j++){
        qDebug() << "分割";
        qDebug() << list.at(j);
        Station *station = Station::selectStationById(list.at(j));
        qDebug() << station->stationName;
        qDebug() << station->stationIp;
        stations.append(station);
    }
    return stations;
}

Station* Station::selectStationById(QString id)
{
    QSqlQuery query(db);
    qDebug() << "id" <<id;
    QString qs = QString("select * from `stationnew` where id = %1").arg(id);
    query.exec(qs);
    QSqlRecord rec = query.record();
    Station *station = new Station();

    int name = rec.indexOf("遥测站名");
    int ip = rec.indexOf("ip地址");
    int member = rec.indexOf("联系人");
    int number = rec.indexOf("联系电话");
    int longitude = rec.indexOf("经度");
    int latitude = rec.indexOf("纬度");

    while (query.next())
    {
        station->stationName = query.value(name).toString();
        station->stationIp = query.value(ip).toString();
        station->stationMember = query.value(member).toString();
        station->stationNumber = query.value(number).toString();
        station->stationLongitude = query.value(longitude).toString();
        station->stationLatitude = query.value(latitude).toString();
        qDebug() << "站名名"<<station->stationName;
    }
    return station;
}
