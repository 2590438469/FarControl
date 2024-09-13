#include "advancesearch.h"
#include "ui_advancesearch.h"
#include "advancesinglesearch.h"
#include "entity/advance.h"
#include <QHostAddress>
#include "config/configinfo.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "util/bytemethod.h"

AdvanceSearch::AdvanceSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceSearch)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->dateEdit_2->setEnabled(false);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&AdvanceSearch::yesButtonSlot);
    connect(ui->checkBox,&QCheckBox::clicked,[=](){
        ui->lineEdit->setEnabled(!ui->lineEdit->isEnabled());
    });
    connect(ui->checkBox_2,&QCheckBox::clicked,[=](){
        ui->lineEdit_2->setEnabled(!ui->lineEdit_2->isEnabled());
    });
    connect(ui->checkBox_3,&QCheckBox::clicked,[=](){
        ui->dateEdit->setEnabled(!ui->dateEdit->isEnabled());
    });
    connect(ui->checkBox_4,&QCheckBox::clicked,[=](){
        ui->dateEdit_2->setEnabled(!ui->dateEdit_2->isEnabled());
    });
}

AdvanceSearch::~AdvanceSearch()
{
    delete ui;
}



void AdvanceSearch::yesButtonSlot()
{
    Advance *advance = new Advance();
    advance->iscodeEnabled = ui->checkBox->isChecked();
    advance->isprotectEnabled = ui->checkBox_2->isChecked();
    advance->isstartTimeEnabled = ui->checkBox_3->isChecked();
    advance->isendTimeEnabled = ui->checkBox_4->isChecked();
    advance->code = ui->lineEdit->text();
    advance->protect = ui->lineEdit_2->text();
    advance->startTime = ui->dateEdit->dateTime().toTime_t();
    advance->endTime = ui->dateEdit_2->dateTime().addDays(1).toTime_t();

    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendAdvanceSearch(advance)),addre,ConfigInfo::centerUdpPort);
    this->close();
}
