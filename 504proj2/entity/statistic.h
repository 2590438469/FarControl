#ifndef STATISTIC_H
#define STATISTIC_H

#include <QObject>

class Statistic : public QObject
{
    Q_OBJECT
public:
    explicit Statistic(QObject *parent = nullptr);
    QString people;
    int startTime;
    int endTime;

signals:

public slots:
};

#endif // STATISTIC_H
