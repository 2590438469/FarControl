#include "agreementanalusis.h"
#include <QDataStream>
#include <QDebug>
#include "firstwindow.h"
AgreeMentAnalusis::AgreeMentAnalusis(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<FileInfo*>>("QList<FileInfo*>");

}

QList<FileInfo*> AgreeMentAnalusis::analysisGrilleFileInfo(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<FileInfo*> list;
    quint32 fileNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileNum;
    qDebug() <<"文件数量" << fileNum;
    for(int i=0;i<fileNum;i++){
        QString fileName;
        quint64 fileSize;
        strea >> fileName;
        strea >> fileSize;
        FileInfo *file = new FileInfo();
        file->fileName = fileName;
        file->fileSize = fileSize;
        qDebug() << "文件名" << fileName;
        qDebug() << "文件大小" << fileSize;
        list.append(file);
    }
    return list;
}

QList<FileInfo*> AgreeMentAnalusis::analysisDisplayFileInfo(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<FileInfo*> list;
    quint32 fileNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileNum;
    qDebug() <<"文件数量" << fileNum;
    for(int i=0;i<fileNum;i++){
        QString fileName;
        quint64 fileSize;
        strea >> fileName;
        strea >> fileSize;
        FileInfo *file = new FileInfo();
        file->fileName = fileName;
        file->fileSize = fileSize;
        qDebug() << "文件名" << fileName;
        qDebug() << "文件大小" << fileSize;
        list.append(file);
    }
    return list;
}

void AgreeMentAnalusis::analysisAllMissionInfo(QByteArray array)
{
    macroInfo.clear();
    basicInfo.clear();
    stationInfo.clear();
    userInfo.clear();
    geshanInfo.clear();
    baseBandInfo.clear();

    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    quint16 macroNum;
    strea >> macroNum;
    for(int i=0;i<macroNum;i++){
        MissionMacroInfo *singleMacroInfo = new MissionMacroInfo();
        strea >> singleMacroInfo->maxing;
        strea >> singleMacroInfo->malv;
        strea >> singleMacroInfo->zichang;
        strea >> singleMacroInfo->zhenchang;
        strea >> singleMacroInfo->zhenmazu;
        strea >> singleMacroInfo->zhenmazuchang;
        strea >> singleMacroInfo->fuzhenfangshi;
        strea >> singleMacroInfo->fuzhenchang;
        strea >> singleMacroInfo->idziweizhi;
        strea >> singleMacroInfo->idzijizhi;
        strea >> singleMacroInfo->idzijishu;
        strea >> singleMacroInfo->jiemizhuangtai;
        strea >> singleMacroInfo->xunhuanfuzhenweizhi;
        strea >> singleMacroInfo->xunhuanfuzhenmazu;
        strea >> singleMacroInfo->duofuhaojianyan;
        strea >> singleMacroInfo->tpc;
        strea >> singleMacroInfo->kuaitongbuzhenmazu;
        strea >> singleMacroInfo->AGC;
        strea >> singleMacroInfo->AFCmoshi;
        strea >> singleMacroInfo->jiaowucha;
        strea >> singleMacroInfo->gongzuodianpin;
        strea >> singleMacroInfo->xinghao;
        strea >> singleMacroInfo->miaoshu;
        strea >> singleMacroInfo->biaoshi;
        strea >> singleMacroInfo->ruanjiemi;
        macroInfo.append(singleMacroInfo);
    }
    quint16 basicNum;
    strea >> basicNum;
    for(int i=0;i<basicNum;i++){
        MissionBasicInfo *singleBasicInfo = new MissionBasicInfo();
        strea >> singleBasicInfo->code;
        strea >> singleBasicInfo->basictime;
        strea >> singleBasicInfo->starttime;
        strea >> singleBasicInfo->endtime;
        strea >> singleBasicInfo->protect;
        strea >> singleBasicInfo->point;
        strea >> singleBasicInfo->status;
        strea >> singleBasicInfo->mainport;
        strea >> singleBasicInfo->calport;
        strea >> singleBasicInfo->backport;
        strea >> singleBasicInfo->planePosition;
        strea >> singleBasicInfo->missionhong;
        strea >> singleBasicInfo->jinzhan;
        strea >> singleBasicInfo->time;

        quint16 stationNum;
        strea >> stationNum;
        for(int j=0;j<stationNum;j++){
            Station *station = new Station();
            strea >> station->stationName;
            strea >> station->stationIp;
            singleBasicInfo->stations.append(station);
        }
        basicInfo.append(singleBasicInfo);
    }
    quint16 stationNum;
    strea >> stationNum;
    for(int i=0;i<stationNum;i++){
        Station *station = new Station();
        strea >> station->stationName;
        strea >> station->stationIp;
        stationInfo.append(station);
    }
    quint16 userNum;
    strea >> userNum;
    for(int i=0;i<userNum;i++){
        User *user = new User();
        strea >> user->code;
        strea >> user->name;
        strea >> user->phoneNumber;
        strea >> user->role;
        strea >> user->status;
        strea >> user->wrongTimes;
        userInfo.append(user);
    }
    quint16 geshanNum;
    strea >> geshanNum;
    for(int i=0;i<geshanNum;i++){
        QString singleGeshanInfo;
        strea >> singleGeshanInfo;
        qDebug() << "解析的数据格栅"<< singleGeshanInfo;
        geshanInfo.append(singleGeshanInfo);
    }
    quint16 baseBandNum;
    strea >> baseBandNum;
    for(int i=0;i<baseBandNum;i++){
        BaseBand *baseBand = new BaseBand();
        strea >> baseBand->id;
        strea >> baseBand->stationName;
        strea >> baseBand->port;
        baseBandInfo.append(baseBand);
    }
}

MissionBasicInfo *AgreeMentAnalusis::analusisNewMission(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;

    MissionBasicInfo *basic = new MissionBasicInfo();
    strea >> basic->code >> basic->basictime >>basic->starttime >> basic->endtime
          >> basic->protect >> basic->point >> basic->status >> basic->mainport
          >> basic->calport >> basic->backport >> basic->planePosition
          >> basic->missionhong >> basic->time;
    quint8 stationsSize;
    QList<Station*> list;
    strea >> stationsSize;
    for(int i=0;i<stationsSize;i++){
        Station *station = new Station();
        strea >> station->stationName;
        strea >> station->stationIp;
        list.append(station);
    }
    basic->stations = list;
    return basic;
}

QString AgreeMentAnalusis::analusisRetrieveMission(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString missionCode;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> missionCode;
    return missionCode;
}

QString AgreeMentAnalusis::analusisAbortMission(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString missionCode;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> missionCode;
    return missionCode;
}

QString AgreeMentAnalusis::analusisGoonMission(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString missionCode;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> missionCode;
    return missionCode;
}

quint8 AgreeMentAnalusis::analusisMd5(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    quint8 result;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> result;
    return result;
}

QList<HealthData *> AgreeMentAnalusis::analusisHealthData(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<HealthData *> list;
    int listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;
    for(int i=0;i<listNum;i++){
        HealthData *data = new HealthData();
        strea >> data->name;
        strea >> data->delay;
        strea >> data->lost;
        strea >> data->status;
        strea >> data->dataIn;
        list.append(data);
    }
    return list;
}

QList<ProcessEntity *> AgreeMentAnalusis::analusisProcessData(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<ProcessEntity *> list;
    int listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;
    for(int i=0;i<listNum;i++){
        ProcessEntity *data = new ProcessEntity();
        strea >> data->name;
        strea >> data->code;
        strea >> data->fileName;
        strea >> data->percent;
        list.append(data);
    }
    return list;
}

QList<GeShan *> AgreeMentAnalusis::analusisAllGeshan(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<GeShan *> list;
    quint64 listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;

    for(int i=0;i<listNum;i++){
        GeShan *geshan = new GeShan();
        strea >> geshan->xuhao  >> geshan->name >> geshan->xinghaochangjia >> geshan->daihao >> geshan->chulipingtai
         >> geshan->xianshipingtai >> geshan->zhuangtaibeizhu >> geshan->jiesuanchengxu >> geshan->setup
         >> geshan->shifoujiami >> geshan->jiamixinxibeizhu >> geshan->xianshihuamianbanben
         >> geshan->jiesuanruanjianwenjianjia >> geshan->beizhu >> geshan->banbengengxinshijian
         >> geshan->people >> geshan->dianzigeshan >> geshan->filesize >> geshan->displayFilesize >> geshan->type;
        list.append(geshan);
    }
    return list;
}

ChildFileWithParent* AgreeMentAnalusis::analusisChildFile(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<ChildFile *> list;
    QString wenjianjia;
    quint64 listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;

    for(int i=0;i<listNum;i++){
        ChildFile *childFile = new ChildFile();
        strea >> childFile->fileName >> childFile->fileSize;
        list.append(childFile);
    }
    strea >> wenjianjia;
    ChildFileWithParent *withParent = new ChildFileWithParent();
    withParent->childList = list;
    withParent->parent = wenjianjia;
    return withParent;
}

QList<MissionBasicInfo *> AgreeMentAnalusis::analusisAdvanceResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<MissionBasicInfo *> alllist;
    strea >> head1 >> head2 >> noneLength >> dataStyle;

    quint16 size;

    strea >> size;
    for(int i=0;i<size;i++){
        MissionBasicInfo *basic = new MissionBasicInfo();
        strea >> basic->code;
        strea >> basic->basictime;
        strea >> basic->starttime;
        strea >> basic->endtime;
        strea >> basic->protect;
        strea >> basic->point;
        strea >> basic->status;
        strea >> basic->mainport;
        strea >> basic->calport;
        strea >> basic->backport;
        strea >> basic->planePosition;
        strea >> basic->missionhong;
        strea >> basic->jinzhan;
        strea >> basic->time;
        quint16 stationsize;
        strea >> stationsize;
        QList<Station*> stations;
        for(int j=0;j<stationsize;j++){
            Station *station = new Station();
            strea >> station->stationName;
            strea >> station->stationIp;
            stations.append(station);
        }
        alllist.append(basic);

    }
    return alllist;
}

QList<RemoteData *> AgreeMentAnalusis::analusisDataAdvanceResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<RemoteData *> list;
    quint64 listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;

    for(int i=0;i<listNum;i++){
        RemoteData *geshan = new RemoteData();
        strea >> geshan->code >> geshan->model >> geshan->time >> geshan->type >> geshan->fileName >> geshan->fileSize >> geshan->id;
        list.append(geshan);
    }
    return list;
}

QList<RemoteData *> AgreeMentAnalusis::analusisAllRemote(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<RemoteData *> list;
    quint64 listNum;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> listNum;

    for(int i=0;i<listNum;i++){
        RemoteData *geshan = new RemoteData();
        strea >> geshan->code >> geshan->model >> geshan->time >> geshan->type >> geshan->fileName >> geshan->fileSize >> geshan->id >> geshan->user;
        list.append(geshan);
    }
    return list;
}

QByteArray AgreeMentAnalusis::analusisDataMd5(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QByteArray resultArray;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> resultArray;
    return resultArray;
}

QByteArray AgreeMentAnalusis::analusisDianziMd5(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QByteArray resultArray;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> resultArray;
    return resultArray;
}

QList<FileLog *> AgreeMentAnalusis::analusisStatisticResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QList<FileLog *> list;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    quint64 listSize;
    strea >> listSize;
    for(int i=0;i<listSize;i++){
        FileLog *fileLog = new FileLog();
        strea >> fileLog->people >> fileLog->time >> fileLog->operation >> fileLog->fileName;
        qDebug() << "筛选结果" << fileLog->people << fileLog->time
                 << fileLog->operation << fileLog->fileName;
        list.append(fileLog);
    }
    return list;
}

int AgreeMentAnalusis::analusisDeleteDataResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    int result;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> result;
    return result;
}

int AgreeMentAnalusis::analusisUpdateDataResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    int result;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> result;
    return result;
}

int AgreeMentAnalusis::analusisUpdateGeshanResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    int result;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> result;
    return result;
}

quint64 AgreeMentAnalusis::analusisRefile(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString fileName;
    quint64 fileSize;
    QString code;
    quint8 isok;
    quint64 nowsize;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileName >> fileSize >> code >> isok >> nowsize;
    return nowsize;
}

