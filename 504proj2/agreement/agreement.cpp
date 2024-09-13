#include "agreement.h"
#include "QDataStream"
#include <QDebug>

AgreeMent::AgreeMent(QObject *parent) : QObject(parent)
{

}

QByteArray AgreeMent::sendCheckAllFileCatalog(AgreeMent::FILE_TYPES type)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    if(type == AgreeMent::GRILLE) streao<<quint8(0x00);
    if(type == AgreeMent::DISPLAY) streao<<quint8(0x01);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x80);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendFileDownLoadRequest(AgreeMent::FILE_TYPES type, QString fileName)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    if(type == AgreeMent::GRILLE) {
        qDebug() << "类型为0";
        streao<<quint8(0x00);
    }
    if(type == AgreeMent::DISPLAY) {
        qDebug() << "类型为1";
        streao<<quint8(0x01);
    }
    qDebug() << type;

    qDebug() <<"协议字段" <<fileName;
    streao << fileName;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x83);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllMissionRequest()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA0);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendNewMission(MissionBasicInfo *basic)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< basic->code << basic->basictime <<basic->starttime << basic->endtime
          << basic->protect << basic->point << basic->status << basic->mainport
          << basic->calport << basic->backport << basic->planePosition
          << basic->missionhong;
    streao << quint8(basic->stations.size());
    for(int i=0;i<basic->stations.size();i++){
        streao << basic->stations.at(i)->stationName;
        streao << basic->stations.at(i)->stationIp;
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA1);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::retrieveMission(QString missionCode)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << missionCode;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA2);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::abortMission(QString missionCode)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << missionCode;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA3);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::goonMission(QString missionCode)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << missionCode;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA4);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendFileInfo(QString fileName, quint64 fileSize, QString code,quint8 type,QByteArray md5,QString parent,QString user,quint8 isFolder,quint8 isgoon)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << fileName << fileSize << code << type << md5 << parent << user << isFolder << isgoon;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x40);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDllMd5(QByteArray array)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << array;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x99);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendGeshan(GeShan *geshan)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << geshan->name << geshan->xinghaochangjia << geshan->daihao << geshan->chulipingtai
     << geshan->xianshipingtai << geshan->zhuangtaibeizhu << geshan->jiesuanchengxu << geshan->setup
     << geshan->shifoujiami << geshan->jiamixinxibeizhu << geshan->xianshihuamianbanben
     << geshan->jiesuanruanjianwenjianjia << geshan->beizhu << geshan->banbengengxinshijian
     << geshan->people << geshan->type;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCA);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDeleteGeshan(QString wenjianjia)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << wenjianjia;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCD);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::requestGeshan()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCB);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::requestGeshanChildFile(QString child)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << child;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCC);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::requestRemoteGeshan()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD0);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDeleteChildGeshan(QString child, QString parent)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << parent << child;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCE);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAdvanceSearch(Advance *advance)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << advance->iscodeEnabled << advance->isprotectEnabled
           << advance->isstartTimeEnabled << advance->isendTimeEnabled;
    streao << advance->code << advance->protect
           << advance->startTime << advance->endTime;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xCF);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDataAdvanceSearch(DataAdvance *advance)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << advance->ismodelEnabled << advance->istypeEnabled
           << advance->isstartTimeEnabled << advance->isendTimeEnabled;
    streao << advance->model << advance->type
           << advance->startTime << advance->endTime;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD6);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendGeshanAdvanceSearch(GeshanAdvance *advance)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << advance->isstartTimeEnabled << advance->isendTimeEnabled;
    streao << advance->startTime << advance->endTime;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xDA);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDownloadRemoteRequest(QString fileName,QString user,QString parentPath)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< fileName << user << parentPath;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD1);
    sendByte.append(sendByteo);
    return sendByte;
}



QByteArray AgreeMent::Datamd5StorgeFinish(QString fileName,quint64 progress,QString parent)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< fileName << progress << parent;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD2);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::Dianzimd5StorgeFinish(QString parentString ,QString fileName)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< parentString<<fileName;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD4);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendStatistic(Statistic *statistic)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< statistic->people << statistic->startTime << statistic->endTime;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD5);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::deleteRemoteData(QString xuhao)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< xuhao;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD7);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendUpdateData(QString xuhao, QString type)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< xuhao << type;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD8);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendUpdateGeshan(GeShan *geshan)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< geshan->xuhao << geshan->name << geshan->xinghaochangjia
              << geshan->daihao << geshan->chulipingtai << geshan->xianshipingtai
          << geshan->zhuangtaibeizhu << geshan->jiesuanchengxu << geshan->setup
           << geshan->shifoujiami << geshan->jiamixinxibeizhu << geshan->beizhu
          << geshan->people << geshan->type << geshan->jiesuanruanjianwenjianjia;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD9);
    sendByte.append(sendByteo);
    return sendByte;
}
QByteArray AgreeMent::sendDownloadDianziRequest(QString parentName, QString fileName,QString user)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< parentName << fileName << user;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xD3);
    sendByte.append(sendByteo);
    return sendByte;
}
