#include "usermanage.h"
#include "ui_usermanage.h"
#include <QDebug>

UserManage::UserManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "账号" << "真实姓名" << "电话号码" << "角色" << "状态";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("usernew"));
    QList<quint8> string_column_list;
    string_column_list << 0 << 1 << 2 << 3 << 4 << 5;
    ui->widget->set_string_column_number(string_column_list);
    QMap<quint8,QStringList> combobox_map;
    QStringList strList1;
    strList1 << "正常" << "已锁定";
    QStringList strList2;
    strList2 << "管理员" << "地面站" << "外单位";
    combobox_map.insert(quint8(3),strList2);
    combobox_map.insert(quint8(4),strList1);
    ui->widget->set_combobox_map(combobox_map);
    ui->widget->set_primaryKeyIndex(0);
    ui->widget->set_resizeMode(QHeaderView::Stretch);
    ui->widget->set_isShow(false);
    ui->widget->initial_widget();
}

UserManage::~UserManage()
{
    delete ui;
}
