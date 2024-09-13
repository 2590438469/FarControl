#include "singleprogress.h"
#include "ui_singleprogress.h"
#include <QMessageBox>

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
    ui->progressBar->setRange(0,size);
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
    ui->progressBar->setValue(value);
    if(value == ui->progressBar->maximum()){
        ui->label_4->setText("");
        ui->label_6->setText("");
        ui->progressBar->setValue(0);
    }
}
