#include "missiontablewidget.h"
#include "ui_missiontablewidget.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QSqlError>
#include "missionnewinsert.h"
#include "firstwindow.h"
#include "config/configinfo.h"

MissionTableWidget::MissionTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionTableWidget)
{
    ui->setupUi(this);
}

MissionTableWidget::~MissionTableWidget()
{
    delete ui;
}

void MissionTableWidget::set_widget_column_header(QStringList header)
{
    widget_column_header = header;
}

void MissionTableWidget::set_string_column_number(QList<quint8> number)
{
    string_column_number = number;
}

void MissionTableWidget::set_combobox_map(QMap<quint8, QStringList> map)
{
    combobox_map = map;
}

void MissionTableWidget::set_database(QString baseName)
{
    dataBaseName = baseName;
}

void MissionTableWidget::set_primaryKeyIndex(quint8 index)
{
    primaryKeyIndex = index;
}

void MissionTableWidget::editFinish(quint8 opResult)
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
                color = new QColor(243,243,243);
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

void MissionTableWidget::deleteFinish(quint8 opResult)
{
    if(opResult){
        QMessageBox::information(this,"删除提示","删除成功");
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }else{
        QMessageBox::information(this,"删除提示","删除失败");
    }
    tableWidget_status = TableWidgetCompleteFlag;
}

void MissionTableWidget::addFinish(quint8 opResult)
{
    if(opResult)
    {
        disconnect(ui->pushButton_2,&QPushButton::clicked,this,&MissionTableWidget::addButton_slot);
        disconnect(ui->pushButton_4,&QPushButton::clicked,this,&MissionTableWidget::finishButton_slot);
        disconnect(ui->pushButton_5,&QPushButton::clicked,this,&MissionTableWidget::editButton_slot);
        disconnect(ui->pushButton_3,&QPushButton::clicked,this,&MissionTableWidget::deleteButton_slot);
        disconnect(ui->pushButton,&QPushButton::clicked,this,&MissionTableWidget::searchButton_slot);
        sendInitialQuest(quint8(0x02));
        QMessageBox::information(this,"添加提示","添加成功");

    }else{
        QMessageBox::information(this,"添加提示","添加失败");
    }

}

void MissionTableWidget::addButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    MissionNewInsert *p = new MissionNewInsert();
    p->show();
}

void MissionTableWidget::deleteButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    qDebug() << "current row" << ui->tableWidget->currentRow();
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    QString str("是否确认删除");
    str.append((ui->tableWidget->item(ui->tableWidget->currentRow(),primaryKeyIndex))->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes)
    {
        tableWidget_status = TableWidgetDeleteFlag;
        finishButton_slot();
    }
}

void MissionTableWidget::finishButton_slot()
{
    QVector<QString> Array;
    quint8 logo;
    switch (tableWidget_status) {
    case TableWidgetEditFlag:
        sendEditInfo(Array,logo);
        break;
    case TableWidgetDeleteFlag:
        sendDeleteInfo(Array,logo);
        break;
    default:
        break;
    }

}

void MissionTableWidget::editButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    currentRow = ui->tableWidget->currentRow();
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        oldValue.append(ui->tableWidget->item(currentRow,i)->text());
    }

    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"编辑提示","请选择一项进行编辑操作");
    }else{
        int currentRow = ui->tableWidget->currentRow();
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(combobox_map.contains(i)){
                QComboBox *combobox = new QComboBox;
                QList<QStringList> values = combobox_map.values(i);
                combobox->addItems(values.at(0));
                combobox->setCurrentText(ui->tableWidget->item(ui->tableWidget->currentRow(),i)->text());
                combobox->setStyleSheet("background-color: rgb(200,200,200);");
                ui->tableWidget->setCellWidget(ui->tableWidget->currentRow(),i,combobox);
            }else{
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

void MissionTableWidget::searchButton_slot()
{
    QString input_name=ui->lineEdit->text();
    int row_num=ui->tableWidget->rowCount();
    QList <QTableWidgetItem *> item = ui->tableWidget->findItems(input_name, Qt::MatchContains);
    for(int i=0;i<row_num;i++)
    {
        ui->tableWidget->setRowHidden(i,true);//隐藏

    }
    //判断符合条件索引是不是空
    if(!item.empty())
    {
        for(int i=0;i<item.count();i++)
        {
            ui->tableWidget->setRowHidden(item.at(i)->row(),false);

        }
    }
}

void MissionTableWidget::initial_table_item(quint8 opResult,QVector<QVector<QString>> array)
{
    ui->tableWidget->setRowCount(opResult);

    for(int i = 0;i < array.size();i++)
    {
        for(int j = 0;j < widget_column_header.size();j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(array[i][j]);
            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(i,j,item);
        }
    }
    for(int i=0;i<widget_column_header.size();i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i,100);
    }

}

quint8 MissionTableWidget::initial_widget(quint8 opResult,QVector<QVector<QString>> array)
{
    if(!widget_column_header.size()){
        qDebug() << "初始化失败，请检查是否使用set_widget_column_header来设置列头";
        return 0;
    }else
    {
        ui->tableWidget->setColumnCount(widget_column_header.size());
        ui->tableWidget->setHorizontalHeaderLabels(widget_column_header);

        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white;border:2px solid white}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white}");
        ui->tableWidget->setStyleSheet("font-size: 12pt;");
        ui->tableWidget->setAlternatingRowColors(true);

        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget->setRowHeight(0,40);
        ui->tableWidget->verticalHeader()->setVisible(0);

        initial_table_item(opResult,array);

        connect(ui->pushButton_2,&QPushButton::clicked,this,&MissionTableWidget::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&MissionTableWidget::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&MissionTableWidget::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&MissionTableWidget::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&MissionTableWidget::searchButton_slot);

        ui->tableWidget->setColumnHidden(23, true);
        ui->tableWidget->setColumnHidden(24, true);
        return 1;
    }

}

QByteArray MissionTableWidget::getInvert(QByteArray array)
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

QByteArray MissionTableWidget::PackInitialQuest(quint8 logo)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    //quint8 frame = 0x01;

    streao<< logo;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x95);
    sendByte.append(sendByteo);
    return sendByte;
}

void MissionTableWidget::sendInitialQuest(quint8 logo)
{
    QByteArray array = PackInitialQuest(logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
    qDebug() << "initial要求已发送";
}

QByteArray MissionTableWidget::PackEditInfo(QVector<QString> Array,quint8 column,quint8 logo)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    quint8 frame = 0x01;
    streao << frame << logo << column;

    for(int i = 0;i <= column;i++)
    {
        streao << Array[i];
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x92);
    sendByte.append(sendByteo);
    return sendByte;
}

void MissionTableWidget::sendEditInfo(QVector<QString> Array,quint8 logo)
{
    quint8 column = ui->tableWidget->columnCount();
    Array.resize(column+1);

    logo = 0x02;

    for(int i = 0;i < column;i++)
    {
        if(combobox_map.contains(i))
        {
            QComboBox *combobox;
            combobox = (QComboBox*)ui->tableWidget->cellWidget(currentRow,i);
            Array[i] = combobox->currentText();
        }
        else
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item = ui->tableWidget->item(currentRow,i);
            Array[i] = item->data(Qt::DisplayRole).toString();
        }
    }
    Array[column] = oldValue.at(primaryKeyIndex);

    QByteArray array = PackEditInfo(Array,column,logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
    qDebug() << "修改信息已发送";
}

QByteArray MissionTableWidget::PackDeleteInfo(QVector<QString> Array,quint8 column,quint8 logo)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    quint8 frame = 0x02;
    streao << frame << logo << column;

    streao << Array[0];

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x93);
    sendByte.append(sendByteo);
    return sendByte;
}

void MissionTableWidget::sendDeleteInfo(QVector<QString> Array,quint8 logo)
{
    quint8 column = ui->tableWidget->columnCount();
    logo = 0x02;
    currentRow = ui->tableWidget->currentRow();
    column = 1;
    Array.resize(column);

    Array[0] = ui->tableWidget->item(currentRow,primaryKeyIndex)->data(Qt::DisplayRole).toString();

    QByteArray array = PackDeleteInfo(Array,column,logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
    qDebug() << "删除信息已发送";
}
