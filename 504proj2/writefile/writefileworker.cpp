#include "writefileworker.h"
#include <QDebug>
#include "config/configinfo.h"
#include <QCryptographicHash>

WriteFileWorker::WriteFileWorker(QObject *parent) : QObject(parent)
{

    qRegisterMetaType<AgreeMent::FILE_TYPES>("AgreeMent::FILE_TYPES");
    file = new QFile;
}

void WriteFileWorker::setFileName(QString fileName)
{
    this->fileName = fileName;
    file->close();
    file = new QFile;
    file->setFileName(fileDirectoryPath+"/"+fileName);
    qDebug() << "下载目录" << fileDirectoryPath+"/"+fileName;
    bool isok = file->open(QIODevice::WriteOnly);
    if(false == isok){
        qDebug()<<"文件打开失败";
    }else{
        qDebug()<<"文件打开成功";
    }
}

void WriteFileWorker::setFileType(AgreeMent::FILE_TYPES fileType)
{
    type = fileType;
}

void WriteFileWorker::setFileSize(quint64 fileSize)
{
    this->fileSize = fileSize;
}

void WriteFileWorker::writeFileData(QByteArray fileData)
{
    qint64 len = file->write(fileData);
    file->waitForBytesWritten(30000);

    nowsize = file->size();
    emit setPorgress(file->size());
    qDebug() << "文件总大小" << fileSize<<"当前大小"<<file->size();
    if(file->size()==fileSize){
        file->close();
        file->open(QIODevice::ReadOnly);
        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(file);

        if(hash.result() == md5){
            emit okReceieve();
        }else{
            emit falseReceieve();
        }

        file->close();
    }
//    quint64 nowsize = file->size();

//    emit sentValue(number,nowsize);
//    if(nowsize == fileSize){
//        file->close();
//        emit finishWrite(number,filename,missionCode);
//        file->deleteLater();
    //    }
}

void WriteFileWorker::setFileInfo(FileInfo *info, AgreeMent::FILE_TYPES type)
{
    qDebug() << "设置文件大小";
    fileSize = info->fileSize;

}
