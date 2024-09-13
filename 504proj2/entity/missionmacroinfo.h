#ifndef MISSIONMACROINFO_H
#define MISSIONMACROINFO_H

#include <QObject>

class MissionMacroInfo : public QObject
{
    Q_OBJECT
public:
    explicit MissionMacroInfo(QObject *parent = nullptr);
    QString maxing;
    QString malv;
    quint32 zichang;
    quint32 zhenchang;
    QString zhenmazu;
    quint32 zhenmazuchang;
    QString fuzhenfangshi;
    quint32 fuzhenchang;
    quint32 idziweizhi;
    quint32 idzijizhi;
    QString idzijishu;
    QString jiemizhuangtai;
    quint32 xunhuanfuzhenweizhi;
    QString xunhuanfuzhenmazu;
    QString duofuhaojianyan;
    QString tpc;
    QString kuaitongbuzhenmazu;
    quint32 AGC;
    QString zhongpindaikuan;
    quint32 AFC;
    QString AFCmoshi;
    quint32 jiaowucha;
    QString gongzuodianpin;
    QString xinghao;
    QString miaoshu;
    QString biaoshi;
    QString ruanjiemi;


signals:

public slots:
};

#endif // MISSIONMACROINFO_H
