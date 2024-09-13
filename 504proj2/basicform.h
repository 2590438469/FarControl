#ifndef BASICFORM_H
#define BASICFORM_H

#include <QWidget>
#include "basicinfo.h"

namespace Ui {
class BasicForm;
}

class BasicForm : public QWidget
{
    Q_OBJECT

public:
    explicit BasicForm(QWidget *parent = nullptr);
    ~BasicForm();
    int rowCount;
    void setRowCount(int count);
    QList<BasicInfo*> list;
    void setTableWidgetItem();

    void exportExcel();
    void initialTablewidget();

private:
    Ui::BasicForm *ui;
};

#endif // BASICFORM_H
