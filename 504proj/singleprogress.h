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

    QString getName();
    QString getCode();
    QString getFileName();
    quint8 getPercent();

    int type;
    quint64 maxmum=0;
    quint64 value=0;

private:
    Ui::SingleProgress *ui;
};

#endif // SINGLEPROGRESS_H
