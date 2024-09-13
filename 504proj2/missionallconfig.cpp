#include "missionallconfig.h"
#include "ui_missionallconfig.h"
#include "missionallconfigsingle.h"

MissionAllConfig::MissionAllConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionAllConfig)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&MissionAllConfig::addItem);
}

MissionAllConfig::~MissionAllConfig()
{
    delete ui;
}

void MissionAllConfig::addItem()
{
    MissionAllConfigSingle *p = new MissionAllConfigSingle();
    ui->verticalLayout->addWidget(p);
}
