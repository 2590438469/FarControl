#include "datastatistic.h"
#include "ui_datastatistic.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include "util/bytemethod.h"
#include "config/configinfo.h"

DataStatistic::DataStatistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStatistic)
{
    ui->setupUi(this);
    QStringList  widget_column_header;
    widget_column_header << "人员"<<"操作" << "文件名"<<"时间";
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

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowHeight(0,40);
    ui->tableWidget->verticalHeader()->setVisible(0);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        Statistic *statistic = new Statistic();
        statistic->people = ui->comboBox->currentText();
        statistic->startTime = ui->dateEdit->dateTime().toTime_t();
        statistic->endTime = ui->dateEdit_2->dateTime().addDays(1).toTime_t();
        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendStatistic(statistic)),addre,ConfigInfo::centerUdpPort);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){

        QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text Files (*.txt)");

        if (!filePath.isEmpty()) {
            QFile file(filePath);

            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out.setCodec("UTF-8");
                out << QString("总计: ") << ui->tableWidget->rowCount() << "\n";
                for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
                    out << ui->tableWidget->item(i, 0)->text() << "   ";
                    out << ui->tableWidget->item(i, 1)->text() << "   ";
                    out << ui->tableWidget->item(i, 2)->text() << "   ";
                    out << ui->tableWidget->item(i, 3)->text() << "   ";
                    out << "\n";
                }
                file.close();
                qDebug() << "File exported successfully.";
            } else {
                qDebug() << "Failed to export file.";
            }
        } else {
            qDebug() << "No file selected.";
        }
    });
}

DataStatistic::~DataStatistic()
{
    delete ui;
}

void DataStatistic::initial()
{
    ui->tableWidget->setRowCount(0);
    ui->comboBox->clear();
    for(int i=0;i<userInfo.size();i++){
        ui->comboBox->addItem(userInfo.at(i)->code);
    }
}

void DataStatistic::initialall(QList<FileLog *> list)
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(list.size());
    for(int i=0;i<list.size();i++){
        QTableWidgetItem *item = new QTableWidgetItem(list.at(i)->people);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,0,item);

        QString op;
        if(list.at(i)->operation == 0){
            op = "遥测文件上传";
        }else if(list.at(i)->operation == 1){
            op = "遥测文件下载";
        }else if(list.at(i)->operation == 2){
            op = "格栅文件上传";
        }else if(list.at(i)->operation == 3){
            op = "格栅文件下载";
        }
        item = new QTableWidgetItem(op);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,1,item);

        item = new QTableWidgetItem(list.at(i)->fileName);
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,2,item);

        item = new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(list.at(i)->time).toString("yyyy-MM-dd hh:mm"));
        item->setFlags(Qt::ItemIsEditable|item->flags());//可编辑
        item->setFlags(Qt::ItemIsEnabled);//不可编辑
        item->setFlags(Qt::ItemIsSelectable|item->flags());//选中变换蓝底
        ui->tableWidget->setItem(i,3,item);

    }
}
