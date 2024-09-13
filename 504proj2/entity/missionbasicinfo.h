#ifndef MISSIONBASICINFO_H
#define MISSIONBASICINFO_H

#include <QObject>
#include "station.h"

class MissionBasicInfo : public QObject
{
    Q_OBJECT
public:
    explicit MissionBasicInfo(QObject *parent = nullptr);

    QString code;
    QString basictime;
    QString starttime;
    QString endtime;
    QString protect;
    QString point;
    QString status;
    QString mainport;
    QString calport;
    QString backport;
    QString planePosition;
    QList<Station*> stations;
    QString missionhong;
    QString jinzhan;
    int time;


signals:

public slots:
};

#endif // MISSIONBASICINFO_H
