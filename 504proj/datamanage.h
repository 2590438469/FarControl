#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QWidget>

namespace Ui {
class DataManage;
}

class DataManage : public QWidget
{
    Q_OBJECT

public:
    explicit DataManage(QWidget *parent = nullptr);
    ~DataManage();

    void initialItem();

private:
    Ui::DataManage *ui;

public slots:
    void refresh();
    void doubleclick(int row,int column);
    void deleteItem();
    void advanceCheckSlot();
    void advanceResult(QString result);
};

#endif // DATAMANAGE_H
