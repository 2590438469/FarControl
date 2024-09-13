#ifndef DATAADVANCE_H
#define DATAADVANCE_H

#include <QObject>

class DataAdvance : public QObject
{
    Q_OBJECT
public:
    explicit DataAdvance(QObject *parent = nullptr);
    int ismodelEnabled;
    QString model;
    int istypeEnabled;
    QString type;
    int isstartTimeEnabled;
    int startTime;
    int isendTimeEnabled;
    int endTime;

signals:

public slots:
};

#endif // DATAADVANCE_H
