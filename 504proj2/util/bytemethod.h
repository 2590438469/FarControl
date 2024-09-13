#ifndef BYTEMETHOD_H
#define BYTEMETHOD_H

#include <QObject>

class ByteMethod : public QObject
{
    Q_OBJECT
public:
    explicit ByteMethod(QObject *parent = nullptr);
    static QByteArray getInvert(QByteArray array);

signals:

public slots:
};

#endif // BYTEMETHOD_H
