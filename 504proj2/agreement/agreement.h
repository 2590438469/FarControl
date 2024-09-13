#ifndef AGREEMENT_H
#define AGREEMENT_H

#include <QObject>
#include "entity/missionbasicinfo.h"
#include "entity/geshan.h"
#include "entity/advance.h"
#include "entity/statistic.h"
#include "entity/dataadvance.h"
#include "entity/geshanadvance.h"

class AgreeMent : public QObject
{
    Q_OBJECT
public:
    explicit AgreeMent(QObject *parent = nullptr);
    enum FILE_TYPES{
        GRILLE = 0,
        DISPLAY = 1
    };

    static QByteArray sendCheckAllFileCatalog(AgreeMent::FILE_TYPES type);
    static QByteArray sendFileDownLoadRequest(FILE_TYPES type,QString fileName);
    static QByteArray sendAllMissionRequest();

    static QByteArray sendNewMission(MissionBasicInfo *basic);
    static QByteArray retrieveMission(QString missionCode);
    static QByteArray abortMission(QString missionCode);
    static QByteArray goonMission(QString missionCode);

    static QByteArray sendFileInfo(QString fileName,quint64 fileSize,QString code,quint8 type,QByteArray md5,QString parent,QString user,quint8 isFolder,quint8 isgoon);

    static QByteArray sendDllMd5(QByteArray array);

    static QByteArray sendGeshan(GeShan *geshan);
    static QByteArray sendDeleteGeshan(QString wenjianjia);

    static QByteArray requestGeshan();
    static QByteArray requestGeshanChildFile(QString child);
    static QByteArray requestRemoteGeshan();

    static QByteArray sendDeleteChildGeshan(QString child,QString parent);

    static QByteArray sendAdvanceSearch(Advance *advance);
    static QByteArray sendDataAdvanceSearch(DataAdvance *advance);
    static QByteArray sendGeshanAdvanceSearch(GeshanAdvance *advance);

    static QByteArray sendDownloadRemoteRequest(QString fileName,QString user,QString parentPath);
    static QByteArray sendDownloadDianziRequest(QString parentName,QString fileName,QString user);

    static QByteArray Datamd5StorgeFinish(QString fileName,quint64 progress,QString parent);
    static QByteArray Dianzimd5StorgeFinish(QString parentString ,QString fileName);

    static QByteArray sendStatistic(Statistic *statistic);

    static QByteArray deleteRemoteData(QString xuhao);

    static QByteArray sendUpdateData(QString xuhao,QString type);

    static QByteArray sendUpdateGeshan(GeShan *geshan);

signals:

public slots:
};

#endif // AGREEMENT_H
