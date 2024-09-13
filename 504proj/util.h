#ifndef UTIL_H
#define UTIL_H

#include <QObject>

class Util : public QObject
{
    Q_OBJECT
public:
    explicit Util(QObject *parent = nullptr);
    static QByteArray getInvert(QByteArray array);

signals:

public slots:
};

#endif // UTIL_H
