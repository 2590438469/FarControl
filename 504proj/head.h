//0803包头
#pragma pack(1)
#include <QObject>
#define LEN_PLANE_NAME 13
#define LEN_PLANE_NO 7
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
    int ftime[8];                    //49-56
    float hour;
    float minute;
    float second;
    float millsecond;
};
#pragma pack()
