#ifndef DATABUS_H
#define DATABUS_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

#include <utils.h>
#include "network/qasioudpsocket.h"
#include "network/udpendpoint.h"

class DataBus : public QObject
{
    Q_OBJECT
public:
    explicit DataBus(const QString &address,
                         const QString &interface2,
                         int port,
                         bool if_broadcast,
                         QObject *parent = nullptr);
    explicit DataBus(const UdpEndpoint &data_source,
                     QObject *parent = nullptr);
    ~DataBus();
    void start();
    void stop();
    void subscribe();
    void disSubscribe();
protected:
    QUdpSocket *udp_socket;
    //QAsioUdpSocket *udp_socket;
    QHostAddress *address, *interface3;
    int port;
    bool if_broadcast;
    int required_count;
signals:
    void packageArrived(const char *pkg, int pkg_len);
protected slots:
    void onDataRecived();
};

#endif // DATABUS_H
