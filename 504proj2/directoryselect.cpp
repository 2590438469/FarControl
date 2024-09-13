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
    connect(ui->pushButton,&QPushButton::clicked,this,&DirectorySelect::selectFilePath);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&DirectorySelect::selectGeshanFilePath);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&DirectorySelect::selectDisplayPath);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&DirectorySelect::selectCustomSoftwarePath);


    ui->label_2->setText(ConfigInfo::genMulu);
    ui->label_4->setText(ConfigInfo::geShanMulu);
    ui->label_6->setText(ConfigInfo::displayMulu);
    ui->label_8->setText(ConfigInfo::customData);
}

DirectorySelect::~DirectorySelect()
{
    delete ui;
}

void DirectorySelect::selectFilePath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    ConfigInfo::writeXml(ConfigInfo::genMuluString,directoryPath);
    ui->label_2->setText(ConfigInfo::genMulu);
    QMessageBox::information(this,"提示信息","修改成功");
}

void DirectorySelect::selectGeshanFilePath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    ConfigInfo::writeXml(ConfigInfo::geShanMuluString,directoryPath);
    ui->label_4->setText(ConfigInfo::geShanMulu);
    QMessageBox::information(this,"提示信息","修改成功");
}

void DirectorySelect::selectDisplayPath()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), QDir::currentPath());
    ConfigInfo::writeXml(ConfigInfo::displayMuluString,directoryPath);
    ui->label_6->setText(ConfigInfo::displayMulu);
    QMessageBox::information(this,"提示信息","修改成功");
}

void DirectorySelect::selectCustomSoftwarePath()
{
    QString directoryPath = QFileDialog::getOpenFileName(nullptr, "Select a file", "", "All Files (*)");
    ConfigInfo::writeXml(ConfigInfo::customDataString,directoryPath);
    ui->label_8->setText(ConfigInfo::customData);
    QMessageBox::information(this,"提示信息","修改成功");
}
