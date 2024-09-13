#include "directoryselect.h"
#include "ui_directoryselect.h"
#include "firstwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "mainwindow.h"
#include <QSqlRecord>
#include "config/configinfo.h"

DirectorySelect::DirectorySelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectorySelect)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&DirectorySelect::setGrillePath);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&DirectorySelect::setDatPath);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&DirectorySelect::setOxPath);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&DirectorySelect::setHeadPath);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&DirectorySelect::setBackupPath);

//    QSqlQuery query(db);
//    QString qs = QString("select * from `constant`");
//    bool ok =query.exec(qs);
//    QSqlRecord rec = query.record();
//    int code = rec.indexOf("文件根目录");
//    while (query.next())
//    {
//        QString codestr = query.value(code).toString();
//        ui->label_2->setText(codestr);
//    }

    ui->label_4->setText(ConfigInfo::grillePath);
    ui->label_8->setText(ConfigInfo::datPath);
    ui->label_10->setText(ConfigInfo::oxPath);
    ui->label_14->setText(ConfigInfo::headPath);
    ui->label_16->setText(ConfigInfo::backupPath);

    ui->label_9->hide();
    ui->label_10->hide();
    ui->pushButton_5->hide();
    ui->line_6->hide();
}

DirectorySelect::~DirectorySelect()
{
    delete ui;
}


void DirectorySelect::setGrillePath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::grillePathString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
        ui->label_4->setText(directoryPath);
    }
}

void DirectorySelect::setDisplayFramePath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::display_frameString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
    }
}

void DirectorySelect::setDatPath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::datPathString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
        ui->label_8->setText(directoryPath);
    }
}

void DirectorySelect::setOxPath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::oxPathString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
        ui->label_10->setText(directoryPath);
    }
}

void DirectorySelect::setHeadPath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::headPathString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
        ui->label_14->setText(directoryPath);
    }
}

void DirectorySelect::setBackupPath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    if(directoryPath!=""){
        ConfigInfo::writeXml(ConfigInfo::backupPathString,directoryPath);
        QMessageBox::information(this,"更新提示","更新成功");
        ui->label_16->setText(directoryPath);
    }
}
