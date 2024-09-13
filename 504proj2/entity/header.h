#ifndef HEADER_H
#define HEADER_H

#include <QObject>

class Header : public QObject
{
    Q_OBJECT
public:
    explicit Header(QObject *parent = nullptr);
    uint32_t head = 0xFE6B2840;
    ushort packType;
    ushort sourceType;
    uint32_t sourceNum;
    ushort targetType;
    uint32_t targetNum;
    uint32_t packgeLenth;
    short  commendType;
    int32_t param1;
    int32_t param2;
    int32_t param3;
    int32_t param4;


signals:

public slots:
};

#endif // HEADER_H
