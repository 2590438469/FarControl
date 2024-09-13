#include "missionnewreview.h"
#include "ui_missionnewreview.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

MissionNewReview::MissionNewReview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionNewReview)
{
    ui->setupUi(this);
}

MissionNewReview::~MissionNewReview()
{
    delete ui;
}

void MissionNewReview::setItemByCode(QString code)
{
    MissionNew2 missionnew2;
    QSqlQuery query(db);
    QString qs = QString("select * from `missionnew2` where `任务标识` = '%1'").arg(code);
    query.exec(qs);
    QSqlRecord rec = query.record();

    while (query.next())
    {
        missionnew2.maxing = query.value(0).toString();
        missionnew2.malv = query.value(1).toString();
        missionnew2.zichang = query.value(2).toInt();
        missionnew2.zhenchang = query.value(3).toInt();
        missionnew2.zhenmazu = query.value(4).toString();
        missionnew2.zhenmazuchang = query.value(5).toInt();
        missionnew2.fuzhenfangshi = query.value(6).toString();
        missionnew2.fuzhenchang = query.value(7).toInt();
        missionnew2.idziweizhi = query.value(8).toInt();
        missionnew2.idzijizhi = query.value(9).toInt();
        missionnew2.idzijishu = query.value(10).toString();
        missionnew2.jiemizhuangtai = query.value(11).toString();
        missionnew2.xunhuanfuzhenweizhi = query.value(12).toInt();
        missionnew2.xunhuanfuzhenmazu = query.value(13).toString();
        missionnew2.duofuhaojianyan = query.value(14).toString();
        missionnew2.tpc = query.value(15).toString();
        missionnew2.kuaitongbuzhenmazu = query.value(16).toString();
        missionnew2.AGC = query.value(17).toInt();
        missionnew2.zhongpindaikuan = query.value(18).toString();
        missionnew2.AFC = query.value(19).toInt();
        missionnew2.AFCmoshi = query.value(20).toString();
        missionnew2.jiaowucha = query.value(21).toInt();
        missionnew2.gongzuodianpin = query.value(22).toString();
        missionnew2.xinghao = query.value(23).toString();
        missionnew2.miaoshu = query.value(24).toString();
        missionnew2.biaoshi = query.value(25).toString();
    }
    ui->lineEdit_17->setText(missionnew2.maxing);
    ui->lineEdit_17->setEnabled(false);
    ui->lineEdit->setText(missionnew2.malv);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setText(QString::number(missionnew2.zichang));
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setText(QString::number(missionnew2.zhenchang));
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_14->setText(missionnew2.zhenmazu);
    ui->lineEdit_14->setEnabled(false);
    ui->lineEdit_4->setText(QString::number(missionnew2.zhenmazuchang));
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_18->setText(missionnew2.fuzhenfangshi);
    ui->lineEdit_18->setEnabled(false);
    ui->lineEdit_5->setText(QString::number(missionnew2.fuzhenchang));
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_6->setText(QString::number(missionnew2.idziweizhi));
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_19->setText(QString::number(missionnew2.idzijizhi));
    ui->lineEdit_19->setEnabled(false);
    ui->lineEdit_20->setText(missionnew2.idzijishu);
    ui->lineEdit_20->setEnabled(false);
    ui->lineEdit_21->setText(missionnew2.jiemizhuangtai);
    ui->lineEdit_21->setEnabled(false);
    ui->lineEdit_7->setText(QString::number(missionnew2.xunhuanfuzhenweizhi));
    ui->lineEdit_7->setEnabled(false);
    ui->lineEdit_16->setText(missionnew2.xunhuanfuzhenmazu);
    ui->lineEdit_16->setEnabled(false);
    ui->lineEdit_22->setText(missionnew2.duofuhaojianyan);
    ui->lineEdit_22->setEnabled(false);
    ui->lineEdit_23->setText(missionnew2.tpc);
    ui->lineEdit_23->setEnabled(false);
    ui->lineEdit_15->setText(missionnew2.kuaitongbuzhenmazu);
    ui->lineEdit_15->setEnabled(false);
    ui->lineEdit_24->setText(QString::number(missionnew2.AGC));
    ui->lineEdit_24->setEnabled(false);
    ui->lineEdit_25->setText(missionnew2.zhongpindaikuan);
    ui->lineEdit_25->setEnabled(false);
    ui->lineEdit_26->setText(QString::number(missionnew2.AFC));
    ui->lineEdit_26->setEnabled(false);
    ui->lineEdit_27->setText(missionnew2.AFCmoshi);
    ui->lineEdit_27->setEnabled(false);
    ui->lineEdit_8->setText(QString::number(missionnew2.jiaowucha));
    ui->lineEdit_8->setEnabled(false);
    ui->lineEdit_9->setText(missionnew2.gongzuodianpin);
    ui->lineEdit_9->setEnabled(false);
    ui->lineEdit_11->setText(missionnew2.xinghao);
    ui->lineEdit_11->setEnabled(false);
    ui->lineEdit_12->setText(missionnew2.miaoshu);
    ui->lineEdit_12->setEnabled(false);
    ui->lineEdit_13->setText(missionnew2.biaoshi);
    ui->lineEdit_13->setEnabled(false);
}
