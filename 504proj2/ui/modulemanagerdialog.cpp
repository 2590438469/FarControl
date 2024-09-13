#include "ui/modulemanagerdialog.h"
#include "ui_modulemanagerdialog.h"

ModuleManagerDialog::ModuleManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleManagerDialog)
{
    ui->setupUi(this);
}

ModuleManagerDialog::~ModuleManagerDialog()
{
    delete ui;
}

void ModuleManagerDialog::setModuleFactoryList(QList<ModuleInterface *> *modules)
{
    m_modules_factory = modules;
    foreach (ModuleInterface *module_factory, *m_modules_factory) {
        ui->listWidgetModules->addItem(module_factory->getModuleName());
    }
}

void ModuleManagerDialog::on_listWidgetModules_currentRowChanged(int currentRow)
{
    ui->plainTextEditModuleInfo->setPlainText((*m_modules_factory)[currentRow]->getModuleInfo());
}

void ModuleManagerDialog::on_pushButtonClose_clicked()
{
    this->close();
}
