#ifndef TEMPFRAMEPARSER_H
#define TEMPFRAMEPARSER_H

#include <algorithm>

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>

#include "utils.h"
#include "frameparser_interface.h"
#include "module_interface.h"


const int MAX_PACKAGE_LENGTH = 65536;
const int LEN_PLANE_NAME = 13;//飞机名长度13；
const int LEN_PLANE_NO = 7;//飞机号长度7
const char SOURCE_NAME[10] = "DY000_00";

//0803包头
#pragma pack(1)
struct _send_data_head_0803{
    uint packLen;   //报的长度，字节数 （无符号长整数） 4
    uint packNo;    //报的序列号，从1开始递加（无符号长整数） 4
    ushort streamNo; // 数据流序号   （无符号短整型数数）2
    char  planeName[LEN_PLANE_NAME]; //飞机名  13
    char  planeNo[LEN_PLANE_NO];     //飞机号  7
    short flightNum; //飞行架次 2
    char  dataType;  //数据类型（0：PCM，1：GPS） 1
    short parNum;    //参数总个数 （=实际参数个数+8） 2
    char  state;     //数据状态（0：正常，1：数据丢失）1
    char  source[8]; //数据源信息（DY998_10）8
    int ftime[8];
};
#pragma pack()

//1004包头
#pragma pack(1)
struct _send_data_head_1004{
    uint   packLen;                  //1-4 整个报（含包头）的长度，字节数 （无符号长整数）  ~
    uint   packNo;                   //5-8 报的序列号，从1开始递加（无符号长整数）          ~
    ushort streamNo;                 //9-10 数据流序号   （无符号短帧数）                   ~
    char   chSrcName[20];            //数据源名称
    ushort flightNum;                //31-32 当数据类型为0或1时表示飞行架次，数据类型为2时表示异步块类型值 ~
    char   dataType;                 //33 数据类型（0：PCM，1：外测，2：异步块原码）        ~
    short  parNum;                   //34－35 参数总个数 （=实际参数个数+8）                ~
    char   state;                    //36 数据状态（0：正常，1：数据丢失）                  ~
    uchar   sourceNo;                 //37 数据源序号
    uchar   sourceType;               //38 数据源类型
    uint    planeID;                  //39-42 飞机唯一标识，即飞机编号，和内测原始数据中的飞机号一致。
    uchar   workMode;                 //43 工作模式，0:实时，大于等于1:回放                  0
    uchar   reversed1;               //44 备用
    ushort  sample;                 //45-46 当数据类型为0或1时表示工程数据发送频率，数据类型为2时此项保留   32
    uchar   reversed2;               //47 备用
    uchar   reversed3;               //48 备用
    int ftime[8];
    float hour;
    float minute;
    float second;
    float millsecond;
};
#pragma pack()


//时间处理
//addr 是遥测八个字节时间的起始位置
void ProcessTime(float  &h, float &m, float &s, float &ms, const unsigned char *addr);

class ViewPackageHelper : public QObject
{
    Q_OBJECT
public:
    explicit ViewPackageHelper(
            int sourceNo, //数据流号
            FrameParserInterface *frameParser,
            QObject *parent = nullptr
    );
    ~ViewPackageHelper();
protected:
    char buffer[MAX_PACKAGE_LENGTH];
    char char_map[255];
    int satel_now_ptr;
    int source_no, para_num, frame_length;
    int send_data_length;
    int isendpacks;
    float h,m,s,ms;
    uint plane_id;
    PreHeadTypeEnum system;
    int package_head_size;
    QString plane_name, plane_no;

    FrameParserInterface *frame_parser;
    char time_stamp[50];
    int last_hour, last_minute, last_second;

    float *pfloatresult;
    int  *ftimeptr;
    Result8Bytes *result_ptr;

    _send_data_head_1004 send_data_head_1004;
    _send_data_head_1004 *send_data_head_1004_ptr;

    _send_data_head_0803 send_data_head_0803;
    _send_data_head_0803 *send_data_head_0803_ptr;

    void PrepareSendDataHead();
    char log_buffer[4096];
    void PrepareSendDataHeadTimeStamp(int h, int m, int s, int ms);
    void init_char_map();
signals:
    void resultReady(const char *sendBuff, int pkgLen);
    void timeStampRaised(const QString &time_str);
public slots:
    void onPackageArrived(const char *pkg, int pkg_len);
};

#endif // TEMPFRAMEPARSER_H
