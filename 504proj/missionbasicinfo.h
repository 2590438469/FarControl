#ifndef MISSIONBASICINFO_H
#define MISSIONBASICINFO_H

#include <QObject>
#include "station.h"
#include "advance.h"

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
    QString stationString;
    int time;

    static QList<MissionBasicInfo*> selectAllMissionBasicInfo();
    static int insertNewMission(MissionBasicInfo *info);
    static int updateJinzhan(QString code,QString jinzhan);
    static int deleleMission(QString code);

    static QList<MissionBasicInfo*> selectByAdvance(Advance* advance);
    static QString selectGeshanByCode(QString code);

signals:

public slots:
};

#endif // MISSIONBASICINFO_H
