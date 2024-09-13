#include "sendfile.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"
#include "math.h"
#include <QThread>
#include "mainwindow.h"
#include "firstwindow.h"
#include <QThread>
#include "util.h"
#include "config/configinfo.h"
#include <QNetworkProxy>

 sendfile:: sendfile(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

void  sendfile::sendFile( sendfile::FILE_TYPE type,QString stationIp,QString filename,quint64 progress,QString parentString){
    if(type == fileType&&stationIp == fileDestIp){
        qDebug() << "文件传输开始" << type << fileDestIp;
        addr = new QHostAddress(stationIp);

        quint16 lin = ConfigInfo::grilleTcpPort.toInt();
        port = &lin;
        filePath = ConfigInfo::datPath+"/"+parentString+"/"+filename;
        socket = new QTcpSocket(this);
        if(socket->state() !=QAbstractSocket::ConnectedState){
            socket->connectToHost(*addr,*port);
            socket->waitForConnected(5000);
            QAbstractSocket::SocketState state = socket->state();
            if(state!=QAbstractSocket::ConnectedState){
                qDebug() << "连接中心端失败" << stationIp << *port;
                qDebug() << socket->errorString();
            }else{
                qDebug() << "连接中心端成功";
            }
        }

        qDebug() <<" 线程内部";
        qint32 len = 0;
        quint64 sendsize =0;
        QFile file;
        quint8 times = 1;
        qDebug() << "文件路径" <<filePath;
        if(filePath.isEmpty()==false){
            QFileInfo info(filePath);
            fileName = info.fileName();
            fileSize = info.size();


            file.setFileName(filePath);

            bool isOk = file.open(QIODevice::ReadOnly);

            if(isOk == false){
                qDebug()<<"文件未成功打开 54";
            }
        }

        qDebug() << "test";
        qDebug() << sendsize << fileSize;

        file.seek(progress);
        sendsize = progress;
        int i=0;
        do
        {
            char buf[64*1024] = {0};


            //read content
            len = file.read(buf,sizeof(buf));

            quint64 hassend;
            if(socket->state() == QAbstractSocket::ConnectedState){
                qDebug() << "写数据";
                hassend = socket->write(buf,len);
                qDebug() << "发送的字节" << hassend;
                i++;
                qDebug() << "发送的包的个数"<< i;
                if(hassend==0&&len!=0){
                    file.seek(sendsize);
                }
                socket->waitForBytesWritten(3000);

            }else{
                qDebug() << "停写数据";
                socket->disconnectFromHost();
                emit abortConnect();
                break;
            }


            sendsize+=hassend;//已发送多少文件内容
            if(len!=0){
                emit sendProgress(sendsize,fileSize);
            }

        }while(len>0);
        file.close();
        QThread::sleep(1);
//        socket->disconnectFromHost();
//        socket->close();
//        socket->deleteLater();
    }

}

void sendfile::sendAbortFile(sendfile::FILE_TYPE type, QString stationIp, QString filename, quint64 progress)
{
    if(type == fileType&&stationIp == fileDestIp){
        qDebug() << "文件传输开始" << type << fileDestIp;
        addr = new QHostAddress(stationIp);

        quint16 lin = ConfigInfo::grilleTcpPort.toInt();
        port = &lin;
//        filePath = ConfigInfo::datPath+"/"+filename;

        socket = new QTcpSocket(this);
        if(socket->state() !=QAbstractSocket::ConnectedState){
            socket->connectToHost(*addr,*port);
            socket->waitForConnected(5000);
            QAbstractSocket::SocketState state = socket->state();
            if(state!=QAbstractSocket::ConnectedState){
                qDebug() << "连接中心端失败" << stationIp << *port;
                qDebug() << socket->errorString();
            }else{
                qDebug() << "连接中心端成功";
            }
        }

        qDebug() <<" 线程内部";
        qint32 len = 0;
        quint64 sendsize =0;
        QFile file;
        quint8 times = 1;
        qDebug() << "文件路径" <<filePath;
        if(filePath.isEmpty()==false){
            QFileInfo info(filePath);
            fileName = info.fileName();
            fileSize = info.size();


            file.setFileName(filePath);

            bool isOk = file.open(QIODevice::ReadOnly);

            if(isOk == false){
                qDebug()<<"文件未成功打开 54";
            }
        }

        qDebug() << "test";
        qDebug() << sendsize << fileSize;

        file.seek(progress);
        qDebug() << "progress"<< progress;
        sendsize = progress;
        int i=0;
        do
        {
            char buf[64*1024] = {0};


            //read content
            len = file.read(buf,sizeof(buf));

            quint64 hassend;
            if(socket->state() == QAbstractSocket::ConnectedState){
                qDebug() << "写数据";
                hassend = socket->write(buf,len);
                qDebug() << "发送的字节" << hassend;
                i++;
                qDebug() << "发送的包的个数"<< i;
                if(hassend==0&&len!=0){
                    file.seek(sendsize);
                }
                socket->waitForBytesWritten(3000);

            }else{
                qDebug() << "停写数据";
                socket->disconnectFromHost();
                emit abortConnect();
                break;
            }


            sendsize+=hassend;//已发送多少文件内容
            if(len!=0){
                emit sendProgress(sendsize,fileSize);
            }

        }while(len>0);
        file.close();
        QThread::sleep(1);
//        socket->disconnectFromHost();
//        socket->close();
//        socket->deleteLater();
    }
}

void sendfile::sendDianziFile(sendfile::FILE_TYPE type, QString stationIp, QString filename, quint64 progress, QString parentString)
{
    if(type == fileType&&stationIp == fileDestIp){
        qDebug() << "文件传输开始" << type << fileDestIp;
        addr = new QHostAddress(stationIp);

        quint16 lin = ConfigInfo::grilleTcpPort.toInt();
        port = &lin;
        filePath = ConfigInfo::grillePath+"/"+parentString+"/"+filename;

        socket = new QTcpSocket(this);
        if(socket->state() !=QAbstractSocket::ConnectingState){
            socket->connectToHost(*addr,*port);
            socket->waitForConnected(5000);
            QAbstractSocket::SocketState state = socket->state();
            if(state!=QAbstractSocket::ConnectingState){
                qDebug() << "连接中心端失败";
            }else{
                qDebug() << "连接中心端成功";
            }
        }

        qDebug() <<" 线程内部";
        qint32 len = 0;
        quint64 sendsize =0;
        QFile file;
        quint8 times = 1;
        qDebug() << "文件路径" <<filePath;
        if(filePath.isEmpty()==false){
            QFileInfo info(filePath);
            fileName = info.fileName();
            fileSize = info.size();


            file.setFileName(filePath);

            bool isOk = file.open(QIODevice::ReadOnly);

            if(isOk == false){
                qDebug()<<"文件未成功打开 54";
            }
        }

        qDebug() << "test";
        qDebug() << sendsize << fileSize;

        file.seek(progress);
        sendsize = progress;
        int i=0;
        do
        {
            char buf[64*1024] = {0};


            //read content
            len = file.read(buf,sizeof(buf));

            quint64 hassend;
            if(socket->state() == QAbstractSocket::ConnectedState){
                qDebug() << "写数据";
                hassend = socket->write(buf,len);
                qDebug() << "发送的字节" << hassend;
                i++;
                qDebug() << "发送的包的个数"<< i;
                if(hassend==0&&len!=0){
                    file.seek(sendsize);
                }
                socket->waitForBytesWritten(3000);

            }else{
                qDebug() << "停写数据";
                socket->disconnectFromHost();
                emit abortConnect();
                break;
            }


            sendsize+=hassend;//已发送多少文件内容
            if(len!=0){
                emit sendProgress(sendsize,fileSize);
            }

        }while(len>0);
        file.close();
        QThread::sleep(1);
//        socket->disconnectFromHost();
//        socket->close();
//        socket->deleteLater();
    }
}


void  sendfile::deleteSlot()
{
    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

void  sendfile::initialSocket()
{

}

QByteArray  sendfile::getInvert(QByteArray array){
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

void  sendfile::setPort(QString tcpPort)
{
    quint16 port16= tcpPort.toInt();
    port = &port16;
}

void  sendfile::setAddr(QString tcpAddr)
{
    addr = new QHostAddress(tcpAddr);
    fileDestIp = tcpAddr;
}
