#include "writefiledata.h"
#include <QDebug>
#include <QFileInfo>
#include "config/configinfo.h"
#include "mainwindow.h"
#include "firstwindow.h"

WriteFiledata::WriteFiledata(QObject *parent) : QObject(parent)
{
    file = new QFile;
}



void WriteFiledata::setFile(QString filePath)
{
    file->close();
    file = new QFile;
    filename = filePath;
    QString dateDir = parentPath;
    QDir dir2;
    if (!dir2.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
        qDebug() << dateDir;
    }else{
        qDebug() << "Folder created successfully";
    }
    file->setFileName(parentPath+ filePath);
    qDebug() << "设置文件名" << filePath;
    bool isok = file->open(QIODevice::WriteOnly);
    if(false == isok){
        qDebug()<<"文件打开失败";
    }else{
        qDebug()<<"文件打开成功";
    }
}

void WriteFiledata::setFile2(QString filePath)
{
    file->close();
    file = new QFile;
    filename = filePath;
    file->setFileName(parentPath+ filePath);
    qDebug() << "设置文件名" << filePath;
    bool isok = file->open(QIODevice::Append);
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

void WriteFiledata::setType(int type)
{
    this->type = type;
    if(type == 0){
        parentPath = ConfigInfo::datPath;
        qDebug() << "类型0";
        return;
    }
    if(type == 2){
        parentPath = ConfigInfo::grillePath;
        qDebug() << "类型2";
    }
    if(type == 3){
        parentPath = ConfigInfo::grillePath;
        qDebug() << "类型3";
    }
    if(type == 4){
        parentPath = ConfigInfo::grillePath;
        qDebug() << "类型4";
    }
}

void WriteFiledata::setParentPath(QString parent)
{
    parentPath = parentPath+"/"+parent+"/";
}

void WriteFiledata::writeFile(QByteArray fileData, int num)
{
    if(num==number){
//        qDebug() << "写文件信息" << info->fileName() << "字节" << fileData.at(0);
        qint64 len = file->write(fileData);
        file->waitForBytesWritten(30000);
        quint64 nowsize = file->size();
        mutiFile.at(num)->nowsize = nowsize;

        emit sentValue(number,nowsize);
        if(nowsize == fileSize){
            file->close();
            emit finishWrite(number,filename,missionCode);
        }
    }
}
