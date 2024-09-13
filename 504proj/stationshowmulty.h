#ifndef STATIONSHOWMULTY_H
#define STATIONSHOWMULTY_H

#include <QWidget>

namespace Ui {
class StationShowMulty;
}

class StationShowMulty : public QWidget
{
    Q_OBJECT

public:
    explicit StationShowMulty(QWidget *parent = nullptr);
    ~StationShowMulty();
    void setStationString(QString station);

private:
    Ui::StationShowMulty *ui;
    QString staionString;
};

#endif // STATIONSHOWMULTY_H
