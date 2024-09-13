#include "stationshow.h"
#include "ui_stationshow.h"
#include "mainwindow.h"
#include "firstwindow.h"

StationShow::StationShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationShow)
{
    ui->setupUi(this);
    QStringList stationName;
    for(int i=0;i<stationInfo.size();i++){
        stationName << stationInfo.at(i)->stationName;
    }
    ui->comboBox->addItems(stationName);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(indexChange(int)));
    ui->label_4->setText(stationInfo.at(0)->stationIp);
    isChecked = false;
    connect(ui->checkBox,&QCheckBox::clicked,this,&StationShow::changeCheckedStatus);

    ui->comboBox_2->clear();
    qDebug() << "打印基带大小" << baseBandInfo.size();
    for(int i=0;i<baseBandInfo.size();i++){
        if(baseBandInfo.at(i)->stationName==stationInfo.at(0)->stationName){
            ui->comboBox_2->addItem(QString::number(baseBandInfo.at(i)->port));
        }
    }
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&StationShow::changeText);
    ui->label_3->hide();
    ui->label_4->hide();
}

StationShow::~StationShow()
{
    delete ui;
}

void StationShow::setName(QString name)
{
    for(int i=0;i<baseBandInfo.size();i++){
        if(name == QString::number(baseBandInfo.at(i)->id)){
            ui->comboBox->setCurrentText(baseBandInfo.at(i)->stationName);
            qDebug() << "设置名" << baseBandInfo.at(i)->stationName;
            changeText(baseBandInfo.at(i)->stationName);

            ui->comboBox_2->setCurrentText(QString::number(baseBandInfo.at(i)->port));
            qDebug() << "设置端口" << QString::number(baseBandInfo.at(i)->port);
            break;
        }
    }
}

void StationShow::setIp(QString ip)
{
    stationIp = ip;
    ui->label_4->setText(stationIp);
}

void StationShow::setPort(QString port)
{
    ui->comboBox_2->setCurrentText(port);
}

void StationShow::setFalse()
{
    ui->checkBox->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
}

QString StationShow::getStationName()
{
    return ui->comboBox->currentText();
}

QString StationShow::getPort()
{
    return ui->comboBox_2->currentText();
}

void StationShow::indexChange(int index)
{
    ui->label_4->setText(stationInfo.at(index)->stationIp);
}

void StationShow::changeCheckedStatus()
{
    isChecked = !isChecked;
}

void StationShow::changeText(QString text)
{
    ui->comboBox_2->clear();
    for(int i=0;i<baseBandInfo.size();i++){
        if(baseBandInfo.at(i)->stationName==text){
            ui->comboBox_2->addItem(QString::number(baseBandInfo.at(i)->port));
        }
    }
}
