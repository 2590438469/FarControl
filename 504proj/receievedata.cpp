#include "receievedata.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QThread>
#include "agreement/agreement.h"
#include "agreement/agreementanalysis.h"
#include "filedownloadrquest.h"
#include "geshan.h"
#include "advance.h"
#include "remotedata.h"
#include "fileinfo.h"
#include "filelog.h"
#include "dataadvance.h"
#include "config/configinfo.h"

receieveData::receieveData(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<Advance*>>("QList<Advance*>");
    qRegisterMetaType<QList<RemoteData*>>("QList<RemoteData*>");
    qRegisterMetaType<QList<FileLog*>>("QList<FileLog*>");
}

void receieveData::readPendingDatagrams(quint64 pend,QByteArray arrjudge,QHostAddress addr,quint16 port){
//    QByteArray arrjudge;
//    arrjudge.resize(4);
    QByteArray arrCurrent;
    quint32 point = 0;
//    int x = udpsocket->readDatagram(arrjudge.data(),arrjudge.size());


//    while (udpsocket->hasPendingDatagrams()) //数据报等待被读取
//    {
//        qDebug() << "haspend";
//        point = 0;
//        quint64 socketava = udpsocket->bytesAvailable();
//        qDebug() << "socketava"<< socketava;
//        quint64 pend = udpsocket->pendingDatagramSize();

//        qDebug() << "pend ava " << pend << socketava;

//        arrjudge.resize(pend);
//        int x = udpsocket->readDatagram(arrjudge.data(),arrjudge.size());


//        arrjudge = getInvert(arrjudge);



        while(point !=pend){
            qDebug() << pend << point << QHostAddress(addr.toIPv4Address()).toString();
            qDebug() << "内部循环";


            if(quint8(arrjudge.at(0))==0x5A && quint8(arrjudge.at(1))==0x5A){
                QDataStream stre(&arrjudge,QIODevice::ReadOnly);
                stre.setVersion(QDataStream::Qt_5_1);
                stre.device()->seek(2);
                quint32 length;
                stre >> length;
                arrCurrent.resize(length+2);
                arrCurrent = arrjudge.mid(0,length+2);

                arrjudge = arrjudge.mid(length+2,arrjudge.size()-length-2);
//                arrjudge.resize(arrjudge.size()-length-2);

                point +=length+2;

                quint8 mesmark = quint8(arrCurrent.at(6));

                User user;
                File filestr;
                MissionResult result;
                QString filename;
                quint32 progress;
                File fileInfo;
                int isStationSubmitflag;
                quint8 fileRequestType;
                fileDownloadRquest *request;
                opResult opresult;
                QByteArray array;
                QString lastname;
                QVector<QString> Array;
                quint8 a;
                quint8 logo;
                MissionBasicInfo *basic;
                QString retrieveCode;
                QString abortCode;
                QString goonCode;
                GeShan *geshan;
                QList<GeShan*> geshanList;
                QString wenjianjia;
                QString deleteWenjianjia;
                ChildFile *deleteChild;
                Advance *advance;
                DataAdvance *dataAdvance;
                QList<RemoteData*> allRemote;
                QString dataFilename;
                FileInfo *md5ResultdataFilename;
                ChildFile *dianziXiazai;
                ChildFile *md5DianziResult;
                qDebug() << "消息类型" <<mesmark;
                FileInfo *dataInfo;
                FileLog *fileLog;
                QList<FileLog*> logList;
                QString deleteGeshanXuhao;
                RemoteData *updateRemote;
                GeShan *updateGeshan;
                GeshanAdvance *geshanAdvance;
                switch (mesmark) {
                case 0x09:
                     user = analysis09(arrCurrent);
                     emit sendUser(user.name,user.password,addr);
//                     judgeUser(user);

//                    analysis09(arrCurrent);
                    break;
                case 0x04:
                    result = analysis04(arrCurrent);
                    if (result.result==0x00){
                        emit finishSend();
                    }
                    break;
                case 0x11:
                    filename = analysis17(arrCurrent);
                    progress = fileProgress.at(fileNameList.indexOf(filename));
                    qDebug() << "文件进度" << progress;
                    udpsocket->writeDatagram(getInvert(s18(filename,progress)),QHostAddress::LocalHost,9010);
                    break;
                case 0x40:
                    fileInfo = analysis40(arrCurrent);
                    isStationSubmitflag = 0;
                    for(int i=0;i<mutiFile.size();i++){
                        if(mutiFile.at(i)->stationIp == QHostAddress(addr.toIPv4Address()).toString()){
                            qDebug() << "判断了";
                            qDebug() << "md5" << fileInfo.md5;
                            isStationSubmitflag = 1;
                            mutiFile.at(i)->filePath = fileInfo.fileName;
                            mutiFile.at(i)->fileSize = fileInfo.fileSize;
                            mutiFile.at(i)->code = fileInfo.code;
                            mutiFile.at(i)->type = fileInfo.type;
                            mutiFile.at(i)->md5 = fileInfo.md5;
                            mutiFile.at(i)->parentPath = fileInfo.parentPath;
                            mutiFile.at(i)->user = fileInfo.user;
                            mutiFile.at(i)->isgoon = fileInfo.isgoon;
                            if(fileInfo.isFolder==1){
                                backUp(fileInfo.parentPath);
                            }
                            emit signalSendBasicInfo(i,fileInfo.code,fileInfo.fileName,fileInfo.fileSize);
                            if(mutiFile.at(i)->isgoon==1){
                                udpsocket->writeDatagram(getInvert(sendReFile(fileInfo,isStationSubmitflag,mutiFile.at(i)->nowsize)),addr,port);
                                qDebug() << "继续的进度" << mutiFile.at(i)->nowsize;
                            }else{
                                udpsocket->writeDatagram(getInvert(sendReFile(fileInfo,isStationSubmitflag,0)),addr,port);
                            }
                            break;

                        }
                    }

                    break;
                case 0x42:
                    emit sendDelete(QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0x50:
                    emit sendAllMission(QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0x80:
                    qDebug() << "收到了文件下载的请求";
                    fileRequestType = AgreeMentAnalysis::analysisFileCheckRequest(arrCurrent);
                    if(fileRequestType == 0){
                        udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGrilleInfo()),addr,port);
                    }
                    if(fileRequestType == 1){
                        udpsocket->writeDatagram(getInvert(AgreeMent::sendAllDisplayInfo()),addr,port);
                    }
                    break;
                case 0x83:
                    qDebug() << "文件下载请求";
                    request = AgreeMentAnalysis::analysisFileDownloadRequest(arrCurrent);
                    request->stationIp = QHostAddress(addr.toIPv4Address()).toString();
                    emit sendDownLoadRuquest(request);
                    qDebug() <<"文件下载请求转发";
                    break;
                case 0xA0:
                    qDebug() << "接收到加载宏的请求";
                    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllMissionInfo()),addr,port);
                    break;

                case 0x90:
                    opresult = analysis_opResult(arrCurrent);
                    qDebug() << "opresult" << opresult.frame << opresult.opresult << opresult.logo;
                    Array = analysis90(arrCurrent);
                    a = addInfo(Array,opresult.logo);
                    array = PackAddInfo(a,opresult);
                    udpsocket->writeDatagram(getInvert(array),addr,port);
                    break;
                case 0x92:
                    opresult = analysis_opResult(arrCurrent);
                    qDebug() << "opresult" << opresult.frame << opresult.opresult << opresult.logo;
                    Array = analysis92(arrCurrent);
                    a = updateInfo(Array,opresult.logo);
                    array = PackAddInfo(a,opresult);
                    udpsocket->writeDatagram(getInvert(array),addr,port);
                    break;
                case 0x93:
                    opresult = analysis_opResult(arrCurrent);
                    qDebug() << "opresult" << opresult.frame << opresult.opresult << opresult.logo;
                    Array = analysis93(arrCurrent);
                    a = deleteInfo(Array,opresult.logo);
                    array = PackAddInfo(a,opresult);
                    udpsocket->writeDatagram(getInvert(array),addr,port);
                    break;
                case 0x95:
                    logo = analysis95(arrCurrent);
                    qDebug() << "接收到了logo:" << logo;
                    emit sendinfo(port,logo,addr);
                    break;
                case 0x96:
                    qDebug() << "接收到了lastname请求";
                    lastname = lastnameInfo();
                    qDebug() << lastname;
                    array = PacklastnameInfo(lastname);
                    udpsocket->writeDatagram(getInvert(array),addr,port);
                    break;
                case 0x98:
                    qDebug() << "接收到了login请求";
                    user = analysis98(arrCurrent);
                    opresult = judgeUser(user);
                    array = PackLoginInfo(opresult);
                    for(int i=0;i<mutiFile.size();i++){
                        if(mutiFile.at(i)->stationIp == QHostAddress(addr.toIPv4Address()).toString()){
                            udpsocket->writeDatagram(getInvert(array),addr,port);
                            break;
                        }
                    }
                    break;

                case 0xA1:
                    qDebug() << "任务发送请求";
                    basic = AgreeMentAnalysis::analusisNewMission(arrCurrent);
                    if(MissionBasicInfo::insertNewMission(basic)){
                        for(int i=0;i<FirstWindow::stations.size();i++){
                            QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
                            udpsocket->writeDatagram(getInvert(AgreeMent::sendNewMissionInfo(basic)),*addr,port);
                        }
                    }
                    //转发任务信息;
                    break;

                case 0xA2:
                    qDebug() << "撤回任务请求";
                    retrieveCode = AgreeMentAnalysis::analusisRetriveMission(arrCurrent);
                    MissionBasicInfo::deleleMission(retrieveCode);
                    for(int i=0;i<FirstWindow::stations.size();i++){
                        QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
                        udpsocket->writeDatagram(getInvert(AgreeMent::sendRetrieveMissionInfo(retrieveCode)),*addr,port);
                    }
                    break;
                case 0xA3:
                    qDebug() << "中止任务请求";
                    abortCode = AgreeMentAnalysis::analusisRetriveMission(arrCurrent);
                    MissionBasicInfo::updateJinzhan(abortCode,"已中止");
                    for(int i=0;i<FirstWindow::stations.size();i++){
                        QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
                        udpsocket->writeDatagram(getInvert(AgreeMent::sendAbortMissionInfo(abortCode)),*addr,port);
                    }
                    break;
                case 0xA4:
                    qDebug() << "继续任务请求";
                    goonCode = AgreeMentAnalysis::analusisgoonMission(arrCurrent);
                    MissionBasicInfo::updateJinzhan(goonCode,"已发送");
                    for(int i=0;i<FirstWindow::stations.size();i++){
                        QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
                        udpsocket->writeDatagram(getInvert(AgreeMent::sendGoonMissionInfo(goonCode)),*addr,port);
                    }
                    break;
                case 0xCA:
                    qDebug() << "geshan";
                    geshan = AgreeMentAnalysis::analusisGeshan(arrCurrent);
                    emit addNewGeshan(geshan,addr);
                    break;
                case 0xCB:
                    qDebug() << "请求格栅";
                    geshanList = GeShan::selectAllGeshan();
                    qDebug() << "格栅大小" << geshanList.size();
                    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllGeShan(geshanList)),addr,port);
                    break;

                case 0xCC:
                    wenjianjia = AgreeMentAnalysis::analusisChildGeshanRequest(arrCurrent);
                    emit sendWenJianjia(wenjianjia,addr);
                    break;

                case 0xCD:
                    qDebug() << "删除格栅";
                    deleteWenjianjia = AgreeMentAnalysis::analusisDeleteGeshan(arrCurrent);
                    emit sendDeleteGeshan(deleteWenjianjia,addr);
                    break;
                case 0xCE:
                    qDebug() << "删除子格栅";
                    deleteChild = AgreeMentAnalysis::analusisDeleteChildGeshan(arrCurrent);
                    emit sendDeleteChild(deleteChild,addr);
                    break;
                case 0xCF:
                    qDebug() <<"高级筛选";
                    advance = AgreeMentAnalysis::analusisAdvance(arrCurrent);
                    emit sendAdvance(advance,addr);
                    break;
                case 0xD0:
                    qDebug() <<"请求遥测管理";
                    allRemote = RemoteData::selectAllGeshan();
                    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllRemote(allRemote)),addr,port);
                    break;
                case 0xD1:
                    qDebug() << "请求下载遥测文件";
                    dataInfo = AgreeMentAnalysis::analusisDatadownloadRequest(arrCurrent);
                    emit sendDataDownfileRequest(dataInfo,QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0xD2:
                    qDebug() << "请求下载遥测文件";
                    md5ResultdataFilename = AgreeMentAnalysis::getMd5Result(arrCurrent);
                    emit sendMd5ResultFileName(md5ResultdataFilename,QHostAddress(addr.toIPv4Address()).toString());
                    break;

                case 0xD3:
                    qDebug() << "请求下载电子格栅文件";
                    dianziXiazai = AgreeMentAnalysis::analusisDianzidownloadRequest(arrCurrent);
                    emit sendDianziDownfileRequest(dianziXiazai,QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0xD4:
                    qDebug() << "请求下载电子格栅文件";
                    md5DianziResult = AgreeMentAnalysis::getDianziMd5Result(arrCurrent);
                    emit sendDianziMd5ResultFileName(md5DianziResult,QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0xD5:
                    qDebug() << "数据统计请求";
                    fileLog = AgreeMentAnalysis::analusisDataStatistic(arrCurrent);
                    logList = FileLog::selectByStation(fileLog);
                    udpsocket->writeDatagram(getInvert(AgreeMent::sendAllFilelog(logList)),addr,port);
                    break;
                case 0xD6:
                    qDebug() <<"数据高级筛选";
                    dataAdvance = AgreeMentAnalysis::analusisDataAdvance(arrCurrent);
                    emit sendDataAdvance(dataAdvance,addr);
                    break;
                case 0xD7:
                    qDebug() << "删除格栅";
                    deleteGeshanXuhao = AgreeMentAnalysis::analusisDeleteGeshan(arrCurrent);
                    if(RemoteData::deleteByXuhao(deleteGeshanXuhao)){
                        udpsocket->writeDatagram(getInvert(AgreeMent::deleteDataResult(1)),addr,port);
                    }else{
                        udpsocket->writeDatagram(getInvert(AgreeMent::deleteDataResult(0)),addr,port);
                    }
                    break;
                case 0xD8:
                    qDebug() << "更新遥测数据";
                    updateRemote = AgreeMentAnalysis::analusisUpdateInfo(arrCurrent);
                    udpsocket->writeDatagram(getInvert(AgreeMent::updateDataResult(RemoteData::updateDataByXuhao(updateRemote->code,updateRemote->type))),addr,port);
                    break;
                case 0xD9:
                    qDebug() << "更新格栅数据";
                    updateGeshan = AgreeMentAnalysis::analusisUpdateGeshan(arrCurrent);
                    udpsocket->writeDatagram(getInvert(AgreeMent::updateDataResult(GeShan::updateGeshan(updateGeshan))),addr,port);
                    break;
                case 0xDA:
                    qDebug() << "格栅高级筛选";
                    geshanAdvance = AgreeMentAnalysis::analusisGeshanAdvance(arrCurrent);
                    emit sendGeshanAdvance(geshanAdvance,addr);
                    break;

            }
        }
    }
}





receieveData::User  receieveData::analysis09(QByteArray array){
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    User user;

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> user.name >> user.password >> user.frame;

    qDebug() << "用户信息";
    qDebug() << user.name << user.password << user.frame;
//    qDebug() <<"test0";
//    int namelength = (int)array.at(4);
//    int pwlength = (int)array.at(25);
//    qDebug() <<"test1";
//    QString name = QString(array.mid(5,namelength));
//    QString password = QString(array.mid(26,pwlength));
//    int frame = (int)array.at(46);
//    user.name = name;
//    user.password = password;
//    user.frame = frame;
    return user;
}

QString receieveData::analysis17(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QString filename;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> filename;

    return filename;
}

receieveData::File receieveData::analysis40(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    File file;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> file.fileName >> file.fileSize >> file.code >> file.type >> file.md5 >> file.parentPath >> file.user >> file.isFolder >> file.isgoon;
    qDebug() << "解析的type" << file.type;

    return file;
}




receieveData::MissionResult receieveData::analysis04(QByteArray array){
    MissionResult missionresult;
    missionresult.result=quint8(array.at(7));
    missionresult.frame = quint8(array.at(8));
    return missionresult;
}

QByteArray receieveData::getInvert(QByteArray array)
{
    unsigned char k = 0x80;
    QByteArray invertArray;
    quint8 tempCharAsc = 0;
    char tempChar;
    invertArray.resize(array.size());
    for(int i=0;i<array.size();i++){
        for(int j=0;j<8;j++){
            if(quint8(array.at(i)) & k){
            }else{
                tempCharAsc += pow(2,7-j);
            }
            k >>=1;
        }
        tempChar = tempCharAsc;
        invertArray[i] = tempChar;
        tempChar = 0;
        tempCharAsc = 0;
        k = 0x80;
    }
    return invertArray;
}

QByteArray receieveData::s10(LoginResult loginResult){
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(0x07) << quint8(0x10)
            << quint8(loginResult.loginStatus) << quint8(loginResult.frame);


    return sendByte;
}

QByteArray receieveData::s18(QString fileName, quint32 position)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);
    strea<< quint8(0x5A) << quint8(0x5A) << quint32(4+1+4+fileName.size()*2+4+1+1) << quint8(0x18) << fileName
         << position << quint8(1) << quint8(1);
    return sendByte;
}

QByteArray receieveData::sendReFile(receieveData::File file, quint8 isok,quint64 nowSize)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << file.fileName << file.fileSize << file.code << isok << nowSize;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x41);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray receieveData::PackAddInfo(quint8 a,opResult opresult)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< a << opresult.frame << opresult.logo;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x91);
    sendByte.append(sendByteo);
    return sendByte;
}

receieveData::opResult receieveData::analysis_opResult(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.frame >> opresult.logo >> opresult.opresult;
    return opresult;
}

QVector<QString> receieveData::analysis90(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QVector<QString> Array;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.frame >> opresult.logo >> opresult.opresult;

    Array.resize(opresult.opresult);
    for(int i = 0;i < opresult.opresult;i++)
    {
        strea >> Array[i];
    }
    qDebug() << "1111";
    return Array;
}

//receieveData::UserInfo receieveData::analysis90(QByteArray array)
//{
//    QDataStream strea(&array,QIODevice::ReadOnly);
//    strea.setVersion(QDataStream::Qt_5_1);

//    quint8 head1;
//    quint8 head2;
//    quint32 noneLength;
//    quint8 dataStyle;
//    UserInfo user ;
//    quint8 logo;

//    strea >> head1 >> head2 >> noneLength >> dataStyle;
//    strea >> user.frame >> logo >> user.username >> user.realname
//            >> user.telenumber >> user.role >> user.status;
//    qDebug() << "1111";
//    return user;
//}

QVector<QString> receieveData::analysis92(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QVector<QString> Array;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.frame >> opresult.logo >> opresult.opresult;

    Array.resize(opresult.opresult+1);
    for(int i = 0;i <= opresult.opresult;i++)
    {
        strea >> Array[i];
    }
    qDebug() << "analysis92";
    return Array;
}

QVector<QString> receieveData::analysis93(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QVector<QString> Array;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.frame >> opresult.logo >> opresult.opresult;

    Array.resize(1);
    strea >> Array[0];
    qDebug() << "analysis93";
    return Array;
}

quint8 receieveData::analysis95(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    quint8 frame;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> frame;
    qDebug() << "frame:" << frame;
    return frame;
}

receieveData::User receieveData::analysis98(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    User user;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> user.name >> user.password;
    return user;
}

quint8 receieveData::addInfo(QVector<QString> Array,quint8 logo)
{
    QList<quint8> string_column_list;
    QString databasename;
    switch (logo) {
    case 0x00:
        databasename = QString("usernew");
        string_column_list << 0 << 1 << 2 << 3 << 4;
        qDebug() << "usernew";
        break;
    case 0x01:
        databasename = QString("stationnew");
        string_column_list << 0 << 1 << 2 << 3 << 4 << 5;
        break;
    case 0x02:
        databasename = QString("missionnew2");
        string_column_list << 0 << 1 << 3 << 4 << 6 << 10 << 11 << 13 << 14 << 15
                           << 16 << 18 << 20 << 22 << 23 << 24 << 25 << 26;
        break;
    case 0x03:
        databasename = QString("baseband");
        string_column_list << 0 << 1 << 3;
        qDebug() << "baseband";
        break;
    case 0x04:
        databasename = QString("datasource");
        string_column_list  << 0;
        qDebug() << "datasource";
        break;
    default:
        break;
    }

    QSqlQuery query(db);
    QString qs = QString("insert into %1 (").arg(databasename);
    QSqlQuery query1(db);
    QString qs1 = QString("SHOW COLUMNS FROM %1").arg(databasename);
    query1.exec(qs1);
    quint8 column = query1.size();
    qDebug() << column;
    if(databasename.compare(QString("usernew")) == 0)
    {
        column = 5;
    }
    if(databasename.compare(QString("stationnew")) == 0)
    {
        column = 6;
    }
    Array.resize(column);
    int i = 0;
    while (query1.next() && i < column)
    {
        qs.insert(qs.size(),"`");
        qs.insert(qs.size(),query1.value(0).toString());
        qs.insert(qs.size(),"`");
        qDebug() << query1.value(0).toString();
        qs.insert(qs.size(),",");
        i++;
    }
    qs.chop(1);
    qs.insert(qs.size(),")");
    qs.insert(qs.size(),"values(");
    qDebug() << "拼接后的字符串" << qs;

    for(int i = 0;i < column;i++)
    {
        if(Array[i]!=nullptr)
        {
            if(string_column_list.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),Array[i]);
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),Array[i]);
                if(Array[i]==""){
                    qs.insert(qs.size(),"NULL,");
                }else{
                    qs.insert(qs.size(),",");
                }
            }
            qDebug() << "ziduan" << Array[i];
        }
        else
        {
            if(string_column_list.contains(i))
            {
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),"',");
            }
            else
            {
                qs.insert(qs.size(),"NULL,");

            }
            qDebug() << "字段空" ;
        }
    }
    qs.chop(1);
    qs.insert(qs.size(),")");
    qDebug() << "拼接后的字符串" << qs;
    bool ok = query.exec(qs);
    if(ok)
    {
        return 0x01;
    }
    else
    {
        qDebug() << qs;
        qDebug() << query.lastError().text();
        return 0x00;
    }
}

quint8 receieveData::updateInfo(QVector<QString> Array,quint8 logo)
{
    QList<quint8> string_column_list;
    QString databasename;
    QString primaryKey;
    quint8 primaryKeyIndex;
    switch (logo) {
    case 0x00:
        databasename = QString("usernew");
        string_column_list << 0 << 1 << 2 << 3 << 4;
        primaryKeyIndex = 0;
        break;
    case 0x01:
        databasename = QString("stationnew");
        string_column_list << 0 << 1 << 2 << 3 << 4 << 5;
        primaryKeyIndex = 0;
        break;
    case 0x02:
        databasename = QString("missionnew2");
        string_column_list << 0 << 1 << 3 << 4 << 6 << 10 << 11 << 13 << 14 << 15
                           << 16 << 18 << 20 << 22 << 23 << 24 << 25 << 26;
        primaryKeyIndex = 25;
        break;
    case 0x03:
        databasename = QString("baseband");
        string_column_list << 0 << 1 << 3;
        primaryKeyIndex = 0;
        break;
    case 0x04:
        databasename = QString("datasource");
        string_column_list  << 0;
        primaryKeyIndex = 1;
        break;
    default:
        break;
    }

    QSqlQuery query(db);
    QString qs = QString("update %1 set ").arg(databasename);
    QSqlQuery query1(db);
    QString qs1 = QString("SHOW COLUMNS FROM %1").arg(databasename);
    query1.exec(qs1);
    quint8 column = query1.size();
    qDebug() << column;
    if(databasename.compare(QString("usernew")) == 0)
    {
        column = 5;
    }
    if(databasename.compare(QString("stationnew")) == 0)
    {
        column = 6;
    }
    Array.resize(column+1);
    qDebug() << "拼接后的字符串" << qs;
    for(int i=0;i<column;i++)
    {
        query1.next();
        if(Array[i]!=nullptr){
            if(string_column_list.contains(i)){
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),query1.value(0).toString());
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),Array[i]);
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),query1.value(0).toString());
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),Array[i]);
                qs.insert(qs.size(),",");
            }
        }else{
            if(string_column_list.contains(i)){
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),query1.value(0).toString());
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),query1.value(0).toString());
                qs.insert(qs.size(),"`");
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"NULL,");
                //qs.insert(qs.size(),",");
            }
        }
        if(i == primaryKeyIndex)
        {
            primaryKey = query1.value(0).toString();
        }
    }
    qs.chop(1);
    if(string_column_list.contains(primaryKeyIndex)){
        qs.insert(qs.size()," where ");
        qs.insert(qs.size(),primaryKey);
        qs.insert(qs.size()," = ");
        qs.insert(qs.size(),"'");
        qs.insert(qs.size(),Array[column]);
        qs.insert(qs.size(),"'");
    }else{
        qs.insert(qs.size()," where ");
        qs.insert(qs.size(),primaryKey);
        qs.insert(qs.size()," = ");
        qs.insert(qs.size(),Array[column]);
    }
    qDebug() << "拼接后的字符串" << qs;
    bool ok = query.exec(qs);
    if(ok)
    {
        return 0x01;
    }
    else
    {
        qDebug() << query.lastError().text();
        return 0x00;
    }
}


quint8 receieveData::deleteInfo(QVector<QString> Array,quint8 logo)
{
    QList<quint8> string_column_list;
    QString databasename;
    QString primaryKey;
    quint8 primaryKeyIndex;
    switch (logo) {
    case 0x00:
        databasename = QString("usernew");
        string_column_list << 0 << 1 << 2 << 3 << 4;
        primaryKeyIndex = 0;
        break;
    case 0x01:
        databasename = QString("stationnew");
        string_column_list << 0 << 1 << 2 << 3 << 4 << 5;
        primaryKeyIndex = 0;
        break;
    case 0x02:
        databasename = QString("missionnew2");
        string_column_list << 0 << 1 << 3 << 4 << 6 << 10 << 11 << 13 << 14 << 15
                           << 16 << 18 << 20 << 22 << 23 << 24 << 25 << 26;
        primaryKeyIndex = 25;
        break;
    case 0x03:
        databasename = QString("baseband");
        string_column_list << 0 << 1 << 3;
        primaryKeyIndex = 0;
        break;
    case 0x04:
        databasename = QString("datasource");
        string_column_list  << 0;
        primaryKeyIndex = 1;
        break;
    default:
        break;
    }
    QSqlQuery query(db);
    QString qs = QString("delete from %1 where ").arg(databasename);
    QString qs1 = QString("SHOW COLUMNS FROM %1").arg(databasename);
    QSqlQuery query1(db);
    query1.exec(qs1);
    quint8 column = query1.size();
    qDebug() << column;
    if(databasename.compare(QString("usernew")) == 0)
    {
        column = 5;
    }
    if(databasename.compare(QString("stationnew")) == 0)
    {
        column = 6;
    }
    Array.resize(1);
    for(int i=0;i<column;i++)
    {
        query1.next();
        if(i == primaryKeyIndex)
        {
            primaryKey = query1.value(0).toString();
        }
    }

    qs.insert(qs.size(),primaryKey);
    qs.insert(qs.size()," = ");
    if(string_column_list.contains(primaryKeyIndex)){
        qs.insert(qs.size(),"'");
        qs.insert(qs.size(),Array[0]);
        qs.insert(qs.size(),"'");
    }else{
        qs.insert(qs.size(),Array[0]);
    }
    qDebug() << "拼接后的字符串" << qs;
    bool ok = query.exec(qs);
    if(ok)
    {
        return 0x01;
    }
    else
    {
        qDebug() << qs;
        qDebug() << query.lastError().text();
        return 0x00;
    }
}

QString receieveData::lastnameInfo()
{
    QSqlQuery query(db);
    QString qs = QString("select name from loginlog where id = (select max(id) from loginlog)");
    query.exec(qs);
    QSqlRecord rec2 = query.record();
    int nameCol = rec2.indexOf("name");
    QString lastname;

    while (query.next())
    {
         lastname = query.value(nameCol).toString();
    }
    return lastname;
}

QByteArray receieveData::PacklastnameInfo(QString lastname)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< lastname;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x97);
    sendByte.append(sendByteo);
    return sendByte;
}

void receieveData::backUp(QString parentString)
{
    int fileid = GeShan::selectFileidByWenjianjia(parentString);
    QList<ChildFile*> list = ChildFile::selectByFileid(fileid);
    if(list.size()!=0) {
        QString dateDir = ConfigInfo::backupPath+"/"+parentString+"_"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm");
        QDir dir2;
        if (!dir2.mkdir(dateDir)) {
            qDebug() << "Failed to create folder";
        }else{
            qDebug() << "Folder created successfully";
        }
        for(int i=0;i<list.size();i++){
            copyFile(ConfigInfo::grillePath+"/"+parentString+"/"+list.at(i)->fileName,dateDir+"/");
        }
        QString dianzi = GeShan::selectDianziByWenjianjia(parentString);
        if(dianzi!=""){
            copyFile(ConfigInfo::grillePath+"/"+parentString+"/"+dianzi,dateDir+"/");
        }

        ChildFile::deleteByFildid(fileid);
    }

}

bool receieveData::copyFolder(const QString &srcFolderPath, const QString &destFolderPath)
{
    QDir srcDir(srcFolderPath);
        QDir destDir(destFolderPath);

        if (!srcDir.exists()) {
            qDebug() << "源文件夹不存在";
            return false;
        }

        if (!destDir.exists()) {
            destDir.mkdir(destFolderPath);
        }

        QStringList fileList = srcDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        foreach (const QString &fileName, fileList) {
            QString srcFilePath = srcDir.filePath(fileName);
            QString destFilePath = destDir.filePath(fileName);
            if (!QFile::copy(srcFilePath, destFilePath)) {
                qDebug() << "复制文件失败:" << srcFilePath;
                return false;
            }
        }

        QStringList subFolderList = srcDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (const QString &subFolder, subFolderList) {
            QString srcSubFolderPath = srcFolderPath + "/" + subFolder;
            QString destSubFolderPath = destFolderPath + "/" + subFolder;
            if (!copyFolder(srcSubFolderPath, destSubFolderPath)) {
                return false;
            }
        }

        return true;
}

bool receieveData::copyFile(QString sourcePath, QString destPath)
{
    QString sourceFilePath = sourcePath; // 源文件路径
    QString destinationFolderPath = destPath; // 目标文件夹路径

    // 创建源文件对象
    QFile sourceFile(sourceFilePath);

    // 获取源文件的文件名
    QString sourceFileName = QFileInfo(sourceFile).fileName();

    // 创建目标文件夹对象
    QDir destinationFolder(destinationFolderPath);

    // 确保目标文件夹存在，如果不存在则创建它
    if (!destinationFolder.exists()) {
        if (!destinationFolder.mkpath(".")) {
            qDebug() << "无法创建目标文件夹";
            return 1;
        }
    }

    // 构造目标文件的完整路径
    QString destinationFilePath = destinationFolderPath + sourceFileName;

    // 尝试复制文件
    if (sourceFile.copy(destinationFilePath)) {
        qDebug() << "文件复制成功";
    } else {
        qDebug() << "文件复制失败";
    }

}

receieveData::opResult receieveData::judgeUser(User user)
{
    opResult opresult;
    QSqlQuery query(db);
    QString qs = QString("select 密码,状态,角色 from usernew where 账号 ='%1'").arg(user.name);

    query.exec(qs);
    QSqlRecord rec = query.record();
    qDebug() << "1:Number of columns: " << rec.count();
    int passwordCol = rec.indexOf("密码");
    int statusCol = rec.indexOf("状态");
    int roleCol = rec.indexOf("角色");
    QString password1;
    QString status;
    QString role;
    int islock;

    if(!query.next())
    {
        //QMessageBox::information(this,"警告","用户名不存在！",QMessageBox::Ok);
        opresult.opresult = 0x03;
    }
    else
    {
        query.exec(qs);
        while (query.next())
        {
             password1 = query.value(passwordCol).toString();
             status = query.value(statusCol).toString();
             role = query.value(roleCol).toString();
        }

        if( (QString::compare(status, QString("正常"),Qt::CaseSensitive)) == 0)
        {
            islock = 0;
        }
        else
        {
            islock = 1;
        }

        QString qs1 = QString("select 错误次数 from usernew where 账号 ='%1'").arg(user.name);
        query.exec(qs1);
        QSqlRecord rec1 = query.record();
        qDebug() << "2:Number of columns: " << rec1.count();
        int errorCol = rec1.indexOf("错误次数");
        int error;
        while (query.next())
        {
             error = query.value(errorCol).toInt();
        }

        QString password2 = QCryptographicHash::hash(user.password.toLatin1(),QCryptographicHash::Md5).toHex();
        qDebug() << islock;
        int x = QString::compare(password1, password2,Qt::CaseSensitive);
        bool a;

        if(x == 0)
        {
            a = true;
        }
        else
        {
            a = false;
        }

        if(!a && islock!=1)
        {
            error++;
            QString qs3 = QString("update usernew set 错误次数 ='%1' where 账号 ='%2'").arg(error).arg(user.name);
            query.exec(qs3);
            if(error==3)
            {
                islock=1;
                QString qs2 = QString("update usernew set 状态 = '%2' where 账号 ='%1'").arg(user.name).arg("已锁定");
                query.exec(qs2);
                QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(user.name);
                query.exec(qs4);
            }
            //QMessageBox::information(this,"警告","密码错误！",QMessageBox::Ok);
            opresult.opresult = 0x00;
        }
        else if(a && islock!=1)
        {
            //QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);
            if( (QString::compare(role, QString("管理员"),Qt::CaseSensitive)) == 0)
            {
                opresult.frame = 0x00;
            }
            else if( (QString::compare(role, QString("地面站"),Qt::CaseSensitive)) == 0)
            {
                opresult.frame = 0x01;
            }else if( (QString::compare(role, QString("外单位"),Qt::CaseSensitive))== 0){
                opresult.frame = 0x02;
            }
            opresult.opresult = 0x01;
            if((QString::compare(role, QString("普通人员"),Qt::CaseSensitive))== 0){
                opresult.opresult = 0x03;
            }
            QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(user.name);
            query.exec(qs4);

            QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
            QString currenttime = dateTime.toString("hh时mm分ss秒");//格式化时间
            qDebug() << currenttime;
            qDebug() << name;
            QString qs5 = QString("insert into loginlog(name,logintime) values('%1','%2')").arg(user.name).arg(currenttime);
            qDebug() << query.exec(qs5);
            qDebug() << db.lastError().text();

        }
        else
        {
            //QMessageBox::information(this,"警告","三次错误输入密码，用户已被锁定，不可再登陆！",QMessageBox::Ok);
            opresult.opresult = 0x02;
        }
    }
    return opresult;
}

QByteArray receieveData::PackLoginInfo(opResult opresult)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< opresult.opresult << opresult.frame;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x99);
    sendByte.append(sendByteo);
    return sendByte;
}

