#include "missionnewinsert.h"
#include "ui_missionnewinsert.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "firstwindow.h"
#include "config/configinfo.h"

MissionNewInsert::MissionNewInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionNewInsert)
{
    ui->setupUi(this);
    initial_combobox_items();
    initial_header();
    connect(ui->pushButton,&QPushButton::clicked,this,&MissionNewInsert::add_button_slot);
    ui->label_25->hide();
    ui->label_26->hide();
    ui->lineEdit_11->hide();
    ui->lineEdit_12->hide();
    ui->lineEdit_7->setEnabled(false);
    ui->lineEdit_16->setEnabled(false);
    ui->label_13->setEnabled(false);
    ui->label_14->setEnabled(false);
    ui->label_34->setEnabled(false);
    connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(text_change(int)));
}

MissionNewInsert::~MissionNewInsert()
{
    delete ui;
}

void MissionNewInsert::initial_combobox_items()
{
    QStringList strList1;
    strList1 << "NRZ-L" << "NRZ-M" <<  "NRZ-S" <<  "Bip-L" << "Bip-M" << "Bip-S" << "RNRZ-L";
    QStringList strList2;
    strList2 << "HEX1" << "HEX2" << "HEX3" << "HEX4" << "HEX5" << "HEX6" << "HEX7" << "HEX8";
    QStringList strList3;
    strList3 << "ID副帧" << "循环副帧" << "无副帧";
    QStringList strList4;
    strList4 << "0" << "1" ;
    QStringList strList5;
    strList5 << "加计数" << "减计数" ;
    QStringList strList6;
    strList6 << "ZZ" << "KJ" ;
    QStringList strList7;
    strList7 << "是" << "否" ;
    QStringList strList8;
    strList8 << "无" << "TPC有效" << "LDPC有效";
    QStringList strList9;
    strList9 << "3" << "10" << "100" << "1000";
    QStringList strList10;
    strList10 << "50K"<< "300K"<< "500K"<< "750K"<< "1M"<< "1.5M"
           << "2.4M"<< "3.3M"<< "4.0M"<< "6.0M"<< "10M"<< "15M"
           << "20M"<< "24M"<<  "33M"<< "40M";
    QStringList strList11;
    strList11 << "3" << "60" << "300";
    QStringList strList12;
    strList12 <<"闭环" << "开环";
    QStringList strList13;
    for(int i=0;i<geshanInfo.size();i++){
        strList13 << geshanInfo.at(i);
    }
    QStringList strList14;
    strList14 << "8" << "16";

    ui->comboBox->addItems(strList1);
    ui->comboBox_2->addItems(strList13);
    ui->comboBox_3->addItems(strList3);
    ui->comboBox_4->addItems(strList4);
    ui->comboBox_5->addItems(strList5);
    ui->comboBox_6->addItems(strList6);
    ui->comboBox_8->addItems(strList7);
    ui->comboBox_9->addItems(strList8);
    ui->comboBox_11->addItems(strList9);
    ui->comboBox_12->addItems(strList10);
    ui->comboBox_13->addItems(strList11);
    ui->comboBox_14->addItems(strList12);
    ui->comboBox_7->addItems(strList14);
}

void MissionNewInsert::initial_header()
{
    widget_column_header << "码型" << "码率" << "字长" << "帧长" << "帧码组"
               << "帧码组长" << "副帧方式" << "副帧长" << "ID字位置" << "ID字基值"
               << "ID字计数方向" << "解密状态" << "循环副帧位置" << "循环副帧码组" << "多符号检验"
               << "TPC/LDPC校验" << "块同步帧码组" << "AGC时间常数" << "中频带宽" << "AFC时间常数"
               << "AFC模式" << "角误差输出带宽" << "工作点频" << "任务型号" << "任务描述" <<"任务标识"<<"软解密";
}

void MissionNewInsert::add_button_slot()
{
    QVector<QString> Array;
    quint8 logo;
    sendAddInfo(Array,logo);

    this->close();
}

void MissionNewInsert::text_change(int index)
{
    if(index==0){
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_16->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_34->setEnabled(false);

        ui->label_8->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->label_32->setEnabled(true);

        ui->label_9->setEnabled(true);
        ui->label_10->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);
        ui->label_33->setEnabled(true);
    }else if(index==1){
        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->lineEdit_6->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);
        ui->label_33->setEnabled(false);

        ui->lineEdit_7->setEnabled(true);
        ui->lineEdit_16->setEnabled(true);
        ui->label_13->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_34->setEnabled(true);

        ui->label_8->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->label_32->setEnabled(true);
    }else{
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_16->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_34->setEnabled(false);

        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->lineEdit_6->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);
        ui->label_33->setEnabled(false);

        ui->label_8->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ui->label_32->setEnabled(false);
    }
}

void MissionNewInsert::sendAddInfo(QVector<QString> Array,quint8 logo)
{
    quint8 column = 27;
    Array.resize(column);
    logo = 0x02;

    Array[0]  = ui->comboBox->currentText();
    Array[1]  = ui->lineEdit->text();
    Array[2]  = ui->comboBox_7->currentText();
    Array[3]  = ui->lineEdit_3->text();
    Array[4]  = ui->lineEdit_14->text();
    Array[5]  = ui->lineEdit_4->text();
    Array[6]  = ui->comboBox_3->currentText();
    if(ui->lineEdit_5->isEnabled()){
        Array[7]  = ui->lineEdit_5->text();
    }else{
        Array[7]  = "";
    }
    if(ui->lineEdit_6->isEnabled()){
        Array[8]  = ui->lineEdit_6->text();
    }else{
        Array[8]  = "";
    }
    if(ui->comboBox_4->isEnabled()){
        Array[9]  = ui->comboBox_4->currentText();
    }else{
        Array[9]  = "";
    }
    if(ui->comboBox_5->isEnabled()){
        Array[10] = ui->comboBox_5->currentText();
    }else{
        Array[10] = "";
    }
    Array[11] = ui->comboBox_6->currentText();
    if(ui->lineEdit_7->isEnabled()){
        Array[12] = ui->lineEdit_7->text();
    }else{
        Array[12] = "";
    }
    if(ui->lineEdit_16->isEnabled()){
        Array[13] = ui->lineEdit_16->text();
    }else{
        Array[13] = "";
    }
    Array[14] = ui->comboBox_8->currentText();
    Array[15] = ui->comboBox_9->currentText();
    Array[16] = ui->lineEdit_15->text();
    Array[17] = ui->comboBox_11->currentText();
    Array[18] = ui->comboBox_12->currentText();
    Array[19] = ui->comboBox_13->currentText();
    Array[20] = ui->comboBox_14->currentText();
    Array[21] = ui->lineEdit_8->text();
    Array[22] = ui->lineEdit_9->text().append("~").append(ui->lineEdit_10->text());
    Array[23] = ui->lineEdit_11->text();
    Array[24] = ui->lineEdit_12->text();
    Array[25] = ui->comboBox_2->currentText();
    if(ui->checkBox->isChecked()){
        Array[26] = "是";
    }else{
        Array[26] = "否";
    }

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

    QByteArray array = sendByte;
    QHostAddress addre;
    addre.setAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(getInvert(array),addre,9001);
}

QByteArray MissionNewInsert::getInvert(QByteArray array)
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
