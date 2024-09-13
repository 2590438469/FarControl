#include "station.h"

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
