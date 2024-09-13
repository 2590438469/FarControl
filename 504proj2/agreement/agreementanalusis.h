#ifndef AGREEMENTANALUSIS_H
#define AGREEMENTANALUSIS_H

#include <QObject>
#include <fileinfo.h>
#include <QMetaType>
#include "entity/missionbasicinfo.h"
#include "healthdata.h"
#include "entity/processentity.h"
#include "entity/geshan.h"
#include "entity/childfile.h"
#include "entity/childfilewithparent.h"
#include "entity/remotedata.h"
#include "entity/filelog.h"
class AgreeMentAnalusis : public QObject
{
    Q_OBJECT
public:
    explicit AgreeMentAnalusis(QObject *parent = nullptr);
    static QList<FileInfo*> analysisGrilleFileInfo(QByteArray array);
    static QList<FileInfo*> analysisDisplayFileInfo(QByteArray array);
    static void analysisAllMissionInfo(QByteArray array);

    static MissionBasicInfo* analusisNewMission(QByteArray array);
    static QString analusisRetrieveMission(QByteArray array);
    static QString analusisAbortMission(QByteArray array);
    static QString analusisGoonMission(QByteArray array);

    static quint8 analusisMd5(QByteArray array);

    static QList<HealthData*> analusisHealthData(QByteArray array);

    static QList<ProcessEntity*> analusisProcessData(QByteArray array);

    static QList<GeShan *> analusisAllGeshan(QByteArray array);

    static ChildFileWithParent* analusisChildFile(QByteArray array);

    static QList<MissionBasicInfo *> analusisAdvanceResult(QByteArray array);
    static QList<RemoteData *> analusisDataAdvanceResult(QByteArray array);

    static QList<RemoteData *> analusisAllRemote(QByteArray array);

    static QByteArray analusisDataMd5(QByteArray array);
    static QByteArray analusisDianziMd5(QByteArray array);

    static QList<FileLog *> analusisStatisticResult(QByteArray array);

    static int analusisDeleteDataResult(QByteArray array);
    static int analusisUpdateDataResult(QByteArray array);


    static int analusisUpdateGeshanResult(QByteArray array);

    static quint64 analusisRefile(QByteArray array);

signals:

public slots:
};

#endif // AGREEMENTANALUSIS_H
