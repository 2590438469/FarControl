#ifndef MISSIONALLCONFIG_H
#define MISSIONALLCONFIG_H

#include <QWidget>

namespace Ui {
class MissionAllConfig;
}

class MissionAllConfig : public QWidget
{
    Q_OBJECT

public:
    explicit MissionAllConfig(QWidget *parent = nullptr);
    ~MissionAllConfig();
    void addItem();

private:
    Ui::MissionAllConfig *ui;
};

#endif // MISSIONALLCONFIG_H
