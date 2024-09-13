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
