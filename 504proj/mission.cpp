#include "mission.h"
#include "missionbasicinfo.h"
#include "missionmacroinfo.h"

Mission::Mission(QObject *parent) : QObject(parent)
{

}

QList<Mission *> Mission::getAllMissionInfo()
{
    QList<Mission *> list;
    QList<MissionBasicInfo*> basicList;
    basicList = MissionBasicInfo::selectAllMissionBasicInfo();
    for(int i=0;i<basicList.size();i++){
        MissionMacroInfo *macro = MissionMacroInfo::selectMacroByBiaoshi(basicList.at(i)->missionhong);
        Mission *mission = new Mission();
        mission->basicInfo = basicList.at(i);
        mission->macroInfo = macro;
        list.append(mission);
    }

    return list;
}
