#include "geshanadvancesearch.h"
#include "ui_geshanadvancesearch.h"
#include "entity/geshanadvance.h"
#include <QHostAddress>
#include "agreement/agreement.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "util/bytemethod.h"
#include "config/configinfo.h"

GeshanAdvanceSearch::GeshanAdvanceSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeshanAdvanceSearch)
{
    ui->setupUi(this);
    ui->dateEdit->setEnabled(false);
    ui->dateEdit_2->setEnabled(false);
    connect(ui->pushButton,&QPushButton::clicked,this,&GeshanAdvanceSearch::yesButtonSlot);
    connect(ui->checkBox_3,&QCheckBox::clicked,[=](){
        ui->dateEdit->setEnabled(!ui->dateEdit->isEnabled());
    });
    connect(ui->checkBox_4,&QCheckBox::clicked,[=](){
        ui->dateEdit_2->setEnabled(!ui->dateEdit_2->isEnabled());
    });
}

GeshanAdvanceSearch::~GeshanAdvanceSearch()
{
    delete ui;
}

void GeshanAdvanceSearch::yesButtonSlot()
{
    GeshanAdvance *advance = new GeshanAdvance();
    advance->isstartTimeEnabled = ui->checkBox_3->isChecked();
    advance->isendTimeEnabled = ui->checkBox_4->isChecked();
    advance->startTime = ui->dateEdit->dateTime().toTime_t();
    advance->endTime = ui->dateEdit_2->dateTime().addDays(1).toTime_t();

    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendGeshanAdvanceSearch(advance)),addre,ConfigInfo::centerUdpPort);
    this->close();
}
