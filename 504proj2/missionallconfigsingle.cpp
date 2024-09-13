#include "missionallconfigsingle.h"
#include "ui_missionallconfigsingle.h"

MissionAllConfigSingle::MissionAllConfigSingle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionAllConfigSingle)
{
    ui->setupUi(this);
    QStringList list;
    list << "0803" << "1004";
    ui->comboBox->addItems(list);
}

MissionAllConfigSingle::~MissionAllConfigSingle()
{
    delete ui;
}
