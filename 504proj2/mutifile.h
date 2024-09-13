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
    QTcpSocket *socket;
    QTcpSocket *testDelaySocket = new QTcpSocket;
    QString code;
    double packgeGet =0;
    QThread *t;
    WriteFiledata *worker;
};

#endif // MUTIFILE_H
