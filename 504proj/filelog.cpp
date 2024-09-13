#include "filelog.h"
#include "mainwindow.h"
#include "firstwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

FileLog::FileLog(QObject *parent) : QObject(parent)
{

}

int FileLog::insertNewLog(FileLog *log)
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `filelog` (`people`, `time`, `opration`, `filename`) VALUES ('%1', %2, %3, '%4')")
            .arg(log->people).arg(log->time).arg(log->operation).arg(log->fileName);

    qDebug() << qs;
    return query.exec(qs);
}

QList<FileLog*> FileLog::selectByStation(FileLog *fileLog)
{
    QSqlQuery query(db);
    QString qs = QString("SELECT * FROM `filelog` where `people` = '%1' and `time` >= %2 and `time` <= %3;")
            .arg(fileLog->people).arg(fileLog->startTime).arg(fileLog->endTime);
    qDebug() << qs;
    query.exec(qs);
    QSqlRecord rec = query.record();

    QList<FileLog*> list;

    int peopleint = rec.indexOf("people");
    int timeint = rec.indexOf("time");
    int oprationint = rec.indexOf("opration");
    int filenameint = rec.indexOf("filename");

    while (query.next())
    {
        FileLog *log = new FileLog();
        log->people = query.value(peopleint).toString();
        log->time = query.value(timeint).toInt();
        log->operation = query.value(oprationint).toInt();
        log->fileName = query.value(filenameint).toString();
        qDebug() << "筛选结果" << log->people << log->time
                 << log->operation << log->fileName;
        list.append(log);
    }
    return list;
}
