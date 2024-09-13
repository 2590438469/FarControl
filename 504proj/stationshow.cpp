#include "stationshow.h"
#include "ui_stationshow.h"

StationShow::StationShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationShow)
{
    ui->setupUi(this);
}

StationShow::~StationShow()
{
    delete ui;
}

void StationShow::setName(QString name)
{
    stationName = name;
    ui->label_2->setText(stationName);
}

void StationShow::setIp(QString ip)
{
    stationIp = ip;
    ui->label_4->setText(stationIp);
}
