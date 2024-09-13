#include "writefiledata.h"
#include <QDebug>
#include <QFileInfo>

WriteFiledata::WriteFiledata(QObject *parent) : QObject(parent)
{

}



void WriteFiledata::setFile(QString filePath)
{
    file = new QFile;
    filename = filePath;
    file->setFileName(filePath);
    qDebug() << "设置文件名" << filePath;
    bool isok = file->open(QIODevice::WriteOnly);
    if(false == isok){
        qDebug()<<"文件打开失败";
    }else{
        qDebug()<<"文件打开成功";
    }
}

void WriteFiledata::setFileSize(quint64 size)
{
    fileSize = size;
}

void WriteFiledata::setNum(int num)
{
    number = num;
}

void WriteFiledata::setCode(QString code)
{
    missionCode = code;
}

void WriteFiledata::writeFile(QByteArray fileData, int num)
{
    if(num==number){
//        qDebug() << "写文件信息" << info->fileName() << "字节" << fileData.at(0);
        qint64 len = file->write(fileData);
        file->waitForBytesWritten(30000);
        quint64 nowsize = file->size();

        emit sentValue(number,nowsize);
        if(nowsize == fileSize){
            file->close();
            emit finishWrite(number,filename,missionCode);
            file->deleteLater();
        }
    }
}
