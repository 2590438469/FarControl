#include "user.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>

User::User(QObject *parent) : QObject(parent)
{

}

QList<User *> User::selectAllUser()
{
    QSqlQuery query(db);
    QString qs = QString("select * from `usernew`");
    query.exec(qs);
    QSqlRecord rec = query.record();
    QList<User*> users;

    int code = rec.indexOf("账号");
    int realname = rec.indexOf("真实姓名");
    int phone = rec.indexOf("电话号码");
    int roleint = rec.indexOf("角色");
    int statusint = rec.indexOf("状态");
    int wrongint = rec.indexOf("错误次数");

    while (query.next())
    {
        User *user = new User();
        user->code = query.value(code).toString();
        user->name = query.value(realname).toString();
        user->phoneNumber = query.value(phone).toString();
        user->role = query.value(roleint).toString();
        user->status = query.value(statusint).toString();
        user->wrongTimes = query.value(wrongint).toInt();
        users.append(user);
    }
    return users;
}
