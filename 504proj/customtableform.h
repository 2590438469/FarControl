#ifndef CUSTOMTABLEFORM_H
#define CUSTOMTABLEFORM_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class CustomTableForm;
}

class CustomTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTableForm(QWidget *parent = nullptr);
    ~CustomTableForm();
    void initialTableWidget(QStringList headlist,QStringList itemList);
    void exportExcel();
    void setPath(QString getpath);

private:
    Ui::CustomTableForm *ui;
    QString path;

signals:
    void sendExport(QTableWidget *tableWidget,QString dateDir,QString filename);
};

#endif // CUSTOMTABLEFORM_H
