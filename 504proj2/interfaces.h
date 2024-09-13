#ifndef INTERFACES_H
#define INTERFACES_H


#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDomDocument>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QtPlugin>

union Result8Bytes{
    float f;
    int l;              //Long will cost 8 byte in x64 compiler.
    uint ul;
    uchar uc[4];
    char c[4];
};

enum PreHeadTypeEnum {
    _NO_HEAD,
    _0803,
    _1004
};

const int MAX_PARAM_NUM = 65536;


#endif // INTERFACES_H
