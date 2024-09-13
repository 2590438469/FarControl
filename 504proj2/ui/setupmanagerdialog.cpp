#include "ui/setupmanagerdialog.h"
#include "ui_setupmanagerdialog.h"

SetupManagerDialog::SetupManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupManagerDialog)
{
    ui->setupUi(this);
}

SetupManagerDialog::~SetupManagerDialog()
{
    delete ui;
}

void SetupManagerDialog::setConfigModels(QVector<ConfigModel *> *config_models)
{
    //ui->listWidgetSetups->clear();
    m_config_models = config_models;
    foreach (ConfigModel *config_model, *m_config_models) {
        qDebug() << config_model;
        ui->listWidgetSetups->addItem(config_model->getSetupName());
    }
}

void SetupManagerDialog::on_listWidgetSetups_currentRowChanged(int currentRow)
{
    ui->labelSetupInfo->setText((*m_config_models)[currentRow]->description);
}

void SetupManagerDialog::on_pushButtonClose_clicked()
{
    this->close();
}
