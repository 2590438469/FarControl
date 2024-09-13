#include "missionnewinsert.h"
#include "ui_missionnewinsert.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

MissionNewInsert::MissionNewInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionNewInsert)
{
    ui->setupUi(this);
    initial_combobox_items();
    initial_header();
    connect(ui->pushButton,&QPushButton::clicked,this,&MissionNewInsert::add_button_slot);
}

MissionNewInsert::~MissionNewInsert()
{
    delete ui;
}

void MissionNewInsert::initial_combobox_items()
{
    QStringList strList1;
    strList1 << "NRZ-L" << "NRZ-M" <<  "NRZ-S" <<  "Bip-L" << "Bip-M" << "Bip-S" << "RNRZ-L";
    QStringList strList2;
    strList2 << "HEX1" << "HEX2" << "HEX3" << "HEX4" << "HEX5" << "HEX6" << "HEX7" << "HEX8";
    QStringList strList3;
    strList3 << "IP副帧" << "循环副帧" << "反码副帧" << "无副帧";
    QStringList strList4;
    strList4 << "0" << "1" ;
    QStringList strList5;
    strList5 << "加计数" << "减计数" ;
    QStringList strList6;
    strList6 << "解密" << "不解密" ;
    QStringList strList7;
    strList7 << "是" << "否" ;
    QStringList strList8;
    strList8 << "无" << "TPC有效" << "LDPC有效";
    QStringList strList9;
    strList9 << "3" << "10" << "100" << "1000";
    QStringList strList10;
    strList10 << "50K"<< "300K"<< "500K"<< "750K"<< "1M"<< "1.5M"
           << "2.4M"<< "3.3M"<< "4.0M"<< "6.0M"<< "10M"<< "15M"
           << "20M"<< "24M"<<  "33M"<< "40M";
    QStringList strList11;
    strList11 << "3" << "60" << "300";
    QStringList strList12;
    strList12 <<"闭环" << "开环";
    ui->comboBox->addItems(strList1);
    ui->comboBox_3->addItems(strList3);
    ui->comboBox_4->addItems(strList4);
    ui->comboBox_5->addItems(strList5);
    ui->comboBox_6->addItems(strList6);
    ui->comboBox_8->addItems(strList7);
    ui->comboBox_9->addItems(strList8);
    ui->comboBox_11->addItems(strList9);
    ui->comboBox_12->addItems(strList10);
    ui->comboBox_13->addItems(strList11);
    ui->comboBox_14->addItems(strList12);
}

void MissionNewInsert::initial_header()
{
    widget_column_header << "码型" << "码率" << "字长" << "帧长" << "帧码组"
               << "帧码组长" << "副帧方式" << "副帧长" << "ID字位置" << "ID字基值"
               << "ID字计数方向" << "解密状态" << "循环副帧位置" << "循环副帧码组" << "多符号检验"
               << "TPC/LDPC校验" << "块同步帧码组" << "AGC时间常数" << "中频带宽" << "AFC时间常数"
               << "AFC模式" << "角误差输出带宽" << "工作点频" << "任务型号" << "任务描述" <<"任务标识";
}

void MissionNewInsert::add_button_slot()
{
    QSqlQuery query(db);
    QString qs = QString("insert into `missionnew2` (");
    for(int i=0;i<widget_column_header.size();i++){
        qs.insert(qs.size(),"`");
        qs.insert(qs.size(),widget_column_header.at(i));
        qs.insert(qs.size(),"`");
        qs.insert(qs.size(),",");
    }
    qs.chop(1);
    qs.insert(qs.size(),")");
    qs.insert(qs.size(),QString("values('%1','%2',%3,'%4','%5',%6,'%7',%8,%9,%10,"
                        "'%11','%12',%13,'%14','%15','%16','%17',%18,'%19',"
                        "%20,'%21',%22,'%23','%24','%25','%26')").arg(ui->comboBox->currentText())
            .arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text())
            .arg(ui->lineEdit_14->text()).arg(ui->lineEdit_4->text()).arg(ui->comboBox_3->currentText())
            .arg(ui->lineEdit_5->text()).arg(ui->lineEdit_6->text()).arg(ui->comboBox_4->currentText())
            .arg(ui->comboBox_5->currentText()).arg(ui->comboBox_6->currentText()).arg(ui->lineEdit_7->text())
            .arg(ui->lineEdit_16->text()).arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText())
            .arg(ui->lineEdit_15->text()).arg(ui->comboBox_11->currentText()).arg(ui->comboBox_12->currentText())
            .arg(ui->comboBox_13->currentText()).arg(ui->comboBox_14->currentText()).arg(ui->lineEdit_8->text())
            .arg(ui->lineEdit_9->text().append("~").append(ui->lineEdit_10->text())).arg(ui->lineEdit_11->text())
            .arg(ui->lineEdit_12->text()).arg(ui->lineEdit_13->text()));
    qDebug() << qs;
    bool ok = query.exec(qs);
    if(ok){
        QMessageBox::information(this,"添加提示","添加成功");
        emit refresh_tableWidget();
        this->close();
    }else{
        QMessageBox::information(this,"添加提示",query.lastError().text());
    }
}
