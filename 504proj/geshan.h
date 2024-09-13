#ifndef GESHAN_H
#define GESHAN_H

#include <QObject>
#include <QWidget>
#include "geshanadvance.h"

class GeShan : public QObject
{
    Q_OBJECT
public:
    explicit GeShan(QObject *parent = nullptr);
    QString xuhao;
    QString name;
    QString xinghaochangjia;
    QString daihao;
    QString chulipingtai;
    QString xianshipingtai;
    QString zhuangtaibeizhu;
    QString jiesuanchengxu;
    QString setup;
    QString shifoujiami;
    QString jiamixinxibeizhu;
    QString xianshihuamianbanben;
    QString jiesuanruanjianwenjianjia;
    QString beizhu;
    QString banbengengxinshijian;
    QString people;
    int fileid;
    QString dianzigeshan;
    quint64 filesize;
    quint64 displayFilesize;
    QString type;

    static int insertNewGeshan(GeShan *geshan);
    static QList<GeShan *> selectAllGeshan();
    static int selectFileidByWenjianjia(QString wenjianjia);
    static QString selectFileWenjianjiaByid(int id);
    static QString selectDianziByWenjianjia(QString wenjianjia);

    static int insertDianziByWenjianjia(QString dianzi,QString wenjianjia,quint64 size);
    static int insertXianshiByWenjianjia(QString xianshi,QString wenjianjia,quint64 size);

    static int deleteGeshan(QString wenjianjia);

    static QList<QString> selectAllWenjianjia();

    static int updateGeshan(GeShan* geshan);

    static QList<GeShan *> selectAllGeshanByAdvance(GeshanAdvance *advance);

signals:

public slots:
};

#endif // GESHAN_H
