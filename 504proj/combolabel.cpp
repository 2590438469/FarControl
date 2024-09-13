#include "combolabel.h"
#include "ui_combolabel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"

ComboLabel::ComboLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboLabel)
{
    ui->setupUi(this);
    QSqlQuery query(db);
    QString qs = QString("select * from `stationnew`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    int ip = rec.indexOf("ip地址");
    int name = rec.indexOf("遥测站名");
    while (query.next())
    {
        nameList.append(query.value(name).toString());
        ipList.append(query.value(ip).toString());
    }
    ui->comboBox->addItems(nameList);
    ui->label->setText(ipList.at(0));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(changeIp(int)));
}

ComboLabel::~ComboLabel()
{
    delete ui;
}

QString ComboLabel::getIp()
{
    return ui->label->text();
}

QString ComboLabel::getName()
{
    return ui->comboBox->currentText();
}

void ComboLabel::changeIp(int index)
{
    ui->label->setText(ipList.at(index));
}
