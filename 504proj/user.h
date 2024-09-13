#ifndef USER_H
#define USER_H

#include <QObject>
/*
 *用户实体类，包含数据库操作
*/

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
    static QList<User *> selectAllUser();

signals:

public slots:
};

#endif // USER_H
