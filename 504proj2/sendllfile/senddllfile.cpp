#include "senddllfile.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"
#include "math.h"
#include <QThread>
#include "mainwindow.h"
#include "firstwindow.h"
#include <QThread>
#include "config/configinfo.h"

 SendDllFile:: SendDllFile(QObject *parent) : QObject(parent)
{

    socket = new QTcpSocket(this);
}


void  SendDllFile::sendFile(QString filepath,quint64 progress){
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    socket = new QTcpSocket(this);
    qDebug() << "filepath" << filepath;
    QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
    if(socket->state() !=QAbstractSocket::ConnectingState){
        socket->connectToHost(*addr,9002);
        QAbstractSocket::SocketState state = socket->state();
        if(state!=QAbstractSocket::ConnectingState){
            qDebug() << "连接中心端失败";
        }else{
            qDebug() << "连接中心端成功";
        }
    }
    socket->waitForConnected(30000);

    qDebug() <<" 线程内部";
    qint32 len = 0;
    quint64 sendsize =0;
    QFile *file = new QFile();
    File filestr;
    quint8 times = 1;
    if(filepath.isEmpty()==false){
        QFileInfo info(filepath);
        filestr.fileName = info.fileName();
        filestr.fileSize = info.size();


        file->setFileName(filepath);

        bool isOk = file->open(QIODevice::ReadOnly);

        if(isOk == false){
            qDebug()<<"文件未成功打开 54";
        }
    }

    qDebug() << "test";
    qDebug() << sendsize << filestr.fileSize;

//    char *pTwoElement;
    file->seek(progress);
    sendsize = progress;
    do
    {
    //        filestr.fileBlockData.clear();
    //        filestr.fileBlockData.resize(0);

        char buf[64*1024] = {0};


        //read content
        len = file->read(buf,sizeof(buf));

        quint64 hassend;
        if(socket->state() == QAbstractSocket::ConnectedState){
            hassend = socket->write(buf,len);
            if(hassend==0&&len!=0){
                file->seek(sendsize);
            }
            socket->waitForBytesWritten(3000);

        }else{
            socket->disconnectFromHost();
            emit abortConnect();
            break;
        }


        sendsize+=hassend;//已发送多少文件内容
        if(len!=0){
            emit sendProgress(sendsize,filestr.fileSize);
        }

    }while(len>0);
    file->close();

}

void  SendDllFile::getpaused(int pau)
{
    qDebug() << "触发停止";
    ispaused = pau;
    qDebug() << ispaused;
}

void  SendDllFile::deleteSlot()
{
    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

QByteArray  SendDllFile::s07(File file){
    QByteArray array;

    QDataStream strea(&array,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    strea << quint8(0x5A) << quint8(0x5A) << quint32(4+1+4+20+file.fileName.size()*2+12+4096+1) << quint8(0x07) << nodenow;

    strea  << file.fileName;    //字节数加4，前四个字节为长度

    strea  << quint32(file.fileSize)<< quint32(file.fileBlockLength) << quint32(file.beginPosition);

    strea.writeRawData(file.fileBlockData,64*1024);

    strea    << quint8(file.frame);
    qDebug() << "new file";
    qDebug() << array.at(4128) <<array.at(4129) <<array.at(4130) <<array.at(4131);
    qDebug() << quint64(array.size());
    return array;
}

void  SendDllFile::initialSocket()
{

}

QByteArray  SendDllFile::getInvert(QByteArray array){
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
