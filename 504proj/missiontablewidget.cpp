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

void MissionTableWidget::initial_table_item()
{
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
    for(int i=0;i<widget_column_header.size();i++){
        ui->tableWidget->horizontalHeader()->resizeSection(i,100);
    }
}

void MissionTableWidget::editFinish()
{
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
                color = new QColor(255,255,255);
            }else{
                color = new QColor(245,245,245);
            }
            item->setBackgroundColor(*color);
        }
    }

    tableWidget_status = TableWidgetCompleteFlag;
    oldValue.clear();
    currentRow = -1;
}

void MissionTableWidget::addFinish()
{
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
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),item->text());
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),item->text());
                qs.insert(qs.size(),",");
            }
            qDebug() << "ziduan" << item->text();
        }else{
            if(string_column_number.contains(i)){
                qs.insert(qs.size(),"'");
                qs.insert(qs.size(),"',");
            }else{
                qs.insert(qs.size(),",");
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
        }
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            QTableWidgetItem *item = ui->tableWidget->item(ui->tableWidget->rowCount()-1,i);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            QColor *color;
            if((ui->tableWidget->rowCount()-1)%2==0){
                color = new QColor(255,255,255);
            }else{
                color = new QColor(245,245,245);
            }
            item->setBackgroundColor(*color);
        }
    }else{
        QMessageBox::information(this,"添加提示",query.lastError().text());
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
    }

    tableWidget_status = TableWidgetCompleteFlag;
}

quint8 MissionTableWidget::initial_widget(){
    if(!widget_column_header.size()){
        qDebug() << "初始化失败，请检查是否使用set_widget_column_header来设置列头";
        return 0;
    }else if(!dataBaseName.size()){
        qDebug() << "初始化失败，请检查是否使用set_database来设置数据库名称";
        return 0;
    }{
        ui->tableWidget->setColumnCount(widget_column_header.size());
        ui->tableWidget->setHorizontalHeaderLabels(widget_column_header);

        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white;border:2px solid white}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(0, 105, 173);font-size: 12pt;color:white}");
        ui->tableWidget->setStyleSheet("font-size: 12pt;");
        ui->tableWidget->setAlternatingRowColors(true);

        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget->setRowHeight(0,40);
        ui->tableWidget->verticalHeader()->setVisible(0);

        initial_table_item();

        connect(ui->pushButton_2,&QPushButton::clicked,this,&MissionTableWidget::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&MissionTableWidget::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&MissionTableWidget::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&MissionTableWidget::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&MissionTableWidget::searchButton_slot);
        return 1;
    }

}

void MissionTableWidget::addButton_slot()
{
    MissionNewInsert *p = new MissionNewInsert();
    connect(p,&MissionNewInsert::refresh_tableWidget,this,&MissionTableWidget::initial_table_item);
    p->show();
}

void MissionTableWidget::deleteButton_slot()
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

void MissionTableWidget::finishButton_slot()
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

void MissionTableWidget::editButton_slot()
{
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
