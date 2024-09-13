#ifndef QASIOUDPSOCKET_H
#define QASIOUDPSOCKET_H

#include <QObject>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include <QAbstractSocket>

#include <thread>

#include "asio.hpp"

class QAsioUdpSocket : public QObject
{
    Q_OBJECT
protected:
    asio::io_context io_context;
    std::thread *t;
    asio::io_context::work *worker;
    asio::ip::udp::socket *socket;
    asio::ip::address *local_address;
    int bind_port;
    asio::ip::udp::endpoint sender_endpoint;
    enum { MAX_LENGTH = 65535 };
    char recv_data[MAX_LENGTH];
    int bytes_recvd;

    QAbstractSocket::BindMode bind_mode;
    bool bindToLocalAddress(quint16 port, QAbstractSocket::BindMode mode);
    void ioContextRun();
public:
    explicit QAsioUdpSocket(QObject *parent = nullptr);
    ~QAsioUdpSocket();

    bool bind(const QHostAddress &address, quint16 port = 0, QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform);
    bool bind(const QString &address, quint16 port = 0, QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform);
    bool bind(quint16 port = 0, QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform);

    void startListen();

    bool joinMulticastGroup(const QHostAddress &groupAddress);
    bool leaveMulticastGroup(const QHostAddress &groupAddress);

    bool joinMulticastGroup(const QString &groupAddress);
    bool leaveMulticastGroup(const QString &groupAddress);

    bool hasPendingDatagrams() const;
    int pendingDatagramSize() const;
    int readDatagram(char *data, int maxSize, QHostAddress *address = nullptr, quint16 *port = nullptr);

    int writeDatagram(const char *data, int size, const QHostAddress &address, quint16 port);
    int writeDatagram(const char *data, int size, const QString &address, quint16 port);
signals:
    void readyRead();
public slots:
};

#endif // QASIOUDPSOCKET_H
