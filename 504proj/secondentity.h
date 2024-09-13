#ifndef SECONDENTITY_H
#define SECONDENTITY_H

#include <QObject>

class SecondEntity : public QObject
{
    Q_OBJECT
public:
    explicit SecondEntity(QObject *parent = nullptr);

    QString xuhao;
    QString renwumingcheng;
    QString xinghaochangjia;
    QString daihao;
    QString chulipingtai;
    QString xianshipingtai;
    QString zhuangtaibeizhu;
    QString jiesuanchengxu;
    QString setup;
    QString yingjianjiami;
    QString jimixinxibeizhu;
    QString renwuhong;
    QString xianshihuamianbanben;
    QString jiesuanruanjian;
    QString beizhu;
    QString banbengengxinshijian;
    QString bianzhiren;

    static int insertInfo(SecondEntity* entity);

signals:

public slots:
};

#endif // SECONDENTITY_H
