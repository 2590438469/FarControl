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
protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void sendStationResult(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

private:
    Ui::StationManage *ui;
signals:
    void disconnectStationManage();
};

#endif // STATIONMANAGE_H
