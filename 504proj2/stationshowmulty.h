#ifndef STATIONSHOWMULTY_H
#define STATIONSHOWMULTY_H

#include <QWidget>
#include "station.h"
#include "stationshow.h"

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
    void setStations(QList<Station*> list);

    void setNothing();

    bool isSend;
    void setIsSend(bool isSend);

    void addItem();
    void deletItem();
    void yes();

    void setMissionCode(QString code);
    QString code;
    QList<StationShow *> allStationShow;

private:
    Ui::StationShowMulty *ui;
    QString staionString;
    QList<Station*> stationList;
};

#endif // STATIONSHOWMULTY_H
