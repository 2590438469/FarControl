#ifndef GESHAN_H
#define GESHAN_H

#include <QObject>
#include <QWidget>

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
    QString fileid;
    QString filename;
    quint64 filesize;
    QString dianzigeshan;
    quint64 displayFilesize;
    QString type;

signals:

public slots:
};

#endif // GESHAN_H
