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

BasicInfoEdit::BasicInfoEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasicInfoEdit)
{
    ui->setupUi(this);
    initialinfo();
    connect(ui->pushButton,&QPushButton::clicked,this,&BasicInfoEdit::insertInfo);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&BasicInfoEdit::deleteMember);
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

    ui->comboBox_4->addItem("未选择");

    QSqlQuery query(db);
    QString qs = QString("select * from usernew");
    query.exec(qs);
    QSqlRecord rec = query.record();
    int name = rec.indexOf("真实姓名");
    int phone = rec.indexOf("电话号码");
    while (query.next())
    {
        ui->comboBox->addItem(query.value(name).toString());
        ui->comboBox_2->addItem(query.value(name).toString());
        ui->comboBox_3->addItem(query.value(phone).toString());
        ui->comboBox_4->addItem(query.value(name).toString());
    }
    QTime *timeIn = new QTime(8,0,0,0);
    QTime *timeEat = new QTime(12,0,0,0);
    ui->timeEdit->setTime(*timeIn);
    ui->timeEdit_2->setTime(*timeEat);

    connect(ui->comboBox_4,&QComboBox::currentTextChanged,this,&BasicInfoEdit::judgeCombobox);
}

void BasicInfoEdit::judgeCombobox(QString text)
{

    QObject* obj = sender(); // 获取信号发送者对象
    QComboBox *comboboxOld = dynamic_cast<QComboBox*>(obj); // 将QObject指针转换为QComboBox指针
    if (comboboxOld == nullptr) {
        qDebug() << "转换失败，进行错误处理";
    } else {
        comboboxList.append(comboboxOld);
        disconnect(comboboxOld,&QComboBox::currentTextChanged,this,&BasicInfoEdit::judgeCombobox);
        QComboBox *combobox = new QComboBox();
        combobox->addItem("未选择");
        if(text!="未选择"){
            QSqlQuery query(db);
            QString qs = QString("select * from usernew");
            query.exec(qs);
            QSqlRecord rec = query.record();
            int name = rec.indexOf("真实姓名");
            while (query.next())
            {
                combobox->addItem(query.value(name).toString());
            }
        }
        ui->horizontalLayout->addWidget(combobox);
        connect(combobox,&QComboBox::currentTextChanged,this,&BasicInfoEdit::judgeCombobox);
    }
}

void BasicInfoEdit::insertInfo()
{
    QSqlQuery query1(db);
    QString qs2 = QString("delete from  missionbasicinfo where `时间`='%1'").arg(ui->dateEdit->dateTime().toString("yyyy.MM.dd"));
    qDebug() << qs2;
    bool ok2 = query1.exec(qs2);

    QString people;
    for(int i=0;i<comboboxList.size();i++){
        if(comboboxList.at(i)->currentText()!="未选择"){
            people.append(comboboxList.at(i)->currentText());
            people.append(",");
        }
    }
    people.chop(1);

    QSqlQuery query(db);
    QString qs = QString("insert into missionbasicinfo (`时间`,`参谋`,`负责人`,`进场时间`,`开饭时间`,`飞机位置`,`联系电话`,`人员`)"
                         " values ('%1','%2','%3','%4','%5','%6','%7','%8')").arg(ui->dateEdit->dateTime().toString("yyyy.MM.dd"))
            .arg(ui->comboBox->currentText()).arg(ui->comboBox_2->currentText()).arg(ui->timeEdit->dateTime().toString("hh:mm"))
            .arg(ui->timeEdit_2->dateTime().toString("hh:mm")).arg(ui->lineEdit->text()).arg(ui->comboBox_3->currentText()).arg(people);
    qDebug() << qs;
    bool ok = query.exec(qs);
    if(ok){
        QMessageBox::information(this,"添加信息","添加成功");
        emit finishUpdate();
        this->hide();
    }else{
        QMessageBox::information(this,"添加信息",query.lastError().text());
    }

}

void BasicInfoEdit::deleteMember()
{
    int count = ui->horizontalLayout->count();

    if(count > 1){
        QWidget *widget = ui->horizontalLayout->itemAt(count - 1)->widget();

        ui->horizontalLayout->removeWidget(widget);

        widget->deleteLater();
        comboboxList.removeLast();
    }

}
