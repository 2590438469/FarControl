#ifndef SINGLEPROGRESS_H
#define SINGLEPROGRESS_H

#include <QWidget>

namespace Ui {
class SingleProgress;
}

class SingleProgress : public QWidget
{
    Q_OBJECT

public:
    explicit SingleProgress(QWidget *parent = nullptr);
    ~SingleProgress();
    void setRange(quint64 size);
    void setStationInfo(QString name);
    void setMissionCode(QString code);
    void setFileName(QString fileName);
    void setValue(quint64 value);

private:
    Ui::SingleProgress *ui;
};

#endif // SINGLEPROGRESS_H
