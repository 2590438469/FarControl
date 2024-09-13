#include "missionsendwidget.h"
#include "ui_missionsendwidget.h"
#include "basicinfoedit.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"
#include <QTimeEdit>
#include <QMessageBox>
#include <QSqlError>
#include <QPushButton>
#include "stationselect.h"
#include "firstwindow.h"
#include "missionnewreview.h"
#include "stationshowmulty.h"
#include "firstwindow.h"
#include "agreement/agreement.h"
#include "config/configinfo.h"
#include "advancesearch.h"
#include "util/bytemethod.h"

QMap<QString,QStringList> unsendStationList;

MissionSendWidget::MissionSendWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionSendWidget)
{
    ui->setupUi(this);
    initial_widgetHeader();
    initial_slots();
//    initial_table_item();
    initial_basic_info();
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&MissionSendWidget::doubleClick);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&MissionSendWidget::deleteButton);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&MissionSendWidget::editButtonSlot);
    int headerTotalSize = ui->tableWidget->horizontalHeader()->length() + ui->tableWidget->frameWidth() * 2;
    tablewidgetLenth = headerTotalSize;

    connect(ui->pushButton_9,&QPushButton::clicked,this,[=](){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendCheckAllFileCatalog(AgreeMent::GRILLE)),*addr,ConfigInfo::centerUdpPort);
        qDebug() << "打印grille" << grilleWidget->fileType;
        grilleWidget->show();
    });
    connect(ui->pushButton_8,&QPushButton::clicked,this,[=](){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(getInvert(AgreeMent::sendCheckAllFileCatalog(AgreeMent::DISPLAY)),*addr,ConfigInfo::centerUdpPort);
        qDebug() << "打印display" << grilleWidget->fileType;
        displayWidget->show();
    });
    connect(ui->pushButton_10,&QPushButton::clicked,this,[=](){
        AdvanceSearch *widget = new AdvanceSearch();
        widget->show();
    });
    connect(ui->pushButton_11,&QPushButton::clicked,this,[=](){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendAllMissionRequest()),*addr,ConfigInfo::centerUdpPort);
    });
//    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->tableWidget->setColumnHidden(7, true);
    ui->tableWidget->setColumnHidden(9, true);
    connect(ui->pushButton_12,&QPushButton::clicked,[=](){
        qDebug() << "撤销";
        if(tableWidget_status == TableWidgetAddFlag){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
            tableWidget_status = TableWidgetCompleteFlag;
            currentRow = -1;
        }
    });
}

MissionSendWidget::~MissionSendWidget()
{
    delete ui;
}

void MissionSendWidget::editFinish()
{
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&MissionSendWidget::doubleClick);
    QTimeEdit *timeeditd;
    timeeditd = (QTimeEdit*)ui->tableWidget->cellWidget(currentRow,1);
    QString timeeditdstr = timeeditd->dateTime().toString("hh:mm");
    ui->tableWidget->removeCellWidget(currentRow,1);
    QTimeEdit *timeeditsta;
    timeeditsta = (QTimeEdit*)ui->tableWidget->cellWidget(currentRow,2);
    QString timeeditstastr = timeeditsta->dateTime().toString("hh:mm");
    ui->tableWidget->removeCellWidget(currentRow,2);
    QTimeEdit *timeeditsto;
    timeeditsto = (QTimeEdit*)ui->tableWidget->cellWidget(currentRow,3);
    QString timeeditstostr = timeeditsto->dateTime().toString("hh:mm");
    ui->tableWidget->removeCellWidget(currentRow,3);
    QComboBox *combobox;
    combobox = (QComboBox*)ui->tableWidget->cellWidget(currentRow,12);
    QString missioncode = combobox->currentText();
    ui->tableWidget->removeCellWidget(currentRow,12);

    QTableWidgetItem *tablewidget = new QTableWidgetItem(timeeditdstr);
    ui->tableWidget->setItem(currentRow,1,tablewidget);

    tablewidget = new QTableWidgetItem(timeeditstastr);
    ui->tableWidget->setItem(currentRow,2,tablewidget);

    tablewidget = new QTableWidgetItem(timeeditstostr);
    ui->tableWidget->setItem(currentRow,3,tablewidget);

    tablewidget = new QTableWidgetItem(missioncode);
    ui->tableWidget->setItem(currentRow,12,tablewidget);

    QMessageBox::information(this,"修改提示","修改成功");
    QTableWidgetItem *item;

    for(int i=0;i<ui->tableWidget->columnCount();i++){
        if(i!=11&&i!=14&&i!=15){
            item = ui->tableWidget->item(currentRow,i);
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            QColor *color;
            if((currentRow)%2==0){
                color = new QColor(243,243,243);
            }else{
                color = new QColor(230,230,230);
            }
            item->setBackgroundColor(*color);
        }

    }
    QPushButton *pushButton = new QPushButton();
    pushButton->setText("发 送");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "color: darkgray;"
                              "}");
    QFont *font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
    ui->tableWidget->setCellWidget(currentRow,14,pushButton);

    pushButton = new QPushButton();
    pushButton->setText("中 止");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "color: darkgray;"
                              "}");
    pushButton->setEnabled(false);
    font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
    ui->tableWidget->setCellWidget(currentRow,15,pushButton);

    pushButton = new QPushButton();
    pushButton->setText("查看遥测站");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;"
                              "padding: 10px;"
                              "color: rgb(100, 100, 100);"
                              "}");
    font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
    ui->tableWidget->setCellWidget(currentRow,11,pushButton);

    tableWidget_status = TableWidgetCompleteFlag;
}

void MissionSendWidget::addFinish()
{
    if(ui->tableWidget->item((ui->tableWidget->rowCount()-1),0)->text()==""){
        QMessageBox::information(this,"提示信息","未填任务代号");
        return ;
    }
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&MissionSendWidget::doubleClick);
    QComboBox *comboboxTem;
    comboboxTem = (QComboBox*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),12);
    QTimeEdit *timeEditTem;
    timeEditTem = (QTimeEdit*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),1);
    QTimeEdit *timeEditTem2;
    timeEditTem2 = (QTimeEdit*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),2);
    QTimeEdit *timeEditTem3;
    timeEditTem3 = (QTimeEdit*)ui->tableWidget->cellWidget((ui->tableWidget->rowCount()-1),3);


    QMessageBox::information(this,"添加提示","添加成功");
    QTableWidgetItem *item;
    item = new QTableWidgetItem();
    item->setText(timeEditTem->dateTime().toString("hh:mm"));
    ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,1);
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),1,item);
    item = new QTableWidgetItem();
    item->setText(timeEditTem2->dateTime().toString("hh:mm"));
    ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,2);
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),2,item);
    item = new QTableWidgetItem();
    item->setText(timeEditTem3->dateTime().toString("hh:mm"));
    ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,3);
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),3,item);
    item = new QTableWidgetItem();
    item->setText(comboboxTem->currentText());
    ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,12);
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),12,item);

    for(int i=0;i<ui->tableWidget->columnCount();i++){
        item = ui->tableWidget->item((ui->tableWidget->rowCount()-1),i);
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
    QPushButton *pushButton = new QPushButton();
    pushButton->setText("发 送");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "color: darkgray;"
                              "}");
    QFont *font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,14,pushButton);

    pushButton = new QPushButton();
    pushButton->setText("中 止");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "color: darkgray;"
                              "}");
    pushButton->setEnabled(false);
    font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,15,pushButton);

    pushButton = new QPushButton();
    pushButton->setText("查看遥测站");
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;"
                              "padding: 10px;"
                              "color: rgb(100, 100, 100);"
                              "}");
    font = new QFont();
    font->setPointSize(12);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,11,pushButton);

    tableWidget_status = TableWidgetCompleteFlag;
}

void MissionSendWidget::initial_table_item()
{
    ui->tableWidget->setRowCount(0);
    QSqlQuery query(db);
    QString qs = QString("select * from `missionsend`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    ui->tableWidget->setRowCount(query.size());

    int lineNum = 0;
    while (query.next())
    {
        for(int i=0;i<ui->tableWidget->columnCount()-1;i++){
            int columnNameIndex = i;
            QString columnName = query.value(columnNameIndex).toString();
            QTableWidgetItem *item = new QTableWidgetItem(columnName);
//            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsEnabled);//不可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(lineNum,i,item);
        }
        QPushButton *pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        pushButton->setText("发 送");
        if(ui->tableWidget->item(lineNum,13)->text()=="已发送"){
            pushButton->setText("撤 回");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("发 送");
            pushButton->setEnabled(false);
        }
        QFont *font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
        ui->tableWidget->setCellWidget(lineNum,14,pushButton);

        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("继 续");
        }else{
            pushButton->setText("中 止");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已撤回"||
                ui->tableWidget->item(lineNum,14)->text()=="未发送"){
            pushButton->setEnabled(false);
        }
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
        ui->tableWidget->setCellWidget(lineNum,15,pushButton);

        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        pushButton->setText("查看遥测站");
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
        ui->tableWidget->setCellWidget(lineNum,11,pushButton);
        lineNum++;
    }
}

void MissionSendWidget::deleteButton()
{
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"删除提示","请选择一项进行删除操作");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    if(ui->tableWidget->item(ui->tableWidget->currentRow(),13)->text()=="已发送"||ui->tableWidget->item(ui->tableWidget->currentRow(),13)->text()=="已中止"){
        QMessageBox::information(this,"删除提示","请先撤回任务");
        return;
    }
    QString str("是否确认删除");
    str.append((ui->tableWidget->item(ui->tableWidget->currentRow(),0))->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes){
        unsendStationList.remove(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
}

void MissionSendWidget::editButtonSlot()
{
    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"编辑提示","请选择一项进行编辑操作");
        return ;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    if(ui->tableWidget->item(ui->tableWidget->currentRow(),13)->text()=="已发送"||ui->tableWidget->item(ui->tableWidget->currentRow(),13)->text()=="已中止"){
        QMessageBox::information(this,"删除提示","请先撤回任务");
        return;
    }
    disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&MissionSendWidget::doubleClick);
    qDebug() << currentRow;
    currentRow = ui->tableWidget->currentRow();
    qDebug() << currentRow;

    if(ui->tableWidget->currentRow()<0){
        QMessageBox::information(this,"编辑提示","请选择一项进行编辑操作");
    }else{
        qDebug() << 1;
        int currentRow = ui->tableWidget->currentRow();
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            if(i==2||i==3||i==1){
                QTimeEdit *time = new QTimeEdit;


                ui->tableWidget->setCellWidget(ui->tableWidget->currentRow(),i,time);
            }else if(i==12){
                QComboBox *combobox = new QComboBox;

                QStringList comboboxList;

                for(int i=0;i<macroInfo.size();i++){
                    comboboxList.append(macroInfo.at(i)->biaoshi);
                }

                combobox->addItems(comboboxList);
                qDebug() << "测试之前";
                combobox->setCurrentText(ui->tableWidget->item(ui->tableWidget->currentRow(),i)->text());

                qDebug() << "测试之后";
                combobox->setStyleSheet("background-color: rgb(200,200,200);");
                ui->tableWidget->setCellWidget(ui->tableWidget->currentRow(),i,combobox);
            }
            else{
                if(i<11){
                    QTableWidgetItem *item = ui->tableWidget->item(currentRow,i);
                    QColor *color = new QColor(200,200,200);
                    item->setBackgroundColor(*color);
                    item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
                    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
                }
            }
            if(i==14||i==15||i==11){
                QPushButton *pushbutton;
                pushbutton = (QPushButton*)ui->tableWidget->cellWidget(currentRow,i);
                pushbutton->setEnabled(false);
            }

        }
    }
    tableWidget_status = TableWidgetEditFlag;
}

void MissionSendWidget::checkStationSlot()
{
    QObject* obj = sender(); // 获取信号发送者对象
    QPushButton *button = dynamic_cast<QPushButton*>(obj); // 将QObject指针转换为QComboBox指针
    QModelIndex modeIdx = ui->tableWidget->indexAt(QPoint(button->frameGeometry().x(),button->frameGeometry().y()));
    qDebug()<<"按钮所在单元格:"<<modeIdx.row()<<":"<<modeIdx.column();

    StationShowMulty *mul = new StationShowMulty();
    qDebug() << "黄台" << ui->tableWidget->item(modeIdx.row(),13)->text();
    if(ui->tableWidget->item(modeIdx.row(),13)->text()!="未发送"&&ui->tableWidget->item(modeIdx.row(),13)->text()!="已撤回"){
        for(int i=0;i<basicInfo.size();i++){
            if(basicInfo.at(i)->code==ui->tableWidget->item(modeIdx.row(),0)->text()){
                mul->setStations(basicInfo.at(i)->stations);
                break;
            }
        }
    }else{
        mul->setMissionCode(ui->tableWidget->item(modeIdx.row(),0)->text());
        mul->setNothing();
    }
    mul->show();
}

void MissionSendWidget::getGrilleCatagortSlot()
{

}

void MissionSendWidget::refreshAllMission()
{
    if(refreshTimes!=0){
        QMessageBox::information(this,"任务提示","刷新成功");
    }else{
        refreshTimes++;
    }
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setRowCount(basicInfo.size());

    int lineNum = 0;
    for(int i=0;i<basicInfo.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(basicInfo.at(i)->code);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,0,item);

        item = new QTableWidgetItem(basicInfo.at(i)->basictime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,1,item);

        item = new QTableWidgetItem(basicInfo.at(i)->starttime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,2,item);

        item = new QTableWidgetItem(basicInfo.at(i)->endtime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,3,item);

        item = new QTableWidgetItem(basicInfo.at(i)->protect);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,4,item);

        item = new QTableWidgetItem(basicInfo.at(i)->point);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,5,item);

        item = new QTableWidgetItem(basicInfo.at(i)->status);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,6,item);

        item = new QTableWidgetItem(basicInfo.at(i)->mainport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,7,item);

        item = new QTableWidgetItem(basicInfo.at(i)->calport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,8,item);

        item = new QTableWidgetItem(basicInfo.at(i)->backport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,9,item);

        item = new QTableWidgetItem(basicInfo.at(i)->planePosition);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,10,item);

        item = new QTableWidgetItem(basicInfo.at(i)->missionhong);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,12,item);

        item = new QTableWidgetItem(basicInfo.at(i)->jinzhan);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,13,item);

        QPushButton *pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "color: darkgray;"
                                  "}");
        pushButton->setText("发 送");
        if(ui->tableWidget->item(lineNum,13)->text()=="已发送"){
            pushButton->setText("撤 回");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("发 送");
            pushButton->setEnabled(false);
        }
        QFont *font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
        ui->tableWidget->setCellWidget(lineNum,14,pushButton);

        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "color: darkgray;"
                                  "}");
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("继 续");
        }else{
            pushButton->setText("中 止");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已撤回"||
                ui->tableWidget->item(lineNum,13)->text()=="未发送"){
            pushButton->setEnabled(false);
        }
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
        ui->tableWidget->setCellWidget(lineNum,15,pushButton);
        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        pushButton->setText("查看遥测站");
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
        ui->tableWidget->setCellWidget(lineNum,11,pushButton);

        QString time =  QDateTime::fromSecsSinceEpoch(basicInfo.at(i)->time).toString("yyyy-MM-dd");
        item = new QTableWidgetItem(time);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,16,item);
        lineNum++;
    }
}

void MissionSendWidget::finishSend(QString code)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,0)->text()==code){
            ui->tableWidget->removeRow(i);
            break;
        }
    }
}

void MissionSendWidget::addNewMission(MissionBasicInfo *basic)
{
    QString updataInfo = "任务%1已下达";
    basicInfo.append(basic);
    updataInfo = updataInfo.arg(basic->code);
    QMessageBox::information(this,"任务更新信息",updataInfo);

    int lineNum = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(lineNum+1);

    QTableWidgetItem *item = new QTableWidgetItem(basic->code);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,0,item);

    item = new QTableWidgetItem(basic->basictime);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,1,item);

    item = new QTableWidgetItem(basic->starttime);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,2,item);

    item = new QTableWidgetItem(basic->endtime);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,3,item);

    item = new QTableWidgetItem(basic->protect);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,4,item);

    item = new QTableWidgetItem(basic->point);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,5,item);

    item = new QTableWidgetItem(basic->status);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,6,item);

    item = new QTableWidgetItem(basic->mainport);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,7,item);

    item = new QTableWidgetItem(basic->calport);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,8,item);

    item = new QTableWidgetItem(basic->backport);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,9,item);

    item = new QTableWidgetItem(basic->planePosition);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,10,item);

    item = new QTableWidgetItem(basic->missionhong);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,12,item);

    item = new QTableWidgetItem("已发送");
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,13,item);

    QPushButton *pushButton = new QPushButton();
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;"
                              "padding: 10px;"
                              "color: rgb(100, 100, 100);"
                              "}");
    pushButton->setText("撤 回");
    QFont *font = new QFont();
    font->setPointSize(8);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
    ui->tableWidget->setCellWidget(lineNum,14,pushButton);

    pushButton = new QPushButton();
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;"
                              "padding: 10px;"
                              "color: rgb(100, 100, 100);"
                              "}");

    pushButton->setText("中 止");
    font = new QFont();
    font->setPointSize(8);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
    ui->tableWidget->setCellWidget(lineNum,15,pushButton);
    pushButton = new QPushButton();
    pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                              "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                              "QPushButton:disabled {"
                              "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                              "border-radius: 5px;"
                              "padding: 10px;"
                              "color: rgb(100, 100, 100);"
                              "}");
    pushButton->setText("查看遥测站");
    font = new QFont();
    font->setPointSize(8);
    pushButton->setFont(*font);
    connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
    ui->tableWidget->setCellWidget(lineNum,11,pushButton);

    QString time =  QDateTime::fromSecsSinceEpoch(basic->time).toString("yyyy-MM-dd");
    item = new QTableWidgetItem(time);
    item->setFlags(Qt::ItemIsEnabled);//不可编辑
    item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
    ui->tableWidget->setItem(lineNum,16,item);
    lineNum++;
    lineNum++;
}

void MissionSendWidget::retrieveMission(QString code)
{
    QString updataInfo = "任务%1已撤回";
    updataInfo = updataInfo.arg(code);
    QMessageBox::information(this,"任务更新信息",updataInfo);
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,0)->text()==code){
            ui->tableWidget->item(i,13)->setText("已撤回");
            QPushButton *pushbutton;
            pushbutton = (QPushButton*)ui->tableWidget->cellWidget(i,14);
            pushbutton->setText("发 送");

            pushbutton = (QPushButton*)ui->tableWidget->cellWidget(i,15);

            pushbutton->setText("中 止");
            pushbutton->setEnabled(false);
            break;
        }
    }
    for(int i=0;i<basicInfo.size();i++){
        if(basicInfo.at(i)->code == code){
            basicInfo.removeAt(i);
            break;
        }
    }
}

void MissionSendWidget::abortMission(QString code)
{
    QString updataInfo = "任务%1已中止";
    updataInfo = updataInfo.arg(code);
    QMessageBox::information(this,"任务更新信息",updataInfo);
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,0)->text()==code){
            ui->tableWidget->item(i,13)->setText("已中止");
            QPushButton *button = (QPushButton*)ui->tableWidget->cellWidget(i,15);
            button->setText("继 续");
            break;
        }
    }
}

void MissionSendWidget::goonMission(QString code)
{
    QString updataInfo = "任务%1已继续";
    updataInfo = updataInfo.arg(code);
    QMessageBox::information(this,"任务更新信息",updataInfo);
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,0)->text()==code){
            ui->tableWidget->item(i,13)->setText("已发送");
            QPushButton *button = (QPushButton*)ui->tableWidget->cellWidget(i,15);
            button->setText("中 止");
            break;
        }
    }
}

void MissionSendWidget::refreshMissionBasic(QList<MissionBasicInfo*> list)
{
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setRowCount(list.size());
    unsendStationList.clear();

    int lineNum = 0;
    for(int i=0;i<list.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->code);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,0,item);

        item = new QTableWidgetItem(list.at(i)->basictime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,1,item);

        item = new QTableWidgetItem(list.at(i)->starttime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,2,item);

        item = new QTableWidgetItem(list.at(i)->endtime);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,3,item);

        item = new QTableWidgetItem(list.at(i)->protect);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,4,item);

        item = new QTableWidgetItem(list.at(i)->point);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,5,item);

        item = new QTableWidgetItem(list.at(i)->status);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,6,item);

        item = new QTableWidgetItem(list.at(i)->mainport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,7,item);

        item = new QTableWidgetItem(list.at(i)->calport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,8,item);

        item = new QTableWidgetItem(list.at(i)->backport);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,9,item);

        item = new QTableWidgetItem(list.at(i)->planePosition);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,10,item);

        item = new QTableWidgetItem(list.at(i)->missionhong);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,12,item);

        item = new QTableWidgetItem(list.at(i)->jinzhan);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,13,item);

        QPushButton *pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        pushButton->setText("发 送");
        if(ui->tableWidget->item(lineNum,13)->text()=="已发送"){
            pushButton->setText("撤 回");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("发 送");
            pushButton->setEnabled(false);
        }
        QFont *font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::sendButton_slot);
        ui->tableWidget->setCellWidget(lineNum,14,pushButton);

        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        if(ui->tableWidget->item(lineNum,13)->text()=="已中止"){
            pushButton->setText("继 续");
        }else{
            pushButton->setText("中 止");
        }
        if(ui->tableWidget->item(lineNum,13)->text()=="已撤回"||
                ui->tableWidget->item(lineNum,13)->text()=="未发送"){
            pushButton->setEnabled(false);
        }
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::abortButton_slot);
        ui->tableWidget->setCellWidget(lineNum,15,pushButton);
        pushButton = new QPushButton();
        pushButton->setStyleSheet("QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;padding: 10px;color: rgb(0, 0, 0);border:2px groove gray;padding:2px 4px;}"
                                  "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #D8D8D8, stop:1 #FFFFFF);}"
                                  "QPushButton:disabled {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FFFFFF, stop:1 #D8D8D8);"
                                  "border-radius: 5px;"
                                  "padding: 10px;"
                                  "color: rgb(100, 100, 100);"
                                  "}");
        pushButton->setText("查看遥测站");
        font = new QFont();
        font->setPointSize(8);
        pushButton->setFont(*font);
        connect(pushButton,&QPushButton::clicked,this,&MissionSendWidget::checkStationSlot);
        ui->tableWidget->setCellWidget(lineNum,11,pushButton);

        QString time =  QDateTime::fromSecsSinceEpoch(list.at(i)->time).toString("yyyy-MM-dd");
        item = new QTableWidgetItem(time);
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(lineNum,16,item);
        lineNum++;
    }
}


void MissionSendWidget::initial_basic_info()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    ui->label_2->setText(current_date_time.toString("yyyy.MM.dd"));
    QSqlQuery query(db);
    QString qs = QString("select * from `missionbasicinfo` where `时间` = '%1'")
            .arg(current_date_time.toString("yyyy.MM.dd"));
    query.exec(qs);
    QSqlRecord rec = query.record();
    int date = rec.indexOf("时间");
    int canmou = rec.indexOf("参谋");
    int fuzeren = rec.indexOf("负责人");
    int jinchangshijian = rec.indexOf("进场时间");
    int kaifanshijian = rec.indexOf("开饭时间");
    int lianxidianhua = rec.indexOf("联系电话");
    int renyuan = rec.indexOf("人员");
    while (query.next())
    {
        ui->label_4->setText(query.value(date).toString());
        ui->label_4->setText(query.value(canmou).toString());
        ui->label_6->setText(query.value(fuzeren).toString());
        ui->label_8->setText(query.value(jinchangshijian).toString());
        ui->label_10->setText(query.value(kaifanshijian).toString());
        ui->label_14->setText(query.value(lianxidianhua).toString());
        ui->label_16->setText(query.value(renyuan).toString());
    }
    qDebug() << qs;
}

QByteArray MissionSendWidget::sendMissionInfo(MissionSend missionBasic,MissionNew2 hong,QString status)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< missionBasic.refreshorinitial << missionBasic.code << missionBasic.basictime
         << missionBasic.starttime << missionBasic.endtime
         << missionBasic.protect << missionBasic.point <<
            missionBasic.status << missionBasic.mainport
         << missionBasic.calport << missionBasic.calport << missionBasic.backport <<
            missionBasic.missionhong << status
         <<hong.maxing << hong.malv << hong.zichang
           << hong.zhenchang<< hong.zhenmazu<< hong.zhenmazuchang
              << hong.fuzhenfangshi<< hong.fuzhenchang
                 << hong.idziweizhi<< hong.idzijizhi
                    << hong.idzijishu<< hong.jiemizhuangtai
                       << hong.xunhuanfuzhenweizhi<< hong.xunhuanfuzhenmazu
                          << hong.duofuhaojianyan<< hong.tpc
                             << hong.kuaitongbuzhenmazu<< hong.AGC
                                << hong.zhongpindaikuan<< hong.AFC
                                   << hong.AFCmoshi<< hong.jiaowucha
                                      << hong.gongzuodianpin<< hong.xinghao
                                         << hong.miaoshu<< hong.biaoshi;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x30);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray MissionSendWidget::withdrawMissionInfo(MissionSendWidget::MissionSend missionBasic, MissionSendWidget::MissionNew2 hong)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< quint8(0x00) << missionBasic.code;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x35);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray MissionSendWidget::abortMissionInfo(MissionSendWidget::MissionSend missionBasic, MissionSendWidget::MissionNew2 hong)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< quint8(0x01) << missionBasic.code;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x35);
    sendByte.append(sendByteo);
    return sendByte;
}

QByteArray MissionSendWidget::goonMissionInfo(MissionSendWidget::MissionSend missionBasic, MissionSendWidget::MissionNew2 hong)
{
    QByteArray sendByte;
    QDataStream strea(&sendByte,QIODevice::WriteOnly);
    strea.setVersion(QDataStream::Qt_5_1);

    QByteArray sendByteo;
    QDataStream streao(&sendByteo,QIODevice::WriteOnly);
    streao.setVersion(QDataStream::Qt_5_1);

    streao<< quint8(0x02) << missionBasic.code;

    strea<< quint8(0x5A) << quint8(0x5A) << quint32(sendByteo.size()+5) << quint8(0x35);
    sendByte.append(sendByteo);
    return sendByte;
}

void MissionSendWidget::resizeEvent(QResizeEvent *event)
{
    int tableWidth = ui->tableWidget->width();
    int headerTotalSize = ui->tableWidget->horizontalHeader()->length() + ui->tableWidget->frameWidth() * 2;

    if (tableWidth >= headerTotalSize) {
        if(tableWidth == headerTotalSize){
        }
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    if (tableWidth < tablewidgetLenth){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void MissionSendWidget::edit_basicInfo()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    BasicInfoEdit *p = new BasicInfoEdit();
    connect(p,&BasicInfoEdit::finishUpdate,this,&MissionSendWidget::updateBasicInfo);
    p->show();
}

void MissionSendWidget::updateBasicInfo(BasicInfo *info)
{
    ui->label_2->setText(info->shijian);
    ui->label_4->setText(info->canmou);
    ui->label_6->setText(info->fuzeren);
    ui->label_8->setText(info->jinchangshijian);
    ui->label_10->setText(info->kaifanshijian);
    ui->label_14->setText(info->lianxidianhua);
    ui->label_16->setText(info->renyuan);
}




void MissionSendWidget::initial_widgetHeader()
{
//    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(227, 234, 240);font-size: 12pt;color:black;border:1px solid rgb(237, 237, 237)}");
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
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setRowHeight(0,40);
    ui->tableWidget->verticalHeader()->setVisible(0);

    qDebug() << "执行了方法";

    QStringList headList;
    headList << "任务代号" << "到位时间" << "起始时间" <<"终止时间" << "保障内容" << "点频" << "状态"<<
                "主收端口"<< "解密端口"<< "备份端口" << "飞机位置"<< "遥测站"<<"任务宏" << "进展" << "发送任务" << "中止任务" << "时间";
    ui->tableWidget->setColumnCount(headList.size());
    ui->tableWidget->setHorizontalHeaderLabels(headList);
}

void MissionSendWidget::initial_slots()
{
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MissionSendWidget::addButton_slot);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MissionSendWidget::finishButton_slot);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&MissionSendWidget::edit_basicInfo);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&MissionSendWidget::missionExport);
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
                for(int i=0;i<ui->tableWidget->rowCount();i++)
                {
                    ui->tableWidget->setRowHidden(item.at(i)->row(),false);
                    ui->label_17->setText(QString(""));
                }
            }


        }
    });
}

void MissionSendWidget::addButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    if(tableWidget_status != TableWidgetCompleteFlag){
        QMessageBox::information(this,"提示信息","请完成当前操作");
        return ;
    }
    disconnect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,&MissionSendWidget::doubleClick);
    QStringList comboboxList;
    for(int i=0;i<macroInfo.size();i++){
        comboboxList.append(macroInfo.at(i)->biaoshi);
    }
    if(tableWidget_status == TableWidgetCompleteFlag){
        ui->tableWidget->setRowCount((ui->tableWidget->rowCount())+1);

        QTimeEdit *attime = new QTimeEdit;
        QTimeEdit *starttime = new QTimeEdit;
        QTimeEdit *endtime = new QTimeEdit;
        qDebug () << "2";
        ui->tableWidget->setCellWidget((ui->tableWidget->rowCount())-1,1,attime);
        ui->tableWidget->setCellWidget((ui->tableWidget->rowCount())-1,2,starttime);
        ui->tableWidget->setCellWidget((ui->tableWidget->rowCount())-1,3,endtime);

        qDebug () << "2";
        QComboBox *combobox = new QComboBox;
        combobox->addItems(comboboxList);
        combobox->setStyleSheet("background-color: rgb(200,200,200);");
        ui->tableWidget->setCellWidget((ui->tableWidget->rowCount())-1,12,combobox);
        qDebug () << "2";

        qDebug () << "2";

        for(int i=0;i<ui->tableWidget->columnCount();i++){
            qDebug () << i;
            QTableWidgetItem *item = new QTableWidgetItem("");
            QColor *color = new QColor(200,200,200);
            item->setBackgroundColor(*color);
            item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
            item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,i,item);
        }

        ui->tableWidget->item((ui->tableWidget->rowCount())-1,13)->setText("未发送");
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,13)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,14)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,11)->setFlags(Qt::ItemIsEditable);

        tableWidget_status = TableWidgetAddFlag;
    }else{
        QMessageBox::information(this,"提示","请完成当前操作");
    }
}

void MissionSendWidget::finishButton_slot()
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

void MissionSendWidget::sendButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    QObject* obj = sender(); // 获取信号发送者对象
    QPushButton *button = dynamic_cast<QPushButton*>(obj); // 将QObject指针转换为QComboBox指针
    QModelIndex modeIdx = ui->tableWidget->indexAt(QPoint(button->frameGeometry().x(),button->frameGeometry().y()));
    qDebug()<<"按钮所在单元格:"<<modeIdx.row()<<":"<<modeIdx.column();

    MissionBasicInfo *basic = new MissionBasicInfo();

    basic->code = ui->tableWidget->item(modeIdx.row(),0)->text();
    basic->basictime = ui->tableWidget->item(modeIdx.row(),1)->text();
    basic->starttime = ui->tableWidget->item(modeIdx.row(),2)->text();
    basic->endtime = ui->tableWidget->item(modeIdx.row(),3)->text();
    basic->protect = ui->tableWidget->item(modeIdx.row(),4)->text();
    basic->point = ui->tableWidget->item(modeIdx.row(),5)->text();
    basic->status = ui->tableWidget->item(modeIdx.row(),6)->text();
    basic->mainport = ui->tableWidget->item(modeIdx.row(),7)->text();
    basic->calport = ui->tableWidget->item(modeIdx.row(),8)->text();
    basic->backport = ui->tableWidget->item(modeIdx.row(),9)->text();
    basic->planePosition = ui->tableWidget->item(modeIdx.row(),10)->text();
    basic->missionhong = ui->tableWidget->item(modeIdx.row(),12)->text();

    if(button->text()=="发 送"){


//        StationSelect *p = new StationSelect(basic);
//        connect(p,&StationSelect::finishSend,this,&MissionSendWidget::finishSend);
//        p->show();

        QList<Station*> stationlist;
        if(unsendStationList.contains(ui->tableWidget->item(modeIdx.row(),0)->text())){
            QStringList list = unsendStationList.value(ui->tableWidget->item(modeIdx.row(),0)->text());
            for(int i=0;i<list.size();i++){
                Station *station = new Station();
                station->stationName = list.at(i);
                for(int j=0;j<stationInfo.size();j++){
                    if(stationInfo.at(j)->stationName==station->stationName){
                        station->stationIp = stationInfo.at(j)->stationIp;
                        break;
                    }
                }
                stationlist.append(station);
            }
            basic->stations = stationlist;
            QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
            udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendNewMission(basic)),*addr,ConfigInfo::centerUdpPort);

            QMessageBox::information(this,"发送提示",QString("任务%1发送成功").arg(basic->code));
            qInfo("用户: %s\t\t 任务%s发送", currentUser.toUtf8().constData(),basic->code.toUtf8().constData());

            unsendStationList.remove(ui->tableWidget->item(modeIdx.row(),0)->text());
            ui->tableWidget->removeRow(modeIdx.row());

        }else{
            QMessageBox::information(this,"提示信息","未选择遥测站");
        }
    }else{
        //撤回
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::retrieveMission(basic->code)),*addr,ConfigInfo::centerUdpPort);
    }
}

void MissionSendWidget::abortButton_slot()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    QObject* obj = sender(); // 获取信号发送者对象
    QPushButton *button = dynamic_cast<QPushButton*>(obj); // 将QObject指针转换为QComboBox指针
    QModelIndex modeIdx = ui->tableWidget->indexAt(QPoint(button->frameGeometry().x(),button->frameGeometry().y()));
    qDebug()<<"按钮所在单元格:"<<modeIdx.row()<<":"<<modeIdx.column();

    if(button->text()=="中 止"){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::abortMission(ui->tableWidget->item(modeIdx.row(),0)->text())),*addr,ConfigInfo::centerUdpPort);
    }else{
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::goonMission(ui->tableWidget->item(modeIdx.row(),0)->text())),*addr,ConfigInfo::centerUdpPort);
    }
}

void MissionSendWidget::missionExport()
{
    bac = new BasicForm;
    bac->setRowCount(ui->tableWidget->rowCount()+4);
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        qDebug() << "循环添加list" << i;
        BasicInfo *info = new BasicInfo;
        info->shijian = ui->label_2->text();
        info->canmou = ui->label_4->text();
        info->fuzeren = ui->label_6->text();
        info->jinchangshijian = ui->label_8->text();
        info->kaifanshijian = ui->label_10->text();
        info->lianxidianhua = ui->label_14->text();
        info->renyuan = ui->label_16->text();

        info->renwudaihao = ui->tableWidget->item(i,0)->text();
        info->daoweishijian = ui->tableWidget->item(i,1)->text();
        info->shijianjiedianqishi = ui->tableWidget->item(i,2)->text();
        info->shijianjiedianzhongzhi = ui->tableWidget->item(i,3)->text();
        info->baozhangneirong = ui->tableWidget->item(i,4)->text();
        info->dianpin = ui->tableWidget->item(i,5)->text();
        info->zhuangtai = ui->tableWidget->item(i,6)->text();
        info->zhuzhouduankou = ui->tableWidget->item(i,7)->text();
        info->jiemiduankou = ui->tableWidget->item(i,8)->text();
        info->beifenduankou = ui->tableWidget->item(i,9)->text();
        info->feijiweizhi = ui->tableWidget->item(i,10)->text();
        info->renwuhong = ui->tableWidget->item(i,12)->text();
        bac->list.append(info);
    }
    bac->initialTablewidget();
    bac->setTableWidgetItem();
    bac->show();
    bac->exportExcel();
}

void MissionSendWidget::sendAllMission(QString ip)
{
    QSqlQuery query(db);
    QString qs = QString("select * from `missionsendinfo` where `ip` = '%1'")
            .arg(ip);
    query.exec(qs);
    QSqlRecord rec = query.record();
    int code = rec.indexOf("code");
    QStringList codelist;
    while (query.next())
    {
        codelist.append(query.value(code).toString());
        qDebug() << "查到的信息" << query.value(code).toString();
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if((ui->tableWidget->item(i,11)->text()!="已撤回")&&codelist.contains(ui->tableWidget->item(i,0)->text())){
            MissionSend missionsend;
            missionsend.refreshorinitial = 0x00;
            missionsend.code = ui->tableWidget->item(i,0)->text();
            missionsend.basictime = ui->tableWidget->item(i,1)->text();
            missionsend.starttime = ui->tableWidget->item(i,2)->text();
            missionsend.endtime = ui->tableWidget->item(i,3)->text();
            missionsend.protect = ui->tableWidget->item(i,4)->text();
            missionsend.point = ui->tableWidget->item(i,5)->text();
            missionsend.status = ui->tableWidget->item(i,6)->text();
            missionsend.mainport = ui->tableWidget->item(i,7)->text().toInt();
            missionsend.calport = ui->tableWidget->item(i,8)->text().toInt();
            missionsend.backport = ui->tableWidget->item(i,9)->text().toInt();
            missionsend.missionhong = ui->tableWidget->item(i,10)->text();
            QString status = ui->tableWidget->item(i,11)->text();
        //    QByteArray array = sendMissionInfo(1,)

            MissionNew2 missionnew2;
            QSqlQuery query(db);
            QString qs = QString("select * from `missionnew2` where `任务标识` = '%1'").arg(missionsend.missionhong);
            query.exec(qs);
            QSqlRecord rec = query.record();

            while (query.next())
            {
                missionnew2.maxing = query.value(0).toString();
                missionnew2.malv = query.value(1).toString();
                missionnew2.zichang = query.value(2).toInt();
                missionnew2.zhenchang = query.value(3).toInt();
                missionnew2.zhenmazu = query.value(4).toString();
                missionnew2.zhenmazuchang = query.value(5).toInt();
                missionnew2.fuzhenfangshi = query.value(6).toString();
                missionnew2.fuzhenchang = query.value(7).toInt();
                missionnew2.idziweizhi = query.value(8).toInt();
                missionnew2.idzijizhi = query.value(9).toInt();
                missionnew2.idzijishu = query.value(10).toString();
                missionnew2.jiemizhuangtai = query.value(11).toString();
                missionnew2.xunhuanfuzhenweizhi = query.value(12).toInt();
                missionnew2.xunhuanfuzhenmazu = query.value(13).toString();
                missionnew2.duofuhaojianyan = query.value(14).toString();
                missionnew2.tpc = query.value(15).toString();
                missionnew2.kuaitongbuzhenmazu = query.value(16).toString();
                missionnew2.AGC = query.value(17).toInt();
                missionnew2.zhongpindaikuan = query.value(18).toString();
                missionnew2.AFC = query.value(19).toInt();
                missionnew2.AFCmoshi = query.value(20).toString();
                missionnew2.jiaowucha = query.value(21).toInt();
                missionnew2.gongzuodianpin = query.value(22).toString();
                missionnew2.xinghao = query.value(23).toString();
                missionnew2.miaoshu = query.value(24).toString();
                missionnew2.biaoshi = query.value(25).toString();
            }

            QByteArray array = sendMissionInfo(missionsend,missionnew2,status);
            QHostAddress addre;
            addre.setAddress(ip);
            udpsocket->writeDatagram(getInvert(array),addre,9010);
        }
    }

    qDebug() << "发送全部任务信息";
}

void MissionSendWidget::doubleClick(int row,int column)
{
    qDebug() << "获取进展" << ui->tableWidget->item(row,13)->text();
    if(ui->tableWidget->item(row,13)->text()=="已发送"){
        review->setButtonAble(true);
    }else{
        review->setButtonAble(false);
    }
    review->modelStatus = ui->tableWidget->item(row,12)->text();
    review->setItemByCode(ui->tableWidget->item(row,12)->text(),ui->tableWidget->item(row,0)->text());
    connect(review,&MissionNewReview::sendFileInfo,remoteDataWidget,&RemoteDataSingleWidget::setDllInfo);
    int flag= 0;
    for(int i=0;i<macroInfo.size();i++){
        if(macroInfo.at(i)->biaoshi==ui->tableWidget->item(row,12)->text()){
            flag = 1;
        }
    }
    if(flag){
        review->show();
    }else{
        QMessageBox::information(this,"加载失败","请刷新");
    }

}

QByteArray MissionSendWidget::getInvert(QByteArray array)
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
