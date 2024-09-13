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
    void setPort(QString port);
    bool isChecked;
    void setFalse();
    QString stationIp;
    QString stationName;
    QString getStationName();
    QString getPort();

private:
    Ui::StationShow *ui;
public slots:
    void indexChange(int index);
    void changeCheckedStatus();

    void changeText(QString text);
};

#endif // STATIONSHOW_H
