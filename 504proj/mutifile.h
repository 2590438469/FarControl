#ifndef MUTIFILE_H
#define MUTIFILE_H
#include <QObject>
#include <QTcpSocket>
#include "writefiledata.h"
#include <QThread>


class MutiFile
{
public:
    MutiFile();

    QString stationName;
    quint64 fileSize;
    QString stationIp;
    QString filePath;
    QTcpSocket *socket = new QTcpSocket();
    QTcpSocket *testDelaySocket = new QTcpSocket;
    QString code;
    double packgeGet =0;
    QThread *t;
    WriteFiledata *worker;

    QByteArray md5;

    int type;

    QString parentPath;
    QString user;

    quint8 isgoon;

    quint64 nowsize;
};

#endif // MUTIFILE_H
