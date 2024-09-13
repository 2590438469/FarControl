#include "stationmanage.h"
#include "ui_stationmanage.h"

StationManage::StationManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "遥测站名" << "ip地址" << "联系人" << "联系电话" << "经度"  << "纬度";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("stationnew"));
    QList<quint8> string_column_list;
    string_column_list << 0 << 1 << 2 << 3 << 4 << 5 << 6;
    ui->widget->set_string_column_number(string_column_list);
    ui->widget->set_primaryKeyIndex(0);
    ui->widget->set_resizeMode(QHeaderView::Stretch);
    ui->widget->set_isShow(false);
    ui->widget->initial_widget();
}

StationManage::~StationManage()
{
    delete ui;
}
