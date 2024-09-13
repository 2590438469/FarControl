#include "childfile.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

ChildFile::ChildFile(QObject *parent) : QObject(parent)
{

}

QList<ChildFile *> ChildFile::selectByFileid(int fileid)
{
    QList<ChildFile *> list;
    QSqlQuery query(db);
    QString qs = QString("select * from `geshanfile` where `fileid` = %1").arg(fileid);
    query.exec(qs);
    QSqlRecord rec = query.record();
    int idint = rec.indexOf("id");
    int filenameint = rec.indexOf("filename");
    int filesizeint = rec.indexOf("filesize");
    int updatetimeint = rec.indexOf("updatetime");
    int fileidint = rec.indexOf("fileid");
    while (query.next())
    {
        ChildFile *file = new ChildFile();
        file->id = query.value(idint).toInt();
        file->fileName = query.value(filenameint).toString();
        file->fileSize = query.value(filesizeint).toLongLong();
        file->updatetime = query.value(updatetimeint).toInt();
        file->fileid = query.value(fileidint).toInt();
        list.append(file);
        qDebug() <<"打印大小" << file->fileSize;
    }
    return list;
}

int ChildFile::deleteByFildid(int fileid)
{
    QSqlQuery query(db);
    QString qs = QString("delete from `geshanfile` where `fileid` = %1").arg(fileid);
    return query.exec(qs);
}

int ChildFile::insertNewInfo(ChildFile *childFile)
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `geshanfile` (`filename`, `filesize`, `updatetime`,`fileid`) VALUES ('%1', %2, %3,%4)").arg(childFile->fileName)
            .arg(childFile->fileSize).arg(childFile->updatetime).arg(childFile->fileid);
    qDebug() << qs;
    return query.exec(qs);
}

int ChildFile::deleteChildFileByFileidAndName(QString name, int fileid)
{
    QSqlQuery query(db);
    QString qs = QString("DELETE FROM `geshanfile` WHERE (`fileid` = %1) AND (`filename` = '%2');")
            .arg(fileid).arg(name);
    qDebug() << qs;
    return query.exec(qs);
}
