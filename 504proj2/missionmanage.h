#ifndef MISSIONMANAGE_H
#define MISSIONMANAGE_H

#include <QWidget>

namespace Ui {
class MissionManage;
}

class MissionManage : public QWidget
{
    Q_OBJECT

public:
    explicit MissionManage(QWidget *parent = nullptr);
    ~MissionManage();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void sendMissionResult(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);
    void sendMissionInitial(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

private:
    Ui::MissionManage *ui;

signals:
    void disconnectMissionManage();

};

#endif // MISSIONMANAGE_H
