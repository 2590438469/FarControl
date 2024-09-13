#include "advancesinglesearch.h"
#include "ui_advancesinglesearch.h"
#include <QDebug>

AdvanceSingleSearch::AdvanceSingleSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceSingleSearch)
{
    ui->setupUi(this);
    QStringList list;
    list << "到位时间" << "时间节点(起始)" << "时间节点(终止)";
    ui->comboBox->addItems(list);

    QStringList list2;
    list2 << "定值" << "最小值" << "最大值";
    ui->comboBox_2->addItems(list2);
}

AdvanceSingleSearch::~AdvanceSingleSearch()
{
    delete ui;
}

quint8 AdvanceSingleSearch::getColumn()
{
    qDebug() << "打印列" << ui->comboBox->currentIndex();
    return ui->comboBox->currentIndex();
}

quint8 AdvanceSingleSearch::getType()
{
    qDebug() << "打印类型" << ui->comboBox_2->currentIndex();
    return ui->comboBox_2->currentIndex();
}

quint8 AdvanceSingleSearch::getHour()
{
    qDebug() << "打印小时" << ui->timeEdit->time().hour();
    return ui->timeEdit->time().hour();
}

quint8 AdvanceSingleSearch::getMinute()
{
    qDebug() << "打印分钟" << ui->timeEdit->time().minute();
    return ui->timeEdit->time().minute();
}
