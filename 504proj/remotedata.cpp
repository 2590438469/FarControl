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
    QString qs = QString("INSERT INTO `datamanage` (`任务标识`, `武器型号`, `时间`, `类型`, `文件名`, `文件大小`,`用户`) VALUES ('%1', '%2', %3, '%4', '%5', %6,'%7')")
            .arg(data->code).arg(data->model).arg(data->time).arg(data->type).arg(data->fileName).arg(data->fileSize).arg(data->user);
    qDebug() << qs;
    return query.exec(qs);
}

QList<RemoteData *> RemoteData::selectAllGeshan()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `datamanage`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<RemoteData*> remotes;

    int codeint = rec.indexOf("任务标识");
    int modelint = rec.indexOf("武器型号");
    int timeint = rec.indexOf("时间");
    int typeint = rec.indexOf("类型");
    int fileNameint = rec.indexOf("文件名");
    int fileSizeint = rec.indexOf("文件大小");
    int idint = rec.indexOf("id");
    int userint = rec.indexOf("用户");

    while (query.next())
    {
        RemoteData *single = new RemoteData();
        single->code = query.value(codeint).toString();
        single->model = query.value(modelint).toString();
        single->time = query.value(timeint).toInt();
        single->type = query.value(typeint).toString();
        single->fileName = query.value(fileNameint).toString();
        single->fileSize = query.value(fileSizeint).toLongLong();
        single->id = query.value(idint).toInt();
        single->user = query.value(userint).toString();
        remotes.append(single);
        qDebug() << "文件大小" << single->fileSize;
    }
    return remotes;
}

QList<RemoteData *> RemoteData::selectByAdvance(DataAdvance *advance)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `datamanage`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<RemoteData*> remotes;

    int codeint = rec.indexOf("任务标识");
    int modelint = rec.indexOf("武器型号");
    int timeint = rec.indexOf("时间");
    int typeint = rec.indexOf("类型");
    int fileNameint = rec.indexOf("文件名");
    int fileSizeint = rec.indexOf("文件大小");
    int idint = rec.indexOf("id");

    while (query.next())
    {
        RemoteData *single = new RemoteData();
        single->code = query.value(codeint).toString();
        single->model = query.value(modelint).toString();
        single->time = query.value(timeint).toInt();
        single->type = query.value(typeint).toString();
        single->fileName = query.value(fileNameint).toString();
        single->fileSize = query.value(fileSizeint).toInt();
        single->id = query.value(idint).toInt();
        remotes.append(single);
    }


    QList<RemoteData*> list2;
    int flag = 1;
    for(int j=0;j<remotes.size();j++){
        if(advance->ismodelEnabled){
            if(remotes.at(j)->model != advance->model){
                flag = 0;
            }
        }
        if(advance->istypeEnabled){
            if(remotes.at(j)->type != advance->type){
                flag = 0;
            }
        }
        if(advance->isstartTimeEnabled){
            if(remotes.at(j)->time < advance->startTime){
                flag = 0;
            }
        }
        if(advance->isendTimeEnabled){
            if(remotes.at(j)->time > advance->endTime){
                flag = 0;
            }
        }
        if(flag){
            list2.append(remotes.at(j));
        }
        flag = 1;
    }

    return list2;
}

int RemoteData::deleteByXuhao(QString xuhao)
{
    QSqlQuery query(db);
    QString qs = QString("delete from `datamanage` WHERE (`id` = %1)").arg(xuhao);
    return query.exec(qs);
}

int RemoteData::updateDataByXuhao(QString xuhao, QString type)
{
    QSqlQuery query(db);
    QString qs = QString("UPDATE `datamanage` SET `类型` = '%1' WHERE (`id` = %2)").arg(type).arg(xuhao);
    return query.exec(qs);
}
