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
#include <QFileDialog>
#include "customtableform.h"
#include "firstwindow.h"
#include "QAxObject"
#include "secondentity.h"

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

void customTableWidget::set_isShow(bool isShow)
{
    if(!isShow){
        ui->pushButton_6->hide();
        ui->pushButton_7->hide();
        ui->horizontalLayout->removeItem(ui->horizontalSpacer_2);
    }
}

void customTableWidget::initial_table_item()
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

void customTableWidget::editFinish()
{
    if(openFileIndex>=0){
        connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
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

void customTableWidget::addFinish()
{
    if(openFileIndex>=0){
        connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
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
            if(i==openFileIndex){
                item->setText(QDir::fromNativeSeparators(item->text()));
            }
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
            if(i==openFileIndex){
                item->setText(QDir::fromNativeSeparators(item->text()));
            }
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

void customTableWidget::importData()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile); // 设置对话框模式为选择现有文件

    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
            QString selectedFile = selectedFiles.first();
            qDebug() << "Selected file: " << selectedFile;
            readExcelAndPrintThirdRow(selectedFile);
        }
    }
}

void customTableWidget::exportData()
{

    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){

        std::vector<int> vecItemIndex;//保存选中行的索引
        QItemSelectionModel *selections = ui->tableWidget->selectionModel(); //返回当前的选择模式
        QModelIndexList selectedsList = selections->selectedIndexes(); //返回所有选定的模型项目索引列表

        for (int i = 0; i < selectedsList.count(); i++)
        {
            vecItemIndex.push_back(selectedsList.at(i).row());
        }
        std::sort(vecItemIndex.begin(), vecItemIndex.end());
        vecItemIndex.erase(std::unique(vecItemIndex.begin(), vecItemIndex.end()), vecItemIndex.end());
        for(int i=0;i<vecItemIndex.size();i++){
            qDebug() << vecItemIndex.at(i);


            CustomTableForm *form = new CustomTableForm();
            form->setPath(directoryPath);
            QStringList list;
            for(int j=0;j<ui->tableWidget->columnCount();j++){
                list<<ui->tableWidget->item(vecItemIndex.at(i),j)->text();
                qDebug() << vecItemIndex.at(i)<<j << ui->tableWidget->item(vecItemIndex.at(i),j)->text();
            }
            form->initialTableWidget(widget_column_header,list);
            form->exportExcel();
        }
    }
}

quint8 customTableWidget::initial_widget(){
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
            connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
        }

        connect(ui->pushButton_2,&QPushButton::clicked,this,&customTableWidget::addButton_slot);
        connect(ui->pushButton_4,&QPushButton::clicked,this,&customTableWidget::finishButton_slot);
        connect(ui->pushButton_5,&QPushButton::clicked,this,&customTableWidget::editButton_slot);
        connect(ui->pushButton_3,&QPushButton::clicked,this,&customTableWidget::deleteButton_slot);
        connect(ui->pushButton,&QPushButton::clicked,this,&customTableWidget::searchButton_slot);
        connect(ui->pushButton_6,&QPushButton::clicked,this,&customTableWidget::importData);
        connect(ui->pushButton_7,&QPushButton::clicked,this,&customTableWidget::exportData);
        return 1;
    }

}

void customTableWidget::addButton_slot()
{
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

void customTableWidget::finishButton_slot()
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

void customTableWidget::editButton_slot()
{
    if(openFileIndex>=0){
        disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&customTableWidget::cellDoubleClicked);
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
    if(input_name == ""){
        ui->label->setText(QString(""));
    }

}

void customTableWidget::cellDoubleClicked(int row, int column)
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


void customTableWidget::sendInfo_slot(quint16 port,quint8 logo,QHostAddress addr)
{
    QString databaseName;

    switch (logo) {
    case 0x00:
        databaseName = QString("usernew");
        break;
    case 0x01:
        databaseName = QString("stationnew");
        break;
    case 0x02:
        databaseName = QString("missionnew2");
        break;
    case 0x03:
        databaseName = QString("baseband");
        break;
    case 0x04:
        databaseName = QString("datasource");
        qDebug() <<1;
        break;
    default:
        break;
    }

    qDebug() <<2;
    QVector<QVector<QString>> Array;
    Array = selectInfo(databaseName);

    qDebug() <<3;
    QByteArray array = PackUserInfo(Array,logo);

    qDebug() <<4;
    udpsocket->writeDatagram(getInvert(array),addr,port);
}

QVector<QVector<QString>> customTableWidget::selectInfo(QString databaseName)
{
    QList<quint8> string_column_list;
    QSqlQuery query1(db);
    QSqlQuery query(db);
    QString qs1 = QString("SHOW COLUMNS FROM %1").arg(databaseName);
    QString qs = QString("select * from %1").arg(databaseName);
    query1.exec(qs1);
    query.exec(qs);
    QSqlRecord rec = query.record();
    quint8 row = query.size();
    quint8 column = query1.size();
    if(databaseName.compare(QString("usernew")) == 0)
    {
        column = 5;
        string_column_list << 0 << 1 << 2 << 3 << 4;
    }
    else if(databaseName.compare(QString("stationnew")) == 0)
    {
        string_column_list << 0 << 1 << 2 << 3 << 4 << 5;
    }
    else if(databaseName.compare(QString("missionnew2")) == 0)
    {
        string_column_list << 0 << 1 << 3 << 4 << 6 << 10 << 11 << 13 << 14 << 15
                           << 16 << 18 << 20 << 22 << 23 << 24 << 25 << 26;
    }

    QVector<QVector<QString>> array;
    //设置数组大小
    array.resize(row);
    for(int j=0;j<array.size();j++)
    {
        array[j].resize(column);
    }

    int rowNum = 0;
    QString columnName;
    while (query.next())
    {
        for(int i = 0;i < column;i++)
        {
            if(!string_column_list.contains(i) && query.value(i).isNull())
            {
                array[rowNum][i] = "";
            }
            else
            {
                columnName = query.value(i).toString();
                qDebug() << "columnName" << columnName;
                array[rowNum][i] = columnName;
            }

        }
        rowNum++;
    }
    return array;
}


QByteArray customTableWidget::PackUserInfo(QVector<QVector<QString>> array,quint8 logo)
{
    quint8 frame = 0x03;
    quint8 row = array.size();
    quint8 column;
    if(array.size()==0){
        column = 0;
    }else{
        column = array[0].size();
    }

    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    qDebug() << 12;
    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);
    streao << row << column << frame << logo;

    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < column;j++)
        {
            QByteArray arr;
            QDataStream data(&arr,QIODevice::WriteOnly);
            data.setVersion(QDataStream::Qt_5_1);
            data << array[i][j];
            sendByteo.append(arr);
        }
    }


    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x94);
    sendByte.append(sendByteo);
    return sendByte;
}

void customTableWidget::readExcelAndPrintThirdRow(const QString &filePath)
{
    QAxObject excel("Excel.Application"); // 创建 Excel 应用程序对象
    excel.setProperty("Visible", false);   // 设置 Excel 不可见

    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath);

    if (!workbook) {
        qDebug() << "Failed to open Excel file";
        return;
    }

    QAxObject *sheet = workbook->querySubObject("Worksheets(int)", 1); // 第一个工作表
    if (!sheet) {
        qDebug() << "Failed to get worksheet";
        workbook->dynamicCall("Close()");
        return;
    }

    QAxObject *usedRange = sheet->querySubObject("UsedRange");
    QAxObject *rows = usedRange->querySubObject("Rows");
    QAxObject *row = rows->querySubObject("Item(int)", 4); // 第三行

    SecondEntity *entity = new SecondEntity();
    entity->xuhao = row->querySubObject("Cells(int, int)", 1, 1)->property("Value").toString();
    entity->renwumingcheng = row->querySubObject("Cells(int, int)", 1, 2)->property("Value").toString();
    entity->xinghaochangjia = row->querySubObject("Cells(int, int)", 1, 3)->property("Value").toString();
    entity->daihao = row->querySubObject("Cells(int, int)", 1, 4)->property("Value").toString();
    entity->chulipingtai = row->querySubObject("Cells(int, int)", 1, 5)->property("Value").toString();
    entity->xianshipingtai = row->querySubObject("Cells(int, int)", 1, 6)->property("Value").toString();
    entity->zhuangtaibeizhu = row->querySubObject("Cells(int, int)", 1, 7)->property("Value").toString();
    entity->jiesuanchengxu = row->querySubObject("Cells(int, int)", 1, 8)->property("Value").toString();
    entity->setup = row->querySubObject("Cells(int, int)", 1, 9)->property("Value").toString();
    entity->yingjianjiami = row->querySubObject("Cells(int, int)", 1, 10)->property("Value").toString();
    entity->jimixinxibeizhu = row->querySubObject("Cells(int, int)", 1, 11)->property("Value").toString();
    entity->renwuhong = row->querySubObject("Cells(int, int)", 1, 12)->property("Value").toString();
    entity->xianshihuamianbanben = row->querySubObject("Cells(int, int)", 1, 13)->property("Value").toString();
    entity->jiesuanruanjian = row->querySubObject("Cells(int, int)", 1, 14)->property("Value").toString();
    entity->beizhu = row->querySubObject("Cells(int, int)", 1, 15)->property("Value").toString();
    entity->banbengengxinshijian = row->querySubObject("Cells(int, int)", 1, 16)->property("Value").toString();
    entity->bianzhiren = row->querySubObject("Cells(int, int)", 1, 17)->property("Value").toString();

    int isInsert = SecondEntity::insertInfo(entity);
    if(isInsert){

        QMessageBox::information(this,"导入提示","导入成功");
        initial_table_item();
    }else{
        QMessageBox::information(this,"导入提示","导入失败");
    }

    // 释放对象
    delete row;
    delete usedRange;
    delete sheet;
    workbook->dynamicCall("Close()");
    delete workbook;
    delete workbooks;

    excel.dynamicCall("Quit()");
}


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
