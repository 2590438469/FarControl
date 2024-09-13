#include "advancesearch.h"
#include "ui_advancesearch.h"
#include "advancedsinglesearch.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "QSqlQuery"
#include "QSqlRecord"
#include "QSqlError"

AdvanceSearch::AdvanceSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceSearch)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&AdvanceSearch::addIndexSlot);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&AdvanceSearch::okButtonSlot);
}

AdvanceSearch::~AdvanceSearch()
{
    delete ui;
}

void AdvanceSearch::setList(QStringList list)
{
    comboList = list;
}

void AdvanceSearch::addIndexSlot()
{
    AdvancedSingleSearch *widget = new AdvancedSingleSearch();
    widget->setMap(map);
    widget->setList(comboList);
    widget->setDingList(dingList);
    ui->verticalLayout->addWidget(widget);
    singleList.append(widget);
}

void AdvanceSearch::okButtonSlot()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `%1` where ").arg(tName);
    for(int i=0;i<singleList.size();i++){
        qs.append(singleList.at(i)->getName());
        if(singleList.at(i)->getCondition()=="定值"){
            qs.append(" = ");
            if(stringNumList.contains(singleList.at(i)->getNameNum())){
                qs.append("'");
                qs.append(singleList.at(i)->getPrice());
                qs.append("'");
            }else{
                qs.append(singleList.at(i)->getPrice());
            }
        }else if(singleList.at(i)->getCondition()=="最小值"){
            qs.append(" > ");
            if(stringNumList.contains(singleList.at(i)->getNameNum())){
                qs.append("'");
                qs.append(singleList.at(i)->getPrice());
                qs.append("'");
            }else{
                qs.append(singleList.at(i)->getPrice());
            }
        }else if(singleList.at(i)->getCondition()=="最大值"){
            qs.append(" < ");
            if(stringNumList.contains(singleList.at(i)->getNameNum())){
                qs.append("'");
                qs.append(singleList.at(i)->getPrice());
                qs.append("'");
            }else{
                qs.append(singleList.at(i)->getPrice());
            }
        }
        qs.append(" and ");
    }
    qs.chop(4);
    qDebug() << "sql语句" << qs;
    emit sendResultString(qs);
    this->close();
}

void AdvanceSearch::setTableName(QString tableName)
{
    tName = tableName;
}

void AdvanceSearch::setStringNumList(QList<quint8> number)
{
    stringNumList = number;
}

void AdvanceSearch::setDingList(QList<int> list)
{
    dingList = list;
}

void AdvanceSearch::setMap(QMap<quint8, QStringList> mapString)
{
    map = mapString;
}
