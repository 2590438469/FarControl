#ifndef GESHANADVANCE_H
#define GESHANADVANCE_H

#include <QObject>

class GeshanAdvance : public QObject
{
    Q_OBJECT
public:
    explicit GeshanAdvance(QObject *parent = nullptr);
    int isstartTimeEnabled;
    int startTime;
    int isendTimeEnabled;
    int endTime;

signals:

public slots:
};

#endif // GESHANADVANCE_H
