#include "datageshanmanage.h"
#include "ui_datageshanmanage.h"
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
#include <QFileDialog>
#include "advancedsinglesearch.h"
#include "advancesearch.h"
#include "config/configinfo.h"

DataGeshanManage::DataGeshanManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataGeshanManage)
{
    ui->setupUi(this);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&DataGeshanManage::advanceCheckSlot);
}

DataGeshanManage::~DataGeshanManage()
{
    delete ui;
}


void DataGeshanManage::set_widget_column_header(QStringList header)
{
    widget_column_header = header;
}

void DataGeshanManage::set_string_column_number(QList<quint8> number)
{
    string_column_number = number;
}

void DataGeshanManage::set_combobox_map(QMap<quint8, QStringList> map)
{
    combobox_map = map;
}

void DataGeshanManage::set_database(QString baseName)
{
    dataBaseName = baseName;
}

void DataGeshanManage::set_primaryKeyIndex(quint8 index)
{
    primaryKeyIndex = index;
}

void DataGeshanManage::set_fileIndex(quint8 index)
{
    openFileIndex = index;
}

void DataGeshanManage::set_codeIndex(quint8 code)
{
    missionCode = code;
}

void DataGeshanManage::set_resizeMode(QHeaderView::ResizeMode mode)
{
    resizeMode = mode;
}

void DataGeshanManage::set_aotuTimeColumn(int column)
{
    timeColumn = column;
    qDebug() << "设置时间1";
}

void DataGeshanManage::initial_table_item()
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(db);
    QString qs = QString("select * from %1").arg(dataBaseName);
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());

    int lineNum = 0;
    while (query.next())
    {
        for(int i=0;i<widget_column_header.size();i++){
            int columnNameIndex = rec.indexOf(widget_column_header.at(i));
            QString columnName = query.value(columnNameIndex).toString();
            QTableWidgetItem *item = new QTableWidgetItem(columnName);
//            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(lineNum,i,item);
        }
        lineNum++;
    }
}

void DataGeshanManage::editFinish()
{
    if(openFileIndex>=0){
        connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataGeshanManage::cellDoubleClicked);
    }
    QSqlQuery query(db);
    QString qs = QString("update %1 set ").arg(dataBaseName);
    qDebug() << "拼接后的字符串" << qs;
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item = ui->tableWidget->item(currentRow,i);

        if(combobox_map.contains(i)){
            QComboBox *combobox;
            combobox = (QComboBox*)ui->tableWidget->cellWidget(currentRow,i);
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),combobox->currentText());
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),combobox->currentText());
                qs.insert(qs.size(),",");
            }
        }else if(item!=nullptr){
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),item->text());
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),item->text());
                qs.insert(qs.size(),",");
            }
        }else{
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),widget_column_header.at(i));
                qs.insert(qs.size(),"=");
                qs.insert(qs.size(),",");
            }
        }
    }
    qs.chop(1);
    if(string_column_number.contains(primaryKeyIndex)){
        qs.insert(qs.size()," where ");
        qs.insert(qs.size(),widget_column_header.at(primaryKeyIndex));
        qs.insert(qs.size()," = ");
        qs.insert(qs.size(),"'");
        qs.insert(qs.size(),oldValue.at(primaryKeyIndex));
        qs.insert(qs.size(),"'");
    }else{
        qs.insert(qs.size()," where ");
        qs.insert(qs.size(),widget_column_header.at(primaryKeyIndex));
        qs.insert(qs.size()," = ");
        qs.insert(qs.size(),oldValue.at(primaryKeyIndex));
    }
    qDebug() << "拼接后的字符串" << qs;

    bool ok = query.exec(qs);
    if(ok){
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
        QMessageBox::information(this,"更改提示",query.lastError().text());
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

void DataGeshanManage::addFinish()
{
    if(openFileIndex>=0){
        connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataGeshanManage::cellDoubleClicked);
    }
    QSqlQuery query(db);
    QString qs = QString("insert into %1 (").arg(dataBaseName);
    for(int i=0;i<widget_column_header.size();i++){
        qs.insert(qs.size(),widget_column_header.at(i));
        qs.insert(qs.size(),",");
    }
    qs.chop(1);
    qs.insert(qs.size(),")");
    qs.insert(qs.size(),"values(");
    qDebug() << "拼接后的字符串" << qs;
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item = ui->tableWidget->item((ui->tableWidget->rowCount()-1),i);
        qDebug() << "i" <<i<< "timeColumn"<<timeColumn;

        if(combobox_map.contains(i)){
            QComboBox *combobox;
            combobox = (QComboBox*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),i);
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),combobox->currentText());
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),combobox->currentText());
                qs.insert(qs.size(),",");
            }
            qDebug() << "ziduan" << combobox->currentText();
        }else if(item!=nullptr){
            if(timeColumn==i&&item->text()==""){
                qDebug() << "满足条件1";
                qs.insert(qs.size(),"'");
                recentTime = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh时mm分");
                qs.insert(qs.size(),recentTime);
                qs.insert(qs.size(),"',");
            }else if(string_column_number.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),item->text());
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),item->text());
                if(item->text()==""){
                    qs.insert(qs.size(),"NULL,");
                }else{
                    qs.insert(qs.size(),",");
                }

            }
            qDebug() << "ziduan" << item->text();
        }else{
            if(timeColumn==i){
                qDebug() << "满足条件2";
                qs.insert(qs.size(),"'");
                recentTime = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh时mm分");
                qs.insert(qs.size(),recentTime);
                qs.insert(qs.size(),"',");
            }else if(string_column_number.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),"NULL,");
            }
            qDebug() << "字段空" ;
        }

    }
    qs.chop(1);
    qs.insert(qs.size(),")");
    qDebug() << "拼接后的字符串" << qs;
    bool ok = query.exec(qs);
    if(ok){
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
                color = new QColor(243,243,243);
            }else{
                color = new QColor(230,230,230);
            }
            item->setBackgroundColor(*color);
        }
    }else{
        QMessageBox::information(this,"添加提示",query.lastError().text());
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
    }

    tableWidget_status = TableWidgetCompleteFlag;
}

quint8 DataGeshanManage::initial_widget(){
    if(!widget_column_header.size()){
        qDebug() << "初始化失败，请检查是否使用set_widget_column_header来设置列头";
        return 0;
    }else if(!dataBaseName.size()){
        qDebug() << "初始化失败，请检查是否使用set_database来设置数据库名称";
        return 0;
    }{
        ui->tableWidget->setColumnCount(widget_column_header.size());
        ui->tableWidget->setHorizontalHeaderLabels(widget_column_header);

        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240, 241, 245),stop:0.9 rgb(220, 227, 235));font-size: 12pt;color:black;border:none;}");
        ui->tableWidget->setStyleSheet("font-size: 12pt;");
    //    ui->tableWidget->setAlternatingRowColors(true);
        QPalette pal = ui->tableWidget->palette();
        pal.setColor(QPalette::Base, QColor(243, 243, 243));
        pal.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
        ui->tableWidget->setPalette(pal);
        ui->tableWidget->setAlternatingRowColors(true);
        ui->tableWidget->viewport()->update();

        ui->tableWidget->horizontalHeader()->setSectionResizeMode(resizeMode);
        ui->tableWidget->setRowHeight(0,40);
        ui->tableWidget->verticalHeader()->setVisible(0);

        initial_table_item();

        if(openFileIndex>=0){
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataGeshanManage::cellDoubleClicked);
        }

        connect(ui->pushButton_2,&QPushButton::clicked,this,&DataGeshanManage::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&DataGeshanManage::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&DataGeshanManage::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&DataGeshanManage::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&DataGeshanManage::searchButton_slot);
        connect(ui->pushButton_6,&QPushButton::clicked,this,&DataGeshanManage::download_slot);
        return 1;
    }

}

void DataGeshanManage::addButton_slot()
{
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataGeshanManage::cellDoubleClicked);
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

void DataGeshanManage::deleteButton_slot()
{
    qDebug() << "current row" << ui->tableWidget->currentRow();
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    QString str("是否确认删除");
    str.append((ui->tableWidget->item(ui->tableWidget->currentRow(),primaryKeyIndex))->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes){
        QSqlQuery query(db);
        QString qs = QString("delete from %1 where ").arg(dataBaseName);
        qs.insert(qs.size(),widget_column_header.at(primaryKeyIndex));
        qs.insert(qs.size()," = ");
        if(string_column_number.contains(primaryKeyIndex)){
            qs.insert(qs.size(),"'");
            qs.insert(qs.size(),ui->tableWidget->item(ui->tableWidget->currentRow(),primaryKeyIndex)->text());
            qs.insert(qs.size(),"'");
        }else{
            qs.insert(qs.size(),ui->tableWidget->item(ui->tableWidget->currentRow(),primaryKeyIndex)->text());
        }
        bool ok = query.exec(qs);

        if(ok){
            QMessageBox::information(this,"删除提示","删除成功");
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }else{
            QMessageBox::information(this,"删除提示",query.lastError().text());
        }
    }
}

void DataGeshanManage::finishButton_slot()
{
    switch (tableWidget_status) {
    case TableWidgetAddFlag:
        addFinish();
        break;
    case TableWidgetEditFlag:
        editFinish();
        break;
    default:
        break;
    }

}

void DataGeshanManage::editButton_slot()
{
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&DataGeshanManage::cellDoubleClicked);
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

void DataGeshanManage::searchButton_slot()
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
        if(ui->lineEdit->text()!=""){
            for(int i=0;i<item.count();i++)
            {
                ui->tableWidget->setRowHidden(item.at(i)->row(),false);
                rowhide++;
                ui->label->setText(QString("查询结果:%1项").arg(QString::number(item.count())));

            }

        }else{
            initial_table_item();
        }
    }

}

void DataGeshanManage::download_slot()
{
    QString filepath = QFileDialog::getOpenFileName(this,"open","../");
    QFileInfo info(filepath);

    QString codestr = ConfigInfo::datFilePath;

    QString dateDir = codestr+QString(QDateTime::currentDateTime().toString("/yyyy年MM月dd日"));
    QDir dir2;
    if (!dir2.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg("数据格栅");
    QDir dir3;
    if (!dir3.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg(info.fileName());
//    QDir dir4;
//    if (!dir4.mkdir(dateDir)) {
//        qDebug() << "Failed to create folder";
//    }else{
//        qDebug() << "Folder created successfully";
//    }

    bool ok = QFile::copy(filepath,dateDir);
    if(ok){
        QMessageBox::information(this,"提示信息","导入成功");
        QSqlQuery query(db);
        QString qs = QString("insert into  `%1` (`格栅路径`,`型号`) values('%2','无')").arg(dataBaseName).arg(dateDir);
        qDebug() << qs;
        query.exec(qs);
        qDebug() <<query.lastError().text();
        initial_table_item();
    }else{
        qDebug() << "旧的路径" << filepath << "新的路径" << dateDir;
        QMessageBox::information(this,"提示信息","导入失败");
    }
}

void DataGeshanManage::cellDoubleClicked(int row, int column)
{
    if(openFileIndex==column){
        QString exe = ui->tableWidget->item(row,openFileIndex)->text().toUtf8();
        QDesktopServices::openUrl(QUrl(QDir::fromNativeSeparators(exe)));
    }
    if(missionCode==column){
        MissionNewReview *p = new MissionNewReview();
        p->setItemByCode(ui->tableWidget->item(row,column)->text());
        p->show();
    }
}

void DataGeshanManage::advanceCheckSlot()
{
    AdvanceSearch *advanceSearch = new AdvanceSearch();
    QStringList list;
    list << "型号" << "平台" << "格栅路径" << "格栅版本";
    QList<quint8> stringNumList;
    stringNumList << 0 << 1 << 2 << 3 << 7 << 8 << 9;
    advanceSearch->setStringNumList(stringNumList);
    advanceSearch->setTableName("datageshan");
    advanceSearch->setList(list);
    advanceSearch->show();
    connect(advanceSearch,&AdvanceSearch::sendResultString,this,&DataGeshanManage::getAdvanceResultString);
}

void DataGeshanManage::getAdvanceResultString(QString resultString)
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(db);
    QString qs = resultString;
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());

    int lineNum = 0;
    while (query.next())
    {
        for(int i=0;i<widget_column_header.size();i++){
            int columnNameIndex = rec.indexOf(widget_column_header.at(i));
            QString columnName = query.value(columnNameIndex).toString();
            QTableWidgetItem *item = new QTableWidgetItem(columnName);
//            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(lineNum,i,item);
        }
        lineNum++;
    }
}
