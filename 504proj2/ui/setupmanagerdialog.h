#ifndef SETUPMANAGERDIALOG_H
#define SETUPMANAGERDIALOG_H

#include <QDialog>
#include "configmodel.h"

namespace Ui {
class SetupManagerDialog;
}

class SetupManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupManagerDialog(QWidget *parent = nullptr);
    ~SetupManagerDialog();
    void setConfigModels(QVector<ConfigModel *> *config_models);

private slots:
    void on_listWidgetSetups_currentRowChanged(int currentRow);
    void on_pushButtonClose_clicked();

private:
    Ui::SetupManagerDialog *ui;
    QVector<ConfigModel *> *m_config_models;
};

#endif // SETUPMANAGERDIALOG_H
