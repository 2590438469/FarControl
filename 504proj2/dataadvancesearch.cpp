#include "dataadvancesearch.h"
#include "ui_dataadvancesearch.h"
#include "entity/dataadvance.h"
#include <QHostAddress>
#include "firstwindow.h"
#include "mainwindow.h"
#include "config/configinfo.h"
#include "util/bytemethod.h"

DataAdvanceSearch::DataAdvanceSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAdvanceSearch)
{
    ui->setupUi(this);
    ui->comboBox->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->dateEdit_2->setEnabled(false);
    connect(ui->pushButton,&QPushButton::clicked,this,&DataAdvanceSearch::yesButtonSlot);
    connect(ui->checkBox,&QCheckBox::clicked,[=](){
        ui->comboBox->setEnabled(!ui->comboBox->isEnabled());
    });
    connect(ui->checkBox_2,&QCheckBox::clicked,[=](){
        ui->lineEdit->setEnabled(!ui->lineEdit->isEnabled());
    });
    connect(ui->checkBox_3,&QCheckBox::clicked,[=](){
        ui->dateEdit->setEnabled(!ui->dateEdit->isEnabled());
    });
    connect(ui->checkBox_4,&QCheckBox::clicked,[=](){
        ui->dateEdit_2->setEnabled(!ui->dateEdit_2->isEnabled());
    });
    ui->comboBox->clear();
    for(int i=0;i<geshanInfo.size();i++){
        ui->comboBox->addItem(geshanInfo.at(i));
    }
}

DataAdvanceSearch::~DataAdvanceSearch()
{
    delete ui;
}

void DataAdvanceSearch::yesButtonSlot()
{
    DataAdvance *advance = new DataAdvance();
    advance->ismodelEnabled = ui->checkBox->isChecked();
    advance->istypeEnabled = ui->checkBox_2->isChecked();
    advance->isstartTimeEnabled = ui->checkBox_3->isChecked();
    advance->isendTimeEnabled = ui->checkBox_4->isChecked();
    advance->model = ui->comboBox->currentText();
    advance->type = ui->lineEdit->text();
    advance->startTime = ui->dateEdit->dateTime().toTime_t();
    advance->endTime = ui->dateEdit_2->dateTime().addDays(1).toTime_t();

    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDataAdvanceSearch(advance)),addre,ConfigInfo::centerUdpPort);
    this->close();
}
