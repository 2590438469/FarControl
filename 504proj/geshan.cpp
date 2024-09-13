#include "geshan.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "QSqlQuery"
#include "QSqlRecord"
#include <QDateTime>

GeShan::GeShan(QObject *parent) : QObject(parent)
{

}

int GeShan::insertNewGeshan(GeShan *geshan)
{
    QSqlQuery query(db);
    geshan->jiesuanruanjianwenjianjia = geshan->daihao+"-"+geshan->zhuangtaibeizhu;
    QString qs = QString("INSERT INTO `geshan` (`任务名称`, `型号厂家`, `代号`, `处理平台`, `显示平台`, "
                         "`状态备注`, `解算程序`, `SETUP名称`, `是否硬件加密`, `加密信息备注`, `显示画面版本`, `解算软件文件夹`, `备注`, `版本更新时间` , `编制人`,`类型`) "
                         "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', %14, '%15','%16')")
            .arg(geshan->name).arg(geshan->xinghaochangjia).arg(geshan->daihao).arg(geshan->chulipingtai).arg(geshan->xianshipingtai).arg(geshan->zhuangtaibeizhu)
            .arg(geshan->jiesuanchengxu).arg(geshan->setup).arg(geshan->shifoujiami).arg(geshan->jiamixinxibeizhu).arg(geshan->xianshihuamianbanben).arg(geshan->jiesuanruanjianwenjianjia)
            .arg(geshan->beizhu).arg(QDateTime::currentDateTime().toTime_t()).arg(geshan->people).arg(geshan->type);
    qDebug() << qs;
    int ok = query.exec(qs);
    if(ok){
        return 1;
    }else{
        return 0;
    }
}

QList<GeShan *> GeShan::selectAllGeshan()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan`");
    QList<GeShan *> list;
    query.exec(qs);
    
    QSqlRecord rec = query.record();
    int xuhao = rec.indexOf("序号");
    int name = rec.indexOf("任务名称");
    int xinghaochangjia = rec.indexOf("型号厂家");
    int daihao = rec.indexOf("代号");
    int chulipingtai = rec.indexOf("处理平台");
    int xianshipingtai = rec.indexOf("显示平台");
    int zhuangtaibeizhu = rec.indexOf("状态备注");
    int jiesuanchengxu = rec.indexOf("解算程序");
    int setup = rec.indexOf("SETUP名称");
    int shifoujiami = rec.indexOf("是否硬件加密");
    int jiamixinxibeizhu = rec.indexOf("加密信息备注");
    int xianshihuamianbanben = rec.indexOf("显示画面版本");
    int jiesuanruanjianwenjianjia = rec.indexOf("解算软件文件夹");
    int beizhu = rec.indexOf("备注");
    int banbengengxinshijian = rec.indexOf("版本更新时间");
    int people = rec.indexOf("编制人");
    int fileid = rec.indexOf("fileid");
    int filename = rec.indexOf("电子格栅文件名");
    int filesize = rec.indexOf("文件大小");
    int displayfilesizeint = rec.indexOf("显示画面大小");
    int typeint = rec.indexOf("类型");
    while (query.next()){
        GeShan *geshan= new GeShan();
        geshan->xuhao = query.value(fileid).toString();
        geshan->name = query.value(name).toString();
        geshan->xinghaochangjia = query.value(xinghaochangjia).toString();
        geshan->daihao = query.value(daihao).toString();
        geshan->chulipingtai = query.value(chulipingtai).toString();
        geshan->xianshipingtai = query.value(xianshipingtai).toString();
        geshan->zhuangtaibeizhu = query.value(zhuangtaibeizhu).toString();
        geshan->jiesuanchengxu = query.value(jiesuanchengxu).toString();
        geshan->setup = query.value(setup).toString();
        geshan->shifoujiami = query.value(shifoujiami).toString();
        geshan->jiamixinxibeizhu = query.value(jiamixinxibeizhu).toString();
        geshan->xianshihuamianbanben = query.value(xianshihuamianbanben).toString();
        geshan->jiesuanruanjianwenjianjia = query.value(jiesuanruanjianwenjianjia).toString();
        geshan->beizhu = query.value(beizhu).toString();
        geshan->banbengengxinshijian = query.value(banbengengxinshijian).toString();
        geshan->people = query.value(people).toString();
        geshan->fileid = query.value(fileid).toInt();
        geshan->dianzigeshan = query.value(filename).toString();
        geshan->filesize = query.value(filesize).toLongLong();
        geshan->displayFilesize = query.value(displayfilesizeint).toLongLong();
        geshan->type = query.value(typeint).toString();
        list.append(geshan);
    }
    return list;
}

int GeShan::selectFileidByWenjianjia(QString wenjianjia)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan` where `解算软件文件夹` = '%1'").arg(wenjianjia);
    query.exec(qs);
    QSqlRecord rec = query.record();
    int fileid = rec.indexOf("fileid");
    int fileidres;
    while (query.next())
    {
        fileidres = query.value(fileid).toInt();
    }
    return fileidres;
}

QString GeShan::selectFileWenjianjiaByid(int id)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan` where `fileid` = %1").arg(id);
    query.exec(qs);
    QSqlRecord rec = query.record();
    int wenjianjia = rec.indexOf("解算软件文件夹");
    QString wenjianjiares;
    while (query.next())
    {
        wenjianjiares = query.value(wenjianjia).toString();
    }
    return wenjianjiares;
}

QString GeShan::selectDianziByWenjianjia(QString wenjianjia)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan` where `解算软件文件夹` = '%1'").arg(wenjianjia);
    query.exec(qs);
    QSqlRecord rec = query.record();
    int fileid = rec.indexOf("电子格栅文件名");
    QString filename;
    while (query.next())
    {
        filename = query.value(fileid).toString();
    }
    return filename;
}

int GeShan::insertDianziByWenjianjia(QString dianzi,QString wenjianjia,quint64 size)
{
    QSqlQuery query(db);
    QString qs = QString("UPDATE `geshan` SET `电子格栅文件名` = '%1', `文件大小` = %2 WHERE (`解算软件文件夹` = '%3')")
            .arg(dianzi).arg(size).arg(wenjianjia);
    qDebug() << qs;
    int ok = query.exec(qs);
    return ok;
}

int GeShan::insertXianshiByWenjianjia(QString xianshi, QString wenjianjia, quint64 size)
{
    QSqlQuery query(db);
    QString qs = QString("UPDATE `geshan` SET `显示画面版本` = '%1', `显示画面大小` = %2 WHERE (`解算软件文件夹` = '%3')")
            .arg(xianshi).arg(size).arg(wenjianjia);
    qDebug() << qs;
    int ok = query.exec(qs);
    return ok;
}

int GeShan::deleteGeshan(QString wenjianjia)
{
    QSqlQuery query(db);
    QString qs = QString("DELETE FROM `geshan` WHERE (`解算软件文件夹` = '%1')")
            .arg(wenjianjia);
    qDebug() << qs;
    int ok = query.exec(qs);
    return ok;
}

QList<QString> GeShan::selectAllWenjianjia()
{
    QList<QString> list;
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan`");
    query.exec(qs);

    QSqlRecord rec = query.record();
    int jiesuanruanjianwenjianjia = rec.indexOf("解算软件文件夹");

    while (query.next()){
        QString wenjianjia = query.value(jiesuanruanjianwenjianjia).toString();
        list.append(wenjianjia);
    }
    return list;
}

int GeShan::updateGeshan(GeShan *geshan)
{
    QSqlQuery query(db);
    QString qs = QString("UPDATE `geshan` SET `任务名称` = '%1', `型号厂家` = '%2', `代号` = '%3', `处理平台` = '%4', `显示平台` = '%5', `状态备注` = '%6', `解算程序` = '%7', `SETUP名称` = '%8', `是否硬件加密` = '%9', `加密信息备注` = '%10', `备注` = '%11', `编制人` = '%12', `类型` = '%13' WHERE (`解算软件文件夹` = '%14')")
            .arg(geshan->name).arg(geshan->xinghaochangjia).arg(geshan->daihao).arg(geshan->chulipingtai).arg(geshan->xianshipingtai).arg(geshan->zhuangtaibeizhu).arg(geshan->jiesuanchengxu).arg(geshan->setup).arg(geshan->shifoujiami).arg(geshan->jiamixinxibeizhu).arg(geshan->beizhu).arg(geshan->people)
            .arg(geshan->type).arg(geshan->jiesuanruanjianwenjianjia);
    return query.exec(qs);

}

QList<GeShan *> GeShan::selectAllGeshanByAdvance(GeshanAdvance *advance)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `geshan`");
    QList<GeShan *> list;
    query.exec(qs);

    QSqlRecord rec = query.record();
    int xuhao = rec.indexOf("序号");
    int name = rec.indexOf("任务名称");
    int xinghaochangjia = rec.indexOf("型号厂家");
    int daihao = rec.indexOf("代号");
    int chulipingtai = rec.indexOf("处理平台");
    int xianshipingtai = rec.indexOf("显示平台");
    int zhuangtaibeizhu = rec.indexOf("状态备注");
    int jiesuanchengxu = rec.indexOf("解算程序");
    int setup = rec.indexOf("SETUP名称");
    int shifoujiami = rec.indexOf("是否硬件加密");
    int jiamixinxibeizhu = rec.indexOf("加密信息备注");
    int xianshihuamianbanben = rec.indexOf("显示画面版本");
    int jiesuanruanjianwenjianjia = rec.indexOf("解算软件文件夹");
    int beizhu = rec.indexOf("备注");
    int banbengengxinshijian = rec.indexOf("版本更新时间");
    int people = rec.indexOf("编制人");
    int fileid = rec.indexOf("fileid");
    int filename = rec.indexOf("电子格栅文件名");
    int filesize = rec.indexOf("文件大小");
    int displayfilesizeint = rec.indexOf("显示画面大小");
    int typeint = rec.indexOf("类型");
    while (query.next()){
        GeShan *geshan= new GeShan();
        geshan->xuhao = query.value(fileid).toString();
        geshan->name = query.value(name).toString();
        geshan->xinghaochangjia = query.value(xinghaochangjia).toString();
        geshan->daihao = query.value(daihao).toString();
        geshan->chulipingtai = query.value(chulipingtai).toString();
        geshan->xianshipingtai = query.value(xianshipingtai).toString();
        geshan->zhuangtaibeizhu = query.value(zhuangtaibeizhu).toString();
        geshan->jiesuanchengxu = query.value(jiesuanchengxu).toString();
        geshan->setup = query.value(setup).toString();
        geshan->shifoujiami = query.value(shifoujiami).toString();
        geshan->jiamixinxibeizhu = query.value(jiamixinxibeizhu).toString();
        geshan->xianshihuamianbanben = query.value(xianshihuamianbanben).toString();
        geshan->jiesuanruanjianwenjianjia = query.value(jiesuanruanjianwenjianjia).toString();
        geshan->beizhu = query.value(beizhu).toString();
        geshan->banbengengxinshijian = query.value(banbengengxinshijian).toString();
        geshan->people = query.value(people).toString();
        geshan->fileid = query.value(fileid).toInt();
        geshan->dianzigeshan = query.value(filename).toString();
        geshan->filesize = query.value(filesize).toInt();
        geshan->displayFilesize = query.value(displayfilesizeint).toInt();
        geshan->type = query.value(typeint).toString();
        list.append(geshan);
    }

    QList<GeShan *> list2;
    int flag = 1;
    for(int j=0;j<list.size();j++){
        qDebug() << list.at(j)->banbengengxinshijian << advance->startTime <<advance->endTime;
        if(advance->isstartTimeEnabled){
            if(list.at(j)->banbengengxinshijian.toInt() < advance->startTime){
                flag = 0;
            }
        }
        if(advance->isendTimeEnabled){
            if(list.at(j)->banbengengxinshijian.toInt() > advance->endTime){
                flag = 0;
            }
        }
        if(flag){
            list2.append(list.at(j));
        }
        flag = 1;
    }
    return list2;
}
