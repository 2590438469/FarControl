#include "customtablewidget.h"
#include "ui_customtablewidget.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QSqlError>
#include <QDesktopServices>
#include <QDir>
#include <QTextCodec>
#include <QDateTime>
#include "missionnewreview.h"
#include "missionsendwidget.h"
#include "ui_missionsendwidget.h"
#include "basicinfoedit.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"
#include <QTimeEdit>
#include <QMessageBox>
#include <QPushButton>
#include "stationselect.h"
#include "firstwindow.h"
#include "config/configinfo.h"

customTableWidget::customTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customTableWidget)
{
    ui->setupUi(this);
}

customTableWidget::~customTableWidget()
{
    delete ui;
}

void customTableWidget::set_widget_column_header(QStringList header)
{
    widget_column_header = header;
}

void customTableWidget::set_string_column_number(QList<quint8> number)
{
    string_column_number = number;
}

void customTableWidget::set_combobox_map(QMap<quint8, QStringList> map)
{
    combobox_map = map;
}

void customTableWidget::set_database(QString baseName)
{
    dataBaseName = baseName;
}

void customTableWidget::set_primaryKeyIndex(quint8 index)
{
    primaryKeyIndex = index;
}

void customTableWidget::set_fileIndex(quint8 index)
{
    openFileIndex = index;
}

void customTableWidget::set_codeIndex(quint8 code)
{
    missionCode = code;
}

void customTableWidget::set_resizeMode(QHeaderView::ResizeMode mode)
{
    resizeMode = mode;
}

void customTableWidget::set_aotuTimeColumn(int column)
{
    timeColumn = column;
    qDebug() << "设置时间";
}

void customTableWidget::initial_table_item()
{
    QSqlQuery query(db);
    QString qs = QString("select * from %1").arg(dataBaseName);
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());
    int lineNum = 0;
    while (query.next())
    {
        for(int i=0;i<widget_column_header.size();i++)
        {
            int columnNameIndex = rec.indexOf(widget_column_header.at(i));
            QString columnName = query.value(columnNameIndex).toString();//   columnName
            QTableWidgetItem *item = new QTableWidgetItem(columnName);
            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(lineNum,i,item);
        }
        lineNum++;
    }
}

quint8 customTableWidget::initial_widget(){
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

        initial_table_item();

        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }

        connect(ui->pushButton_2,&QPushButton::clicked,this,&customTableWidget::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&customTableWidget::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&customTableWidget::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&customTableWidget::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&customTableWidget::searchButton_slot);
        connect(ui->pushButton_8,&QPushButton::clicked,this,&customTableWidget::backButton_slot);
        return 1;
    }

}

void customTableWidget::initial_table_item(quint8 opResult,QVector<QVector<QString>> array)
{
      ui->tableWidget->setRowCount(opResult);
//    QVector<QVector<QString>> array;
//    //设置数组大小
//    array.resize(opResult);
//    for(int j=0;j<array.size();j++)
//    {
//        array[j].resize(widget_column_header.size());
//    }

//    QList<receieveData::UserInfo>::const_iterator it;
//    int i;
//    for (it = userList.constBegin(),i = 0; it != userList.constEnd(); ++it,i++)
//    {
//        const receieveData::UserInfo& user = *it;
//        qDebug() << "username:" << user.username << "realname:" << user.realname << "realname:" << user.realname;

//        array[i][0] = user.username;
//        array[i][1] = user.realname;
//        array[i][2] = user.telenumber;
//        array[i][3] = user.role;
//        array[i][4] = user.status;
//    }
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

}

void customTableWidget::editFinish(quint8 opResult)
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

void customTableWidget::addFinish(quint8 opResult)
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

void customTableWidget::deleteFinish(quint8 opResult)
{
    if(opResult){
        QMessageBox::information(this,"删除提示","删除成功");
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }else{
        QMessageBox::information(this,"删除提示","删除失败");
    }
    tableWidget_status = TableWidgetCompleteFlag;
}

quint8 customTableWidget::initial_widget(quint8 opResult,QVector<QVector<QString>> array)
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

        initial_table_item(opResult,array);

        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }

        connect(ui->pushButton_2,&QPushButton::clicked,this,&customTableWidget::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&customTableWidget::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&customTableWidget::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&customTableWidget::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&customTableWidget::searchButton_slot);       
        connect(ui->pushButton_8,&QPushButton::clicked,this,&customTableWidget::backButton_slot);
        return 1;
    }

}

void customTableWidget::addButton_slot()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
    }

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

        tableWidget_status = TableWidgetAddFlag;
    }else{
        QMessageBox::information(this,"提示","请完成当前操作");
    }
}

void customTableWidget::deleteButton_slot()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
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

void customTableWidget::finishButton_slot()
{
    QVector<QString> Array;
    quint8 logo;
    switch (tableWidget_status) {
    case TableWidgetAddFlag:
        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }
        sendAddInfo(Array,logo);
        break;
    case TableWidgetEditFlag:
        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }
        sendEditInfo(Array,logo);
        break;
    case TableWidgetDeleteFlag:
        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }
        sendDeleteInfo(Array,logo);
        break;
    default:
        break;
    }

}

void customTableWidget::editButton_slot()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return ;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
    }
    currentRow = ui->tableWidget->currentRow();

    if(ui->tableWidget->currentRow() < 0){
        QMessageBox::information(this,"编辑提示","请选择一项进行编辑操作");
        tableWidget_status = TableWidgetCompleteFlag;
    }else{
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            oldValue.append(ui->tableWidget->item(currentRow,i)->text());
        }
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


void customTableWidget::searchButton_slot()
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

void customTableWidget::backButton_slot()
{
    qDebug() << "撤销";
    if(tableWidget_status == TableWidgetAddFlag){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
        tableWidget_status = TableWidgetCompleteFlag;
    }
    currentRow = -1;
}

void customTableWidget::cellDoubleClicked(int row, int column)
{
    if(openFileIndex==column){
        QString exe = ui->tableWidget->item(row,openFileIndex)->text().toUtf8();
        QDesktopServices::openUrl(QUrl(QDir::fromNativeSeparators(exe)));
    }
    if(missionCode==column){
        MissionNewReview *p = new MissionNewReview();
        p->setItemByCode(ui->tableWidget->item(row,column)->text(),"未加载");
        p->show();
    }
}

QByteArray customTableWidget::PackAddInfo(QVector<QString> Array,quint8 column,quint8 logo)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    quint8 frame = 0x00;
    streao << frame << logo << column;

    for(int i = 0;i < column;i++)
    {
        streao << Array[i];
    }

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x90);
    sendByte.append(sendByteo);
    return sendByte;
}

void customTableWidget::sendAddInfo(QVector<QString> Array,quint8 logo)
{
    currentRow = ui->tableWidget->currentRow();
    quint8 column = ui->tableWidget->columnCount();
    Array.resize(column);

    switch (column) {
    case 5:
        logo = 0x00;
        break;
    case 6:
        logo = 0x01;
        break;
    case 4:
        logo = 0x03;
        break;
    case 2:
        logo = 0x04;
        break;
    default:
        break;
    }

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

    QByteArray array = PackAddInfo(Array,column,logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
}

QByteArray customTableWidget::PackEditInfo(QVector<QString> Array,quint8 column,quint8 logo)
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

void customTableWidget::sendEditInfo(QVector<QString> Array,quint8 logo)
{
    quint8 column = ui->tableWidget->columnCount();
    Array.resize(column+1);

    switch (column) {
    case 5:
        logo = 0x00;
        break;
    case 6:
        logo = 0x01;
        break;
    case 4:
        logo = 0x03;
        break;
    case 2:
        logo = 0x04;
        break;
    default:
        break;
    }

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
}

QByteArray customTableWidget::PackDeleteInfo(QVector<QString> Array,quint8 column,quint8 logo)
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

void customTableWidget::sendDeleteInfo(QVector<QString> Array,quint8 logo)
{
    quint8 column = ui->tableWidget->columnCount();
    switch (column) {
    case 5:
        logo = 0x00;
        break;
    case 6:
        logo = 0x01;
        break;
    case 4:
        logo = 0x03;
        break;
    case 2:
        logo = 0x04;
        break;
    default:
        break;
    }
    currentRow = ui->tableWidget->currentRow();
    column = 1;
    Array.resize(column);

    Array[0] = ui->tableWidget->item(currentRow,primaryKeyIndex)->data(Qt::DisplayRole).toString();

    QByteArray array = PackDeleteInfo(Array,column,logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
}

//QByteArray customTableWidget::PackEditInfo(UserInfo user)
//{
//    QByteArray sendByte;
//    QDataStream strea(&sendByte,QIODevice::WriteOnly);
//    strea.setVersion(QDataStream::Qt_5_1);

//    QByteArray sendByteo;
//    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
//    streao.setVersion(QDataStream::Qt_5_1);

//    streao<< user.username << user.realname << user.telenumber
//         << user.role << user.status << user.oldusername << user.frame;

//    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x92);
//    sendByte.append(sendByteo);
//    return sendByte;
//}

//void customTableWidget::sendEditInfo(UserInfo user)
//{
//    currentRow = ui->tableWidget->currentRow();
//    user.username = ui->tableWidget->item(currentRow,0)->data(Qt::DisplayRole).toString();
//    user.realname = ui->tableWidget->item(currentRow,1)->data(Qt::DisplayRole).toString();
//    user.telenumber = ui->tableWidget->item(currentRow,2)->data(Qt::DisplayRole).toString();

//    QComboBox *combobox1;
//    QComboBox *combobox2;
//    combobox1 = (QComboBox*)ui->tableWidget->cellWidget(currentRow,3);
//    combobox2 = (QComboBox*)ui->tableWidget->cellWidget(currentRow,4);

//    user.role = combobox1->currentText();
//    user.status = combobox2->currentText();
//    user.frame = 0x01;

//    qDebug() << user.username;
//    qDebug() << user.realname;
//    qDebug() << user.telenumber;
//    qDebug() << user.role;
//    qDebug() << user.status;
//    user.oldusername = oldValue.at(primaryKeyIndex);

//    QByteArray array = PackEditInfo(user);
//    QHostAddress addre;
//    addre.setAddress("127.0.0.1");
//    udpsocket->writeDatagram(getInvert(array),addre,9001);
//}

//QByteArray customTableWidget::PackDeleteInfo(UserInfo user)
//{
//    QByteArray sendByte;
//    QDataStream strea(&sendByte,QIODevice::WriteOnly);
//    strea.setVersion(QDataStream::Qt_5_1);

//    QByteArray sendByteo;
//    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
//    streao.setVersion(QDataStream::Qt_5_1);

//    streao<< user.username << user.frame;

//    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x93);
//    sendByte.append(sendByteo);
//    return sendByte;
//}

//void customTableWidget::sendDeleteInfo(UserInfo user)
//{
//    currentRow = ui->tableWidget->currentRow();
//    user.username = ui->tableWidget->item(currentRow,0)->data(Qt::DisplayRole).toString();
//    user.frame = 0x02;

//    qDebug() << user.username;
//    QByteArray array = PackDeleteInfo(user);
//    QHostAddress addre;
//    addre.setAddress("127.0.0.1");
//    udpsocket->writeDatagram(getInvert(array),addre,9001);
//}

QByteArray customTableWidget::getInvert(QByteArray array)
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

QByteArray customTableWidget::PackInitialQuest(quint8 logo)
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

void customTableWidget::sendInitialQuest(quint8 logo)
{
    QByteArray array = PackInitialQuest(logo);
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,ConfigInfo::centerUdpPort);
    qDebug() << "initial要求已发送";
}


void customTableWidget::set_isShow(bool isShow)
{
    if(!isShow){
        ui->pushButton_6->hide();
        ui->pushButton_7->hide();
        ui->horizontalLayout->removeItem(ui->horizontalSpacer_2);
    }
}

void customTableWidget::set_isJidai(bool isJidai)
{
    this->isJidai = isJidai;
}

