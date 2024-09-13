#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString code;
    QString name;
    QString phoneNumber;
    QString role;
    QString status;
    int wrongTimes;

signals:

public slots:
};

#endif // USER_H
