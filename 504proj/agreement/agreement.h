#ifndef AGREEMENT_H
#define AGREEMENT_H

#include <QObject>
#include "missionbasicinfo.h"
#include "healthdata.h"
#include "processentity.h"
#include "geshan.h"
#include "childfile.h"
#include "remotedata.h"
#include "filelog.h"

class AgreeMent : public QObject
{
    Q_OBJECT
public:
    explicit AgreeMent(QObject *parent = nullptr);
    static QByteArray sendAllGrilleInfo();
    static QByteArray sendAllDisplayInfo();
    static QByteArray sendAllMissionInfo();

    static QByteArray sendNewMissionInfo(MissionBasicInfo *basic);
    static QByteArray sendRetrieveMissionInfo(QString code);
    static QByteArray sendAbortMissionInfo(QString code);
    static QByteArray sendGoonMissionInfo(QString code);

    static QByteArray sendMd5Result(quint8 result);

    static QByteArray sendAllHealthData(QList<HealthData*> list);

    static QByteArray sendAllProcessData(QList<ProcessEntity*> list);

    static QByteArray sendAllGeShan(QList<GeShan*> list);

    static QByteArray addGeshanComplete();

    static QByteArray addGeshanWrong();

    static QByteArray sendAllChildfile(QList<ChildFile *> list,QString parent);

    static QByteArray sendAdvanceResult(QList<MissionBasicInfo*> list);
    static QByteArray sendDataAdvanceResult(QList<RemoteData*> list);

    static QByteArray sendAllRemote(QList<RemoteData*> list);

    static QByteArray sendDataMd5(QByteArray array);
    static QByteArray sendDianziMd5(QByteArray array);

    static QByteArray sendAllFilelog(QList<FileLog*> list);

    static QByteArray deleteDataResult(int result);
    static QByteArray updateDataResult(int result);

    static QByteArray updateGeshanResult(int result);

signals:

public slots:
};

#endif // AGREEMENT_H
