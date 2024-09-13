#include "datamanage.h"
#include "ui_datamanage.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlError>
#include "advancesearch.h"
#include <QMap>


DataManage::DataManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataManage)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
    ui->tableWidget->setStyleSheet("font-size: 12pt;");
//    ui->tableWidget->setAlternatingRowColors(true);
    QPalette pal = ui->tableWidget->palette();
    pal.setColor(QPalette::Base, QColor(255, 255, 255));
    pal.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
    ui->tableWidget->setPalette(pal);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->viewport()->update();

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowHeight(0,40);
    ui->tableWidget->verticalHeader()->setVisible(0);

    qDebug() << "执行了方法";

    QStringList headList;
    headList << "任务代号" << "武器型号-状态" << "时间" <<"类型" << "存储路径";
    ui->tableWidget->setColumnCount(headList.size());
    ui->tableWidget->setHorizontalHeaderLabels(headList);
    initialItem();



    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataManage::doubleclick);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&DataManage::deleteItem);

    connect(ui->pushButton_6,&QPushButton::clicked,this,&DataManage::advanceCheckSlot);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString input_name=ui->lineEdit->text();
        int row_num=ui->tableWidget->rowCount();
        QList <QTableWidgetItem *> item = ui->tableWidget->findItems(input_name, Qt::MatchContains);
        for(int i=0;i<row_num;i++)
        {
            ui->tableWidget->setRowHidden(i,true);//隐藏

        }
        //判断符合条件索引是不是空
        int rowhide = 0;
        if(!item.empty())
        {
            if(ui->lineEdit->text()!=""){
                for(int i=0;i<item.count();i++)
                {
                    ui->tableWidget->setRowHidden(item.at(i)->row(),false);
                    rowhide++;
                    ui->label_17->setText(QString("查询结果:%1项").arg(QString::number(item.count())));

                }

            }else{
                initialItem();
            }
        }
    });
}

DataManage::~DataManage()
{
    delete ui;
}

void DataManage::initialItem()
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(db);
    QString qs = QString("select * from `datamanage`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());

    int code = rec.indexOf("任务标识");
    int model = rec.indexOf("武器型号");
    int time = rec.indexOf("时间");
    int classi = rec.indexOf("类型");
    int path = rec.indexOf("存储路径");
    int linenum=0;

    while (query.next())
    {
        QString codestr = query.value(code).toString();
        QString modelstr = query.value(model).toString();
        QString timestr = query.value(time).toString();
        QString classistr = query.value(classi).toString();
        QString pathstr = query.value(path).toString();
        QTableWidgetItem *item = new QTableWidgetItem(codestr);
        ui->tableWidget->setItem(linenum,0,item);
        item = new QTableWidgetItem(modelstr);
        ui->tableWidget->setItem(linenum,1,item);
        item = new QTableWidgetItem(timestr);
        ui->tableWidget->setItem(linenum,2,item);
        item = new QTableWidgetItem(classistr);
        ui->tableWidget->setItem(linenum,3,item);
        item = new QTableWidgetItem(pathstr);
        ui->tableWidget->setItem(linenum,4,item);
        linenum++;
    }
}

void DataManage::refresh()
{
    initialItem();
}

void DataManage::doubleclick(int row, int column)
{

    QString dirPath = ui->tableWidget->item(row,4)->text(); // 文件夹路径

    QDesktopServices::openUrl(QUrl::fromLocalFile(dirPath));
}

void DataManage::deleteItem()
{
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    QString str("是否确认删除");
    str.append((ui->tableWidget->item(ui->tableWidget->currentRow(),0))->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes){
        QSqlQuery query(db);
        QString qs = QString("delete from `datamanage` where `任务标识` = ");
        qs.insert(qs.size(),"'");
        qs.insert(qs.size(),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
        qs.insert(qs.size(),"'");
        bool ok = query.exec(qs);

        if(ok){
            QMessageBox::information(this,"删除提示","删除成功");
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }else{
            QMessageBox::information(this,"删除提示",query.lastError().text());
        }
    }
}

void DataManage::advanceCheckSlot()
{
    AdvanceSearch *advanceSearch = new AdvanceSearch();
    QStringList list;
    list << "任务标识" << "武器型号"  <<"类型" << "存储路径";
    QList<quint8> stringNumList;
    stringNumList << 0 << 1 << 2 << 3 ;
    advanceSearch->setStringNumList(stringNumList);
    advanceSearch->setTableName("datamanage");
    advanceSearch->setList(list);
    QMap<quint8, QStringList> map;
    QStringList list2;
    list2 << "类型1" << "类型2" << "类型3" ;
    map.insert(2,list2);
    advanceSearch->setMap(map);
    QList<int> intList;
    intList<< 2;
    advanceSearch->setDingList(intList);
    advanceSearch->show();
    connect(advanceSearch,&AdvanceSearch::sendResultString,this,&DataManage::advanceResult);
}

void DataManage::advanceResult(QString result)
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(db);
    QString qs = result;
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());

    int code = rec.indexOf("任务标识");
    int model = rec.indexOf("武器型号");
    int time = rec.indexOf("时间");
    int classi = rec.indexOf("类型");
    int path = rec.indexOf("存储路径");
    int linenum=0;

    while (query.next())
    {
        QString codestr = query.value(code).toString();
        QString modelstr = query.value(model).toString();
        QString timestr = query.value(time).toString();
        QString classistr = query.value(classi).toString();
        QString pathstr = query.value(path).toString();
        QTableWidgetItem *item = new QTableWidgetItem(codestr);
        ui->tableWidget->setItem(linenum,0,item);
        item = new QTableWidgetItem(modelstr);
        ui->tableWidget->setItem(linenum,1,item);
        item = new QTableWidgetItem(timestr);
        ui->tableWidget->setItem(linenum,2,item);
        item = new QTableWidgetItem(classistr);
        ui->tableWidget->setItem(linenum,3,item);
        item = new QTableWidgetItem(pathstr);
        ui->tableWidget->setItem(linenum,4,item);
        linenum++;
    }
}
