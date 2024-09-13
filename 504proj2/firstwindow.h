#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDialog>
#include <QtCharts>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "progress.h"
#include "progress.h"
#include "receievedata.h"
#include "usermanage.h"
#include "stationmanage.h"
#include "missionmanage.h"
#include "gemanage.h"
#include "mutifile.h"
#include "writefiledata.h"
#include "battleform.h"
#include "directoryselect.h"
#include "delaytest.h"
#include "downloadtest.h"
#include "filedownloadwidget.h"
#include "writefile/writefileworker.h"
#include "fileinfo.h"
#include "remotedatawidget.h"
#include "entity/mission.h"
#include "entity/missionbasicinfo.h"
#include "entity/missionmacroinfo.h"
#include "healthdata.h"
#include "entity/user.h"
#include "datastatistic.h"
#include "entity/baseband.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class FirstWindow;
}
extern QJsonArray array2;
extern QUdpSocket *udpsocket;

extern QTcpServer *tcpServer;
extern QTcpSocket *tcpSocket1;
extern QTcpSocket *tcpSocket2;


extern QTcpServer *grilleTcpserver;
extern QTcpServer *displayTcpserver;

extern QList<MutiFile*> mutiFile;

extern QString currentUser;

extern FileDownLoadWidget *grilleWidget;
extern FileDownLoadWidget *displayWidget;

extern WriteFileWorker *grilleWorker;
extern WriteFileWorker *displayWorker;

extern RemoteDataWidget *p;

extern QList<MissionMacroInfo*> macroInfo;
extern QList<MissionBasicInfo*> basicInfo;
extern QList<Mission*> missionInfo;
extern QList<Station*> stationInfo;
extern QList<User*> userInfo;
extern QList<QString> geshanInfo;
extern QList<BaseBand*> baseBandInfo;

extern QString userName;

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();

    QTcpSocket *tcpSocket33;

    DataStatistic *dataStatistic = new DataStatistic();
    static int role;
    void initialAllCustomTableWidget();

    void initialMenuSlots();

    void post();
    void postback(QNetworkReply * reply);


    void post2(QString name);
    void postback2(QNetworkReply * reply);

    int tt=0;


    void post3();
    void postback3(QNetworkReply * reply);
    void post4(QString param);
    void postback4(QNetworkReply * reply);
    void print1();
    void print2();
    void print3();
    void print4();

    void initial_multiFile();
    void testDelay();

    void softewareInsert();

    QUdpSocket *testPackgeSocket;

    void setName(QString name);
    void setRoleText(int frame);


private:
    Ui::FirstWindow *ui;

    const quint8 SELFCHECKSUC = 0x00;
    const quint8 SELFCHECKFAIL = 0x01;

    const quint8 CHANGENODE = 0x00;
    const quint8 STOPCODE = 0x01;
    const quint8 RECALLCODE = 0x02;

    const quint8 STATUSA = 0x00;  // send
    const quint8 STATUSB = 0x01;  // reback
    const quint8 STATUSC = 0x02;  // update
    const quint8 STATUSD = 0x03;  // abort
    const quint8 STATUSE = 0x04;  // go on
    const quint8 STATUSF = 0x05;  // finished

    const quint8 MISSIONBACKSUC = 0x00;
    const quint8 MISSIONBACKFAIL = 0x01;

    const quint8 FILERECSUC = 0x01;
    const quint8 FILERECFAIL = 0x02;

    const quint8 RESEND = 0x01;
    const quint8 NOTRESEND = 0x02;
    QNetworkAccessManager * manager;
    QNetworkAccessManager * manager2;
    QNetworkAccessManager * manager3;
    QNetworkAccessManager * manager4;

    UserManage *pageUserManage;
    StationManage *pageStationManage;
    MissionManage *pageMissionManage;
    GeManage *pageGeManage;

    QTimer *m_pTimer;

    QTimer *m_pTimer2;

    QTimer *m_pTimer3;

    QTcpServer * tcpServer;//监听socket
    QTcpSocket * tcpSocket;//通信socket

    QByteArray arraylin;

    quint32 packageLength;


    void dealdata();
    void dealfiledata();

    void initialstack();
    void initialtcp();
    void connecttcprec(QTcpSocket *tcpSocket);

    void printStationInfo();

    void printMission();

    void setPushStyleSheet(QPushButton *button);
    void setCommonStyleSheet(QPushButton *button);

    void initialDataGeshanManage();

    QUdpSocket *testOutSocket;


//    QString fileName;
//    quint64 filesize;
//    quint64 sendsize;


//    quint64 recsize;



    bool isfile;

    int heart;

    int h;

    QString oldmissionNode;

    void printChart();




    void printUserInfo();

    int rowEdit;
    int rowEdit1;
    int rowEdit2;
    QString oldname;

    int isedit = 0;
    int isedit1 = 0;
    int isedit2 = 0;
    QTableWidgetItem *o;
    QTableWidgetItem *item;

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
        QString node;
        quint32 fileSize;
        quint32 fileBlockLength;
        quint32 beginPosition;
        char fileBlockData[4096];
        quint8 frame;
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
    struct Stackinfo{
        QString stackname;
        QString stackip;
    };
    Stackinfo oldStackInfo;

    void judgeUser(User user);
    void updateDatabase(MissionResult result);
    quint8 calChecksum(QByteArray array);
    void writeFile(File filestr);
    void writebase(File filestr);

    void printfile();

    progress *pro = new progress;
    DirectorySelect *dire = new DirectorySelect;

    File filestr;
    QFile file;
    QString filePath;


    quint32 sendsize = 0;
    QList<QString> fileNameList;
    QList<quint32> fileProgress;
    QComboBox *editor;

    QComboBox *editor2;

//    QTimer dataTimer;
    QTimer chartTimer;
    QTimer currentTimer;



    QColor *barColor;
    QBrush *a;
    QPen *pen;

    QVector<double> ticks;
    QVector<QString> labels;



    QVector<double> ticks2;
    QVector<QString> labels2;

    QVector<double> ticks3;
    QVector<QString> labels3;

    QVector<double> ticks4;
    QVector<double> ticks5;

    QVector<double> fossilData1;
    QVector<double> fossilData2;

    QLinearGradient plotGradient;



    QColor *barColor2;
    QBrush *b;

    receieveData *worker;
    WriteFiledata *worker2;
    DelayTest *worker3;
    DownLoadTest *worker4;


    QThread *grilleThread;

    QThread *displayThread;

    void printRTimeChart();

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

    quint8 analysis01(QByteArray array);
    SelfDetect analysis02(QByteArray array);
    Mission analysis03(QByteArray array);
    MissionResult analysis04(QByteArray array);
    quint8 analysis05(QByteArray array);
    healthInfo analysis06(QByteArray array);
    File analysis07(QByteArray array);
    User analysis09(QByteArray array);
    LoginResult analysis10(QByteArray array) ;
public:

    QByteArray getInvert(QByteArray array);
    BattleForm *battleForm = new BattleForm();


protected:
    void mousePressEvent(QMouseEvent *event);


public slots:
    void handleTimeout();  //超时处理函数

    void handleTimeout2();  //超时处理函数
    void handleTimeout3();  //超时处理函数

    void handleCurrentTime();

    void cellClickedSlot(int x, int y);
    void cellClickedSlot1(int x, int y);


    void getPro(QString filename,quint64 allsize,quint64 nowsize,QString node);
    void refreshMission();
    void getBattleBasicInfo(int num,QString code,QString fileName,quint64 range);

    void getFinish(int num,QString filename,QString code);
    void getDelayReturn(MutiFile *muti, int time);
    void getDownloadReturn(QString ip, int time);
    void getCurrentUser(QString user);
    void getDelete(QString ip);
    void logButtonPush();

    void initialGrille(QList<FileInfo*> list);

    void initialDisplay(QList<FileInfo*> list);

    void getGrilleProgress(quint64 pro);
    void getDisplayProgress(quint64 pro);

    void disconnectUserManage();
    void disconnectStationManage();
    void disconnectMissionManage();
    void disconnectBaseBandManage();
    void disconnectDataSourceManage();

    void refreshHealthData(QList<HealthData*> list);

    void testPackgeSocketSlot();
    void getDataMd5(QByteArray array);
    void getDianziMd5(QByteArray array);
private slots:
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_12_clicked();
    void testSlot(int x,int y);

    void on_tableWidget_customContextRequested(const QPoint &pos);

    void on_pushButton_clicked();

    void on_stackedWidget_customContextMenuRequested(const QPoint &pos);

    void on_tableWidget_4_customContextMenuRequested(const QPoint &pos);

    void readPendingDatagrams();




    void on_pushButton_9_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_6_clicked();

    void getNewStr(QString,int,int);
    void realtimeDataSlot();

    void realtimeChartSlot();

    void writeSendFile(QString fileName,QString node,
                       quint32 fileSize,quint32 fileBlockLength,
                       quint32 beginPosition,quint8 frame);
    void on_pushButton_16_clicked();


    void getUser(QString name,QString password,QHostAddress addr);



    void on_pushButton_23_clicked();

    void finishFile(QString filename,QString node);

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_tableWidget_5_customContextMenuRequested(const QPoint &pos);

    void refreshStationInfo();

    void on_tableWidget_6_customContextMenuRequested(const QPoint &pos);

    void cellClickedSlot2(int x, int y);

    void on_pushButton_17_clicked();

    void MenuUserSlots();
    void MenuStationSlots();
    void MenuMissionSlots();
    void MenuGeshanSlots();
    void MenuDirectorySlots();
    void MenuJidaiSlots();
    void MenuDatasourceSlots();

    void outSocketRead();
    void initialTimer();

    void on_pushButton_11_clicked();

signals:
    void SendData(int x,int y);
    void sendStr(int);

    void sendSocketData(quint64 pend,QByteArray arrayjudge,QHostAddress addr,quint16 port);
    void sendPro(QString filename,quint64 allsize,quint64 nowsize,QString node);

    void sendWriteFile(QByteArray ,int);
    void emitDelayTest(MutiFile*);
    void emitDelayDownloadTest(QString ip);
    void emitdeleteProgress(int num);

    void sendGrilleFileData(QByteArray);
    void sendDisplayFileData(QByteArray);
};

#endif // FIRSTWINDOW_H
