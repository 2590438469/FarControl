#include "battleform.h"
#include "ui_battleform.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QTableWidget>
#include <QAxObject>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QDateTime>
#include <QDebug>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "mainwindow.h"
#include <QDir>
#include "battleformline.h"

#include <QThread>
#include "config/configinfo.h"

BattleForm::BattleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleForm)
{
    ui->setupUi(this);
    initialTablewidget();
}

BattleForm::~BattleForm()
{
    delete ui;
}

void BattleForm::initialTablewidget()
{
    ui->tableWidget->setRowCount(22);
    ui->tableWidget->setColumnCount(4);
    QTableWidget *table = ui->tableWidget;

    table->setSpan(2, 2, 1, 2);
    table->setSpan(3, 2, 1, 2);
    table->setSpan(4, 2, 1, 2);
    table->setSpan(5, 2, 1, 2);
    table->setSpan(6, 0, 3, 1);
    table->setSpan(6, 1, 1, 2);
    table->setSpan(7, 1, 1, 2);
    table->setSpan(8, 1, 1, 2);

       // 填充表格数据
    table->setItem(0, 0, new QTableWidgetItem("任务代号"));
    table->setItem(0, 2, new QTableWidgetItem("执行日期"));
    table->setItem(1, 0, new QTableWidgetItem("设备编号"));
    table->setItem(1, 1, new QTableWidgetItem("字符串"));
    table->setItem(1, 2, new QTableWidgetItem("数据类型"));
    table->setItem(1, 3, new QTableWidgetItem("Xx数据"));
    table->setItem(2, 0, new QTableWidgetItem("文件名"));
    table->setItem(2, 1, new QTableWidgetItem("跟踪目标"));
    table->setItem(2, 2, new QTableWidgetItem("记录段落"));
    table->setItem(3, 1, new QTableWidgetItem("字符串"));

    table->setItem(6, 0, new QTableWidgetItem("码型"));
    table->setItem(6, 2, new QTableWidgetItem("码率"));
    table->setItem(7, 0, new QTableWidgetItem("字长"));
    table->setItem(7, 2, new QTableWidgetItem("帧长："));
    table->setItem(8, 0, new QTableWidgetItem("帧码组"));
    table->setItem(8, 2, new QTableWidgetItem("帧码组长"));
    table->setItem(9, 0, new QTableWidgetItem("副帧方式"));
    table->setItem(9, 2, new QTableWidgetItem("副帧长"));
    table->setItem(10, 0, new QTableWidgetItem("ID字位置"));
    table->setItem(10, 2, new QTableWidgetItem("ID字基值"));
    table->setItem(11, 0, new QTableWidgetItem("ID字技术方向"));
    table->setItem(11, 2, new QTableWidgetItem("解密状态"));
    table->setItem(12, 0, new QTableWidgetItem("循环副帧位置"));
    table->setItem(12, 2, new QTableWidgetItem("循环副帧码组"));
    table->setItem(13, 0, new QTableWidgetItem("多符号检验"));
    table->setItem(13, 2, new QTableWidgetItem("TPC/LDPC校验"));
    table->setItem(14, 0, new QTableWidgetItem("块同步帧码组"));
    table->setItem(14, 2, new QTableWidgetItem("AGC时间常数"));
    table->setItem(15, 0, new QTableWidgetItem("中频带宽"));
    table->setItem(15, 2, new QTableWidgetItem("AFC时间常数"));
    table->setItem(16, 0, new QTableWidgetItem("AFC模式"));
    table->setItem(16, 2, new QTableWidgetItem("角误差输出带宽"));
    table->setItem(17, 0, new QTableWidgetItem("工作点频"));
    table->setItem(17, 2, new QTableWidgetItem("任务型号"));
    table->setItem(18, 0, new QTableWidgetItem("任务描述"));
    table->setItem(18, 2, new QTableWidgetItem("任务标识"));

    table->setItem(20, 0, new QTableWidgetItem("负责人"));

    table->setItem(20, 2, new QTableWidgetItem("数据采集人"));

    table->setItem(21, 0, new QTableWidgetItem("接受单位"));

    table->setItem(21, 2, new QTableWidgetItem("接收人"));

}

void BattleForm::finishExport()
{
    t->quit();
    t->deleteLater();
    worker->deleteLater();
    emit finishExport();
}

void BattleForm::exportExcel()
{
    QString codestr = ConfigInfo::datFilePath;

    QString dateDir = codestr+QString(QDateTime::currentDateTime().toString("/yyyy年MM月dd日"));
    QDir dir2;
    if (!dir2.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg(xinghao);
    QDir dir3;
    if (!dir3.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg(miaoshu);
    QDir dir4;
    if (!dir4.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg(biaoshi);
    QDir dir5;
    if (!dir5.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }


    QTableWidget *tableWidget = ui->tableWidget;
    t = new QThread;
    worker = new BattleFormLine;
    worker->moveToThread(t);

//    connect(this,&missionreview::sendFile,worker,&SendFile::sendFile);
    connect(this,&BattleForm::sendExport,worker,&BattleFormLine::exportForm);
    connect(worker,&BattleFormLine::finishExport,this,&BattleForm::finishExport);

    t->start();
    emit sendExport(tableWidget,dateDir,filename);

}

void BattleForm::setTableWidgetItem()
{
    QTableWidget *table = ui->tableWidget;
    table->setItem(6, 1, new QTableWidgetItem(malv));
    table->setItem(6, 3, new QTableWidgetItem(maxing));
    table->setItem(7, 1, new QTableWidgetItem(zichang));
    table->setItem(7, 3, new QTableWidgetItem(zhenchang));
    table->setItem(8, 1, new QTableWidgetItem(zhenmazu));
    table->setItem(8, 3, new QTableWidgetItem(zhenmazuchang));
    table->setItem(9, 1, new QTableWidgetItem(fuzhenfangshi));
    table->setItem(9, 3, new QTableWidgetItem(fuzhenchang));
    table->setItem(10, 1, new QTableWidgetItem(idziweizhi));
    table->setItem(10, 3, new QTableWidgetItem(idzijizhi));
    table->setItem(11, 1, new QTableWidgetItem(idzijishu));
    table->setItem(11, 3, new QTableWidgetItem(jiemizhuangtai));
    table->setItem(12, 1, new QTableWidgetItem(xunhuanfuzhenweizhi));
    table->setItem(12, 3, new QTableWidgetItem(xunhuanfuzhenmazu));
    table->setItem(13, 1, new QTableWidgetItem(duofuhaojianyan));
    table->setItem(13, 3, new QTableWidgetItem(tpc));
    table->setItem(14, 1, new QTableWidgetItem(kuaitongbuzhenmazu));
    table->setItem(14, 3, new QTableWidgetItem(AGC));
    table->setItem(15, 1, new QTableWidgetItem(zhongpindaikuan));
    table->setItem(15, 3, new QTableWidgetItem(AFC));
    table->setItem(16, 1, new QTableWidgetItem(AFCmoshi));
    table->setItem(16, 3, new QTableWidgetItem(jiaowucha));
    table->setItem(17, 1, new QTableWidgetItem(gongzuodianpin));
    table->setItem(17, 3, new QTableWidgetItem(xinghao));
    table->setItem(18, 1, new QTableWidgetItem(miaoshu));
    table->setItem(18, 3, new QTableWidgetItem(biaoshi));

    table->setItem(0, 1, new QTableWidgetItem(code));
    table->setItem(0, 3, new QTableWidgetItem(date));
    table->setItem(3, 0, new QTableWidgetItem(filename));
    table->setItem(2, 2, new QTableWidgetItem(startendtime));
}
