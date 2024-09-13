#ifndef STATIONMANAGE_H
#define STATIONMANAGE_H

#include <QWidget>

namespace Ui {
class StationManage;
}

class StationManage : public QWidget
{
    Q_OBJECT

public:
    explicit StationManage(QWidget *parent = nullptr);
    ~StationManage();

private:
    Ui::StationManage *ui;
};

#endif // STATIONMANAGE_H
