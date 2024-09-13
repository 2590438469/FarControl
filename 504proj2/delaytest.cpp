#include "delaytest.h"
#include <QHostAddress>
#include <QElapsedTimer>
#include <QTcpSocket>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>

DelayTest::DelayTest(QObject *parent) : QObject(parent)
{

}

void DelayTest::delayTest(MutiFile* muti)
{
    QHostAddress addr;
    addr.setAddress(muti->stationIp);
    quint16 port = 9011;

    QElapsedTimer *timer = new QElapsedTimer;
    timer->start();

    muti->testDelaySocket->connectToHost(addr, port);
    if (muti->testDelaySocket->waitForConnected(9999)) {
        qint64 elapsed = timer->elapsed();
        muti->testDelaySocket->disconnectFromHost();
        QThread::sleep(1);
        delete timer;
        emit dalayReturn(muti,elapsed);
    } else {
//        qDebug() << "Connection failed:" << muti->testDelaySocket->errorString();
        QThread::sleep(1);
        delete timer;
        emit dalayReturn(muti,9999);
    }
}
