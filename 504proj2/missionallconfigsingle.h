#ifndef MISSIONALLCONFIGSINGLE_H
#define MISSIONALLCONFIGSINGLE_H

#include <QWidget>

namespace Ui {
class MissionAllConfigSingle;
}

class MissionAllConfigSingle : public QWidget
{
    Q_OBJECT

public:
    explicit MissionAllConfigSingle(QWidget *parent = nullptr);
    ~MissionAllConfigSingle();

private:
    Ui::MissionAllConfigSingle *ui;
};

#endif // MISSIONALLCONFIGSINGLE_H
