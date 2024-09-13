#ifndef RECEIEVEDATA_H
#define RECEIEVEDATA_H

#include <QObject>
#include <QUdpSocket>
#include "fileinfo.h"
#include "entity/missionbasicinfo.h"
#include "healthdata.h"
#include "entity/processentity.h"
#include "entity/geshan.h"
#include "entity/childfile.h"
#include "entity/childfilewithparent.h"
#include "entity/remotedata.h"
#include "entity/filelog.h"

class receieveData : public QObject
{
    Q_OBJECT
public:
    explicit receieveData(QObject *parent = nullptr);
    struct opResult
    {
        quint8 opresult;
        quint8 frame;
        quint8 logo;
    };

    struct User
    {
        QString name;
        QString password;
        quint8 frame;
    };

    struct SelfDetect
    {
        quint8 resultMes;
        quint8 frame;
    };

    struct Mission
    {
        QString greatNode;
        quint8 greatVersion;
        quint8 changeMark;
        quint8 startYear;
        quint8 startMonth;
        quint8 startDay;
        quint8 startHour;
        quint8 startMinute;
        quint8 endYear;
        quint8 endMonth;
        quint8 endDay;
        quint8 endHour;
        quint8 endMinute;
        QString modelName;
        quint8 missionStatus;
        QString memberId;
        quint8 frame;
        quint8 checksum;
    };

    struct MissionResult
    {
        quint8 result;
        quint8 frame;
    };

    struct healthInfo
    {
        quint8 stationNode;
        quint8 frame;
    };

    struct LoginResult
    {
        quint8 loginStatus;
        quint8 frame;
    };

    struct File{
        QString fileName;
        quint64 fileSize;
        QString code;
    };
    struct UserLoginSend{
        quint8 header1 = 0x5A;
        quint8 header2 = 0x5A;
        quint8 dataLength = 0x2E;
        quint8 mesMark = 0x09;
        quint8 nameLength;
        char name[20];
        quint8 passwordLength;
        char password[20];
        quint8 frame;
        quint8 checksum;
    };
    QList<QString> fileNameList;
    QList<quint32> fileProgress;

    QByteArray s01(quint8 frame);
    QByteArray s02(SelfDetect selfDetect);
    QByteArray s03(Mission mission);
    QByteArray s04(MissionResult missionResult);
    QByteArray s05(quint8 frame);
    QByteArray s06(healthInfo info);
    QByteArray s07(File file);
//    QByteArray s08(file);
    QByteArray s09(User user);
    QByteArray s10(LoginResult loginResult) ;
    QByteArray s18(QString fileName,quint32 position);
    QByteArray sendReFile(File file,quint8 isok);

    quint8 analysis01(QByteArray array);
    SelfDetect analysis02(QByteArray array);
    Mission analysis03(QByteArray array);
    MissionResult analysis04(QByteArray array);
    quint8 analysis05(QByteArray array);
    healthInfo analysis06(QByteArray array);
    File analysis07(QByteArray array);
    User analysis09(QByteArray array);
    LoginResult analysis10(QByteArray array) ;
    QString analysis17(QByteArray array) ;
    File analysis40(QByteArray array);

    QByteArray getInvert(QByteArray array);
    quint8 calChecksum(QByteArray array);
    void writeFile(File filestr);
    void judgeUser(User user);
    void writebase(File filestr);

    opResult analysis91(QByteArray array);
    opResult analysis941(QByteArray array);
    QVector<QVector<QString>> analysis942(QByteArray array);
    QVector<QVector<QString>> analysis96(QByteArray array);
    QString analysis97(QByteArray array);
    opResult analysis99(QByteArray array);



signals:

    void sendPro(QString filename,quint64 allsize,quint64 nowsize,QString node);
    void sendWriteFile(QString fileName,QString node,
        quint32 fileSize,quint32 fileBlockLength,
        quint32 beginPosition,quint8 frame);
    void sendUser(QString name,QString password,QHostAddress addr);
    void finishSend();
    void signalSendBasicInfo(int num,QString code,QString fileName,quint64 range);
    void sendAllMission(QString ip);
    void sendDelete(QString ip);
    void initialGrille(QList<FileInfo*>);
    void initialDisplay(QList<FileInfo*>);
    void refreshAllMission();

    void sendAddUserResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array);
    void sendStationResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array);
    void sendMissionResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array);
    void sendBaseBandResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array);
    void sendDataSourceResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array);
    void sendMissionInitial(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

    void setLastname(QString lastname);
    void login(opResult opresult);

    void startSendDllFile(quint64);

    void addNewMission(MissionBasicInfo*);
    void retrieveMission(QString code);
    void abortMission(QString code);
    void goonMission(QString code);

    void sendMd5Result(quint8);

    void sendHealthData(QList<HealthData*>);
    void sendProcessData(QList<ProcessEntity*>);

    void sendAllGeshan(QList<GeShan *>);
    void finishAddGeshan();
    void wrongAddGeshan();

    void sendChildFile(ChildFileWithParent*);

    void sendAdvanceResult(QList<MissionBasicInfo*>);
    void sendDataAdvanceResult(QList<RemoteData*>);

    void sendAllRemote(QList<RemoteData *>);

    void sendDataMd5(QByteArray);
    void sendDianziMd5(QByteArray);

    void sendStatisticResult(QList<FileLog*>);

    void sendDeleteDataResult(int);
    void sendUpdateDataResult(int);


    void sendUpdateGeshanResult(int);

public slots:
    void readPendingDatagrams(quint64 pend,QByteArray arrjudge,QHostAddress addr,quint16 port);
};

#endif // RECEIEVEDATA_H
