#ifndef DATASTATISTIC_H
#define DATASTATISTIC_H

#include <QWidget>
#include "entity/filelog.h"

namespace Ui {
class DataStatistic;
}

class DataStatistic : public QWidget
{
    Q_OBJECT

public:
    explicit DataStatistic(QWidget *parent = nullptr);
    ~DataStatistic();
    void initial();

    void initialall(QList<FileLog*> list);

private:
    Ui::DataStatistic *ui;
};

#endif // DATASTATISTIC_H
