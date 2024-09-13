#include "loginfo.h"
#include "ui_loginfo.h"
#include <QFile>
#include <QDebug>

LogInfo::LogInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInfo)
{
    ui->setupUi(this);
}

LogInfo::LogInfo(QString filepath, QWidget *parent):
    QWidget(parent),
    ui(new Ui::LogInfo)
{
    ui->setupUi(this);
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return;
    }

    // Read the file line by line and add each line to the list widget
    while (!file.atEnd()) {
        QString line = QString::fromLocal8Bit(file.readLine().trimmed());
        ui->listWidget->addItem(line);
    }

    file.close();

}

LogInfo::~LogInfo()
{
    delete ui;
}
