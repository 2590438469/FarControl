#include "datamanage.h"
#include "ui_datamanage.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "datamanage.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlError>
#include <QDateTime>
#include "config/configinfo.h"
#include "util/bytemethod.h"
#include "dataadvancesearch.h"

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
    headList << "任务代号" << "武器型号-状态" << "时间" <<"类型" << "文件名" << "文件大小" << "序号" << "上传者";
    ui->tableWidget->setColumnCount(headList.size());
    ui->tableWidget->setHorizontalHeaderLabels(headList);
    initialItem();


//    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataManage::doubleclick);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&DataManage::deleteItem);

    ui->pushButton_2->hide();

    connect(ui->pushButton_6,&QPushButton::clicked,this,&DataManage::downloadItem);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&DataManage::sendRefresh);

    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        DataAdvanceSearch *p = new DataAdvanceSearch();
        p->show();
    });
    connect(ui->pushButton_4,&QPushButton::clicked,this,&DataManage::finishButtonSlot);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&DataManage::editButtonSlot);
}

DataManage::~DataManage()
{
    delete ui;
}

void DataManage::initialItem()
{
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
}

void DataManage::deleteItem()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    if(tableWidget_status==1){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    QString str("是否确认删除");
    str.append((ui->tableWidget->item(ui->tableWidget->currentRow(),6))->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes){
        QByteArray array = AgreeMent::deleteRemoteData(ui->tableWidget->item(ui->tableWidget->currentRow(),6)->text());
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);
    }
}

void DataManage::refreshAll(QList<RemoteData *> list)
{

    tableWidget_status = 0;
    if(refreshTimes!=0){
        QMessageBox::information(this,"提示信息","刷新成功");
    }
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(list.size());

    refreshTimes ++ ;

    for(int i=0;i<list.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->code);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,0,item);

        item = new QTableWidgetItem(list.at(i)->model);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,1,item);

        item = new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(list.at(i)->time).toString("yyyy-MM-dd hh:mm"));
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,2,item);

        item = new QTableWidgetItem(list.at(i)->type);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,3,item);

        item = new QTableWidgetItem(list.at(i)->fileName);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,4,item);

        item = new QTableWidgetItem(QString::number(list.at(i)->fileSize));
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,5,item);

        item = new QTableWidgetItem(QString::number(list.at(i)->id));
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,6,item);

        item = new QTableWidgetItem(list.at(i)->user);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,7,item);
    }
}

void DataManage::downloadItem()
{
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"提示信息","未选择项");
        return;
    }
    QMessageBox::information(this,"提示信息","开始下载");
    FileInfo *info = new FileInfo();
    info->fileName = ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text();
    info->fileSize = ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text().toLongLong();
    fileDownload1->setFileInfo(info);
    grilleWorker->fileDirectoryPath = ConfigInfo::displayMulu;
    grilleWorker->parentString = ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
    grilleWorker->setFileName(ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text());
    grilleWorker->setFileSize(ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text().toLongLong());

    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDownloadRemoteRequest(ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text(),userName,ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text())),addre,ConfigInfo::centerUdpPort);
}

void DataManage::sendRefresh()
{
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::requestRemoteGeshan()),addre,ConfigInfo::centerUdpPort);
}

void DataManage::getDeleteResult(int result)
{
    if(result){
        QMessageBox::information(this,"删除提示","删除成功,请刷新");
    }else{
        QMessageBox::information(this,"删除提示","删除失败");
    }
}

void DataManage::getUpdateResult(int result)
{
    if(result){
        QMessageBox::information(this,"删除提示","更新成功");
    }else{
        QMessageBox::information(this,"删除提示","更新失败,请刷新");
    }
}

void DataManage::editButtonSlot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(tableWidget_status==1){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    tableWidget_status = 1;
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"提示信息","未选择项");
        return;
    }
    currentRow = ui->tableWidget->currentRow();
    QTableWidgetItem *item = ui->tableWidget->item(ui->tableWidget->currentRow(),3);
    QColor *color = new QColor(200,200,200);
    item->setBackgroundColor(*color);
    item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
}

void DataManage::finishButtonSlot()
{
    if(tableWidget_status!=1){
        qDebug() << "无效";
        return ;
    }
    qDebug() << "有效";
    QTableWidgetItem *item = ui->tableWidget->item(currentRow,3);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    QColor *color;
    if(currentRow%2==0){
        color = new QColor(255,255,255);
    }else{
        color = new QColor(230,230,230);
    }
    item->setBackgroundColor(*color);

    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendUpdateData(ui->tableWidget->item(currentRow,6)->text(),ui->tableWidget->item(currentRow,3)->text())),addre,ConfigInfo::centerUdpPort);
    tableWidget_status = 0;
}
