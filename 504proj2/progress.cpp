#include "progress.h"
#include "ui_progress.h"
#include <QMessageBox>
#include <QDebug>

progress::progress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progress)
{
    ui->setupUi(this);
}

progress::~progress()
{
    delete ui;
}

void progress::addItem(QString stationName)
{
    SingleProgress *p = new SingleProgress();
    p->setStationInfo(stationName);
    ui->verticalLayout->addWidget(p);
    progressList.append(p);
}

void progress::setFileValue(int num, quint64 value)
{
    progressList.at(num)->setValue(value/100);
}

void progress::getDeleteProgress(int num)
{
    progressList.at(num)->setMissionCode("");
    progressList.at(num)->setFileName("");
    progressList.at(num)->setValue(0);
}

void progress::getProcessData(QList<ProcessEntity *> list)
{
    if(progressList.size()!=list.size()){
        for(int i=0;i<list.size();i++){

            SingleProgress *p = new SingleProgress();
            ui->verticalLayout->addWidget(p);
            progressList.append(p);
        }
    }
    for(int i=0;i<list.size();i++){
        progressList.at(i)->setFileName(list.at(i)->fileName);
        progressList.at(i)->setStationInfo(list.at(i)->name);
        progressList.at(i)->setMissionCode(list.at(i)->code);
        progressList.at(i)->setValue(list.at(i)->percent);
    }
}

void progress::setFileNameCodeRange(int num,QString code,QString name,quint64 range)
{
    progressList.at(num)->setFileName(name);
    progressList.at(num)->setMissionCode(code);
    progressList.at(num)->setRange(range/100);
}


