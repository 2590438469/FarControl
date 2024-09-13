#include "receievedata.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QThread>
#include "agreement/agreementanalusis.h"
#include "fileinfo.h"
#include "healthdata.h"
#include "entity/processentity.h"
#include "entity/childfile.h"
#include "entity/childfilewithparent.h"
#include "entity/remotedata.h"
#include "entity/filelog.h"

receieveData::receieveData(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<FileInfo*>>("QList<FileInfo*>");
    qRegisterMetaType<QList<HealthData*>>("QList<HealthData*>");
    qRegisterMetaType<QList<ProcessEntity*>>("QList<ProcessEntity*>");
    qRegisterMetaType<QList<GeShan*>>("QList<GeShan*>");
    qRegisterMetaType<QList<ChildFile*>>("QList<ChildFile*>");
    qRegisterMetaType<QList<MissionBasicInfo*>>("QList<MissionBasicInfo*>");
    qRegisterMetaType<QList<RemoteData*>>("QList<RemoteData*>");
    qRegisterMetaType<QList<FileLog*>>("QList<FileLog*>");
//    qRegisterMetaType<ChildFileWithParent*>("ChildFileWithParent*");
}

void receieveData::readPendingDatagrams(quint64 pend,QByteArray arrjudge,QHostAddress addr,quint16 port){
//    QByteArray arrjudge;
//    arrjudge.resize(4);
    QByteArray arrCurrent;
    quint32 point = 0;
    for(int i=0;i<arrjudge.size();i++){
        if(quint8(arrjudge.at(i))==0x5A){
        }
    }
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
                opResult opresult;
                QList<FileInfo*> grilleFileList;
                QString lastname;
                QList<FileInfo*> displayFileList;
                QVector<QVector<QString>> array;
                MissionBasicInfo *newMission;
                QString retrieveMissionCode;
                QString abortMissionCode;
                QString goonMissionCode;
                quint8 md5Result;
                QList<HealthData*> healthList;
                QList<ProcessEntity*> processList;
                QList<GeShan*> geshanList;
                QList<ChildFile *> childFileList;
                ChildFileWithParent *withParent;
                QList<MissionBasicInfo*> advanceList;
                QList<RemoteData*> allRemote;
                QList<RemoteData*> allRemoteAdvanceList;
                QByteArray md5Array;
                QByteArray dianziMd5Array;
                QList<FileLog*> statisResultList;
                quint64 resuFile;
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
                            isStationSubmitflag = 1;
                            mutiFile.at(i)->filePath = fileInfo.fileName;
                            mutiFile.at(i)->fileSize = fileInfo.fileSize;
                            mutiFile.at(i)->code = fileInfo.code;
                            emit signalSendBasicInfo(i,fileInfo.code,fileInfo.fileName,fileInfo.fileSize);
                        }
                    }
                    udpsocket->writeDatagram(getInvert(sendReFile(fileInfo,isStationSubmitflag)),addr,9010);
                    break;
                case 0x42:
                    emit sendDelete(QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0x50:
                    emit sendAllMission(QHostAddress(addr.toIPv4Address()).toString());
                    break;
                case 0x81:
                    qDebug() << 81;
                    grilleFileList = AgreeMentAnalusis::analysisGrilleFileInfo(arrCurrent);
                    emit initialGrille(grilleFileList);
                    qDebug() << "解析完成";
                    break;
                case 0x82:
                    qDebug() << 82;
                    displayFileList = AgreeMentAnalusis::analysisDisplayFileInfo(arrCurrent);
                    emit initialDisplay(displayFileList);
                    break;
                case 0x91:
                    opresult = analysis91(arrCurrent);
                    qDebug() << "结果" << opresult.frame << "opresult.logo" << opresult.logo;
                    switch (opresult.logo) {
                    case 0x00:
                        emit sendAddUserResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x01:
                        emit sendStationResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x02:
                        emit sendMissionResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x03:
                        emit sendBaseBandResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x04:
                        emit sendDataSourceResult(opresult.opresult,opresult.frame,array);
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x94:
                    qDebug() << "94";
                    opresult = analysis941(arrCurrent);
                    array = analysis942(arrCurrent);
                    switch (opresult.logo) {
                    case 0x00:
                        emit sendAddUserResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x01:
                        emit sendStationResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x02:
                        emit sendMissionResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x03:
                        emit sendBaseBandResult(opresult.opresult,opresult.frame,array);
                        break;
                    case 0x04:
                        emit sendDataSourceResult(opresult.opresult,opresult.frame,array);
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x97:
                    lastname = analysis97(arrCurrent);
                    qDebug() << lastname;
                    emit setLastname(lastname);
                    break;
                case 0x99:
                    opresult = analysis99(arrCurrent);
                    qDebug() << "LoginResult" << opresult.opresult << opresult.frame;
                    emit login(opresult);
                    break;
                case 0xA1:
                    qDebug() << "91的消息";
                    AgreeMentAnalusis::analysisAllMissionInfo(arrCurrent);
                    emit refreshAllMission();
                    break;
                case 0x41:
                    qDebug() << "文件开始发送";
                    resuFile = AgreeMentAnalusis::analusisRefile(arrCurrent);
                    emit startSendDllFile(resuFile);
                    break;
                case 0xB1:
                    qDebug() << "任务更新";
                    newMission = AgreeMentAnalusis::analusisNewMission(arrCurrent);
                    emit addNewMission(newMission);
                    break;
                case 0xB2:
                    qDebug() << "任务撤回";
                    retrieveMissionCode = AgreeMentAnalusis::analusisRetrieveMission(arrCurrent);
                    emit retrieveMission(retrieveMissionCode);
                    break;
                case 0xB3:
                    qDebug() << "任务中止";
                    abortMissionCode = AgreeMentAnalusis::analusisAbortMission(arrCurrent);
                    emit abortMission(abortMissionCode);
                    break;
                case 0xB4:
                    qDebug() << "任务继续";
                    goonMissionCode = AgreeMentAnalusis::analusisGoonMission(arrCurrent);
                    emit goonMission(goonMissionCode);
                    break;

                case 0x98:
                    qDebug() << "md5校验结束";
                    md5Result = AgreeMentAnalusis::analusisMd5(arrCurrent);
                    emit sendMd5Result(md5Result);
                    break;

                case 0xB9:
                    healthList = AgreeMentAnalusis::analusisHealthData(arrCurrent);
                    emit sendHealthData(healthList);
                    break;

                case 0xBA:
                    processList = AgreeMentAnalusis::analusisProcessData(arrCurrent);
                    emit sendProcessData(processList);
                    break;

                case 0xBB:
                    qDebug() << "geshan全部";
                    geshanList = AgreeMentAnalusis::analusisAllGeshan(arrCurrent);
                    qDebug() << "大小" << geshanList.size();
                    emit sendAllGeshan(geshanList);
                    break;
                case 0xBC:
                    emit finishAddGeshan();
                    break;
                case 0xBD:
                    emit wrongAddGeshan();
                    break;
                case 0xBE:
                    qDebug() << "刷新子文件信息";
                    withParent = AgreeMentAnalusis::analusisChildFile(arrCurrent);
                    emit sendChildFile(withParent);
                    break;
                case 0xBF:
                    qDebug() << "高级筛选";
                    advanceList = AgreeMentAnalusis::analusisAdvanceResult(arrCurrent);
                    emit sendAdvanceResult(advanceList);
                    break;
                case 0xC0:
                    qDebug() << "刷新遥测管理界面";
                    allRemote = AgreeMentAnalusis::analusisAllRemote(arrCurrent);
                    emit sendAllRemote(allRemote);
                    break;

                case 0xC1:
                    qDebug() << "存储遥测文件md5";
                    md5Array = AgreeMentAnalusis::analusisDataMd5(arrCurrent);
                    emit sendDataMd5(md5Array);
                    break;
                case 0xC2:
                    qDebug() << "存储电子文件md5";
                    md5Array = AgreeMentAnalusis::analusisDianziMd5(arrCurrent);
                    emit sendDianziMd5(md5Array);
                    break;
                case 0xC3:
                    qDebug() << "加载筛选结果";
                    statisResultList = AgreeMentAnalusis::analusisStatisticResult(arrCurrent);
                    emit sendStatisticResult(statisResultList);
                    break;

                case 0xC4:
                    qDebug() << "遥测数据高级筛选结果";
                    allRemoteAdvanceList = AgreeMentAnalusis::analusisDataAdvanceResult(arrCurrent);
                    emit sendDataAdvanceResult(allRemoteAdvanceList);
                    break;
                case 0xC5:
                    qDebug() << "删除遥测结果";
                    emit sendDeleteDataResult(AgreeMentAnalusis::analusisDeleteDataResult(arrCurrent));
                    break;
                case 0xC6:
                    qDebug() << "更新遥测结果";
                    emit sendUpdateDataResult(AgreeMentAnalusis::analusisUpdateDataResult(arrCurrent));
                    break;
                case 0xC7:
                    qDebug() << "更新格栅结果";
                    emit sendUpdateGeshanResult(AgreeMentAnalusis::analusisUpdateGeshanResult(arrCurrent));
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
    strea >> file.fileName >> file.fileSize >> file.code;

    return file;
}




receieveData::MissionResult receieveData::analysis04(QByteArray array){
    MissionResult missionresult;
    missionresult.result=quint8(array.at(7));
    missionresult.frame = quint8(array.at(8));
    return missionresult;
}



void receieveData::judgeUser(User user){
    QSqlQuery query(db);
        QString qs = QString("select 密码,状态 from usernew where 账号 ='%1'").arg(user.name);

        query.exec(qs);
        QSqlRecord rec = query.record();
        qDebug() << "1:Number of columns: " << rec.count();
        int passwordCol = rec.indexOf("密码");
        int statusCol = rec.indexOf("状态");
        QString password1;
        QString status;
        int islock;

        if(!query.next())
        {
            LoginResult result;
            result.loginStatus = 0x01;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);
        }
        else
        {
            query.exec(qs);
            while (query.next())
            {
                 password1 = query.value(passwordCol).toString();
                 status = query.value(statusCol).toString();
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
            int x = QString::compare(password1, password2);
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
            LoginResult result;
            result.loginStatus = 0x01;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);

        }
        else if(a && islock!=1)
        {
            //QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);
            LoginResult result;
            result.loginStatus = 0x00;
            result.frame = 1;
            QByteArray array = s10(result);
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);

            QString qs4 = QString("update usernew set 错误次数 = 0 where 账号 ='%1'").arg(user.name);
            query.exec(qs4);

    //        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    //        QString currenttime = dateTime.toString("hh时mm分ss秒");//格式化时间
    //        qDebug() << currenttime;
    //        qDebug() << name;
    //        QString qs5 = QString("insert into loginlog(name,logintime) values('%1','%2')").arg(user.name).arg(currenttime);
    //        query.exec(qs5);

        }
        else
        {
            qDebug() << "用户被锁定";
        }
        }
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

QByteArray receieveData::sendReFile(receieveData::File file, quint8 isok)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao << file.fileName << file.fileSize << file.code << isok;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x41);
    sendByte.append(sendByteo);
    return sendByte;
}

receieveData::opResult receieveData::analysis91(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.opresult >> opresult.frame >> opresult.logo;
    qDebug() << "222233333";
    return opresult;
}

receieveData::opResult receieveData::analysis941(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    opResult opresult;
    quint8 column;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.opresult >> column >> opresult.frame >> opresult.logo;
    return opresult;
}

QVector<QVector<QString>> receieveData::analysis942(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    opResult opresult;
    quint8 column;
    quint8 logo;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.opresult >> column >> opresult.frame >> logo;

    QVector<QVector<QString>> arr;
    //设置数组大小
    arr.resize(opresult.opresult);
    for(int j=0;j<arr.size();j++)
    {
        arr[j].resize(column);
    }

    for(int i = 0;i < opresult.opresult;i++)
    {
        for(int j = 0;j < column;j++)
        {
            strea >> arr[i][j];
        }
    }
    qDebug() << "接受界面初始信息";
    return arr;
}

QString receieveData::analysis97(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    QString lastname;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> lastname;

    return lastname;
}

receieveData::opResult receieveData::analysis99(QByteArray array)
{
    QDataStream strea(&array,QIODevice::ReadOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    quint8 head1;
    quint8 head2;
    quint32 noneLength;
    quint8 dataStyle;
    opResult opresult;

    strea >> head1 >> head2 >> noneLength >> dataStyle;
    strea >> opresult.opresult >> opresult.frame;

    return opresult;
}
