#include "combolabel.h"
#include "ui_combolabel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"
#include "firstwindow.h"
#include "entity/baseband.h"

ComboLabel::ComboLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboLabel)
{
    ui->setupUi(this);
    isSelect = false;
    for(int i=0;i<stationInfo.size();i++){
        nameList.append(stationInfo.at(i)->stationName);
        ipList.append(stationInfo.at(i)->stationIp);
    }
    ui->comboBox->addItems(nameList);
    ui->label->setText(ipList.at(0));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(changeIp(int)));
    connect(ui->checkBox,&QCheckBox::clicked,[=](){
        isSelect = !isSelect;
    });
    ui->comboBox_2->clear();
    for(int i=0;i<baseBandInfo.size();i++){
        if(baseBandInfo.at(i)->stationName==stationInfo.at(0)->stationName){
            ui->comboBox_2->addItem(QString::number(baseBandInfo.at(i)->port));
        }
    }
}

ComboLabel::~ComboLabel()
{
    delete ui;
}

QString ComboLabel::getIp()
{
    return ui->label->text();
}

QString ComboLabel::getName()
{
    return ui->comboBox->currentText();
}

void ComboLabel::changeText(QString text)
{
    ui->comboBox_2->clear();
    for(int i=0;i<baseBandInfo.size();i++){
        if(baseBandInfo.at(i)->stationName==text){
            ui->comboBox_2->addItem(QString::number(baseBandInfo.at(i)->port));
        }
    }
}

void ComboLabel::changeIp(int index)
{
    ui->label->setText(ipList.at(index));
}
