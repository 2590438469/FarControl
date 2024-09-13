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

void DelayTest::setIp(QString stationIp)
{
    ip = stationIp;
}

void DelayTest::delayTest(MutiFile* muti)
{
    if(muti->stationIp == ip){
        QHostAddress addr;
        addr.setAddress(muti->stationIp);
        quint16 port = 9011;

        QElapsedTimer *timer = new QElapsedTimer;
        timer->start();
        QTcpSocket *socket =new QTcpSocket(this);

        socket->connectToHost(addr, port);
        if (socket->waitForConnected(9999)) {
            qint64 connectTime = timer->elapsed(); // 记录连接成功时刻
            socket->disconnectFromHost();
            qint64 elapsed = connectTime; // 计算实际延迟
            delete timer;
            emit dalayReturn(muti, elapsed);
        } else {
            delete timer;
            emit dalayReturn(muti, 9999);
        }
        socket->deleteLater();
    }

}
