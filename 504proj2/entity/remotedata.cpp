#include "remotedata.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

RemoteData::RemoteData(QObject *parent) : QObject(parent)
{

}

int RemoteData::insertNewRemoteData(RemoteData *data)
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `datamanage` (`任务标识`, `武器型号`, `时间`, `类型`, `文件名`, `文件大小`) VALUES ('%1', '%2', %3, '%4', '%5', %6)")
            .arg(data->code).arg(data->model).arg(data->time).arg(data->type).arg(data->fileName).arg(data->fileSize);
    qDebug() << qs;
    return query.exec(qs);
}
