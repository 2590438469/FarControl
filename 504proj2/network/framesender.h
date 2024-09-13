#ifndef FRAMESENDER_H
#define FRAMESENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "utils.h"
#include "network/udpendpoint.h"

class FrameSender : public QObject
{
    Q_OBJECT
public:
    explicit FrameSender(const QString &address,
             const QString &interface2,
             int port,
             bool if_broadcast,
             QObject *parent = nullptr
    );
    explicit FrameSender(const UdpEndpoint &data_source,
                         QObject *parent = nullptr);
    ~FrameSender();

protected:
    QUdpSocket *udp_socket;
    QHostAddress *address;
    QHostAddress *interface3;
    int port;
    bool if_broadcast;

signals:

public slots:
    void onFrameReady(const char *proDataBuffer, int pkgLen);
};

#endif // FRAMESENDER_H
