#include "filedata.h"
#include "ui_filedata.h"
#include <QDebug>
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

filedata::filedata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filedata)
{
    ui->setupUi(this);
}

filedata::~filedata()
{
    delete ui;
}

void filedata::GetData(int x, int y)
{
    qDebug() << "i get the data :"<< x<<"  "<<y;
    QSqlQuery queryrownum=QSqlQuery(db);
    queryrownum.exec("SELECT distinct rowpro FROM pro504.filedata;");
    QSqlRecord rec = queryrownum.record();

    QStringList verheader;
    qDebug() << "Number of columns: " << rec.count();
    qDebug() << "number of ver:" << queryrownum.size();

    int rowpro = rec.indexOf("rowpro"); // index of the field "name"
    while (queryrownum.next())
    {
       qDebug() << queryrownum.value(rowpro).toString(); // output all names
       verheader << queryrownum.value(rowpro).toString();
    }


   QSqlQuery queryvernum=QSqlQuery(db);
   queryvernum.exec("SELECT distinct verpro FROM pro504.filedata;");
   QSqlRecord rec2 = queryvernum.record();

   QStringList strHeader;
   //设置表头 勾选 << 服务器地址 << 数据库类型 << 数据库名称 << 用户名

   qDebug() << "Number of columns: " << rec2.count();
   int verpro = rec2.indexOf("verpro"); // index of the field "name"
   while (queryvernum.next())
   {
        qDebug() << queryvernum.value(verpro).toString(); // output all names
        strHeader << queryvernum.value(verpro).toString();
   }

   ui->tableWidget->setColumnCount(queryvernum.size());
   ui->tableWidget->setRowCount(queryrownum.size());


   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");
   ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView { font-size: 19pt; }");

   ui->tableWidget->setHorizontalHeaderLabels(strHeader);  //添加表头
   ui->tableWidget->setVerticalHeaderLabels(verheader);  //添加列头

   QSqlQuery querydata=QSqlQuery(db);
   querydata.exec("SELECT data FROM filedata;");
   QSqlRecord rec3 = querydata.record();

   int data = rec3.indexOf("data");
   for(int i=0;i<queryvernum.size();i++)
   {
       for(int j=0;j<queryrownum.size();j++)
       {
           querydata.next();
           ui->tableWidget->setItem(i,j,new QTableWidgetItem(querydata.value(data).toString()));
       }
   }
}
