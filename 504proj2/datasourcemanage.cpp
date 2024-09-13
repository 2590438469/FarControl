#include "datasourcemanage.h"
#include "ui_datasourcemanage.h"

DataSourceManage::DataSourceManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataSourceManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "ip地址" << "端口号";
    ui->widget->set_widget_column_header(headerList);
    ui->widget->set_database(QString("datasource"));
    QList<quint8> string_column_list;
    string_column_list << 0;
    ui->widget->set_string_column_number(string_column_list);
    ui->widget->set_primaryKeyIndex(1);
    ui->widget->set_resizeMode(QHeaderView::Stretch);
    ui->widget->set_isShow(false);
    //ui->widget->initial_widget();
}

DataSourceManage::~DataSourceManage()
{
    delete ui;
}

void DataSourceManage::sendDataSourceResult(quint8 opResult,quint8 frame,QVector<QVector<QString>> array)
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

void DataSourceManage::closeEvent(QCloseEvent *event)
{
    // 断开信号与槽连接
    emit disconnectDataSourceManage();
    QWidget::closeEvent(event);
}
