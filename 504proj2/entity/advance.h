#ifndef ADVANCE_H
#define ADVANCE_H

#include <QObject>

class Advance : public QObject
{
    Q_OBJECT
public:
    explicit Advance(QObject *parent = nullptr);
    int iscodeEnabled;
    QString code;
    int isprotectEnabled;
    QString protect;
    int isstartTimeEnabled;
    int startTime;
    int isendTimeEnabled;
    int endTime;

signals:

public slots:
};

#endif // ADVANCE_H
