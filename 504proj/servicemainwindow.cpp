#include "servicemainwindow.h"
#include "ui_servicemainwindow.h"

ServiceMainWindow::ServiceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServiceMainWindow)
{
    ui->setupUi(this);
}

ServiceMainWindow::~ServiceMainWindow()
{
    delete ui;
}
