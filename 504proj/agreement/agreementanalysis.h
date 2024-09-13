#ifndef AGREEMENTANALYSIS_H
#define AGREEMENTANALYSIS_H

#include <QObject>
#include "filedownloadrquest.h"
#include "missionbasicinfo.h"
#include "geshan.h"
#include "childfile.h"
#include "advance.h"
#include "fileinfo.h"
#include "filelog.h"
#include "dataadvance.h"
#include "remotedata.h"
#include "geshanadvance.h"

class AgreeMentAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit AgreeMentAnalysis(QObject *parent = nullptr);
    static quint8 analysisFileCheckRequest(QByteArray array);
    static fileDownloadRquest* analysisFileDownloadRequest(QByteArray array);
    static quint8 analusisDllRequest(QByteArray array);

    static MissionBasicInfo* analusisNewMission(QByteArray array);
    static QString analusisRetriveMission(QByteArray array);
    static QString analusisabortMission(QByteArray array);
    static QString analusisgoonMission(QByteArray array);

    static QByteArray analusisMd5(QByteArray array);

    static GeShan* analusisGeshan(QByteArray array);
    static QString analusisDeleteGeshan(QByteArray array);

    static QString analusisChildGeshanRequest(QByteArray array);
    static ChildFile* analusisDeleteChildGeshan(QByteArray array);

    static Advance* analusisAdvance(QByteArray array);
    static DataAdvance *analusisDataAdvance(QByteArray array);
    static GeshanAdvance *analusisGeshanAdvance(QByteArray array);

    static FileInfo* analusisDatadownloadRequest(QByteArray array);
    static ChildFile* analusisDianzidownloadRequest(QByteArray array);

    static FileInfo* getMd5Result(QByteArray array);
    static ChildFile *getDianziMd5Result(QByteArray array);

    static FileLog *analusisDataStatistic(QByteArray array);

    static QString analusisDeleteData(QByteArray array);

    static RemoteData *analusisUpdateInfo(QByteArray array);

    static GeShan *analusisUpdateGeshan(QByteArray array);
signals:

public slots:
};

#endif // AGREEMENTANALYSIS_H
