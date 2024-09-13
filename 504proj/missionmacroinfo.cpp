#include "missionmacroinfo.h"
#include "station.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include "firstwindow.h"
#include "mainwindow.h"

MissionMacroInfo::MissionMacroInfo(QObject *parent) : QObject(parent)
{

}

MissionMacroInfo *MissionMacroInfo::selectMacroByBiaoshi(QString MacroBiaoshi)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `missionnew2` where '任务标识' = %1").arg(MacroBiaoshi);
    query.exec(qs);
    QSqlRecord rec = query.record();
    MissionMacroInfo *macroInfo = new MissionMacroInfo();

    int maxingint = rec.indexOf("码型");
    int malvint = rec.indexOf("码率");
    int zichangint = rec.indexOf("字长");
    int zhenchangint = rec.indexOf("帧长");
    int zhenmazuint = rec.indexOf("帧码组");
    int zhenmazuchangint = rec.indexOf("帧码组长");
    int fuzhenfangshiint = rec.indexOf("副帧方式");
    int fuzhenchangint = rec.indexOf("副帧长");
    int idziweizhiint = rec.indexOf("ID字位置");
    int idzijizhiint = rec.indexOf("ID字基值");
    int idzijishuint = rec.indexOf("ID字计数方向");
    int jiemizhuangtaiint = rec.indexOf("解密状态");
    int xunhuanfuzhenweizhiint = rec.indexOf("循环副帧位置");
    int xunhuanfuzhenmazuint = rec.indexOf("循环副帧码组");
    int duofuhaojianyanint = rec.indexOf("多符号检验");
    int tpcint = rec.indexOf("TPC/LDPC校验");
    int kuaitongbuzhenmazuint = rec.indexOf("块同步帧码组");
    int AGCint = rec.indexOf("AGC时间常数");
    int zhongpindaikuanint = rec.indexOf("中频带宽");
    int AFCint = rec.indexOf("AFC时间常数");
    int AFCmoshiint = rec.indexOf("AFC模式");
    int jiaowuchaint = rec.indexOf("角误差输出带宽");
    int gongzuodianpinint = rec.indexOf("工作点频");
    int xinghaoint = rec.indexOf("任务型号");
    int miaoshuint = rec.indexOf("任务描述");
    int biaoshiint = rec.indexOf("任务标识");

    while (query.next())
    {
        macroInfo->maxing = query.value(maxingint).toString();
        macroInfo->malv = query.value(malvint).toString();
        macroInfo->zichang = query.value(zichangint).toInt();
        macroInfo->zhenchang = query.value(zhenchangint).toInt();
        macroInfo->zhenmazu = query.value(zhenmazuint).toString();
        macroInfo->zhenmazuchang = query.value(zhenmazuchangint).toInt();
        macroInfo->fuzhenfangshi = query.value(fuzhenfangshiint).toString();
        macroInfo->fuzhenchang = query.value(fuzhenchangint).toInt();
        macroInfo->idziweizhi = query.value(idziweizhiint).toInt();
        macroInfo->idzijizhi = query.value(idzijizhiint).toInt();
        macroInfo->idzijishu = query.value(idzijishuint).toString();
        macroInfo->jiemizhuangtai = query.value(jiemizhuangtaiint).toString();
        macroInfo->xunhuanfuzhenweizhi = query.value(xunhuanfuzhenweizhiint).toInt();
        macroInfo->xunhuanfuzhenmazu = query.value(xunhuanfuzhenmazuint).toString();
        macroInfo->duofuhaojianyan = query.value(duofuhaojianyanint).toString();
        macroInfo->tpc = query.value(tpcint).toString();
        macroInfo->kuaitongbuzhenmazu = query.value(kuaitongbuzhenmazuint).toString();
        macroInfo->AGC = query.value(AGCint).toInt();
        macroInfo->zhongpindaikuan = query.value(zhongpindaikuanint).toString();
        macroInfo->AFC = query.value(AFCint).toInt();
        macroInfo->AFCmoshi = query.value(AFCmoshiint).toString();
        macroInfo->jiaowucha = query.value(jiaowuchaint).toInt();
        macroInfo->gongzuodianpin = query.value(gongzuodianpinint).toString();
        macroInfo->xinghao = query.value(xinghaoint).toString();
        macroInfo->miaoshu = query.value(miaoshuint).toString();
        macroInfo->biaoshi = query.value(biaoshiint).toString();
    }
    return macroInfo;
}

QList<MissionMacroInfo*> MissionMacroInfo::selectAllMacro()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `missionnew2`");

    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<MissionMacroInfo*> list;

    int maxingint = rec.indexOf("码型");
    int malvint = rec.indexOf("码率");
    int zichangint = rec.indexOf("字长");
    int zhenchangint = rec.indexOf("帧长");
    int zhenmazuint = rec.indexOf("帧码组");
    int zhenmazuchangint = rec.indexOf("帧码组长");
    int fuzhenfangshiint = rec.indexOf("副帧方式");
    int fuzhenchangint = rec.indexOf("副帧长");
    int idziweizhiint = rec.indexOf("ID字位置");
    int idzijizhiint = rec.indexOf("ID字基值");
    int idzijishuint = rec.indexOf("ID字计数方向");
    int jiemizhuangtaiint = rec.indexOf("解密状态");
    int xunhuanfuzhenweizhiint = rec.indexOf("循环副帧位置");
    int xunhuanfuzhenmazuint = rec.indexOf("循环副帧码组");
    int duofuhaojianyanint = rec.indexOf("多符号检验");
    int tpcint = rec.indexOf("TPC/LDPC校验");
    int kuaitongbuzhenmazuint = rec.indexOf("块同步帧码组");
    int AGCint = rec.indexOf("AGC时间常数");
    int zhongpindaikuanint = rec.indexOf("中频带宽");
    int AFCint = rec.indexOf("AFC时间常数");
    int AFCmoshiint = rec.indexOf("AFC模式");
    int jiaowuchaint = rec.indexOf("角误差输出带宽");
    int gongzuodianpinint = rec.indexOf("工作点频");
    int xinghaoint = rec.indexOf("任务型号");
    int miaoshuint = rec.indexOf("任务描述");
    int biaoshiint = rec.indexOf("任务标识");
    int ruanjiemiint = rec.indexOf("软解密");

    while (query.next())
    {
        MissionMacroInfo *macroInfo = new MissionMacroInfo();
        macroInfo->maxing = query.value(maxingint).toString();
        macroInfo->malv = query.value(malvint).toString();
        macroInfo->zichang = query.value(zichangint).toInt();
        macroInfo->zhenchang = query.value(zhenchangint).toInt();
        macroInfo->zhenmazu = query.value(zhenmazuint).toString();
        macroInfo->zhenmazuchang = query.value(zhenmazuchangint).toInt();
        macroInfo->fuzhenfangshi = query.value(fuzhenfangshiint).toString();
        macroInfo->fuzhenchang = query.value(fuzhenchangint).toInt();
        macroInfo->idziweizhi = query.value(idziweizhiint).toInt();
        macroInfo->idzijizhi = query.value(idzijizhiint).toInt();
        macroInfo->idzijishu = query.value(idzijishuint).toString();
        macroInfo->jiemizhuangtai = query.value(jiemizhuangtaiint).toString();
        macroInfo->xunhuanfuzhenweizhi = query.value(xunhuanfuzhenweizhiint).toInt();
        macroInfo->xunhuanfuzhenmazu = query.value(xunhuanfuzhenmazuint).toString();
        macroInfo->duofuhaojianyan = query.value(duofuhaojianyanint).toString();
        macroInfo->tpc = query.value(tpcint).toString();
        macroInfo->kuaitongbuzhenmazu = query.value(kuaitongbuzhenmazuint).toString();
        macroInfo->AGC = query.value(AGCint).toInt();
        macroInfo->zhongpindaikuan = query.value(zhongpindaikuanint).toString();
        macroInfo->AFC = query.value(AFCint).toInt();
        macroInfo->AFCmoshi = query.value(AFCmoshiint).toString();
        macroInfo->jiaowucha = query.value(jiaowuchaint).toInt();
        macroInfo->gongzuodianpin = query.value(gongzuodianpinint).toString();
        macroInfo->xinghao = query.value(xinghaoint).toString();
        macroInfo->miaoshu = query.value(miaoshuint).toString();
        macroInfo->biaoshi = query.value(biaoshiint).toString();
        macroInfo->ruanjiemi = query.value(ruanjiemiint).toString();
        list.append(macroInfo);
    }

    return list;
}
