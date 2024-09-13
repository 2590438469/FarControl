#include "gemanage.h"
#include "ui_gemanage.h"

GeManage::GeManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "序号" << "任务名称" << "型号单位" << "代号" << "处理平台"
                  << "显示平台" << "状态备注" << "解算程序" << "SETUP名称" << "是否硬件加密"
                  << "加密信息备注及任务宏" << "显示画面版本" << "解算软件" << "备注"
                     << "版本更新时间" << "编制人";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("geshan"));
    QList<quint8> string_column_list;
    string_column_list << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10
                          << 11 << 12 << 13 << 14 << 15;
    ui->widget->set_string_column_number(string_column_list);
    ui->widget->set_primaryKeyIndex(0);
    ui->widget->set_fileIndex(12);
    ui->widget->set_aotuTimeColumn(14);
    ui->widget->set_resizeMode(QHeaderView::ResizeToContents);
    ui->widget->initial_widget();
}

GeManage::~GeManage()
{
    delete ui;
}
