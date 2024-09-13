#include "agreement.h"
#include "QDataStream"
#include <QDebug>
#include <QDir>
#include "config/configinfo.h"
#include "missionmacroinfo.h"
#include "missionbasicinfo.h"
#include "geshan.h"
#include "user.h"
#include "baseband.h"

AgreeMent::AgreeMent(QObject *parent) : QObject(parent)
{

}

QByteArray AgreeMent::sendAllGrilleInfo()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    QDir *dir = new QDir(ConfigInfo::grillePath);
    if(!dir->exists())
    {
        qDebug() << "文件夹找不到";
    }
    dir->setFilter(QDir::Files | QDir::NoDotAndDotDot); // 只获取文件，排除"."和".."

    QFileInfoList fileList = dir->entryInfoList();
    streao << quint32(fileList.size());

    foreach (QFileInfo fileInfo, fileList) {
        QString fileName = fileInfo.fileName();
        qint64 fileSize = fileInfo.size();

        qDebug() << "File Name:" << fileName;
        qDebug() << "File Size:" << fileSize << "bytes";
        streao << fileName << fileSize;
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x81);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllDisplayInfo()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    QDir *dir = new QDir(ConfigInfo::display_frame);
    if(!dir->exists())
    {
        qDebug() << "文件夹找不到";
    }
    dir->setFilter(QDir::Files | QDir::NoDotAndDotDot); // 只获取文件，排除"."和".."

    QFileInfoList fileList = dir->entryInfoList();
    streao << quint32(fileList.size());

    foreach (QFileInfo fileInfo, fileList) {
        QString fileName = fileInfo.fileName();
        qint64 fileSize = fileInfo.size();

        qDebug() << "File Name:" << fileName;
        qDebug() << "File Size:" << fileSize << "bytes";
        streao << fileName << fileSize;
    }


    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x82);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllMissionInfo()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    QList<MissionMacroInfo*> allMacroInfo = MissionMacroInfo::selectAllMacro();
    streao<<quint16(allMacroInfo.size());
    for(int i=0;i<allMacroInfo.size();i++){
        streao << allMacroInfo.at(i)->maxing;
        streao << allMacroInfo.at(i)->malv;
        streao << allMacroInfo.at(i)->zichang;
        streao << allMacroInfo.at(i)->zhenchang;
        streao << allMacroInfo.at(i)->zhenmazu;
        streao << allMacroInfo.at(i)->zhenmazuchang;
        streao << allMacroInfo.at(i)->fuzhenfangshi;
        streao << allMacroInfo.at(i)->fuzhenchang;
        streao << allMacroInfo.at(i)->idziweizhi;
        streao << allMacroInfo.at(i)->idzijizhi;
        streao << allMacroInfo.at(i)->idzijishu;
        streao << allMacroInfo.at(i)->jiemizhuangtai;
        streao << allMacroInfo.at(i)->xunhuanfuzhenweizhi;
        streao << allMacroInfo.at(i)->xunhuanfuzhenmazu;
        streao << allMacroInfo.at(i)->duofuhaojianyan;
        streao << allMacroInfo.at(i)->tpc;
        streao << allMacroInfo.at(i)->kuaitongbuzhenmazu;
        streao << allMacroInfo.at(i)->AGC;
        streao << allMacroInfo.at(i)->AFCmoshi;
        streao << allMacroInfo.at(i)->jiaowucha;
        streao << allMacroInfo.at(i)->gongzuodianpin;
        streao << allMacroInfo.at(i)->xinghao;
        streao << allMacroInfo.at(i)->miaoshu;
        streao << allMacroInfo.at(i)->biaoshi;
        streao << allMacroInfo.at(i)->ruanjiemi;
    }
    QList<MissionBasicInfo*> allBasicInfo = MissionBasicInfo::selectAllMissionBasicInfo();
    streao<<quint16(allBasicInfo.size());
    for(int i=0;i<allBasicInfo.size();i++){
        streao << allBasicInfo.at(i)->code;
        streao << allBasicInfo.at(i)->basictime;
        streao << allBasicInfo.at(i)->starttime;
        streao << allBasicInfo.at(i)->endtime;
        streao << allBasicInfo.at(i)->protect;
        streao << allBasicInfo.at(i)->point;
        streao << allBasicInfo.at(i)->status;
        streao << allBasicInfo.at(i)->mainport;
        streao << allBasicInfo.at(i)->calport;
        streao << allBasicInfo.at(i)->backport;
        streao << allBasicInfo.at(i)->planePosition;
        streao << allBasicInfo.at(i)->missionhong;
        streao << allBasicInfo.at(i)->jinzhan;
        streao << allBasicInfo.at(i)->time;

        QStringList list = allBasicInfo.at(i)->stationString.split(",");
        streao << quint16(list.size());
        for(int j=0;j<list.size();j++){
            streao << list.at(j);
            streao << QString("00");
        }
    }

    QList<Station*> stations = Station::selectAllStations();
    streao << quint16(stations.size());
    for(int i=0;i<stations.size();i++){
        streao << stations.at(i)->stationName;
        streao << stations.at(i)->stationIp;
    }
    QList<User*> users = User::selectAllUser();
    streao << quint16(users.size());
    for(int i=0;i<users.size();i++){
        streao << users.at(i)->code;
        streao << users.at(i)->name;
        streao << users.at(i)->phoneNumber;
        streao << users.at(i)->role;
        streao << users.at(i)->status;
        streao << users.at(i)->wrongTimes;
    }
    QList<QString> geshanList = GeShan::selectAllWenjianjia();
    streao << quint16(geshanList.size());
    for(int i=0;i<geshanList.size();i++){
        streao << geshanList.at(i);
        qDebug() << "发送的格栅" << geshanList.at(i);
    }
    QList<BaseBand*> baseBands = BaseBand::selectAllBaseBand();
    streao << quint16(baseBands.size());
    for(int i=0;i<baseBands.size();i++){
        streao << baseBands.at(i)->id;
        streao << baseBands.at(i)->stationName;
        streao << baseBands.at(i)->port;
    }
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xA1);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendNewMissionInfo(MissionBasicInfo *basic)
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
          << basic->missionhong << basic->time;
    streao << quint8(basic->stations.size());
    for(int i=0;i<basic->stations.size();i++){
        streao << basic->stations.at(i)->stationName;
        streao << basic->stations.at(i)->stationIp;
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xB1);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendRetrieveMissionInfo(QString code)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << code;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xB2);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAbortMissionInfo(QString code)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << code;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xB3);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendGoonMissionInfo(QString code)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << code;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xB4);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendMd5Result(quint8 result)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << result;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x98);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllHealthData(QList<HealthData *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << list.size();
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->name;
        streao << list.at(i)->delay;
        streao << list.at(i)->lost;
        streao << list.at(i)->status;
        streao << list.at(i)->dataIn;
    }
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xB9);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllProcessData(QList<ProcessEntity *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << list.size();
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->name;
        streao << list.at(i)->code;
        streao << list.at(i)->fileName;
        streao << list.at(i)->percent;
    }
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBA);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllGeShan(QList<GeShan *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);
    
    streao << quint64(list.size());
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->xuhao  << list.at(i)->name << list.at(i)->xinghaochangjia << list.at(i)->daihao << list.at(i)->chulipingtai
         << list.at(i)->xianshipingtai << list.at(i)->zhuangtaibeizhu << list.at(i)->jiesuanchengxu << list.at(i)->setup
         << list.at(i)->shifoujiami << list.at(i)->jiamixinxibeizhu << list.at(i)->xianshihuamianbanben
         << list.at(i)->jiesuanruanjianwenjianjia << list.at(i)->beizhu << list.at(i)->banbengengxinshijian
         << list.at(i)->people << list.at(i)->dianzigeshan << list.at(i)->filesize << list.at(i)->displayFilesize << list.at(i)->type;
    }
    
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBB);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::addGeshanComplete()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBC);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::addGeshanWrong()
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBD);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllChildfile(QList<ChildFile *> list,QString parent)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << quint64(list.size());
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->fileName << list.at(i)->fileSize;
    }
    streao << parent;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBE);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAdvanceResult(QList<MissionBasicInfo *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);
    QList<MissionBasicInfo *> allBasicInfo = list;
    streao<<quint16(allBasicInfo.size());
    for(int i=0;i<allBasicInfo.size();i++){
        streao << allBasicInfo.at(i)->code;
        streao << allBasicInfo.at(i)->basictime;
        streao << allBasicInfo.at(i)->starttime;
        streao << allBasicInfo.at(i)->endtime;
        streao << allBasicInfo.at(i)->protect;
        streao << allBasicInfo.at(i)->point;
        streao << allBasicInfo.at(i)->status;
        streao << allBasicInfo.at(i)->mainport;
        streao << allBasicInfo.at(i)->calport;
        streao << allBasicInfo.at(i)->backport;
        streao << allBasicInfo.at(i)->planePosition;
        streao << allBasicInfo.at(i)->missionhong;
        streao << allBasicInfo.at(i)->jinzhan;
        streao << allBasicInfo.at(i)->time;
        streao << quint16(allBasicInfo.at(i)->stations.size());
        for(int j=0;j<allBasicInfo.at(i)->stations.size();j++){
            streao << allBasicInfo.at(i)->stations.at(j)->stationName;
            streao << allBasicInfo.at(i)->stations.at(j)->stationIp;
        }
    }
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xBF);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDataAdvanceResult(QList<RemoteData *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << quint64(list.size());
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->code;
        streao << list.at(i)->model;
        streao << list.at(i)->time;
        streao << list.at(i)->type;
        streao << list.at(i)->fileName;
        streao << list.at(i)->fileSize;
        streao << list.at(i)->id;
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC4);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllRemote(QList<RemoteData *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << quint64(list.size());
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->code;
        streao << list.at(i)->model;
        streao << list.at(i)->time;
        streao << list.at(i)->type;
        streao << list.at(i)->fileName;
        streao << list.at(i)->fileSize;
        streao << list.at(i)->id;
        streao << list.at(i)->user;
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC0);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDataMd5(QByteArray array)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << array;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC1);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendDianziMd5(QByteArray array)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << array;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC2);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::sendAllFilelog(QList<FileLog *> list)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << quint64(list.size());
    for(int i=0;i<list.size();i++){
        streao << list.at(i)->people << list.at(i)->time << list.at(i)->operation << list.at(i)->fileName;
    }
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC3);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::deleteDataResult(int result)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << result;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC5);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::updateDataResult(int result)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << result;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC6);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray AgreeMent::updateGeshanResult(int result)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << result;
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0xC7);
    sendByte.append(sendByteo);
    return sendByte;
}
