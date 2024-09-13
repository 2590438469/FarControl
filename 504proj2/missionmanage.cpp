#include "missionmanage.h"
#include "ui_missionmanage.h"
#include <QDebug>
#include <QCloseEvent>
#include "receievedata.h"
#include <QMetaType>

MissionManage::MissionManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "码型" << "码率" << "字长" << "帧长" << "帧码组"
               << "帧码组长" << "副帧方式" << "副帧长" << "ID字位置" << "ID字基值"
               << "ID字计数方向" << "解密状态" << "循环副帧位置" << "循环副帧码组" << "多符号检验"
               << "TPC/LDPC校验" << "块同步帧码组" << "AGC时间常数" << "中频带宽" << "AFC时间常数"
               << "AFC模式" << "角误差输出带宽" << "工作点频" << "任务型号" << "任务描述" <<"数据格栅" << "软解密";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("missionnew2"));
    QList<quint8> string_column_list;
    string_column_list << 0 << 1 << 3 << 4 << 6 << 10 << 11 << 13 << 14 << 15
                       << 16 << 18 << 20 << 22 << 23 << 24 << 25 << 26;
    ui->widget->set_string_column_number(string_column_list);
    QMap<quint8,QStringList> combobox_map;
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
    combobox_map.insert(quint8(0),strList1);
    combobox_map.insert(quint8(4),strList2);
    combobox_map.insert(quint8(6),strList3);
    combobox_map.insert(quint8(9),strList4);
    combobox_map.insert(quint8(10),strList5);
    combobox_map.insert(quint8(11),strList6);
    combobox_map.insert(quint8(14),strList7);
    combobox_map.insert(quint8(15),strList8);
    combobox_map.insert(quint8(16),strList2);
    combobox_map.insert(quint8(17),strList9);
    combobox_map.insert(quint8(18),strList10);
    combobox_map.insert(quint8(19),strList11);
    combobox_map.insert(quint8(20),strList12);
    ui->widget->set_combobox_map(combobox_map);
    ui->widget->set_primaryKeyIndex(25);
    //ui->widget->initial_widget();
}

MissionManage::~MissionManage()
{
    delete ui;
}

void MissionManage::sendMissionResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array)
{
    qDebug() << "信号接受";
    switch (frame) {
    case 0x01:
        ui->widget->editFinish(opResult);
        break;
    case 0x00:
        ui->widget->addFinish(opResult);
        break;
    case 0x02:
        ui->widget->deleteFinish(opResult);
        break;
    case 0x03:
        ui->widget->initial_widget(opResult,array);
        break;
    default:
        break;
    }
}

void MissionManage::sendMissionInitial(quint8 opResult,quint8 frame,QVector<QVector<QString>> array)
{
    qDebug() << "信号接受2222";
    switch (frame) {
    case 0x03:
        ui->widget->initial_widget(opResult,array);
        break;
    default:
        break;
    }
}

void MissionManage::closeEvent(QCloseEvent *event)
{
    // 断开信号与槽连接
    emit disconnectMissionManage();
    QWidget::closeEvent(event);
}

