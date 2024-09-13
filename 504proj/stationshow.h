#ifndef STATIONSHOW_H
#define STATIONSHOW_H

#include <QWidget>

namespace Ui {
class StationShow;
}

class StationShow : public QWidget
{
    Q_OBJECT

public:
    explicit StationShow(QWidget *parent = nullptr);
    ~StationShow();
    void setName(QString name);
    void setIp(QString ip);

private:
    Ui::StationShow *ui;
    QString stationIp;
    QString stationName;
};

#endif // STATIONSHOW_H
