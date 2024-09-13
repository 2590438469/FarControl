#ifndef MISSIONSENDWIDGET_H
#define MISSIONSENDWIDGET_H

#include <QWidget>
#include <QByteArray>
#include "basicform.h"
#include "missionnewreview.h"

namespace Ui {
class MissionSendWidget;
}

class MissionSendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MissionSendWidget(QWidget *parent = nullptr);
    ~MissionSendWidget();
    QByteArray getInvert(QByteArray array);

private:
    Ui::MissionSendWidget *ui;

    enum TableWidgetStatusFlag {
        TableWidgetEditFlag = 2,
        TableWidgetAddFlag = 1,
        TableWidgetCompleteFlag = 0
    };

    struct MissionSend
    {
        quint8 refreshorinitial;    //第五位的0x01表示更新，0x00表示初始化
        QString code;
        QString basictime;
        QString starttime;
        QString endtime;
        QString protect;
        QString point;
        QString status;
        quint32 mainport;
        quint32 calport;
        quint32 backport;
        QString missionhong;
    };
    struct MissionNew2
    {
        QString maxing;
        QString malv;
        quint32 zichang;
        quint32 zhenchang;
        QString zhenmazu;
        quint32 zhenmazuchang;
        QString fuzhenfangshi;
        quint32 fuzhenchang;
        quint32 idziweizhi;
        quint32 idzijizhi;
        QString idzijishu;
        QString jiemizhuangtai;
        quint32 xunhuanfuzhenweizhi;
        QString xunhuanfuzhenmazu;
        QString duofuhaojianyan;
        QString tpc;
        QString kuaitongbuzhenmazu;
        quint32 AGC;
        QString zhongpindaikuan;
        quint32 AFC;
        QString AFCmoshi;
        quint32 jiaowucha;
        QString gongzuodianpin;
        QString xinghao;
        QString miaoshu;
        QString biaoshi;
    };
    TableWidgetStatusFlag tableWidget_status = TableWidgetCompleteFlag;


    void editFinish();
    void addFinish();

    void initial_basic_info();
    QByteArray sendMissionInfo(MissionSend missionBasic,MissionNew2 hong,QString status);
    QByteArray withdrawMissionInfo(MissionSend missionBasic,MissionNew2 hong);
    QByteArray abortMissionInfo(MissionSend missionBasic,MissionNew2 hong);
    QByteArray goonMissionInfo(MissionSend missionBasic,MissionNew2 hong);

    int currentRow;
    int tablewidgetLenth;
    QList<QString> oldValue;
    void resizeEvent(QResizeEvent *event);


public:
    BasicForm *bac = new BasicForm;

    MissionNewReview *review = new MissionNewReview;



public slots:
    void edit_basicInfo();
    void updateBasicInfo();
    void initial_widgetHeader();
    void initial_slots();

    void addButton_slot();
//    void deleteButton_slot();
    void finishButton_slot();
    void sendButton_slot();
    void abortButton_slot();

    void missionExport();
    void sendAllMission(QString ip);

    void doubleClick(int row,int column);
//    void editButton_slot();
//    void searchButton_slot();

    void initial_table_item();

    void deleteButton();

    void editButtonSlot();


    void checkStationSlot();

    void advanceCheckSlot();

    void getAdvanceResultString(QString resultString);

    void finishSend(QString code);
};

#endif // MISSIONSENDWIDGET_H
