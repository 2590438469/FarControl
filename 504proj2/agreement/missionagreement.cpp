#include "missionagreement.h"
#include "QDataStream"
#include <QDebug>
#include "entity/header.h"

#define  P_UNKOWN         -1	// 无效命令
#define  P_LOGIN               1    // 系统登录命令
#define  P_LOGOUT             2    // 注销命令
#define  P_CONFIG              3	 // 配置命令
#define  P_DOWNLOAD_SETUP  4    // 下载SETUP文件
#define  P_START_SETUP        5    // 启动传送SETUP文件
#define  P_QUERY_DATA        6    // 查询数据文件基本信息
#define  P_EXPORT_SETUP      7    // 从文件导出SETUP文件
#define  P_RUN_MODE          8    // 选择运行模式（实时、回放）
#define  P_RUN_CONTROL       9    // 运行控制
#define  P_VERSION             10   // 版本查询
#define 	P_RUN_STATUS         11   // 基本运行状态查询
#define  P_QUERY_STREAM      12  // 查询某个数据文件的数据流等详细信息
#define  P_STATUS_UP           13   // 状态上传命令
#define  P_MESSAGE            14   //即时通讯（聊天）
#define  P_GET_PWD            15   //获取系统口令
#define  P_GET_ZHCONFIG      16   // 主控从综合服务获取配置
#define  P_PUT_ZHCONFIG       17  // 主控向综合服务发送配置
#define  P_SYSLOG_MAN        18   // 系统日志管理命令
#define  P_FTP_DOWNLOAD     19  // 通过FTP从数据库下载SETUP命令
#define  P_STREAM_LIST        20  // 得到所有飞机流列表的命令
#define  P_RECORD_CTRL       21  // 对综合存储软件的记录控制命令
#define  P_YCKZ_STATUS       22  // 主控状态命令
#define  P_VIDEO_TARGET　　　23  // 获取视频目标信息命令
#define  P_GET_PARANAME     30  //主控从综合存储软件得到参数信息

#define  TYPE_CMD     0
#define  TYPE_REPLY    1

MissionAgreement::MissionAgreement(QObject *parent) : QObject(parent)
{

}

QByteArray MissionAgreement::packHead(Header *header)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    strea << header->head << header->packType << header->sourceType << header->sourceNum
          << header->targetType << header->targetNum << header->packgeLenth
          << header->commendType << header->param1 << header->param2
          << header->param3 << header->param4;
    return sendByte;
}

QByteArray MissionAgreement::sendLogin(LoginInfo *info)
{
    QByteArray sendByte;

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao.writeRawData(info->user,sizeof(info->user));
    streao.writeRawData(info->pwd,sizeof(info->pwd));

    Header *header = new Header();
    header->packType = TYPE_CMD;
    header->sourceType = 1;
    header->sourceNum = 0;
    header->targetType = 0;
    header->targetNum = 0;
    header->packgeLenth = sendByteo.size();
    header->commendType = P_LOGIN;
    header->param1 = 8002;

    sendByte = packHead(header);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray MissionAgreement::getStreamList()
{
    QByteArray sendByte;

    Header *header = new Header();
    header->packType = TYPE_CMD;
    header->sourceType = 1;
    header->sourceNum = 0;
    header->targetType = 0;
    header->targetNum = 0;
    header->packgeLenth = 0;
    header->commendType = P_FTP_DOWNLOAD;

    sendByte = packHead(header);
    return sendByte;
}

QByteArray MissionAgreement::sendConfig()
{
    QByteArray sendByte;

    Header *header = new Header();
    header->packType = TYPE_CMD;
    header->sourceType = 1;
    header->sourceNum = 0;
    header->targetType = 0;
    header->targetNum = 0;
    header->packgeLenth = 0;
    header->commendType = P_PUT_ZHCONFIG;

    sendByte = packHead(header);
    return sendByte;
}
