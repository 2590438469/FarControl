#include "basicinfoedit.h"
#include "ui_basicinfoedit.h"
#include <QDateTime>
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>
#include <QComboBox>
#include <QMessageBox>
#include <QSqlError>
#include "firstwindow.h"

BasicInfoEdit::BasicInfoEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasicInfoEdit)
{
    ui->setupUi(this);
    initialinfo();
    connect(ui->pushButton,&QPushButton::clicked,this,&BasicInfoEdit::insertInfo);
    int j=0;
    for(int i=0;i<userInfo.size();i++){
        if(userInfo.at(i)->role=="普通人员"){
            QCheckBox *checkBox = new QCheckBox();
            checkBox->setText(userInfo.at(i)->name);
            ui->gridLayout_2->addWidget(checkBox,j/7,j%7);
            checkBoxList.append(checkBox);
            j++;
        }
    }
}

BasicInfoEdit::~BasicInfoEdit()
{
    delete ui;
}

void BasicInfoEdit::initialinfo()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    ui->dateEdit->setDateTime(current_date_time);
//    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");



    QTime *timeIn = new QTime(8,0,0,0);
    QTime *timeEat = new QTime(12,0,0,0);
    ui->timeEdit->setTime(*timeIn);
    ui->timeEdit_2->setTime(*timeEat);
    QStringList nameList;
    QStringList phoneList;
    for(int i=0;i<userInfo.size();i++){
        if(userInfo.at(i)->role == "普通人员"){
            nameList << userInfo.at(i)->name;
            phoneList << userInfo.at(i)->phoneNumber;
        }
    }
    ui->comboBox->addItems(nameList);
    ui->comboBox_2->addItems(nameList);
    ui->comboBox_3->addItems(phoneList);

}

void BasicInfoEdit::insertInfo()
{
    QMessageBox::information(this,"添加信息","添加成功");
    QString people;
    int j=0;
    for(int i=0;i<checkBoxList.size();i++){
        if(checkBoxList.at(i)->isChecked()){
            people.append(checkBoxList.at(i)->text());
            people.append(",");
            j++;
        }
        if(j!=0&&j%5==0){
            people.append("\n");
        }
    }
    people.chop(1);
    BasicInfo *basicInfo = new BasicInfo();

    basicInfo->shijian = ui->dateEdit->dateTime().toString("yyyy.MM.dd");
    basicInfo->canmou = ui->comboBox->currentText();
    basicInfo->fuzeren = ui->comboBox_2->currentText();
    basicInfo->jinchangshijian = ui->timeEdit->dateTime().toString("hh:mm");
    basicInfo->kaifanshijian = ui->timeEdit_2->dateTime().toString("hh:mm");
    basicInfo->lianxidianhua = ui->comboBox_3->currentText();
    basicInfo->renyuan = people;
    emit finishUpdate(basicInfo);
    this->close();
}
