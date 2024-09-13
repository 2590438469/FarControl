#include "gemanage.h"
#include "ui_gemanage.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "QSqlQuery"
#include "QSqlRecord"
#include <QMessageBox>
#include "entity/geshan.h"
#include "config/configinfo.h"
#include "remotedatawidget.h"
#include "util/bytemethod.h"
#include <QDir>
#include "geshanadvancesearch.h"


QList<QString> folderFileList;

GeManage::GeManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeManage)
{
    ui->setupUi(this);
    QStringList headerList;
    headerList << "序号" << "任务名称" << "型号单位" << "武器型号" << "处理平台"
                  << "显示平台" << "武器状态" << "解算程序" << "SETUP名称" << "是否硬件加密"
                  << "加密信息备注"  << "显示画面名称" << "数据格栅名称" << "备注"
                  << "版本更新时间" << "编制人" << "电子格栅名称" << "电子格栅文件大小" << "显示画面文件大小" << "类型";
    set_widget_column_header(headerList);
    QList<quint8> string_column_list;
    string_column_list << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10
                       << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19;
    set_string_column_number(string_column_list);
    set_primaryKeyIndex(0);



    set_resizeMode(QHeaderView::ResizeToContents);
    initial_widget();
    connect(ui->pushButton_6,&QPushButton::clicked,this,&GeManage::uploadButtonSlot);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&GeManage::downloadButtonSlot);
    ui->tableWidget->setColumnHidden(1, true);
    ui->tableWidget->setColumnHidden(18, true);
    ui->tableWidget->setColumnHidden(17, true);
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::requestGeshan()),*addr,ConfigInfo::centerUdpPort);
    });
    connect(ui->pushButton_9,&QPushButton::clicked,[=](){
        GeshanAdvanceSearch *search = new GeshanAdvanceSearch();
        search->show();
    });
    connect(ui->pushButton_12,&QPushButton::clicked,[=](){
        qDebug() << "撤销";
        if(tableWidget_status == TableWidgetAddFlag){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
            tableWidget_status = TableWidgetCompleteFlag;
            currentRow = -1;
        }
    });
}

GeManage::~GeManage()
{
    delete ui;
}

void GeManage::set_widget_column_header(QStringList header)
{
    widget_column_header = header;
}

void GeManage::set_string_column_number(QList<quint8> number)
{
    string_column_number = number;
}

void GeManage::set_combobox_map(QMap<quint8, QStringList> map)
{
    combobox_map = map;
}

void GeManage::set_database(QString baseName)
{
    dataBaseName = baseName;
}

void GeManage::set_primaryKeyIndex(quint8 index)
{
    primaryKeyIndex = index;
}

void GeManage::set_fileIndex(quint8 index)
{
    openFileIndex = index;
}

void GeManage::set_codeIndex(quint8 code)
{
    missionCode = code;
}

void GeManage::set_resizeMode(QHeaderView::ResizeMode mode)
{
    resizeMode = mode;
}

void GeManage::set_aotuTimeColumn(int column)
{
    timeColumn = column;
    qDebug() << "设置时间";
}

void GeManage::initial_table_item(QList<GeShan*> list)
{
    tableWidget_status = TableWidgetCompleteFlag;
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
    if(refreshTimes!=0){
        QMessageBox::information(this,"刷新提示","刷新成功");
    }
    refreshTimes++;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(list.size());
    for(int i=0;i<list.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->xuhao);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,0,item);

        item = new QTableWidgetItem(list.at(i)->name);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,1,item);

        item = new QTableWidgetItem(list.at(i)->xinghaochangjia);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,2,item);

        item = new QTableWidgetItem(list.at(i)->daihao);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,3,item);

        item = new QTableWidgetItem(list.at(i)->chulipingtai);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,4,item);

        item = new QTableWidgetItem(list.at(i)->xianshipingtai);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,5,item);

        item = new QTableWidgetItem(list.at(i)->zhuangtaibeizhu);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,6,item);

        item = new QTableWidgetItem(list.at(i)->jiesuanchengxu);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,7,item);

        item = new QTableWidgetItem(list.at(i)->setup);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,8,item);

        item = new QTableWidgetItem(list.at(i)->shifoujiami);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,9,item);

        item = new QTableWidgetItem(list.at(i)->jiamixinxibeizhu);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,10,item);

        item = new QTableWidgetItem(list.at(i)->xianshihuamianbanben);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,11,item);

        item = new QTableWidgetItem(list.at(i)->jiesuanruanjianwenjianjia);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,12,item);

        item = new QTableWidgetItem(list.at(i)->beizhu);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,13,item);

        item = new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(list.at(i)->banbengengxinshijian.toInt()).toString("yyyy-MM-dd hh:mm"));
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,14,item);

        item = new QTableWidgetItem(list.at(i)->people);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,15,item);

        item = new QTableWidgetItem(list.at(i)->dianzigeshan);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,16,item);

        item = new QTableWidgetItem(QString::number(list.at(i)->filesize));
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,17,item);

        item = new QTableWidgetItem(QString::number(list.at(i)->displayFilesize));
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,18,item);

        item = new QTableWidgetItem(list.at(i)->type);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,19,item);
    }
}

void GeManage::finishAddGeshan()
{
    tableWidget_status = TableWidgetCompleteFlag;
    QMessageBox::information(this,"添加提示","添加成功");
    ui->tableWidget->setRowCount(0);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(AgreeMent::requestGeshan()),addre,ConfigInfo::centerUdpPort);
}

void GeManage::wrongAddGeshan()
{
    tableWidget_status = TableWidgetCompleteFlag;
    QMessageBox::information(this,"添加提示","添加失败");
    ui->tableWidget->setRowCount(0);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(AgreeMent::requestGeshan()),addre,ConfigInfo::centerUdpPort);
}

void GeManage::refreshChildFile(ChildFileWithParent* withParent)
{
    fileDownLoadWidget->refreshWidget(withParent);
}

quint8 GeManage::initial_widget(){
    if(!widget_column_header.size()){
        qDebug() << "初始化失败，请检查是否使用set_widget_column_header来设置列头";
        return 0;
    }else{
        ui->tableWidget->setColumnCount(widget_column_header.size());
        ui->tableWidget->setHorizontalHeaderLabels(widget_column_header);

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

        ui->tableWidget->horizontalHeader()->setSectionResizeMode(resizeMode);
        ui->tableWidget->setRowHeight(0,40);
        ui->tableWidget->verticalHeader()->setVisible(0);




        connect(ui->pushButton_2,&QPushButton::clicked,this,&GeManage::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&GeManage::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&GeManage::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&GeManage::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&GeManage::searchButton_slot);
        connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
        return 1;
    }

}


void GeManage::editFinish(quint8 opResult)
{
    if(opResult){
        QMessageBox::information(this,"更改提示","更改成功");
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(combobox_map.contains(i)){
                QComboBox *combobox;
                combobox = (QComboBox*)ui->tableWidget->cellWidget(currentRow,i);
                QTableWidgetItem *item = new QTableWidgetItem(combobox->currentText());
                ui->tableWidget->removeCellWidget(currentRow,i);
                ui->tableWidget->setItem(currentRow,i,item);
            }
        }
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            QTableWidgetItem *item = ui->tableWidget->item(currentRow,i);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            QColor *color;
            if(currentRow%2==0){
                color = new QColor(255,255,255);
            }else{
                color = new QColor(245,245,245);
            }
            item->setBackgroundColor(*color);
        }
    }else{
        QMessageBox::information(this,"更改提示","更改失败");
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(combobox_map.contains(i)){
                QComboBox *combobox;
                combobox = (QComboBox*)ui->tableWidget->cellWidget(currentRow,i);
                QTableWidgetItem *item = new QTableWidgetItem(oldValue.at(i));
                ui->tableWidget->removeCellWidget(currentRow,i);
                ui->tableWidget->setItem(currentRow,i,item);
            }else{
                QTableWidgetItem *item = new QTableWidgetItem(oldValue.at(i));
                ui->tableWidget->setItem(currentRow,i,item);
            }
        }
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            QTableWidgetItem *item = ui->tableWidget->item(currentRow,i);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            QColor *color;
            if(currentRow%2==0){
                color = new QColor(255,255,255);
            }else{
                color = new QColor(230,230,230);
            }
            item->setBackgroundColor(*color);
        }
    }

    tableWidget_status = TableWidgetCompleteFlag;
    oldValue.clear();
    currentRow = -1;
}

void GeManage::addFinish(quint8 opResult)
{
    if(opResult){
        QMessageBox::information(this,"添加提示","添加成功");
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(combobox_map.contains(i)){
                QComboBox *combobox;
                combobox = (QComboBox*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),i);
                QTableWidgetItem *item = new QTableWidgetItem(combobox->currentText());
                ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,i);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
            }
            if(timeColumn==i){
                QTableWidgetItem *item = new QTableWidgetItem(recentTime);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
            }
        }
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            QTableWidgetItem *item = ui->tableWidget->item(ui->tableWidget->rowCount()-1,i);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            QColor *color;
            if((ui->tableWidget->rowCount()-1)%2==0){
                color = new QColor(255,255,255);
            }else{
                color = new QColor(230,230,230);
            }
            item->setBackgroundColor(*color);
        }
    }else{
        QMessageBox::information(this,"添加提示","添加失败");
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
    }

    tableWidget_status = TableWidgetCompleteFlag;
}

void GeManage::deleteFinish(quint8 opResult)
{
    if(opResult){
        QMessageBox::information(this,"删除提示","删除成功");
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }else{
        QMessageBox::information(this,"删除提示","删除失败");
    }
    tableWidget_status = TableWidgetCompleteFlag;
}

quint8 GeManage::initial_widget(quint8 opResult,QVector<QVector<QString>> array)
{
    if(!widget_column_header.size())
    {
        qDebug() << "初始化失败，请检查是否使用set_widget_column_header来设置列头";
        qDebug() << "初始化成功";
        return 0;
    }
    else
    {
        qDebug() << "初始化成功";
        ui->tableWidget->setColumnCount(widget_column_header.size());
        ui->tableWidget->setHorizontalHeaderLabels(widget_column_header);

        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
        ui->tableWidget->setStyleSheet("font-size: 12pt;");
        QPalette pal = ui->tableWidget->palette();
        pal.setColor(QPalette::Base, QColor(255, 255, 255));
        pal.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
        ui->tableWidget->setPalette(pal);
        ui->tableWidget->setAlternatingRowColors(true);
        ui->tableWidget->viewport()->update();

        ui->tableWidget->horizontalHeader()->setSectionResizeMode(resizeMode);
        ui->tableWidget->setRowHeight(0,40);
        ui->tableWidget->verticalHeader()->setVisible(0);



        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
        }

        connect(ui->pushButton_2,&QPushButton::clicked,this,&GeManage::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&GeManage::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&GeManage::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&GeManage::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&GeManage::searchButton_slot);
        return 1;
    }

}

void GeManage::addButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示","请完成当前操作");
        return ;
    }
    disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
    if(tableWidget_status == TableWidgetCompleteFlag){
        ui->tableWidget->setRowCount((ui->tableWidget->rowCount())+1);

        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(combobox_map.contains(i)){
                QComboBox *combobox = new QComboBox;
                QList<QStringList> values = combobox_map.values(i);
                combobox->addItems(values.at(0));
                combobox->setStyleSheet("background-color: rgb(200,200,200);");
                ui->tableWidget->setCellWidget((ui->tableWidget->rowCount())-1,i,combobox);
            }else{
                QTableWidgetItem *item = new QTableWidgetItem("");
                QColor *color = new QColor(200,200,200);
                item->setBackgroundColor(*color);
                item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
                item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
            }
        }
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->flags());//选中变换蓝底


        ui->tableWidget->item(ui->tableWidget->rowCount()-1,14)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,14)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,14)->flags());//选中变换蓝底

        ui->tableWidget->item(ui->tableWidget->rowCount()-1,16)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,16)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,16)->flags());//选中变换蓝底

        ui->tableWidget->item(ui->tableWidget->rowCount()-1,17)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,17)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,17)->flags());//选中变换蓝底


        ui->tableWidget->item(ui->tableWidget->rowCount()-1,11)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,11)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,11)->flags());//选中变换蓝底

        ui->tableWidget->item(ui->tableWidget->rowCount()-1,12)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,12)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,12)->flags());//选中变换蓝底

        ui->tableWidget->item(ui->tableWidget->rowCount()-1,18)->setFlags(Qt::ItemIsEnabled);//不可编辑
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,18)->setFlags(Qt::ItemIsSelectable|ui->tableWidget->item(ui->tableWidget->rowCount()-1,18)->flags());//选中变换蓝底
        tableWidget_status = TableWidgetAddFlag;
    }else{
        QMessageBox::information(this,"提示","请完成当前操作");
    }
}

void GeManage::deleteButton_slot()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示","请完成当前操作");
        return ;
    }
    QString str("是否确认删除第%1项");
    str = str.arg(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes)
    {
        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendDeleteGeshan(ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text())),addre,ConfigInfo::centerUdpPort);
    }
}

void GeManage::finishButton_slot()
{
    QVector<QString> Array;
    quint8 logo;
    switch (tableWidget_status) {
    case TableWidgetAddFlag:
        addFinish();
        break;
    case TableWidgetEditFlag:
        editFinish();
        break;
    case TableWidgetDeleteFlag:
        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
        }
        break;
    default:
        break;
    }

}

void GeManage::editButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示","请完成当前操作");
        return ;
    }
    disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
    currentRow = ui->tableWidget->currentRow();

    if(ui->tableWidget->currentRow() < 0){
        QMessageBox::information(this,"编辑提示","请选择一项进行编辑操作");
    }else{
        int currentRow = ui->tableWidget->currentRow();
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(i!=0&&i!=11&&i!=12&&i!=14&&i!=16&&i!=17&&i!=0&&i!=18&&i!=3&&i!=6){
                QTableWidgetItem *item = ui->tableWidget->item(currentRow,i);
                QColor *color = new QColor(200,200,200);
                item->setBackgroundColor(*color);
                item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
                item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            }
        }
    }
    tableWidget_status = TableWidgetEditFlag;
}

void GeManage::searchButton_slot()
{
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
        for(int i=0;i<item.count();i++)
        {
            ui->tableWidget->setRowHidden(item.at(i)->row(),false);
            rowhide++;

        }

        ui->label->setText(QString("查询结果:%1项").arg(QString::number(item.count())));
    }
    else
    {
        ui->label->setText(QString("查询结果:0项"));
    }
    if(input_name == ""){
        ui->label->setText(QString(""));
    }

}

void GeManage::uploadButtonSlot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"提示信息","未选择行");
        return;
    }

    if(ui->tableWidget->currentColumn() == 16){
        QString filePath = QFileDialog::getOpenFileName(this,"open","../");

        if(filePath.isEmpty()==false){
            QFileInfo info(filePath);
            QString fileName = info.fileName();
            quint64 fileSize = info.size();
            QString filePath = info.absoluteFilePath();

            FileInfo *fileInfo = new FileInfo();

            fileInfo->code = "无";
            fileInfo->fileName = fileName;
            fileInfo->fileSize = fileSize;
            fileInfo->status = "无";
            fileInfo->model = "无";
            fileInfo->filePath = filePath;
            fileInfo->parentPath = ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text();

            QCryptographicHash hash(QCryptographicHash::Md5);
            QFile *file = new QFile();
            file->setFileName(filePath);
            file->open(QIODevice::ReadOnly);

            hash.addData(file);


            QByteArray array;

            array = AgreeMent::sendFileInfo(fileName,fileSize,"无",3,hash.result(),ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text(),userName,0,0);
            fileInfo->type = 3;
            qDebug() << "11文件路径" << fileInfo->filePath;
            remoteDataWidget->setDllInfo(fileInfo);

            QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
            udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

            file->close();
            QMessageBox::information(this,"传输提示","开始上传");

        }else{
            qDebug() << "文件路劲获取失败";
        }
    }else if(ui->tableWidget->currentColumn() == 11){
        QString filePath = QFileDialog::getOpenFileName(this,"open","../");

        if(filePath.isEmpty()==false){
            QFileInfo info(filePath);
            QString fileName = info.fileName();
            quint64 fileSize = info.size();
            QString filePath = info.absoluteFilePath();

            FileInfo *fileInfo = new FileInfo();

            fileInfo->code = "无";
            fileInfo->fileName = fileName;
            fileInfo->fileSize = fileSize;
            fileInfo->status = "无";
            fileInfo->model = "无";
            fileInfo->filePath = filePath;
            fileInfo->parentPath = ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text();

            QCryptographicHash hash(QCryptographicHash::Md5);
            QFile *file = new QFile();
            file->setFileName(filePath);
            file->open(QIODevice::ReadOnly);

            hash.addData(file);


            QByteArray array;

            array = AgreeMent::sendFileInfo(fileName,fileSize,"无",4,hash.result(),ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text(),userName,0,0);
            fileInfo->type = 4;
            qDebug() << "11文件路径" << fileInfo->filePath;
            remoteDataWidget->setDllInfo(fileInfo);

            QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
            udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

            file->close();
            QMessageBox::information(this,"传输提示","开始上传");

        }else{
            qDebug() << "文件路劲获取失败";
        }
    }else if(ui->tableWidget->currentColumn() == 12){
        QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
        if(directoryPath==""){
            return;
        }
        QDir directory(directoryPath);
        if (!directory.exists()) {
            qDebug() << "Directory does not exist: " << directoryPath;
            return;
        }

        directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        QFileInfoList fileInfoList = directory.entryInfoList();

        folderFileList.append(ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text());
        foreach (const QFileInfo &fileInfo, fileInfoList) {
            qDebug() << "File Absolute Path: " << fileInfo.absoluteFilePath();
            folderFileList.append(fileInfo.absoluteFilePath());
        }








        if(folderFileList.size()>1){
            QFileInfo info(folderFileList.at(1));
            QString fileName = info.fileName();
            quint64 fileSize = info.size();
            QString filePath = info.absoluteFilePath();

            FileInfo *fileInfo = new FileInfo();

            fileInfo->code = "无";
            fileInfo->fileName = fileName;
            fileInfo->fileSize = fileSize;
            fileInfo->status = "无";
            fileInfo->model = "无";
            fileInfo->filePath = filePath;
            fileInfo->parentPath = folderFileList.at(0);

            QCryptographicHash hash(QCryptographicHash::Md5);
            QFile *file = new QFile();
            file->setFileName(filePath);
            file->open(QIODevice::ReadOnly);

            hash.addData(file);


            QByteArray array;

            array = AgreeMent::sendFileInfo(fileName,fileSize,"无",2,hash.result(),folderFileList.at(0),userName,1,0);
            fileInfo->type = 2;
            remoteDataWidget->setDllInfo(fileInfo);

            QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
            udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

            file->close();
        }else{
            folderFileList.clear();
        }
    }
}

void GeManage::downloadButtonSlot()
{
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"提示信息","未选择项");
        return;
    }
    QMessageBox::information(this,"提示信息","开始下载");
    if(ui->tableWidget->currentColumn() == 16){
        FileInfo *info = new FileInfo();
        info->fileName = ui->tableWidget->item(ui->tableWidget->currentRow(),16)->text();
        info->fileSize = ui->tableWidget->item(ui->tableWidget->currentRow(),17)->text().toLongLong();
        fileDownload1->setFileInfo(info);

        grilleWorker->fileDirectoryPath = ConfigInfo::geShanMulu;
        grilleWorker->setFileName(ui->tableWidget->item(ui->tableWidget->currentRow(),16)->text());
        grilleWorker->parentString = ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text();
        grilleWorker->setFileSize(ui->tableWidget->item(ui->tableWidget->currentRow(),17)->text().toLongLong());

        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDownloadDianziRequest(ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text(),ui->tableWidget->item(ui->tableWidget->currentRow(),16)->text(),userName)),addre,ConfigInfo::centerUdpPort);
    }else if(ui->tableWidget->currentColumn() == 11){
        FileInfo *info = new FileInfo();
        info->fileName = ui->tableWidget->item(ui->tableWidget->currentRow(),11)->text();
        info->fileSize = ui->tableWidget->item(ui->tableWidget->currentRow(),18)->text().toLongLong();
        fileDownload1->setFileInfo(info);

        grilleWorker->fileDirectoryPath = ConfigInfo::geShanMulu;
        grilleWorker->setFileName(ui->tableWidget->item(ui->tableWidget->currentRow(),11)->text());
        grilleWorker->parentString = ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text();
        grilleWorker->setFileSize(ui->tableWidget->item(ui->tableWidget->currentRow(),18)->text().toLongLong());

        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDownloadDianziRequest(ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text(),ui->tableWidget->item(ui->tableWidget->currentRow(),11)->text(),userName)),addre,ConfigInfo::centerUdpPort);
    }
}

void GeManage::cellDoubleClicked(int row, int column)
{
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(AgreeMent::requestGeshanChildFile(ui->tableWidget->item(row,12)->text())),addre,ConfigInfo::centerUdpPort);
    fileDownLoadWidget->setstring(ui->tableWidget->item(row,12)->text());
    fileDownLoadWidget->show();
    connect(fileDownLoadWidget,&FileDownLoadWidget::sendFileInfo,remoteDataWidget,&RemoteDataSingleWidget::setDllInfo);
    connect(this,&GeManage::sendFileInfo,remoteDataWidget,&RemoteDataSingleWidget::setDllInfo);
}

QByteArray GeManage::getInvert(QByteArray array)
{
    unsigned char k = 0x80;
    QByteArray invertArray;
    quint8 tempCharAsc = 0;
    char tempChar;
    invertArray.resize(array.size());
    for(int i=0;i<array.size();i++){
        for(int j=0;j<8;j++){
            if(quint8(array.at(i)) & k){
            }else{
                tempCharAsc += pow(2,7-j);
            }
            k >>=1;
        }
        tempChar = tempCharAsc;
        invertArray[i] = tempChar;
        tempChar = 0;
        tempCharAsc = 0;
        k = 0x80;
    }
    return invertArray;
}

void GeManage::addFinish()
{
    if(ui->tableWidget->item(ui->tableWidget->rowCount()-1,3)->text()==""){
        QMessageBox::information(this,"提示信息","未填武器型号");
        return ;
    }
    if(ui->tableWidget->item(ui->tableWidget->rowCount()-1,6)->text()==""){
        QMessageBox::information(this,"提示信息","未填武器状态");
        return ;
    }
    GeShan *geshan = new GeShan();
    geshan->name = ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->text();
    geshan->xinghaochangjia = ui->tableWidget->item(ui->tableWidget->rowCount()-1,2)->text();
    geshan->daihao = ui->tableWidget->item(ui->tableWidget->rowCount()-1,3)->text();
    geshan->chulipingtai = ui->tableWidget->item(ui->tableWidget->rowCount()-1,4)->text();
    geshan->xianshipingtai = ui->tableWidget->item(ui->tableWidget->rowCount()-1,5)->text();
    geshan->zhuangtaibeizhu = ui->tableWidget->item(ui->tableWidget->rowCount()-1,6)->text();
    geshan->jiesuanchengxu = ui->tableWidget->item(ui->tableWidget->rowCount()-1,7)->text();
    geshan->setup = ui->tableWidget->item(ui->tableWidget->rowCount()-1,8)->text();
    geshan->shifoujiami = ui->tableWidget->item(ui->tableWidget->rowCount()-1,9)->text();
    geshan->jiamixinxibeizhu = ui->tableWidget->item(ui->tableWidget->rowCount()-1,10)->text();
    geshan->xianshihuamianbanben = ui->tableWidget->item(ui->tableWidget->rowCount()-1,11)->text();
    geshan->jiesuanruanjianwenjianjia = ui->tableWidget->item(ui->tableWidget->rowCount()-1,12)->text();
    geshan->beizhu = ui->tableWidget->item(ui->tableWidget->rowCount()-1,13)->text();
    geshan->banbengengxinshijian = ui->tableWidget->item(ui->tableWidget->rowCount()-1,14)->text();
    geshan->people = ui->tableWidget->item(ui->tableWidget->rowCount()-1,15)->text();
    geshan->type = ui->tableWidget->item(ui->tableWidget->rowCount()-1,19)->text();
    qDebug() << "发送的type" << geshan->type <<ui->tableWidget->item(ui->tableWidget->rowCount()-1,19)->text();
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendGeshan(geshan)),addre,ConfigInfo::centerUdpPort);
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);

}

void GeManage::editFinish()
{
    GeShan *geshan = new GeShan();
    geshan->xuhao = ui->tableWidget->item(currentRow,0)->text();
    geshan->name = ui->tableWidget->item(currentRow,1)->text();
    geshan->xinghaochangjia = ui->tableWidget->item(currentRow,2)->text();
    geshan->daihao = ui->tableWidget->item(currentRow,3)->text();
    geshan->chulipingtai = ui->tableWidget->item(currentRow,4)->text();
    geshan->xianshipingtai = ui->tableWidget->item(currentRow,5)->text();
    geshan->zhuangtaibeizhu = ui->tableWidget->item(currentRow,6)->text();
    geshan->jiesuanchengxu = ui->tableWidget->item(currentRow,7)->text();
    geshan->setup = ui->tableWidget->item(currentRow,8)->text();
    geshan->shifoujiami = ui->tableWidget->item(currentRow,9)->text();
    geshan->jiamixinxibeizhu = ui->tableWidget->item(currentRow,10)->text();
    geshan->beizhu = ui->tableWidget->item(currentRow,13)->text();
    geshan->people = ui->tableWidget->item(currentRow,15)->text();
    geshan->type = ui->tableWidget->item(currentRow,19)->text();
    geshan->jiesuanruanjianwenjianjia =  ui->tableWidget->item(currentRow,12)->text();
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        QTableWidgetItem *item = ui->tableWidget->item(currentRow,i);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        QColor *color;
        if(currentRow%2==0){
            color = new QColor(255,255,255);
        }else{
            color = new QColor(245,245,245);
        }
        item->setBackgroundColor(*color);
    }
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(AgreeMent::sendUpdateGeshan(geshan)),addre,ConfigInfo::centerUdpPort);
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&GeManage::cellDoubleClicked);
}

void GeManage::sendFolderFile()
{
    if(folderFileList.size()>1){
        QFileInfo info(folderFileList.at(1));
        QString fileName = info.fileName();
        quint64 fileSize = info.size();
        QString filePath = info.absoluteFilePath();

        FileInfo *fileInfo = new FileInfo();

        fileInfo->code = "无";
        fileInfo->fileName = fileName;
        fileInfo->fileSize = fileSize;
        fileInfo->status = "无";
        fileInfo->model = "无";
        fileInfo->filePath = filePath;
        fileInfo->parentPath = folderFileList.at(0);

        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile *file = new QFile();
        file->setFileName(filePath);
        file->open(QIODevice::ReadOnly);

        hash.addData(file);


        QByteArray array;

        array = AgreeMent::sendFileInfo(fileName,fileSize,"无",2,hash.result(),folderFileList.at(0),userName,0,0);
        fileInfo->type = 2;
        remoteDataWidget->setDllInfo(fileInfo);

        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

        file->close();
    }else{
        folderFileList.clear();
    }

}

void GeManage::getUpdateResult(int result)
{
    if(result){
        QMessageBox::information(this,"更新提示","更新成功");
    }else{
        QMessageBox::information(this,"更新提示","更新失败，请刷新");
    }
}



