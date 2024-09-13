#include "baseband.h"
#include "mainwindow.h"
#include "firstwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

BaseBand::BaseBand(QObject *parent) : QObject(parent)
{

}

int BaseBand::insertNew(BaseBand *baseBand)
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `baseband` (`stationname`, `port`) VALUES ('%1', %2);")
            .arg(baseBand->stationName).arg(baseBand->port);
    qDebug() << qs;
    return query.exec(qs);
}

int BaseBand::deleteByBaseband(BaseBand *baseBand)
{

}

int BaseBand::editBaseband(BaseBand *oldBaseBand, BaseBand *newBaseBand)
{

}

QList<BaseBand *> BaseBand::selectAllBaseBand()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `stationnew`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<BaseBand*> baseBands;

    int nameint = rec.indexOf("stationname");
    int portint = rec.indexOf("port");
    int idint = rec.indexOf("id");

    while (query.next())
    {
        BaseBand *baseBand = new BaseBand();
        baseBand->stationName = query.value(nameint).toString();
        baseBand->port = query.value(portint).toInt();
        baseBand->id = query.value(nameint).toInt();
        baseBands.append(baseBand);
    }
    return baseBands;
}

int BaseBand::insertInfo()
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `baseband` (`stationname`, `port`) VALUES ('%1', %2);")
            .arg(this->stationName).arg(this->port);
    qDebug() << qs;
    return query.exec(qs);
}
