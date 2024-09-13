#ifndef STATION_H
#define STATION_H

#include <QObject>

class Station : public QObject
{
    Q_OBJECT
public:
    explicit Station(QObject *parent = nullptr);
    explicit Station(QString ip,
    QString name,
    QString member,
    QString number,
    QString longitude,
    QString latitude,
    QString id,QObject *parent = nullptr);


    QString stationIp;
    QString stationName;
    QString stationMember;
    QString stationNumber;
    QString stationLongitude;
    QString stationLatitude;
    QString stationId;

    static QList<Station*> selectAllStations();
    static QList<Station*> selectAllStationsBySplitString(QString splintString);
    static Station* selectStationById(QString id);

private:

signals:

public slots:
};

#endif // STATION_H
