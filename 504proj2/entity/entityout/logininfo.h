#ifndef LOGININFO_H
#define LOGININFO_H

#include <QObject>

class LoginInfo : public QObject
{
    Q_OBJECT
public:
    explicit LoginInfo(QObject *parent = nullptr);
    char user[16];
    char pwd[32];

signals:

public slots:
};

#endif // LOGININFO_H
