#include "missionbasicinfo.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include "station.h"
#include <QSqlError>

MissionBasicInfo::MissionBasicInfo(QObject *parent) : QObject(parent)
{

}

QList<MissionBasicInfo *> MissionBasicInfo::selectAllMissionBasicInfo()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `missionsend`");
    query.exec(qs);
    QSqlRecord rec = query.record();

    QList<MissionBasicInfo *> list;

    int codeint = rec.indexOf("任务代号");
    int basictimeint = rec.indexOf("到位时间");
    int starttimeint = rec.indexOf("时间节点(起始)");
    int endtimeint = rec.indexOf("时间节点(终止)");
    int protectint = rec.indexOf("保障内容");
    int pointint = rec.indexOf("点频");
    int statusint = rec.indexOf("状态");
    int mainportint = rec.indexOf("主收端口");
    int calportint = rec.indexOf("解密端口");
    int backportint = rec.indexOf("备份端口");
    int planePositionint = rec.indexOf("飞机位置");
    int stationsint = rec.indexOf("遥测站");
    int missionhongint = rec.indexOf("任务宏");
    int jinzhanint = rec.indexOf("进展");
    int timeint = rec.indexOf("time");



    while (query.next())
    {
        MissionBasicInfo *info = new MissionBasicInfo();
        QString stationSte;
        info->code = query.value(codeint).toString();
        info->basictime = query.value(basictimeint).toString();
        info->starttime = query.value(starttimeint).toString();
        info->endtime = query.value(endtimeint).toString();
        info->protect = query.value(protectint).toString();
        info->point = query.value(pointint).toString();
        info->status = query.value(statusint).toString();
        info->mainport = query.value(mainportint).toString();
        info->calport = query.value(calportint).toString();
        info->backport = query.value(backportint).toString();
        info->planePosition = query.value(planePositionint).toString();
        stationSte = query.value(stationsint).toString();
        info->missionhong = query.value(missionhongint).toString();
        info->jinzhan = query.value(jinzhanint).toString();
        info->time = query.value(timeint).toInt();
        info->stationString = query.value(stationsint).toString();

        info->stations = Station::selectAllStationsBySplitString(stationSte);
        list.append(info);
    }


    QList<MissionBasicInfo *> list2;
    for(int i=0;i<list.size();i++){
        QDateTime currentDateTime = QDateTime::currentDateTime();

        // Set the time to 0:00:00 of the current day
        QDateTime todayMidnight = currentDateTime;
        todayMidnight = todayMidnight.addDays(-1);
        todayMidnight.setTime(QTime(0, 0, 0));

        // Convert QDateTime to a Unix timestamp (seconds since epoch)
        qint64 timestamp = todayMidnight.toSecsSinceEpoch();




        // Set the time to 0:00:00 of tomorrow
        QDateTime tomorrowMidnight = currentDateTime;
        tomorrowMidnight.setTime(QTime(23, 59, 59));

        // Convert QDateTime to a Unix timestamp (seconds since epoch)
        qint64 timestamp2 = tomorrowMidnight.toSecsSinceEpoch();

        if(list.at(i)->time>timestamp && list.at(i)->time<timestamp2){
            qDebug() << list.at(i)->time << timestamp << timestamp2;
            list2.append(list.at(i));
        }
        qDebug() << timestamp << timestamp2;

    }
    return list2;
}

int MissionBasicInfo::insertNewMission(MissionBasicInfo *info)
{
    QString stationString;
    for(int i=0;i<info->stations.size();i++){
        stationString.append(info->stations.at(i)->stationName);
        qDebug() << "插入的" << info->stations.at(i)->stationName;
        stationString.append(",");
    }
    stationString.chop(1);
    QSqlQuery query(db);
    int nowtime = QDateTime::currentDateTime().toTime_t();
    QString qs = QString("INSERT INTO `missionsend` (`任务代号`, `到位时间`, `时间节点(起始)`, `时间节点(终止)`, `保障内容`, "
                         "`点频`, `状态`, `主收端口`, `解密端口`, `备份端口`, `飞机位置`, `遥测站`, `任务宏`, `进展`,`time`) "
                         "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', %8, '%9', %10, '%11', '%12', '%13', '%14', %15)")
            .arg(info->code).arg(info->basictime).arg(info->starttime).arg(info->endtime)
            .arg(info->protect).arg(info->point).arg(info->status).arg("0").arg(info->calport)
            .arg("0").arg(info->planePosition).arg(stationString).arg(info->missionhong).arg("已发送")
            .arg(nowtime);
    int ok = query.exec(qs);
    info->time = nowtime;
    qDebug() << qs;
    qDebug() << query.lastError().text();
    return ok;
}

int MissionBasicInfo::updateJinzhan(QString code, QString jinzhan)
{
    QSqlQuery query(db);
    QString qs = QString("update `missionsend` set `进展`  ='%1' where `任务代号` = '%2'").arg(jinzhan).arg(code);
    query.exec(qs);
    return 1;
}

int MissionBasicInfo::deleleMission(QString code)
{
    QSqlQuery query(db);
    QString qs = QString("delete from `missionsend` where `任务代号` = '%1'").arg(code);
    query.exec(qs);
    return 1;
}

QList<MissionBasicInfo *> MissionBasicInfo::selectByAdvance(Advance* advance)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `missionsend`");
    query.exec(qs);
    QSqlRecord rec = query.record();

    QList<MissionBasicInfo *> list;

    int codeint = rec.indexOf("任务代号");
    int basictimeint = rec.indexOf("到位时间");
    int starttimeint = rec.indexOf("时间节点(起始)");
    int endtimeint = rec.indexOf("时间节点(终止)");
    int protectint = rec.indexOf("保障内容");
    int pointint = rec.indexOf("点频");
    int statusint = rec.indexOf("状态");
    int mainportint = rec.indexOf("主收端口");
    int calportint = rec.indexOf("解密端口");
    int backportint = rec.indexOf("备份端口");
    int planePositionint = rec.indexOf("飞机位置");
    int stationsint = rec.indexOf("遥测站");
    int missionhongint = rec.indexOf("任务宏");
    int jinzhanint = rec.indexOf("进展");
    int timeint = rec.indexOf("time");



    while (query.next())
    {
        MissionBasicInfo *info = new MissionBasicInfo();
        QString stationSte;
        info->code = query.value(codeint).toString();
        info->basictime = query.value(basictimeint).toString();
        info->starttime = query.value(starttimeint).toString();
        info->endtime = query.value(endtimeint).toString();
        info->protect = query.value(protectint).toString();
        info->point = query.value(pointint).toString();
        info->status = query.value(statusint).toString();
        info->mainport = query.value(mainportint).toString();
        info->calport = query.value(calportint).toString();
        info->backport = query.value(backportint).toString();
        info->planePosition = query.value(planePositionint).toString();
        stationSte = query.value(stationsint).toString();
        info->missionhong = query.value(missionhongint).toString();
        info->jinzhan = query.value(jinzhanint).toString();
        info->time = query.value(timeint).toInt();

        info->stations = Station::selectAllStationsBySplitString(stationSte);
        list.append(info);
    }
    QList<MissionBasicInfo *> list2;
    int flag = 1;
    for(int j=0;j<list.size();j++){
        if(advance->iscodeEnabled){
            if(list.at(j)->code != advance->code){
                qDebug() <<"判断code";
                flag = 0;
            }
        }
        if(advance->isprotectEnabled){
            if(list.at(j)->protect != advance->protect){
                qDebug() <<"判断protect";
                flag = 0;
            }
        }
        if(advance->isstartTimeEnabled){
            qDebug() <<"判断开始时间" << list.at(j)->code;
            if(list.at(j)->time < advance->startTime){
                qDebug() << "开始不成立" << list.at(j)->time << advance->startTime;
                flag = 0;
            }
        }
        if(advance->isendTimeEnabled){
            qDebug() <<"判断结束时间" << list.at(j)->code;
            if(list.at(j)->time > advance->endTime){
                qDebug() << "结束不成立" << list.at(j)->time << advance->startTime;
                flag = 0;
            }
        }
        if(flag){
            list2.append(list.at(j));
        }
        flag = 1;
    }
    qDebug() << "筛选结果大小" << list2.size();

    return list2;
}

QString MissionBasicInfo::selectGeshanByCode(QString code)
{
    QSqlQuery query(db);
    QString qs = QString("SELECT * FROM missionsend where `任务代号` = '%1'").arg(code);
    query.exec(qs);
    QSqlRecord rec = query.record();

    QString result;

    int missionhong = rec.indexOf("任务宏");

    while (query.next())
    {
        result = query.value(missionhong).toString();
    }
    return result;
}
