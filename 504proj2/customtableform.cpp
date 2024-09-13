#include "customtableform.h"
#include "ui_customtableform.h"
#include "customtableformline.h"
#include <QThread>
#include <QDateTime>
#include <QDebug>

CustomTableForm::CustomTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomTableForm)
{
    ui->setupUi(this);
}

CustomTableForm::~CustomTableForm()
{
    delete ui;
}

void CustomTableForm::initialTableWidget(QStringList headlist, QStringList itemList)
{
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(headlist.size());
    QTableWidget *table = ui->tableWidget;

    for(int i=0;i<headlist.size();i++){
        table->setItem(0, i,new QTableWidgetItem(headlist.at(i)));
        table->setItem(1, i,new QTableWidgetItem(itemList.at(i)));
        qDebug() << headlist.at(i)<< itemList.at(i);
    }
}

void CustomTableForm::exportExcel()
{
    QString dateDir = path;


    QTableWidget *tableWidget = ui->tableWidget;
    QThread *t = new QThread;
    CustomTableFormLine *worker = new CustomTableFormLine;
    worker->moveToThread(t);

//    connect(this,&missionreview::sendFile,worker,&SendFile::sendFile);
    connect(this,&CustomTableForm::sendExport,worker,&CustomTableFormLine::exportForm);

    t->start();

    emit sendExport(tableWidget,dateDir,QString(QDateTime::currentDateTime().toString("/yyyy年MM月dd日ss秒"))+QString(ui->tableWidget->item(1,0)->text()));
}

void CustomTableForm::setPath(QString getpath)
{
    path = getpath;
}
