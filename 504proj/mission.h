#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include "missionbasicinfo.h"
#include "missionmacroinfo.h"

class Mission : public QObject
{
    Q_OBJECT
public:
    explicit Mission(QObject *parent = nullptr);
    MissionBasicInfo *basicInfo;
    MissionMacroInfo *macroInfo;

    static QList<Mission*> getAllMissionInfo();

signals:

public slots:
};

#endif // MISSION_H
