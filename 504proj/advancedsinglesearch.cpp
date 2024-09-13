#include "advancedsinglesearch.h"
#include "ui_advancedsinglesearch.h"

AdvancedSingleSearch::AdvancedSingleSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvancedSingleSearch)
{
    ui->setupUi(this);
    QStringList list;
    list << "定值" << "最小值" << "最大值";
    ui->comboBox_2->addItems(list);
    ui->comboBox_3->hide();
}

AdvancedSingleSearch::~AdvancedSingleSearch()
{
    delete ui;
}

void AdvancedSingleSearch::setList(QStringList list)
{
    comboList = list;
    ui->comboBox->addItems(list);
}

QString AdvancedSingleSearch::getName()
{
    return ui->comboBox->currentText();
}

QString AdvancedSingleSearch::getCondition()
{
    return ui->comboBox_2->currentText();
}

QString AdvancedSingleSearch::getPrice()
{
    if(!ui->lineEdit->isHidden()){
        return ui->lineEdit->text();
    }else{
        return ui->comboBox_3->currentText();
    }
}

int AdvancedSingleSearch::getNameNum()
{
    return ui->comboBox->currentIndex();
}

void AdvancedSingleSearch::setMap(QMap<quint8, QStringList> mapString)
{
    map = mapString;
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboChange(int)));
    if(mapString.contains(0)){
        ui->lineEdit->hide();
        ui->comboBox_3->clear();
        ui->comboBox_3->addItems(map.value(0));
        ui->comboBox_3->show();
    }
}

void AdvancedSingleSearch::setDingList(QList<int> list)
{
    dingList = list;
    if(dingList.contains(0)){
        QStringList list;
        list << "定值";
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(list);
    }
}

void AdvancedSingleSearch::comboChange(int index)
{
    if(map.contains(ui->comboBox->currentIndex())){
        ui->lineEdit->hide();
        ui->comboBox_3->clear();
        ui->comboBox_3->addItems(map.value(index));
        ui->comboBox_3->show();
    }else{
        ui->lineEdit->show();
        ui->comboBox_3->hide();
    }
    if(dingList.contains(index)){
        QStringList list;
        list << "定值";
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(list);
    }else{
        QStringList list;
        list << "定值" << "最小值" << "最大值";
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(list);
    }
}
