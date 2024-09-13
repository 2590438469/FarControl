#ifndef STATIONSELECT_H
#define STATIONSELECT_H

#include <QWidget>
#include "combolabel.h"
#include "entity/missionbasicinfo.h"

namespace Ui {
class StationSelect;
}

class StationSelect : public QWidget
{
    Q_OBJECT

public:
    explicit StationSelect(QWidget *parent = nullptr);
    explicit StationSelect(MissionBasicInfo *basic,QWidget *parent = nullptr);
    ~StationSelect();

private:
    Ui::StationSelect *ui;
    QByteArray sendArray;
    QList<QString> comboLabelList;
    QList<ComboLabel*> comboLabelList2;
    QString missionCode;
    MissionBasicInfo *missionBasicInfo;

public slots:
    void addStation();
    void deleteStation();
    void send();

signals:
    void refreshWidget();
    void finishSend(QString code);
};

#endif // STATIONSELECT_H
