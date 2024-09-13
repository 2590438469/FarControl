#include "missoninput.h"
#include "ui_missoninput.h"

missoninput::missoninput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::missoninput)
{
    ui->setupUi(this);
}

missoninput::~missoninput()
{
    delete ui;
}
