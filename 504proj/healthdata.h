#ifndef HEALTHDATA_H
#define HEALTHDATA_H

#include <QObject>

class HealthData : public QObject
{
    Q_OBJECT
public:
    explicit HealthData(QObject *parent = nullptr);
    QString name;
    QString delay;
    QString lost;
    QString status;
    QString dataIn;

signals:

public slots:
};

#endif // HEALTHDATA_H
