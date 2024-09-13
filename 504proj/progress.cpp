#include "progress.h"
#include "ui_progress.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "util/bytemethod.h"
#include "agreement/agreement.h"
#include "firstwindow.h"
#include "mainwindow.h"

progress::progress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progress)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,[=](){
        QList<ProcessEntity*> list;
        for(int i=0;i<progressList.size();i++){
            ProcessEntity *entity = new ProcessEntity();
            entity->name = progressList.at(i)->getName();
            entity->code = progressList.at(i)->getCode();
            entity->fileName = progressList.at(i)->getFileName();
            entity->percent = progressList.at(i)->getPercent();
            list.append(entity);
        }
        for(int i=0;i<FirstWindow::stations.size();i++){
            QHostAddress *addr = new QHostAddress(FirstWindow::stations.at(i)->stationIp);
            udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendAllProcessData(list)),*addr,9051);
            delete addr;
        }
        for(int i=0;i<list.size();i++){
            delete list.at(i);
        }

    });
    timer->start(1000);

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
    progressList.at(num)->setValue(value);
}

void progress::getDeleteProgress(int num)
{
    progressList.at(num)->setMissionCode("");
    progressList.at(num)->setFileName("");
    progressList.at(num)->setValue(0);
}

void progress::setFileNameCodeRange(int num,QString code,QString name,quint64 range)
{
    progressList.at(num)->setFileName(name);
    progressList.at(num)->setMissionCode(code);
    progressList.at(num)->setRange(range);
}


