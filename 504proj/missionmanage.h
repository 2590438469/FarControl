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

private:
    Ui::MissionManage *ui;
};

#endif // MISSIONMANAGE_H
