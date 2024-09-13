#include "sendfile.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"
#include "math.h"
#include <QThread>
#include "firstwindow.h"

sendfile::sendfile(QObject *parent) : QObject(parent)
{

}


void sendfile::sendFile(QString filepath, QString node,QString ip1,QString ip2){
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qDebug() << "触发了发送文件的信号";
    qDebug() << "查看参数"  << filepath << node;
    qint32 len = 0;
    quint64 sendsize =0;
    QFile file;
    File filestr;
    quint8 times = 1;
    nodenow = node;
    if(filepath.isEmpty()==false){
        QFileInfo info(filepath);
        filestr.fileName = info.fileName();
        filestr.fileSize = info.size();


        file.setFileName(filepath);

        bool isOk = file.open(QIODevice::ReadOnly);

        if(isOk == false){
            qDebug()<<"文件未成功打开 54";
        }
    }


//    char *pTwoElement;
    do
    {
//        filestr.fileBlockData.clear();
//        filestr.fileBlockData.resize(0);

        char buf[4096] = {0};


        //read content
        len = file.read(buf,sizeof(buf));
//        pTwoElement = (buf);


        filestr.fileBlockLength = len;

        for(int i=0;i<len;i++){
            filestr.fileBlockData[i] = buf[i];
        }
        filestr.beginPosition = sendsize;
        filestr.frame = times;

        filestr.node = node;
        times++;
        QByteArray array = s07(filestr);
        qDebug() << "两个头："<< quint8(array.at(0)) << quint8(array.at(1));
        qDebug() << "第一千五百个字节";
        qDebug() << array.at(1500);


        if(QString::compare(ip1,QString(""))!=0){
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress(ip1),9010);
            qDebug() << "socket发送了多少字节" << hassend;
        }
        if(QString::compare(ip2,QString(""))!=0){
            quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress(ip2),9010);
            qDebug() << "socket发送了多少字节" << hassend;
        }
//        quint64 hassend = udpsocket->writeDatagram(getInvert(array),QHostAddress::LocalHost,9010);
//        qDebug() << "socket发送了多少字节" << hassend;

        sendsize+=len;//已发送多少文件内容
        emit sendPro(sendsize,filestr.fileSize);
        QThread::msleep(4);


    }while(sendsize<filestr.fileSize);
}

QByteArray sendfile::s07(File file){
    QByteArray array;

    QDataStream strea(&array,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    strea << quint8(0x5A) << quint8(0x5A) << quint32(4+1+4+20+file.fileName.size()*2+12+4096+1) << quint8(0x07) << nodenow;

    strea  << file.fileName;    //字节数加4，前四个字节为长度

    strea  << quint32(file.fileSize)<< quint32(file.fileBlockLength) << quint32(file.beginPosition);

    strea.writeRawData(file.fileBlockData,4096);

    strea    << quint8(file.frame);
    qDebug() << "new file";
    qDebug() << array.at(4128) <<array.at(4129) <<array.at(4130) <<array.at(4131);
    qDebug() << quint64(array.size());
    return array;
}

QByteArray sendfile::getInvert(QByteArray array){
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
