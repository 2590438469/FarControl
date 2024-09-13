#include "basebandmanage.h"
#include "ui_basebandmanage.h"
#include "mainwindow.h"
#include "firstwindow.h"

BaseBandManage::BaseBandManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseBandManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList  << "基带名"<< "遥测站名" << "基带端口号"<< "组播地址";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("baseband"));
    QList<quint8> string_column_list;
    string_column_list << 0 << 1 << 3;
    ui->widget->set_string_column_number(string_column_list);
    ui->widget->set_primaryKeyIndex(0);
    QMap<quint8,QStringList> combobox_map;
    QStringList strList1;
    for(int i=0;i<stationInfo.size();i++){
        strList1 << stationInfo.at(i)->stationName;
    }
    combobox_map.insert(quint8(1),strList1);
    ui->widget->set_combobox_map(combobox_map);
    ui->widget->set_resizeMode(QHeaderView::Stretch);
    ui->widget->set_isShow(false);
    //ui->widget->initial_widget();
}

BaseBandManage::~BaseBandManage()
{
    delete ui;
}

void BaseBandManage::sendBaseBandResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array)
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

void BaseBandManage::closeEvent(QCloseEvent *event)
{
    // 断开信号与槽连接
    emit disconnectBaseBandManage();
    QWidget::closeEvent(event);
}
