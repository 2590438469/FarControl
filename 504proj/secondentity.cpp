#include "secondentity.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "firstwindow.h"
#include "mainwindow.h"

SecondEntity::SecondEntity(QObject *parent) : QObject(parent)
{

}

int SecondEntity::insertInfo(SecondEntity *entity)
{
    QSqlQuery query(db);
    QString qs = QString("INSERT INTO `geshan` (`序号`, `任务名称`, `型号厂家`, `代号`, `处理平台`, `显示平台`, `状态备注`, `解算程序`, `SETUP名称`, `是否硬件加密`, `加密信息备注`, `任务宏`, `显示画面版本`, `解算软件`, `备注`, `版本更新时间`, `编制人`) "
                         "VALUES (%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17');")
            .arg(entity->xuhao).arg(entity->renwumingcheng).arg(entity->xinghaochangjia)
            .arg(entity->daihao).arg(entity->chulipingtai).arg(entity->xianshipingtai)
            .arg(entity->zhuangtaibeizhu).arg(entity->jiesuanchengxu).arg(entity->setup)
            .arg(entity->yingjianjiami).arg(entity->jimixinxibeizhu).arg(entity->renwuhong)
            .arg(entity->xianshihuamianbanben).arg(entity->jiesuanruanjian).arg(entity->beizhu)
            .arg(entity->banbengengxinshijian).arg(entity->bianzhiren);
    qDebug() << qs;
    return query.exec(qs);
}
