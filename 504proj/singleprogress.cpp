#include "singleprogress.h"
#include "ui_singleprogress.h"
#include <QMessageBox>
#include <QDebug>

SingleProgress::SingleProgress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleProgress)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

SingleProgress::~SingleProgress()
{
    delete ui;
}

void SingleProgress::setRange(quint64 size)
{
    if(size>2147483647){
        type = 1;
        ui->progressBar->setMaximum(size/10);
        maxmum = size/10;
    }else{
        type = 0;
        ui->progressBar->setMaximum(size);
        maxmum = size;
    }
}

void SingleProgress::setStationInfo(QString name)
{
    ui->label_2->setText(name);
}

void SingleProgress::setMissionCode(QString code)
{
    ui->label_4->setText(code);
}

void SingleProgress::setFileName(QString fileName)
{
    ui->label_6->setText(fileName);
}

void SingleProgress::setValue(quint64 value)
{
    if(type){
        ui->progressBar->setValue(value/10);
        this->value = value/10;
    }else{
        ui->progressBar->setValue(value);
        this->value = value;
    }
//    ui->progressBar->setValue(value/100);
    if(this->value == maxmum){
        ui->label_4->setText("");
        ui->label_6->setText("");
        ui->progressBar->setValue(0);
        value = 0;
    }
}

QString SingleProgress::getName()
{
    return ui->label_2->text();
}

QString SingleProgress::getCode()
{
    return ui->label_4->text();
}

QString SingleProgress::getFileName()
{
    return ui->label_6->text();
}

quint8 SingleProgress::getPercent()
{
    if(maxmum==0){
        return 0;
    }else{
//        qDebug() << value*100/maxmum << value*100 <<maxmum;
        return value*100/maxmum;
    }

}
