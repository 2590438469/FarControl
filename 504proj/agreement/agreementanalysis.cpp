#include "agreementanalysis.h"
#include <QDataStream>
#include <QDebug>
#include "geshan.h"
#include "dataadvance.h"
#include "geshanadvance.h"

AgreeMentAnalysis::AgreeMentAnalysis(QObject *parent) : QObject(parent)
{

}

quint8 AgreeMentAnalysis::analysisFileCheckRequest(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    quint8 fileType;
    strea >> fileType;
    qDebug() << "文件类型"<< fileType;
    return fileType;
}

fileDownloadRquest* AgreeMentAnalysis::analysisFileDownloadRequest(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    fileDownloadRquest *request = new fileDownloadRquest();
    strea >> request->fileType;
    strea >> request->fileName;
    return request;
}

quint8 AgreeMentAnalysis::analusisDllRequest(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    quint8 isok;
    QString fileName;
    QString code;
    quint64 fileSize;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileName >> fileSize >> code >> isok;
    return isok;
}

MissionBasicInfo *AgreeMentAnalysis::analusisNewMission(QByteArray array)
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
          >> basic->missionhong;
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

QString AgreeMentAnalysis::analusisRetriveMission(QByteArray array)
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

QString AgreeMentAnalysis::analusisabortMission(QByteArray array)
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

QString AgreeMentAnalysis::analusisgoonMission(QByteArray array)
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

QByteArray AgreeMentAnalysis::analusisMd5(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QByteArray md5;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> md5;
    return md5;
}

GeShan* AgreeMentAnalysis::analusisGeshan(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    GeShan *geshan = new GeShan();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> geshan->name >> geshan->xinghaochangjia >> geshan->daihao >> geshan->chulipingtai
     >> geshan->xianshipingtai >> geshan->zhuangtaibeizhu >> geshan->jiesuanchengxu >> geshan->setup
     >> geshan->shifoujiami >> geshan->jiamixinxibeizhu >> geshan->xianshihuamianbanben
     >> geshan->jiesuanruanjianwenjianjia >> geshan->beizhu >> geshan->banbengengxinshijian
     >> geshan->people >> geshan->type;
    qDebug() << "解析的type" << geshan->type;
    return geshan;
}

QString AgreeMentAnalysis::analusisDeleteGeshan(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString wenjianjia;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> wenjianjia;
    return wenjianjia;
}

QString AgreeMentAnalysis::analusisChildGeshanRequest(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString wenjianjia;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> wenjianjia;
    return wenjianjia;
}

ChildFile* AgreeMentAnalysis::analusisDeleteChildGeshan(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    ChildFile *child = new ChildFile();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> child->parentString >> child->fileName;
    return child;
}

Advance* AgreeMentAnalysis::analusisAdvance(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    Advance *advance = new Advance();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> advance->iscodeEnabled >> advance->isprotectEnabled
           >> advance->isstartTimeEnabled >> advance->isendTimeEnabled;
    strea >> advance->code >> advance->protect
           >> advance->startTime >> advance->endTime;
    qDebug() << "打印高级筛选" << advance->iscodeEnabled << advance->isprotectEnabled
             << advance->isstartTimeEnabled << advance->isendTimeEnabled<< advance->code << advance->protect
             << advance->startTime << advance->endTime;
    return advance;
}

DataAdvance *AgreeMentAnalysis::analusisDataAdvance(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    DataAdvance *advance = new DataAdvance();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> advance->ismodelEnabled >> advance->istypeEnabled
           >> advance->isstartTimeEnabled >> advance->isendTimeEnabled;
    strea >> advance->model >> advance->type
           >> advance->startTime >> advance->endTime;
    return advance;
}

GeshanAdvance *AgreeMentAnalysis::analusisGeshanAdvance(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    GeshanAdvance *advance = new GeshanAdvance();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> advance->isstartTimeEnabled >> advance->isendTimeEnabled;
    strea >> advance->startTime >> advance->endTime;
    return advance;
}

FileInfo* AgreeMentAnalysis::analusisDatadownloadRequest(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    FileInfo *info = new FileInfo();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> info->fileName >> info->user >> info->parentPath;

    return info;
}

ChildFile* AgreeMentAnalysis::analusisDianzidownloadRequest(QByteArray array)
{
    ChildFile *childFile = new ChildFile();
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> childFile->parentString;
    strea >> childFile->fileName;
    strea >> childFile->user;

    return childFile;
}

FileInfo* AgreeMentAnalysis::getMd5Result(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    FileInfo *fileInfo = new FileInfo();

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileInfo->fileName >> fileInfo->fileSize >> fileInfo->parentPath;

    return fileInfo;
}

ChildFile *AgreeMentAnalysis::getDianziMd5Result(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    ChildFile *childFile = new ChildFile();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> childFile->parentString >> childFile->fileName;

    return childFile;
}

FileLog *AgreeMentAnalysis::analusisDataStatistic(QByteArray array)
{
    FileLog *fileInfo = new FileLog();
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> fileInfo->people >> fileInfo->startTime >> fileInfo->endTime;

    return fileInfo;
}

QString AgreeMentAnalysis::analusisDeleteData(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    QString xuhao;
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> xuhao;
    return xuhao;
}

RemoteData *AgreeMentAnalysis::analusisUpdateInfo(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    RemoteData *remoteData = new RemoteData();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> remoteData->code >> remoteData->type;
    return remoteData;
}

GeShan *AgreeMentAnalysis::analusisUpdateGeshan(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    GeShan *geshan = new GeShan();
    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> geshan->xuhao >> geshan->name >> geshan->xinghaochangjia
              >> geshan->daihao >> geshan->chulipingtai >> geshan->xianshipingtai
          >> geshan->zhuangtaibeizhu >> geshan->jiesuanchengxu >> geshan->setup
           >> geshan->shifoujiami >> geshan->jiamixinxibeizhu >> geshan->beizhu
          >> geshan->people >> geshan->type >> geshan->jiesuanruanjianwenjianjia;
    return geshan;
}

