#include "missionagreementanalusis.h"
#include "entity/header.h"
#include <QDataStream>
#include "math.h"

MissionAgreementAnalusis::MissionAgreementAnalusis(QObject *parent) : QObject(parent)
{

}

int MissionAgreementAnalusis::analusisLoginResult(QByteArray array)
{
    Header *header = new Header();
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea >> header->head >> header->packType >> header->sourceType >> header->sourceNum
          >> header->targetType >> header->targetNum >> header->packgeLenth
          >> header->commendType >> header->param1 >> header->param2
          >> header->param3 >> header->param4;
    int result = header->param1%2^16;
    return result;
}

QList<PlaneStream *> MissionAgreementAnalusis::analusisPlaneStream(QByteArray array)
{
    QList<PlaneStream *> list;
    Header *header = new Header();
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea >> header->head >> header->packType >> header->sourceType >> header->sourceNum
          >> header->targetType >> header->targetNum >> header->packgeLenth
          >> header->commendType >> header->param1 >> header->param2
          >> header->param3 >> header->param4;
    for(int i=0;i<header->packgeLenth;i++){
        PlaneStream *planeStream = new PlaneStream();
        strea.readRawData(planeStream->streamName,sizeof(planeStream->streamName));
        strea >> planeStream->streamType;

        strea.readRawData(planeStream->setupName,sizeof(planeStream->setupName));
        strea >> planeStream->videoFlag
              >> planeStream->GPSFlag;
        list.append(planeStream);
    }
    return list;
}

int MissionAgreementAnalusis::analusisConfigResult(QByteArray array)
{
    Header *header = new Header();
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea >> header->head >> header->packType >> header->sourceType >> header->sourceNum
          >> header->targetType >> header->targetNum >> header->packgeLenth
          >> header->commendType >> header->param1 >> header->param2
          >> header->param3 >> header->param4;
    return header->param1;
}
