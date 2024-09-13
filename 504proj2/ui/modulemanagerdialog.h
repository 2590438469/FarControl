#ifndef MODULEMANAGERDIALOG_H
#define MODULEMANAGERDIALOG_H

#include <QDialog>
#include <QList>

#include "frameparser_interface.h"
#include "module_interface.h"

namespace Ui {
class ModuleManagerDialog;
}

class ModuleManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleManagerDialog(QWidget *parent = nullptr);
    ~ModuleManagerDialog();
    void setModuleFactoryList(QList<ModuleInterface *> *modules);
private slots:
    void on_listWidgetModules_currentRowChanged(int currentRow);

    void on_pushButtonClose_clicked();

private:
    Ui::ModuleManagerDialog *ui;
    QList<ModuleInterface *> *m_modules_factory;
};

#endif // MODULEMANAGERDIALOG_H
